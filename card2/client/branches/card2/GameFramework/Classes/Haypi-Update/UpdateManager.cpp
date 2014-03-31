//
//  UpdateManager.cpp
//
//  Created by jim kaden on 13-5-7.
//

#include "UpdateManager_imp.h"

#include "support/zip_support/unzip.h"
#include <typeinfo>
#include <algorithm>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
//#include "ScriptingCore.h"
//#include "js_bindings_config.h"
//#include "spidermonkey_specifics.h"
//#include "js_bindings_core.h"
//#include "js_bindings_system_functions.h"
//#include "js_manual_conversions.h"
//#include "Haypi-JSBObject.h"
#include "cocos2dxframework.h"
#include "Base.h"
//#include "FileUtils.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include "TriVersion.h"
#include <fstream>
#include "../Haypi-Crypt/Crypt.h"
using namespace haypi;

#ifndef CCLOG
#define CCLOG printf
#endif

#define PATH_SEPERATOR  '/'
#define PATH_SEPERATOR_STR  "/"

extern std::string Helper_getDeviceID();
extern void Helper_createDir(char* path);
extern std::string Helper_getPathForName(char* path);
extern std::string Helper_getBundleVersion();
extern bool enCryptDes(unsigned char* data, int len, unsigned char* outData, int* pLen, char* key, int keyLen);
extern bool deCryptDes(unsigned char* data, int len, unsigned char* outData, int* pLen, char* key, int keyLen);


static UpdateManagerImp* theUpdateManager = NULL;

static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}


static const char* valueForKey(const char *key, std::map<std::string, std::string>* dict)
{
    if (dict)
    {
        std::map<std::string, std::string>::iterator it = dict->find(key);
        return it!=dict->end() ? it->second.c_str() : "";
    }
    return "";
}

static std::string tempNameForUrl(std::string url)
{
    struct timeval curtime;
    gettimeofday(&curtime, NULL);
    
    char* pos = strrchr(url.c_str(), '.');
    char path[250];
    if ( pos == NULL )
        snprintf(path, 250, "%ld-%d-%d", curtime.tv_sec, curtime.tv_usec, rand());
    else
        snprintf(path, 250, "%ld-%d-%d%s", curtime.tv_sec, curtime.tv_usec, rand(), pos);
    
    return Helper_getPathForName(path);
}

void thread_route_sighandler(int sig)
{
    if ( sig == SIGUSR1 )
        CCLOG("thread_route_sighandler received SIGUSR1");
    pthread_exit(NULL);
}

bool readFileData(std::string path, std::vector<char>& buff)
{
    try
    {
        std::ifstream is(path.c_str(), std::ios::binary | std::ios::in);
        if ( is.is_open() == false )
            return false;
        while ( !is.eof())
        {
            char buf[256];
            int len = is.readsome(buf, 256);
            if ( len <= 0 )
                break;
            buff.insert(buff.end(), buf, buf+len);
        }
        is.close();
    }
    catch (...)
    {
        buff.clear();
        return false;
    }
    return true;
}

static std::string toHex(unsigned char* text, int len)
{
#define hexChar(x) (x)>=10 ? (x)-10+'A' : (x)+'0'
    unsigned char* buf = new unsigned char[len*2+1];
    unsigned char* p = buf;
    int i = 0;
    while ( i < len)
    {
        *p++ = hexChar(((text[i] >> 4) & 0x0f));
        *p++ = hexChar(text[i] & 0x0f);
        i ++;
    }
    *p = 0;
    std::string ret = std::string((char*)buf, p - buf);
    delete[] buf;
    return ret;
}

static std::string FileMd5(std::string path)
{
    unsigned char digest[16];
    MD5_CTX context;
    std::vector<char> buff;
    if ( readFileData(path, buff) == false )
        return std::string("");
    MD5Init (&context);
    MD5Update (&context, (unsigned char*)buff.data(), buff.size());
    MD5Final (digest, &context);
    return toHex(digest, 16);
}

FileList::FileInfo* FileList::FileInfo::clone()
{
    FileList::FileInfo* ret = new FileList::FileInfo();
    ret->copy(this);
    return ret;
}


void FileList::FileInfo::copy(FileList::FileInfo* other)
{
    this->name = other->name;
    this->local = other->local;
    this->md51 = other->md51;
    this->md52 = other->md52;
    this->ver = other->ver;
    this->size = other->size;
    this->url = other->url;
    this->critic = other->critic;
}

bool FileList::FileInfo::isSame(FileList::FileInfo* other)
{
    if ( this->md51 == other->md51
        && this->ver == other->ver
        && this->size == other->size
        )
    {
        if ( this->critic == 0 || this->md52 == other->md52)
        {
            return true;
        }
    }
    return false;
}

bool FileList::FileInfo::adjustInfo()
{
    UpdateManagerImp* mgr = (UpdateManagerImp*)UpdateManager::sharedInstance();
    std::string path = mgr->pathForName((char*)name.c_str());
    bool valid = true;
    if ( path == "" )
    {
        valid = false;
        CCLOG("No such file[%s] %s", name.c_str(), path.c_str());
        return false;
    }
    else
    {
        struct stat stat_;
        if ( stat(path.c_str(), &stat_) )
        {
            valid = false;
            CCLOG("Cannot stat file %s", path.c_str());
            return false;
        }
        else
        {
            size = stat_.st_size;
            unsigned char digest[16];
            haypi::MD5Data(name.c_str(), name.length(), digest);
            md51 = toHex(digest, 16);
            CCLOG("file name %s <= %s", md51.c_str(), name.c_str());
            md52 = FileMd5(path);
            CCLOG("file md5 %s <= %s", md52.c_str(), path.c_str());
        }
    }
    return true;
}

FileList::UrlInfo* FileList::UrlInfo::clone()
{
    FileList::UrlInfo* ret = new FileList::UrlInfo();
    ret->addr = addr;
    ret->name = name;
    ret->size = size;
    ret->md5 = md5;
    ret->ver = ver;
    return ret;
}

FileList::FileList(std::string path)
{
    _sversion = CURRENT_SVERSION;
    _cversion = CURRENT_CVERSION;
    if ( path.length() > 4 && strcasecmp(path.substr(path.length()-4, 4).c_str(), ".hum") == 0 )
        load(path);
    else if ( path != "" )
        parseXml(path);
}

void FileList::clear()
{
    FileInfoIterator it = _fileList.begin();
    for(; it!= _fileList.end(); it++)
    {
        delete it->second;
    }
    
    UrlInfoIterator it2 = _urlList.begin();
    for(; it2 != _urlList.end(); it2 ++)
    {
        delete it2->second;
    }
}

FileList::~FileList()
{
    clear();
}

void FileList::setFileInfo(std::string name, FileList::FileInfo* info)
{
    _fileList.insert(FileList::FileInfoPair(name, info));
}



bool FileList::parseXml(std::string path)
{
    try
    {
        std::vector<char> buff;
        if ( readFileData(path, buff ) == false )
            throw new XmlParseError();
        
        xmlSAXHandler saxHandler;
        memset( &saxHandler, 0, sizeof(saxHandler) );
        // Using xmlSAXVersion( &saxHandler, 2 ) generate crash as it sets plenty of other pointers...
        saxHandler.initialized = XML_SAX2_MAGIC;  // so we do this to force parsing as SAX2.
        saxHandler.startElement = &FileListXmlParser::startElement;
        saxHandler.endElement = &FileListXmlParser::endElement;
        saxHandler.characters = &FileListXmlParser::textHandler;
        
        FileListXmlParser parser(this);
        int result = xmlSAXUserParseMemory( &saxHandler, &parser, (const char *)buff.data(), buff.size() );
        xmlCleanupParser();
        if ( result != 0 )
        {
            throw new XmlParseError();
        }
    }
    catch (std::exception& e)
    {
        throw e;
    }
    _path = path;
    return true;
}


DownloadList* FileList::searchUrls()
{
    DownloadList* urlList = new DownloadList();
    FileListType::iterator it = _fileList.begin();
    while ( it != _fileList.end())
    {
        if ( it->second->url != "" )
        {
            std::string addr = it->second->url;
            DownloadList::UrltoNamesType::iterator it2 = urlList->_urlList.find(addr);
            if ( it2 != urlList->_urlList.end() )
            {
                CCLOG("More than one file stored in a single url found! %s => %s", it->second->name.c_str(), addr.c_str());
                it2->second.insert(it->second->name);
            }
            else
            {
                DownloadList::NamesCollection lst ;
                lst.insert(it->second->name);
                urlList->_urlList.insert(DownloadList::UrltoNamesPair(addr, lst));
            }
        }
        it ++;
    }
    return urlList;
}

void FileList::setLocal(std::string name, std::string localPath)
{
    FileInfoIterator it = _fileList.find(name);
    if ( it != _fileList.end())
    {
        it->second->local = localPath;
        CCLOG(" haypi update manager: localpath for name[%s]: %s", name.c_str(), localPath.c_str());
    }
}

std::string FileList::getLocal(std::string name)
{
    FileInfoIterator it = _fileList.find(name);
    if ( it != _fileList.end() )
        return it->second->local;
    return std::string("");
}

void FileList::setUrlInfo(std::string name, FileList::UrlInfo* info)
{
    _urlList.insert(FileList::UrlInfoPair(name, info));
}


FileList::UrlInfo* FileList::getUrlInfo(std::string name)
{
    UrlInfoIterator it = _urlList.find(name);
    if ( it != _urlList.end() )
        return (UrlInfo*)it->second;
    return NULL;
}

int FileList::validation()
{
    int ret = 0;
    UpdateManager* mgr = UpdateManager::sharedInstance();
    std::vector<std::string> removeList;
    FileInfoIterator it = _fileList.begin();
    for(; it!= _fileList.end(); it++)
    {
        std::string path = mgr->pathForName((char*)it->second->name.c_str());
        bool valid = true;
        if ( path == "")
        {
            valid = false;
            CCLOG("No such file %s", path.c_str());
        }
        else
        {
            struct stat stat_;
            if ( stat(path.c_str(), &stat_) )
            {
                valid = false;
                CCLOG("Cannot stat file %s", path.c_str());
            }
            else
            {
                if ( ! stat_.st_mode & S_IFREG )
                {
                    valid = false;
                    CCLOG("Not a regular file %s", path.c_str());
                }
                if(stat_.st_size != it->second->size)
                {
                    valid = false;
                    CCLOG("Incorrect size. %s", path.c_str());
                }
                if ( it->second->critic )
                {
                    // check md5
                    if ( it->second->md52 != FileMd5(path) )
                    {
                        valid = false;
                        CCLOG("Incorrect md5. %s", it->second->md52.c_str());
                    }
                }
            }
        }
        if ( valid == false )
        {
            removeList.push_back(it->first);
            ret ++;
        }
    }
    std::vector<std::string>::iterator it2 = removeList.begin();
    while( it2 != removeList.end() )
    {
        it = _fileList.find(*it2);
        if ( it != _fileList.end() )
        {
            _fileList.erase(it);
            delete it->second;
        }
        it2 ++;
    }
    return ret;
}

#pragma pack(1)

bool FileList::save(std::string path)
{
#define WRITE_UINT32(buf, data) {const char* p = (const char*)&data; (buf).insert((buf).end(), p, p+sizeof(uint32_t));}    
#define WRITE_STRING(buf, str) {uint32_t strLen=(str).length(); const char* p=(str).c_str(); WRITE_UINT32((buf), strLen); (buf).insert((buf).end(), p, p + strLen);}
    
    try
    {
        std::vector<char> buffer;
        
        WRITE_STRING(buffer, std::string(CURRENT_UM_VER));
        WRITE_STRING(buffer, _sversion);
        WRITE_STRING(buffer, _cversion);
        WRITE_STRING(buffer, _url);
        uint32_t number = _fileList.size();
        WRITE_UINT32(buffer, number);
        for (FileInfoIterator it = _fileList.begin(); it != _fileList.end(); it++)
        {
            WRITE_STRING(buffer, it->second->name);
            WRITE_STRING(buffer, it->second->local);
            WRITE_STRING(buffer, it->second->url);
            WRITE_STRING(buffer, it->second->md51);
            WRITE_STRING(buffer, it->second->md52);
            WRITE_STRING(buffer, it->second->ver);
            WRITE_UINT32(buffer, it->second->size);
            WRITE_UINT32(buffer, it->second->critic);
        }
        
        CryptFunctions* des = CryptFunctions::createCrypt(CryptFunctions::CM_DES_ECB);
        if ( des == NULL )
            throw new std::exception;
        int outputLen = buffer.size()+8;
        unsigned char* output = new unsigned char[outputLen];
        if ( des->encrypt((unsigned char*)buffer.data(), buffer.size(), output, &outputLen) )
        {
            std::ofstream os(path.c_str(), std::ios::binary | std::ios::out | std::ios::trunc);
            os.write((const char*)output, outputLen);
            os.close();
        }
        delete des;
        delete[] output;
    }
    catch (...)
    {
    }

    
    return true;
}
//#define READ_UINT32(p, data) {data = *(uint32_t*)(p); (p) += sizeof(uint32_t);}
//void READ_STRING(char* p, std::string& str)
//{
//    uint32_t sl=0;
//    READ_UINT32((p), sl);
//    (str)=std::string((p), sl);
//    (p)+= sl;
//}

bool FileList::load(std::string path)
{
#define READ_UINT32(p, data) {data = *(uint32_t*)(p); (p) += sizeof(uint32_t);}
#define READ_STRING(p, str) {uint32_t sl=0;READ_UINT32((p), sl); (str)=std::string((p), sl); (p)+= sl;}
    
    try
    {
        std::vector<char> buff_stream;
        if ( readFileData(path, buff_stream) == false )
            return false;
        
        CryptFunctions* des = CryptFunctions::createCrypt(CryptFunctions::CM_DES_ECB);
        if ( des == NULL )
            throw;
        int outputLen = buff_stream.size()+8;
        char* buff = new char[outputLen];
        char* p = buff;
        if ( des->decrypt((unsigned char*)buff_stream.data(), buff_stream.size(), (unsigned char*)buff, &outputLen) )
        {
            // 此处有隐患
            // 应当使用C++类来处理此buffer，暂时如此实现
            
            std::string um_ver;
            READ_STRING(p, um_ver);
            if ( um_ver != CURRENT_UM_VER )
            {
                return false;
            }
            READ_STRING(p, _sversion);
            READ_STRING(p, _cversion);
            READ_STRING(p, _url);
            uint32_t number = 0;
            READ_UINT32(p, number);
            for ( uint32_t i = 0 ; i < number; i ++)
            {
                FileInfo* fi = new FileInfo;
                READ_STRING(p, fi->name);
                READ_STRING(p, fi->local);
                READ_STRING(p, fi->url);
                READ_STRING(p, fi->md51);
                READ_STRING(p, fi->md52);
                READ_STRING(p, fi->ver);
                READ_UINT32(p, fi->size);
                READ_UINT32(p, fi->critic);
                _fileList.insert(FileInfoPair(fi->name, fi));
            }
            _path = path;
        }
        delete[] buff;
        delete des;
    }
    catch (std::exception& e)
    {
        CCLOG("FileList::load %s", e.what());
        return false;
    }
    return true;
}

bool FileList::hasSameFile(FileInfo* info)
{
    FileInfoIterator it = _fileList.find(info->name);
    if ( it != _fileList.end())
    {
        if ( it->second->isSame(info))
            return true;
    }
    return false;
}



FileList* FileList::diff(FileList* local)
{
    FileList* ret = new FileList("");
    FileInfoIterator it = _fileList.begin();
    for(; it!= _fileList.end(); it++)
    {
        if(!local->hasSameFile(it->second) ||
           UpdateManager::sharedInstance()->pathForName((char*)it->second->name.c_str()) == std::string("") )
        {
            ret->_fileList.insert(FileInfoPair(it->second->name, it->second->clone()));
        }
    }
    
    UrlInfoIterator it2 = _urlList.begin();
    for (; it2 != _urlList.end(); it2 ++)
    {
        ret->_urlList.insert(UrlInfoPair(it2->second->name, it2->second->clone()));
    }
    ret->setCVersion(_cversion);
    ret->setSVersion(_sversion);
    ret->setUrl(_url);
    return ret;
}

void FileList::combineWith(FileList* other)
{
    FileInfoIterator it = other->getFileList()->begin();
    for(; it!= other->getFileList()->end(); it++)
    {
        FileInfoIterator myIt = _fileList.find(it->first);
        FileInfo* info = NULL;
        if ( myIt != _fileList.end() )
        {
            info = myIt->second;
            info->copy(it->second);
        }
        else
        {
            info = it->second->clone();
            _fileList.insert(FileInfoPair(it->first, info));
        }
    }
    _sversion = other->_sversion;
    _cversion = other->_cversion;
    _url = other->_url;
}

void adjustInfoCallback(FileList::FileInfoPair it)
{
    it.second->adjustInfo();
}

void FileList::adjustAllInfo()
{
    std::for_each(_fileList.begin(), _fileList.end(), adjustInfoCallback);
}

// implement pure virtual methods of CCSAXDelegator
void FileListXmlParser::startElement(void *ctx, const unsigned char *name, const unsigned char **atts)
{
    FileListXmlParser* pThis = (FileListXmlParser*)ctx;
    std::string elementName = (char*)name;
    std::map<std::string, std::string> *attributeDict = new std::map<std::string, std::string>();
    //CCLOG(" startElement %s", elementName.c_str());
    if(atts && atts[0])
    {
        for(int i = 0; atts[i]; i += 2)
        {
            std::string key = (char*)atts[i];
            std::string value = (char*)atts[i+1];
            attributeDict->insert(std::pair<std::string, std::string>(key, value));
            //CCLOG(" xml:  attribute %s=%s",  key.c_str(), value.c_str());
        }
    }
    if(elementName == "haypi-um")
    {
        std::string version = valueForKey("version", attributeDict);
        if ( version != CURRENT_UM_VER )
        {
            CCLOG("Haypi Update Manager: Unsupported UM version: %s, current version %s", version.c_str(), CURRENT_UM_VER);
            throw new UMVerError();
        }
    }
    else if(elementName == "filelist")
    {
        // If this is an external tileset then start parsing that
        std::string sversion = valueForKey("sversion", attributeDict);
        std::string cversion = valueForKey("cversion", attributeDict);
        std::string upgradeUrl = valueForKey("upgradeUrl", attributeDict);
        // check version
        pThis->fileList->setSVersion( sversion );
        pThis->fileList->setCVersion( cversion );
        pThis->fileList->setUpgradeUrl(upgradeUrl);
        
        pThis->currentSection = "filelist";
    }
    else if(elementName == "urllist")
    {
        // If this is an external tileset then start parsing that
        pThis->currentSection = "urllist";
    }
    else if(elementName == "file")
    {
        if ( pThis->currentSection == "filelist" )
            pThis->lastElement = new FileList::FileInfo;
    }
    else if(elementName == "url")
    {
        if ( pThis->currentSection == "urllist" )
            pThis->lastElement = new FileList::UrlInfo;
    }
    if (attributeDict)
    {
        attributeDict->clear();
        delete attributeDict;
    }

}

void FileListXmlParser::endElement(void *ctx, const unsigned char *name)
{
    FileListXmlParser* pThis = (FileListXmlParser*)ctx;
    std::string elementName = (char*)name;
    //CCLOG(" endElement %s, text %s", elementName.c_str(), currentString.c_str());
    if(elementName == "file" )
    {
        if ( pThis->lastElement && pThis->lastElement->tag() == "file" )
        {
            FileList::FileInfo* lastFile = (FileList::FileInfo*)pThis->lastElement;
            if ( lastFile->name != "" )
                pThis->fileList->setFileInfo(lastFile->name, lastFile);
        }
        
    }
    else if (elementName == "name")
    {
        // The map element has ended
        if ( pThis->lastElement )
        {
            if ( pThis->lastElement->tag() == "file"  )
            {
                FileList::FileInfo* lastFile = (FileList::FileInfo*)pThis->lastElement;
                lastFile->name = pThis->currentString;
            }
            else if ( pThis->lastElement->tag() == "url" )
            {
                FileList::UrlInfo* lastUrl = (FileList::UrlInfo*)pThis->lastElement;
                lastUrl->name = pThis->currentString;
            }
            pThis->currentString = "";
        }
    }
    else if (elementName == "md51")
    {
        if ( pThis->lastElement )
        {
            if ( pThis->lastElement->tag() == "file"  )
            {
                FileList::FileInfo* lastFile = (FileList::FileInfo*)pThis->lastElement;
                lastFile->md51 = pThis->currentString;
            }
            pThis->currentString = "";
        }
    }
    else if (elementName == "md52")
    {
        if ( pThis->lastElement )
        {
            if ( pThis->lastElement->tag() == "file"  )
            {
                FileList::FileInfo* lastFile = (FileList::FileInfo*)pThis->lastElement;
                lastFile->md52 = pThis->currentString;
            }
            pThis->currentString = "";
        }
    }
    else if (elementName == "ver")
    {
        if ( pThis->lastElement )
        {
            if ( pThis->lastElement->tag() == "file"  )
            {
                FileList::FileInfo* lastFile = (FileList::FileInfo*)pThis->lastElement;
                lastFile->ver = pThis->currentString;
            }
            else if ( pThis->lastElement->tag() == "url" )
            {
                FileList::UrlInfo* lastUrl = (FileList::UrlInfo*)pThis->lastElement;
                lastUrl->ver = pThis->currentString;
            }
            pThis->currentString = "";
        }
    }
    else if (elementName == "size")
    {
        if ( pThis->lastElement )
        {
            if ( pThis->lastElement->tag() == "file"  )
            {
                FileList::FileInfo* lastFile = (FileList::FileInfo*)pThis->lastElement;
                lastFile->size = atoi(pThis->currentString.c_str());
            }
            else if ( pThis->lastElement->tag() == "url" )
            {
                FileList::UrlInfo* lastUrl = (FileList::UrlInfo*)pThis->lastElement;
                lastUrl->size = atoi(pThis->currentString.c_str());
            }
            pThis->currentString = "";
        }
    }
    else if (elementName == "critic")
    {
        if ( pThis->lastElement )
        {
            if ( pThis->lastElement->tag() == "file"  )
            {
                FileList::FileInfo* lastFile = (FileList::FileInfo*)pThis->lastElement;
                lastFile->critic = atoi(pThis->currentString.c_str());
            }
            pThis->currentString = "";
        }
    }
    else if (elementName == "url")
    {
        if ( pThis->lastElement )
        {
            if ( pThis->lastElement->tag() == "file"  )
            {
                FileList::FileInfo* lastFile = (FileList::FileInfo*)pThis->lastElement;
                lastFile->url = pThis->currentString;
            }
            if ( pThis->lastElement->tag() == "url" )
            {
                FileList::UrlInfo* lastUrl = (FileList::UrlInfo*)pThis->lastElement;
                pThis->fileList->setUrlInfo(lastUrl->name, lastUrl);
            }
            pThis->currentString = "";
        }
    }
    else if (elementName == "addr")
    {
        if ( pThis->lastElement )
        {
            if ( pThis->lastElement->tag() == "url" )
            {
                FileList::UrlInfo* lastUrl = (FileList::UrlInfo*)pThis->lastElement;
                lastUrl->addr = pThis->currentString;
            }
            pThis->currentString = "";
        }
    }
    else if (elementName == "addr2")
    {
        if ( pThis->lastElement )
        {
            if ( pThis->lastElement->tag() == "url" )
            {
                FileList::UrlInfo* lastUrl = (FileList::UrlInfo*)pThis->lastElement;
                lastUrl->addr2 = pThis->currentString;
            }
            pThis->currentString = "";
        }
    }
}


void FileListXmlParser::textHandler(void *ctx, const unsigned char *ch, int len)
{
    std::string pText((char*)ch,0,len);
    FileListXmlParser* pThis = (FileListXmlParser*)ctx;
    pThis->currentString += trim(pText);
}


bool DownloadList::moveFile(std::string src,std::string dst, bool deleteSrc)
{
    if ( src == dst )
        return false;
    char buff[1024];
    int len = 0;
    try
    {
        std::ifstream src_stream (src.c_str(), std::ios::binary | std::ios::in);
        std::ofstream dst_stream (src.c_str(), std::ios::binary | std::ios::out | std::ios::trunc);
        if ( src_stream.is_open() == false)
            throw new std::exception;
        if ( dst_stream.is_open() == false)
            throw new std::exception;
        
        while( !src_stream.eof() )
        {
            len = src_stream.readsome(buff, 1024);
            if ( len <= 0 )
                break;
            dst_stream.write((const char*)buff,len);
        }
        src_stream.close();
        dst_stream.close();
        
        if ( deleteSrc )
            unlink(src.c_str());

    }
    catch (...)
    {
    }
    return true;
}

bool DownloadList::download(FileList* remotelist)
{
    UrltoNamesType::iterator it = _urlList.begin();

    HTTPDownload htp;
    long size = 0;
    while ( it != _urlList.end() )
    {
        FileList::UrlInfo* urlInfo = remotelist->getUrlInfo(it->first);
        if ( urlInfo != NULL )
        {
            htp.addUrl(urlInfo->addr);
            size += urlInfo->size;
        }
        it ++;
    }

    htp.get();
    while ( htp.wait(0.5) == false && htp.state() == HTTPDownload::HD_Unfinished)
    {
        int pos = size > 0 ? htp.size() * 100 / size : 0;
        if ( pos > 99 )
            pos = 99;
        ((UpdateManagerImp*)UpdateManager::sharedInstance())->setProgress(pos);
    }
    if ( htp.state() != HTTPDownload::HD_OK )
        return false;
    
    it = _urlList.begin();
    while ( it != _urlList.end() )
    {
        FileList::UrlInfo* urlInfo = remotelist->getUrlInfo(it->first);
        std::string tempPath = htp.getDestination(urlInfo->addr);
        if ( tempPath != "" && access (tempPath.c_str(), R_OK) == 0 )
        {
            if ( isZip(tempPath))
            {
                expandZip(tempPath, &it->second, remotelist);
                unlink(tempPath.c_str());
            }
            else
            {
                std::string localSubPath = hexPath((char*)(*it->second.begin()).c_str());
                moveFile(tempPath, UpdateManager::sharedInstance()->rootPath() + localSubPath, true);
                NamesCollection::iterator nit = it->second.begin();
                while ( nit != it->second.end())
                {
                    remotelist->setLocal(*nit, localSubPath);
                    nit ++;
                }
            }
        }
        it ++;
    }
    
    ((UpdateManagerImp*)UpdateManager::sharedInstance())->setProgress(100);
    return true;
}

/*
 "src/test.js" => 'FA/test.js'
 "ccbResource/a.png' => 'GF/a.png'
 */
std::string DownloadList::hexPath(char* name)
{
    std::string ret = "";
    unsigned char digest[16];
    haypi::MD5Data(name, strlen(name),digest);
    digest[2] = 0;
    digest[1] = (digest[0] & 0x0f) + 'A';
    digest[0] = ((digest[0] >> 4) & 0x0f) + 'A';
    
    createDirectories(std::string((char*)digest));
    
    char* pos = strrchr((const char*)name, '/');
    if ( pos == NULL )
    {
        ret = std::string((char*)digest) + std::string("/") + name;
    }
    else
    {
        ret = std::string((char*)digest) + std::string(pos);
    }
    return ret;
}

bool DownloadList::isZip(std::string filepath)
{
    unzFile pFile = unzOpen(filepath.c_str());
    if (!pFile)
    {
        return false;
    }
    unzClose(pFile);
    return true;
}

bool DownloadList::createDirectories(std::string subdirs)
{

    std::string rootPath = UpdateManager::sharedInstance()->rootPath();
    bool ret = false;
    if ( subdirs.length() > 0)
    {
        if ( subdirs[0] == PATH_SEPERATOR )
        {
            // absolute path
        }
        else
        {
            int len = subdirs.length();
            int pos = subdirs.find((const char*)PATH_SEPERATOR_STR, 0, len );
            int pos_prev = 0;
            while ( pos != std::string::npos)
            {
                Helper_createDir((char*)(rootPath + subdirs.substr(pos_prev, pos - pos_prev)).c_str());
                pos ++;
                if ( len < pos )
                    break;
                pos_prev = pos ;
                pos = subdirs.find((const char*)PATH_SEPERATOR_STR, pos, len - pos );
            }
            
            if ( pos_prev != std::string::npos )
            {
                Helper_createDir((char*)(rootPath + subdirs.substr(pos_prev, len - pos_prev)).c_str());
            }
            ret = true;
        }
    }
    return ret;
}

bool DownloadList::expandZip(std::string downloadPath, DownloadList::NamesCollection* extractList, FileList* filelist)
{
    std::string rootPath = UpdateManager::sharedInstance()->rootPath();
    bool ret = true;
    do
    {
        unzFile pFile = unzOpen(downloadPath.c_str());
        if (!pFile)
        {
            ret = false;
            break;
        }
        
        unsigned char * pBuffer = NULL;
        int bufSize = 0;
        
        int nRet = unzGoToFirstFile(pFile);
        while (UNZ_OK == nRet)
        {
            char filename[260];
            unz_file_info FileInfo;
            nRet = unzGetCurrentFileInfo(pFile, &FileInfo, filename, sizeof(filename), NULL, 0, NULL, 0);
            if( UNZ_OK == nRet)
            {
                bool needUnzip = true;
                if (needUnzip)
                {
                    nRet = unzOpenCurrentFile(pFile);
                    if (UNZ_OK == nRet)
                    {
                        if (bufSize < FileInfo.uncompressed_size)
                        {
                            bufSize = FileInfo.uncompressed_size;
                            if (pBuffer)
                                delete [] pBuffer;
                            pBuffer = new unsigned char[bufSize];
                        }
                        int nSize = unzReadCurrentFile(pFile, pBuffer, FileInfo.uncompressed_size);
                        //CCAssert(nSize == 0 || nSize == (int)FileInfo.uncompressed_size, "the file size is wrong");
                        
                        if ( extractList->find(filename) != extractList->end() )
                        {
                            std::string localSubPath = hexPath(filename);
                            try
                            {
                                std::ofstream os( (rootPath + localSubPath).c_str(), std::ios::binary | std::ios::out | std::ios::trunc );
                                os.write((char*)pBuffer, nSize);
                                os.close();
                                filelist->setLocal(filename, localSubPath);
                            }
                            catch (...)
                            {
                                
                            }
                        }
                        unzCloseCurrentFile(pFile);
                    }
                }
            }
            
            nRet = unzGoToNextFile(pFile);
        }
        
        unzClose(pFile);
        ret = true;
        
        if (pBuffer)
            delete [] pBuffer;
        
    }
    while(0);
    return ret;
}

HTTPDownload::HTTPDownload()
{
    init();
}

HTTPDownload::HTTPDownload(std::string url)
{
    init();
    addUrl(url);
}

HTTPDownload::HTTPDownload(std::string url, std::string dest)
{
    init();
    addUrl(url, dest);
}

HTTPDownload::HTTPDownload(FileList::UrlInfo* info)
{
    init();

    std::string dest = tempNameForUrl(info->addr);
    addUrl(info->clone(), dest);
}

void HTTPDownload::addUrl(std::string url)
{
    std::string dest = tempNameForUrl(url);
    addUrl(url, dest);
}

void HTTPDownload::addUrl(std::string url, std::string dest)
{
    // add before thread starts
    FileList::UrlInfo* info = new FileList::UrlInfo;
    info->addr = url;
    info->addr2 = "";
    addUrl(info, dest);
}

void HTTPDownload::addUrl(FileList::UrlInfo* info, std::string dest)
{
    mapUrlToDest.insert(MapUrlToDestPair(info, dest));
}

void HTTPDownload::init()
{
    CCLOG("HTTPDownload::init");
    _size = 0;
    //thread = NULL;
    _state = HD_Idle;
    _exitFlag = false;
    pthread_cond_init(&_cond, NULL);
    pthread_mutex_init(&_mutex, NULL);
    
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&_rwLock, &attr);
}

HTTPDownload::~HTTPDownload()
{
    //if ( _state == HD_Unfinished  )
        cancel();
    CCLOG("HTTPDownload::~HTTPDownload");
    pthread_mutex_destroy(&_mutex);
    CCLOG("HTTPDownload::~HTTPDownload destroy mutex");
    pthread_cond_destroy(&_cond);
    pthread_mutex_destroy(&_rwLock);
    
    MapUrlToDestType::iterator it = mapUrlToDest.begin();
    while ( it!= mapUrlToDest.end() )
    {
        delete it->first;
        it ++;
    }
    mapUrlToDest.clear();
}

void* HTTPDownload_routine(void* param)
{
    signal(SIGUSR1, thread_route_sighandler);
    HTTPDownload* pThis = (HTTPDownload*)param;
    try
    {
        pThis->routine();
    }
    catch(...)
    {
    }
    return NULL;
}

size_t HTTPDownload::readData(void *ptr, size_t size, size_t nmemb, void *param)
{
    HTTPDownload* pThis = (HTTPDownload*)param;
    return pThis->read(ptr, size, nmemb);
}

size_t HTTPDownload::read(void* ptr, size_t size, size_t nmemb)
{
    size_t sizes = size * nmemb;
    if ( _exitFlag )
        return 0; // cause curl error and then exit
    try
    {
        if ( os.is_open() )
        {
            os.write((char*)ptr, sizes);
            incrementSize(sizes);
        }
        
    }
    catch (...)
    {
        return 0;
    }
    return sizes;
}

// HTTP Get Method
void HTTPDownload::get()
{
    //if ( thread )
    //    cancel();
    _state = HD_Unfinished;
    _size = 0;
    _getMethod = true;
    //thread = new pthread_t;
    pthread_create(&thread, NULL, &HTTPDownload_routine, this);
}

int HTTPDownload::download(std::string url)
{
#define CHECK_RET(x) if((x)!= CURLE_OK)break
    CURLcode code = CURL_LAST;
    do
    {
        int responseCode;
        char s_errorBuffer[2048];
        
        CURL *curl = curl_easy_init();
        
        CHECK_RET(curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, s_errorBuffer));
        CHECK_RET(curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60));
        CHECK_RET(curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30));
        CHECK_RET(curl_easy_setopt(curl, CURLOPT_URL, url.c_str()));
        CHECK_RET(curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, url.c_str()));
        CHECK_RET(curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HTTPDownload::readData));
        CHECK_RET(curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)this));
        CHECK_RET(curl_easy_perform(curl));
        
        code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
        if (code != CURLE_OK || responseCode != 200)
        {
            code = CURLE_HTTP_RETURNED_ERROR;
            setState(HD_error);
            break;
        }
        
        if (curl)
        {
            curl_easy_cleanup(curl);
        }

    }
    while(0);
    
    return code;
}

void HTTPDownload::routine()
{
    CURLcode code = CURLE_OK;
    
    try
    {
        MapUrlToDestType::iterator it = mapUrlToDest.begin();
        
        while ( it != mapUrlToDest.end() )
        {
            FileList::UrlInfo* info = it->first;
            CCLOG("downloading %s to %s", info->addr.c_str(), it->second.c_str());
            os.open(it->second.c_str(), std::ios::binary | std::ios::trunc | std::ios::out);
            if ( os.is_open() )
            {
                // first try
                code = (CURLcode)download(info->addr);
                if ( code != CURLE_OK )
                {
                    if ( _exitFlag )
                        break;
                    
                    if ( info->addr2 != "" )
                    {
                        // reopen for second try
                        os.close();
                        os.open(it->second.c_str(), std::ios::binary | std::ios::trunc | std::ios::out);
                        
                        if ( os.is_open() )
                        {
                            code = (CURLcode)download(info->addr2);
                        }
                    }
                }
                os.close();
            }
            
            if ( code != CURLE_OK )
                break;
            if ( _exitFlag )
                break;
            it ++;
        }
    }
    catch (...)
    {
        
    }
    
    if ( code == CURLE_OK )
        setState(HD_OK);
    
    pthread_mutex_lock(&_mutex);
    //delete thread;
    //thread = NULL;
    pthread_cond_signal(&_cond);
    pthread_mutex_unlock(&_mutex);
    pthread_detach(pthread_self());
#undef CHECK_RET
}

bool HTTPDownload::wait(float second)
{
    bool ret = true;
    pthread_mutex_lock(&_mutex);
    struct timespec ts;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    ts.tv_sec = tv.tv_sec + (int)second;
    ts.tv_nsec = (second - (int)second)* 1000000000L ;
    if ( pthread_cond_timedwait(&_cond, &_mutex, &ts) )
    {
        ret = false;
    }
    pthread_mutex_unlock(&_mutex);
    return ret;
}

void HTTPDownload::cancel()
{
    _exitFlag = true;
    //pthread_mutex_lock(&_mutex);
    //if ( thread )
    {
        int kill_ret = pthread_kill(thread, 0);
        if ( kill_ret == ESRCH )
        {
            // thread was already finished
            CCLOG("upgradeThread was already finished");
        }
        else
        {
            CCLOG("upgradeThread is canceling");
            sleep(1);
            pthread_kill(thread, SIGUSR1);
            pthread_join(thread, NULL);
        }

    }

}

HTTPDownload::HD_STATE HTTPDownload::state()
{
    HD_STATE ret = HD_error;
    pthread_mutex_lock(&_rwLock);
    ret = _state;
    pthread_mutex_unlock(&_rwLock);
    return ret;
}
void HTTPDownload::setState(HTTPDownload::HD_STATE state)
{
    pthread_mutex_lock(&_rwLock);
    _state = state;
    pthread_mutex_unlock(&_rwLock);
}

long HTTPDownload::size()
{
    long ret = 0;
    pthread_mutex_lock(&_rwLock);
    ret = _size;
    pthread_mutex_unlock(&_rwLock);
    return ret;
}

void HTTPDownload::incrementSize(long size)
{
    pthread_mutex_lock(&_rwLock);
    _size += size;
    pthread_mutex_unlock(&_rwLock);
    //CCLOG("current size %d", _size);
}

std::string HTTPDownload::getDestination(std::string url)
{
    if ( url == "" )
        return std::string("");
    MapUrlToDestType::iterator it = mapUrlToDest.begin();
    while ( it != mapUrlToDest.end() )
    {
        if ( it->first->addr == url
            || it->first->addr2 == url)
            return it->second;
        it ++;
    }
    return std::string("");
}

std::string HTTPDownload::sync_downloadFromUrl(std::string url)
{
    HTTPDownload htp;
    htp.addUrl(url);
    std::string ret = htp.getDestination(url);
    htp.get();
    
    while (!htp.wait(1) && htp.state() == HTTPDownload::HD_Unfinished);
    if ( htp.state() != HTTPDownload::HD_OK )
        ret = "";
    
    return ret;
}

UpdateManager* UpdateManager::sharedInstance()
{
    if ( theUpdateManager == NULL )
        theUpdateManager = new UpdateManagerImp();
    return theUpdateManager;
}

UpdateManagerImp::UpdateManagerImp()
{
    theUpdateManager = this;
    _progress = 0;
    _rootPath = "";
    pthread_rwlock_init(&_rwLock, NULL);
    pthread_mutex_init(&_upgradeMutex, NULL);
    _checking = false;
    setState(UMS_NoChecking);
    loadLocal();
}

UpdateManagerImp::~UpdateManagerImp()
{
    if ( _checking )
        pthread_kill(_upgradeThread, 9);
    pthread_join(_upgradeThread, NULL);
    delete _localFileList;
    _checking = false;
    pthread_mutex_destroy(&_upgradeMutex);
    pthread_rwlock_destroy(&_rwLock);
}

void UpdateManagerImp::clean()
{
    if ( _checking )
    {
        int kill_ret = pthread_kill(_upgradeThread, 0);
        if ( kill_ret == ESRCH )
        {
            // thread was already finished
            CCLOG("upgradeThread was already finished");
        }
        else
        {
            sleep(1);
            pthread_kill(_upgradeThread, SIGUSR1);
            pthread_join(_upgradeThread, NULL);
        }
    }
    
    _checking = false;
    setState(UMS_NoChecking);
    loadLocal();
}



void UpdateManagerImp::checkBundleVersion()
{
    /*
     首先检查本地随App下载的资源版本号，如果大于或者等于release存储的版本号，则清空文件列表，如果版本号小于或此文件不存在，则以release目录中资源为主
     -  ios系统从bundle中获得资源版本号文件
     -  由于android系统会自zip中解压，因此android系统的资源版本号文件从解压后的文件夹获得
     */
    TriVersion* localBundleVersion = NULL;
    TriVersion* localVersion = NULL;
    
    std::string bundleVersion = Helper_getBundleVersion();
    if ( bundleVersion != "" )
    {
        // 1.2, 1.3,
        localBundleVersion = new TriVersion(bundleVersion);
    }
    
    // 1.1.3, 1.2.3
    localVersion = new TriVersion(_localFileList->getCVersion());
 
    if ( (localBundleVersion == NULL)
        || (localVersion->compareMiddle(*localBundleVersion) == TriVersion::VCR_LessThan)
        || (localVersion->compare(*localBundleVersion) == TriVersion::VCR_LessThan)
        )
    {
        CCLOG("BundleVersion is %s, Release version is %s", bundleVersion.c_str(), _localFileList->getCVersion().c_str());
    }
    else
    {
        CCLOG("Clear cache. BundleVersion is %s, Release version is %s", bundleVersion.c_str(), _localFileList->getCVersion().c_str());
        _localFileList->clear();
    }
    
    if ( localBundleVersion )
        delete localBundleVersion;
    if ( localVersion )
        delete localVersion;
}

void UpdateManagerImp::loadLocal()
{
    _rootPath = Helper_getPathForName((char*)"");
    std::string localPath = Helper_getPathForName((char*)"local_filelist.hum");
    _localFileList = new FileList(localPath);
    _localFileList->validation();
    checkBundleVersion();
}

void* upgradeManager_route(void* context)
{
    signal(SIGUSR1, thread_route_sighandler);
    UpdateManagerImp* mgr = (UpdateManagerImp*)UpdateManager::sharedInstance();
    char* url = (char*)context;
    mgr->checkRemoteUrl(url);
    free(url);
    
    return NULL;
}


bool UpdateManagerImp::checkRemoteUrl(char* url)
{
    // download file list
    bool ret = false;
    FileList* remotelist = NULL;
    FileList* diff = NULL;
    DownloadList* urlList = NULL;
    
    do
    {
        try
        {
            setState(UMS_PreProcessing);
            std::string remoteFilelistPath = HTTPDownload::sync_downloadFromUrl(url);
            
            if ( remoteFilelistPath == "")
            {
                // 远程没有可下载的文件列表，应该认为是出错还是无错继续？
                setState(UMS_Error, UME_ConnectionLost);
                break;
            }
            
            remotelist  = new FileList(remoteFilelistPath);
            if ( remotelist == NULL )
            {
                setState(UMS_Error, UME_BadRemoteList);
                break;
            }
            
            unlink(remoteFilelistPath.c_str());
            
            remotelist->setUrl(url);
            

            TriVersion localCVer(_localFileList->getCVersion());
            TriVersion remoteCVer(remotelist->getCVersion());
            
            if ( localCVer.compare(remoteCVer) == TriVersion::VCR_BigChange )
            {
                _upgradeUrl = remotelist->getUpgradeUrl();
                setState(UMS_Error, UME_BigVersionChanged);
                break;
            }
            
            
            diff = remotelist->diff(_localFileList);
            
            if ( diff->getFileList()->size() > 0 )
            {
                urlList = diff->searchUrls();
                
                setState(UMS_Downloading);
                
                if ( !urlList->download(diff) )
                {
                    setState(UMS_Error, UME_ConnectionLost);
                    break;
                }
                
                _localFileList->combineWith(diff);
                _localFileList->adjustAllInfo();
                
                std::string localPath = Helper_getPathForName((char*)"local_filelist.hum");
                if ( !_localFileList->save(localPath) )
                {
                    setState(UMS_Error, UME_ConnectionLost);
                    break;
                }
            }
            else
            {
                CCLOG("All files are up-to-date. Skip!");
            }
            setState(UMS_OK);
            ret = true;
        }
        catch( UMVerError& e1 )
        {
            setState(UMS_Error, UME_BigVersionChanged);
            ret = false;
        }
        catch ( XmlParseError& e2)
        {
            setState(UMS_Error, UME_BadRemoteList);
            ret = false;
        }
        catch (...)
        {
            setState(UMS_Error, UME_GeneralError);
            ret = false;
        }
    }
    while(0);
    
    if ( remotelist )
        delete remotelist;
    if ( diff )
        delete diff;
    if ( urlList )
        delete urlList;
    
    // clean
    pthread_mutex_lock(&_upgradeMutex);
    _checking = false;
    pthread_mutex_unlock(&_upgradeMutex);
    
    return ret;
}

void urlEncrypt(char *bf, int length)
{
    for(int i=0;i<length;i++)
    {
        bf[i] ^= 0x78;
    }
}

bool UpdateManagerImp::checkVersion(const char* url, int deviceType , int gcType , int platform , int market )
{
    // get the remote file list
#define kAction_Upgrade 130
    bool ret = true;
    pthread_mutex_lock(&_upgradeMutex);
    if ( _checking )
        ret = false;
    else
    {
        char cmd[256];
        char encryptCmd[256];
        char base64Cmd[312];
        char urlCmd[512];
        char key[8] = {1,9,7,5,0,3,0,9};
        int len = 256;
        int len2 = 256;
        memset((char*)cmd, 0, sizeof(cmd));
        
        
        
        CryptFunctions* des = CryptFunctions::createCrypt(CryptFunctions::CM_DES_ECB);
        CryptFunctions* base64 = CryptFunctions::createCrypt(CryptFunctions::CM_Base64);
        
        snprintf(cmd, 256, "ACTION=%d&DeviceType=%d&GC=%d&Platform=%d&Market=%d&DeviceID=%s", kAction_Upgrade, deviceType, gcType, platform, market, Helper_getDeviceID().c_str() );
        int length = strlen(cmd);
        urlEncrypt(cmd, strlen(cmd));
        
        //if ( des->encrypt((unsigned char*)cmd, strlen(cmd), (unsigned char*)encryptCmd, &len) == false
        //    || base64->encrypt((unsigned char*)encryptCmd, len, (unsigned char*)base64Cmd, &len2) == false )
        if (base64->encrypt((unsigned char*)cmd, length, (unsigned char*)base64Cmd, &len2) == false)
        {
            setState(UMS_Error, UME_GeneralError);
            _checking = false;
            ret = false;
        }
        else
        {
            printf("\n%s\n",base64Cmd);
            snprintf(urlCmd, 512, "%s?param=%s", url, toHex((unsigned char*)base64Cmd, len2).c_str());
            pthread_create(&_upgradeThread, NULL, upgradeManager_route, strdup(urlCmd));
            _checking = true;
            ret = true;
        }
        delete base64;
        delete des;
    }
    pthread_mutex_unlock(&_upgradeMutex);
    return ret;
}

std::string UpdateManagerImp::pathForName(char* path)
{
    if ( _rootPath == "" || path[0] == PATH_SEPERATOR )
        return std::string("");
    
    
    std::string localPath = _localFileList->getLocal(path);
    if ( localPath == "" )
        return std::string("");
    
    std::string ret = _rootPath + localPath;
    if ( access(ret.c_str(), R_OK ) == 0 )
        return ret;
    return std::string("");
}

int UpdateManagerImp::progress()
{
    long ret = 0;
    pthread_rwlock_rdlock(&_rwLock);
    ret = _progress;
    pthread_rwlock_unlock(&_rwLock);
    return ret;
}

void UpdateManagerImp::setProgress(int progress)
{
    if ( _progress != progress )
        CCLOG("Downloading %d%%", progress);
    pthread_rwlock_wrlock(&_rwLock);
    _progress = progress;
    pthread_rwlock_unlock(&_rwLock);
}

UpdateManager::UM_STATE UpdateManagerImp::state()
{
    UM_STATE ret = UMS_Error;
    pthread_rwlock_rdlock(&_rwLock);
    ret = _state;
    pthread_rwlock_unlock(&_rwLock);
    return ret;
}

UpdateManager::UM_ERROR UpdateManagerImp::error()
{
    UM_ERROR ret = UME_NoError;
    pthread_rwlock_rdlock(&_rwLock);
    ret = _error;
    pthread_rwlock_unlock(&_rwLock);
    return ret;
}

void UpdateManagerImp::setState(UM_STATE state, UM_ERROR error)
{
    if ( _state != state )
        CCLOG("UM State change from %d to %d", _state, state);
    if ( state == UpdateManager::UMS_Error )
        CCLOG("UM Error %d", error);
    
    pthread_rwlock_wrlock(&_rwLock);
    _state = state;
    _error = error;
    pthread_rwlock_unlock(&_rwLock);
}

bool UpdateManagerImp::hasBigChange(std::string version)
{
    TriVersion incoming(version);
    TriVersion localVersion(_localFileList->getCVersion());
    return incoming.compareMiddle(localVersion) != TriVersion::VCR_Equal;
}


std::string UpdateManagerImp::getInuseVersion()
{
    std::string bundleversion = Helper_getBundleVersion();
    std::string localversion = _localFileList ? _localFileList->getCVersion(): "";
    if (bundleversion == "")
        return localversion;
    if (localversion == "")
        return bundleversion;
    TriVersion tver1(bundleversion);
    TriVersion tver2(localversion);
    
    if (tver1.compareMiddle(tver2) == TriVersion::VCR_LessThan)
        return bundleversion;
    
    if (tver1.compare(tver2) == TriVersion::VCR_BigThan)
        return localversion;
    
    return bundleversion;
}

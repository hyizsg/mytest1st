//
//  UpdateManager.h
//
//  Created by jim kaden on 13-5-7.
//

#ifndef __UPDATEMANAGER_IMP_H__
#define __UPDATEMANAGER_IMP_H__
#include <stdlib.h>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <pthread.h>
#include <curl/curl.h>
#include <fstream>
#include "UpdateManager.h"

#define CURRENT_UM_VER      "1.0.0"
#define CURRENT_SVERSION    "1.0.0"
#define CURRENT_CVERSION    "1.0.0"

namespace haypi
{
    class DownloadList;
    class FileListXmlParser;
    
    class FileList
    {
    public:
        std::string _path;      // local path for file list
        std::string _url;       // original url for file list
        std::string _sversion;
        std::string _cversion;
        std::string _upgradeUrl;
        
        class InfoElement
        {
        private:
            std::string _elementTag;
        public:
            std::string tag(){return _elementTag;}
            
        protected:
            void setTag(std::string tag){_elementTag=tag;}
        };
        
        class FileInfo : public InfoElement
        {
        public:
            std::string name;   // file name
            std::string local;  // local path
            std::string url;    // file url in short
            std::string md51;   // file name md5
            std::string md52;   // file content md5
            std::string ver;
            uint32_t size;
            uint32_t critic;    // if 1, check content md5 every time
        public:
            FileInfo(){setTag("file");}
            FileInfo* clone();
            void copy(FileInfo* other);
            bool isSame(FileInfo* other);
            bool adjustInfo();
        };
        
        class UrlInfo : public InfoElement
        {
        public:
            std::string addr;   // file URI
            std::string addr2;  // alternative file URI
            std::string name;   // file url in short (xxx.zip)
            std::string md5;    // file content md5
            std::string ver;    // file ver
            uint32_t size;      // file size
            
        public:
            UrlInfo(){setTag("url");}
            UrlInfo* clone();
        };
        
        typedef std::map<std::string, FileInfo*>::iterator FileInfoIterator;
        typedef std::pair<std::string, FileInfo*> FileInfoPair;
        typedef std::map<std::string, FileInfo*> FileListType;

        typedef std::map<std::string, UrlInfo*>::iterator UrlInfoIterator;
        typedef std::pair<std::string, UrlInfo*> UrlInfoPair;
        typedef std::map<std::string, UrlInfo*> UrlListType;
        
        FileListType _fileList;
        UrlListType _urlList;
        
    public:
        std::string getUrl(){return _url;}
        void setUrl(std::string url){_url = url;}
        std::string getUpgradeUrl(){return _upgradeUrl;}
        void setUpgradeUrl(std::string url){_upgradeUrl = url;}
        
        FileListType* getFileList(){return &_fileList;}
        void setSVersion(std::string ver){_sversion=ver;}
        void setCVersion(std::string ver){_cversion=ver;}
        std::string getSVersion(){return _sversion;}
        std::string getCVersion(){return _cversion;}
        
        void setFileInfo(std::string name, FileInfo* info);
        void setLocal(std::string name, std::string localPath);
        std::string getLocal(std::string name);
        
        void setUrlInfo(std::string name, UrlInfo* info);
        UrlInfo* getUrlInfo(std::string name);
        void adjustAllInfo();
    public:
        FileList(std::string path);
        virtual ~FileList();
        void clear();
        
        friend class FileListXmlParser;
        
        bool parseXml(std::string path);
        
        bool save(std::string path);
        bool load(std::string path);
        int validation();
        FileList* diff(FileList* to);
        void combineWith(FileList* other);
        
        bool hasSameFile(FileInfo* info);

        DownloadList* searchUrls();

    };
    
    class FileListXmlParser
    {
    public:
        FileList* fileList;
        
        FileList::InfoElement* lastElement;
        std::string currentSection;
        std::string currentString;
        
    public:
        FileListXmlParser(FileList* flist){fileList = flist;}
        bool parseXml(std::string path);
        
        static void startElement(void *ctx, const unsigned char *name, const unsigned char **atts);
        static void endElement(void *ctx, const unsigned char *name);
        static void textHandler(void *ctx, const unsigned char *ch, int len);
    };
    
    class DownloadList
    {
    public:
        typedef std::set<std::string> NamesCollection;
        
        typedef std::map<std::string, NamesCollection > UrltoNamesType;
        typedef std::pair<std::string, NamesCollection > UrltoNamesPair;
        UrltoNamesType _urlList;
    public:
        UrltoNamesType* getUrlList(){return &_urlList;}
        bool download(FileList* list);
        bool expandZip(std::string src, DownloadList::NamesCollection* fvec, FileList* flist);
        std::string hexPath(char* name);
        bool isZip(std::string filepath);
        bool createDirectories(std::string subdirs);
        bool moveFile(std::string src,std::string dst, bool deleteSrc);
    };
    
    class HTTPDownload
    {
    public:
        typedef enum
        {
            HD_OK,
            HD_Unfinished,
            HD_error,
            HD_Idle,
        }
        HD_STATE;
    private:
        pthread_t thread;
        pthread_mutex_t _rwLock;
        
        pthread_cond_t _cond;
        pthread_mutex_t _mutex;
        
        typedef std::map<FileList::UrlInfo*, std::string> MapUrlToDestType;
        typedef std::pair<FileList::UrlInfo*, std::string> MapUrlToDestPair;
        
        MapUrlToDestType mapUrlToDest;
        
        std::ofstream os;
        bool _getMethod;
        long _size;
        HD_STATE _state;
        bool _exitFlag; // android没有pthread_cancel, 用此变量模拟
        
    private:
        void setState(HD_STATE state);
        void incrementSize(long size);
        void init();
        int download(std::string url);
        
    public:
        HTTPDownload(FileList::UrlInfo*);
        HTTPDownload(std::string url);
        HTTPDownload(std::string url, std::string dest);
        HTTPDownload();
        
        ~HTTPDownload();
        void get();
        bool wait(float second);
        void cancel();
        
        HD_STATE state();
        long size();
        void addUrl(std::string url);
        void addUrl(std::string url, std::string dest);
        void addUrl(FileList::UrlInfo* info, std::string dest);
        
        std::string getDestination(std::string url);
        void routine();
        size_t read(void *ptr, size_t size, size_t nmemb);
        
    public:
        // helper
        static std::string sync_downloadFromUrl(std::string url);
        static size_t readData(void *ptr, size_t size, size_t nmemb, void *stream);
    };
    
    class UpdateManagerImp : public UpdateManager
    {
    private:
        std::string _rootPath;
        std::string _upgradeUrl;
        FileList* _localFileList;
        
        int _progress;
        bool _checking;
        UM_STATE _state;
        UM_ERROR _error;
        pthread_t _upgradeThread;
        pthread_mutex_t _upgradeMutex;
        pthread_rwlock_t _rwLock;
        
    public:
        UpdateManagerImp();
        ~UpdateManagerImp();
        bool checkVersion(const char* url, int deviceType = 0, int gcType = 0, int platform = 0, int market = 0);
        int progress();
        UM_STATE state();
        UM_ERROR error();
        void clean();
        std::string pathForName(char* path);
        std::string rootPath(){return _rootPath;}
        std::string upgradeUrl(){return _upgradeUrl;}
        std::string currentVersion(){ return _localFileList ? _localFileList->getCVersion(): "";}
        bool hasBigChange(std::string version);        
        std::string getInuseVersion();
    private:
        void loadLocal();
        void checkBundleVersion();
        void setProgress(int progress);
        void setState(UM_STATE state, UM_ERROR error = UME_NoError);
    public:
        friend class DownloadList;
        bool checkRemoteUrl(char* url);
    };
    
    class XmlParseError : public std::exception{};
    class UMVerError : public std::exception{};
};
#endif /* defined(__GameFramework__UpdateManager__) */

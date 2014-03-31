//
//  HTextReader.cpp
//  testReadtxt
//
//  Created by 周 刚 on 13-4-24.
//
//


#include "cocos2d.h"

USING_NS_CC;


#include "HTextReader.h"
#include <string.h>

#include "headers.h"
#include "HLocalString.h"

void decodeConfig(unsigned char *data, int len)
{
    for(int i=0;i<len;i++)
    {
        switch (i%3) {
            case 0:
                data[i] = data[i] ^ 0xff;
                break;
            case 1:
                data[i] = data[i] ^ 0xf1;
                break;
            case 2:
                data[i] = data[i] ^ 0xf3;
                break;
        }
    }
}

HTextReader::HTextReader(const char* file)
{
    std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(file);
    unsigned long len = 0;
    unsigned char* data = CCFileUtils::sharedFileUtils()->getFileData(fullpath.c_str(), "rt", &len);
    
    decodeConfig(data, len);
    
    m_pData = data;
    m_pIndex = data;
    if (strncmp((const char*)m_pIndex, "\xef\xbb\xbf", 3) == 0) {
        m_pIndex += 3;
    }    
    
    m_nLen = len;
    m_bDelete = true;
}

HTextReader::HTextReader(unsigned char* data, unsigned long size)
{
    m_pData = data;
    m_pIndex = data;
    if (strncmp((const char*)m_pIndex, "\xef\xbb\xbf", 3) == 0) {
        m_pIndex += 3;
    }
    m_nLen = size;
    m_bDelete = false;
}

HTextReader::~HTextReader()
{
    if(m_bDelete) delete [] m_pData;
    m_pData = NULL;
}

bool HTextReader::_isBlank(char c)
{
    return c == '\n' || c == '\r' || c == '\t' || c == ' ' || c == '\0';
}

bool HTextReader::haveNext()
{
    while (m_pIndex - m_pData < m_nLen) {
        if (_isBlank(*m_pIndex)) {
            m_pIndex++;
        }else
            break;
    }
    
    return m_pIndex - m_pData < m_nLen;
}

bool HTextReader::getNext(char *str)
{
    static HLocalString* local = NULL;
    if (local == NULL) {
        local = HLocalString::createWithPlist("LocalConfig.plist");
        local->retain();
    }
    
    
    if (haveNext()) {
        unsigned char* p = m_pIndex;
        while (p-m_pData<m_nLen && !_isBlank(*p)){
            p++;
        }
    
        strncpy(str, (const char*)m_pIndex, (p-m_pIndex));
        str[p-m_pIndex] = 0;
        
        strcpy(str, local->getLocalString(str));
        
        m_pIndex = p;
        
        return true;
    }
    return false;
}


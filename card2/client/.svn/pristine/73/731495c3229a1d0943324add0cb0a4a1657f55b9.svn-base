
#include "cocos2dxframework.h"

HNAMESPACE_BEGIN

HString* HString::create(const std::string& str) {
    HString* pRet = new HString(str);
//    pRet->autorelease();
    CC_AUTO_RELEASE(pRet);
    return pRet;
}

HString* HString::createWithFormat(const char* format, ...) {
    HString* pRet = HString::create("");
    va_list ap;
    va_start(ap, format);
    pRet->initWithFormatAndValist(format, ap);
    va_end(ap);
    
    return pRet;
}

HString* HString::createWithData(const unsigned char* pData, unsigned long nLen) {
    HString* pRet = NULL;
    if (pData != NULL)
    {
        char* pStr = (char*)malloc(nLen+1);
        if (pStr != NULL)
        {
            pStr[nLen] = '\0';
            if (nLen > 0)
            {
                memcpy(pStr, pData, nLen);
            }
            
            pRet = HString::create(pStr);
            free(pStr);
        }
    }
    return pRet;
}

HString* HString::createWithContentsOfFile(const char* pszFileName) {
    unsigned long size = 0;
    unsigned char* pData = 0;
    HString* pRet = NULL;
    pData = CCFileUtils::sharedFileUtils()->getFileData(pszFileName, "rb", &size);
    pRet = HString::createWithData(pData, size);
    CC_SAFE_DELETE_ARRAY(pData);
    return pRet;
}

HString* HString::createWithBoolean(bool value) {
    char pStr[64];
    strcpy(pStr, value ? "true" : "false");
    HString* pRet = HString::create(pStr);
    pRet->setValueType(HSVT_BOOLEAN);
    return pRet;
}

HString* HString::createWithInteger(int value) {
    char pStr[64];
    sprintf(pStr, "%d", value);
    HString* pRet = HString::create(pStr);
    pRet->setValueType(HSVT_INTEGER);
    return pRet;
}

HString* HString::createWithUInteger(unsigned int value) {
    char pStr[64];
    sprintf(pStr, "%d", value);
    HString* pRet = HString::create(pStr);
    pRet->setValueType(HSVT_UINTEGER);
    return pRet;
}

HString* HString::createWithFloat(float value) {
    char pStr[64];
    sprintf(pStr, "%f", value);
    HString* pRet = HString::create(pStr);
    pRet->setValueType(HSVT_FLOAT);
    return pRet;
}

HString* HString::createWithDouble(double value) {
    char pStr[64];
    sprintf(pStr, "%f", value);
    HString* pRet = HString::create(pStr);
    pRet->setValueType(HSVT_DOUBLE);
    return pRet;
}

bool HString::initWithFormatAndValist(const char* format, va_list ap) {
    int kMaxStringLen = (1024*32);
    
    bool bRet = false;
    char* pBuf = (char*)malloc(kMaxStringLen);
    if (pBuf != NULL) {
        vsnprintf(pBuf, kMaxStringLen, format, ap);
        m_sString = pBuf;
        free(pBuf);
        bRet = true;
    }
    return bRet;
}

HNAMESPACE_END

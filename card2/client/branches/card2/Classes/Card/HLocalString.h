//
//  HLocalString.h
//  card
//
//  Created by zhou gang on 13-11-25.
//
//

#ifndef __card__HLocalString__
#define __card__HLocalString__

class HLocalString : public CCObject {
    HSINGLETON_OBJECT(HLocalString);
    
public:
    const char* __restrict getLocalString(const char *sKey);
    void replaceString(CCNode* pNode);
    
    static string getLocalPath();
    static const char* getLocalResName(const char* orgRes);
    
    static HLocalString* createWithPlist(const char* plist);
    
protected:
    __retain CCDictionary* m_pLocalCache;
    
    
};


#define ccLocalizedString(key)        (HLocalString::getInstance()->getLocalString(key))
#define ccLocalizedStringF(key, ...)  (CCString::createWithFormat(ccLocalizedString(key), ##__VA_ARGS__)->getCString())

#define _L(key, ...) ccLocalizedStringF(key, ##__VA_ARGS__)

#endif /* defined(__card__HLocalString__) */

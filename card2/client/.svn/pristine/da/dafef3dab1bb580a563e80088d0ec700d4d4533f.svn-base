//
//  HLocalString.cpp
//  card
//
//  Created by zhou gang on 13-11-25.
//
//


#include "headers.h"
#include "HLocalString.h"
//#include "carddef.h"

HSINGLETON_OBJECT_IMP(HLocalString);

HLocalString::HLocalString()
: m_pLocalCache(NULL)
{
    
}

HLocalString::~HLocalString()
{
    CC_SAFE_RELEASE_NULL(m_pLocalCache);
}

HLocalString* HLocalString::createWithPlist(const char* plist)
{
    HLocalString* lc = new HLocalString;
    CC_AUTO_RELEASE(lc);
    
    string path =  CCFileUtils::sharedFileUtils()->fullPathForFilename((getLocalPath() + plist).c_str());
    if (CCFileUtils::sharedFileUtils()->isAbsolutePath(path)) {
        lc->m_pLocalCache = CCDictionary::createWithContentsOfFile(path.c_str());
        lc->m_pLocalCache->retain();
    }else{
        lc->m_pLocalCache = new CCDictionary;
    }
    
    return lc;
}

const char* __restrict HLocalString::getLocalString(const char *sKey){
    
    if(m_pLocalCache==NULL){
        std::string sDir=getLocalPath() + "LocalString.plist";
        m_pLocalCache=CCDictionary::createWithContentsOfFile(sDir.c_str());
        m_pLocalCache ? m_pLocalCache->retain() : (void)(m_pLocalCache = new CCDictionary);
    }
    
    CCString* value = (CCString *)m_pLocalCache->objectForKey(sKey);
    
    if (value) {
        CCLOG("LocalString: %s ==> %s", sKey, value->getCString());
    }
    
    return value ? value->getCString() : sKey;
}

string HLocalString::getLocalPath()
{
    ccLanguageType lt = kLanguageLocal;//CCApplication::sharedApplication()->getCurrentLanguage();
    
    std::string sDir;
    
    switch (lt) {
        case cocos2d::kLanguageChinese:
            sDir = kIsTaiWanChinese ? "lang/zh-Hant/" : "lang/zh-Hans/";
            break;
        default:
            sDir = "lang/zh-Hant/";
            break;
    }
    
    return sDir;
}

const char* HLocalString::getLocalResName(const char* orgRes)
{
    ccLanguageType lt= CCApplication::sharedApplication()->getCurrentLanguage();
    
    std::string fix;


    switch (lt) {
        case cocos2d::kLanguageChinese:
            fix = kIsTaiWanChinese ? "_tw" : "";
            break;
        default:
            fix = "_tw";
            break;
    }
    
    if (fix.length() > 0 && strstr(orgRes, fix.c_str()) == NULL) {
        char tmp[strlen(orgRes)+1 + fix.length()];
        strcpy(tmp, orgRes);
        
        char* p = strchr(tmp, '.');
        *p = 0;
        
        return _T("%s%s.%s", tmp, fix.c_str(), p+1);
    }
    
    return orgRes;
    
}

void HLocalString::replaceString(cocos2d::CCNode *pNode)
{
    CCLabelTTF* label = dynamic_cast<CCLabelTTF*>(pNode);
    CCControlButton* btn = dynamic_cast<CCControlButton*>(pNode);
    CCEditBox* edit = dynamic_cast<CCEditBox*>(pNode);
    
    if (edit) {
        
    }else if (btn) {
        const char* str = ccLocalizedString(btn->getTitleForState(CCControlStateNormal)->getCString());
//        HUIHelper::setButtonString(str, btn);
    }else if(label) {
        label->setString(ccLocalizedString(label->getString()));
    }else{
        CCArray* children = pNode->getChildren();
        FOREACH(CCNode*, child, children) {
            replaceString(child);
        }
    }
}
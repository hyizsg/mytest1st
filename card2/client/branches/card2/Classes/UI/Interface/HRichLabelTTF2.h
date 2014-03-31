//
//  HRichLabelTTF2.h
//  card
//
//  Created by zhou gang on 13-5-24.
//
//

#ifndef __card__HRichLabelTTF2__
#define __card__HRichLabelTTF2__
//
//#include "cocos2d.h"
//USING_NS_CC;
//
//#include "cocos-ext.h"
//USING_NS_CC_EXT;
//
#include "HGrayProtocol.h"
//
//#define _Stroke_Label_Angle_ 30

class HRichLabelTTF2 : public HRichLabelTTF, public HGrayProtocol {
    
    typedef HRichLabelTTF super;
    
public:
    
    CREATE_FUNC(HRichLabelTTF2);
    
    static HRichLabelTTF2* create(const char *string, const char *fontName, float fontSize,ccColor3B color = ccWHITE);
    
    ///
    HRichLabelTTF2();
    virtual ~HRichLabelTTF2();
    
    
    virtual void setBlack(bool var);
    virtual bool isBlack();
    
protected:
    
    bool m_bBlack;
};

class HRichLabelTTF2Loader : public HRichLabelTTFLoader {
    
public:
    virtual ~HRichLabelTTF2Loader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HRichLabelTTF2Loader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HRichLabelTTF2);
    
    virtual void onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader);
    virtual void onHandlePropTypeText(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pText, CCBReader * pCCBReader);
    virtual void parseProperties(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader); 
    std::string m_str;
};

static inline ccColor4B cc4FromString(const char* pString)
{
    const char* hex = pString;
    ++ hex;
    
    char *str;
    unsigned int value = (unsigned int)strtoll(hex, &str, 16);//十六进制
    
    int r = (value >> 16) & 0xff;
    int g = (value >> 8)  & 0xff;
    int b = (value & 0xff);
    int a = (value >> 24) & 0xff;
    
    CC_UNUSED_PARAM(a);
    
    
    return ccc4(r, g, b, a);
}

static inline CCPoint ccpFromString(const char* pString)
{
    float x = atof(pString);
    float y = atof(strchr(pString,',') +1);
    
    return ccp(x, y);
}

#endif /* defined(__card__HRichLabelTTF2__) */



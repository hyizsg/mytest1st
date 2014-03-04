//
//  HpCharaInstLoader.h
//  HpAnimationDemo
//
//  Created by zhou gang on 14-3-4.
//
//

#ifndef __HpAnimationDemo__HpCharaInstLoader__
#define __HpAnimationDemo__HpCharaInstLoader__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "HpCharaInst.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_HPAM_BEGIN

class HpCharaInstLoader : public CCNodeLoader {
    
public:
    virtual ~HpCharaInstLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HpCharaInstLoader, loader);
    
    
    virtual void onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HpCharaInst);
    
};

NS_HPAM_END

#endif /* defined(__HpAnimationDemo__HpCharaInstLoader__) */

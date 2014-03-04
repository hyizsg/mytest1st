//
//  HpCharaInstLoader.cpp
//  HpAnimationDemo
//
//  Created by zhou gang on 14-3-4.
//
//

#include "HpCharaInstLoader.h"

NS_HPAM_BEGIN

#define PROPERTY_ANIMA_NAME     "Anima Name"
#define PROPERTY_ANIMA_REPEAT   "Repeat Num"

void HpCharaInstLoader::onHandlePropTypeString(CCNode *pNode, CCNode *pParent, const char *pPropertyName, const char *pString, CCBReader *pCCBReader)
{
    HpCharaInst* inst = ((HpCharaInst *)pNode);
    
    if(strcmp(pPropertyName, PROPERTY_ANIMA_NAME) == 0) {
        inst->playAniByName(pString, true);
    } else if(strcmp(pPropertyName, PROPERTY_ANIMA_REPEAT) == 0) {
        inst->playAniByName(inst->getCurrentAnimationName()->getCString(), 0, 30, atoi(pString), false);
    } else {
        return CCNodeLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, pCCBReader);
    }
    
    
}


NS_HPAM_END
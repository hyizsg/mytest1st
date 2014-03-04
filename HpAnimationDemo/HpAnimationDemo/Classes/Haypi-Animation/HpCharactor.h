#ifndef HPCHARATOR_H
#define HPCHARATOR_H

#include "cocos2d.h"
#include "HpCharactorManager.h"
#include "HpAnimBuildVisitor.h"
#include "HpAnimation.h"

USING_NS_CC;

namespace haypi_animation{

class HpCharactor : public CCObject{
public:
    CC_SYNTHESIZE_READONLY(CCArray*, m_plist_array, PLists)
    CC_SYNTHESIZE_READONLY(CCDictionary*, m_anima_map, Animas)
public:
    HpCharactor();
    virtual ~HpCharactor();
    void build();
};

}

#endif // HPCHARATOR_H

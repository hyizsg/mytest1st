#ifndef HPANIMASTATUS_H
#define HPANIMASTATUS_H

#include "cocos2d.h"
#include "sys/types.h"

#include "HpKeyframe.h"
#include "HpCharactorManager.h"

USING_NS_CC;

namespace haypi_animation{
class HpAnimaStatus : public CCObject {
private:
    CCArray* m_pLayer_status_list;

public:
    CC_SYNTHESIZE(uint, m_uLayer_index, LayerIndex)
public:
    HpAnimaStatus();
    virtual ~HpAnimaStatus();

    void recycle();

    void setLastGKey(HpKeyframe* p_gKey, HpContentKeyframe* p_ckey);
    HpKeyframe* getLastGKey();
    HpContentKeyframe* getLastCKey();
    void clearSubAS();
    HpAnimaStatus* getSubAS();
};


class HpLayerStatus : public CCObject {
private:
    HpAnimaStatus* m_pSubani_status;
    
protected:
    CC_SYNTHESIZE_RETAIN(HpKeyframe*, m_pLastGKey, LastGKey)
    CC_SYNTHESIZE_RETAIN(HpContentKeyframe*, m_pLastCKey, LastCKey)
    
public:
    HpLayerStatus();
    ~HpLayerStatus();

    

    void recycle();
    HpAnimaStatus* getSubAS();

};
}


#endif // HPANIMASTATUS_H

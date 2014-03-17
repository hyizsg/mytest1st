/**
 * @author mingjiang.bai
 * @date 20121214
 *
 *
 */

#include "HpAnimaStatus.h"
#include "Hpheaders.h"

NS_HPAM_BEGIN


HpLayerStatus::HpLayerStatus(){
    m_pSubani_status = NULL;
    m_pLastCKey = NULL;
    m_pLastGKey = NULL;
    
    CCLog("HpLayerStatus: %d", this);
}

HpLayerStatus::~HpLayerStatus(){

}

void HpLayerStatus::recycle(){
    if(m_pSubani_status){
        HpCharactorManager::sharedManager()->recycleAS(m_pSubani_status);
        m_pSubani_status = NULL;
    }
}

HpAnimaStatus* HpLayerStatus::getSubAS(){
    if(m_pSubani_status == NULL){
        CCObject* _as =  HpCharactorManager::sharedManager()->requestAS();
        if(_as == NULL){
            HPLOG("");
        }
        m_pSubani_status = static_cast<HpAnimaStatus*>(_as);
    }
    
    return m_pSubani_status;
}




/**
 * @brief HpAnimaStatus::HpAnimaStatus
 */

HpAnimaStatus::HpAnimaStatus(){
    m_pLayer_status_list = new CCArray;
    m_fElapsed = 0;
    m_uLayer_index = 0;
    CCLog("HpAnimaStatus: %d", this);
}

HpAnimaStatus::~HpAnimaStatus(){
    CC_SAFE_RELEASE(m_pLayer_status_list);
}

void HpAnimaStatus::recycle(){
    
    CCObject* item = NULL;
    CCARRAY_FOREACH(m_pLayer_status_list, item){
        HpLayerStatus* ls = static_cast<HpLayerStatus*>(item);
        HpCharactorManager::sharedManager()->recycleLS(ls);
    }


    m_pLayer_status_list->removeAllObjects();
}

void HpAnimaStatus::setLastGKey(HpKeyframe *p_gKey, HpContentKeyframe *p_ckey){
    if(this->getLayerIndex() > m_pLayer_status_list->count()){
        CCAssert(0, "Invalid LayIndex : HpAnimaStatus::setLastGKey");
    }

    if(this->getLayerIndex() == m_pLayer_status_list->count()){
        CCObject* _ls = HpCharactorManager::sharedManager()->requestLS();
        HpLayerStatus* ls = static_cast<HpLayerStatus*>(_ls);
        ls->setLastGKey(p_gKey);
        ls->setLastCKey(p_ckey);
        m_pLayer_status_list->addObject(ls);
    } else {
        HpLayerStatus* ls = static_cast<HpLayerStatus*> (m_pLayer_status_list->objectAtIndex(this->getLayerIndex()));
        ls->setLastGKey(p_gKey);
        ls->setLastCKey(p_ckey);
    }

}

void HpAnimaStatus::clearSubAS(){
    HpLayerStatus* hls = static_cast<HpLayerStatus*>(m_pLayer_status_list->objectAtIndex(this->getLayerIndex()));
    hls->recycle();
}


HpAnimaStatus* HpAnimaStatus::getSubAS(){
    HpLayerStatus* hls = static_cast<HpLayerStatus*>(m_pLayer_status_list->objectAtIndex(this->getLayerIndex()));
    HpAnimaStatus* ret = hls->getSubAS();
    if(ret == NULL){
        HPLOG("");
    }
    return hls->getSubAS();
}

HpKeyframe* HpAnimaStatus::getLastGKey(){
    HpLayerStatus* hls = static_cast<HpLayerStatus*>(m_pLayer_status_list->objectAtIndex(this->getLayerIndex()));
    return hls->getLastGKey();
}

HpContentKeyframe* HpAnimaStatus::getLastCKey(){
    HpLayerStatus* hls = static_cast<HpLayerStatus*>(m_pLayer_status_list->objectAtIndex(this->getLayerIndex()));
    return hls->getLastCKey();
}

NS_HPAM_END

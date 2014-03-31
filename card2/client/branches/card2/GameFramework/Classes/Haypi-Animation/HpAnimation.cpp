#include "HpAnimation.h"
#include "HpLayer.h"
#include "HpLog.h"


using namespace haypi_animation;


HpAnimation::HpAnimation(int len){
    this->m_iLen = len;
    this->m_pLayer_array = new CCArray;
}

HpAnimation::HpAnimation(HpAnimation *p_ani){
    this->m_iLen = p_ani->getLength();
    this->m_pLayer_array = new CCArray;

    CCObject* p_item = NULL;
    CCARRAY_FOREACH(p_ani->getLayers(), p_item){
        HpLayer* p_layer = static_cast<HpLayer*>(p_item);
        HpLayer* p_newLayer = p_layer->clone();
        this->m_pLayer_array->addObject(p_newLayer);
    }
}

HpAnimation::~HpAnimation(){
    CC_SAFE_RELEASE(m_pLayer_array);
}


HpAnimation* HpAnimation::clone(){
    HpAnimation* ret = new HpAnimation(this);
//    ret->autorelease();
    CC_AUTO_RELEASE(ret);
    return ret;
}

HpLayer* HpAnimation::getLayerByName(CCString *p_name){

    CCObject* p_item = NULL;
    CCARRAY_FOREACH(m_pLayer_array, p_item){
        HpLayer* p_layer = static_cast<HpLayer*> (p_item);
        if(p_layer->getName()->isEqual(p_name)){
           
            return p_layer;
        }
    }
 
    return NULL;
}

bool HpAnimation::insertLayer(HpLayer *p_layer, CCString *p_target){
    if(p_layer == NULL){
        return false;
    }

    int idx = findLayerByName(p_target);
    if(idx == m_pLayer_array->count()){
        return false;
    }

    m_pLayer_array->insertObject(p_layer, idx);
    return true;
}

bool HpAnimation::replaceLayer(CCString *p_target, HpLayer *p_layer){
    if(p_layer == NULL){
        return false;
    }

    int idx = findLayerByName(p_target);
    if(idx == m_pLayer_array->count()){
        return false;
    }

    m_pLayer_array->replaceObjectAtIndex(idx, p_layer);
    return true;
}

void HpAnimation::replaceContent(CCString *p_content, CCString *p_layer, HpContentKeyframe *p_ckf){
    if(p_layer){
        HpLayer* l = getLayerByName(p_layer);
        if(l){
            l->replaceContent(p_content, p_ckf);
        }

    } else {
        
        CCObject* arrayItem = NULL;
        CCARRAY_FOREACH(m_pLayer_array, arrayItem){
            HpLayer* l = static_cast<HpLayer*>(arrayItem);
            l->replaceContent(p_content, p_ckf);
        }
    }
}


int HpAnimation::findLayerByName(CCString *p_name){
    if(p_name == NULL){
        return m_pLayer_array->count();
    }


    int i = 0;

    CCObject* arrayItem = NULL;
    CCARRAY_FOREACH(m_pLayer_array, arrayItem){
        HpLayer* p_layer = static_cast<HpLayer*>(arrayItem);
        if(p_layer->getName()->isEqual(p_name)){
            break;
        }
        ++ i;
    }

    return i;

}

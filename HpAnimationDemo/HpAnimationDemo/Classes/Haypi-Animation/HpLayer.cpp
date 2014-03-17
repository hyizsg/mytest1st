/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 *
 */

#include "HpLayer.h"

#include "Hpheaders.h"


NS_HPAM_BEGIN

/**
 * @brief HpLayer::HpLayer
 * @param p_name
 */
HpLayer::HpLayer(CCString *p_name){
    CC_SAFE_RETAIN(p_name);
    m_pName = p_name;
    m_iDura = 0;
    m_pGkey_array = new CCArray;
    m_pCkey_array = new CCArray;
    m_pGkey_indexer = new CCArray;
    m_iGkey_offset = 0;
}

/**
 * @brief HpLayer::HpLayer
 * @param p_layer
 */
HpLayer::HpLayer(HpLayer* p_layer){
    m_pName = p_layer->getName();
    m_iDura = p_layer->getDuration();
    m_pGkey_array = p_layer->getKeys();
    m_pGkey_indexer = p_layer->getIndexer();
    
    m_pName->retain();
    m_pGkey_array->retain();
    m_pGkey_indexer->retain();
    
    m_iGkey_offset = p_layer->getIndexOffset();

    m_pCkey_array = new CCArray(p_layer->getContentKeys()->count());

    CCObject* item = NULL;
    CCARRAY_FOREACH(p_layer->getContentKeys(), item){
        HpContentKeyframe* k = dynamic_cast<HpContentKeyframe*>(item);
        HpContentKeyframe* new_k = k->clone();
        m_pCkey_array->addObject(new_k);
    }
}

/**
 * @brief HpLayer::~HpLayer
 */
HpLayer::~HpLayer(){
    m_pName->release();
    m_pGkey_array->release();
    m_pCkey_array->release();
    m_pGkey_indexer->release();
}

/**
 * @brief clone
 * @return
 */
HpLayer* HpLayer::clone(){
    HpLayer* ret = new HpLayer(this);
//    ret->autorelease();
    HP_AUTO_RELEASE(ret);
    return ret;
}


/**
 * @brief HpLayer::build
 */
void HpLayer::build(){
    HPLOG("HpLayer.............................................................build");
    
    CCObject* item = NULL;
    CCARRAY_FOREACH(getKeys(), item){
        HpKeyframe* k = dynamic_cast<HpKeyframe*>(item);
        
        if(k != NULL){
            HPLOG("k is not NULL");
            
            if(k->getContent() != NULL){
                if(k->getContent()->getCString() == NULL){
                    HPLOG("");
                }
                HPLOG("apple.....%s", k->getContent()->getCString());
            } else {
                HPLOG("apple.....content = NULL");
            }
            if(k->getInterps()){
                HPLOG("Yes");
            } else {
                HPLOG("No");
            }
        } else {
            HPLOG("k == NULL");
        }
    }
    
    if(m_pCkey_array->count() == 0){

        this->indexGeneralKeys();
        this->buildContentKeys();
    }

}

/**
 * @brief HpLayer::buildContentKeys
 */
void HpLayer::buildContentKeys(){
    HpKeyframe* p_last = NULL;

    CCObject* item = NULL;
    CCARRAY_FOREACH(m_pGkey_array, item){
        HpKeyframe* p_k = dynamic_cast<HpKeyframe*> (item);
      
        if(p_last == NULL
                || p_k->getContentType() != p_last->getContentType()
                || (p_k->getContent() != NULL  && !(p_k->getContent()->isEqual(p_last->getContent())))){

            HpContentKeyframe* cf = NULL;
            if(p_k->getContentType() == HPCONTENTTYPE_IMAGE){
                cf = new HpImageKeyframe;
            } else if(p_k->getContentType() == HPCONTENTTYPE_ANIMA){
                cf = new HpAnimaKeyframe;
                ((HpAnimaKeyframe*)cf)->setIsTimeInherited(p_k->getIsTimeInherited());
            } else {
                cf = new HpNullKeyframe;
            }

            cf->setTime(p_k->getTime());
            cf->setContentName(p_k->getContent());
            
            m_pCkey_array->addObject(cf);
            cf->release();
        }
        p_last = p_k;
        p_k = NULL;
    }
}

/**
 * @brief HpLayer::indexGeneralKeys
 */
void HpLayer::indexGeneralKeys(){
    if(m_pGkey_array->count() == 0){
        m_iGkey_offset = 0;
        m_iDura = 0;
    } else {

        int i = 0;
        HpKeyframe* start_key = dynamic_cast<HpKeyframe*>(m_pGkey_array->objectAtIndex(0));
        int gindex_start = m_iGkey_offset = start_key->getTime();

        CCObject* item = NULL;
        CCARRAY_FOREACH(m_pGkey_array, item){
            HpKeyframe* k = dynamic_cast<HpKeyframe*>(item);

            for(int j = gindex_start; j < k->getTime(); ++ j){
                m_pGkey_indexer->addObject(m_pGkey_array->objectAtIndex(i - 1));
            }

            gindex_start = k->getTime();
            ++ i;
        }


        m_pGkey_indexer->addObject(m_pGkey_array->objectAtIndex(m_pGkey_array->count() - 1));
        m_iDura = m_pGkey_indexer->count() + m_iGkey_offset;
    }
}

/**
 * @brief HpLayer::getKeyframeAt
 * @param index
 * @return
 */
HpKeyframe* HpLayer::getKeyframeAt(int index){
    if(m_iDura == 0 ||m_pGkey_array == NULL || index < m_iGkey_offset){
        return NULL;
    }
    if(index >= m_iDura){
        index = m_iDura - 1;
    }
    CCObject* _retObj = m_pGkey_indexer->objectAtIndex(index - m_iGkey_offset);
    return dynamic_cast<HpKeyframe*>(_retObj);
}

/**
 * @brief HpLayer::getContentKeyframeAt
 * @param index
 * @return
 */
HpContentKeyframe* HpLayer::getContentKeyframeAt(int index){
    HPLOG("apple...m_pCkey_array->count() %d   index %d", m_pCkey_array->count(), index);
    
    HpContentKeyframe* ck = NULL;
    for (int i=0; i<m_pCkey_array->count(); i++) {
        HpContentKeyframe* tmpk = dynamic_cast<HpContentKeyframe*>(m_pCkey_array->objectAtIndex(i));
        if (tmpk->getTime() > index) {
            break;
        }
        
        ck = tmpk;
    }

    return ck;

}

/**
 * @brief HpLayer::replaceContent
 * @param p_name
 * @param p_content
 */
void HpLayer::replaceContent(CCString *p_name, HpContentKeyframe *p_content){
    for(int i = 0; i < m_pCkey_array->count(); i ++){
        CCObject* _ck = m_pCkey_array->objectAtIndex(i);
        HpContentKeyframe* ck = dynamic_cast<HpContentKeyframe*>(_ck);
        if(strcmp(ck->getContentName()->getCString(), p_name->getCString()) == 0){
            HpContentKeyframe* newck = dynamic_cast<HpContentKeyframe*>(p_content->clone());
            newck->setContentName(ck->getContentName());
            newck->setTime(ck->getTime());
            m_pCkey_array->replaceObjectAtIndex(i, newck);
        }
    }

}



NS_HPAM_END

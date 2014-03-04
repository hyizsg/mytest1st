#include "HpCharactor.h"
#include "Hpheaders.h"

NS_HPAM_BEGIN

HpCharactor::HpCharactor(){
    this->m_plist_array = new CCArray;
    this->m_anima_map = new CCDictionary;
}

HpCharactor::~HpCharactor(){
    CC_SAFE_RELEASE(m_plist_array);
    CC_SAFE_RELEASE(m_anima_map);
}


void HpCharactor::build(){
    CCObject* arrayItem = NULL;
    CCARRAY_FOREACH(m_plist_array, arrayItem){
        CCString* plist_name = static_cast<CCString*>(arrayItem);        
        HpCharactorManager::sharedManager()->loadPlist(plist_name->getCString());
    }

    HpAnimBuildVisitor* visitor = HpCharactorManager::sharedManager()->getBuilder();
    visitor->begin(this->getAnimas());
    
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(m_anima_map, pElement) {
        HpAnimation* a = static_cast<HpAnimation*>(pElement->getObject());       
        visitor->visitAnima(a, true, 0);
    }

    visitor->end();
}


NS_HPAM_END
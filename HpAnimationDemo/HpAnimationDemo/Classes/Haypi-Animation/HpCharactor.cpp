#include "HpCharactor.h"
#include "HpLog.h"

using namespace haypi_animation;

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
        HpCharactorManager::SharedCharactorManager()->loadPlist(plist_name);
    }

    HpAnimBuildVisitor* visitor = HpCharactorManager::SharedCharactorManager()->getBuilder();
    visitor->begin(this->getAnimas());
    
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(m_anima_map, pElement) {
        HpAnimation* a = static_cast<HpAnimation*>(pElement->getObject());       
        visitor->visitAnima(a, true, 0);
    }

    visitor->end();
}

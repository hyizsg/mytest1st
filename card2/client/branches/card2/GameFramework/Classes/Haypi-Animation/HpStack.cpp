/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 *
 */

#include "HpStack.h"

#include "HpLog.h"


using namespace haypi_animation;


HpStack::HpStack(){
    this->m_cArray = new CCArray();
}

HpStack::HpStack(int capacity){
    this->m_cArray = new CCArray(capacity);
}


HpStack::~HpStack(){
    CC_SAFE_RELEASE(m_cArray);
}

void HpStack::push(CCObject* item){
    if(item == NULL){
        HPLOG("");
    }
    this->m_cArray->addObject(item);
}

CCObject* HpStack::pop(){
    HPLOG("pop..............................%d", m_cArray->count());
    if(m_cArray->count() > 0){
       
        CCObject* item = m_cArray->objectAtIndex(m_cArray->count() - 1);
        m_cArray->removeObjectAtIndex(m_cArray->count() - 1);
        if(item == NULL){
            HPLOG("test");
        }
        return item;
    }
    return NULL;
}

CCObject* HpStack::peek(){
   
    if(getCount() > 0){
        return m_cArray->objectAtIndex(getCount() - 1);
    }
    return NULL;

}

void HpStack::clear(){
    m_cArray->removeAllObjects();
}

int HpStack::getCount(){
    return m_cArray->count();
}

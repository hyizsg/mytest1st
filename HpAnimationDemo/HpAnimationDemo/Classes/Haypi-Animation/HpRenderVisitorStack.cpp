#include "HpRenderVisitorStack.h"



NS_HPAM_BEGIN

HpAffineTransformStack::HpAffineTransformStack(int capacity){
    m_capacity = MAX(1, capacity);
    m_top = 0;
    m_array = (CCAffineTransform*)malloc(m_capacity * sizeof(CCAffineTransform));
}

HpAffineTransformStack::~HpAffineTransformStack(){
    free(m_array);
}

void HpAffineTransformStack::resize(int capacity){
    if(capacity < MAX(m_top, 1))
        return;

    CCAffineTransform* new_array = (CCAffineTransform*)malloc(capacity * sizeof(CCAffineTransform));
    memcpy(new_array, m_array, m_top * sizeof(CCAffineTransform));
    free(m_array);
    m_array = new_array;
}

CCAffineTransform* HpAffineTransformStack::pop(){
    if(m_top > 0)
        return &m_array[-- m_top];
    return NULL;
}

CCAffineTransform* HpAffineTransformStack::peek(){
    if(m_top > 0)
        return &m_array[m_top - 1];
    return NULL;
}

void HpAffineTransformStack::push (CCAffineTransform* p_transform){
    if(m_capacity == m_top)
        resize(2 * m_capacity);
    m_array[m_top ++] = *p_transform;
}

    
    
    
    /*
     *
     *
     *  HpColorStack
     *
     */
    
    
HpColorStack::HpColorStack(int capacity){
    m_capacity = MAX(1, capacity);
    m_top = 0;
    m_array = (ccColor4F*)malloc(m_capacity * sizeof(ccColor4F));
}

    HpColorStack::~HpColorStack(){
        free(m_array);
    }
    
void HpColorStack::resize(int capacity){
    if(capacity < MAX(m_top, 1))
        return;

    ccColor4F* new_array = (ccColor4F*)malloc(capacity * sizeof(ccColor4F));
    memcpy(new_array, m_array, m_top * sizeof(ccColor4F));
    free(m_array);
    m_array = new_array;
}

ccColor4F* HpColorStack::pop(){
    if(m_top > 0)
        return &m_array[-- m_top];
    return NULL;
}

ccColor4F* HpColorStack::peek(){
    if(m_top > 0)
        return &m_array[m_top - 1];
    return NULL;
}

void HpColorStack::push (ccColor4F* p_color){
    if(m_capacity == m_top)
        resize(2 * m_capacity);
    m_array[m_top ++] = *p_color;
}


NS_HPAM_END

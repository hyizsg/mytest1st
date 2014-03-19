#ifndef HPRENDERVISITORSTACK_H
#define HPRENDERVISITORSTACK_H

#include "math.h"
#include "cocos2d.h"
#include "Hpheaders.h"

USING_NS_CC;

//NS_HPAM_BEGIN

template <typename T>
class HpStack : public CCObject {
private:
    T* m_array;
    int m_capacity;
    int m_top;
    
public:
    HpStack(int capacity)
    {
        m_capacity = MAX(1, capacity);
        m_top = 0;
        m_array = (T*)malloc(m_capacity * sizeof(T));
    }
    
    virtual ~HpStack()
    {
        free(m_array);
    }
    
    void resize(int capacity)
    {
        if(capacity < MAX(m_top, 1))
            return;
        
        T* new_array = (T*)malloc(capacity * sizeof(T));
        memcpy(new_array, m_array, m_top * sizeof(T));
        free(m_array);
        m_array = new_array;
    }
    
    T* pop()
    {
        if(m_top > 0)
            return &m_array[-- m_top];
        return NULL;
    }
    
    T* peek()
    {
        if(m_top > 0)
            return &m_array[m_top - 1];
        return NULL;
    }
    
    void push (T* p_transform)
    {
        if(m_capacity == m_top)
            resize(2 * m_capacity);
        m_array[m_top ++] = *p_transform;
    }
    
};

typedef struct _tRenderInfo {
    CCAffineTransform tf;
    ccColor4F color;
    ccColor4F light;
    float gray;
}HpRenderInfo;


typedef HpStack<HpRenderInfo> HpRenderStack;


//NS_HPAM_END

#endif // HPRENDERVISITORSTACK_H

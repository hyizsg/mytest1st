#ifndef HPRENDERVISITORSTACK_H
#define HPRENDERVISITORSTACK_H

#include "math.h"

#include "cocos2d.h"

USING_NS_CC;

namespace haypi_animation{
class HpAffineTransformStack : public CCObject{
private:
    CCAffineTransform* m_array;
    int m_capacity;
    int m_top;

public:
    HpAffineTransformStack(int capacity);
    virtual ~HpAffineTransformStack();

    void resize(int capacity);
    CCAffineTransform* pop();
    CCAffineTransform* peek();
    void push (CCAffineTransform* p_transform);

};

class HpColorStack : public CCObject {
private:
    ccColor4F* m_array;
    int m_capacity;
    int m_top;

public:

    HpColorStack(int capacity);
    ~HpColorStack();
    void resize(int capacity);

    ccColor4F* pop();
    ccColor4F* peek();

    void push (ccColor4F* p_color);
};
}

#endif // HPRENDERVISITORSTACK_H

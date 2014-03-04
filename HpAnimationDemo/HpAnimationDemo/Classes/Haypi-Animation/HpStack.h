/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 *
 */

#ifndef HPSTACK_H
#define HPSTACK_H

#include "cocos2d.h"
#include "Hpheaders.h"

USING_NS_CC;

NS_HPAM_BEGIN
class HpStack : public cocos2d::CCObject{
private:
    cocos2d::CCArray* m_cArray;
public:
    HpStack();
    HpStack(int capacity);
    virtual ~HpStack();

    void push(CCObject* item);
    CCObject* pop();
    CCObject* peek();
    void clear();
    int getCount();
    const CCArray* getArray() {return m_cArray;}

};


NS_HPAM_END

#endif // HPSTACK_H

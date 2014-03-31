//
//  HCallFunc.h
//  card2
//
//  Created by zhou gang on 14-2-11.
//
//

#ifndef __card2__HCallFunc__
#define __card2__HCallFunc__

typedef void (CCObject::*SEL_CallFuncI)(int value);
#define callfuncI_selector(_SELECTOR) (SEL_CallFuncI)(&_SELECTOR)


class HCallFuncI : public CCCallFunc {
    
    
public:
    static HCallFuncI * create(CCObject* pSelectorTarget, SEL_CallFuncI selector, int value);
    virtual void execute();
    
protected:
    
	int m_nValue;
};


template <class T, class Y>
class HCallFuncT : public CCCallFunc {
    
public:
    typedef void (CCObject::*SEL_CallFuncT)(T tvalue, Y yvalue);
    
public:
    static HCallFuncT<T, Y> * create(CCObject* pSelectorTarget, SEL_CallFuncT selector, T tvalue, Y yvalue)
    {
        HCallFuncT<T, Y>* call = new HCallFuncT<T, Y>;
        
        call->initWithTarget(pSelectorTarget);
        call->m_pCallFunc = (SEL_CallFunc)selector;
        call->m_pCache = new CCArray;
        
        call->m_tValue = tvalue;
        call->m_yValue = yvalue;
        
        string name1 = typeid(tvalue).name();
        if (name1 == "i" || name1 == "d" || name1 == "f") {
            
        }else{
            tvalue != 0 ? call->m_pCache->addObject((CCObject*)tvalue) : (void)tvalue;
        }
        
        string name2 = typeid(yvalue).name();
        if (name2 == "i" || name2 == "d" || name2 == "f") {
            
        }else{
            yvalue != 0 ? call->m_pCache->addObject((CCObject*)yvalue) : (void)yvalue;
        }
        
        //        call->autorelease();
        CC_AUTO_RELEASE(call);
        return call;
    }
    
    virtual void execute()
    {
        if (m_pCallFuncO) {
            (m_pSelectorTarget->*((SEL_CallFuncT)m_pCallFunc))(m_tValue, m_yValue);
        }
    }
    
    HCallFuncT(){}
    virtual ~HCallFuncT(){ CC_SAFE_RELEASE_NULL(m_pCache); }
    
    T m_tValue;
    Y m_yValue;
    
    CCArray* m_pCache;
};


typedef HCallFuncT<int, int> HCallFuncII;
#define callfuncII_selector(_SELECTOR) (HCallFuncII::SEL_CallFuncT)(&_SELECTOR)


typedef HCallFuncT<CCObject*, int> HCallFuncOI;
#define callfuncOI_selector(_SELECTOR) (HCallFuncOI::SEL_CallFuncT)(&_SELECTOR)



#endif /* defined(__card2__HCallFunc__) */

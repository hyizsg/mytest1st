//
//  HGrayProtocol.h
//  card
//
//  Created by 周 刚 on 13-4-30.
//
//

#ifndef __card__HGrayProtocol__
#define __card__HGrayProtocol__

class HGrayProtocol {
    
public:
    virtual void setBlack(bool var) = 0;
    virtual bool isBlack() = 0;
};

class HGrayObject : public HGrayProtocol {
    
public:
    
    HGrayObject(): m_bBlack(false){}
    virtual ~HGrayObject(){}

    
    virtual bool isBlack() { return m_bBlack; }
    
    virtual void setBlack(bool var) {
//        if (m_bBlack != var)
        {
            m_bBlack = var;
            setBlackOnChildren(var, dynamic_cast<CCNode*>(this));
        }
    }
    
    static void setBlackOnChildren(bool var, CCNode* node) {
        CCObject* child;
        CCArray* children=node->getChildren();
        CCARRAY_FOREACH(children, child)
        {
            HGrayProtocol* pNode = dynamic_cast<HGrayProtocol*>(child);
            if (pNode) {
                pNode->setBlack(var);
            }
            setBlackOnChildren(var, (CCNode*)child);
        }
    }
    
protected:
    bool m_bBlack;
};

#endif /* defined(__card__HGrayProtocol__) */

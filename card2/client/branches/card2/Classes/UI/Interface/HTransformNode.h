//
//  HTransformNode.h
//  card
//
//  Created by zhou gang on 13-5-18.
//
//

#ifndef __card__HTransformNode__
#define __card__HTransformNode__

#include "HpTransformProtocol.h"

class HTransformNode : public CCLayer,  public haypi_animation::HpTransformProtocol {
    
    
public:
    CC_PROPERTY_PASS_BY_REF(CCAffineTransform, m_tTransform, Transform);
    
    HCREATE_FUNC(HTransformNode);
    
    HTransformNode();
    ~HTransformNode();
    
    virtual CCAffineTransform nodeToParentTransform(void);
};

class HTransformNodeLoader : public CCLayerLoader {
    
    
public:
    virtual ~HTransformNodeLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HTransformNodeLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HTransformNode);
};

#endif /* defined(__card__HTransformNode__) */

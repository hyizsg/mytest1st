//
//  HTransformProtocol.h
//  card
//
//  Created by zhou gang on 13-5-18.
//
//

#ifndef __card__HTransformProtocol__
#define __card__HTransformProtocol__

#include "cocos2d.h"
#include "Hpheaders.h"

USING_NS_CC;

NS_HPAM_BEGIN
class HpTransformProtocol
{
public:
    virtual void setTransform(const CCAffineTransform& m) = 0;
    virtual const CCAffineTransform& getTransform() = 0;
    
};

NS_HPAM_END



#endif /* defined(__card__HTransformProtocol__) */

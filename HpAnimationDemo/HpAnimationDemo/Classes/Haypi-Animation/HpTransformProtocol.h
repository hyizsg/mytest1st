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

USING_NS_CC;

namespace haypi_animation{
    class HpTransformProtocol {
    public:
        virtual void setTransform(const CCAffineTransform& m) = 0;
        virtual const CCAffineTransform& getTransform() = 0;
        
    };
}

#endif /* defined(__card__HTransformProtocol__) */

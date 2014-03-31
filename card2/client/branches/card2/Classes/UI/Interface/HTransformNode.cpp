//
//  HTransformNode.cpp
//  card
//
//  Created by zhou gang on 13-5-18.
//
//



#include "../../headers.h"

HTransformNode::HTransformNode()
{
    m_tTransform = CCAffineTransformIdentity;
}

HTransformNode::~HTransformNode()
{
    
}


CCAffineTransform HTransformNode::nodeToParentTransform(void)
{
    return CCAffineTransformConcat(CCNode::nodeToParentTransform(), m_tTransform);
}

void HTransformNode::setTransform(const cocos2d::CCAffineTransform &var)
{
    m_tTransform = var;
    CCNode::m_bTransformDirty = true;
}

const CCAffineTransform& HTransformNode::getTransform()
{
    return m_tTransform;
}

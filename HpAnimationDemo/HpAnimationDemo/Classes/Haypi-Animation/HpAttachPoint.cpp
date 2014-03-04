#include "HpAttachPoint.h"
#include "HpTransformProtocol.h"

NS_HPAM_BEGIN


HpAttachPoint::HpAttachPoint(){
    m_object_attached = new CCArray;
    m_layerInst = NULL;
    m_layerName = NULL;
    m_animaName = NULL;
}

HpAttachPoint::~HpAttachPoint(){
    CC_SAFE_RELEASE(m_object_attached);
    CC_SAFE_RELEASE(m_layerName);
    CC_SAFE_RELEASE(m_layerInst);
    CC_SAFE_RELEASE(m_animaName);
}

void HpAttachPoint::attach(CCNode *p_obj){
    int i = 0;
    for(; i < m_object_attached->count(); ++ i){
        if(m_object_attached->objectAtIndex(i)->isEqual(p_obj)){
            break;
        }
    }

    if(i == m_object_attached->count()){
        m_object_attached->addObject(p_obj);
    }
}

void HpAttachPoint::remove(CCNode *p_obj){
    m_object_attached->removeObject(p_obj);
}


void HpAttachPoint::apply(const CCAffineTransform& m, const ccColor4F& color)
{
    if(getLayerInst()) {
        
        CCObject* item = NULL;
        CCARRAY_FOREACH(m_object_attached, item){
            CCNode* obj = static_cast<CCNode*>(item);
            HpTransformProtocol* node = dynamic_cast<HpTransformProtocol*>(obj);
            if (node != NULL) {
                node->setTransform(m);
//                CCLOG("{%.3f, %.3f, %.3f, %.3f, %.3f, %.3f}",
//                      m.a, m.b, m.c, m.d, m.tx, m.ty);
            }else{
                obj->setScaleX(m.a);
                obj->setScaleY(m.d);
                obj->setSkewX(CC_RADIANS_TO_DEGREES(atan(m.c/m.a)));
                obj->setSkewY(CC_RADIANS_TO_DEGREES(atan(m.b/m.d)));
                obj->setPosition(m.tx, m.ty);
////                
//                CCAffineTransform mm = obj->nodeToParentTransform();
//                
//                CCLOG("{%.3f, %.3f, %.3f, %.3f, %.3f, %.3f}=>{%.3f, %.3f, %.3f, %.3f, %.3f, %.3f}",
//                      m.a, m.b, m.c, m.d, m.tx, m.ty, mm.a, mm.b, mm.c, mm.d, mm.tx, mm.ty);
            }
            
            CCRGBAProtocol* node2 = dynamic_cast<CCRGBAProtocol*>(obj);
            if (node2 != NULL) {
                node2->setColor(ccc3(color.r*255, color.g*255, color.b*255));
                node2->setOpacity(color.a*255);
            }
        }
    }
}

NS_HPAM_END

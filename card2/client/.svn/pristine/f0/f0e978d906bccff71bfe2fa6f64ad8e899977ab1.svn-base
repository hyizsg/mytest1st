//
//  HRGBObject.h
//  card
//
//  Created by zhou gang on 13-7-3.
//
//

#ifndef __card__HRGBObject__
#define __card__HRGBObject__

class HRGBObject : public CCRGBAProtocol {
    
    
public:
    
    HRGBObject();
    virtual ~HRGBObject();
    
    CC_PROPERTY(GLubyte, m_cOpacity, Opacity);
    CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color);
    CC_PROPERTY_BOOL(bool, m_bIsOpacityModifyRGB, OpacityModifyRGB);
    

    virtual const ccColor3B& getDisplayedColor(void) { return ccWHITE; }
    virtual GLubyte getDisplayedOpacity(void) { return 0; }
    virtual bool isCascadeColorEnabled(void) { return false; }
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled) {}
    virtual void updateDisplayedColor(const ccColor3B& color) {}
    virtual bool isCascadeOpacityEnabled(void) { return false; }
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) {}
    virtual void updateDisplayedOpacity(GLubyte opacity) {}
    
public:
    static void setOpacityOnChildren(GLubyte opacity, CCNode* root);
    static void setColorOnChildren(const ccColor3B& color, CCNode* root);
    static void setOpacityModifyRGBOnChildren(bool bModify, CCNode* root);
};

#endif /* defined(__card__HRGBObject__) */

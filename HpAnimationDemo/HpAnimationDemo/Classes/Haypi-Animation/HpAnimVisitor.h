/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 *
 */

#ifndef HPANIMVISITOR_H
#define HPANIMVISITOR_H

#include "cocos2d.h"
#include "HpLog.h"


NS_HPAM_BEGIN

class HpAnimation;
class HpLayer;
class HpKeyframe;
class HpImageKeyframe;
class HpAnimaKeyframe;
class HpNullKeyframe;


class HpAnimVisitor : public cocos2d::CCObject{
public:
    virtual void begin(CCObject* p_map) = 0;
    virtual void end() = 0;
    virtual void visitAnima(HpAnimation* p_ani,bool p_first,float p_frm) = 0;
    virtual void visitLayer(HpLayer* p_layer,bool p_first,float p_frm) = 0;
    virtual void visitNullKey(HpNullKeyframe* p_nkf,HpKeyframe* p_frm,float time) = 0;
    virtual void visitImageKey(HpImageKeyframe* p_ikf,HpKeyframe* p_frm,float time) = 0;
    virtual void visitAnimaKey(HpAnimaKeyframe* p_akf,HpKeyframe* p_frm,float time) = 0;
};
    
class HpCharactor;

class HpCharactorParser : public cocos2d::CCObject
{
    
public:
    virtual HpCharactor* parse(const char* p_file) = 0;
    
};

NS_HPAM_END

#endif // HPANIMVISITOR_H

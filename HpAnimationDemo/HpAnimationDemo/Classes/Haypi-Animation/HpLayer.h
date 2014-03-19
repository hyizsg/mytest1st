/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 *
 */

#ifndef HPLAYER_H
#define HPLAYER_H

#include "cocos2d.h"

#include "HpKeyframe.h"
#include "HpAnimaKeyframe.h"
#include "HpImageKeyframe.h"
#include "HpNullKeyframe.h"

USING_NS_CC;

NS_HPAM_BEGIN

class HpKeyframe;
class HpContentKeyframe;

class HpLayer : public CCObject{
private:

    CC_SYNTHESIZE_READONLY(CCString*, m_pName, Name)
    CC_SYNTHESIZE_READONLY(CCArray*, m_pGkey_array, Keys)
    CC_SYNTHESIZE_READONLY(CCArray*, m_pCkey_array, ContentKeys)
    CC_SYNTHESIZE_READONLY(int, m_iDura, Duration)
    CC_SYNTHESIZE_READONLY(CCArray*, m_pGkey_indexer, Indexer)
    CC_SYNTHESIZE_READONLY(int, m_iGkey_offset, IndexOffset)

public:
    HpLayer(CCString* p_name);
    HpLayer(HpLayer* p_layer);

    virtual ~HpLayer();

    HpLayer* clone();
    void build();

    HpKeyframe* getKeyframeAt(int index);
    HpContentKeyframe* getContentKeyframeAt(int index);
    void replaceContent(CCString* p_name, HpContentKeyframe* p_content);
private:
    void buildContentKeys();
    void indexGeneralKeys();

};



NS_HPAM_END

#endif // HPLAYER_H

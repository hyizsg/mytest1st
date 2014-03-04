//
//  HpCharactorBinParser.h
//  Cocos2DxFirstlosSample
//
//  Created by zhou gang on 13-3-7.
//
//

#ifndef __Cocos2DxFirstlosSample__HpCharactorBinParser__
#define __Cocos2DxFirstlosSample__HpCharactorBinParser__

#include "HpAnimVisitor.h"

#include "cocos2d.h"
USING_NS_CC;

namespace haypi_animation{

class HpCharactor;
class HpAnimation;
class HpLayer;
class HpKeyframe;
class HpBinaryReader;

class HpCharactorBinParser : public HpCharactorParser
{
    HpCharactor* m_cur_chara;
    HpAnimation* m_cur_anima;
    HpLayer* m_cur_layer;
    HpKeyframe* m_cur_keyfrm;
    
public:
    virtual HpCharactor* parse(const char* p_file);
    
protected:
    void readAnimation(HpBinaryReader* reader, char* buffer);
    void readLayer(HpBinaryReader* reader, char* buffer);
    void readKeyFrame(HpBinaryReader* reader, char* buffer);
    void readCommon(HpBinaryReader* reader, char* buffer);
    
};

}

#endif /* defined(__Cocos2DxFirstlosSample__HpCharactorBinParser__) */

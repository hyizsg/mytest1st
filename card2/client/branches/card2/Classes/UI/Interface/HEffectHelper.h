//
//  HEffectHelper.h
//  card
//
//  Created by zhou gang on 13-7-25.
//
//

#ifndef __card__HEffectHelper__
#define __card__HEffectHelper__

#define FPS     30

class HEffectHelper : public CCObject {
    
    
public:
    static HEffectHelper* create(const char* fileName);
    static void destroyEffect(const char *filename);
    
    HEffectHelper();
    virtual ~HEffectHelper();
    
    virtual bool initWithFileName(const char* fileName);
    
    HpCharaInst* createInst(CCNode* parent = NULL);
    // loop
    HpCharaInst* playAnima(const char* name,  CCNode* parent, const CCPoint& pos = CCPointZero);
    // once
    HpCharaInst* playEffect(const char* name, CCNode* parent, const CCPoint& pos = CCPointZero, float starttime=0, bool autodestroy = true, float delaytime=0.0f);
    // num == 0 <==> loop
    HpCharaInst* playAnima(const char* name, CCNode* parent, float start_time, int fps, unsigned int num);
    // keep only one inst by tag
    HpCharaInst* playAnimaByTag(const char* name, CCNode* parent, const CCPoint& pos, int tag);
    
public:
    CC_SYNTHESIZE_RETAIN(CCString*, m_pCharId, CharID);
    
    __assign HpCharactorManager* m_pMgr;
};

#endif /* defined(__card__HEffectHelper__) */

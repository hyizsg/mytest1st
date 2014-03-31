#ifndef ANIMATIONPLAYERMGR_H
#define ANIMATIONPLAYERMGR_H

#include "cocos2d.h"

#include "HpCharaInst.h"
#include "HpCharaInstObserver.h"

//#define ANIMATION_0 "ani0"
//#define ANIMATION_1 "ani1"

#define ANIMATION_0                     "动画   0"
#define ANIMATION_1                     "动画   1"

using namespace haypi_animation;

USING_NS_CC;

class AnimationPlayerMgr : CCObject{
private:
    CCDictionary* animations_;
    CCString* m_aniFilePath;

private:
    CCString* aniInstByAniId(CCString* aniId, CCString* suffix);

public:
    AnimationPlayerMgr();
    ~AnimationPlayerMgr();
    static AnimationPlayerMgr* sharedAnimationPlayerMgr();
    static void destroyAnimationPlayerMgr();
    
    void setDisplayModeIsHD(bool isHD, float scale);
    void setAniFilePath(const char* path);
    void setPlistFilePath(const char* path);
    void setSpriteCache(CCSpriteFrameCache* tmp);
    
    HpCharaInst* creatAniInst(CCString* aniId, CCNode* parent);
    HpCharaInst* creatAniInst(CCString *aniId, CCString* suffix, CCNode *parent);

    void removeAnimation(CCString* aniId);
    void removeAnimation(CCString *aniId, CCString* suffix);
    void removeAllAnimation();

    CCObject* aniInstByName(CCString* ani_file_name);
    CCObject* aniInstByName(CCString *ani_file_name, CCString* suffix);

    void replaceContentOfAniInst(CCObject* aniInst, CCString* content, CCString* filename);


    void playAnimation(CCString* aniId, HpCharaInstObserver* delegate);
    void playAnimation(CCString *aniId, CCString* suffix, HpCharaInstObserver *delegate);
    void playAnimation(CCString *aniId, CCString* suffix, bool isRepeat, HpCharaInstObserver *delegate);
    void playAnimation(CCString *aniId, CCString* suffix, int fps, bool isRepeat, HpCharaInstObserver* delegate);


    void playAniInst(HpCharaInst* aniInst, HpCharaInstObserver* delegate);
    void playAniInst(HpCharaInst* aniInst, bool isRepeat, HpCharaInstObserver* delegate);
    void playAniInst(HpCharaInst* aniInst, int fps, bool isRepeat, HpCharaInstObserver* delegate);

    bool hasContentName(CCString* contentName, CCObject* aniInst);

};

#endif // ANIMATIONPLAYERMGR_H


#include "AnimationPlayerMgr.h"
#include "cocos2dxframework.h"

static AnimationPlayerMgr* sAniPlayerMgr = NULL;

AnimationPlayerMgr::AnimationPlayerMgr(){
    animations_ = CCDictionary::create();
    animations_->retain();
    m_aniFilePath = NULL;
}

AnimationPlayerMgr::~AnimationPlayerMgr(){
    animations_->release();
    m_aniFilePath->release();
}

AnimationPlayerMgr* AnimationPlayerMgr::sharedAnimationPlayerMgr(){
    if(sAniPlayerMgr == NULL){
        sAniPlayerMgr = new AnimationPlayerMgr;
    }

    return sAniPlayerMgr;
}

void AnimationPlayerMgr::destroyAnimationPlayerMgr(){
    sAniPlayerMgr->release();
}

void AnimationPlayerMgr::setDisplayModeIsHD(bool isHD, float scale) {
    HpCharactorManager* aniMgr = HpCharactorManager::SharedCharactorManager();
    
    aniMgr->setHD(isHD);
    aniMgr->getRender()->setLocalScale(isHD? 0.5f : 1.0f);
    aniMgr->getRender()->setGlobalScale(scale);
}

void AnimationPlayerMgr::setAniFilePath(const char* path) {
    m_aniFilePath = CCString::create(path);
    m_aniFilePath->retain();
}

void AnimationPlayerMgr::setSpriteCache(CCSpriteFrameCache* tmp) {
    HpCharactorManager::SharedCharactorManager()->setSpriteFrameCache(tmp);
}

void AnimationPlayerMgr::setPlistFilePath(const char* path) {
    HpCharactorManager* aniMgr = HpCharactorManager::SharedCharactorManager();
    aniMgr->setAniFilePath(CCString::create(path));
}

CCString* AnimationPlayerMgr::aniInstByAniId(CCString* aniId, CCString* suffix){
    if(suffix){
        return CCString::createWithFormat("%s%s", aniId->getCString(), suffix->getCString());
    } else {
        return aniId;
    }
}

HpCharaInst* AnimationPlayerMgr::creatAniInst(CCString* aniId, CCNode* parent){
    return creatAniInst(aniId, NULL, parent);
}

HpCharaInst* AnimationPlayerMgr::creatAniInst(CCString *aniId, CCString* suffix, CCNode *parent){
    CCString* anifile =  NULL;
    if (m_aniFilePath == NULL || m_aniFilePath->compare("") == 0) {
        anifile = aniId;
    } else {
        anifile = CCString::create(m_aniFilePath->getCString());
        anifile->m_sString.append(aniId->getCString());
    }
    
    
    CCString* aniInstId = this->aniInstByAniId(aniId, suffix);
    HpCharaInst* aniInst = dynamic_cast<HpCharaInst*>(animations_->objectForKey(aniInstId->getCString()));

    if(!aniInst){
        HpCharactorManager::SharedCharactorManager()->loadCharactorForId(aniId, anifile);

        CCAssert(parent, "The parent node of this animation cannot be NULL");

        aniInst = dynamic_cast<HpCharaInst*>(HpCharactorManager::SharedCharactorManager()->createInstanceOfId(aniId, dynamic_cast<CCNode*>(parent)));
        CCAssert(aniInst, "aniInst cannot be NULL");
        animations_->setObject(aniInst, aniInstId->getCString());
    }
    else
    {
        if(aniInst->getParent() != parent)
        {
            aniInst->removeFromParentAndCleanup(true);
            aniInst->addToWorld(parent);
        }
    }
    return aniInst;

}

void AnimationPlayerMgr::removeAnimation(CCString* aniId){
    this->removeAnimation(aniId, NULL);
}

void AnimationPlayerMgr::removeAnimation(CCString *aniId, CCString* suffix){

    CCString* aniInstId = this->aniInstByAniId(aniId, suffix);
    CCObject* value = animations_->objectForKey(aniInstId->getCString());
    if(value){
        if(dynamic_cast<HpCharaInst*>(value) != NULL){
            HpCharaInst* aniInst = dynamic_cast<HpCharaInst*>(value);
            aniInst->stopAllActions();
            aniInst->removeFromParentAndCleanup(true);
            animations_->removeObjectForKey(aniInstId->getCString());
        } else {

        }
    }
}

void AnimationPlayerMgr::removeAllAnimation(){
    CCDictElement* element = NULL;
    CCDICT_FOREACH(animations_, element){
        CCObject* obj = element->getObject();
        if(dynamic_cast<HpCharaInst*>(obj)){
            HpCharaInst* aniInst = dynamic_cast<HpCharaInst*>(obj);
            aniInst->stopAllActions();
            aniInst->removeFromParentAndCleanup(true);
        } else {

        }
    }

    animations_->removeAllObjects();
    HpCharactorManager::SharedCharactorManager()->removeAllCharactor();

}

CCObject* AnimationPlayerMgr::aniInstByName(CCString* ani_file_name){
    return this->aniInstByName(ani_file_name, NULL);
}

CCObject* AnimationPlayerMgr::aniInstByName(CCString* ani_file_name, CCString* suffix){
    return animations_->objectForKey(this->aniInstByAniId(ani_file_name, suffix)->getCString());
}

void AnimationPlayerMgr::replaceContentOfAniInst(CCObject* aniInst, CCString* content, CCString* filename){
//    CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage(filename->getCString());
//    if (tex == NULL) {
//        return ;
//    }
//    
//    CCRect rect = CCRectZero;
//    rect.size = tex->getContentSize();
//    
//    CCSpriteFrame* frame = CCSpriteFrame::create(filename->getCString(), rect);
     CCSpriteFrame* frame = haypi::HSourceCache::getInstance()->spriteFrameWithName(filename->getCString());
    if(dynamic_cast<HpCharaInst*>(aniInst) != NULL){
        HpCharaInst* inst = dynamic_cast<HpCharaInst*>(aniInst);
        CCString* p_ani = new CCString(ANIMATION_0);
        inst->replaceContent(content, NULL, p_ani, frame);
        p_ani->release();
    } else {
        CCAssert(false, "The Object \"aniInst\" is not kind of class HpCharaInst");
    }

}


void AnimationPlayerMgr::playAnimation(CCString* aniId, HpCharaInstObserver* delegate){
    this->playAnimation(aniId, NULL, delegate);
}

void AnimationPlayerMgr::playAnimation(CCString *aniId, CCString* suffix, HpCharaInstObserver *delegate){
    this->playAnimation(aniId, suffix, false, delegate);
}

void AnimationPlayerMgr::playAnimation(CCString *aniId, CCString* suffix, bool isRepeat, HpCharaInstObserver *delegate){
    CCString* aniInstId = this->aniInstByAniId(aniId, suffix);
    CCObject* _aniInst = animations_->objectForKey(aniInstId->getCString());
    HpCharaInst* aniInst = dynamic_cast<HpCharaInst*>(_aniInst);
    this->playAniInst(aniInst, isRepeat, delegate);
}

void AnimationPlayerMgr::playAnimation(CCString *aniId, CCString* suffix, int fps, bool isRepeat, HpCharaInstObserver* delegate) {
    CCString* aniInstId = this->aniInstByAniId(aniId, suffix);
    CCObject* _aniInst = animations_->objectForKey(aniInstId->getCString());
    HpCharaInst* aniInst = dynamic_cast<HpCharaInst*>(_aniInst);
    this->playAniInst(aniInst, fps, isRepeat, delegate);
}


void AnimationPlayerMgr::playAniInst(HpCharaInst* aniInst, HpCharaInstObserver* delegate){
    this->playAniInst(aniInst, false, delegate);
}

void AnimationPlayerMgr::playAniInst(HpCharaInst* aniInst, bool isRepeat, HpCharaInstObserver* delegate){
    this->playAniInst(aniInst, 30, isRepeat, delegate);
}

void AnimationPlayerMgr::playAniInst(HpCharaInst* aniInst, int fps, bool isRepeat, HpCharaInstObserver* delegate){
    aniInst->setDelegate(delegate);
    aniInst->runAction(CCShow::create());
    CCString* animation = CCString::create(ANIMATION_0);
    aniInst->playAniByName(animation, 0, fps, isRepeat);
}

bool AnimationPlayerMgr::hasContentName(CCString* contentName, CCObject* aniInst){
    if (dynamic_cast<HpCharaInst*>(aniInst) != NULL) {
        HpCharaInst* inst = static_cast<HpCharaInst*>(aniInst);
        return inst->hasContent(contentName);
    }
    
    return false;
}

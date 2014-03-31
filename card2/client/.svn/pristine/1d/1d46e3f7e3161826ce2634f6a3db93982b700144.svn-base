//
//  HEffectHelper.cpp
//  card
//
//  Created by zhou gang on 13-7-25.
//
//

#include "headers.h"
#include "HEffectHelper.h"

HEffectHelper::HEffectHelper()
: m_pCharId(NULL)
{
    
}

HEffectHelper::~HEffectHelper()
{
    CC_SAFE_RELEASE_NULL(m_pCharId);
}

HEffectHelper* HEffectHelper::create(const char *fileName)
{
    HEffectHelper* effect = new HEffectHelper;
    effect->initWithFileName(fileName);
//    effect->autorelease();
    CC_AUTO_RELEASE(effect);
    
    return effect;
}

void HEffectHelper::destroyEffect(const char *filename)
{
    HpCharactorManager::SharedCharactorManager()->destroyCharactorForId(CCString::create(filename));
}

bool HEffectHelper::initWithFileName(const char* fileName)
{
    setCharID(CCString::create(fileName));
    
    m_pMgr = HpCharactorManager::SharedCharactorManager();
    m_pMgr->loadCharactorForId(m_pCharId, m_pCharId);
    
    return true;
}

HpCharaInst* HEffectHelper::createInst(CCNode* parent)
{
    HpCharaInst* inst = (HpCharaInst*)m_pMgr->createInstanceOfId(m_pCharId, parent);
    return inst;
}

HpCharaInst* HEffectHelper::playAnima(const char* name, CCNode* parent, const CCPoint& pos)
{
    HpCharaInst* inst = createInst(parent);
    inst->playAniByName(CCString::create(name), 0, FPS, 0, false);
    inst->setPosition(pos);
    return inst;
}

HpCharaInst* HEffectHelper::playEffect(const char* name, CCNode* parent, const CCPoint& pos, float starttime, bool autodestroy, float delaytime)
{
    HpCharaInst* inst = createInst(parent);
    inst->playAniByName(CCString::create(name), starttime, FPS, 1, autodestroy);
    inst->setPosition(pos);
    return inst;
}

HpCharaInst* HEffectHelper::playAnima(const char* name, CCNode* parent, float start_time, int fps, unsigned int num)
{
    HpCharaInst* inst = createInst(parent);
    inst->playAniByName(CCString::create(name), start_time, fps, num, num == 0 ? false : true);
    
    return inst;
}

HpCharaInst* HEffectHelper::playAnimaByTag(const char* name, CCNode* parent, const CCPoint& pos, int tag)
{
    if (parent->getChildByTag(tag) != NULL)
        return (HpCharaInst*)(parent->getChildByTag(tag));
    
    HpCharaInst* inst = playAnima(name, parent, pos);
    inst->setTag(tag);
    
    return inst;
}


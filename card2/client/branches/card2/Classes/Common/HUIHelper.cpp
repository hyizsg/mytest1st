//
//  HUIHelper.cpp
//  card
//
//  Created by zhou gang on 13-6-4.
//
//

#include "../headers.h"
#include "HPlayerLevelUp.h"
#include "SimpleAudioEngine.h"
#include "HGameConfig.h"

HSINGLETON_OBJECT_IMP(HUIHelper);

HUIHelper::HUIHelper()
: m_lastRewardInfo(NULL)
, m_lastRewardMsg(NULL)
, m_heavenRewardInfo(NULL)
, m_player(NULL)
{
    m_effectId = CCString::create("game/effect_ui_merge.chr");
    m_effectId->retain();
    
    
    NOTIFY_ADD_OBSERVER(HUIHelper::notifyGetCardGroup, itoa(ACTION_GET_CARD_GROUP));
    
}

HUIHelper::~HUIHelper()
{
    NOTIFY_REMOVE_OBSERVER(itoa(ACTION_GET_CARD_GROUP));
}

void HUIHelper::onAddActive()
{
    HMessageBox* box = HMessageBox::show(ccLocalizedString("HCOM_BUY_POWER_TIP"), "", HMB_OKCANCEL, getInstance());
    
    getInstance()->messageMap[box] = "add active";
}


static char* pBeginW = 0;
static int pLength = 0;

void beginW(char* dst)
{
    pBeginW = dst;
}

void write(const char* src)
{
    pLength = strlen(src);
    memcpy(pBeginW, src, pLength);
    pBeginW += pLength;
}

void write(const char* src1, const char* src2)
{
    write(src1); write(src2);
}

void write(const char* src1, const char* src2, const char* src3)
{
    write(src1); write(src2); write(src3);
}

void endW()
{
    *pBeginW= 0;
    if (strcmp(pBeginW-3, "，") == 0) {
        pBeginW -= 3;
        *pBeginW= 0;
    }
}

void HUIHelper::parseRewardInfo(CCDictionary* reward)
{
    char buff[1024]={0};
    
    if (reward)
    {
        bool needln = false;
        beginW(buff);
        
        const char* coin = PARSE_STR(reward, "Coin")->getCString();
        const char* exp = PARSE_STR(reward, "EXP")->getCString();
        const char* stone = PARSE_STR(reward, "Stone")->getCString();
        const char* gold = PARSE_STR(reward, "Gold")->getCString();
        
        if (coin[0] > '0' || exp[0] > '0' || stone[0] > '0' || gold[0] > '0') {
            write(ccLocalizedString("HCOM_GET"));  needln = true;
        }
        
        if (coin[0] > '0') write(ccLocalizedString("HCOM_COIN"), coin, "，");
        if (gold[0] > '0') write(ccLocalizedString("HCOM_GOLD"), gold, "，");
        if (stone[0] > '0') write(ccLocalizedString("HCOM_STONE"), stone, "，");
        if (exp[0] > '0') write(ccLocalizedString("HCOM_EXP"), exp, "，");
        
        if (needln) {
            pBeginW -= strlen("，");
        }
        
        
        CCArray* prop = PARSE_ARR(reward, "Prop");
        if (prop != NULL && prop->count() > 0) {
            if(needln) write(ccLocalizedString("HCOM_GET2"));
            else write(ccLocalizedString("HCOM_GET"));
            
            FOREACH(CCString*, strp, prop) {
                int id = strp->intValue();
                if (id < 1000 || id > 40000) {
                    // 道具
                    write(ccLocalizedString("HCOM_OBJ"));
                    write(getPropById(id)->name, "，");
                }else if(id < 9000){
                    // 卡片
                    write(ccLocalizedString("HCOM_CARD"));
                    write(getCardById(id)->name, "，");
                }else if(id < 10000){
                    // 法宝
                    write(ccLocalizedString("HCOM_MAGIC"));
                    write(getMagicById(id, 0)->name, "，");
                }
            }
            
            needln = true;
        }
        
        endW();
    }
    
    
    HC_SET(getInstance()->m_lastRewardMsg, CCString::create(buff));
    HC_SET(getInstance()->m_lastRewardInfo, reward);
    
    CCLOG("\n%s", buff);
}

void HUIHelper::showReward(CCDictionary* reward, HMessageDelegate* delegate)
{
    parseRewardInfo(reward);
    
    if (getInstance()->m_lastRewardMsg->length() > 0) {
        HMessageBox::show(getInstance()->m_lastRewardMsg->getCString(), NULL, 1, delegate);
    }else if(delegate){
        HMessageBox::show(ccLocalizedString("HCOM_BAT_SUCCESS"), NULL, 1, delegate);
    }
}

void HUIHelper::adjustScale(cocos2d::CCSprite *sprite, float scale)
{
    sprite->setScale(sprite->getScale() * ( g_Game->isRetina() ? scale : scale*0.5));
}

void HUIHelper::showLevelUp(int lv)
{
    HPlayerLevelUp::show(lv);
}

void HUIHelper::onOK(HMessageBox* sender)
{
    if (messageMap[sender] == "add active") {
        
        HDataCenter::post(HLevelRequest::create(HLevelRequest::AddActive, NULL));
        
    }
    
    messageMap.erase(sender);
}

void HUIHelper::onCancel(HMessageBox* sender)
{
    
}

HpCharaInst *HUIHelper::playUIAnimWithTag(const char *name, cocos2d::CCNode *world, int tag)
{
    if (world->getChildByTag(tag) != NULL)
        return (HpCharaInst*)(world->getChildByTag(tag));
    
    HpCharaInst* inst = playUIAnima(name, world);
    inst->setTag(tag);
    inst->setDelegate(getInstance());
    
    return inst;
}

HpCharaInst* HUIHelper::playUIAnima(const char* name, CCNode* world)
{   
    HpCharactorManager* mgr = HpCharactorManager::SharedCharactorManager();
    mgr->loadCharactorForId(getInstance()->m_effectId, getInstance()->m_effectId);
    
    HpCharaInst* inst = (HpCharaInst*)mgr->createInstanceOfId(getInstance()->m_effectId, world);
    inst->playAniByName(CCString::create(name), 0, FPS, 0, false);
    inst->setPosition(CENTER(world));
    inst->setDelegate(getInstance());   
    
    return inst;
}


HpCharaInst* HUIHelper::playUIEffect(const char *name, cocos2d::CCNode *world, bool autodestroy)
{
    HpCharactorManager* mgr = HpCharactorManager::SharedCharactorManager();
    mgr->loadCharactorForId(getInstance()->m_effectId, getInstance()->m_effectId);
    
    HpCharaInst* inst = (HpCharaInst*)mgr->createInstanceOfId(getInstance()->m_effectId, world);
    inst->playAniByName(CCString::create(name), 0, FPS, 1, autodestroy);
    inst->setPosition(CENTER(world));
    inst->setDelegate(getInstance());    
    return inst;
}

void HUIHelper::removeUIAnimByTag(cocos2d::CCNode *world, int tag)
{
    world->removeChildByTag(tag);
}

void HUIHelper::actionOnAnimationEnd(HpAnimation* p_ani, HpCharaInst* p_sender)
{
    
}

void HUIHelper::actionOnCustomEvent(CCString* p_event, HpCharaInst* p_sender)
{
    int id = p_event->intValue();
    if (HBattleEffectHelper::s_soundId.find(id) == HBattleEffectHelper::s_soundId.end()) {
        HBattleEffectHelper::s_soundId.insert(id);
        g_Game->addMusic(CCString::createWithFormat("%d.mp3", id), id);
    }
    
    g_Game->playSoundEffect(id);
}



void HUIHelper::setLabelColor(cocos2d::CCLabelTTF *label, CC_UI_COLOR color)
{
    label->setColor(getColor(color));
}

ccColor3B HUIHelper::getColor(CC_UI_COLOR color)
{
    switch (color) {
        case CC_COLOR_YELLOW:
            return ccc3(254, 174, 2);
        case CC_COLOR_GREEN:
            return ccc3(223, 254, 0);
        case CC_COLOR_BLUE:
            return ccc3(16, 195, 239);
        case CC_COLOR_MEAT:
            return ccc3(249, 187, 106);
        case CC_COLOR_GREY:
            return ccc3(127, 133, 137);
        case CC_COLOR_DARKBROWN:
            return ccc3(42, 31, 25);
        case CC_COLOR_RED:
            return ccc3(255, 0, 0);
        case CC_COLOR_TAB:
            return ccc3(179, 140, 90);
        case CC_COLOR_BLACK:
            return ccc3(0,0,0);
        case CC_COLOR_WHITE:
            return ccc3(255, 255, 255);
        default:
            break;
    }
    return ccc3(0, 0, 0);
}


void HUIHelper::setButtonString(const char *str, cocos2d::extension::CCControlButton *btn)
{
    if (btn) {
        CCString *cstr = CCString::create(str);
        btn->setTitleForState(cstr, CCControlStateNormal);
        btn->setTitleForState(cstr, CCControlStateHighlighted);
        btn->setTitleForState(cstr, CCControlStateDisabled);
    }
}

void HUIHelper::setButtonImg(const char *img, cocos2d::extension::CCControlButton *btn)
{
    CCSpriteFrame *frame = _M(img);
    
    btn->setBackgroundSpriteFrameForState(frame, CCControlStateNormal);
    frame = _M(img);
    btn->setBackgroundSpriteFrameForState(frame, CCControlStateHighlighted);
    frame = _M(img);
    btn->setBackgroundSpriteFrameForState(frame, CCControlStateDisabled);
}

void HUIHelper::setButtonPic(const char *pic, cocos2d::extension::CCControlButton *btn)
{
    // delete by zg
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(pic);
    CCRect rect = CCRectZero;
    rect.size = texture->getContentSize();
    CCSpriteFrame *sf = CCSpriteFrame::createWithTexture(texture, rect);    
    btn->setBackgroundSpriteFrameForState(sf, CCControlStateNormal);
    sf = CCSpriteFrame::createWithTexture(texture, rect);
    btn->setBackgroundSpriteFrameForState(sf, CCControlStateHighlighted);
    sf = CCSpriteFrame::createWithTexture(texture, rect);
    btn->setBackgroundSpriteFrameForState(sf, CCControlStateDisabled);
}


void HUIHelper::setButtonTitleImg(const char *img, cocos2d::extension::CCControlButton *btn)
{
    for (int j=0; j<3; j++) {
        CCLabelTTF* label = CCLabelTTF::create();
        label->setDisplayFrame(_M(img));
        btn->setTitleLabelForState(label, CCControlState(1<<j));
        //btn->setLabelAnchorPoint(ccp(0.5, 0.58));        
    }

}

void HUIHelper::setStars(cocos2d::CCNode *stars, int starcount, int starmax)
{
    if (stars == NULL)
        return;
    
    for (int i=0; i<starmax; i++) {
        CCSprite* star = (CCSprite*)stars->getChildren()->objectAtIndex(i);
        if (i < starcount) {
            star->setVisible(true);
        }else{
            star->setVisible(false);
        }
    }
}

void HUIHelper::setCardConfigButton(CCControlButton *btn)
{
    if (btn){
        HUIHelper::setButtonString(_T(ccLocalizedString("HCOM_CARDG"), num2cn(getCurrBag()->getCurrGroupIndex()+1)), btn);
    }
}

void HUIHelper::addChild(CCNode* parent, CCNode* child)
{
    addChild(parent, child, child->getZOrder());
    
}

void HUIHelper::addChild(CCNode* parent, CCNode* child, int zOrder)
{
    child->retain();
    child->removeFromParentAndCleanup(false);
    parent->addChild(child, zOrder);
    child->release();
    
}

void HUIHelper::notifyGetCardGroup(CCObject* obj)
{
    HDataRequest* request = dynamic_cast<HDataRequest*>(obj);
    if (request) {
        if (request->isNotifyError()) {
            
        }else {
            HUIHelper::showPlayerCardGroup(request->getResult());
        }
    }
}


void HUIHelper::showPlayerCardGroup(int uid, int battleType, int OtherID)
{
    CCDictionary* param = CCDictionary::create();
    param->setObject(HString::createWithInteger(uid), "UID");
    param->setObject(HString::createWithInteger(battleType), "BattleType");
    param->setObject(HString::createWithInteger(OtherID), "OtherID");
    
    HWindow::post(ACTION_GET_CARD_GROUP, param);
}

void HUIHelper::showPlayerCardGroup(CCDictionary* info)
{
    if (getInstance()->m_player == NULL) {
        getInstance()->m_player = HPlayer::createWithBag();
        getInstance()->m_player->retain();
    }
    
    HPlayer* player = getInstance()->m_player;
    CCDictionary* hero = PARSE_DIC(info, "Hero");
    tParseReplayPlayer(player, hero);
    
    player->getBag()->setCurrGroupIndex(0);
    
    {CCArray *cardinfo = (CCArray*)(info->objectForKey("Card"));
        if (cardinfo) {
            vector<HUserCard*> cardlist;
            FOREACH(CCDictionary*, dic, cardinfo){
                HUserCard* card = new HUserCardObject;
                card->setUserId(PARSE_INT(dic, "CID"));
                card->setKeyCard(getCardById(PARSE_INT(dic, "CardID")));
                card->setLevel(PARSE_INT(dic, "Level"));
                card->setExp(PARSE_INT(dic, "EXP"));
                
                vector<int> ft;
                CCArray* feature = PARSE_ARR(dic, "Feature");
                FOREACH(CCString*, strft, feature) {
                    ft.push_back(strft->intValue());
                }
                card->setFeature(ft);
                
                cardlist.push_back(card);
            }
            player->getBag()->updateCardList(cardlist);
            player->getBag()->updateCurrCardGroup(cardlist);
        }}
    
    
    {CCArray* magicsinfo = (CCArray*)info->objectForKey("Magic");
        if (magicsinfo != NULL) {
            vector<HUserMagic*> magiclist;
            FOREACH(CCDictionary*, dic, magicsinfo){
                HUserMagic* magic = new HUserMagicObject;
                magic->setUserId(PARSE_INT(dic, "MID"));
                magic->setLevel(PARSE_INT(dic, "Level"));
                magic->setKeyMagic(getMagicById(PARSE_INT(dic, "MagicID"), magic->getLevel()));
                magic->setExp(PARSE_INT(dic, "EXP"));
                magiclist.push_back(magic);
            }
            player->getBag()->updateMagicList(magiclist);
            player->getBag()->updateCurrMagicGroup(magiclist);
        }}
    
  
    HConfigMainWindow* config = HConfigMainWindow::create();
    config->setReadOnly(true);
    config->setNeedLockInfo(false);
    config->initWithPlayer(player);
    
    config->presentRootLayer();
}

CCNode* HUIHelper::getFirstChildWithDeep(CCNode* pNode, int deep)
{
    CCAssert(deep > 0, "deep must be bigger than 0");
    
    if (pNode && pNode->getChildrenCount() > 0) {
        pNode = (CCNode*)pNode->getChildren()->objectAtIndex(0);
        if (deep == 1) {
            return pNode;
        }else{
            return getFirstChildWithDeep(pNode, deep-1);
        }
    }else{
        return NULL;
    }

}


void HUIHelper::enableMusicBackGround(bool enable)
{
    if (enable){        
        g_Game->setBGMusicVolume(0.5);
    } else {
        g_Game->setBGMusicVolume(0);
    }
}

void HUIHelper::enableMusicEffect(bool enable)
{
    if (enable){
        g_Game->setSoundEffectVolume(0.5);
    } else {
        g_Game->setSoundEffectVolume(0);
    }
}

void HUIHelper::addToTopMost(CCNode* node)
{
    HRootScene::current()->getTopShowLayer()->addChild(node);
//    g_Game->getUILayer()->getParent()->addChild(node, g_Game->getUILayer()->getZOrder()+1);
}

bool HUIHelper::checkSeniorCard(const vector<int>& cards, CCCallFunc* callback, const char* msg)
{
    bool hlv = false, hstar = false;
    
    for (int i=0; i<cards.size(); i++) {
        HUserCard* card = getCurrBag()->cardByUId(cards[i]);
        if (card->getLevel() > 0 || card->getExp() > 0) { hlv = true; }
        if (card->getKeyCard()->star_num >= 4) { hstar = true; }
        if (hlv && hstar) { break; }
    }
    
    if (hstar || hlv) {
        HMessageBox::show(msg ? msg : ccLocalizedString("HCOM_TIP_SENIOR_CARD"), NULL, HMB_OKCANCEL, callback);
    }else{
        callback->execute();
    }
    
    return true;
}

bool HUIHelper::checkSeniorMagic(const vector<int> &magics, cocos2d::CCCallFunc *callback, const char* msg)
{
    bool hlv = false, hstar = false;
    
    for (int i=0; i<magics.size(); i++) {
        HUserMagic* card = getCurrBag()->magicByUId(magics[i]);
        if (card->getLevel() > 0 || card->getExp() > 0) { hlv = true; }
        if (card->getKeyMagic()->star_num >= 4) { hstar = true; }
        if (hlv && hstar) { break; }
    }
    
    if (hstar || hlv) {
        HMessageBox::show(msg ? msg : ccLocalizedString("HCOM_TIP_SENIOR_MAGIC"), NULL, HMB_OKCANCEL, callback);
    }else{
        callback->execute();
    }
    
    return true;
}

void HUIHelper::clipLayer(haypi::HRootLayer *layer)
{    
    layer->getCCBNode()->retain();
    layer->getCCBNode()->removeFromParentAndCleanup(false);
    CCNode *node = layer->getCCBNode();
    CCScrollView* scrol = CCScrollView::create(layer->getCCBNode()->getContentSize());
    
    scrol->setScaleX(node->getScaleX());
    scrol->setScaleY(node->getScaleY());
    
    scrol->setContainer(layer->getCCBNode());
    
    layer->addChild(scrol);
    scrol->setContentSize(layer->getCCBNode()->getContentSize());   
    scrol->setPosition(HGameManager::getInstance()->getRootStartPos());
    layer->getCCBNode()->setAnchorPoint(CCPointZero);
    layer->getCCBNode()->setPosition(CCPointZero);
    layer->getCCBNode()->release();
    
    scrol->setTouchEnabled(false);
}


const char* HUIHelper::getDataString(time_t nTime)
{
    char str[80];
    strftime(str, sizeof(str), "%Y-%m-%d-%H:%M:%S", localtime(&nTime));
    return CCString::create(str)->getCString();
}

void HUIHelper::dumpAllTexture()
{
    return;
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
    HUserBag::getInstance()->dumpCachedTextureInfo();
}

const ccColor3B HUIHelper::colorLevel(int lv)
{
    switch (lv)
    {
        case 1:
            return ccWHITE;
        case 2:
            return HC_COLOR_GREEN;
        case 3:
            return HC_COLOR_BLUE;
        case 4:
            return HC_COLOR_PURPLE;
        case 5:
            return HC_COLOR_YELLOW;
            
        default:
            return ccWHITE;
    }
}

bool HUIHelper::checkBuyActiveGuide(HRootLayer* parent, CCNode* addbtn)
{
    bool bRet = false;
    do {
        if (getCurrBag()->getActive() <=2 && !getCurrBag()->isActiveBought()) {
            HNewbieGuide* guide = HNewbieGuide::create(214);
            if (guide) {
                bRet = true;
                guide->showIn(parent);
                guide->runAction(HGuideChat::create(1, 3));
                guide->runAction(HGuideReward::create(3));
                guide->runAction(HGuideChat::create(4, 4));
                guide->runAction(HGuideClick::create(5, addbtn));
                guide->hiddenAfterActionWithoutAnima();
            }
            
            CC_BREAK_IF(guide);
        }
//        
//        if (/*getCurrBag()->getActive() >= 50 && */HNewbieGuide::isPass(214, 5)) {
//            HNewbieGuide* guide = HNewbieGuide::create(214, 7);
//            if (guide) {
//                bRet = true;
//                guide->showIn(parent);
//                guide->runAction(HGuideChat::create(7, 7));
//            }
//            
//            CC_BREAK_IF(guide);
//        }
    } while (false);
    
    return bRet;
}

const char* HUIHelper::rank2str(int rank, int limitRank)
{
    static const char* rankstr[] = {ccLocalizedString("HCOM_NO1"), ccLocalizedString("HCOM_NO2"), ccLocalizedString("HCOM_NO3")};
    
    if (rank < 0) {
        return "--";
    }else if (rank < 3) {
        return rankstr[rank];
    }else if(rank >= limitRank) {
        return _T("%d+", limitRank);
    }
    
    return _T("%d", rank+1);
}

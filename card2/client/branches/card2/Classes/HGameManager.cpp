//
//  HGameManager.cpp
//  card2
//
//  Created by zhou gang on 14-2-10.
//
//

#include "headers.h"
#include "UpdateManager.h"
#include "HGameManager.h"
#include "HLoginMainWindow.h"
#include "HMainCityWindow.h"

HGameManager* g_Game = NULL;
HSourceCache* g_SourceCache = NULL;
HSINGLETON_OBJECT_IMP(HGameManager);

void afterCreateWindow()
{
//    CrossDelegate::SNSHasLogin();
}

int requestScreenOrientation()
{
    return HORIENTATION_LANDSCAPE;
}

HGameDelegate *requestGameDelegate()
{
    
    HGameDelegate::ratioOfEquality();
    addSupportedScreenData(480, 320, "iphone", 1);
    
    return (g_Game = HGameManager::getInstance());
}

HGameManager::HGameManager()
{
    setPlatFormAndMarket(CURR_GCTYPE, CURR_PLATFORM);
    setNetParameters(HPASSPORTURL, HLOCALPASSPORTURL, HGAME_ID, HSOCKETIP, HSOCKETPORT, HVISIT_WEBSITE, "1");
    enableSocket(true);
    setProtocolTimeoutInterval(15.0f);
    HNetManager::getInstance()->setMaxConnectTime(30);
}

HGameManager::~HGameManager()
{
    
}

void HGameManager::preloadLoaders()
{
    
}

void HGameManager::initGame()
{
    g_Game = this;
    g_SourceCache = m_pSourceCache;
    
#ifdef ANDROID
    std::string searchPath = CCFileUtils::sharedFileUtils()->getWritablePath() + "resource/";
    CCFileUtils::sharedFileUtils()->addSearchPath(searchPath.c_str());
#else
    CCFileUtils::sharedFileUtils()->addSearchPath("public_res/");
#endif
    
    
    HPlistManager::getInstance()->addPlist("ui/ccbDefaultImages.plist");
    
    initCCBLoader();
    loadConfig();
    initResources();
    
//    CCDirector::sharedDirector()->setDisplayStats(false);
    CCDirector::sharedDirector()->setAnimationInterval(1.0/30);
    
    HThreadTextureCache::getInstance()->start();
    
    HMainCityWindow* city = HMainCityWindow::create();
    HRootScene::current()->pressentGame(city);
    
    HLoginMainWindow* login = HLoginMainWindow::create();
    login->presentRootLayer(false);
    
    CCDirector::sharedDirector()->drawScene();
    
}

void HGameManager::enterBackground()
{
    
}

void HGameManager::enterForeground()
{
    
}

void HGameManager::onNeedHeartBeat()
{
    
}

void HGameManager::onNeedUpdateData()
{
    
}

void HGameManager::onNeedReLogin()
{
    
}

void HGameManager::onNetworkFailed()
{
    
}

void HGameManager::onForceCloseByServer()
{
    
}

void HGameManager::onNeedAccount()
{
    
}

void HGameManager::startGame()
{
    this->GetUserInfo();
}

void HGameManager::initDirector()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    
    PHSCREENDATA pData = currentScreenData();
    CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    CCSize screenSize = frameSize;
    
    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);
    bool isRetina = AppDelegate::getInstance()->getRetinaScreen();
    if (!isRetina) {
        if (screenSize.width > pData->width * 1.5f) {
            isRetina = true;
            AppDelegate::getInstance()->setRetinaScreen(isRetina);
        } else {
            HLOGI("Retina Display Not supported");
        }
    }
    
    if (isRetina) {
        pDirector->setContentScaleFactor(2.0f);
        screenSize = CCSizeMake(screenSize.width / 2, screenSize.height / 2);
        HLOGI("Retina Display  supported");
    }
    else{
        pDirector->setContentScaleFactor(2.0f);
    }
    
    float sx = screenSize.width / pData->width;
    float sy = screenSize.height / pData->height;
    float startx = 0;
    float starty = 0;
    
    if (HRootLayer::m_sbRatioOfEquality) {
        sx = sy = MIN(sx, sy);
        startx = (screenSize.width - pData->width * sx)/(2*sx);
        starty = (screenSize.height - pData->height * sy)/(2*sy);
    }
    
    if (false)// CrossDelegate::isIphone5())
    {
        HRootScene::isAddSlib = true;
    } else {
        if (startx >= 15) {
            HRootScene::isAddSlib = true;
        }
    }
    
    CCSize designSize = HRootScene::isAddSlib ? CCSizeMake(startx*2+480, 320) : CCSizeMake(480, 320);
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);
    
    m_szScreen = pDirector->getWinSize();
    
    m_pSourceCache = HSourceCache::getInstance();
    m_pTimerManager = HTimerManager::getInstance();
    
    float retinaFactor = 2;//CrossDelegate::getEGLViewContentScaleFactor();
    float scaleFactor = CCEGLView::sharedOpenGLView()->getScaleX();
    
    if (HRootScene::isAddSlib) {
        pData->startX = startx;
        pData->startY = starty;
    }
    
    pData->osStartX = startx * scaleFactor / retinaFactor;
    pData->osStartY = starty * scaleFactor / retinaFactor;
    pData->gameResourceScale = (screenSize.width > pData->width * 1.5)  ? 2 : 1;
    
//    CCLOG("<screen>");
//    CCLOG("\tos.frame_size: [%.1f, %.1f]", frameSize.width, frameSize.height);
//    CCLOG("\tos.retina: %s", CrossDelegate::getEGLViewContentScaleFactor() == 2.0f ? "true" : "false");
//    CCLOG("\tos.scale_factor: %.1f", CrossDelegate::getEGLViewContentScaleFactor());
//    CCLOG("\tgl.retina: %s", isRetina ? "true" : "false");
//    CCLOG("\tgl.scale_factor: %.1f", pDirector->getContentScaleFactor());
//    CCLOG("\tgl.window_size: [%.1f, %.1f]", m_szScreen.width, m_szScreen.height);
//    CCLOG("\tgl.design_size: [%.1f, %.1f]", designSize.width, designSize.height);
//    CCLOG("\tgl.scaleXY: [%.3f, %.3f]", CCEGLView::sharedOpenGLView()->getScaleX(), CCEGLView::sharedOpenGLView()->getScaleY());
//    CCLOG("\tgl.startXY: [%.1f, %.1f]", pData->startX, pData->startY);
//    CCLOG("\tos.startXY: [%.1f, %.1f]", getOSViewStartPosition().x, getOSViewStartPosition().y);
//    CCLOG("</screen>");

}

void HGameManager::initCCBLoader()
{
    CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->unregisterCCNodeLoader("CCLabelTTF");
    CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->unregisterCCNodeLoader("HRichLabelTTF");
//    CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->unregisterCCNodeLoader("CCControlButton");
    CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->unregisterCCNodeLoader("CCEditBox");
    CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->unregisterCCNodeLoader("CCSprite");
    CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->unregisterCCNodeLoader("CCTableView");
    
    REGISTER_CCNODE_LOADER(CCSprite, HRichSpriteLoader::loader());
    REGISTER_CCNODE_LOADER(HRichSprite, HRichSpriteLoader::loader());
    
    REGISTER_CCNODE_LOADER(HTransformNode, HTransformNodeLoader::loader());
    REGISTER_CCNODE_LOADER(CCProgressTimer, CCProgressTimerLoader::loader());
    REGISTER_CCNODE_LOADER(CCLabelTTF, HRichLabelTTF2Loader::loader());
    REGISTER_CCNODE_LOADER(HRichLabelTTF, HRichLabelTTF2Loader::loader());
    REGISTER_CCNODE_LOADER(HRichLabelTTF2, HRichLabelTTF2Loader::loader());
//    REGISTER_CCNODE_LOADER(HEditField, HEditFieldLoader::loader());
    
//    REGISTER_CCNODE_LOADER(CCControlButton, HRichButtonLoader::loader());
    REGISTER_CCNODE_LOADER(HRichButton, HRichButtonLoader::loader());
#ifndef ANDROID
    REGISTER_CCNODE_LOADER(CCEditBox, HCardEditBoxLoader::loader());
#else
    REGISTER_CCNODE_LOADER(CCEditBox, HEditBoxLoader::loader());
#endif
    REGISTER_CCNODE_LOADER(CCTableView, CCTableViewLoader2::loader());
    REGISTER_CCNODE_LOADER(HTableView, HTableViewLoader::loader());
    REGISTER_CCNODE_LOADER(HTableViewCell, HTableViewCellLoader::loader());
    
    REGISTER_CCNODE_LOADER(HNewbieChatDialog, HNewbieChatDialogLoader::loader());
}

void HGameManager::loadConfig()
{
    
}

void HGameManager::initResources()
{
    
}

void HGameManager::onMessageBox(const char *message, const char *titile)
{
    
}

void HGameManager::receiveDataTimeout(int command)
{
    
}

void HGameManager::onDataReceived(int command, CCDictionary *result)
{
    switch (command) {
        case 301:
        {
            if (this->ParseUserInfo(result))
            {
                HRootScene::current()->getRunningLayer()->dismissLater(true, 0.1f);
            }
            
            break;
        }
    }
}

void HGameManager::GetUserInfo()
{
    CCDictionary *param = CCDictionary::create();
    
    param->setObject(HString::create(haypi::UpdateManager::sharedInstance()->getInuseVersion()), "ClientVersion");
    this->postRequest(301, param, this, true, 0, HNET_MODE_SOCKET);
}

bool HGameManager::ParseUserInfo(CCDictionary *result)
{
    if (result == NULL) {
        return false;
    }
    
    return true;
    
    CCDictionary *userinfo = (CCDictionary*)(result->objectForKey("UserInfo"));
    
    if (!userinfo)
    {
        return true;
    }
    
    HPlayer* player = getCurrPlayer();
    HUserBag* bag = getCurrBag();
    HUserMap* map = getCurrMap();
    
    
    {
        if (result->objectForKey("DC") != NULL)
        {
            player->setHasDailyGet(PARSE_INT(result, "DC"));
        }
    }
    
    {
        if (result->objectForKey("SName") != NULL)
        {
            player->setServerName(PARSE_STR(result, "SName"));
        }
    }
    
    {
        player->setServerID(PARSE_INT(result, "SID"));
    }
    
    {CCDictionary* heroinfo = (CCDictionary*)userinfo->objectForKey("HeroInfo");
        if (heroinfo != NULL) {
            player->setName(PARSE_STR(heroinfo, "Name")->getCString());
            player->setIconID(PARSE_INT(heroinfo, "Avatar"));
            player->setOriIconId(PARSE_INT(heroinfo, "Guide"));
            
            
            int oldlv = player->getLevel();
            int newlv = PARSE_INT(heroinfo, "Level");
            if (oldlv > 0 && newlv>oldlv) {
//                HUIHelper::showLevelUp(newlv);
            }
            
            player->setLevel(PARSE_INT(heroinfo, "Level"));
            player->setExp(PARSE_INT(heroinfo, "EXP"));
            player->setHP(getHeroByLevel(player->getLevel())->hp);
            player->setLDLayer(PARSE_INT(heroinfo, "LdLayer"));
            player->setLdRank(PARSE_INT(heroinfo, "LdRank"));
            player->setMaxCard(PARSE_INT(heroinfo, "MaxCard"));
            player->setMaxMagic(PARSE_INT(heroinfo, "MaxMagic"));
        }}
    
    {CCDictionary* memeberinfo = PARSE_DIC(userinfo, "MemberInfo");
        if (memeberinfo != NULL) {
            player->setUserID(PARSE_INT(memeberinfo, "UID"));
            HRegistInfo* regist = HRegistInfo::create();
            // ..
            regist->setUserName(PARSE_STR(memeberinfo, "Username"));
            regist->setPassword(PARSE_STR(memeberinfo, "Password"));
            regist->setEmail(PARSE_STR(memeberinfo, "Email"));
            regist->setDeviceID(PARSE_STR(memeberinfo, "DeviceID"));
            regist->setRegionID(PARSE_STR(memeberinfo, "RegionID"));
            regist->setInvitedBy(PARSE_STR(memeberinfo, "InvitedBy"));
            player->setRegistInfo(regist);
            
            player->setStatus(PARSE_INT(memeberinfo, "Status"));
            player->setVIP(PARSE_INT(memeberinfo, "VIP"));
            player->setHasRename(PARSE_INT(memeberinfo, "Rename"));
        }}
    
    
    {CCDictionary* mailinfo = PARSE_DIC(userinfo, "MailInfo");
        if (mailinfo != NULL) {
            player->setMaxMailID(PARSE_INT(mailinfo, "MaxMID"));
            
//            CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFY_MAIL_CHANGE);
        }}
    
    {CCDictionary* rcinfo = PARSE_DIC(userinfo, "RCInfo");
        if (rcinfo != NULL) {
            player->setRewardNum(PARSE_INT(rcinfo, "RCNum"));
        }}
    
    
    
    {CCArray* maplist = (CCArray*)userinfo->objectForKey("MapList");
        if (maplist != NULL) {
            map->updateMapLevel(maplist);
        }}
    
    
    {CCArray* heavenlist = (CCArray*)userinfo->objectForKey("Heaven");
        if (heavenlist != NULL) {
            map->updateHeaven(heavenlist);
        }}
    
    
    if (userinfo->objectForKey("CardsInfo") != NULL) {
        CCString *cardstr = PARSE_STR(userinfo, "CardsInfo");
        if (cardstr != NULL) {
            bag->updateCardList(cardstr);
        }
    }
    
    if (userinfo->objectForKey("MagicsInfo") != NULL) {
        CCString *magicstr = PARSE_STR(userinfo, "MagicsInfo");
        if (magicstr != NULL) {
            vector<HUserMagic*> magiclist;
            vector<int> intvec;
            HUserBag::parseIntStr(magicstr, intvec);
            int co = intvec.size();
            for(int i=0;i<co;i+=4)
            {
                HUserMagic* magic = new HUserMagicObject;
                magic->setUserId(intvec[i]);
                magic->setLevel(intvec[i+2]);
                magic->setExp(intvec[i+3]);
                magic->setKeyMagic(getMagicById(intvec[i+1], magic->getLevel()));
                magiclist.push_back(magic);
            }
            bag->updateMagicList(magiclist);
        }
    }
    
    {CCDictionary* groupinfo = (CCDictionary*)userinfo->objectForKey("GroupInfo");
        if (groupinfo != NULL) {
            bag->setCurrGroupIndex(max(0, PARSE_INT(groupinfo, "CurGroupID")));
            int num = PARSE_INT(groupinfo, "GroupNum");
            char key[] = "0";
            CCDictionary* groups = (CCDictionary*)groupinfo->objectForKey("Groups");
            for (int i=0; i<num; i++, key[0]++) {
                CCDictionary* dic = (CCDictionary*)groups->objectForKey(key);
                if (dic != NULL) {
                    bag->updateCardGroup(PARSE_ARR(dic, "Cards"), i);
                    bag->updateMagicGroup(PARSE_ARR(dic, "Magics"), i);
                }else{
                    bag->updateCardGroup(NULL, i);
                    bag->updateMagicGroup(NULL, i);
                }
            }
        }}
    
    {CCDictionary* baginfo = (CCDictionary*)userinfo->objectForKey("WareHouseInfo");
        if(baginfo != NULL) {
            bag->setCoin(PARSE_INT(baginfo, "Coin"));
            bag->setGold(PARSE_INT(baginfo, "Gold"));
            bag->setStone(PARSE_INT(baginfo, "Stone"));
            bag->setActive(PARSE_INT(baginfo, "Active"));
            bag->setMaxActive(PARSE_INT(baginfo, "MaxActive"));
            bag->setActiveWaitTime(PARSE_INT(baginfo, "ActiveWaitTime"));
            bag->setActBuyNum(PARSE_INT(baginfo, "ActBuyNum"));
            bag->setMaxActBuyNum(PARSE_INT(baginfo, "MaxActBuyNum"));
            bag->setBuyGold(PARSE_INT(baginfo, "BuyGold"));
            bag->updateFragMap(PARSE_ARR(baginfo, "Bead"));
            bag->setActPrice(PARSE_INT(baginfo, "ActPrice"));
            bag->setActNum(PARSE_INT(baginfo, "ActGain"));
            bag->setNextGainTime(PARSE_INT(baginfo, "NextGainTime"));
            bag->setActiveBought(PARSE_INT(baginfo, "PowerBuy"));
        }}
    
    {
        CCDictionary *dic = PARSE_DIC(userinfo, "IAPPayInfo");
        if (dic != NULL) {
            bag->updateIapInfo(dic);
//            CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFY_IAPBUYLIST_CHANGE);
        }
    }
    
    {CCArray* symbolarr = PARSE_ARR(userinfo, "TechInfo");
        if (symbolarr != NULL) {
            bag->updateSymbolMap(symbolarr);
        }}
    
    {
        if (userinfo->objectForKey("CC") != NULL)
        {
            HPlayer::currPlayer()->setCardChange(PARSE_INT(userinfo, "CC"));
        }
        if (userinfo->objectForKey("MC") != NULL)
        {
            HPlayer::currPlayer()->setMagicChange(PARSE_INT(userinfo, "MC"));
        }
    }
    
    {
        CCArray* newbie = PARSE_ARR(userinfo, "NewBie");
        if (newbie) {
            HNewbieGuide::updateLog(newbie);
        }
    }
    
    {
        CCDictionary* sina = PARSE_DIC(userinfo, "ProfileInfo");
        if (sina) {
            bag->setWbRid(PARSE_INT(sina, "WBRID"));
            bag->setWbNum(PARSE_INT(sina, "WBRNum"));
        }
        
    }
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(ACTION_UPDATE_USERINFO_STR, userinfo);
    
    
    return true;
}

void HGameManager::preProcessNetResult(int command, CCDictionary *result)
{
    
}

void HGameManager::onUpdateFinished()
{
    
}




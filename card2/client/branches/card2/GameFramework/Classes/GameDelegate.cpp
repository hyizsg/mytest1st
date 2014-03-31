
#include "cocos2dxframework.h"
#include "Base.h"
#include "MusicManager.h"
#include "GameScene.h"
#include "AppDelegate.h"
#include "NetManager.h"

HNAMESPACE_BEGIN

void HGameDelegate::initDirector()
{
//    CCDirector *pDirector = CCDirector::sharedDirector();
//    
//    PHSCREENDATA pData = currentScreenData();
//    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
//    
//    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
//    // pDirector->enableRetinaDisplay(true);
//    bool isRetina = AppDelegate::getInstance()->getRetinaScreen();
//    if (!isRetina) {
//        if (screenSize.width > pData->width * 1.5f) {
//            isRetina = true;
//            AppDelegate::getInstance()->setRetinaScreen(isRetina);
//        } else {
//            HLOGI("Retina Display Not supported");
//        }
//    }
//    
//    if (isRetina) {
//        pDirector->setContentScaleFactor(2.0f);
//        screenSize = CCSizeMake(screenSize.width / 2, screenSize.height / 2);
//        HLOGI("Retina Display  supported");
//    }
//    //    pData = currentScreenData(true);
//    pData->scaleX = screenSize.width / pData->width;
//    pData->scaleY = screenSize.height / pData->height;
//    pData->gameResourceScale = (screenSize.width > pData->width * 1.5)  ? 2 : 1; //screenSize.width / pData->width;// (screenSize.width > pData->width * 1.5)  ? 2 : 1;
//    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(screenSize.width, screenSize.height, kResolutionNoBorder);
//    
//    m_szScreen = pDirector->getWinSize();
//    
//    updateScissors();
//    
//    
//    m_pSourceCache = HSourceCache::getInstance();
//    m_pTimerManager = HTimerManager::getInstance();
}

HGameDelegate::HGameDelegate(): m_bIsFake(false), m_pSafeMemorySize(1), m_iTotalMemory(-1),m_hasLogin(false) {
    srandom((unsigned int)time(NULL));
    srand((unsigned int)time(NULL) + 999);    
}

HGameDelegate::~HGameDelegate() {
}

bool HGameDelegate::memoryIsSafe() {
//    return true;
    if (m_iTotalMemory < 1) {
        CCDictionary *dict = HNetManager::getInstance()->getSystemInfo();
        m_iTotalMemory = dict->valueForKey("totalMemory")->intValue();
        HLOGI("memory: safe(%d M), total(%d M)", m_pSafeMemorySize, m_iTotalMemory);
    }
    return m_iTotalMemory >= m_pSafeMemorySize;
}

CCObject *HGameDelegate::asyncLoginError(int commmand, CCObject *param) {
    CCString *errorStr = dynamic_cast<CCString *>(param);
    CCDictionary *dict = dictionaryFromJSON(errorStr ? errorStr->getCString() : "", 0);
    onLoginError(commmand, dict);
    return NULL;
}

CCObject *HGameDelegate::asyncReceiveLastUserState(int state, cocos2d::CCObject *param)
{
    onReceiveLastUserState(state);
    return NULL;
}

void HGameDelegate::onLoginError(int errorCode, CCDictionary *param)  {
    if (errorCode == HNETFAILED) {
        onMessageBox("net failed", "");
    } else {
        onMessageBox("Login error with action com", HString::createWithInteger(errorCode)->getCString());
    }
}

void HGameDelegate::clear() {
    m_pUILayer->dismissAllRootLayers();
    m_pGameDecorationLayer->dismissAllRootLayers();
    m_pGameShowLayer->removeAllChildrenWithCleanup(true);
    m_pSourceCache->clear();
}

void HGameDelegate::updateScissors() {
//    if (HRootLayer::m_sbRatioOfEquality) {
//        PHSCREENDATA pData = currentScreenData();
//        if ((pData->scaleX < pData->scaleY)) {
//            float posY = 0;//(m_szScreen.height - pData->height * pData->scaleX) / 2;
//            m_szScreen.height *= pData->scaleX / pData->scaleY;
//            //delete by zg
////            CCDirector::sharedDirector()->setDefaultScissor(CCRectMake(0, posY, m_szScreen.width, m_szScreen.height));
//            pData->scaleY = pData->scaleX;
//        } else {
//            float posX = 0;//(m_szScreen.width - pData->width * pData->scaleY) / 2;
//            m_szScreen.width *= pData->scaleY / pData->scaleX;
//            //delete by zg
////            CCDirector::sharedDirector()->setDefaultScissor(CCRectMake(posX, 0, m_szScreen.width, m_szScreen.height));
//            pData->scaleX = pData->scaleY;
//        }
//    }
}

void HGameDelegate::setHeartBeatInterval(int seconds) {
    HNetManager::getInstance()->setHeartBeatInterval(seconds);
}

void HGameDelegate::setReloginInterval(int seconds) {
    AppDelegate::getInstance()->setReloginInterval(seconds);
}

void HGameDelegate::setProtocolTimeoutInterval(int seconds) {
    HNetManager::getInstance()->setProtocolTimeoutInterval(seconds);
}

void HGameDelegate::initGame() {
    //this->initDirector();    
    
    HGameScene *pGameScene = AppDelegate::getInstance()->getGameScene();
    m_pGameShowLayer = pGameScene->getGameShowLayer();
    m_pGameDecorationLayer = pGameScene->getGameDecorationLayer();
    m_pUILayer = pGameScene->getUILayer();
}

void HGameDelegate::onCommand(int command, const char *param) {
    if ((command >= HCOMMAND_VIEW_MIN) && (command <= HCOMMAND_VIEW_MAX)) {
        CCDictionary *dict = dictionaryFromJSON(param, 0);
        if (!dict) return;
        CCArray *array = (CCArray *)dict->objectForKey(HVIEWKEY_ALL);
        if (!array) return;
        switch (command) {
            case HVIEWCMD_CHECK: {
                for (int i = 0; i < array->count(); ++i) {
                    CCDictionary *value = (CCDictionary *)array->objectAtIndex(i);
                    int type = value->valueForKey(HVIEWKEY_TYPE)->intValue();
                    if (type == HVIEWTYPE_EDITBOX) {
                        int viewID = value->valueForKey(HVIEWKEY_ID)->intValue();
                        const CCString *text = value->valueForKey(HVIEWKEY_TEXT);
                        HViewPageManager::getInstance()->checkView(viewID, text->getCString());
                    }
                }
            }
                break;
            case HVIEWCMD_SETTEXT: {
                for (int i = 0; i < array->count(); ++i) {
                    CCDictionary *value = (CCDictionary *)array->objectAtIndex(i);
                    int type = value->valueForKey(HVIEWKEY_TYPE)->intValue();
                    if (type == HVIEWTYPE_EDITBOX) {
                        int viewID = value->valueForKey(HVIEWKEY_ID)->intValue();
                        const CCString *text = value->valueForKey(HVIEWKEY_TEXT);
                        HViewPageManager::getInstance()->setText(viewID, text->getCString());
                    }
                }
            }
            default:
                break;
        }
    }
}

CCPoint HGameDelegate::posToScreen(CCNode *node) {
    if (!node) return CCPointZero;
    CCPoint pos = node->getPosition();
    HGameScene *pGameScene = AppDelegate::getInstance()->getGameScene();
    if (node == pGameScene) return pos;
    do {
        CCNode *parent = node->getParent();
        if (!parent) break;
        const CCPoint &p = parent->getPosition();
        const CCSize &s = parent->getContentSize();
        const CCPoint &a = parent->getAnchorPoint();
        pos = CCPointMake(pos.x * parent->getScaleX() + p.x + s.width * a.x, pos.y * parent->getScaleY() + p.y + s.height * a.y);
        if (parent == pGameScene) break;
        node = parent;
    } while (1);
    return pos;
}

float HGameDelegate::scaleToScreen(CCNode *node) {
    float scale = 1.0f;
    if (!node) return scale;
    HGameScene *pGameScene = AppDelegate::getInstance()->getGameScene();
    if (node == pGameScene) return scale;
    do {
        CCNode *parent = node->getParent();
        if (!parent) break;
        scale *= parent->getScale();
        if (parent == pGameScene) break;
        node = parent;
    } while (1);
    return scale;
}

CCRect HGameDelegate::rectToDeviceInPixels(CCNode *node) {
    if (!node) return CCRectZero;
    
	CCSize contentSize = node->getContentSize();
	CCRect rect = CCRectMake(0, 0, contentSize.width, contentSize.height);
    rect = CCRectApplyAffineTransform(rect, node->nodeToWorldTransform());
    
    CCEGLViewProtocol* eglView = CCEGLView::sharedOpenGLView();
    float viewH = eglView->getFrameSize().height;//eglView->getViewPortRect().size.height;
    
    CCPoint visiblePos = ccp(rect.origin.x * eglView->getScaleX(), rect.origin.y * eglView->getScaleY());
    CCPoint screenGLPos = ccpAdd(visiblePos, eglView->getViewPortRect().origin);
    
    rect.origin = CCPointMake(screenGLPos.x, screenGLPos.y);
    rect.size = CCSizeMake(rect.size.width * eglView->getScaleX(), rect.size.height * eglView->getScaleY());
    rect.origin.y = viewH - rect.origin.y - rect.size.height;
    return rect;
    
//    CCPoint anchorPoint = node->getAnchorPoint();
//    CCPoint designCoord = node->getPosition();
//    CCSize designSize = node->getContentSize();
//    designCoord = CCPointMake(designCoord.x - designSize.width * anchorPoint.x, designCoord.y - designSize.height * anchorPoint.y);
//    designCoord = node->getParent()->convertToWorldSpace(designCoord);
//    
//    CCRect rect;
//    rect.origin = designCoord;
//    rect.size = designSize;
//    
//    HGameScene *pGameScene = AppDelegate::getInstance()->getGameScene();
//    if (node == pGameScene) return rect;
//    float scaleX = 1.0f;
//    float scaleY = 1.0f;
//    do {
//        CCNode *parent = node->getParent();
//        if (!parent) break;
//        scaleX *= parent->getScaleX();
//        scaleY *= parent->getScaleY();
//        if (parent == pGameScene) break;
//        node = parent;
//    } while (1);
//    rect.origin.x = rect.origin.x * CC_CONTENT_SCALE_FACTOR();
//    rect.origin.y = rect.origin.y * CC_CONTENT_SCALE_FACTOR();
//    rect.size.width = rect.size.width * scaleX * CC_CONTENT_SCALE_FACTOR();
//    rect.size.height = rect.size.height * scaleY * CC_CONTENT_SCALE_FACTOR();
//    rect.origin.y = CCDirector::sharedDirector()->getWinSizeInPixels().height - rect.origin.y - rect.size.height;
//    return rect;
}

void HGameDelegate::setRandomSeed(long seed) {
    haypi::setRandomSeed(seed);
}

long HGameDelegate::getRandom() {
    return haypi::getRandom();
}

bool HGameDelegate::stringEndsWith(const char *filename, const char *ends) {
    return haypi::stringEndsWith(filename, ends);
}

void HGameDelegate::setDurationOfFadeInOut(float fin, float fout) {
    haypi::setDurationOfFadeInOut(fin, fout);
}

const char *HGameDelegate::adjustText(const char *content, const char *font, int fontSize, int width, int minTextLength) {
    return haypi::adjustText(content, font, fontSize, width, minTextLength);
}

//base64
int HGameDelegate::encodeBase64(void *result, const void *data, int len) {
    return haypi::encodeBase64(result, data, len);
}

int HGameDelegate::decodeBase64(void *result, const void *data, int len) {
    return haypi::decodeBase64(result, data, len);
}

//md5
void HGameDelegate::MD5Init (MD5_CTX *context) {
    haypi::MD5Init(context);
}

void HGameDelegate::MD5Update (MD5_CTX *context, unsigned char *input, unsigned int inputLen) {
    haypi::MD5Update(context, input, inputLen);
}

void HGameDelegate::MD5Final (unsigned char digest[16], MD5_CTX *context) {
    haypi::MD5Final(digest, context);
}

void HGameDelegate::MD5Data(const void *data, int len, unsigned char digest[16]) {
    haypi::MD5Data(data, len, digest);
}

//zip
int HGameDelegate::zip(unsigned char *data, int len, unsigned char *result, int size) {
    return haypi::zip(data, len, result, size);
}

int HGameDelegate::unzip(unsigned char *data, int len, unsigned char *result, int size) {
    return haypi::unzip(data, len, result, size);
}

void HGameDelegate::unzipFile(const char *zipFile, const char *dir, const char *resultPath, FuncOnPercent onPercent, bool onlyMatch, bool pvr2Png) {    
    CCArray *excludeList = CCArray::createWithCapacity(16);
    CCArray *includeList = CCArray::createWithCapacity(16);
    if (onlyMatch) {
        //delete by zg
//        if (HFileUtils::getInstance()->getIsRetina()) {
//            excludeList->addObject(CCString::create(".jpeg"));
//            excludeList->addObject(CCString::create(".jpg"));
//            excludeList->addObject(CCString::create(".plist"));
//            excludeList->addObject(CCString::create(".plistb"));
//            excludeList->addObject(CCString::create(".png"));
//            excludeList->addObject(CCString::create(".pvr"));
//            excludeList->addObject(CCString::create(".pvr.ccz"));
//            
//            includeList->addObject(CCString::create("_hd.jpeg"));
//            includeList->addObject(CCString::create("_hd.jpg"));
//            includeList->addObject(CCString::create("_hd.plist"));
//            includeList->addObject(CCString::create("_hd.plistb"));
//            includeList->addObject(CCString::create("_hd.png"));
//            includeList->addObject(CCString::create("_hd.pvr"));
//            includeList->addObject(CCString::create("_hd.pvr.ccz"));
//        } else {
//            excludeList->addObject(CCString::create("_hd.jpeg"));
//            excludeList->addObject(CCString::create("_hd.jpg"));
//            excludeList->addObject(CCString::create("_hd.plist"));
//            excludeList->addObject(CCString::create("_hd.plistb"));
//            excludeList->addObject(CCString::create("_hd.png"));
//            excludeList->addObject(CCString::create("_hd.pvr"));
//            excludeList->addObject(CCString::create("_hd.pvr.ccz"));
//        }
//        PHSCREENDATA screenData = currentScreenData();
//        excludeList->addObject(CCString::create(".ccbi"));
//        includeList->addObject(CCString::createWithFormat("_%s.ccbi", screenData->suffix));
    }
    
    haypi::unzipFile(zipFile, dir, resultPath, (excludeList->count() > 0) ? excludeList : NULL, (includeList->count() > 0) ? includeList : NULL, onPercent, pvr2Png);
}

bool HGameDelegate::pathExists(const char *path) {
    return haypi::pathExists(path);
}

//dictionary
CCDictionary *HGameDelegate::dictionaryFromPlist(const char *data, unsigned int size) {
    return haypi::dictionaryFromPlist(data, size);
}

CCDictionary *HGameDelegate::dictionaryFromPlist(const char *filename) {
    return haypi::dictionaryFromPlist(filename);
}

CCDictionary *HGameDelegate::dictionaryFromJSON(const char *data, unsigned int size) {
    return haypi::dictionaryFromJSON(data, size);
}

CCDictionary *HGameDelegate::dictionaryFromJSON(const char *filename) {
    return haypi::dictionaryFromJSON(filename);
}

std::string HGameDelegate::dictionaryToJSON(CCDictionary *dict) {
    return haypi::dictionaryToJSON(dict);
}

//music
void HGameDelegate::setBGMusicVolume(float volume) {
    HMusicManager::getInstance()->setBGMusicVolume(volume);
}

float HGameDelegate::getBGMusicVolume() {
    return HMusicManager::getInstance()->getBGMusicVolume();
}

void HGameDelegate::setSoundEffectVolume(float volume) {
    HMusicManager::getInstance()->setSoundEffectVolume(volume);
}

float HGameDelegate::getSoundEffectVolume() {
    return HMusicManager::getInstance()->getSoundEffectVolume();
}

void HGameDelegate::addMusic(CCString *musicFile, int musicID) {
    //delete by zg
//    char *dir = HFileUtils::getInstance()->getResourceExtendPath();
    char * dir = NULL;
    if (dir) {
        CCString *file = CCString::createWithFormat("%smusic/%s", dir, musicFile->getCString());
        if (pathExists(file->getCString())) musicFile = file;
    }
    else {
        std::string str = "music/";
        str += musicFile->getCString();
        musicFile = HString::create(CCFileUtils::sharedFileUtils()->fullPathForFilename(str.c_str()));
    }
    HMusicManager::getInstance()->addMusic(musicFile, musicID);
}

void HGameDelegate::playMusic(int musicID, bool loop) {
    HMusicManager::getInstance()->playMusic(musicID, loop);
}

void HGameDelegate::playSoundEffect(int effectID, bool loop) {
    HMusicManager::getInstance()->playSoundEffect(effectID, loop);
}

//date
int HGameDelegate::secondsSince1970() {
    return haypi::secondsSince1970();
}

const char *HGameDelegate::dateFormat(int format, int secsSince1970) {
    return haypi::dateFormat(format, secsSince1970);
}

//net
//void HGameDelegate::onUserLoggedIn(int uid,int hostCode)
//{
//    HGameScene *pGameScene = AppDelegate::getInstance()->getGameManager();
//}
void HGameDelegate::setPlatFormAndMarket(int platform, int market)
{
    HNetManager::setPlatFormAndMarket(platform, market);
}

void HGameDelegate::setNetParameters(const char *passportURL, const char *localPassportURL, const char *gameID, const char *socketIPKey, const char *socketPortKey, const char *webSite, const char *version) {
    haypi::setNetParameters(passportURL, localPassportURL, gameID, socketIPKey, socketPortKey, webSite, version);
}

void HGameDelegate::enableSocket(bool enable, bool needRequestIP) {
    HNetManager::getInstance()->setUseSocket(enable);
    HNetManager::getInstance()->setNeedRequestIP(needRequestIP);
}

void HGameDelegate::enableHttpReplaceSocket(bool enable) {
    HNetManager::getInstance()->setEnableHttpReplaceSocket(enable);
}

void HGameDelegate::fakeLoginWithAccount(const char *username, const char *password) {
    m_bIsFake = true;
    HNetManager::getInstance()->fakeLoginWithAccount(username, password);
}

void HGameDelegate::fakeLogin() {
    m_bIsFake = true;
    HNetManager::getInstance()->fakeLogin();
}

void HGameDelegate::loginWithAccount(const char *username, const char *password) {
    m_bIsFake = false;
    HNetManager::getInstance()->loginWithAccount(username, password);
}

void HGameDelegate::login() {
    m_bIsFake = false;
    HNetManager::getInstance()->login();
}

void HGameDelegate::registerProtocolDelegate(int action, HObject *delegate) {
    HNetManager::getInstance()->registerProtocolDelegate(action, delegate);
}

void HGameDelegate::unregisterProtocolDelegate(int action, HObject *delegate) {
    HNetManager::getInstance()->unregisterProtocolDelegate(action, delegate);
}

bool HGameDelegate::waitingForLogin() {
    return HNetManager::getInstance()->waitingForLogin();
}

void HGameDelegate::clearLoginStatus() {
    HNetManager::getInstance()->setLoginStatus(0);
}

void HGameDelegate::requestRegisterWithParam0(int param0) {
    HNetManager::getInstance()->requestRegisterWithParam0(param0);
}

void HGameDelegate::requestRegisterWithParam0(int param0,int param1) {
    HNetManager::getInstance()->requestRegisterWithParam0(param0,param1);
}

void HGameDelegate::requestRegisterWithInviteUID(const char* inviteUID) {
    HNetManager::getInstance()->requestRegisterWithInviteCode(CCString::create(inviteUID));
}

void HGameDelegate::requestRegisterWithInviteUIDAndSid(const char *inviteUID, int sid)
{
    HNetManager::getInstance()->requestRegisterWithInviteCodeAndSid(CCString::create(inviteUID), sid);
}

const bool HGameDelegate::isFakeRegistered() {
    return HNetManager::getInstance()->getIsFakeRegistered();
}

const bool HGameDelegate::isRegistered() {
    return HNetManager::getInstance()->getIsRegistered();
}

const CCString *HGameDelegate::getUserID() {
    return HNetManager::getInstance()->getUID();
}

const CCString *HGameDelegate::getHash() {
    return HNetManager::getInstance()->getHash();
}

const CCString* HGameDelegate::getUsername(){
    return HNetManager::getInstance()->getUsername();
}

const CCString *HGameDelegate::getDeviceID() {
    return HNetManager::getInstance()->getDeviceID();
}

const CCString *HGameDelegate::getAuthKey() {
    return HNetManager::getInstance()->getAuthKey();
}

void HGameDelegate::changeUsername(const char *username, const char *authkey) {
    HNetManager::getInstance()->changeUsername(username, authkey);
}

void HGameDelegate::disableServerList() {
    HNetManager::disableServerList();
}

CCDictionary* HGameDelegate::requestServerList(bool fake) {
    return HNetManager::getInstance()->requestServerList(fake);
}
void HGameDelegate::resetAccount() {
    HNetManager::getInstance()->resetAccount();
 
}

void HGameDelegate::visitWeb(const char *webSite) {
    HNetManager::getInstance()->visitWeb(webSite);
}

void HGameDelegate::sendMessage(int msgID, CCDictionary *param) {
    HNetManager::getInstance()->sendMessage(msgID, param);
}

bool HGameDelegate::postRequest(int command, CCDictionary *param, HObject *delegate, bool ignoreDuplicaiton, int commandLevel, int netMode) {
    return HNetManager::getInstance()->postRequest(command, param, delegate, ignoreDuplicaiton, commandLevel, netMode);
}

void HGameDelegate::convertPVR2PNG(const char *pvr, const char *png) {
    haypi::convertPVR2PNG(pvr, png);
}

void HGameDelegate::attachPath(const char *path) {
    // delete by zg
//    HFileUtils::getInstance()->attachPath(path);
}

bool HGameDelegate::isExtendedResources() {
    //delete by zg
//    const char *zipFilePath = HFileUtils::getInstance()->getResourceZipFilePath();
//    if (!zipFilePath) zipFilePath = getResourceZipFilePathEx();
//    if (zipFilePath) {
//        bool needUpdateResource = true;
//        char resultPath[260];
//        strcpy(resultPath, CCFileUtils::sharedFileUtils()->getWriteablePath().c_str());
//        strcat(resultPath, "resource/");
//        if (pathExists(resultPath)) {
//            HFileUtils::getInstance()->setResourceExtendPath(resultPath);
//            int oldVer = -1;
//            unsigned long size = 0;
//            unsigned char *data = HFileUtils::getInstance()->getFileData("config/ver", &size);
//            if (data) {
//                oldVer = 0;
//                char *d = (char *)data;
//                while ((d < (char *)data + size) && (*d >= '0') && (*d <= '9')) { oldVer = oldVer * 10 + (*d - '0'); ++d; }
//                ++d;
//                int checkVer = 0;
//                while ((d < (char *)data + size) && (*d >= '0') && (*d <= '9')) { checkVer = checkVer * 10 + (*d - '0'); ++d; }
//                if (oldVer != checkVer) oldVer = -1;
////                oldVer = atoi((const char *)data);
//                delete [] data;
//            }
//            HFileUtils::getInstance()->setResourceExtendPath(NULL);
//            int newVer = -1;
//            data = HFileUtils::getInstance()->getFileData("config/ver", &size);
//            if (data) {
//                newVer = atoi((const char *)data);
//                delete [] data;
//            }
//            if (newVer <= oldVer) {
//                needUpdateResource = false;
//            }
//            HFileUtils::getInstance()->setResourceExtendPath(resultPath);
//        }
//        if (!needUpdateResource) {
//            return true;
//        }
//    }
    return false;
}


void onPercentOfExtendResources(int percent) {
    
}

void HGameDelegate::extendResources(FuncOnPercent onPercent, bool onlyMatch) {
    //delete by zg
//    const char *zipFilePath = HFileUtils::getInstance()->getResourceZipFilePath();
//    if (!zipFilePath) zipFilePath = getResourceZipFilePathEx();
//    if (zipFilePath) {
//        char resultPath[260];
//        strcpy(resultPath, CCFileUtils::sharedFileUtils()->getWriteablePath().c_str());
//        strcat(resultPath, "resource/");
//        bool needUpdateResource = true;
//        int newVer = 0;
//        HFileUtils::getInstance()->setResourceExtendPath(NULL);
//        unsigned long size = 0;
//        unsigned char *data = HFileUtils::getInstance()->getFileData("config/ver", &size);
//        if (data) {
//            newVer = atoi((const char *)data);
//            delete [] data;
//        }
//        if (pathExists(resultPath)) {
//            HFileUtils::getInstance()->setResourceExtendPath(resultPath);
//            int oldVer = -1;
//            data = HFileUtils::getInstance()->getFileData("config/ver", &size);
//            if (data) {
//                oldVer = 0;
//                char *d = (char *)data;
//                while ((d < (char *)data + size) && (*d >= '0') && (*d <= '9')) { oldVer = oldVer * 10 + (*d - '0'); ++d; }
//                ++d;
//                int checkVer = 0;
//                while ((d < (char *)data + size) && (*d >= '0') && (*d <= '9')) { checkVer = checkVer * 10 + (*d - '0'); ++d; }
//                if (oldVer != checkVer) oldVer = -1;
////                oldVer = atoi((const char *)data);
//                delete [] data;
//            }
//            if (newVer <= oldVer) {
//                needUpdateResource = false;
//            }
//            HLOGI("extendResources: old(%d), new(%d)", oldVer, newVer);
//        }
//        HFileUtils::getInstance()->setResourceExtendPath(resultPath);
//        
//        if (needUpdateResource) {
//            bool pvr2Png = !CCConfiguration::sharedConfiguration()->supportsPVRTC() || !HSourceCache::getInstance()->getUsePVR();
//            unzipFile(zipFilePath, stringEndsWith(zipFilePath, "apk") ? "assets/" : "", resultPath, onPercent, onlyMatch, pvr2Png);
//            char version[32];
//            sprintf(version, "%d\n%d\n", newVer, newVer);
//            strcat(resultPath, "config/ver");
//            HFileUtils::getInstance()->saveFileToLocal((const char *)version, strlen(version), resultPath);
//        }
//    }
}

void HGameDelegate::ratioOfEquality() {
    HRootLayer::m_sbRatioOfEquality = true;
}

//private

//void HGameDelegate::preLoadLoaders() {
//    CCNodeLoaderLibrary *library = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
//    library->registerCCNodeLoader("CCEditBox", CCEditBoxLoader::loader());
//    library->registerCCNodeLoader("CCTableView", CCTableViewLoader::loader());
//}







//static const char *gSupportLocale[] = {
//    "en",
//    "zh_cn",
//    NULL
//};
static char gLocaleCode[32] = "en";
static CCDictionary *gLocaleLangs = NULL;

void setLocaleCode(const char *localCode) {
    strcpy(gLocaleCode, localCode);
    char *pChar = gLocaleCode;
    while (*pChar != '\0') {
        if ((*pChar >= 'A') && (*pChar <= 'Z')) *pChar += 'a' - 'A';
        ++pChar;
    }
//    bool bFind = false;
//    int i = 0;
//    while (gSupportLocale[i] != NULL) {
//        if (0 == strcmp(gSupportLocale[i], gLocaleCode)) {
//            bFind = true;
//            break;
//        }
//        ++i;
//    }
//    if (!bFind) strcpy(gLocaleCode, gSupportLocale[0]);
    HLOGI("locale: -%s-", gLocaleCode);
//    if (gLocaleLangs) {
//        updateLocaleStrings();
//    }
}

void loadLocaleStrings(const char *locale) {
    if (gLocaleLangs == NULL) {
        gLocaleLangs = new CCDictionary();
    }
    
    char filename[256];
    sprintf(filename, "lang/%s.lproj/Localizable.strings", locale);
    unsigned long size = 0;
    unsigned char *data = CCFileUtils::sharedFileUtils()->getFileData(filename, "rb", &size);
    if (!data) {
        char *pos = strstr(locale, "_");
        if (pos) {
            char realLocale[256];
            int len = pos - locale;
            strncpy(realLocale, locale, len);
            realLocale[len] = '\0';
            sprintf(filename, "lang/%s.lproj/Localizable.strings", realLocale);
            data = CCFileUtils::sharedFileUtils()->getFileData(filename, "rb", &size);
        }
    }
    if (data) {
        if (size > 0) {
//            gLocaleLangs->removeAllObjects();
            int bufSize = 1024;
            char *buf = new char [bufSize];
            char *pDataEnd = (char *)data + size;
            char *pLineStart = (char *)data;
            while (pLineStart < pDataEnd) {
                while ((*pLineStart == ' ') || (*pLineStart == '\t') || (*pLineStart == '\r') || (*pLineStart == '\n')) ++pLineStart;
                if (pLineStart >= pDataEnd) break;
                if ((pLineStart[0] == '/') && (pLineStart[1] == '/')) {
                    pLineStart += 2;
                    while ((pLineStart < pDataEnd) && (*pLineStart != '\n')) ++pLineStart;
                    continue;
                }
                char *pLineEnd = pLineStart;
                while ((pLineEnd < pDataEnd) && (*pLineEnd != '\n')) ++pLineEnd;
                ++pLineEnd;
                if (pLineEnd > pDataEnd) break;
                
                do {
                    char *pKeyStart = pLineStart;
                    while ((pKeyStart < pLineEnd) && (*pKeyStart != '"')) ++pKeyStart;
                    ++pKeyStart;
                    if (pKeyStart >= pLineEnd) break;
                    char *pKeyEnd = pKeyStart;
                    while ((pKeyEnd < pLineEnd) && (*pKeyEnd != '"')) ++pKeyEnd;
                    ++pKeyEnd;
                    if (pKeyEnd >= pLineEnd) break;
                    
                    char *pValueStart = pKeyEnd;
                    while ((pValueStart < pLineEnd) && (*pValueStart != '"')) ++pValueStart;
                    ++pValueStart;
                    if (pValueStart >= pLineEnd) break;
                    char *pValueEnd = pValueStart;
                    while ((pValueEnd < pLineEnd) && (*pValueEnd != '"')) {
                        if (*pValueEnd == '\\') ++pValueEnd;
                        ++pValueEnd;
                    }
                    ++pValueEnd;
                    if (pValueEnd >= pLineEnd) break;
                    
                    int keyLen = pKeyEnd - pKeyStart - 1;
                    char key[256];
                    strncpy(key, pKeyStart, keyLen);
                    key[keyLen] = '\0';
                    
                    int valueLen = pValueEnd - pValueStart - 1;
                    while (valueLen > bufSize) bufSize *= 2;
                    int index = 0;
                    for (int i = 0; i < valueLen; ++i) {
                        if (pValueStart[i] != '\\') {
                            buf[index++] = pValueStart[i];
                        } else {
                            ++i;
                            switch (pValueStart[i]) {
                                case 'r':
                                    buf[index++] = '\r';
                                    break;
                                case 'n':
                                    buf[index++] = '\n';
                                    break;
                                case 't':
                                    buf[index++] = '\t';
                                    break;
                                default:
                                    buf[index++] = pValueStart[i];
                                    break;
                            }
                        }
                    }
                    buf[index++] = '\0';
                    CCString *value = CCString::create(buf);
//                    CCString *value = CCString::createWithData((unsigned char *)pValueStart, pValueEnd - pValueStart - 1);
                    gLocaleLangs->setObject(value, key);
                } while (0);
                pLineStart = pLineEnd;
            }
            delete [] buf;
        }
        delete [] data;
    }
}

void updateLocaleStrings() {
    if (gLocaleLangs) gLocaleLangs->removeAllObjects();
    loadLocaleStrings("en");
    if (strcmp(gLocaleCode, "en")) {
        loadLocaleStrings(gLocaleCode);
    }
}

bool HLocalizedStringExists(const char *str) {
    return NULL != gLocaleLangs->objectForKey(str);
}

const char *HLocalizedString(const char *str) {
    CCString *pRet = (CCString *)gLocaleLangs->objectForKey(str);
    if (pRet) {
        return pRet->getCString();
    }
    return str;
}

CCString *HLocalizedStringCCString(const char *str) {
    CCString *pRet = (CCString *)gLocaleLangs->objectForKey(str);
    if (pRet) {
        return pRet;
    }
    return CCString::create(str);
}

static HSCREENDATA gSupportScreens[8];
static int gScreenCount = 0;

//static HSCREENDATA gSupportScreens[] = {
    //    {320, 240, 1.0f, 1.0f, "xsmall", 1},
//    {480, 320, 1.0f, 1.0f, "iphone", 1},
    //    {480, 340, 1.0f, 1.0f, "small", 1},
    //    {568, 320, 1.0f, 1.0f, "iphone5", 1},
    //    {800, 480, 1.0f, 1.0f, "medium", 2},
    //    {1024, 768, 1.0f, 1.0f, "ipad", 2},
    //    {1280, 800, 1.0f, 1.0f, "large", 2},
    //    {2048, 1536, 1.0f, 1.0f, "xlarge", 4},
//};


void addSupportedScreenData(int width, int height, const char *suffix, float gameResourceScale) {
    if (gScreenCount >= 8) return;
    float ratio = height * 1.0f / width;
    int index = 0;
    for (index = 0; index < gScreenCount; ++index) {
        if (ratio < gSupportScreens[index].ratio) break;
    }
    if (index < gScreenCount) {
        memmove(&gSupportScreens[index + 1], &gSupportScreens[index], sizeof(HSCREENDATA) * (gScreenCount - index));
    }
    gSupportScreens[index].width = width;
    gSupportScreens[index].height = height;
    gSupportScreens[index].ratio = height * 1.0f / width;
    gSupportScreens[index].startX = 0.0f;
    gSupportScreens[index].startY = 0.0f;
    strcpy(gSupportScreens[index].suffix, suffix);
    gSupportScreens[index].gameResourceScale = gameResourceScale;
    ++gScreenCount;
}

static bool gNoHDResource = false;
bool noHDResource() {
    return gNoHDResource;
}

static PHSCREENDATA gCurrentScreenData = NULL;
PHSCREENDATA currentScreenData(bool forceLoad) {
    if (forceLoad) gCurrentScreenData = NULL;
    if (!gCurrentScreenData) {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        float ratio = screenSize.height / screenSize.width;
        for (int i = gScreenCount - 1; i > 0; --i) {
            float midRatio = (gSupportScreens[i].ratio + gSupportScreens[i - 1].ratio) / 2;
            if (ratio > midRatio) {
                gCurrentScreenData = &gSupportScreens[i];
                break;
            }
//            if (((int)screenSize.width == (int)gSupportScreens[i].width) && ((int)screenSize.height == (int)gSupportScreens[i].height)) {
//                gCurrentScreenData = &gSupportScreens[i];
//                break;
//            }
//            float midW = (gSupportScreens[i].width + gSupportScreens[i - 1].width) / 2;
//            float midH = (gSupportScreens[i].height + gSupportScreens[i - 1].height) / 2;
//            if ((screenSize.width >= midW) && (screenSize.height >= midH)) {
//                gCurrentScreenData = &gSupportScreens[i];
//                break;
//            }
        }
        if (!gCurrentScreenData) gCurrentScreenData = &gSupportScreens[0];
//        gCurrentScreenData->scaleX = screenSize.width / gCurrentScreenData->width;
//        gCurrentScreenData->scaleY = screenSize.height / gCurrentScreenData->height;
//        HLOGI("cxj screen data:{%d, %d, %f, %f, %s}", (int)gCurrentScreenData->width, (int)gCurrentScreenData->height, gCurrentScreenData->scaleX, gCurrentScreenData->scaleY, gCurrentScreenData->suffix);
        if (AppDelegate::getInstance()->getRetinaScreen()) { //retina screen
            if (gCurrentScreenData->width >= 1024) {
                gNoHDResource = true;
            }
//            if (screenSize.width >= 1024) {
//                gCurrentScreenData->gameResourceScale = 2;
//            }
        } else {
//            if (gCurrentScreenData->scaleX > 1.5f) {
//                gCurrentScreenData->gameResourceScale = 2;
//            }
        }
    }
    return gCurrentScreenData;
}

std::string getUILayout(const char *layout, PHSCREENDATA *retScreenData) {
#if 1
    if (retScreenData) *retScreenData = currentScreenData();
    return layout;
#else
    std::string filename = layout;
    int pos = filename.rfind(".ccbi");
    if (pos < 1) return filename;
//    int count = sizeof(gSupportScreens) / sizeof(gSupportScreens[0]);
    for (int i = gScreenCount - 1; i > 0; --i) {
        int len = (int)strlen(gSupportScreens[i].suffix);
        if ((pos > len) && !strcmp(filename.c_str() + pos - len, gSupportScreens[i].suffix)) {
            filename.replace(pos - len, len, "");
            pos -= len;
            break;
        }
    }
    std::string ret = filename;
    
    PHSCREENDATA pData = currentScreenData();
    if (std::string::npos == ret.find(pData->suffix)) {
        ret.insert(pos, "_");
        ret.insert(pos + 1, pData->suffix);
    }
    ret.insert(0, "/");
    ret.insert(0, pData->suffix);
    ret.insert(0, "layout/");
    bool bExists = HFileUtils::getInstance()->pathExists(ret.c_str());
    if (!bExists) {
        int index = 0;
        for (index = gScreenCount - 1; index > 0; --index) {
            if (pData == &gSupportScreens[index]) break;
        }
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        for (int i = 1; i < gScreenCount; ++i) {
            for (int j = 0; j < 2; ++j) {
                int k = index;
                if (j == 0) {
                    k -= i;
                    if (k < 0) continue;
                } else {
                    k += i;
                    if (k >= gScreenCount) continue;
                }
                pData = &gSupportScreens[k];
                pData->scaleX = screenSize.width / pData->width;
                pData->scaleY = screenSize.height / pData->height;
                //                gCurrentScreenData = pData;
                ret = filename;
                if (std::string::npos == ret.find(pData->suffix)) {
                    ret.insert(pos, "_");
                    ret.insert(pos + 1, pData->suffix);
                }
                ret.insert(0, "/");
                ret.insert(0, pData->suffix);
                ret.insert(0, "layout/");
                bExists = HFileUtils::getInstance()->pathExists(ret.c_str());
                if (bExists) break;
            }
            if (bExists) break;
        }
    }
    if (!bExists) ret = layout;
    if (retScreenData) *retScreenData = pData;
    return ret;
#endif
}

HNAMESPACE_END

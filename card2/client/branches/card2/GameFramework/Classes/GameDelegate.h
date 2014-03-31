#ifndef  _GAME_DELEGATE_H_
#define  _GAME_DELEGATE_H_

HNAMESPACE_BEGIN

#define HCOMMAND_VIEW_MIN -999
#define HCOMMAND_VIEW_MAX -100

class CC_DLL HGameDelegate: public HObject {
    CC_SYNTHESIZE(bool, m_bIsFake, IsFake)
    CC_SYNTHESIZE(CCSize, m_szScreen, ScreenSize);
//    CC_SYNTHESIZE_READONLY(HFileUtils *, m_pFileUtils, FileUtils);
    CC_SYNTHESIZE_READONLY(HSourceCache *, m_pSourceCache, SourceCache);
    CC_SYNTHESIZE_READONLY(HTimerManager *, m_pTimerManager, TimerManager);

    CC_SYNTHESIZE_READONLY(HGameShowLayer *, m_pGameShowLayer, GameShowLayer);
    CC_SYNTHESIZE_READONLY(HUILayer *, m_pGameDecorationLayer, GameDecorationLayer);
    CC_SYNTHESIZE_READONLY(HUILayer *, m_pUILayer, UILayer);
    
    CC_SYNTHESIZE(int, m_pSafeMemorySize, SafeMemorySize); //unit: M bytes
public:
    HGameDelegate();
    virtual ~HGameDelegate();
    bool HasLogin() { return m_hasLogin; }
    bool memoryIsSafe();
    
    CCObject *asyncInitGame(int command, CCObject *param) { initGame(); return NULL; }
    
    virtual void clear();
    
    virtual void updateScissors();
    
    void setHeartBeatInterval(int seconds);
    void setReloginInterval(int seconds);
    void setProtocolTimeoutInterval(int seconds);
    
    int UID;
    int Hash;
    virtual void preloadLoaders()  = 0;
    virtual void initGame();
    virtual void enterBackground() = 0;
    virtual void enterForeground() = 0;
    
    virtual void onNeedHeartBeat() {}
    virtual void onNeedUpdateData() {}
    virtual void onNeedReLogin() {}
    virtual void onNetworkFailed() {}
    virtual void onForceCloseByServer() {}
    virtual void onNeedAccount() = 0;
    virtual void startGame() = 0;
    virtual void initDirector();
    
    CCObject *asyncLoginError(int commmand, CCObject *param);
    CCObject *asyncReceiveLastUserState(int state, CCObject *param);
    virtual void onReceiveLastUserState(int state) {}
    virtual void onLoginError(int errorCode, CCDictionary *param);
    
    virtual void onMessageBox(const char *message, const char *titile) = 0;
    
    
    virtual void updateNetDictionary(bool bIsSocket, CCDictionary *param, CCDictionary *socket) {}
    virtual void receiveDataTimeout(int command) = 0;
    
    virtual void preProcessNetResult(int command, CCDictionary *result) = 0;
    
    virtual bool processFailedNetResult(int command, CCDictionary *result) { return false; }
   
    virtual void onCommand(int command, const char *param);
    virtual void onBackPressed() {}
    virtual void onMenuPressed() {}
    
    virtual void onRootLayerCountChanged(int count) {}
    
    CCPoint posToScreen(CCNode *node);
    float scaleToScreen(CCNode *node);
    CCRect rectToDeviceInPixels(CCNode *node);
    
    //common
    void setRandomSeed(long seed);
    long getRandom();
    
    bool stringEndsWith(const char *filename, const char *ends);
    
    void setDurationOfFadeInOut(float fin, float fout);
    
    const char *adjustText(const char *content, const char *font, int fontSize, int width, int minTextLength = 0);
    
    //base64
    int encodeBase64(void *result, const void *data, int len);
    int decodeBase64(void *result, const void *data, int len);
    
    //md5
    void MD5Init (MD5_CTX *context);
    void MD5Update (MD5_CTX *context, unsigned char *input, unsigned int inputLen);
    void MD5Final (unsigned char digest[16], MD5_CTX *context);
    void MD5Data(const void *data, int len, unsigned char digest[16]);
    
    //zip
    int zip(unsigned char *data, int len, unsigned char *result, int size);
    int unzip(unsigned char *data, int len, unsigned char *result, int size);
    void unzipFile(const char *zipFile, const char *dir, const char *resultPath, FuncOnPercent onPercent = NULL, bool onlyMatch = false, bool pvr2Png = false);
    bool pathExists(const char *path);
    
    //dictionary
    CCDictionary *dictionaryFromPlist(const char *data, unsigned int size);
    CCDictionary *dictionaryFromPlist(const char *filename);
    CCDictionary *dictionaryFromJSON(const char *data, unsigned int size);
    CCDictionary *dictionaryFromJSON(const char *filename);
    std::string dictionaryToJSON(CCDictionary *dict);
    
    //music
    virtual void setBGMusicVolume(float volume);
    virtual float getBGMusicVolume();
    virtual void setSoundEffectVolume(float volume);
    virtual float getSoundEffectVolume();
    void addMusic(CCString *musicFile, int musicID);
    virtual void playMusic(int musicID, bool loop = true);
    virtual void playSoundEffect(int effectID, bool loop = false);
    
    
    //date
    int secondsSince1970();
    const char *dateFormat(int format, int secsSince1970);
    
    //net
    //void onUserLoggedIn(int uid,int hostCode);
    void setPlatFormAndMarket(int platform, int market);
    void registerProtocolDelegate(int action, HObject *delegate);
    void unregisterProtocolDelegate(int action, HObject *delegate);
    bool waitingForLogin();
    void clearLoginStatus();
    void setNetParameters(const char *passportURL, const char *localPassportURL, const char *gameID, const char *socketIPKey, const char *socketPortKey, const char *webSite, const char *version);
    void enableSocket(bool enable, bool needRequestIP = false);
    void enableHttpReplaceSocket(bool enable);
    void fakeLoginWithAccount(const char *username, const char *password);
    void fakeLogin();
    void loginWithAccount(const char *username, const char *password);
    void login();
    void resetAccount();
    void requestRegisterWithParam0(int param0);
    void requestRegisterWithParam0(int param0,int param1);
    void requestRegisterWithInviteUID(const char* inviteUID);
    void requestRegisterWithInviteUIDAndSid(const char *inviteUID, int sid);
    void visitWeb(const char *webSite = NULL);
    void sendMessage(int msgID, CCDictionary *param);
    virtual bool postRequest(int command, CCDictionary *param, HObject *delegate, bool ignoreDuplicaiton, int commandLevel = 0, int netMode = -1);
    //request for server list
    void disableServerList();
    virtual void onReceiveServerList(CCArray *serverlist){}
    CCDictionary* requestServerList(bool fake);
    const bool isFakeRegistered();
    const bool isRegistered();
    const CCString *getUserID();
    const CCString *getHash();
    const CCString *getUsername();
    const CCString *getDeviceID();
    const CCString *getAuthKey();
    void changeUsername(const char *username, const char *authkey);
    //
    void convertPVR2PNG(const char *pvr, const char *png);
    void attachPath(const char *path);
    bool isExtendedResources();
    void extendResources(FuncOnPercent onPercent = NULL, bool onlyMatch = false);
    static void ratioOfEquality();
    
protected:
    bool m_hasLogin;
    
private:
    int m_iTotalMemory; //unit: M bytes
};

CC_DLL void setLocaleCode(const char *localCode);
CC_DLL void updateLocaleStrings();
CC_DLL bool HLocalizedStringExists(const char *str);
CC_DLL const char *HLocalizedString(const char *str);

CC_DLL CCString *HLocalizedStringCCString(const char *str);

CC_DLL typedef struct {
    short width;
    short height;
    float ratio;
    float startX;
    float startY;
    float osStartX;
    float osStartY;
    char suffix[12];
    float gameResourceScale;
}HSCREENDATA, *PHSCREENDATA;

CC_DLL void addSupportedScreenData(int width, int height, const char *suffix, float gameResourceScale);
CC_DLL bool noHDResource();
CC_DLL PHSCREENDATA currentScreenData(bool forceLoad = false);
CC_DLL std::string getUILayout(const char *layout, PHSCREENDATA *retScreenData);

HNAMESPACE_END

#endif // _GAME_DELEGATE_H_


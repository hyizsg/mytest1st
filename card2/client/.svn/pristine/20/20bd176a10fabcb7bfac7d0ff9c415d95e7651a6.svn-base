#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

class CC_DLL HKeypadDelegate: public CCObject, public CCKeypadDelegate {
public:
    virtual void keyBackClicked();
    virtual void keyMenuClicked();
};

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  AppDelegate : private cocos2d::CCApplication {
    CC_SYNTHESIZE_READONLY(haypi::HGameDelegate *, m_pGameDelegate, GameManager);
    CC_SYNTHESIZE_READONLY(haypi::HGameScene *, m_pGameScene, GameScene);
    CC_SYNTHESIZE(int, m_iReloginInterval, ReloginInterval);
    CC_SYNTHESIZE(bool, m_bIsRetinaScreen, RetinaScreen);
    
public:
    AppDelegate();
    virtual ~AppDelegate();
    
    static AppDelegate *getInstance();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
    
private:
    static AppDelegate *m_sAppDelegate;
    HKeypadDelegate m_oKaypadDeletage;
    long m_lTimeEnterBackground;
    
    void preLoadLoaders();
};

#endif // _APP_DELEGATE_H_


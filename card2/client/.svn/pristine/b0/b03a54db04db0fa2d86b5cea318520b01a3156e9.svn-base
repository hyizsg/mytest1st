#ifndef _GAME_SCENE_H__
#define _GAME_SCENE_H__

HNAMESPACE_BEGIN

class HLoadingLayer;

class CC_DLL HGameScene: public CCScene {
    CC_SYNTHESIZE_READONLY(HGameShowLayer *, m_pGameShowLayer, GameShowLayer);
    CC_SYNTHESIZE_READONLY(HUILayer *, m_pGameDecorationLayer, GameDecorationLayer);
    CC_SYNTHESIZE_READONLY(HUILayer *, m_pUILayer, UILayer);
public:
    HGameScene();
    virtual ~HGameScene();

    virtual bool init();
    
    void startAIV(bool bLockTouch = false);
    void stopAIV();
    
    void startGame();
    
private:
    HLoadingLayer *m_pLoadingLayer;
};

HNAMESPACE_END

#endif // _GAME_SCENE_H__

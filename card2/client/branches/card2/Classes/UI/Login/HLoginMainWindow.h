//
//  HLoginMainWindow.h
//  card2
//
//  Created by zhou gang on 14-2-13.
//
//

#ifndef __card2__HLoginMainWindow__
#define __card2__HLoginMainWindow__


class HLoginMainWindow : public HWindow {
    HUICLASS_DELARE(HLoginMainWindow, HWindow)
    
public:
    virtual bool init();
    virtual void onPresented();
    
    void resetUI();
    void notifyActionMsg(CCObject* obj);
    
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    CLICK_SEL_DELARE(onAccountClick);
    CLICK_SEL_DELARE(onWebClick);
    
    CLICK_SEL_DELARE(onFakeAccountClick);
    CLICK_SEL_DELARE(onFakeStartClick);
    CLICK_SEL_DELARE(onFakeResetClick);
  
};


#endif /* defined(__card2__HLoginMainWindow__) */

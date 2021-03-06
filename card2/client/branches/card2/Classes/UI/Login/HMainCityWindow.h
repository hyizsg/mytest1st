//
//  HMainCityWindow.h
//  card2
//
//  Created by zhou gang on 14-2-13.
//
//

#ifndef __card2__HMainCityWindow__
#define __card2__HMainCityWindow__

class HMainCityWindow : public HWindow{
    HUICLASS_DELARE(HMainCityWindow, HWindow)
    
public:
    virtual bool init();
    virtual void onPresented();
    
    void resetUI();
    void notifyActionMsg(CCObject* obj);
    
public:
    __assign HRichSprite* m_pBg;
    
};

#endif /* defined(__card2__HMainCityWindow__) */

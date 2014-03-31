//
//  HBattleController.h
//  card
//
//  Created by zhou gang on 13-5-21.
//
//

#ifndef __card__HBattleController__
#define __card__HBattleController__

class HBattleDelegate
{
public:
    virtual void onBattleEnded(int winner, CCDictionary* reward, CCDictionary* extReward) = 0;
};

class HBattleController : public CCObject {
    HSINGLETON_OBJECT(HBattleController);

    
public:
    void startBattle(CCDictionary* batSeq, bool isBoss);
    void startBattle(CCDictionary* batSeq, bool isBoss, HBattleDelegate* delegate);
    
    void startBattleEx(CCDictionary* batSeq, bool isBoss);
    
    HWindow* getBattleWnd() { return NULL; }
};

#endif /* defined(__card__HBattleController__) */

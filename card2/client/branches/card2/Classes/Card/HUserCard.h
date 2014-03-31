//
//  HUserCard.h
//  card
//
//  Created by zhou gang on 13-4-7.
//
//

#ifndef __card__HUserCard__
#define __card__HUserCard__

class HUserCard;
#include "./ConfigClass/HCard.h"

class HCardTouchedDelegate
{
public:
    virtual void touchedEvent(HUserCard* sender, int tag) = 0;
};

class HUserCard : public HUserObject
{
public:
    CC_SYNTHESIZE(const HCard*, m_keyCard, KeyCard);
    CC_SYNTHESIZE(int, m_hpGain, HpGain);
    CC_SYNTHESIZE(int, m_atkGain, AtkGain);
    CC_SYNTHESIZE(int, m_round, Round);
    CC_SYNTHESIZE(vector<int>, m_feature, Feature);

public:
    HUserCard();
    virtual ~HUserCard();
    
    virtual const HKey* getKeyObject(void);
    virtual void setKeyObject(const HKey* var);
    
    void addHpGain(int gain);
    void addAtkGain(int gain);
    
    int getHp();
    int getAttackPower();
    
    virtual int getOriginAtkPower();
    virtual int getOriginHp();
    
    int getUnlockedSkillCount();
    int getUnlockedfeature();

    int getLvupExp(int lv = -1);
    const char* getExpStr();
    float getExpPercentage();
    
    virtual void clearCard();
    
    virtual const char* getIcon();
    virtual const char* getRaceIcon();
    
    virtual void setUserObject(HUserObject* uobj);
    virtual HUserObject* getUserObject();
    virtual void updateUserObject();
    
    virtual void setUserCard(HUserCard* ucard);
    virtual HUserCard* getUserCard();
    virtual void updateUserCard();
    
    static const char* getIconLarge(int id);
    static const char* getIconMiddle(int id);
    static const char* getIconSmall(int id);
    
    static const char* getRaceLarge(int id);
    static const char* getRaceMiddle(int id);
    static const char* getRaceSmall(int id);
    
    static const char* getRaceLargeByIdx(int idx);
    
    static const char* getSkillIcon(int id);
    
    
public:
    CC_SYNTHESIZE(HCardTouchedDelegate*, m_tDelegate, TouchedDelegate);
    CC_SYNTHESIZE(int, m_tTag, TouchedTag);

};
        
class HUserCardObject : public HUserCard , public CCObject
{
public:
    HCREATE_FUNC(HUserCardObject);
    static HUserCardObject* create(int id, int level = 0);
};

class HUserBattleCard : public HUserCard {
    
public:
    HUserBattleCard();
    ~HUserBattleCard();
    
public:
    CC_PROPERTY(int, m_oriAttack, OriginAtkPower);
    CC_PROPERTY(int, m_oriHp, OriginHp);
    CC_PROPERTY(int, m_oriRound, Round);
    
    CC_SYNTHESIZE_BOOL(bool, m_bInBattle, InBattle);
    
    virtual void setUserCard(HUserCard* ucard);
    
    virtual void clearCard();
    
};

struct usercard_key_fun { int operator()(void* card) { return ((HUserCard*)card)->getUserId(); } };


#endif /* defined(__card__HUserCard__) */

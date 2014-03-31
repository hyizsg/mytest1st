//
//  HUserCard.cpp
//  card
//
//  Created by zhou gang on 13-4-7.
//
//

#include "../headers.h"

HUserCard::HUserCard()
: m_feature(3)
{
    m_userId = 0;
    m_keyCard = NULL;
    m_atkGain = 0;
    m_hpGain = 0;
    m_tTag = -1;
    m_round = -1;
    m_tDelegate = NULL;
    m_exp = 0;
    m_level = 0;
}

HUserCard::~HUserCard()
{
    
}


void HUserCard::setUserCard(HUserCard* ucard)
{
    if (ucard != NULL) {
        setKeyCard(ucard->getKeyCard());
        setLevel(ucard->getLevel());
        setUserId(ucard->getUserId());
        setExp(ucard->getExp());
        setFeature(ucard->m_feature);
    }else{
        setKeyCard(NULL);
    }
}

void HUserCard::updateUserCard()
{
    setUserCard(getUserCard());
}

HUserCard* HUserCard::getUserCard()
{
    return getCurrBag()->cardByUId(m_userId);
}

void HUserCard::setUserObject(HUserObject* uobj)
{
    CCAssert(!uobj || (uobj && dynamic_cast<HUserCard*>(uobj)) , "not a usercard");
    setUserCard(dynamic_cast<HUserCard*>(uobj));
}

HUserObject* HUserCard::getUserObject()
{
    return getUserCard();
}

void HUserCard::updateUserObject()
{
    updateUserCard();
}

int HUserCard::getAttackPower()
{
    return max(0, getOriginAtkPower() + m_atkGain);
}

int HUserCard::getHp()
{
    return max(0, getOriginHp() + m_hpGain);
    
}

int HUserCard::getOriginAtkPower()
{
    return max(0, m_keyCard->attack + m_keyCard->atk_acc * m_level + (m_feature[1] ? m_keyCard->awake[1]->args : 0));
}

int HUserCard::getOriginHp()
{
    return max(0, m_keyCard->hp + m_keyCard->hp_acc * m_level + (m_feature[0] ? m_keyCard->awake[0]->args : 0));
}

int HUserCard::getUnlockedSkillCount()
{
    return (m_level / 5) + 1 ;
}

int HUserCard::getUnlockedfeature()
{
    for (int i=0; i<3; i++) {
        if (m_feature[i] == 0) {
            return i;
        }
    }
    
    return 0;
}

const HKey* HUserCard::getKeyObject(void)
{
    return m_keyCard;
}

void HUserCard::setKeyObject(const HKey* var)
{
    CCAssert(!var || (var && dynamic_cast<const HCard*>(var)) , "not a key card");
    m_keyCard = dynamic_cast<const HCard*>(var);
}

int HUserCard::getLvupExp(int lv)
{
    if (lv == -1) {
        lv = m_level;
    }
    
    lv = clampf(lv, 0, getKeyCard()->level_max);
    
    return getStrongByCard(this, lv)->lup_exp;
}

const char* HUserCard::getExpStr()
{
    if (m_level < getKeyCard()->level_max) {
        return _T("%d/%d", m_exp, getLvupExp());
    }else{
        int exp = getLvupExp(getKeyCard()->level_max-1);
        return _T("%d/%d", exp, exp);
    }
}

float HUserCard::getExpPercentage()
{
    return m_level == getKeyCard()->level_max ? 100 : m_exp * 100.f / getLvupExp();
}

void HUserCard::addHpGain(int gain)
{
    m_hpGain += gain;
}

void HUserCard::addAtkGain(int gain)
{
    m_atkGain += gain;
}

void HUserCard::clearCard()
{
    setTouchedDelegate(NULL);
    setTouchedTag(-1);
    setKeyCard(NULL);
    setLevel(0);
    m_feature[0] = m_feature[1] = m_feature[2] = 0;
    m_atkGain = m_hpGain = 0;
}

const char* HUserCard::getIcon()
{
    return (m_keyCard->icon); //CCAssert(0, "must overorive it")
}

const char* HUserCard::getRaceIcon()
{
    return (_T("%d", getKeyCard()->race)); //CCAssert(0, "must overorive it")
}

//-----------------
const char* HUserCard::getIconLarge(int id)
{
    return _T("game/card/318_440/%s%s.jpg", getCardById(id)->icon, "_a");
}

const char* HUserCard::getIconMiddle(int id)
{
    return _T("game/card/120_166/%s%s.jpg", getCardById(id)->icon, "_b");
}

const char* HUserCard::getIconSmall(int id)
{
    return _T("game/card/120_120/%s%s.jpg", getCardById(id)->icon, "_c");
}

const char* HUserCard::getRaceLarge(int id)
{
    return _T("game/card/382_524/card_a_%d.png", getCardById(id)->race);
}

const char* HUserCard::getRaceMiddle(int id)
{
    return _T("card_b_%d.png", getCardById(id)->race);
}

const char* HUserCard::getRaceSmall(int id)
{
    return _T("card_c_%d.png", getCardById(id)->race);
}

const char* HUserCard::getSkillIcon(int id)
{
    return _T("game/skill/%s", getSkillById(id)->icon);
}

const char* HUserCard::getRaceLargeByIdx(int idx)
{
    return _T("game/card/382_524/card_a_%d.png", idx);
}

//----
HUserCardObject* HUserCardObject::create(int id, int level)
{
    HUserCardObject* card = new HUserCardObject;
    card->setKeyCard(getCardById(id));
    card->setLevel(level);
//    card->autorelease();
    CC_AUTO_RELEASE(card);
    return card;
    
}

//------------

HUserBattleCard::HUserBattleCard()
: HUserCard()
, m_bInBattle(false)
, m_oriAttack(0)
, m_oriHp(0)
{
    
}

HUserBattleCard::~HUserBattleCard()
{
    
}

int HUserBattleCard::getOriginHp()
{
    return m_bInBattle ? m_oriHp : HUserCard::getOriginHp();
}

void HUserBattleCard::setOriginHp(int var)
{
    m_oriHp = var;
}

int HUserBattleCard::getOriginAtkPower()
{
    return m_bInBattle ? m_oriAttack : HUserCard::getOriginAtkPower();
}

void HUserBattleCard::setOriginAtkPower(int var)
{
    m_oriAttack = var;
}

int HUserBattleCard::getRound()
{
    return m_bInBattle ? m_oriRound : HUserCard::getRound();
}

void HUserBattleCard::setRound(int var)
{
    (m_bInBattle ? m_oriRound : m_round) = var;
}

void HUserBattleCard::setUserCard(HUserCard* ucard)
{
    HUserCard::setUserCard(ucard);
    HUserBattleCard* bcard = dynamic_cast<HUserBattleCard*>(ucard);
    
    if (bcard) {
        m_bInBattle = bcard->m_bInBattle;
        m_oriAttack = bcard->m_oriAttack;
        m_oriHp = bcard->m_oriHp;
        m_oriRound = bcard->m_oriRound;
        m_atkGain = bcard->m_atkGain;
        m_hpGain = bcard->m_hpGain;
    }
}

void HUserBattleCard::clearCard()
{
    HUserCard::clearCard();
    
    m_bInBattle = false;
    m_oriAttack = 0;
    m_oriHp = 0;
    m_oriRound = 0;
    m_atkGain = 0;
    m_hpGain = 0;
}


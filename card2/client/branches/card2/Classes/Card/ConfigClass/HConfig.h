//
//  HConfig.h
//  card
//
//  Created by zhou gang on 13-6-5.
//
//

#ifndef __card__HConfig__
#define __card__HConfig__

#include "HCard.h"
#include "HSkill.h"
#include "HHero.h"
#include "HMagic.h"
#include "HBuff.h"
#include "HProp.h"
#include "HExchange.h"
#include "HCommodity.h"
#include "HMonster.h"
#include "HLevel.h"
#include "HHeaven.h"
#include "HTemple.h"
#include "HHeaven.h"
#include "HStrong.h"
#include "HSymbol.h"
#include "HPvp.h"
#include "HUpgrade.h"
#include "HChallenge.h"
#include "HNewbie.h"
#include "HAchieve.h"
#include "HActConfig.h"


typedef enum {
    MONEY_COIN = 1,
    MONEY_GOLD = 2,
    MONEY_STONE = 3,
    FRAG_UNI = 64,
} MoneyType;

static inline const HCard* getCardById(int id) {
    if (HCard::cards.find(id) != HCard::cards.end())
    {
        return HCard::cardById(id);
    }
    return NULL;
}

static inline const HHero* getHeroByLevel(int level){
    return HHero::heros[MIN(level, MAX_LEVEL)];
}

static inline int getLevelOfCardNum(int num){
    for (int i=1; ; i++) {
        if (HHero::heros[i]->card_num == num) {
            return i;
        }
    }
    return -1;
}

static inline int getLevelOfMagicNum(int num){
    for (int i=1; ; i++) {
        if (HHero::heros[i]->magic_num == num) {
            return i;
        }
    }
    return -1;
}

static inline const HLevel* getLevelById(int id) {
    return HLevel::levels.find(id) != HLevel::levels.end() ?  HLevel::levels[id] : NULL;
}

static inline const HMagic* getMagicById(int id, int level){
    CCAssert(HMagic::magics.find(id) != HMagic::magics.end(), "no magic id");
    return HMagic::magics[id][level];
}


static inline const HSkill* getSkillById(int id) {
    CCAssert(HSkill::skills.find(id) != HSkill::skills.end(), "no skill id");
    return HSkill::skillById(id);
}

static inline const HBuff* getBuffById(int id){
    return HBuff::buffs[id];
}

static const HProp* getPropById(int id){
    return HProp::props[id];
}

static inline const HStrong* getStrongById(int id)
{
    return HStrong::strongs[id];
}

static inline const HStrong* getStrongByCard(HUserCard* card, int level)
{
    return HStrong::strongs[(card->getKeyCard()->star_num << 8) | level << 4 | card->getKeyCard()->type];
}

static inline const HStrong* getStrongByCard(HUserCard* card)
{
    return HStrong::strongs[(card->getKeyCard()->star_num << 8) | card->getLevel() << 4 | card->getKeyCard()->type];
}

static inline const HStrong* getStrongByMagic(HUserMagic* magic, int level)
{
    return HStrong::strongs[(0x10 | magic->getKeyMagic()->star_num) << 8 | level << 4];
}

static inline const HStrong* getStrongByMagic(HUserMagic* magic)
{
    return HStrong::strongs[(0x10 | magic->getKeyMagic()->star_num) << 8 | magic->getLevel() << 4];
}

static inline const HExchange* getExchangeById(int id) {
    return HExchange::exchanges[id];
}

static inline const HCommodity* getCommodityById(int id){
    return HCommodity::getCommodityById(id);
}

static inline const HTemple* getTempleById(int id){
    return HTemple::temples[id];
}

static inline const HHeaven* getHeavenById(int id){
    return HHeaven::heavens[id];
}

static inline const HHeaven* getFirstHeavenAtTowerIndex(int towerIndex) {
    if (HHeaven::heavensList.find(towerIndex) != HHeaven::heavensList.end()) {
        return HHeaven::heavensList[towerIndex][0];
    }
    return NULL;
}

static inline const HHeaven* getLastHeavenAtTowerIndex(int towerIndex) {
    if (HHeaven::heavensList.find(towerIndex) != HHeaven::heavensList.end()) {
        return HHeaven::heavensList[towerIndex][HHeaven::heavensList[towerIndex].size()-1];
    }
    return NULL;
}

static inline const HSymbol* getSymbolById(int id, int level){
    return HSymbol::symbols[id][level];
}

static inline const HPvp* getPvpById(int id){
    return HPvp::pvps[id];
}

static inline const HFcPvp* getFcPvpById(int id){
    return HFcPvp::pvps[id];
}

static inline const HUpgrade* getUpgradeById(int id){
    if (HUpgrade::grades.find(id) != HUpgrade::grades.end())
        return HUpgrade::grades[id];
    return NULL;
}

static inline const HUgExchange* getUgExchangeId(int id, int idx){
    return HUgExchange::exchanges[id][idx];
}

static inline const vector<const HUgExchange*>& getUgExchangeId(int id){
    return HUgExchange::exchanges[id];
}

static inline const HMonster* getMonsterById(int id){
    return HMonster::monsters[id];
}

static inline const HChallenge* getChallengebyId(int id, int idx){
    return HChallenge::challenges[id][idx];
}

static inline const vector<const HChallenge*>& getChallengebyId(int id){
    return HChallenge::challenges[id];
}

static inline const vector<const HNewbie*>& getNewbieById(int id) {
    return HNewbie::newbies[id];
}

#endif /* defined(__card__HConfig__) */ 


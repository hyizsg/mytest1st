//
//  HBag.h
//  card
//
//  Created by zhou gang on 13-5-3.
//
//

#ifndef __card__HBag__
#define __card__HBag__

#include <map>
using namespace std;

//class HActiveInfo: public CCObject
//{
//public:
//    HActiveInfo();
//    virtual ~HActiveInfo();
//    CC_SYNTHESIZE(int, m_peach, Peach);
//    CC_SYNTHESIZE(int, m_treeLv, TreeLv);
//    CC_SYNTHESIZE(int, m_dailyNum, DailyNum);
//    
//    CCDictionary *getJson();
//};


class HPlayer;

class HUserBag : public CCObject {
    HSINGLETON_OBJECT(HUserBag);
    
public:
    typedef struct {
        int id;
        int level;
        int exp;
    } symbol;
    
    typedef map<int, HUserCard*> HUserCardMap;
    typedef map<int, HUserMagic*> HUserMagicMap;
    typedef map<int, int> HFragInfoMap;
    typedef map<int, symbol> HSymbolMap;    
    
public:
    
    HUserBag(HPlayer* player);
    
    CC_SYNTHESIZE(HPlayer*, m_player, Player);
    CC_SYNTHESIZE(int, m_gold, Gold);
    CC_SYNTHESIZE(int, m_coin, Coin);
    CC_SYNTHESIZE(int, m_stone, Stone);
    CC_SYNTHESIZE(int, m_active, Active);
    CC_SYNTHESIZE(int, m_maxActive, MaxActive);
    
    CC_SYNTHESIZE(int, m_activeWaitTime, ActiveWaitTime); //下次恢复一点的描述
    CC_SYNTHESIZE(int, m_actBuyNum, ActBuyNum); //活力购买次数
    CC_SYNTHESIZE(int, m_maxActBuyNum, MaxActBuyNum); //最大活力购买次数
    CC_SYNTHESIZE(int, m_actPrice, ActPrice); //活力购买价格
    CC_SYNTHESIZE(int, m_actNum, ActNum); //活力点数
    CC_SYNTHESIZE(int, m_buyGold, BuyGold); //累积充值元宝个数
    CC_SYNTHESIZE(int, m_nextGainTime, NextGainTime); //下次领取俸禄时间
    CC_SYNTHESIZE_BOOL(bool, m_isActiveBought, ActiveBought);
    CC_SYNTHESIZE(float, m_monsterAtkListDelta, MonsterAtkListDelta);
    CC_SYNTHESIZE(int, m_wbRid, WbRid);
    CC_SYNTHESIZE(int, m_wbRun, WbNum);
    
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(vector<HUserCard*>, m_allCardList, AllCardList)
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(HUserCardMap, m_allCardMap, AllCardMap);   // HUserCard
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(vector<vector<int> >, m_cardGroup, CardGroup); // HUserCard::user_id
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(vector<HUserMagic*>, m_allMagicList, AllMagicList)
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(HUserMagicMap, m_allMagicMap, AllMagicMap);   // HUserMagic
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(vector<vector<int> >, m_magicGroup, MagicGroup); // HUserMagic::user_id
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(HFragInfoMap, m_allFragMap, AllFragMap);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(HSymbolMap, m_symbolMap, AllSymbolMap);    
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(vector<int>,m_iapHasBuy, IapHasBuy);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(vector<int>,m_iapfirstreward, IapFirstReward);
    CC_SYNTHESIZE(int, m_iapFirstGot, IapFirstGot);
    
    CC_SYNTHESIZE(int, m_currGroupIndex, CurrGroupIndex);   // Index:0, 1, 2
    
    HUserCard* cardByIndex(int index);
    HUserCard* cardByUId(int id);
    HUserMagic* magicByUId(int id);
    
    
    vector<int> getCardsInGroup();
    vector<int> getCardsWithoutInGroup();
    vector<int> getCardsInCurrGroup();
    vector<int> getCardsWithoutInCurrGroup();
    
    vector<int> getMagicsInCurrGroup();
    vector<int> getMagicsWithoutInCurrGroup();
    vector<int> getMagicsInGroup();
    vector<int> getMagicsWithoutInGroup();
    
    void updateCurrCardGroup(const vector<int>& cards);
    void updateCurrCardGroup(const vector<HUserCard*>& cards);
    
    void updateCurrMagicGroup(const vector<int>& magics);
    void updateCurrMagicGroup(const vector<HUserMagic*>& magics);
    
    void AddIapItem(int itemid);
    void updateIapInfo(CCDictionary *dic);    
    bool CheckIapHasBuy(int itemid);
    bool CheckCommonHasBuy();
public:
    void dumpCachedTextureInfo();
    
    void updateCardList(const vector<HUserCard*> & card);
    void updateMagicList(const vector<HUserMagic*>& magic);
    
    void updateCardList(CCObject* cards);
    
    void updateCardGroup(CCArray* arr, int index);
    void updateMagicGroup(CCArray* arr, int index);
    
    void updateFragMap(CCArray* arr);
    int getFragNumByType(int type);
    
    void updateSymbolMap(CCArray* arr);
    const symbol* symbolById(int id);
    
    int getSymbolHp();
    int getSymbolAttack();
    
    int getSymbolAddedByType(int type);
    
    static void parseIntStr(CCString *str, vector<int> &vec);

protected:
    template <typename T>
    static void _resizeVectorByIndex(vector< vector<T> >& vec, int index);
    
    template <typename T, typename P, typename Func>
    static void _updateVectorByArr(vector<T> & vec, P* begin, int count, Func fun);
    
    template <typename T1, typename T2, typename P, typename FuncKey, typename FuncValue>
    static void _updateMapByArr(map<T1, T2> & tmap, P* begin, int count, FuncKey funKey, FuncValue funValue);
    
    
protected:

    friend class HPlayer;
    char m_strBuff[128];
    
public:
    CCTexture2D* textureWithName(const char* name);
    void removeAllTexture();
    
    const char* getDefaultIcon(const char* icon);
    
};

extern const char* num2cn(int n);

static inline void testnum2cn()
{
    num2cn(2);
}

static inline HUserBag* getCurrBag()
{
    return HUserBag::getInstance();
}

static const char* getDefaultIcon(const char* icon)
{
    return getCurrBag()->getDefaultIcon(icon);
}

static const char* path2key(const char* path)
{
    const char* key = strrchr(path, '/');
    return key ? key+1 : path;
}

struct compare_card_base{
    virtual bool operator ()(int, int) = 0;
};

struct compare_card_uid  {
    bool operator ()(int a, int b){ return a < b; }
};

struct compare_card_att
{
    HUserBag* _bag;
    compare_card_att(HUserBag* bag = getCurrBag()) : _bag(bag) {}
    
    bool operator ()(int a, int b)
    {
        int at1 = _bag->cardByUId(a)->getAttackPower();
        int at2 = _bag->cardByUId(b)->getAttackPower();
        return at1 != at2 ? at1 < at2 : a < b;
    }
};

struct compare_card_hp
{
    HUserBag* _bag;
    compare_card_hp(HUserBag* bag = getCurrBag()) : _bag(bag) {}
    
    bool operator ()(int a, int b)
    {
        int h1 = _bag->cardByUId(a)->getHp();
        int h2 = _bag->cardByUId(b)->getHp();
        return h1 != h2 ? h1 < h2 : a < b;
    }
};

struct compare_card_leader
{
    HUserBag* _bag;
    compare_card_leader(HUserBag* bag = getCurrBag()) : _bag(bag) {}
    
    bool operator ()(int a, int b)
    {
        int ld1 = _bag->cardByUId(a)->getKeyCard()->leaded;
        int ld2 = _bag->cardByUId(b)->getKeyCard()->leaded;
        return ld1 != ld2 ? ld1 < ld2 : a < b;
    }
};
        
struct compare_card_level
{
    HUserBag* _bag;
    compare_card_level(HUserBag* bag = getCurrBag()) : _bag(bag) {}
    
    bool operator ()(int a, int b)
    {
        int lv1 = _bag->cardByUId(a)->getLevel();
        int lv2 = _bag->cardByUId(b)->getLevel();
        return lv1 != lv2 ? lv1 < lv2 : a < b;
    }
};

/// ------
struct compare_card_kid
{
    HUserBag* _bag;
    compare_card_kid(HUserBag* bag = getCurrBag()) : _bag(bag) {}
    
    bool operator ()(int a, int b)
    {
        return operator()(a, b, _bag);
    }
    
    bool operator ()(int a, int b, HUserBag* bag)
    {
        int id1 = bag->cardByUId(a)->getKeyCard()->id;
        int id2 = bag->cardByUId(b)->getKeyCard()->id;
        return id1 != id2 ? id1 < id2 : a < b;
    }
};

struct compare_card_kid_obj
{
    static compare_card_kid cmp_kid;
};

struct compare_card_att_k
{
    HUserBag* _bag;
    compare_card_att_k(HUserBag* bag = getCurrBag()) : _bag(bag) {}
    
    bool operator ()(int a, int b)
    {
        int at1 = _bag->cardByUId(a)->getAttackPower();
        int at2 = _bag->cardByUId(b)->getAttackPower();
        return at1 != at2 ? at1 < at2 : compare_card_kid_obj::cmp_kid(a, b, _bag);
    }
};

struct compare_card_hp_k
{
    HUserBag* _bag;
    compare_card_hp_k(HUserBag* bag = getCurrBag()) : _bag(bag) {}
    
    bool operator ()(int a, int b)
    {
        int h1 = _bag->cardByUId(a)->getHp();
        int h2 = _bag->cardByUId(b)->getHp();
        return h1 != h2 ? h1 < h2 : compare_card_kid_obj::cmp_kid(a, b, _bag);
    }
};

struct compare_card_leader_k : public compare_card_kid_obj
{
    HUserBag* _bag;
    compare_card_leader_k(HUserBag* bag = getCurrBag()) : _bag(bag) {}
    
    bool operator ()(int a, int b)
    {
        int ld1 = _bag->cardByUId(a)->getKeyCard()->leaded;
        int ld2 = _bag->cardByUId(b)->getKeyCard()->leaded;
        return ld1 != ld2 ? ld1 < ld2 : compare_card_kid_obj::cmp_kid(a, b, _bag);
    }
};

struct compare_card_level_k
{
    HUserBag* _bag;
    compare_card_level_k(HUserBag* bag = getCurrBag()) : _bag(bag) {}
    
    bool operator ()(int a, int b)
    {
        int lv1 = _bag->cardByUId(a)->getLevel();
        int lv2 = _bag->cardByUId(b)->getLevel();
        return lv1 != lv2 ? lv1 < lv2 : compare_card_kid_obj::cmp_kid(a, b, _bag);
    }
};

#endif /* defined(__card__HBag__) */

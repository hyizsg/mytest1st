//
//  HPlayer.cpp
//  card
//
//  Created by zhou gang on 13-4-7.
//
//


#include "../headers.h"

HPlayer* HPlayer::s_player = NULL;

HPlayer* HPlayer::currPlayer()
{
    if (s_player == NULL) {
        s_player = new HPlayer;
        s_player->setBag(getCurrBag());
        s_player->getBag()->setPlayer(s_player);
        
        s_player->setMap(getCurrMap());
        s_player->getMap()->setPlayer(s_player);
    }
    return s_player;
}

void HPlayer::pureCurPlayer()
{
    CC_SAFE_RELEASE_NULL(s_player);
}

HPlayer::HPlayer()
{
    m_iconId = NULL;
    m_userBag = NULL;
    m_userMap = NULL;
    m_level = 0;
    m_exp = 0;
    m_hp = 0;
    m_leader = 0;
    m_userId = 0;
    m_userData = NULL;
    m_registInfo = NULL;
    m_vip = 0;
    m_rename = 0;
    m_rewardNum = 0;
    m_maxMailID = 0;
    m_cardChange = 0;
    m_magicChange = 0;
    m_dailyGet = 0;
    m_oriIconId = 0;
    m_MaxCard = m_MaxMagic = 0;
    m_serverId = 0;
    m_serverName = NULL;
    m_userData = NULL;
}

HPlayer::~HPlayer()
{
    CC_SAFE_RELEASE_NULL(m_userBag);
    CC_SAFE_RELEASE_NULL(m_userData);
    CC_SAFE_RELEASE_NULL(m_serverName);
}

HPlayer* HPlayer::createWithBag()
{
    HPlayer* play = new HPlayer;
    HUserBag* bag = new HUserBag(play);
    
//    bag->autorelease();
//    play->autorelease();
    
    CC_AUTO_RELEASE(bag);
    CC_AUTO_RELEASE(play);
    
    return play;
}

const char* HPlayer::getIcon() const
{
    return getIcon(m_iconId);
}

const char* HPlayer::getIcon(int id)
{
    if (getCardById(id) == NULL){
        id = id <= 0 ? getCurrPlayer()->getOriIconId() : id;
        if (id <= 0)
            id = 6006;
        return _T("game/card/120_120/%04d%s.jpg", id, "_c");
    }else{
        return HUserCard::getIconSmall(id);
    }
}

int HPlayer::getLeader()
{
    return m_leader == 0 ? getHeroByLevel(m_level)->lead_power : m_leader;
}

void HPlayer::setLeader(int var)
{
    m_leader = var;
}

const char* HPlayer::getName() const
{
    return m_name.length() == 0 ? getCurrPlayer()->m_name.c_str() : m_name.c_str();
}

void HPlayer::setName(const char* name)
{
    m_name = name;
}

int HPlayer::getLvupExp()
{
    return getHeroByLevel(m_level+1)->exp;
}

const char* HPlayer::getExpStr()
{
    return _T("%d/%d", m_exp, getLvupExp());
}

float HPlayer::getExpPercentage()
{
    return m_exp * 100.f / getLvupExp();
}

void HPlayer::setData(CCObject* data, const char* key)
{
    if (m_userData == NULL) {
        m_userData = new CCDictionary;
    }
    m_userData->setObject(data, key);
}

CCObject* HPlayer::dataForKey(const char* key)
{
    if (!m_userData) {
        return NULL;
    }
    
    return m_userData->objectForKey(key);
}

int HPlayer::intForKey(const char *key)
{
    if (!m_userData) {
        return 0;
    }
    
    CCObject* data = m_userData->objectForKey(key);
    if (dynamic_cast<CCString*>(data)) {
        return ((CCString*)data)->intValue();
    }else if(dynamic_cast<CCInteger*>(data)){
        return ((CCInteger*)data)->getValue();
    }
    return 0;
}

const char* HPlayer::strForKey(const char* key)
{
    if (!m_userData) {
        return "";
    }
    
    return dynamic_cast<CCString*>(m_userData->objectForKey(key))->getCString();
}

void HPlayer::removeDataForKey(const char* key)
{
    CCAssert(m_userData, "");
    m_userData->removeObjectForKey(key);
}

void HPlayer::clearData()
{
    CCAssert(m_userData, "");
    m_userData->removeAllObjects();
}

HPlayer* HPlayer::careateTmpPlayer()
{
    s_player = getCurrPlayer();
    s_player->m_name = ("HR00001");
    
    srand((int)time(NULL));
    HUserBag* bag = getCurrBag();
    
    FORUP(i, 20) {
        HUserCard* card = new HUserCardObject();
        int tmpid = 1001 + i;//(rand() % 4 + 1 ) * 1000 + rand() % 20 + 1 ;
        card->setKeyCard(getCardById(tmpid));
        card->setLevel(rand() % 10 + 1);
        card->setExp(rand() % 1000);
        card->setUserId(10100 + i);
        bag->m_allCardList.push_back(card);
        bag->m_allCardMap[card->getUserId()] = (card);
    }
    
    FORUP(i, 10) {
        HUserMagic* magic = new HUserMagicObject(); //10705
        int tmpid = (rand() % 5 + 1) * 10000 + (rand() % 8 + 1) * 100 + (rand() % 2) + 1;
        magic->setLevel(rand() % 5 + 1);
        magic->setKeyMagic(getMagicById(tmpid, magic->getLevel()));
        magic->setExp(rand() % 1000);
        magic->setUserId(10100 + i);
        bag->m_allMagicList.push_back(magic);
        bag->m_allMagicMap[magic->getUserId()] = magic;
    }
    
    bag->m_cardGroup.push_back(vector<int>());
    bag->m_magicGroup.push_back(vector<int>());
    bag->m_cardGroup[0].push_back(bag->m_allCardList[0]->getUserId());
    bag->m_cardGroup[0].push_back(bag->m_allCardList[1]->getUserId());
    bag->m_cardGroup[0].push_back(bag->m_allCardList[2]->getUserId());
    bag->m_magicGroup[0].push_back(bag->m_allMagicList[0]->getUserId());
    
    bag->m_cardGroup.push_back(vector<int>());
    bag->m_magicGroup.push_back(vector<int>());
    bag->m_cardGroup[1].push_back(bag->m_allCardList[3]->getUserId());
    bag->m_cardGroup[1].push_back(bag->m_allCardList[4]->getUserId());
    bag->m_cardGroup[1].push_back(bag->m_allCardList[5]->getUserId());
    
    bag->m_currGroupIndex = 0;
    
    bag->m_gold = rand() % 1000;
    bag->m_coin = rand() % 10000;

    s_player->m_level = rand() % 10 + 1;
    s_player->m_exp = rand() % 1000;
    s_player->m_hp = getHeroByLevel(s_player->m_level)->hp;
    s_player->m_iconId = 1001;
    
    
    return s_player;
}

const char *HPlayer::getInviteCode(int uid)
{
    char buff[50] = {0};
    int pos = 0;
    int j=0;
    while(uid > 0)
    {
        j = uid % 36;
        
        if (j>=10)
        {
            buff[pos] = 'A' + (j-10);
        }
        else {
            buff[pos] = '0' + j;
        }
        
        uid = uid / 36;
        pos++;
    }
    buff[pos] = '\0';
    
    for(int i=0;i<pos/2;i++)
    {
        char temp = buff[i];
        buff[i] = buff[pos-1-i];
        buff[pos-1-i] = temp;
    }
    return HString::create(buff)->getCString();
}

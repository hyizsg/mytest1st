//
//  HPlayer.h
//  card
//
//  Created by zhou gang on 13-4-7.
//
//

#ifndef __card__HPlayer__
#define __card__HPlayer__

class HRegistInfo : public CCObject {
    
public:
    CC_SYNTHESIZE_RETAIN(CCString*, m_userName, UserName);
    CC_SYNTHESIZE_RETAIN(CCString*, m_password, Password);
    CC_SYNTHESIZE_RETAIN(CCString*, m_email, Email);
    CC_SYNTHESIZE_RETAIN(CCString*, m_deviceId, DeviceID);
    CC_SYNTHESIZE_RETAIN(CCString*, m_regionId, RegionID);
    CC_SYNTHESIZE_RETAIN(CCString*, m_invitedBy, InvitedBy);    
    
    HRegistInfo(): m_userName(NULL), m_password(NULL), m_email(NULL), m_deviceId(NULL), m_regionId(NULL), m_invitedBy(NULL){}
    ~HRegistInfo() {
        CC_SAFE_RELEASE_NULL(m_userName);
        CC_SAFE_RELEASE_NULL(m_password);
        CC_SAFE_RELEASE_NULL(m_email);
        CC_SAFE_RELEASE_NULL(m_deviceId);
        CC_SAFE_RELEASE_NULL(m_regionId);
        CC_SAFE_RELEASE_NULL(m_invitedBy);
    }
    
    HCREATE_FUNC(HRegistInfo);

};



class HPlayer : public CCObject
{
public:
    CC_SYNTHESIZE(int, m_userId, UserID);
    CC_SYNTHESIZE(int, m_iconId, IconID);
    CC_SYNTHESIZE(int, m_oriIconId, OriIconId);
    CC_SYNTHESIZE(int, m_status, Status);
    CC_SYNTHESIZE(int, m_serverId, ServerID);
    
    CC_SYNTHESIZE(int, m_level, Level);
    CC_SYNTHESIZE(int, m_hp, HP);
    CC_SYNTHESIZE(int, m_exp, Exp);
    CC_SYNTHESIZE(int, m_vip, VIP);
    CC_SYNTHESIZE(int, m_rename, HasRename);
    CC_SYNTHESIZE(int, m_rewardNum, RewardNum);
    CC_SYNTHESIZE(int, m_maxMailID, MaxMailID);
    
    CC_SYNTHESIZE(int, m_cardChange, CardChange);
    CC_SYNTHESIZE(int, m_magicChange, MagicChange);
    CC_SYNTHESIZE(int, m_dailyGet, HasDailyGet);
    
    CC_SYNTHESIZE(int, m_ldrank, LdRank);
    CC_SYNTHESIZE(int, m_ldLayer, LDLayer);
    CC_SYNTHESIZE(int, m_MaxCard, MaxCard);
    CC_SYNTHESIZE(int, m_MaxMagic, MaxMagic);
    
    CC_PROPERTY(int, m_leader, Leader);
    
    const char* getName() const;
    void setName(const char* name);

    
    CC_SYNTHESIZE_RETAIN(CCDictionary*, m_userData, UserData);
    CC_SYNTHESIZE_RETAIN(HUserBag*, m_userBag, Bag);
    CC_SYNTHESIZE_RETAIN(HUserMap*, m_userMap, Map);
    CC_SYNTHESIZE_RETAIN(HRegistInfo*, m_registInfo, RegistInfo);
    CC_SYNTHESIZE_RETAIN(CCString*, m_serverName, ServerName);
    
    
    HPlayer();
    virtual ~HPlayer();
    
    static HPlayer* createWithBag();
    
    const char* getIcon() const;
    
    int getLvupExp();
    const char* getExpStr();
    float getExpPercentage();
    
    void setData(CCObject* data, const char* key);
    CCObject* dataForKey(const char* key);
    int intForKey(const char* key);
    const char* strForKey(const char* key);
    
    template<class T>
    T dataForKey(const char* key) { return (T) m_userData->objectForKey(key); }
    
    void removeDataForKey(const char* key);
    void clearData();

    static HPlayer* currPlayer();
    static void pureCurPlayer();
    static HPlayer* careateTmpPlayer();
    
    static const char* getIcon(int id);
    static const char* getInviteCode(int uid);
    
protected:
    static HPlayer* s_player;
    string m_name;
    
};

static inline HPlayer* getCurrPlayer()
{
    return HPlayer::currPlayer();
}


#define tParseReplayPlayer(player, pl)   \
    (player)->setUserID(PARSE_INT(pl, "UID"));       \
    (player)->setName(PARSE_STR(pl, "Name")->getCString());        \
    (player)->setIconID(PARSE_INT(pl, "Avatar"));        \
    (player)->setLevel(PARSE_INT(pl, "Level"));


#endif /* defined(__card__HPlayer__) */

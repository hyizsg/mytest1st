//
//  HActConfig.h
//  card
//
//  Created by bo wei on 13-7-16.
//
//

#ifndef __card__HActConfig__
#define __card__HActConfig__

#define MAX_VIP_FUNCTIONS 13

class HVipConfig {
public:
    int level;
    int requireGold;
    int functions[MAX_VIP_FUNCTIONS];
    int gold;
    int money;
    int stone;
    int itemid;
    int itemcount;
    
    HVipConfig();

public:
    class HVipDescConfig {
    public:
        int functionid;
        const char *desc;
        int paramType;        
    };
    
public:
    static vector<string> strings;
    
    static map<int, const HVipDescConfig*> vipDescMap;
    
    static map<int, const HVipConfig*> vipmap;
    static int maxVipLevel;
    static vector<const HVipConfig*> vipList;
    
    static const char *getVipFunDesc(int viplevel);
    static const HVipConfig *getConfig(int viplevel);
	static int load();
};

class HFriendRewardConfig {
public:
    int id;    
    int rewardID;
    int rewardCount;
    int friendCount;
    int friendLevel;
    int hasreceived;
    const char *desc;

public:
    static vector<string> strings;
    static vector<HFriendRewardConfig*> rewardList;
    
	static int load();
};

class HCheckInConfig {
    
public:
    int day;
    int rewardid;
    int rewardcount;    
    
public:
    static vector<string> strings;
    static vector<HCheckInConfig*> checkinList;
    static CCString *jsonData;
    
	static int load();
    static void updateConfig(CCDictionary *dic);
    static const char *getJsonData();
};


#endif /* defined(__card__HActConfig__) */

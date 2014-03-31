//
//  HActConfig.cpp
//  card
//
//  Created by bo wei on 13-7-16.
//
//

#include "headers.h"
#include "base.h"


vector<string> HVipConfig::strings;
vector<const HVipConfig*> HVipConfig::vipList;
map<int, const HVipConfig*> HVipConfig::vipmap;
map<int, const HVipConfig::HVipDescConfig*> HVipConfig::vipDescMap;
int HVipConfig::maxVipLevel = 0;

HVipConfig::HVipConfig()
{
    level = 0;
    requireGold = 0;
    for (int i=0;i<MAX_VIP_FUNCTIONS;i++)
        functions[i] = 0;
    gold = 0;
    money = 0;
    stone = 0;
    itemid = 0;
    itemcount = 0;
}

const HVipConfig* HVipConfig::getConfig(int viplevel)
{
    if ((viplevel <= 0) || (viplevel > maxVipLevel))
        return NULL;
    return vipmap[viplevel];
}

const char *HVipConfig::getVipFunDesc(int viplevel)
{
    static char buff[3000] = {0};
    memset(buff, 0, sizeof(buff));
    char *ptr = buff;
    if ((viplevel <= 0) || (viplevel > maxVipLevel))
        return ptr;
    
    const HVipConfig *vip1 = vipmap[viplevel];
    const HVipConfig *vip0 = vipmap[viplevel-1];
    
    int startindex = 1;
    for(int i=0;i<MAX_VIP_FUNCTIONS;i++)
    {
        if (vip1->functions[i] == 0)
            continue;
        int delta = vip1->functions[i] - vip0->functions[i];
        if (delta<=0)
            continue;
        const HVipDescConfig *descconfig = vipDescMap[i+1];
        if (startindex != 1)
        {
            ptr += sprintf(ptr, "\n");
        }
        ptr += sprintf(ptr, "%d.", startindex);
        //if ((i==1) || (i==2) || (i==9)) {
            ptr += sprintf(ptr, descconfig->desc, vip1->functions[i]);
        //} else {
        //    ptr += sprintf(ptr, descconfig->desc, delta);
        //}
        
        startindex++;
    }    
    
    return buff;
}

int HVipConfig::load()
{
    LOAD_STRING("config/VIP_base.txt");
    
    vipmap.clear();
    vipList.clear();    
    
    HVipConfig* gd0 = new HVipConfig;
    gd0->level = 0;
    vipmap[gd0->level] = gd0;
    
    for (int i=0; i<strings.size();) {
        HVipConfig* gd = new HVipConfig;
        gd->level = atoi(strings[i++].c_str());
        gd->requireGold = atoi(strings[i++].c_str());
        for(int j=0;j<MAX_VIP_FUNCTIONS;j++) {
            gd->functions[j] = atoi(strings[i++].c_str());
        }
        gd->gold = atoi(strings[i++].c_str());
        gd->money = atoi(strings[i++].c_str());
        gd->stone = atoi(strings[i++].c_str());        
    
        vector<char*> pl = split((char*)(strings[i++].c_str()), ";");
        if (pl.size() >= 2) {
            gd->itemid = atoi(pl[0]);
            gd->itemcount = atoi(pl[1]);
        } else {
            gd->itemid = 0;
            gd->itemcount = 0;
        }
        maxVipLevel = gd->level;
        vipList.push_back(gd);
        vipmap[gd->level] = gd;
    }

    strings.clear();
    vipDescMap.clear();
    LOAD_STRING("config/VIP_other.txt");
    for (int i=0; i<strings.size();) {
        HVipDescConfig* gd = new HVipDescConfig;
        gd->functionid = atoi(strings[i++].c_str());
        gd->desc = strings[i++].c_str();
        gd->paramType = atoi(strings[i++].c_str());
        vipDescMap[gd->functionid] = gd;
    }
    
    return vipList.size();
}

vector<string> HFriendRewardConfig::strings;
vector<HFriendRewardConfig*> HFriendRewardConfig::rewardList;

int HFriendRewardConfig::load()
{   
    LOAD_STRING("config/invite.txt");
    
    rewardList.clear();
    
    for (int i=0; i<strings.size();) {
        HFriendRewardConfig* gd = new HFriendRewardConfig;
        gd->id = atoi(strings[i++].c_str());
        gd->desc = strings[i++].c_str();
        gd->friendCount = atoi(strings[i++].c_str());
        gd->friendLevel = atoi(strings[i++].c_str());
        gd->rewardCount = atoi(strings[i++].c_str());
        gd->rewardID = 3;
        vector<char*> pl = split((char*)(strings[i++].c_str()), ";");
        if (pl.size() >= 2) {
            gd->rewardID = atoi(pl[0]);
            gd->rewardCount = atoi(pl[1]);
        }
        
        gd->hasreceived = 0;
        rewardList.push_back(gd);
    }
    
    return rewardList.size();
}


vector<string> HCheckInConfig::strings;
vector<HCheckInConfig*> HCheckInConfig::checkinList;
CCString* HCheckInConfig::jsonData = NULL;

int HCheckInConfig::load()
{
    return 0;
    LOAD_STRING("config/Daily.txt");
 
    return 0;
    checkinList.clear();
    
    for (int i=0; i<strings.size();) {
        HCheckInConfig* gd = new HCheckInConfig;
        gd->day = atoi(strings[i++].c_str());
        gd->rewardid = atoi(strings[i++].c_str());
        gd->rewardcount = atoi(strings[i++].c_str());
        checkinList.push_back(gd);
    }
    
    return 0;
}

const char *HCheckInConfig::getJsonData()
{
    if (jsonData == NULL)
    {
        CCDictionary *dic = CCDictionary::create();
        CCArray *arr = CCArray::create();
        for(int i=0;i<checkinList.size();i++)
        {
            HCheckInConfig *config = checkinList[i];
            CCDictionary* dicitem = CCDictionary::create();
            dicitem->setObject(HString::createWithInteger(config->day), "Day");
            dicitem->setObject(HString::createWithInteger(config->rewardid), "ID");
            dicitem->setObject(HString::createWithInteger(config->rewardcount), "Count");
            arr->addObject(dicitem);
        }
        dic->setObject(arr, "Config");
        jsonData = CCString::create(haypi::dictionaryToJSON(dic));
        jsonData->retain();
    }
    return jsonData->getCString();
}


void HCheckInConfig::updateConfig(cocos2d::CCDictionary *dic)
{
    if (dic == NULL)
        return;
    CCArray* data = PARSE_ARR(dic, "Daily");
    if (data == NULL)
        return;
    if (data->count() % 3 != 0)
        return;
    
    checkinList.clear();
    for(int i=0;i<data->count();i+=3)
    {
        int day = ((CCString*)(data->objectAtIndex(i)))->intValue();
        int id = ((CCString*)(data->objectAtIndex(i+1)))->intValue();
        int count = ((CCString*)(data->objectAtIndex(i+2)))->intValue();
        
        HCheckInConfig* gd = new HCheckInConfig;
        gd->day = day;
        gd->rewardid = id;
        gd->rewardcount = count;
        checkinList.push_back(gd);       
    }
}

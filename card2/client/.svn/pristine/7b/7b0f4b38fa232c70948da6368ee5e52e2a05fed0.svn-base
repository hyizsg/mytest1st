//
//  HGameConfig.cpp
//  card
//
//  Created by bo wei on 13-7-6.
//
//

#include "HGameConfig.h"
#include <time.h>


HSINGLETON_OBJECT_IMP(HGameConfig);

int HGameConfig::Uni4 = 10;
int HGameConfig::Uni5 = 10;
float HGameConfig::GhostListRefreshSecond = 5;

HGameConfig::HGameConfig()
{
    
}

HGameConfig::~HGameConfig()
{
}

int HGameConfig::getFragUniCount(int itemid)
{
    int star = HGameConfig::getItemStar(itemid);
    if (star == 4)
        return Uni4;
    if (star == 5)
        return Uni5;
    return 10;
}

// type <==> id
CardItemType HGameConfig::getItemType(int type)
{
    if (type < 1000)
        return CARDITEM_PROP;
    if ((type >= 1000) && (type < 9000))
        return CARDITEM_CARD;
    if ((type>=9000) && (type < 10000))
    {
        return CARDITEM_MAGIC;
    }
    
    type = type / 10;
    if ((type >= 1000) && (type < 9000)){
        if (type == 5999) {
            return CARDITEM_PROP;
        }else{
            return CARDITEM_CARDFRAG;
        }
    }
    if ((type>=9000) && (type < 10000))
    {
        return CARDITEM_MAGIC;
    }
    return CARDITEM_NONE;
}

int HGameConfig::getItemStar(int type)
{
    CardItemType itemtype = HGameConfig::getItemType(type);
    int star = 0;
    switch (itemtype) {        
        case CARDITEM_CARDFRAG:
        {
            type = type / 10;
            const HCard *card = getCardById(type);
            star = card->star_num;
        }
            break;
        case CARDITEM_MAGICFRAG:
        {
            type = type / 10;
            const HMagic* item = getMagicById(type, 0);
            star = item->star_num;
        }
            break;
        case CARDITEM_CARD:
        {
            const HCard *card = getCardById(type);
            star = card ? card->star_num : 0;
        }
            break;
        case CARDITEM_MAGIC:
        {
            const HMagic* item = getMagicById(type, 0);
            star = item->star_num;
        }
            break;
        default:
            break;
    }
    return star;
}

const char *HGameConfig::getItemIconLarge(int type)
{
    CardItemType itemtype = HGameConfig::getItemType(type);
    switch (itemtype) {
        case CARDITEM_NONE:
            return NULL;
        case CARDITEM_PROP:
        {
            return NULL;
        }
            break;
        case CARDITEM_CARDFRAG:
        {
            type = type / 10;
            return HUserCard::getIconLarge(type);
        }
            break;
        case CARDITEM_MAGICFRAG:
        {
            type = type / 10;
            return HUserMagic::getIconLarge(type);
        }
            break;
        case CARDITEM_CARD:
        {
            return HUserCard::getIconLarge(type);
        }
            break;
        case CARDITEM_MAGIC:
        {
            return HUserMagic::getIconLarge(type);
        }
            break;
        default:
            break;
    }
    return NULL;
}

// type <==> id
const char * HGameConfig::getItemIcon(int type)
{
    CardItemType itemtype = HGameConfig::getItemType(type);
    switch (itemtype) {
        case CARDITEM_NONE:
            return "";
        case CARDITEM_PROP:
            {
                const HProp *prop = HProp::getProp(type);
                return prop ? prop->icon : "";
            }
            break;
        case CARDITEM_CARDFRAG:
            {
                type = type / 10;
                return HUserCard::getIconSmall(type);
            }
            break;
        case CARDITEM_MAGICFRAG:
            {
                type = type / 10;
                return HUserMagic::getIconSmall(type);                
            }
            break;
        case CARDITEM_CARD:
            {
                if (type == 6006 || type == 6007) {
                    return HPlayer::getIcon(type);
                }else{
                    return HUserCard::getIconSmall(type);
                }
            }
            break;
        case CARDITEM_MAGIC:
            {
                return HUserMagic::getIconSmall(type);
            }
            break;           
        default:
            break;
    }
    return "";
}

int HGameConfig::getMaxLevel(int type)
{
    int level = 0;
    CardItemType itemtype = HGameConfig::getItemType(type);
    switch (itemtype) {
        case CARDITEM_CARDFRAG:
        {
            type = type / 10;
            const HCard *card = getCardById(type);
            level = card->level_max;
        }
            break;
        case CARDITEM_MAGICFRAG:
        {
            type = type / 10;
            const HMagic* item = getMagicById(type, 0);
            level = item->level_max;
        }
            break;
        case CARDITEM_CARD:
        {
            const HCard *card = getCardById(type);
            level = card->level_max;
        }
            break;
        case CARDITEM_MAGIC:
        {
            const HMagic* item = getMagicById(type, 0);
            level = item->level_max;
        }
            break;
        default:
            break;
    }
    return level;
}



int HGameConfig::getRaceID(int type)
{
    CardItemType itemtype = HGameConfig::getItemType(type);
    int race = 1;
    switch (itemtype) {
        case CARDITEM_CARDFRAG:
        {
            type = type / 10;
            const HCard *card = getCardById(type);
            race = card->race;
        }
            break;
        case CARDITEM_MAGICFRAG:
        {
            type = type / 10;
            const HMagic* item = getMagicById(type, 0);
            race = item->race;
        }
            break;
        case CARDITEM_CARD:
        {
            const HCard *card = getCardById(type);
            race = card ? card->race : race;
        }
            break;
        case CARDITEM_MAGIC:
        {
            const HMagic* item = getMagicById(type, 0);
            race = item->race;
        }
            break;
        default:
            break;
    }
    return race;
}

const char *HGameConfig::getRaceIconLarge(int id)
{
    int race = getRaceID(id);
    if (race < 0)
    {
        return "game/card/382_524/card_a_1.png";
        return NULL;
    }
    return _T("game/card/382_524/card_a_%d.png", race);
}

const char *HGameConfig::getRaceIcon(int type)
{
    int race = getRaceID(type);
    if (race < 0)
    {
        return "card_c_1.png";
        return NULL;
    }
    return _T("card_c_%d.png", race);
}

// type <==> id
const char * HGameConfig::getItemName(int type)
{
    CardItemType itemtype = HGameConfig::getItemType(type);
    const char* name = NULL;
    switch (itemtype) {
        case CARDITEM_NONE:
            break;
        case CARDITEM_PROP:
        case CARDITEM_CARDFRAG:
        case CARDITEM_MAGICFRAG:
            {
                const HProp *prop = HProp::getProp(type);
                name = (prop!=NULL)?prop->name:"";
            }
            break;
        case CARDITEM_CARD:
        {
            if (type == 6006 || type == 6007) {
                return ccLocalizedString("HCOM_DEFAULT_AVATAR");
            }else{
                const HCard* card = getCardById(type);
                name = (card!=NULL)?card->name:"";
            }
        }
            break;
        case CARDITEM_MAGIC:
        {
            const HMagic *magic = getMagicById(type, 0);
            name = (magic!=NULL)?magic->name:"";
        }
            break;
        default:
            break;
    }
    //CCLOG("------ getItemName: %d\t%s-------------", type, name);
    
    return name;
}

const char *HGameConfig::getKeyString(int type)
{
    const char *key = "";
    switch (type) {
        case CONFIG_MUSICBACK:
            key = "backMusic";
            return key;
            break;
        case CONFIG_MUSIC:
            key = "music";
            return key;
            break;
        case CONFIG_AUTO:
            key = "auto";
            break;
        case CONFIG_MAILMAX:
            key = "maxMaile";
            break;
        default:
            key = itoa(type);
            break;
    }
    int uid = HPlayer::currPlayer()->getUserID();
    return _T("m%d_%s", uid, key);
}

const char *HGameConfig::getKeyDefault(int type)
{
    switch (type) {
        case CONFIG_MUSICBACK:            
        case CONFIG_MUSIC:            
        case CONFIG_AUTO:
            return "1";
        case CONFIG_MAILMAX:
            return "0";
        default:
            break;
    }
    return "";
}

void HGameConfig::setConfig(int type, int value)
{
    setConfig(type, itoa(value));
}

void HGameConfig::setConfig(int type, const char *value)
{
    CCUserDefault::sharedUserDefault()->setStringForKey(getKeyString(type), value);
    CCUserDefault::sharedUserDefault()->flush(); 
}

const char *HGameConfig::getStrValue(int type)
{
    const char *defaultvalue = getKeyDefault(type);
    string value = CCUserDefault::sharedUserDefault()->getStringForKey(getKeyString(type), defaultvalue);
    return HString::create(value)->getCString();
}

int HGameConfig::getIntValue(int type)
{
    return atoi(getStrValue(type));
}


int HGameTime::m_deltaTime = 0;

int HGameTime::getLocalTime()
{
    return time(NULL);
}

void HGameTime::setServerTime(int stime)
{    
    m_deltaTime = getLocalTime() -stime;
}

int HGameTime::getServerTime()
{    
    return getLocalTime()-m_deltaTime;
}

int HGameTime::getTimeInterval(int totime)
{    
    return totime - getServerTime();
}

bool HGameTime::hasReachTime(int time)
{
    return ((getServerTime()-time)>=0);
}

int HGameTime::getTodayChinaTime(int hour, int minute, int second)
{
    time_t time = getServerTime();
    time += 8 * 3600;
    struct tm tmvalue;
    gmtime_r(&time, &tmvalue);
    tmvalue.tm_hour = hour;
    tmvalue.tm_min = minute;
    tmvalue.tm_sec = second;
#ifdef ANDROID
    time = mktime(&tmvalue);
    time += tmvalue.tm_gmtoff;
#else
    time = timegm(&tmvalue);
#endif
    time -= 8*3600;
    return time;
}


HServerTimer* HServerTimer::create(int totime, const char *format, HTimerType type, CCCallFunc* callback)
{
    HServerTimer* timer = new HServerTimer;
    timer->m_toTime = totime+1;
    timer->m_format = format;
    timer->m_type = type;
    timer->m_done = false;
    timer->m_callback = NULL;
    timer->setCallBack(callback);
//    timer->autorelease();
    CC_AUTO_RELEASE(timer);
    return timer;
}

void HServerTimer::update(float dt)
{
    int second = max(0, HGameTime::getTimeInterval(m_toTime));
    
    int day = second / 86400;
    int hour = (second - 86400*day) / 3600;
    int minut = (second - 86400*day - 3600*hour) / 60;
    int sec = (second - 86400*day - 3600*hour - minut * 60);
    
    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(getTarget());
    const char* tm = "";
    switch (m_type) {
        case ET_Day:
        {
            static const char* dayformat = ccLocalizedString("HCOM_TIMER_DAY");
            tm = _T(dayformat, day, hour, minut, sec);
        }
            break;
            
        case ET_Hour:
        {
            tm = _T("%02d:%02d:%02d", day*24+hour, minut, sec);
        }
            break;
            
        default:
            break;
    }
    
    label->setString(_T(m_format.c_str(), tm));
    
    if (second == 0 && !m_done) {
        m_done = true;
        if (m_callback) {
            m_callback->execute();
            CC_SAFE_RELEASE_NULL(m_callback);
        }
    }
    
}


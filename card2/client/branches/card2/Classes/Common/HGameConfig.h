//
//  HGameConfig.h
//  card
//
//  Created by bo wei on 13-7-6.
//
//

#ifndef __card__HGameConfig__
#define __card__HGameConfig__

#include "headers.h"

typedef enum {
    CONFIG_MUSICBACK = 1000,
    CONFIG_MUSIC,
    CONFIG_AUTO,
    CONFIG_NEWBIE,
    CONFIG_MAILMAX
} ConfigType;

typedef enum {
    CARDITEM_NONE,
    CARDITEM_PROP,
    CARDITEM_CARDFRAG,
    CARDITEM_MAGICFRAG,
    CARDITEM_CARD,
    CARDITEM_MAGIC,
} CardItemType;

class HGameConfig: public CCObject
{
    HSINGLETON_OBJECT(HGameConfig);
    
public:
    static CardItemType getItemType(int id);
    static const char *getItemIcon(int id);
    static const char *getItemIconLarge(int id);
    static const char *getItemName(int id);
    static int getItemStar(int type);
    static const char *getRaceIcon(int id);
    static const char *getRaceIconLarge(int id);
    static int getRaceID(int type);
    static int getMaxLevel(int type);
    
    static int getFragUniCount(int itemid);
    
    static int Uni4;
    static int Uni5;
    static float GhostListRefreshSecond;
    
public:
    static const char *getKeyString(int id);
    static const char *getKeyDefault(int id);
    
    
    
public:
    void setConfig(int type, const char *value);
    void setConfig(int type, int value);
    int getIntValue(int type);
    const char *getStrValue(int id);    
};

class HGameTime
{
private:
    static int m_deltaTime;
public:
    static int getLocalTime();
    static int getServerTime();
    static void setServerTime(int stime);
    static int getTimeInterval(int totime);
    static bool hasReachTime(int time);
    static int getTodayChinaTime(int hour, int minute=0, int second=0);    
};

class HServerTimer : public CCActionInterval {
    
public:
    
    typedef enum{ET_Day, ET_Hour, ET_Minu, ET_Sec} HTimerType;
    
public:
    static HServerTimer* create(int totime, const char* format, HTimerType type = ET_Hour, CCCallFunc* callback = NULL);
    
    HServerTimer():m_callback(NULL){}
    virtual ~HServerTimer(){ CC_SAFE_RELEASE_NULL(m_callback); }
    
    virtual void update(float dt);
    virtual bool isDone() {return m_done;}
    
    
protected:
    __assign int m_toTime;
    __assign string m_format;
    __assign HTimerType m_type;
    __assign bool m_done;
    
    CC_SYNTHESIZE_RETAIN(CCCallFunc*, m_callback, CallBack);
    
};

#endif /* defined(__card__HGameConfig__) */

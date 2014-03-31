//
//  HUserObject.h
//  card
//
//  Created by zhou gang on 13-7-24.
//
//

#ifndef __card__HUserObject__
#define __card__HUserObject__

class HKey {
    
public:
    int id;
    const char* icon;
    const char* name;
    const char* description;
    char star_num;
    char race;
    char level_max;
    
    virtual ~HKey() {}
    
};

class HUserObject
{
public:
    CC_SYNTHESIZE(int, m_userId, UserId);
    CC_SYNTHESIZE(int, m_level, Level);
    CC_SYNTHESIZE(int, m_exp, Exp);
    
    virtual const HKey* getKeyObject(void) = 0;
    virtual void setKeyObject(const HKey* var) = 0;
    
public:
    HUserObject();
    virtual ~HUserObject();
    
    virtual int getLvupExp(int lv = -1) = 0;
    virtual const char* getExpStr() = 0;
    virtual float getExpPercentage() = 0;
    
    virtual const char* getIcon() = 0;
    virtual const char* getRaceIcon() = 0;
    virtual const char* getRaceName();
    
    virtual void setUserObject(HUserObject* uobj) = 0;
    virtual HUserObject* getUserObject() = 0;
    virtual void updateUserObject() = 0;
    virtual void resetUI() { resetUI(false); }
    virtual void resetUI(bool inThread) {}
    
};

#endif /* defined(__card__HUserObject__) */

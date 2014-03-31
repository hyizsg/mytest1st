//
//  HUserMagic.h
//  card
//
//  Created by zhou gang on 13-4-15.
//
//

#ifndef __card__HUserMagic__
#define __card__HUserMagic__

class HUserMagic;
#include "./ConfigClass/HMagic.h"

class HMagicTouchedDelegate
{
public:
    virtual void touchedEvent(HUserMagic* sender, int tag) = 0;
};

class HUserMagic : public HUserObject {
    
    
public:
//    CC_SYNTHESIZE(int, m_userId, UserId);
    CC_SYNTHESIZE(const HMagic*, m_keyMagic, KeyMagic);
//    CC_SYNTHESIZE(int, m_level, Level);
//    CC_SYNTHESIZE(int, m_exp, Exp);
    
    CC_SYNTHESIZE(HMagicTouchedDelegate*, m_tDelegate, TouchedDelegate);
    CC_SYNTHESIZE(int, m_tTag, TouchedTag);
    
public:
    HUserMagic();
    ~HUserMagic() {}
    virtual const char* getIcon();
    virtual void setUserMagic(const HUserMagic* magic);
    virtual HUserMagic* getUserMagic();
    virtual void updateUserMagic();
    
    virtual const char* getRaceIcon();
    
    int getLvupExp(int lv = -1);
    const char* getExpStr();
    float getExpPercentage();
    
    virtual void setUserObject(HUserObject* uobj);
    virtual HUserObject* getUserObject();
    virtual void updateUserObject();
    
    virtual const HKey* getKeyObject(void);
    virtual void setKeyObject(const HKey* var);
    
    void clearMagic()
    {
        setTouchedDelegate(NULL);
        setTouchedTag(-1);
        setKeyMagic(NULL);
    }
    
    static const char* getIconLarge(int id);
    static const char* getIconMiddle(int id);
    static const char* getIconFire(int id);
    static const char* getIconSmall(int id);
    
    static const char* getRaceLarge(int id);
    static const char* getRaceMiddle(int id);
    static const char* getRaceSmall(int id);
    
};



class HUserMagicObject : public HUserMagic, public CCObject {
    
public:
    HCREATE_FUNC(HUserMagicObject);
    static HUserMagicObject* create(int id, int level = 0);

};

#include "HUserBag.h"

struct usermagic_key_fun { int operator()(void* magic) { return ((HUserMagic*)magic)->getUserId(); } };

struct compare_magic_base{
    virtual bool operator ()(int, int) = 0;
};

struct compare_magic_level
{
    bool operator ()(int a, int b)
    {
        int lv1 = getCurrBag()->magicByUId(a)->getLevel();
        int lv2 = getCurrBag()->magicByUId(b)->getLevel();
        return lv1 != lv2 ? lv1 < lv2 : a < b;
    }
};

struct compare_magic_uid {
    bool operator ()(HUserMagic* a, HUserMagic* b){ return a->getUserId() < b->getUserId(); }
    bool operator ()(int a, int b){ return a < b; }
};

struct compare_magic_kid {
    bool operator ()(int a, int b)
    {
        int lv1 = getCurrBag()->magicByUId(a)->getKeyMagic()->id;
        int lv2 = getCurrBag()->magicByUId(b)->getKeyMagic()->id;
        return lv1 != lv2 ? lv1 < lv2 : a < b;
    }
};

struct compare_magic_kid_obj {
    static compare_magic_kid cmp_kid;
};


struct compare_magic_level_k
{
    bool operator ()(int a, int b)
    {
        int lv1 = getCurrBag()->magicByUId(a)->getLevel();
        int lv2 = getCurrBag()->magicByUId(b)->getLevel();
        return lv1 != lv2 ? lv1 < lv2 : compare_magic_kid_obj::cmp_kid(a, b);
    }
};

#endif /* defined(__card__HUserMagic__) */

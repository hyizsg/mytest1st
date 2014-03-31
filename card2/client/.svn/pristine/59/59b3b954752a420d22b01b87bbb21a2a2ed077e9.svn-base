//
//  HUserMagic.cpp
//  card
//
//  Created by zhou gang on 13-4-15.
//
//


#include "../headers.h"


compare_magic_kid compare_magic_kid_obj::cmp_kid;

HUserMagic::HUserMagic()
: m_tTag(-1)
, m_tDelegate(NULL)
, m_keyMagic(NULL)
{
    
}

void HUserMagic::setUserMagic(const HUserMagic* umagic)
{
    if (umagic != NULL) {
        setKeyMagic(umagic->getKeyMagic());
        setLevel(umagic->getLevel());
        setUserId(umagic->getUserId());
        setExp(umagic->getExp());
    }else{
        setKeyMagic(NULL);
    }
}

const char* HUserMagic::getIcon()
{
    return (getKeyMagic()->icon); // CCAssert(0, "must overorive it")
}

const char* HUserMagic::getRaceIcon()
{
    return (_T("%d", getKeyMagic()->race)); //CCAssert(0, "must overorive it"),
}

int HUserMagic::getLvupExp(int lv)
{
    if(lv == -1) lv = m_level;
    return getStrongByMagic(this, lv)->lup_exp;
}

const char* HUserMagic::getExpStr()
{
    if (m_level < 4) {
        return _T("%d/%d", m_exp, getLvupExp());
    }else{
        return _T("%d/%d", getLvupExp(3), getLvupExp(3));
    }
}

float HUserMagic::getExpPercentage()
{
    return m_level == 10 ? 100 : m_exp * 100.f / getLvupExp();
}

HUserMagic* HUserMagic::getUserMagic()
{
    return getCurrBag()->magicByUId(m_userId);
}

void HUserMagic::updateUserMagic()
{
    setUserMagic(getUserMagic());
}

void HUserMagic::setUserObject(HUserObject* uobj)
{
    CCAssert(!uobj || (uobj && dynamic_cast<const HUserMagic*>(uobj)) , "not a user magic");
    setUserMagic(dynamic_cast<HUserMagic*>(uobj));
}

HUserObject* HUserMagic::getUserObject()
{
    return getUserMagic();
}

void HUserMagic::updateUserObject()
{
    updateUserMagic();
}

const HKey* HUserMagic::getKeyObject(void)
{
    return getKeyMagic();
}

void HUserMagic::setKeyObject(const HKey* var)
{
    CCAssert(!var || (var && dynamic_cast<const HMagic*>(var)) , "not a key magic");
    m_keyMagic = dynamic_cast<const HMagic*>(var);
}

////////----

const char* HUserMagic::getIconLarge(int id)
{
//    return "game/magic/9307_a.jpg";
    return _T("game/magic/%s%s.jpg", getMagicById(id, 0)->icon, "_a");
}

const char* HUserMagic::getIconMiddle(int id)
{
//    return "game/magic/9307_b.jpg";
    return _T("game/magic/%s%s.jpg", getMagicById(id, 0)->icon, "_b");
}

const char *HUserMagic::getIconSmall(int id)
{
    return _T("game/magic/%s%s.png", getMagicById(id, 0)->icon, "_c");
}

const char* HUserMagic::getIconFire(int id)
{
//    return "game/magic/9307_d.png";
    return _T("game/magic/%s%s.png", getMagicById(id, 0)->icon, "_d");
}

const char* HUserMagic::getRaceLarge(int id)
{
    return _T("game/card/382_524/card_a_%d.png", getMagicById(id, 0)->race);
}

const char* HUserMagic::getRaceMiddle(int id)
{
    return _T("card_b_%d.png", getMagicById(id, 0)->race);
}

const char* HUserMagic::getRaceSmall(int id)
{
    return _T("card_c_%d.png", getMagicById(id, 0)->race);
}

// --

HUserMagicObject* HUserMagicObject::create(int id, int level)
{
    HUserMagicObject* mg = new HUserMagicObject;
    mg->setKeyMagic(getMagicById(id, level));
    mg->setLevel(level);
//    mg->autorelease();
    CC_AUTO_RELEASE(mg);
    return mg;
}

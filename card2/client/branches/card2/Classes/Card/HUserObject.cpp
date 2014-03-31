//
//  HUserObject.cpp
//  card
//
//  Created by zhou gang on 13-7-24.
//
//


#include "../headers.h"

HUserObject::HUserObject()
: m_userId(0)
, m_level(0)
, m_exp(0)
{
    
}

HUserObject::~HUserObject()
{
    
}

const char* HUserObject::getRaceName()
{
    static const char* g_race[] = {"", ccLocalizedString("HCOM_TU"), ccLocalizedString("HCOM_SHUI"), ccLocalizedString("HCOM_HUO"), ccLocalizedString("HCOM_MU"), ccLocalizedString("HCOM_JIN")};
    return g_race[getKeyObject()->race];
}

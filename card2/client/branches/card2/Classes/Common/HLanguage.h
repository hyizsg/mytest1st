//
//  HLanguage.h
//  card
//
//  Created by bo wei on 13-7-11.
//
//

#ifndef __card__HLanguage__
#define __card__HLanguage__

#include "headers.h"
#include <map>

class HLanguage: public CCObject
{
    HSINGLETON_OBJECT(HLanguage);
public:
    static const char *getError(int errorcode, const char *defaultvalue, bool usedefault = false);
private:
    void init();
    CCDictionary m_Datas;
};


#endif /* defined(__card__HLanguage__) */

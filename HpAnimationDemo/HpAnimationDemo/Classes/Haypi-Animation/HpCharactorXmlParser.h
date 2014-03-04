#ifndef HPCHARACTORXMLPARSE_H
#define HPCHARACTORXMLPARSE_H

#include "cocos2d.h"

#include "HpAnimation.h"
#include "HpLayer.h"
#include "HpKeyframe.h"
#include "HpCharactor.h"


USING_NS_CC;

namespace haypi_animation{

class HpCharactor;

enum CharKeyPropertyType{
    CharKeyProperty_None,
    CharKeyProperty_Image,
    CharKeyProperty_Anima,
    CharKeyProperty_Time,
    CharKeyProperty_TimeInher,
    CharKeyProperty_Center,
    CharKeyProperty_Trans,
    CharKeyProperty_Scale,
    CharKeyProperty_Rot,
    CharKeyProperty_Skew,
    CharKeyProperty_Color,
    CharKeyProperty_ColorEx,
    CharKeyProperty_Event
};


class HpCharactorXmlParser : public HpCharactorParser, public CCSAXDelegator{
private:
    HpCharactor* m_cur_chara;
    HpAnimation* m_cur_anima;
    HpLayer* m_cur_layer;
    HpKeyframe* m_cur_keyfrm;
    int m_cur_property;

private:
    bool m_isJumpHeadData;
    bool m_dealEnd;


    std::string m_startXmlElement;
    std::string m_endXmlElement;
    std::string m_currString;

public:
    HpCharactorXmlParser();
    virtual ~HpCharactorXmlParser();
    
    HpCharactor* parse(const char* p_file);
    
    void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *s, int len);

    CCString* getAttribute(const char* att, const char **atts);
    
    CCPoint MakeCGPointFromString(const char* p_string);
};

}



#endif // HPCHARACTORXMLPARSE_H

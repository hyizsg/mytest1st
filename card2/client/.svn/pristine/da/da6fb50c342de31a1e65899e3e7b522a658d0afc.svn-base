#include "HpCharactorXmlParser.h"


#include "HpImageKeyframe.h"
#include "HpAnimaKeyframe.h"
#include "HpInterpHolder.h"
#include "HpLinearInterpolator.h"
#include "HpSplineInterpolator.h"
#include "HpGlobalFunc.h"
#include "HpCharactor.h"

#include "HpLog.h"

using namespace haypi_animation;

HpCharactorXmlParser::HpCharactorXmlParser(){
    m_cur_chara = NULL;
    m_cur_anima = NULL;
    m_cur_layer = NULL;
    m_cur_keyfrm = NULL;
}
HpCharactorXmlParser::~HpCharactorXmlParser(){
    
}


CCObject* HpCharactorXmlParser::parse(CCString *p_file){
    m_cur_chara = NULL;

    string full_path = CCFileUtils::sharedFileUtils()->fullPathForFilename(p_file->getCString());
    CCSAXParser* parser = new CCSAXParser;
    if(parser->init("UTF-8")){
        parser->setDelegator(this);
        parser->parse(full_path.c_str());

    }
    
    CC_SAFE_DELETE(parser);
//	m_cur_chara->autorelease();
    CC_AUTO_RELEASE(m_cur_chara);
    return m_cur_chara;

}

CCString* HpCharactorXmlParser::getAttribute(const char* att, const char **atts){
    CCString* ret = CCString::create("");
    for(; atts != NULL; atts ++){
        if(strcmp(*atts, att) == 0){
            ret->m_sString = *(atts + 1);
            break;
        }
        ++ atts;
    }

//    HPLOG("apple...HpCharactorXmlParser......%s", ret->getCString());
    return ret;
}

void HpCharactorXmlParser::startElement(void *ctx, const char *pname, const char **atts){
    CC_UNUSED_PARAM(ctx);

//    HPLOG("HpCharactorXmlParser....startElement name %s", pname);
    
    m_dealEnd = false;
    m_startXmlElement = (char*)pname;

    if(m_startXmlElement.compare("Charactor") == 0){
        m_cur_property = CharKeyProperty_None;
        m_cur_chara = new HpCharactor();
    } else if(m_startXmlElement.compare("plist") == 0){
        CCString* path = getAttribute("file", atts);
        m_cur_chara->getPLists()->addObject(path);

    } else if(m_startXmlElement.compare("Animation") == 0){
        CCString* name = getAttribute("name", atts);
        CCString* len = getAttribute("length", atts);

        HPLOG("HpCharactorXmlParser....startElement name %s，                 name %s, length %d",pname, name->getCString(), len->intValue());
        if(m_cur_chara->getAnimas()->objectForKey(name->getCString())){
            HPLOG("Duplicated animation id : %s", name->getCString());
        }
        m_cur_anima = new HpAnimation(len->intValue());
        m_cur_chara->getAnimas()->setObject(m_cur_anima, name->getCString());
		m_cur_anima->release();

    } else if(m_startXmlElement.compare("Node") == 0){
        CCString* name = getAttribute("name", atts);
        m_cur_layer = new HpLayer(name);
        m_cur_anima->getLayers()->addObject(m_cur_layer);
		m_cur_layer->release();

    } else if(m_startXmlElement.compare("Key") == 0){
        m_cur_keyfrm = new HpKeyframe;

        CCString* type = getAttribute("type", atts);
        
        if(type->compare("NullKey") == 0)
            m_cur_keyfrm->setContentType(HPCONTENTTYPE_NULL);
        else if(type->compare("ImageKey") == 0)
            m_cur_keyfrm->setContentType(HPCONTENTTYPE_IMAGE);
        else if(type->compare("AnimaKey") == 0)
            m_cur_keyfrm->setContentType(HPCONTENTTYPE_ANIMA);

        m_cur_keyfrm->setArrayIndex(m_cur_layer->getKeys()->count());
        m_cur_layer->getKeys()->addObject(m_cur_keyfrm);
        m_cur_keyfrm->release();
    } else if(m_startXmlElement.compare("Image") == 0){
        m_cur_property = CharKeyProperty_Image;
    } else if(m_startXmlElement.compare("Anima") == 0){
        m_cur_property = CharKeyProperty_Anima;
    } else if(m_startXmlElement.compare("Time") == 0){
        m_cur_property = CharKeyProperty_Time;
    } else if (m_startXmlElement.compare("TimeInher") == 0){
        m_cur_property = CharKeyProperty_TimeInher;
    } else if(m_startXmlElement.compare("Center") == 0){
        m_cur_property = CharKeyProperty_Center;
    } else if(m_startXmlElement.compare("Scale") == 0){
        m_cur_property = CharKeyProperty_Scale;
    } else if(m_startXmlElement.compare("Skew") == 0){
        m_cur_property = CharKeyProperty_Skew;
    } else if(m_startXmlElement.compare("Rot") == 0){
        m_cur_property = CharKeyProperty_Rot;
    } else if(m_startXmlElement.compare("Trans") == 0){
        m_cur_property = CharKeyProperty_Trans;
    } else if(m_startXmlElement.compare("Color") == 0){
        m_cur_property = CharKeyProperty_Color;
    } else if(m_startXmlElement.compare("Event") == 0){
        m_cur_property = CharKeyProperty_Event;
    } else if(m_startXmlElement.compare("Interps") == 0){
        if(m_cur_chara->getAnimas()->objectForKey("10100") == m_cur_anima){
            HPLOG("HpCharactorXmlParser....startElement name %s", pname);
        }
        
        HpInterpHolder* holder = new HpInterpHolder;
        m_cur_keyfrm->setInterps(holder);
		holder->release();
    } else if(m_startXmlElement.compare("Interp") == 0){
        CCString* type = getAttribute("type", atts);
        if(m_cur_chara->getAnimas()->objectForKey("10100") == m_cur_anima){
            HPLOG("HpCharactorXmlParser....startElement name %s, atts %s", pname, type->getCString());
        }
        
        HpInterp* interp;
        if(type->compare("linear") == 0)
            interp = HpLinearInterp::Interp();
        else if (type->compare("spline") == 0)
            interp = HpSplineInterp::interp(getAttribute("ctrlpts", atts));

        CCString* target = getAttribute("target", atts);
        if(target->compare("Center") == 0)
            m_cur_keyfrm->getInterps()->setCenterInterp(interp);
        else if(target->compare("Scale") == 0)
            m_cur_keyfrm->getInterps()->setScaleInterp(interp);
        else if(target->compare("Skew") == 0)
            m_cur_keyfrm->getInterps()->setSkewInterp(interp);
        else if(target->compare("Rot") == 0)
            m_cur_keyfrm->getInterps()->setRotInterp(interp);
        else if(target->compare("Trans") == 0)
            m_cur_keyfrm->getInterps()->setTransInterp(interp);
        else if(target->compare("Color") == 0)
            m_cur_keyfrm->getInterps()->setColorInterp(interp);
    }
}

void HpCharactorXmlParser::endElement(void *ctx, const char *name){
    CC_UNUSED_PARAM(ctx);
//    HPLOG("HpCharactorXmlParser....endElement s %s", name);
    m_cur_property = CharKeyProperty_None;
    m_dealEnd = true;
}

void HpCharactorXmlParser::textHandler(void *ctx, const char *s, int len){
    CC_UNUSED_PARAM(ctx);
    if(m_dealEnd) return;

    m_currString = string((char*)s, 0, len);
//    HPLOG("HpCharactorXmlParser....textHandler s %s", m_currString.c_str());
//    char* curr = const_cast<char*>(m_currString.c_str());
    CCString* cur_string = CCString::create(m_currString);

    cur_string->retain();

    switch (m_cur_property)
    {
    case CharKeyProperty_None:
        break;
    case CharKeyProperty_Image:
    case CharKeyProperty_Anima:
        m_cur_keyfrm->setContent(cur_string);
        break;
    case CharKeyProperty_Event:
        m_cur_keyfrm->setEvent(cur_string);
        break;
    case CharKeyProperty_Center:
        m_cur_keyfrm->setCenter(MakeCGPointFromString(cur_string->getCString()));
        break;
    case CharKeyProperty_Color:
    {
        const char* hex = m_currString.c_str();
        ++ hex;

        char *str;
        unsigned int value = (unsigned int)strtoll(hex, &str, 16);//十六进制

        m_cur_keyfrm->setColor(ccc4f(((value >> 16) & 0xff) / 255.f,
                                   ((value >> 8) & 0xff) / 255.f,
                                   (value & 0xff) / 255.f,
                                   ((value >> 24) & 0xff) / 255.f));
        break;
    }
    case CharKeyProperty_Rot:
        m_cur_keyfrm->setRot(cur_string->floatValue());
        break;
    case CharKeyProperty_Scale:
        m_cur_keyfrm->setScale(MakeCGPointFromString(cur_string->getCString()));
        break;
    case CharKeyProperty_Skew:
        m_cur_keyfrm->setSkew(MakeCGPointFromString(cur_string->getCString()));
        break;
    case CharKeyProperty_Time:
        m_cur_keyfrm->setTime(cur_string->intValue());
        break;
    case CharKeyProperty_TimeInher:
        m_cur_keyfrm->setIsTimeInherited(cur_string->boolValue());
        break;
    case CharKeyProperty_Trans:
        m_cur_keyfrm->setTrans(MakeCGPointFromString(cur_string->getCString()));
        break;
    default:
        break;
    }
    
    cur_string->release();
}

CCPoint HpCharactorXmlParser::MakeCGPointFromString(const char* p_string){
    CCString* poi = CCString::createWithFormat("{%s}", p_string);
    return CCPointFromString(poi->getCString());
}

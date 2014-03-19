//
//  HpCharactorBinParser.cpp
//  Cocos2DxFirstlosSample
//
//  Created by zhou gang on 13-3-7.
//
//

#include "HpCharactorBinParser.h"
#include "HpBinaryReader.h"

#include "HpCharactor.h"
#include "HpAnimation.h"
#include "HpLayer.h"
#include "HpKeyframe.h"

#include "HpImageKeyframe.h"
#include "HpAnimaKeyframe.h"
#include "HpNullKeyframe.h"
#include "HpInterpHolder.h"
#include "HpLinearInterpolator.h"
#include "HpSplineInterpolator.h"

NS_HPAM_BEGIN
    
    typedef unsigned char  Byte;
    
static Byte ChrReadingVersionMax = 0x5;
static Byte ChrReadingVersion = 0x00;
static float Byte2Double = 1/255.f;

CCPoint ReadPoint(HpBinaryReader* reader);
ccColor4F ReadColor(HpBinaryReader* reader);
HpInterp* ReadInterp(HpBinaryReader* reader);

HpCharactor* HpCharactorBinParser::parse(const char* p_file)
{
    
    m_cur_chara = new HpCharactor();
    HpBinaryReader* reader = NULL;
    
    const string& full_path = CCFileUtils::sharedFileUtils()->fullPathForFilename(p_file);
    
    unsigned long size = 0;
    char* pBuffer = (char*)CCFileUtils::sharedFileUtils()->getFileData(full_path.c_str(), "rt", &size);
    if (pBuffer != NULL && size > 0)
    {
        reader = new HpBinaryReader(pBuffer, size);
    }
    
    char buffer[128] = {0};
    
    reader->ReadChars(buffer, 3);
    if (strncasecmp(buffer, "CHR", 3) != 0) return NULL;
    
    ChrReadingVersion = reader->ReadByte();
    
    if (ChrReadingVersion > ChrReadingVersionMax) {
        CCLOG("HpCharactorBinParser max reader version is %d, but the file version is %d", ChrReadingVersionMax, ChrReadingVersion);
        CCAssert(0, "");
        return NULL;
    }
    
    Byte plist_count = reader->ReadByte();
    for(int i=0; i<plist_count;i++)
    {
        reader->ReadString(buffer);
        char* p = strrchr(buffer, '\\');
        m_cur_chara->getPLists()->addObject(CCString::create(p ? p+1 : buffer));
    }
    
    unsigned short anim_count = reader->ReadUInt16();
    for(int i=0; i<anim_count; i++) {
        readAnimation(reader, buffer);
    }
    
    reader->Close();
    CC_SAFE_DELETE(reader);
    CC_SAFE_DELETE_ARRAY(pBuffer);
    
    
    return m_cur_chara;
}

void HpCharactorBinParser::readAnimation(HpBinaryReader *reader, char *buffer)
{
    reader->ReadString(buffer);
    char* anim_name = buffer;
    if (m_cur_chara->getAnimas()->objectForKey(anim_name))
        CCLOGERROR("Duplicated animation id : %s", anim_name);
    
    int len = 0;
    switch (ChrReadingVersion) {
        case 0x02:
        case 0x03:
            len = reader->ReadByte();
            break;
        default:
            len = reader->ReadUInt16();
            break;
    }
    
    m_cur_anima = new HpAnimation(len);
    m_cur_chara->getAnimas()->setObject(m_cur_anima, anim_name);
    CC_SAFE_RELEASE(m_cur_anima);
    
    Byte layer_count = reader->ReadByte();
    for(int i=0; i<layer_count; i++) {
        readLayer(reader, buffer);
    }
}

void HpCharactorBinParser::readLayer(HpBinaryReader *reader, char *buffer)
{
    reader->ReadString(buffer);
    CCString* layer_name = new CCString(buffer);
    m_cur_layer = new HpLayer(layer_name);
    m_cur_anima->getLayers()->addObject(m_cur_layer);
    
    CC_SAFE_RELEASE(layer_name);
    CC_SAFE_RELEASE(m_cur_layer);
    
    unsigned short key_count = reader->ReadUInt16();
    for(int k=0; k<key_count; k++) {
        readKeyFrame(reader, buffer);
    }
}

void HpCharactorBinParser::readKeyFrame(HpBinaryReader *reader, char *buffer)
{
    m_cur_keyfrm = new HpKeyframe();
    m_cur_keyfrm->setContentType((HpContentType)reader->ReadByte());
    m_cur_keyfrm->setArrayIndex(m_cur_layer->getKeys()->count());
    m_cur_layer->getKeys()->addObject(m_cur_keyfrm);
    
    CC_SAFE_RELEASE(m_cur_keyfrm);
    
    if (m_cur_keyfrm->getContentType() != HPCONTENTTYPE_NULL) {
        reader->ReadString(buffer);
        CCString* content_name = new CCString(buffer);
        m_cur_keyfrm->setContent(content_name);
        CC_SAFE_RELEASE(content_name);
    }
    
    readCommon(reader, buffer);
}

void HpCharactorBinParser::readCommon(HpBinaryReader *reader, char *buffer)
{
    switch (ChrReadingVersion) {
        case 0x02:
        case 0x03:
            m_cur_keyfrm->setTime(reader->ReadByte());
            break;
            
        default:
            m_cur_keyfrm->setTime(reader->ReadUInt16());
            break;
    }
    
    if (m_cur_keyfrm->getContentType() == HPCONTENTTYPE_NULL)
        return;
    
    if (m_cur_keyfrm->getContentType() == HPCONTENTTYPE_ANIMA)
        m_cur_keyfrm->setIsTimeInherited(reader->ReadBoolean());
    
    m_cur_keyfrm->setCenter(ReadPoint(reader));
    m_cur_keyfrm->setScale(ReadPoint(reader));
    m_cur_keyfrm->setSkew(ReadPoint(reader));
    m_cur_keyfrm->setRot(reader->ReadSingle());
    m_cur_keyfrm->setTrans(ReadPoint(reader));
    m_cur_keyfrm->setColor(ReadColor(reader));
    
    if (ChrReadingVersion >= 0x05) {
        m_cur_keyfrm->setLight(ReadColor(reader));
    }else{
        m_cur_keyfrm->setLight(ccClear4F);
    }
    
    if (ChrReadingVersion >= 0x06) {
        m_cur_keyfrm->setGray(reader->ReadByte());
    }else{
        m_cur_keyfrm->setGray(0);
    }
    
    reader->ReadString(buffer);
    CCString* event = buffer[0] ? new CCString(buffer) : NULL;
    m_cur_keyfrm->setEvent(event);
    CC_SAFE_RELEASE(event);
    
    Byte interp_type = reader->ReadByte();
    if (interp_type > 0) {
        HpInterpHolder* holder = new HpInterpHolder();
        m_cur_keyfrm->setInterps(holder);
        CC_SAFE_RELEASE(holder);
        
        if (interp_type == 1) {
            holder->setCenterInterp(HpLinearInterp::Interp());
            holder->setScaleInterp(HpLinearInterp::Interp());
            holder->setSkewInterp(HpLinearInterp::Interp());
            holder->setRotInterp(HpLinearInterp::Interp());
            holder->setTransInterp(HpLinearInterp::Interp());
            holder->setColorInterp(HpLinearInterp::Interp());
        }else if (interp_type == 2) {
            HpInterp* interp = ReadInterp(reader);
            holder->setCenterInterp(interp);
            holder->setScaleInterp(interp);
            holder->setSkewInterp(interp);
            holder->setRotInterp(interp);
            holder->setTransInterp(interp);
            holder->setColorInterp(interp);
        }else if (interp_type == 3) {
            holder->setCenterInterp(ReadInterp(reader));
            holder->setScaleInterp(ReadInterp(reader));
            holder->setSkewInterp(ReadInterp(reader));
            holder->setRotInterp(ReadInterp(reader));
            holder->setTransInterp(ReadInterp(reader));
            holder->setColorInterp(ReadInterp(reader));
        }
    }
}

///---extension-------------------------------------------------

CCPoint ReadPoint(HpBinaryReader* reader)
{
    CCPoint p ;
    p.x = reader->ReadSingle();
    p.y = reader->ReadSingle();
    return p;
}

ccColor4F ReadColor(HpBinaryReader* reader)
{
    ccColor4F color;
    color.r = reader->ReadByte()*Byte2Double;
    color.g = reader->ReadByte()*Byte2Double;
    color.b = reader->ReadByte()*Byte2Double;
    color.a = reader->ReadByte()*Byte2Double;
    return color;
}

HpInterp* ReadInterp(HpBinaryReader* reader)
{
    switch (ChrReadingVersion) {
        case 0x02:
        {
            HpSplineInterp* interp = new HpSplineInterp();
            interp->P1 = ReadPoint(reader);
            interp->P2 = ReadPoint(reader);
//            interp->autorelease();
            HP_AUTO_RELEASE(interp);
            return interp;
        }
        default:
        {
            float x1 = reader->ReadByte()*Byte2Double;
            float y1 = reader->ReadByte()*Byte2Double;
            float x2 = reader->ReadByte()*Byte2Double;
            float y2 = reader->ReadByte()*Byte2Double;
            return HpSplineInterp::interp(x1, y1, x2, y2);
        }
    }
}
    


NS_HPAM_END
//
//  HCommonObject.cpp
//  card2
//
//  Created by zhou gang on 14-2-11.
//
//

#include "headers.h"
#include "HCommonObject.h"

HCommonObject::HCommonObject()
{
    
}

HCommonObject::~HCommonObject()
{
    for (int i=0; i<m_observers.size(); i++) {
        CCNotificationCenter::sharedNotificationCenter()->removeObserver((CCObject*)(this), m_observers[i].c_str());
    }
    
    m_observers.clear();
}

void HCommonObject::messageBox(const char *msg)
{
    HMessageBox::show(msg);
}

void HCommonObject::startAIV()
{
    HRootScene::current()->startAIV();
}

void HCommonObject::stopAIV()
{
    HRootScene::current()->stopAIV();
}

void HCommonObject::post(HDataRequest* request)
{
    HDataCenter::post(request);
}

void HCommonObject::post(int cmdId, CCDictionary* param)
{
    post(HDataRequest::create(cmdId, param));
}

void HCommonObject::notifyActionMsg(cocos2d::CCObject *obj)
{
    
}

void HCommonObject:: addObserver(int cmdid)
{
    addObserver(itoa(cmdid));
}

void HCommonObject::addObserver(const char *cmdstr)
{
    addObserver(callfuncO_selector(HCommonObject::notifyActionMsg), cmdstr);
}

void HCommonObject::addObserver(SEL_CallFuncO sel, int cmdid)
{
    addObserver(sel, itoa(cmdid));
}

void HCommonObject::addObserver(SEL_CallFuncO sel, const char* cmdstr)
{
    m_observers.push_back(cmdstr);
    CCNotificationCenter::sharedNotificationCenter()->addObserver((CCObject*)this, sel, cmdstr, nil);
}

void HCommonObject::playButtonSound()
{
    HGameManager::getInstance()->playSoundEffect(HMUSIC_BUTTON);
}

void HCommonObject::playSoundById(int id)
{
    HGameManager::getInstance()->playSoundEffect(id);
}


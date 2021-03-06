﻿//
//  HMaskLayer2.cpp
//  card
//
//  Created by zhou gang on 13-10-31.
//
//

#include "../../headers.h"
#include "HWindow.h"
#include "HRootScene.h"
#include "HMaskLayer2.h"

int HMaskWindow2::tolerant_frame = 2;

HMaskWindow2::HMaskWindow2()
: m_bMasking(false)
, m_nFrameCount(0)
{
    m_pTaskList = new CCArray;
    m_pSecondTaskList = new CCArray;
    
    scheduleUpdate();
    setOpacity(0);
    setVisible(false);
}

HMaskWindow2::~HMaskWindow2()
{
    unscheduleUpdate();
    CC_SAFE_RELEASE_NULL(m_pTaskList);
    CC_SAFE_RELEASE_NULL(m_pSecondTaskList);
}

HMaskWindow2* HMaskWindow2::create()
{
    HMaskWindow2* mask = new HMaskWindow2;
    mask->initWithColor(ccc4(0, 0, 0, 0));
    mask->onEnter();
    CC_AUTO_RELEASE(mask);
    return mask;
}

HRootScene* HMaskWindow2::scene()
{
    CCNode* parent = getParent();
    while (parent) {
        HRootScene* scene = dynamic_cast<HRootScene*>(parent);
        if (scene) {
            return scene;
        }else{
            parent = parent->getParent();
        }
    }
    
    return NULL;
}

void HMaskWindow2::maskWithInOut(HWindow *pIn, HWindow *pOut, float fDuration, bool bCleanup)
{
    if (m_pTaskList->count() == 0) {
        m_nFrameCount = 0;
    }
    
    pIn = pIn == NULL ? HWindow::create() : pIn;
    pOut = pOut == NULL ? HWindow::create() : pOut;
    
    
    CCArray* tasklist = m_pSecondTaskList;
    
    if (m_pTaskList->count() == 0) {
        tasklist = m_pTaskList;
    }else if (m_nFrameCount <= tolerant_frame) {
        if ((!pIn->isDialog() && !bCleanup) || // 动画弹入 present
            (!pOut->isDialog() && bCleanup)) { // 动画弹出 dismiss
            tasklist = m_pTaskList;
        }
    }
    
    HMaskData* data = (HMaskData*)tasklist->lastObject();
    tasklist->addObject(HMaskData::create(pIn, pOut, fDuration, bCleanup));
    
    if (data && data->getInWnd() == pOut && !pIn->isDialog()) {
        data->setInWnd(pOut->isDialog() ? HDialog::create() : HWindow::create());
    }
    
    if (!scene()->isRunning()) {
        beginMask();
    }else{
        CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(false);
    }
}

void HMaskWindow2::update(float dt)
{
    m_nFrameCount ++;
}

void HMaskWindow2::beginMask()
{
    if (m_bMasking || m_pTaskList->count() == 0) {
        return;
    }
    
    bool useAnima = false;
    
    if (scene()->isRunning()){
        FOREACH(HMaskData*, data, m_pTaskList)
        {
            if (data->getInWnd()->isEnableAnimaInOut()) {
                if ((!data->getInWnd()->isDialog() && !data->isSendCleanup()) || // 动画弹入 present
                    (!data->getOutWnd()->isDialog() && data->isSendCleanup())) { // 动画弹出 dismiss
                    useAnima = true;
                    break;
                }
            }
        }
    }
    
    
    if (scene()->isRunning() && m_nFrameCount <= tolerant_frame && useAnima) {
        return;
    }
    
    m_bMasking = true;
    
    if (!useAnima) {
        begin();
        hideOutShowIn();
        finish();
    }else{
        
        CCActionInterval* a = (CCActionInterval *)CCSequence::create
        (
         CCCallFunc::create(this, callfunc_selector(HMaskWindow2::begin)),
         CCFadeIn::create(HRootScene::gfDurationFadeInOut*0.5f),
         CCCallFunc::create(this, callfunc_selector(HMaskWindow2::hideOutShowIn)),
         CCFadeOut::create(HRootScene::gfDurationFadeInOut*0.5f),
         CCCallFunc::create(this, callfunc_selector(HMaskWindow2::finish)),
         NULL
         );
        this->runAction(a);//->setTag(kMaskActionTag);
        this->setOpacity(0);
        this->setVisible(true);
    }
    
}

void HMaskWindow2::begin()
{
    if (this->scene()->isRunning()) {
        FOREACH(HMaskData*, data, m_pTaskList){
            if(data->getOutWnd()->getParent()) {
                data->getOutWnd()->onExitTransitionDidStart();
            }
            if (data->getInWnd()->getParent() && !data->getInWnd()->isRunning()) {
                data->getInWnd()->onEnter();
            }
        }
    }
}

void HMaskWindow2::hideOutShowIn()
{
    FOREACH(HMaskData*, data, m_pTaskList){
        if (!data->isSendCleanup()) { // present
            int state = (data->getOutWnd()->isDialog() << 1) | data->getInWnd()->isDialog();
            switch (state) {
                case 0b00:
                    data->getOutWnd()->setVisible(false);
                    data->getInWnd()->setVisible(true);
                    break;
                case 0b01:
                case 0b11:
                    data->getInWnd()->setVisible(true);
                    break;
                case 0b10:
                {
                    HDialog* dlg = (HDialog*)data->getOutWnd();
                    dlg->setVisible(false);
                    dlg->getOwnner()->setVisible(false);
                    data->getInWnd()->setVisible(true);
                }
                    break;
                    
                default:
                    break;
            }
        }
        else{   // dissmis
            int state = (data->getOutWnd()->isDialog() << 1) | data->getInWnd()->isDialog();
            switch (state) {
                case 0b00:
                    data->getOutWnd()->setVisible(false);
                    data->getInWnd()->setVisible(true);
                    break;
                case 0b01:
                {
                    data->getOutWnd()->setVisible(false);
                    HDialog* dlg = (HDialog*)data->getInWnd();
                    dlg->setVisible(true);
                    dlg->getOwnner()->setVisible(true);
                }
                    break;
                case 0b10:
                case 0b11:
                    data->getOutWnd()->setVisible(false);
                    break;
                    
                default:
                    break;
            }
            
        }
    }
}

void HMaskWindow2::finish()
{
    bool bRunning = this->scene()->isRunning();
    
    FOREACH(HMaskData*, data, m_pTaskList){
        if (bRunning) {
            if (data->getOutWnd()->getParent()) {
                data->getOutWnd()->onExit();
            }
            
            if (data->getInWnd()->getParent()) {
                data->getInWnd()->onEnterTransitionDidFinish();
            }
        }
        if (data->isSendCleanup()) {
            data->getOutWnd()->removeFromParent();
        }
    }
    
    m_pTaskList->removeAllObjects();
    swap(m_pTaskList, m_pSecondTaskList);
    
    this->setVisible(false);
    this->setOpacity(0);
    this->m_bMasking = false;
    m_nFrameCount = 0;
    
    if (!bRunning) {
        beginMask();
    }else if (m_pTaskList->count() == 0) {
        CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true);
    }
}


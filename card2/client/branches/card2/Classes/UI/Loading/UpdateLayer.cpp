﻿//
//  UpdateLayer.cpp
//  card
//
//  Created by bo wei on 13-6-20.
//
//

#include "UpdateLayer.h"
#include "UpdateManager.h"
#include "HGameManager.h"
#include "HMessageBox.h"
#include "carddef.h"

BEGIN_PLIST(HUpdateWindow)
PLIST(start960)
END_PLIST()

BEGIN_MEMBER_MAP(HUpdateWindow)
MEMBER(m_pLoadingLabel)
MEMBER(m_pLoadingLine)
MEMBER(m_pMsg)
END_MEMBER_MAP()

BEGIN_CLICK_MAP(HUpdateWindow)
END_CLICK_MAP()

HUpdateWindow::HUpdateWindow()
{
//    INIT_PLISTS_CCBI(ccbi);
    
    //NOTIFY_ADD_OBSERVER(HFriendMain::notifyMsg, itoa(ACTION_FRIEND_GET));
}

HUpdateWindow::~HUpdateWindow()
{
//    DISPOSE_PLISTS();
    
    /*NOTIFY_REMOVE_OBSERVER(itoa(ACTION_HANDBOOK_INFO));*/
    
    recycleCell(this);
    removeAllChildren();
    getCurrBag()->removeAllTexture();
}

bool HUpdateWindow::init()
{   
    haypi::UpdateManager::sharedInstance()->checkVersion(checkVersionUrl, CURR_DEVICETYPE, CURR_GCTYPE, CURR_PLATFORM, 0);    
    
    this->scheduleUpdate();
    m_pLoadingLine->setPercentage(0.0f);
    
    return true;
}

void HUpdateWindow::resetUI(bool bfirst)
{
}

void HUpdateWindow::updateProgress()
{
    int progress = haypi::UpdateManager::sharedInstance()->progress();
    char buff[256];
    sprintf(buff, ccLocalizedString("HUPDATE_DOWNLOAD"), progress);
    m_pLoadingLabel->setString(buff);
    m_pLoadingLine->setPercentage(1.0*progress);
    if (progress > 0)
    {
        m_pLoadingLabel->setVisible(true);
    }
}

void HUpdateWindow::update(float 	delta)
{
    haypi::UpdateManager::UM_STATE state = haypi::UpdateManager::sharedInstance()->state();
    switch (state) {
        case haypi::UpdateManager::UMS_Error:
            this->unscheduleUpdate();
            HMessageBox::show(ccLocalizedString("HUPDATE_DOWNLOAD_ERR_RETRY"), ccLocalizedString("HCOM_TIP_MSG"), HMB_OK, this);
            //CrossDelegate::ShowAlterView("", this, (SEL_AlertViewCb)(&UpdateLayer::alterCallback));
            break;
        case haypi::UpdateManager::UMS_Downloading:
            updateProgress();
            break;
        case haypi::UpdateManager::UMS_OK:
            this->unscheduleUpdate();
            HMessageBox::show(ccLocalizedString("HUPDATE_SUCCESS"), ccLocalizedString("HCOM_TIP_MSG"), HMB_OK, this);
            //CrossDelegate::ShowAlterView("下载完成", this, (SEL_AlertViewCb)(&UpdateLayer::alterCallback));
            break;
        default:
            break;
    }    
}

void HUpdateWindow::onOK(HMessageBox* sender)
{
    haypi::UpdateManager *manager = haypi::UpdateManager::sharedInstance();
    haypi::UpdateManager::UM_STATE state = manager->state();
    if (state == haypi::UpdateManager::UMS_Error)
    {
        restart();
    }
    else {
        HGameManager::getInstance()->onUpdateFinished();
        this->dismissRootLayer(false);
    }
}

void HUpdateWindow::restart()
{
    haypi::UpdateManager *manager = haypi::UpdateManager::sharedInstance();
    manager->clean();
    updateProgress();
    haypi::UpdateManager::sharedInstance()->checkVersion(checkVersionUrl, CURR_DEVICETYPE, CURR_GCTYPE, CURR_PLATFORM, 0);
    this->scheduleUpdate();
}

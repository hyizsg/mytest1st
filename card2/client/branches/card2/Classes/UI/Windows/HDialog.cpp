//
//  HDialog.cpp
//  card
//
//  Created by zhou gang on 13-7-11.
//
//

#include "../../headers.h"
#include "HRootScene.h"
#include "HDialog.h"

HDialog::HDialog()
{
    
}

HDialog::~HDialog()
{
    
}

HWindow* HDialog::getOwnner()
{
    HWindow* ownner = NULL;
    CCNode* ui = this->scene()->getUIShowLayer();
    for (int i=ui->getChildrenCount()-1; i>=0; i--) {
        HWindow* wnd = (HWindow*)ui->getChildren()->objectAtIndex(i);
        if (wnd == this) {
            while (i>0){
                HWindow* prewnd = (HWindow*)ui->getChildren()->objectAtIndex(--i);
                if (!prewnd->isDialog()) {
                    ownner = prewnd;
                    break;
                }
            }
            
            if (ownner == NULL) {
                ownner = this->scene()->getGameShowLayer();
            }
            
            break;
        }
    }
    
    return ownner;
    
}

void HDialog::setVisible(bool visible)
{
    super::setVisible(visible);
    
//    CCNode* ui = this->scene()->getUIShowLayer();
//    for (int i=ui->getChildrenCount()-1; i>=0; i--) {
//        HWindow* wnd = (HWindow*)ui->getChildren()->objectAtIndex(i);
//        if (wnd == this) {
//            HWindow* prewnd = NULL;
//            if (i > 0) {
//                prewnd = (HWindow*)ui->getChildren()->objectAtIndex(--i);
//            }
//            else {
//                prewnd = this->scene()->getGameShowLayer();
//            }
//            
//            prewnd->setVisible(visible);
//            
//            break;
//        }
//    }
}

void HDialog::presentRootLayer(bool bAnima)
{
    HRootScene::current()->presentDialog(this, bAnima);
}

void HDialog::dismissRootLayer(bool bAnima)
{
    HRootScene::current()->dissmisDialog(this, bAnima);
}

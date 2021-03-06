//
//  UpdateLayer.h
//  card
//
//  Created by bo wei on 13-6-20.
//
//

#ifndef __card__UpdateLayer__
#define __card__UpdateLayer__

#include <iostream>


#include "headers.h"

class HUpdateWindow: public HWindow, public HMessageDelegate
{
    HUICLASS_DELARE(HUpdateWindow, HWindow)
    
public:
    virtual bool init();
    virtual void resetUI(bool bfisrt  = false);    
    
    virtual void onOK(HMessageBox* sender);
    
    virtual void update	(	float 	delta	);
private:
    void updateProgress();
    void restart();
    
    __assign CCLabelTTF* m_pMsg;
    __assign CCLabelTTF* m_pLoadingLabel;
    __assign CCProgressTimer* m_pLoadingLine;
    
};


#endif /* defined(__card__UpdateLayer__) */

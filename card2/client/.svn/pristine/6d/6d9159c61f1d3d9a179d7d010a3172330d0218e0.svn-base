//
//  headers.h
//  card2
//
//  Created by zhou gang on 14-2-10.
//
//


#include "cocos2dxframework.h"
#include "GameScene.h"
#include "AppDelegate.h"
#include "carddef.h"

USING_HNAMESPACE;

#define HMUSIC_LOGIN              0
#define HMUSIC_BG                    1
#define HMUSIC_BUTTON           2
#define HMUSIC_DIALOG           3
#define HMUSIC_BATTLE1           4
#define HMUSIC_BATTLE2            5
#define HMUSIC_BATTLE_BOSS          6
#define HMUSIC_HELL                 7
#define HMUSIC_REPLAY               8
#define HMUSIC_AWAKE                9
#define HMUSIC_CHRISTMAS            10
#define HMUSIC_NEWYEAR            11

#define MAX_STAR    5
#define MAX_SKILL   4
#define MAX_CARD    10
#define MAX_MAGIC   4
#define MAX_LEVEL   100

#define CC_SYNTHESIZE_BOOL(varType, varName, funName)\
protected: varType varName;\
public: virtual varType is##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

#define CC_PROPERTY_BOOL(varType, varName, funName)\
protected: varType varName;\
public: virtual varType is##funName(void);\
public: virtual void set##funName(varType var) ;


#define CENTER(node) (ccpMult(ccpFromSize(node->getContentSize()), 0.5f))


class HGameManager;
extern HGameManager* g_Game;
extern HSourceCache* g_SourceCache;


#include "HCallFunc.h"

#include "HGameManager.h"
#include "HDataCenter.h"
#include "HLanguage.h"

#include "UIDefine.h"
#include "HPlistMgr.h"
#include "HCommonObject.h"

#include "HUserObject.h"
#include "HTextReader.h"

#include "HUserCard.h"
#include "HUserMagic.h"
#include "HUserMap.h"
#include "HUserBag.h"
#include "HPlayer.h"
#include "HConfig.h"
#include "HLocalString.h"

#include "HThreadTextureCache.h"
#include "CCProgressTimerLoader.h"
#include "HGrayProtocol.h"
#include "HRGBObject.h"
#include "HRichLabelTTF2.h"
#include "HRichSprite.h"
#include "HRichButton.h"
#include "HTableView.h"
#include "HTableViewCell.h"
#include "HTransformNode.h"

#include "HAnimaCenter.h"
#include "HLabelChangedCmd.h"
#include "HMoveNodeCmd.h"
#include "HShakeNodeCmd.h"
#include "HTransformCmd.h"

#include "HRootScene.h"
#include "HWindow.h"
#include "HDialog.h"
#include "HLoadingLayer.h"

#include "HLoadingWindow.h"
#include "UpdateLayer.h"

#include "HMessageBox.h"
#include "HNewbieGuide.h"
#include "HNewbieAction.h"

#include "HEffectHelper.h"
#include "HBattleController.h"



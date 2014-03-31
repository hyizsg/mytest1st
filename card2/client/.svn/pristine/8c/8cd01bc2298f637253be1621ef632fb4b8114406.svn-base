//
//  HMoveNodeCmd.h
//  card
//
//  Created by zhou gang on 13-3-26.
//
//

#ifndef __card__HMoveNodeCmd__
#define __card__HMoveNodeCmd__

class HMoveNodeCmd : public HAnimaCommand {
    HCLASSTYPE(HMoveNodeCmd, HAnimaCommand);
    
public:
    HMoveNodeCmd(CCNode* target, CCNode* middle, CCNode* to, CMD_ARGS);
    virtual ~HMoveNodeCmd();
    
    static HMoveNodeCmd* create(CCNode* target, CCNode* middle, CCNode* to, CMD_DEFAULT_ARGS = 0.15f);
    static HMoveNodeCmd* create(CCNode* target, CCNode* middle, CCNode* to, const CCPoint& postion, CMD_DEFAULT_ARGS = 0.15);
    
    virtual void begin();
    virtual void update(float delta);
    virtual void end();
    
public:
    CCNode* m_middle;
    CCNode* m_to;
    CCPoint m_position;
    CCNode* m_rootChild;
    
    CCPoint m_from_point;
    CCPoint m_to_point;
    
    int m_parent_zIndex;
};

#endif /* defined(__card__HMoveNodeCmd__) */

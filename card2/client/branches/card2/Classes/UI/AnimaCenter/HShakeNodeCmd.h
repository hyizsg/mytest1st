//
//  HShakeNodeCmd.h
//  card
//
//  Created by zhou gang on 13-5-9.
//
//

#ifndef __card__HShakeNodeCmd__
#define __card__HShakeNodeCmd__

class HShakeNodeCmd : public HAnimaCommand {
    
    
public:
    HShakeNodeCmd(CCNode* target, CMD_ARGS);
    virtual ~HShakeNodeCmd();
    
    static HShakeNodeCmd* create(CCNode* target, int times, float offx=3, float offy=0, CMD_DEFAULT_ARGS = 0.1f);
    
    virtual void begin();
    virtual void update(float delta);
    virtual void end();
    virtual bool isOver();
    
protected:
    int m_offx, m_offy;
    
    float m_beginx, m_beginy;
    float m_endx, m_endy;
    
    int m_times;
    CCNode* m_rootChild;
};

#endif /* defined(__card__HShakeNodeCmd__) */

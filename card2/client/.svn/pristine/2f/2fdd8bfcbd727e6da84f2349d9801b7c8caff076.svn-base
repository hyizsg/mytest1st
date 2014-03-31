//
//  HAnimaCenter.h
//  card
//
//  Created by zhou gang on 13-3-26.
//
//

#ifndef __card__HAnimaCenter__
#define __card__HAnimaCenter__

class HAnimaCommand;

class HAnimaDelegate {
    
public:
    virtual void onAnimaEnd(HAnimaCommand* cmd) = 0;
};

typedef enum { AF_None, AF_Dead, AF_Dead2, AF_Grave2Bat, AF_MoveNode, AF_MoveToWait, AF_MoveToStack, AF_Attack, AF_Damage, AF_DamageHide, AF_DamageLine, AF_DelAtk, AF_MoveToSelect, AF_MoveToUnSelect, AF_SkillName, AF_Max} AnimaFlag;

#define CMD_DEFAULT_ARGS    HAnimaDelegate* delegate=NULL, AnimaFlag flag=AF_None, double duration
#define CMD_ARGS            HAnimaDelegate* delegate, AnimaFlag flag, double duration

class HAnimaCommand : public CCObject
{
    CC_SYNTHESIZE_RETAIN(CCNode*, m_pTarget, Target);
    CC_SYNTHESIZE(HAnimaDelegate*, m_pDelegate, Delegate);
    CC_SYNTHESIZE(double, m_total_time, TotalTime)
    CC_SYNTHESIZE(AnimaFlag, m_flag, Flag);
    CC_SYNTHESIZE(double, m_duration, Duration);
    
public:
    HAnimaCommand(CCNode* target = NULL, CMD_DEFAULT_ARGS = 0.3f);
    virtual ~HAnimaCommand();
    
    virtual void begin();
    virtual void update(float delta);
    virtual void end();
    virtual bool isOver();

    virtual bool isKindOf(const std::string &name) { return name == "HAnimaCommand"; }
    
    template <typename T> inline T lerp(T from, T to)
    {
        float t = fabs(m_duration) < 1e-3 ? 0 : clampf(m_total_time / m_duration, 0, 1);
        return (T)clampf((from * (1-t) + to * t), from, to);
    }
};

class HAnimaCenter : public CCNode {
    HSINGLETON_OBJECT(HAnimaCenter);
    
private:
    virtual void update(float fDelta);
    virtual void onExit() {}
    
public:
    static void play(HAnimaCommand* cmd)
    {
        cmd->begin();
        getInstance()->m_cmd_cache->addObject(cmd);
    }
    
protected:
    __retain CCArray* m_cmd_cache;
    __retain CCTimer* m_timer;

    
};

class HAnimaProtocol
{
public:
    virtual bool isAnimaing() = 0;
    virtual void setAnimaing(bool bAnimaing) = 0;
};

class HAnimaObject : public HAnimaProtocol
{    
    
public:
    HAnimaObject() : m_bAnimaing(false) {}
    ~HAnimaObject(){}
    virtual bool isAnimaing() { return m_bAnimaing; }
    virtual void setAnimaing(bool bAnimaing) { m_bAnimaing = bAnimaing; }
    
protected:
    bool m_bAnimaing;
};





#endif /* defined(__card__HAnimaCenter__) */

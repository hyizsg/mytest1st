//
//  HTransformCmd.h
//  card
//
//  Created by zhou gang on 13-4-2.
//
//

#ifndef __card__HTransformCmd__
#define __card__HTransformCmd__

class HTransformCmd : public HAnimaCommand {
    HCLASSTYPE(HTransformCmd, HAnimaCommand)
    
public:
    typedef enum
    {
        None = 0,
        Translate = 0x01,
        Position = Translate << 1,
        Scale = Position << 1,
        Rotation = Scale << 1,
        Skew = Rotation << 1,
        Alpha = Skew << 1, //value: 0 ~ 1
    } CmdType;
    
public:

    
    HTransformCmd(CCNode* target, CMD_ARGS);
    static HTransformCmd* create(CCNode* target, float tx, float ty, int type, CMD_DEFAULT_ARGS = 0.3f);

    
public:
    virtual void begin();
    virtual void update(float delta);
    
public:
    CCPoint m_origin;
    CCPoint m_target;
    
    int m_type;
};

#endif /* defined(__card__HTransformCmd__) */

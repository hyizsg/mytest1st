//
//  HLabelChangedCmd.h
//  card
//
//  Created by zhou gang on 13-3-26.
//
//

#ifndef __card__HLabelChangedCmd__
#define __card__HLabelChangedCmd__

class HLabelChangedCmd : public HAnimaCommand {
    HCLASSTYPE(HLabelChangedCmd, HAnimaCommand);
public:
    HLabelChangedCmd(CCNode* pTarget, int orgin_num, int target_num, const char* format, HAnimaDelegate* delegate);
    virtual ~HLabelChangedCmd();
    
    static HLabelChangedCmd* create(CCNode* pTarget, int orgin_num, int target_num, const char* format, HAnimaDelegate* delegate, AnimaFlag flag = AF_None);
    
    virtual void begin();
    virtual void update(float delta);
    
public:
    int m_orgin_num;
    int m_target_num;
    int m_flag;
    CCString* m_format;
    
    double m_text_num;
};

class HLabelChangel : public CCActionInterval
{
public:
    
    HLabelChangel();
    virtual ~HLabelChangel();
    
    virtual void update(float dt);
    virtual void startWithTarget(CCNode *pTarget);
    
    static HLabelChangel* create(float dur, int org_num, int tar_num, const char* format);
    bool init(float dur, int org_num, int tar_num, const char* format);
    
public:
    int m_orgin_num;
    int m_target_num;
    int m_flag;
    CCString* m_format;
    
    double m_text_num;
 
};

#endif /* defined(__card__HLabelChangedCmd__) */

//
//  HCommonObject.h
//  card2
//
//  Created by zhou gang on 14-2-11.
//
//

#ifndef __card2__HCommonObject__
#define __card2__HCommonObject__

class HCommonObject
{
    
public:
    HCommonObject();
    virtual ~HCommonObject();
    
    void startAIV();
    void stopAIV();
    
    virtual void messageBox(const char* msg);
    
    virtual void notifyActionMsg(CCObject* obj);
    virtual void addObserver(int cmdid);
    virtual void addObserver(const char* cmdstr);
    virtual void addObserver(SEL_CallFuncO sel, int cmdid);
    virtual void addObserver(SEL_CallFuncO sel, const char* cmdstr);
    
    static void post(HDataRequest* request);
    static void post(int cmdId, CCDictionary* param = NULL);
    
    static void playButtonSound();
    static void playSoundById(int id);
    
    
protected:
    vector<string> m_observers;
    
};

#endif /* defined(__card2__HCommonObject__) */

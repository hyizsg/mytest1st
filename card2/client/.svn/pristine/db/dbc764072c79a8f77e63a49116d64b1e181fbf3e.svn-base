#ifndef _UI_LAYER_H_
#define _UI_LAYER_H_

HNAMESPACE_BEGIN

void setDurationOfFadeInOut(float fin, float fout);

class CC_DLL HUILayer: public HCommonLayer {
    HCLASSTYPE(HUILayer, HCommonLayer);
public:
    HUILayer();
    virtual ~HUILayer();
    
    void presentRootLayer(HRootLayer *layer, bool inQueue = false);
    void dismissRootLayer(HRootLayer *layer);
    
    void dismissAllRootLayers();
    
    void backupAllRootLayers();
    void restoreAllRootLayers();
    
    bool onBackPressed();
    bool onMenuPressed();
    
    HRootLayer *findWithClass(const std::string &className);
    
    virtual void onOK();
    
    virtual void animOutEnd();
private:    
    CCArray *m_pQueneRootLayers;
    CCArray *m_pRecycledRootLayers;
    CCArray *m_pBackupRootLayer;
    
    HRootLayer *m_pCurrentLayer;
    HRootLayer *m_pPreEndingLayer;
    
    void updateAllRootLayers();
    
    void stopMaskAnimation();
    void endPresentFadeIn();
    void endPresentFadeOut();
    void endDismissFadeIn();
    void endDismissFadeOut();
};

HNAMESPACE_END

#endif // _UI_LAYER_H_

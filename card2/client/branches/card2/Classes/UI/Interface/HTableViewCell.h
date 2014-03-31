//
//  HTableViewCell.h
//  BattleShip
//
//  Created by huangwei on 10/26/12.
//
//

#ifndef __BattleShip__CCTableViewCommonCell__
#define __BattleShip__CCTableViewCommonCell__

class CC_DLL HTableViewCell:public CCTableViewCell, public HRGBObject, public HGrayObject, public CCBMemberVariableAssigner ,public CCBSelectorResolver//public HRootLayer,
{
public:
    HTableViewCell(const char*fileName);
    HTableViewCell();
    virtual ~HTableViewCell();
    
    virtual bool init() {return true;}
    virtual void clear();
    
    static HTableViewCell *create(const char*fileName);
    static HTableViewCell *create();
    static CCSize GetCellSize(const char*fileName);
    
    
    
    CC_SYNTHESIZE(CCNode*, m_pRootChild, RootChild);
    CC_PROPERTY(int, m_iBaseTouchPriority, BaseTouchPriority);
    
    void updateAndAdjust(CCNode *node, float scaleX, float scaleY);
    
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    
    
    CCSize m_cellSize;
    CCSize CellSize();
    
    void readNodeGraphFromFile(const char*fileName);
    void AddJSCCBNode(const char *ccbfile, CCNode* node);
    void ReadCell(HTableViewCell*oldCell);
    
    bool isKindOf(std::string name) { return name == "HTableViewCell"; }
    CCSprite *cloneSprite(CCSprite *pPrototype);
    CCLabelTTF *cloneLabelTTF(CCLabelTTF *pPrototype);
    
    void updatePriorityTouchLayer(CCNode *node);
    //HProgressBar * cloneProgressBar(HProgressBar *pPrototype );
    

};

class HTableViewCellLoader : public CCNodeLoader
{
public:
    virtual ~HTableViewCellLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HTableViewCellLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HTableViewCell);
};

class HCellHelper  {
    HSINGLETON_OBJECT(HCellHelper);

protected:
    static CCDictionary* s_cellCache;
    
public:
    template<class T>
    T* popCell()
    {
        printf("Cocos2d: HCellHelper - pop cell: ");
        T* pRet = NULL;
        CCArray* list = PARSE_ARR(s_cellCache, T::getCCBI());
        
        if (list != NULL) {
            FOREACH(HTableViewCell*, cell, list) {
                T* item = dynamic_cast<T*>(cell);
                if (item && item->retainCount() == 1) {
                    pRet = item; pRet->clear();
                    printf("\t%s\tin cache", T::getCCBI());
                    break;
                }
            }
        }
        
        if (pRet == NULL) {
            pRet = T::create();
            pushCell(pRet);
            printf("\t%s\tin create", T::getCCBI());
        }
        
        printf("\t\t0x%x\n", (int)(pRet));
        
        return pRet;
    }
    
    void CCLog(const char* format, ... ) {}
    void printf(const char* format, ... ){}
    
    template<class T>
    void pushCell(T* node)
    {
        CCArray* list = PARSE_ARR(s_cellCache, T::getCCBI());
        
        if (list == NULL) {
            list = CCArray::create();
            s_cellCache->setObject(list, T::getCCBI());
        }
        
        if (!list->containsObject(node)) {
            list->addObject(node);
        }
    }
    
    void recycle(bool bForce)
    {
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(s_cellCache, pElement)
        {
            CCArray* list = PARSE_ARR(s_cellCache, pElement->getStrKey());
            FOREACH(HTableViewCell*, cell, list) {
                if (bForce || cell->retainCount() == 1) {
                    CCLog("\trecycle %s: 0x%x", pElement->getStrKey(), (unsigned)cell);
                    cell->clear();
                }else{
                    CCLog("\tkeep %s:0x%x", pElement->getStrKey(), (unsigned)cell);
                }
            }
        }
    }
    
    void recycle(CCNode* root)
    {
        HTableViewCell* cell = dynamic_cast<HTableViewCell*>(root);
        if (cell) {
            cell->clear();
            return;
        }
        
        CCArray* children = root->getChildren();
        FOREACH(CCNode*, child, children){
            recycle(child);
        }
    }
};


template<class T> static inline 
T* popCell() {
    return HCellHelper::getInstance()->popCell<T>();
}

static inline
void recycleCell(bool bForce = false) {
    HCellHelper::getInstance()->recycle(bForce);
}

static inline
void recycleCell(CCNode* root) {
    HCellHelper::getInstance()->recycle(root);
}

#endif /* defined(__BattleShip__CCTableViewCommonCell__) */

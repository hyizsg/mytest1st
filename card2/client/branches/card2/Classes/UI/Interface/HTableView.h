//
//  HTableView.h
//  card
//
//  Created by zhou gang on 13-4-8.
//
//

#ifndef __card__HTableView__
#define __card__HTableView__

class HTableView;

class HTableViewDelegate
{
    
public:
    virtual void tableCellTouched(HTableView* table, CCNode* cell) = 0;
};

class HTableViewDataSource
{
    
public:
    virtual CCSize cellSizeForTable(HTableView *table) { return  CCSizeZero; }
    virtual float cellHeightForTable(HTableView *table) = 0;
    virtual CCNode* tableCellAtIndex(HTableView *table, unsigned int idx) = 0;
    virtual unsigned int numberOfCellsInTableView(HTableView *table) = 0;
    virtual unsigned int numberOfCellsInRow(HTableView* table) = 0;
};

class HTableCellCheckingTouch {
    
    
public:
    // don't handle the touch when returning true
    virtual bool checkTouch(CCTouch *pTouch, CCEvent *pEvent) = 0;
};

class HTableView : public CCTableView
{
    
public:
    HTableView();
    virtual ~HTableView();
    
    static HTableView* create(HTableViewDataSource* dataSource, CCSize size, CCNode *container = NULL);
    
    void reloadData(bool scrollTobegin = false);
    CCNode* dequeueCell();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    
    class HTableViewImp : public CCObject, public CCTableViewDataSource, public CCTableViewDelegate {
        
        virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
        virtual CCSize cellSizeForTable(CCTableView *table);
        virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
        virtual unsigned int numberOfCellsInTableView(CCTableView *table);
        
        virtual void scrollViewDidScroll(CCScrollView* view){}
        virtual void scrollViewDidZoom(CCScrollView* view){}
    };
    

public:
    bool isKindOf(std::string name) { return name == "HTableView"; }
    
    CC_SYNTHESIZE(HTableViewDataSource*, m_hDataSource, HDataSource);
    CC_SYNTHESIZE(HTableViewDelegate*, m_hDelegate, HDelegate);
    
protected:
    __assign int m_cellCount;
    __assign int m_colCount;
    __assign int m_rowCount;
    __assign float m_cellHeight;
    
    __assign CCNode* m_dequeueNode;
    __retain CCTouch* m_pTouch;
    
    __assign int m_oldRowCount;
    __retain HTableViewImp* m_selfDelegate;
    
    friend class HTableViewImp;
    
};

class CCTableViewLoader2 : public CCScrollViewLoader {
    
public:
    virtual ~CCTableViewLoader2() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCTableViewLoader2, loader);
    
    virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {}
    virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader) { }
    virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {}
    
protected:
    virtual CCTableView * createCCNode(CCNode * pParent, CCBReader * pCCBReader)
    {
        CCTableView* table = CCTableView::create(dynamic_cast<CCTableViewDataSource*>(pCCBReader->getOwner()), CCSizeMake(100, 100));
        table->setDelegate(dynamic_cast<CCTableViewDelegate*>(pCCBReader->getOwner()));
        table->setVerticalFillOrder(kCCTableViewFillTopDown);
        return table;
    }
};

class HTableViewLoader : public CCTableViewLoader2 {
    
public:
    virtual ~HTableViewLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HTableViewLoader, loader);
    
protected:
    virtual HTableView * createCCNode(CCNode * pParent, CCBReader * pCCBReader)
    {
        HTableView* table = HTableView::create(dynamic_cast<HTableViewDataSource*>(pCCBReader->getOwner()), CCSizeMake(100, 100));
        table->setHDelegate(dynamic_cast<HTableViewDelegate*>(pCCBReader->getOwner()));
        table->setVerticalFillOrder(kCCTableViewFillTopDown);
        return table;
    }
};


#endif /* defined(__card__HTableView__) */

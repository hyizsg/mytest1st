//
//  HTableView.cpp
//  card
//
//  Created by zhou gang on 13-4-8.
//
//

#include "../../headers.h"

HTableView::HTableView()
: m_hDelegate(NULL)
, m_pTouch(NULL)
{
    m_oldRowCount = m_rowCount = 0;
    m_selfDelegate = new HTableViewImp;
}

HTableView::~HTableView()
{
    CC_SAFE_RELEASE(m_pTouch);
    CC_SAFE_RELEASE(m_selfDelegate);
}

HTableView* HTableView::create(HTableViewDataSource* dataSource, CCSize size, CCNode* container)
{
    HTableView *table = new HTableView();
    table->initWithViewSize(size, container);
//    table->autorelease();
    CC_AUTO_RELEASE(table);
    table->setHDataSource(dataSource);
    table->setDataSource(table->m_selfDelegate);
    table->_updateContentSize();
    
    return table;
}

void HTableView::reloadData(bool scrollToBegin)
{
    setDataSource(m_selfDelegate);
    setDelegate(m_selfDelegate);
    
    if (m_hDataSource != NULL) {
        
        m_cellCount = m_hDataSource->numberOfCellsInTableView(this);
        m_colCount = m_hDataSource->numberOfCellsInRow(this);
        m_rowCount = m_cellCount <= 0 || m_colCount <= 0 ? 0 : (m_cellCount - 1) / m_colCount + 1;
        
        if (scrollToBegin || (m_eDirection != kCCScrollViewDirectionHorizontal && m_oldRowCount != m_rowCount)) {
            m_eOldDirection = kCCScrollViewDirectionNone;
        }
        
        if (m_eOldDirection != m_eDirection)
        {
            if (m_eDirection != kCCScrollViewDirectionHorizontal &&
                m_eVordering == kCCTableViewFillBottomUp)
            {
                m_eOldDirection = m_eDirection;
                m_pContainer->setPosition(0, 0);
            }
        }
        
        CCTableView::reloadData();
        
        m_oldRowCount = m_rowCount;
    }
}

CCNode* HTableView::dequeueCell()
{
    return m_dequeueNode;
}

void HTableView::HTableViewImp::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    HTableView* pTable = (HTableView*)table;
    if (!pTable->isVisible() || pTable->m_hDelegate == NULL) {
        return;
    }
    
    if (!pTable->isVisible() || !cell->isVisible()) {
        return;
    }
    
    
    if (pTable->m_pTouches->count() == 1 && !pTable->isTouchMoved()) {

        if (pTable->m_eDirection == kCCScrollViewDirectionHorizontal) {
            
            HTableCellCheckingTouch* check = dynamic_cast<HTableCellCheckingTouch*>(cell);
            if (check == NULL || !check->checkTouch(pTable->m_pTouch, NULL)) {
                pTable->m_hDelegate->tableCellTouched(pTable, cell);
            }
        }
        else //if (m_eDirection == kCCScrollViewDirectionVertical)
        {
//            CCPoint point = pTable->m_pTouch->getLocation();
//            CCRect frame;
            
            for (int i=0; i<cell->getChildrenCount(); i++) {
                CCNode* node = (CCNode*)cell->getChildren()->objectAtIndex(i);
                if (node->isVisible() && isTouchInside(pTable->m_pTouch, node)) {
                    HTableCellCheckingTouch* check = dynamic_cast<HTableCellCheckingTouch*>(node);
                    if (check == NULL || !check->checkTouch(pTable->m_pTouch, NULL)) {
                        pTable->m_hDelegate->tableCellTouched(pTable, node);
                    }
                    break;

                }
            }
        }
    }
}

CCSize HTableView::HTableViewImp::cellSizeForTable(CCTableView *table)
{
    HTableView* pTable = (HTableView*)table;
    if (pTable->m_eDirection == kCCScrollViewDirectionHorizontal) {
        
        return pTable->m_hDataSource->cellSizeForTable(pTable);
    }
    else //if (m_eDirection == kCCScrollViewDirectionVertical)
    {
        pTable->m_cellHeight = pTable->m_hDataSource->cellHeightForTable(pTable);
        return CCSizeMake(pTable->m_obContentSize.width, pTable->m_cellHeight);
    }
}

CCTableViewCell* HTableView::HTableViewImp::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    HTableView* pTable = (HTableView*)table;
    CCTableViewCell* cell = table->dequeueCell();
    
    if (pTable->m_eDirection == kCCScrollViewDirectionHorizontal) {
        pTable->m_dequeueNode = cell;
        if(cell)cell->setVisible(true);
        cell = dynamic_cast<CCTableViewCell*>(pTable->m_hDataSource->tableCellAtIndex(pTable, idx));
    }
    else //if (m_eDirection == kCCScrollViewDirectionVertical)
    {
        if (cell == NULL) {
            cell = new CCTableViewCell;
            cell->setContentSize(CCSizeMake(pTable->m_obContentSize.width, pTable->m_cellHeight));
//            cell->autorelease();
            CC_AUTO_RELEASE(cell);
        }
        
        FORUP(i, pTable->m_colCount) {
            CCNode* node = NULL;
            if (idx * pTable->m_colCount + i < pTable->m_cellCount) {
                if (cell->getChildrenCount() > i) {
                    pTable->m_dequeueNode = (CCNode*)cell->getChildren()->objectAtIndex(i);
                    pTable->m_dequeueNode->setVisible(true);
                    node = pTable->m_hDataSource->tableCellAtIndex(pTable, idx * pTable->m_colCount + i);
                    
                    if (node == pTable->m_dequeueNode) {
                        continue;
                    }
                    
                    pTable->m_dequeueNode->removeFromParent();
                    
                }else{
                    pTable->m_dequeueNode = NULL;
                    node = pTable->m_hDataSource->tableCellAtIndex(pTable, idx * pTable->m_colCount + i);
                }
                
                cell->addChild(node);
                float length = pTable->m_obContentSize.width / pTable->m_colCount;
                float xOfViews = (length - node->getContentSize().width * node->getScaleX()) / 2;
                node->setPosition(i*length + xOfViews, 0);
                node->setTag(idx * pTable->m_colCount + i);
                
            }else{
                if (cell->getChildrenCount() > i) {
                    ((CCNode*)cell->getChildren()->objectAtIndex(i))->setVisible(false);
                }
            }
        }
;
    }
    
        
    return cell;
}

unsigned int HTableView::HTableViewImp::numberOfCellsInTableView(CCTableView *table)
{
    HTableView* pTable = (HTableView*)table;
    if (pTable->m_eDirection == kCCScrollViewDirectionHorizontal) {
        
        return pTable->m_cellCount;
    }
    else //if (m_eDirection == kCCScrollViewDirectionVertical)
    {
        return pTable->m_rowCount;
    }
}

void HTableView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    HC_SET(m_pTouch, pTouch);
    CCTableView::ccTouchEnded(pTouch, pEvent);
    
//    if (!this->isVisible()) {
//        return;
//    }
//    
//    if (m_pTouchedCell){
//        if (isTouchInside(pTouch, m_pTouchedCell))
//        {
//            m_pTableViewDelegate->tableCellUnhighlight(this, m_pTouchedCell);
//            m_pTableViewDelegate->tableCellTouched(this, m_pTouchedCell);
//        }
//        
//        m_pTouchedCell = NULL;
//    }
//    
//    CCScrollView::ccTouchEnded(pTouch, pEvent);
}

bool HTableView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
//    if (getDirection() == kCCScrollViewDirectionNone) {
//        return true;
//    }
    return CCTableView::ccTouchBegan(pTouch, pEvent);
}

void HTableView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (getDirection() == kCCScrollViewDirectionNone) {
        return;
    }
    return CCTableView::ccTouchMoved(pTouch, pEvent);
}

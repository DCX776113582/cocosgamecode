//
//  GoodsShelf.h
//  AnimalAid
//
//  Created by mac on 14-11-15.
//
//

#ifndef __AnimalAid__GoodsShelf__
#define __AnimalAid__GoodsShelf__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SuperShopScene.h"
#include "YJNotificationCenter.h"
USING_NS_CC;
USING_NS_CC_EXT;
class GoodsShelf:public SuperShopScene , public TableViewDataSource , public TableViewDelegate,public YJObserver

{
public:
    static Scene * CreateScene( int type);
    virtual bool initWithType(int type);
    virtual void back();
    static  int typeN;
    static  int notHidden;
    ~GoodsShelf();
    //tableviewDataSource
    
    void tableCellTouched(TableView* table, TableViewCell* cell);
    
    void tableCellHighlight(TableView* table, TableViewCell* cell);
    
    void tableCellUnhighlight(TableView* table, TableViewCell* cell);
    
    
    //tableviewdelegate
    
    Size cellSizeForTable(TableView *table);
    
    TableViewCell tableCellAtIndex(TableView *table, unsigned int idx);
    
     int numberOfCellsInTableView(TableView *table);
    
    void scrollViewDidScroll(ScrollView* view);
    
    void scrollViewDidZoom(ScrollView* view);
    //通知者
    virtual void notifyUpdate();
    void reloadMyTable(int idx);
    //触摸操作
    
    bool onTouchBegan(Touch *pTouch, Event *pEvent);
    
    void onTouchMoved(Touch *pTouch, Event *pEvent);
    
    void onTouchEnded(Touch *pTouch, Event *pEvent);
    
    void onTouchCancelled(Touch *pTouch, Event *pEvent);
    
    virtual void onExit();

    void getGoodsMessage(int type);
    
    void setMoney(char * money);
    
    //设置第一个木板为选择状态
    void setFirstBoard();
    
private:
    
    CCLabelBMFont * moneyLabel;
    int type;
    CCArray * arrayPic;
    CCArray * arrayGoods;
    CCTableView * tableView;
};
#endif /* defined(__AnimalAid__GoodsShelf__) */

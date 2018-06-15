//
//  GoodsShelf.cpp
//  AnimalAid
//
//  Created by mac on 14-11-15.
//
//

#include "GoodsShelf.h"
#include "ChooseItem.h"
#include "GoodsItem.h"
#include "ShopScene.h"
#include "CommonDefine.h"
#include "GameDataCenter.h"
#define WIN_SIZE_WIDTH 510
#define WIN_SIZE_HEIGHT 368
#define TABLEVIEW_CELL_NUM 5
#define CELL_SIZE_WIDTH 127.5
int GoodsShelf:: typeN = -1;
int GoodsShelf:: notHidden = -1;
CCScene * GoodsShelf:: CreateScene( int type)
{
    CCScene * scene = CCScene::create();
    GoodsShelf * layer = new GoodsShelf();
    layer->initWithType(type);
    scene->addChild(layer);
    return scene;
    
}
bool GoodsShelf:: initWithType(int type)
{
    
    if (!SuperShopScene::init())
    {
        return false;
    }
    NOTIFICATION_CENTER->attachObserver(this, "hiddenOtherItems");
    NOTIFICATION_CENTER->attachObserver(this, "reload");
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("CoinNum", 300);
    VSIZE;
    arrayPic = CCArray::createWithCapacity(30);
    arrayGoods = CCArray::createWithCapacity(30);
    arrayGoods->retain();
    this->getGoodsMessage(type);
    
    
    
    typeN = type;
    this->type = type;
    
    //声明一个tableView
    tableView = CCTableView::create(this, CCSizeMake(WIN_SIZE_WIDTH, WIN_SIZE_HEIGHT));
    tableView->setDirection(kCCScrollViewDirectionHorizontal);
    tableView->setDelegate(this);
    
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    tableView->setPosition(CCPointZero);
    this->addChild(tableView);
    
    //添加金钱标签
    char moneyStr[10];
    
    sprintf(moneyStr, "%d", DATA_CENTER->m_moneyNum);
    moneyLabel = CCLabelBMFont::create(moneyStr, "uiImage/font.fnt");
    moneyLabel->setPosition(ccp( vsize.width - moneyLabel->getContentSize().width, vsize.height - moneyLabel->getContentSize().height));
    this->addChild(moneyLabel);

    return true;
}

//tableviewDataSource

void GoodsShelf:: tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("第%d行",cell->getIdx());
}

void GoodsShelf:: tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
    
}
void GoodsShelf:: tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
   //cell->removeChildByTag(1);
}


//tableviewdelegate

CCSize GoodsShelf:: cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(CELL_SIZE_WIDTH, WIN_SIZE_HEIGHT);
}

CCTableViewCell * GoodsShelf::  tableCellAtIndex(CCTableView *table, unsigned int idx)
{
//    CCLog("idx= %d",idx);
    CCTableViewCell * cell = table->dequeueCell();
    if (!cell)
    {
        cell = new CCTableViewCell();
        cell ->autorelease();
    }
   
    //添加背景
    //cell->removeAllChildren();
    CCLog("type = %d typeN = %d  idx = %d",type,typeN,idx);
    CCString * str = (CCString *)arrayPic->objectAtIndex(idx);
    const  char * picStr = str->getCString();
    
    GoodsItem * goodsItem = new GoodsItem(picStr,typeN,idx);
    goodsItem->setAnchorPoint(CCPointZero);
    goodsItem->setPosition(CCPointZero);
    cell->addChild(goodsItem);
    arrayGoods->addObject(goodsItem);
    return cell;
}
void GoodsShelf:: setMoney(char* money)
{
    moneyLabel->setString(money);
    
}
void GoodsShelf:: getGoodsMessage(int type)
{
    CCArray * array = CCArray::createWithContentsOfFile("GoodsMessage.plist");
//    CCLog("type = %d",type);
    arrayPic= (CCArray *)array->objectAtIndex(type-1);
    arrayPic->retain();
//    CCLog("array->count= %d",arrayPic->count());
    
                             
}
unsigned int GoodsShelf:: numberOfCellsInTableView(CCTableView *table)
{
    return TABLEVIEW_CELL_NUM;
}

void GoodsShelf:: scrollViewDidScroll(CCScrollView* view){}
void GoodsShelf:: scrollViewDidZoom(CCScrollView* view){}
//触摸操作
bool GoodsShelf:: ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
void GoodsShelf:: ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){}

void GoodsShelf:: ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){}

void GoodsShelf:: ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){}

void GoodsShelf:: back()
{
    CCScene * scene = ShopScene::CreateScene();
    CCDirector::sharedDirector()->replaceScene(scene);
}

void GoodsShelf:: onExit()
{
    CCLayer::onExit();
    NOTIFICATION_CENTER->dttachObserver("hiddenOtherItems");
    SuperShopScene::onExit();
    
}

//取消选中状态
void GoodsShelf:: notifyUpdate()
{
    CCLog("列表中的个数：%d",arrayGoods->count());
    for (int i = 0 ; i < arrayGoods->count();  i ++)
    {
        GoodsItem * goodsItemTemp = ( GoodsItem *) arrayGoods->objectAtIndex(i);
//        CCLog("type = %d",type);
        if (goodsItemTemp->getType() == BRIDGES)
        {
//            CCLog("goodsNum = %d",goodsItemTemp->getGoodsNum());
              goodsItemTemp->hiddenLayerColor();
        }
    }
    
}
void GoodsShelf:: reloadMyTable(int idx)
{
    
    tableView->updateCellAtIndex(idx);

    
}
void GoodsShelf:: setFirstBoard()
{
   ((GoodsItem *)arrayGoods->objectAtIndex(0))->setApply();
}

GoodsShelf::~GoodsShelf()
{
    arrayGoods->release();
    arrayPic->release();
    
}
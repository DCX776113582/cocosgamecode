//
//  GoodsItem.cpp
//  AnimalAid1
//
//  Created by mac on 14-11-16.
//
//

#include "GoodsItem.h"
#include "ChooseItem.h"
#include "AnimateTools.h"
#include "CommonDefine.h"
#include "GameDataCenter.h"
#include "GoodsShelf.h"
int Price[] = {0,50,100,150,200};

GoodsItem:: GoodsItem(const char * picFile,int type,int goodsNum)
{
    
    this->type = type;//记录是哪一种商品
    this->goodsNum = goodsNum;
    char goodsTypeStr[10];
    sprintf(goodsTypeStr, "%d%d",type,goodsNum);
    goodsType = new char[10];
    strcpy(goodsType, goodsTypeStr);//记录这种商品的哪一个
    
    //添加购买按钮
    buyItem = CCMenuItemImage::create("shop/buy.png", "shop/buy.png",this, menu_selector(GoodsItem::buy));
    float x = this->getContentSize().width / 2;
    float y = this->getContentSize().height / 2;
    buyItem->setPosition(ccp(x, buyItem->getContentSize().height));
    
    
    turnOn = CCMenuItemImage::create("shop/apply1.png", "shop/apply1.png",this, menu_selector(GoodsItem::apply));
    turnOn->setPosition(buyItem->getPosition());

    CCMenuItemImage * turnOff = CCMenuItemImage::create("shop/apply2.png", "shop/apply2.png",this, menu_selector(GoodsItem::unApply));
    turnOff->setPosition(buyItem->getPosition());
    
    menu = CCMenu::create(turnOn,buyItem, NULL);
    menu->setAnchorPoint(CCPointZero);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
    
    //添加应用状态layer
    layerColor = CCLayerGradient::create(ccc4(255,0, 0, 80), ccc4(255,0 , 0, 15));
    layerColor->setContentSize(this->getContentSize());
    layerColor->setAnchorPoint(CCPointZero);
    layerColor->setPosition(CCPointZero);
    this->addChild(layerColor);
    
    CCMenu * menu1 = CCMenu::create(turnOff,NULL);
    menu1->setAnchorPoint(CCPointZero);
    menu1->setPosition(CCPointZero);

    layerColor->addChild(menu1);
    layerColor->setVisible(false);
    layerColor->retain();
    
    USER_DEFAULT;
    
    int hits =  GET_INT("hits");
    int bridge = GET_INT("bridge");
    if (hits == 0 && this->goodsNum == 0 && type == HITS)
    {
        //记录购买状态,第一个道具默认解锁
        SET_INT(goodsType ,2);
        SET_INT("hits", 1);
        layerColor->setVisible(true);
        buyItem->setVisible(false);
    }
    
    if (bridge == 0 && this->goodsNum == 0 && type == BRIDGES)
    {
        //记录购买状态,第一个道具默认解锁
        SET_INT(goodsType ,2);
        SET_INT("bridge", 1);
        layerColor->setVisible(true);
        buyItem->setVisible(false);
    }
    if (type == HITS &&  goodsNum == 0)
    {
        char hitApplyState[20];
        sprintf(hitApplyState, "hitapply%d",this->goodsNum);
        SET_BOOL(hitApplyState, true);
    }
    
    
    USER_FLUSH;
    int  state = GET_INT(goodsType);
    if(state == 1)
    {
        buyItem->setVisible(false);
        turnOn->setVisible(true);

    }
    else if(state == 0)
    {
        buyItem->setVisible(true);
        turnOn->setVisible(false);
    }
    else if(state == 2)
    {
        buyItem->setVisible(false);
        turnOn->setVisible(false);
        layerColor->setVisible(true);
        applyState = true;
        
    }
    //添加价格
    
    char priceStr[15];
    sprintf(priceStr, "%d",Price[goodsNum]);
    CCLabelBMFont * priceLabel = CCLabelBMFont::create(priceStr,"uiImage/font.fnt");
    
    priceLabel->setScale(1.5);
    priceLabel->setPosition(ccp(buyItem->getContentSize().width / 2,buyItem->getContentSize().height * 3));
    buyItem->addChild(priceLabel);
    
    //添加商品精灵
    goodsSprie = CCSprite::create(picFile);
    goodsSprie->setTag(goodsNum);
    goodsSprie->setPosition(ccp(x , y));
    if (type == HITS)
    {
        char picStr[20];
        sprintf(picStr, "man%drun_0",goodsNum+1);
        AnimateTools::runAction(goodsSprie,goodsNum+1);
        goodsSprie->setScale(2);
        
    }
    else if(type == PERKS || type == BRIDGES)
    {
        CCRotateBy * rotate = CCRotateBy::create(4, 360);
        CCRepeatForever * repeat = CCRepeatForever::create(rotate);
        goodsSprie->runAction(repeat);
    }
    this->addChild(goodsSprie);
    
}

GoodsItem:: ~GoodsItem()
{
    delete []goodsType;
    layerColor->release();
}

void GoodsItem:: buy()
{
    PLAY_EFFECT("music/button02.mp3");
    CCLog("money = %d",DATA_CENTER->m_moneyNum);
    int money = DATA_CENTER->m_moneyNum;
    
    
    CCLog("money = %d",DATA_CENTER->m_moneyNum);
    if (money - Price[goodsNum] >= 0)
    {
        DATA_CENTER->m_moneyNum -= Price[goodsNum];
        char moneyStr[10];
        sprintf(moneyStr, "%d",DATA_CENTER->m_moneyNum);
        ((GoodsShelf *)this->getParent()->getParent()->getParent()->getParent())->setMoney(moneyStr);
        buyItem->setVisible(false);
        turnOn->setVisible(true);
        
        //记录购买状态
        USER_DEFAULT;
        SET_INT(goodsType ,1);
        USER_FLUSH;
        
    }
    else
    {
        CCMessageBox("金钱不足", "提示");
        
    }
    
}

#pragma mark 应用此商品
void GoodsItem:: apply()
{
        PLAY_EFFECT("music/button02.mp3");
        //记录应用状态
        USER_DEFAULT;
        SET_INT(goodsType ,2);
//        CCLog("apply******** type= %d  bridge= %d  goodsNum = %d goodsType=%s",type,BRIDGES,goodsNum,goodsType);
        if(type == BRIDGES)
        {
            switch (goodsNum)
            {
                case  normalType:
                      DATA_CENTER->setBoardType(normalType);
                      break;
                    
                case  typeOne:
                      DATA_CENTER->setBoardType(typeOne);
                      break;
                    
                case  typeTwo:
                      DATA_CENTER->setBoardType(typeTwo);
                      break;
                    
                case  typeThree:
                      DATA_CENTER->setBoardType(typeThree);
                      break;
                    
                case  typeFour:
                      DATA_CENTER->setBoardType(typeFour);
                      break;
                    
                default:
                    break;
            }
            
            //将其余的选中项清除掉选中状态
            GoodsShelf::notHidden = goodsNum;
            
            NOTIFICATION_CENTER->notifyForKey("hiddenOtherItems");
            
            //将文件中的其它木板的状态修改为购买状态
            
            for (int i = 0; i <= 4; ++ i)
            {
                if (i != this->goodsNum)
                {
                    char str[10];
                    sprintf(str, "%d%d",type,i);
                    int state = GET_INT(str);
                    if (state != 0)
                    {
                        SET_INT(str, 1);
                        
                    }
                    
                }
            }
    }
    else if(type == HITS)
    {
        char hitApplyState[20];
        sprintf(hitApplyState, "hitapply%d",this->goodsNum);
        SET_BOOL(hitApplyState, true);
    }
    layerColor->setVisible(true);
    turnOn->setVisible(false);
    ((GoodsShelf *)this->getParent()->getParent()->getParent()->getParent())->reloadMyTable(this->goodsNum);
    
    CCLog("应用成功");
    USER_FLUSH;
}

#pragma mark 取消应用此商品
void GoodsItem:: unApply()
{
    PLAY_EFFECT("music/button02.mp3");
    layerColor->setVisible(false);
    CCLog("Unapply***** type=%d  goodsNum=%d goodstype= %s",type,goodsNum,goodsType);
    
    //记录取消应用状态
    USER_DEFAULT;
    SET_INT(goodsType ,1);
   
    if (type == HITS)
    {
        char hitApplyState[20];
        sprintf(hitApplyState, "hitapply%d",this->goodsNum);
        SET_BOOL(hitApplyState, false);
    }
    else if(type ==  BRIDGES)
    {
        
        ((GoodsShelf *)this->getParent()->getParent()->getParent()->getParent())->setFirstBoard();
        
    }
    turnOn->setVisible(true);
    ((GoodsShelf *)this->getParent()->getParent()->getParent()->getParent())->reloadMyTable(this->goodsNum);
    CCLog("取消应用成功");
    USER_FLUSH;
}

int GoodsItem:: getType()
{
    return type;
}

int GoodsItem:: getGoodsNum()
{
    return goodsNum;
}
char * GoodsItem:: getGoodsType()
{
    return goodsType;
}
bool GoodsItem:: getGoodsState()
{
    return applyState;
    
}
#pragma mark 隐藏选中状态
void GoodsItem:: hiddenLayerColor()
{
    layerColor->setVisible(false);
    USER_DEFAULT;
    int state = GET_INT(goodsType);
    USER_FLUSH;
    if (state != 0 )
    {
        turnOn->setVisible(true);
    }
}
//设置为应用状态
void  GoodsItem:: setApply()
{
    USER_DEFAULT;
    SET_INT("20", 2);
    USER_FLUSH;
    layerColor->setVisible(true);
    ((GoodsShelf *)this->getParent()->getParent()->getParent()->getParent())->reloadMyTable(0);
}


//
//  GoodsItem.h
//  AnimalAid1
//
//  Created by mac on 14-11-16.
//
//

#ifndef __AnimalAid1__GoodsItem__
#define __AnimalAid1__GoodsItem__

#include <iostream>
#include "cocos2d.h"
#include "SuperItem.h"
#include "YJNotificationCenter.h"
USING_NS_CC;

class GoodsItem : public SuperItem
{
public:
   
    GoodsItem(const char * picFile,int type,int goodsNum);
    ~GoodsItem();
    void buy();
    void apply();
    void unApply();
    int getType();
    char * getGoodsType();
    int getGoodsNum();
    bool getGoodsState();
    void hiddenLayerColor();
    
    //设置为应用状态
    void setApply();
private:
    int goodsNum;
    int type;
    char * goodsType;
    CCSprite * goodsSprie;
    CCMenuItemImage * buyItem;
    CCMenuItemToggle * applyItem;
    CCMenuItemImage * turnOn;
    CCLayerGradient * layerColor;
    CCMenu * menu ;
    bool allReadyBuy;
    bool applyState;
    
     
    
};
#endif /* defined(__AnimalAid1__GoodsItem__) */

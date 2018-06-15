//
//  ChooseItem.h
//  AnimalAid
//
//  Created by mac on 14-11-15.
//
//

#ifndef __AnimalAid__ChooseItem__
#define __AnimalAid__ChooseItem__

#include <iostream>
#include "cocos2d.h"
#include "SuperItem.h"
USING_NS_CC;

typedef enum
{
    HITS = 1,
    BRIDGES,
    PERKS,
    COINS
    
    
    
}itemType;

class ChoooseItem : public SuperItem
{
public:
    ChoooseItem(int type);
    ~ChoooseItem();
    void setType(int type);
    void initSomeThing(int type);
    void tobuyWhat();
    
    //让一个精灵执行一个设置好的旋转动作
    void runRepeatAction(CCSprite * sprite);
    
   
private:
    int type;
    CCSprite * typeSprite;
    CCSprite * nameSprite;
    CCSprite * starSprite;
    CCMenuItemImage * itemImage;
    
    
};
#endif /* defined(__AnimalAid__ChooseItem__) */

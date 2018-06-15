//
//  ChooseItem.cpp
//  AnimalAid
//
//  Created by mac on 14-11-15.
//
//

#include "ChooseItem.h"
#include "GoodsShelf.h"
#include "AnimateTools.h"
#include "CommonDefine.h"
ChoooseItem:: ChoooseItem(int type)
{
    this->type= type;
    this->initSomeThing(type);
}

void ChoooseItem:: initSomeThing(int type)
{
 
    //添加表示物品类型的精灵
    float x = this->getContentSize().width / 2;
    float y = this->getContentSize().height;
    switch (type)
    {
        case HITS:
        {
            typeSprite = CCSprite::create("shop/hits.png");
            AnimateTools::runAction(typeSprite,1);
            typeSprite->setScale(2);
            break;
        }
            
        case BRIDGES:
        {
            typeSprite = CCSprite::create("shop/bridge/bridge2.png");
            this->runRepeatAction(typeSprite);
            break;
        }
            
        case PERKS:
        {
            
            typeSprite = CCSprite::create("shop/aboutus.png");
            this->runRepeatAction(typeSprite);
            break;
        }
            
        case COINS:
        {
            
            typeSprite = CCSprite::create("shop/aboutus.png");
            this->runRepeatAction(typeSprite);
            break;
        }
        default:
            break;
    }
    
    typeSprite->setPosition(ccp(x , y * 2 / 3));
    this->addChild(typeSprite);
    
    //添加星星
    starSprite = CCSprite::create("shop/star.png");
    starSprite->setPosition(ccp( x, y / 3));
    this->addChild(starSprite);
    
    //添加菜单选项
    itemImage = CCMenuItemImage::create("shop/cell.png", "shop/cell.png", this, menu_selector(ChoooseItem::tobuyWhat));
    itemImage->setOpacity(0);
    itemImage->setPosition(ccp(this->boundingBox().size.width / 2,this->boundingBox().size.height / 2));
    itemImage->setContentSize(CCSizeMake(this->getContentSize().width, this->getContentSize().height));
    CCMenu * menu = CCMenu::create(itemImage,NULL);
    menu->setAnchorPoint(CCPointZero);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
    
    if(type == COINS || type == PERKS)
    {
        CCLabelBMFont * label = CCLabelBMFont::create("building", "uiImage/font.fnt");
        label->setPosition(ccp(x , y * 1.5 / 3 ));
        this->addChild(label,1);
        itemImage->setEnabled(false);
        
    }
}

void ChoooseItem:: setType(int type)
{
    this->type = type;
}

void ChoooseItem:: tobuyWhat()
{
    PLAY_EFFECT("music/button02.mp3");
    CCScene * goodShelf = CCTransitionSlideInT::create(1, GoodsShelf::CreateScene(this->type));
    CCDirector::sharedDirector()->replaceScene(goodShelf);
    
    GoodsShelf::typeN = this->type;

    
}

void ChoooseItem:: runRepeatAction(CCSprite * sprite)
{
    CCRepeatForever * repeat;
    if (this->type == BRIDGES)
    {
        CCMoveBy * move1 = CCMoveBy::create(1, ccp(40, 0));
        CCActionInterval * move2 = move1->reverse();
        CCSequence * seq = CCSequence::create(move1,move2,NULL);
        repeat = CCRepeatForever::create(seq);
    }
    else
    {
        CCRotateBy *  rotate = CCRotateBy::create(2, 360);
        repeat = CCRepeatForever::create(rotate);
        
    }
    sprite->runAction(repeat);
    
}

ChoooseItem:: ~ChoooseItem()
{
    
}

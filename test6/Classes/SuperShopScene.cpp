//
//  SuperShopScene.cpp
//  AnimalAid1
//
//  Created by mac on 14-11-16.
//
//

#include "SuperShopScene.h"
#include "AnimateTools.h"
#include "CommonDefine.h"
#include "GameDataCenter.h"
Scene * SuperShopScene:: CreateScene()
{
    Scene * scene = Scene::create();
    SuperShopScene * layer = SuperShopScene::create();
    scene->addChild(layer);
    return scene;
}
bool SuperShopScene:: init()
{
    if (!Layer::init())
    {
        return false;
    }
    VSIZE;
    
    //添加底色板

    LayerGradient * layerColor = LayerGradient::create(ccc4(0,0, 0, 220), ccc4(255, 0, 0, 220));
    layerColor->setAnchorPoint(Vec2::ZERO);
    layerColor->setPosition(Vec2::ZERO);
    this->addChild(layerColor);
    
    //    添加顶栏
    Sprite * topSprite = Sprite::create("shop/shopBar.png");
    topSprite->setScaleX(vsize.width /topSprite->getContentSize().width);
    topSprite->setAnchorPoint(Vec2::ZERO);
    topSprite->setPosition(Vec2(0, vsize.height - topSprite->boundingBox().size.height));
    
    this->addChild(topSprite);
    
    //添加返回按钮
    MenuItemImage * itemImage = MenuItemImage::create("shop/return.png", "shop/return.png");
    itemImage->setPosition(Vec2(itemImage->getContentSize().width / 2,vsize.height - itemImage->getContentSize().height / 2));
    itemImage->setScale(0.8);
    Menu * menu = Menu::create(itemImage,NULL);
    menu->setAnchorPoint(Vec2::ZERO);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    
    //添加漂浮物
    
    AnimateTools::runFountPartical(this, snowPartical);
    
   //添加灯笼
   this->addLantern(Vec2(vsize.width / 4 , vsize.height - 50));
   this->addLantern(Vec2(vsize.width  * 3 / 4, vsize.height - 50));
    
   

    return true;
}

void SuperShopScene::back()
{
    
}
void SuperShopScene:: addLantern(CCPoint position)
{
    CCSprite * lantern = CCSprite::create("shop/lantern.png");
    lantern->setAnchorPoint(ccp(0.5, 1));
    lantern->setPosition(position);
    lantern->setRotation(-90);
    CCRotateBy * rotate1 = CCRotateBy::create(3, 180);
    CCActionInterval * rotate2 = rotate1->reverse();
    CCSequence * seq = CCSequence::create(rotate1,rotate2,NULL);
    CCRepeatForever * repeat = CCRepeatForever::create(seq);
    lantern->runAction(repeat);
                       
    this->addChild(lantern,9);
    
    
}


void SuperShopScene:: onExit()
{
    CCLayer::onExit();
}

void SuperShopScene::keyBackClicked()
{
    
}
//
//  ShopScene.cpp
//  AnimalAid
//
//  Created by mac on 14-11-15.
//
//

#include "ShopScene.h"
#include "ChooseItem.h"
#include "GameScene.h"
#include "CommonDefine.h"
#include "BeginScene.h"
#include "cocos-ext.h"

CCScene * ShopScene:: CreateScene()
{
    CCScene * scene = CCScene::create();
    ShopScene * layer = ShopScene::create();
    scene->addChild(layer);
    return scene;
}
bool ShopScene:: init()
{
    if (!SuperShopScene::init())
    {
        return false;
    }
  
   
//    添加选项菜单
    for (int i = 1; i <= 4; i ++)
    {
        ChoooseItem * item = new ChoooseItem(i);
        item->setPosition(ccp(item->boundingBox().size.width / 2 + (i - 1) * item->boundingBox().size.width , item->boundingBox().size.height / 2));
        this->addChild(item);
    }
    
    CCScale9Sprite * scSprite = CCScale9Sprite::create("BeginSceneImage/slice19_19.png");
    scSprite->setScale(0.4);
    CCControlButton * playButton = CCControlButton::create(scSprite);
    playButton->setPreferredSize(CCSizeMake(240, 100));
    playButton->setPosition(ccp( 240,playButton->boundingBox().size.height /2 +10));
    playButton->addTargetWithActionForControlEvents(this,cccontrol_selector(ShopScene::play), CCControlEventTouchUpInside);
    playButton->setTouchPriority(-200);
    this->addChild(playButton);
    
    return true;
}

void ShopScene::keyBackClicked()
{
    this->back();
}

void ShopScene:: back()
{
    PLAY_EFFECT("music/button02.mp3");
    CCScene * scene = BeginScene::scene();
    DIRECTOR_REPLACE(scene);
}
void ShopScene:: play()
{
    PLAY_EFFECT("music/button02.mp3");
    CCScene * scene = GameScene::scene();
    DIRECTOR_REPLACE(scene);
    
}

void ShopScene::onExit()
{
    CCLayer::onExit();
}


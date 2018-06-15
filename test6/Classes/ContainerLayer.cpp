//
//  ContainerLayer.cpp
//  SaveTheNinja
//
//  Created by fly on 14-11-22.
//
//

#include "ContainerLayer.h"
#include "GameScene.h"
#include "GameDataCenter.h"
#include "CommonDefine.h"

bool ContainerLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }

    this->initData();
    //this->setTouchEnabled(true);
    return true;
}

void ContainerLayer::initData()
{
    for(int i = 0; i < LEVEL_COUNT; i++) {
       
        //添加底部树木精灵
        CCSprite *bottomsSprite = CCSprite::create("BeginSceneImage/tree.png");
        bottomsSprite->setAnchorPoint(ccp(0.5, 1));
        bottomsSprite->setPosition(ccp(VISIBLE_SIZE_WIDTH/2*(i+1), 90));
        bottomsSprite->setScale(0.6);
        this->addChild(bottomsSprite,1);
        
        //创建itemImage上部精灵
        CCString *str = CCString::createWithFormat("BeginSceneImage/scrollmenu_0%d.png",i + 1);
        
        //创建button
        CCScale9Sprite *scaleSprite = CCScale9Sprite::create(str->getCString());
        scaleSprite->setAnchorPoint(ccp(0.5, 0));
        scaleSprite->setPosition(ccp(0, 0));
        scaleSprite->setScale(0.6);
        CCControlButton *button = CCControlButton::create(scaleSprite);
        this->addChild(button);
        button->setTag(i + 1);
        button->addTargetWithActionForControlEvents(this, cccontrol_selector(ContainerLayer::buttonCallfunc), CCControlEventTouchUpInside);
        button->setAnchorPoint(ccp(0.5, 0));
        button->setPosition(ccp(VISIBLE_SIZE_WIDTH/2*(i+1), 80));
        
        switch (i) {
            case 0:
                button->setPreferredSize(CCSize(147, 247));
                button->setPosition(ccp(VISIBLE_SIZE_WIDTH/2*(i+1), 70));
                break;
            case 1:
                button->setPreferredSize(CCSize(160, 202));
                button->setPosition(ccp(VISIBLE_SIZE_WIDTH/2*(i+1), 80));
                break;
            
            case 2:
                button->setPreferredSize(CCSize(209, 232));
                button->setPosition(ccp(VISIBLE_SIZE_WIDTH/2*(i+1), 70));
                break;
            
            case 3:
                button->setPreferredSize(CCSize(209, 232));
                button->setPosition(ccp(VISIBLE_SIZE_WIDTH/2*(i+1), 70));
                break;
                
            case 4:
                button->setPreferredSize(CCSize(160, 232));
                button->setPosition(ccp(VISIBLE_SIZE_WIDTH/2*(i+1), 70));
                break;
                
            default:
                break;
        }
        if (i >= DATA_CENTER->getUnlockLevel()) {
            button->setTouchEnabled(false);
            CCSprite *lockSprite = CCSprite::create("BeginSceneImage/lock_0.png");
            lockSprite->setPosition(ccp(button->getPosition().x, 145));
            lockSprite->setScale(0.6);
            lockSprite->setColor(ccc3(100, 100, 100));
            this->addChild(lockSprite);
            scaleSprite->setOpacity(80);
            scaleSprite->setColor(ccc3(80, 80, 80));
        }
        
    }
    
}

void ContainerLayer::buttonCallfunc(CCObject *pSender)
{
    CCControlButton *temp = dynamic_cast<CCControlButton*>(pSender);
    if (temp) {
        DATA_CENTER->setSelectLevelNum(temp->getTag());
        CCScene *scene = CCTransitionCrossFade::create(0.5, GameScene::scene());
        DIRECTOR_REPLACE(scene);
    }
}

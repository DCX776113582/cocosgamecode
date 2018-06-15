//
//  AudioAndShopNode.cpp
//  FirstProject
//
//  Created by fly on 14-11-17.
//
//

#define visibleSize CCDirector::sharedDirector()->getVisibleSize()

#include "AudioAndShopNode.h"
#include "cocos-ext.h"
#include "GameDataCenter.h"
#include "AudioController.h"
#include "ShopScene.h"
USING_NS_CC_EXT;

bool AudioAndShopNode::init()
{
    if (!CCNode::init()) {
        return false;
    }
    shopNode = CCNode::create();
    this->addChild(shopNode);
    this->initShopButton();
    this->initAudioMenu();
    return true;
}

void AudioAndShopNode::initShopButton()
{
    //shop按钮初始化
    CCScale9Sprite *scaleSprite1 = CCScale9Sprite::create("BeginSceneImage/shop_0.png");
    scaleSprite1->setAnchorPoint(ccp(0, 0));
    scaleSprite1->setScale(0.5);
    CCScale9Sprite *scaleSprite2 = CCScale9Sprite::create("BeginSceneImage/shop_0.png");
    scaleSprite2->setScale(0.5);
    scaleSprite2->setAnchorPoint(ccp(0, 0));
    CCControlButton *button = CCControlButton::create(scaleSprite1);
    button->setPreferredSize(CCSize(99, 179));
    button->setBackgroundSpriteForState(scaleSprite2, CCControlStateHighlighted);
    button->addTargetWithActionForControlEvents(this, cccontrol_selector(AudioAndShopNode::callBackMethod), CCControlEventTouchUpInside);
    button->setPosition(ccp(0, 0));
    button->setAnchorPoint(ccp(0, 0));
    button->setTouchPriority(-2);
    shopNode->addChild(button);
    
    //shop金币数目初始化
    CCLabelBMFont *goldLabel = CCLabelBMFont::create(CCString::createWithFormat("%d",DATA_CENTER->m_moneyNum)->getCString(), "uiImage/font.fnt");
    goldLabel->setPosition(25, 0);
    goldLabel->setScale(0.65);
    shopNode->addChild(goldLabel);
    
    //金币闪烁
    CCFadeIn *fadeIn = CCFadeIn::create(0.6f);
    CCFadeOut *fadeOut = CCFadeOut::create(1.2f);
    CCSequence *seq = CCSequence::create(fadeOut,fadeIn,NULL);
    goldLabel->runAction(CCRepeatForever::create(seq));
    
    //获得按钮在屏幕上显示的位置
    shopPoint = ccp(visibleSize.width - scaleSprite2->boundingBox().size.width/7*8, 0);
    
    //设置按钮位置在屏幕外，隐藏按钮
    shopNode->setPosition(ccp(visibleSize.width + 20, 0));
}

#pragma mark 创建音乐控制按钮
void AudioAndShopNode::initAudioMenu()
{
    //初始化声音控制按钮，并将其位置设置在屏幕外
    CCMenuItemImage *onImage = CCMenuItemImage::create("BeginSceneImage/soundOn_0.png", "BeginSceneImage/soundOn_0.png");
    CCMenuItemImage *offImage = CCMenuItemImage::create("BeginSceneImage/soundOff_0.png", "BeginSceneImage/soundOff_0.png");
    CCMenuItemToggle *soundToggle = CCMenuItemToggle::createWithTarget(this, menu_selector(AudioAndShopNode::audioOnAndOff), onImage,offImage,NULL);
    soundToggle->setPosition(ccp(0, 0));
    soundToggle->setSelectedIndex(AudioController::getInstance()->m_isBgMusicOn ? 0 : 1);
    audioMenu1 = CCMenu::createWithItem(soundToggle);
    audioMenu1->setPosition(ccp(-20, 45));
    audioMenu1->setAnchorPoint(ccp(0, 0));
    audioMenu1->setScale(0.5);
    this->addChild(audioMenu1);
}

void AudioAndShopNode::appearAction()
{
    //商店按钮移动到屏幕内
    CCMoveTo *moveTo1 = CCMoveTo::create(1.0, shopPoint);
    shopNode->runAction(moveTo1);
    
    //声音控制按钮移动到屏幕内
    CCMoveTo *moveTo2 = CCMoveTo::create(1.0, ccp(25, 45));
    audioMenu1->runAction(moveTo2);
}

void AudioAndShopNode::audioOnAndOff()
{
    //停止所有的音乐、音效
    AudioController::parseAllMusic();
}

void AudioAndShopNode::callBackMethod()
{
    CCTransitionFadeUp *shop = CCTransitionFadeUp::create(0.5f, ShopScene::CreateScene());
    DIRECTOR_REPLACE(shop);
}

void AudioAndShopNode::reciprocate()
{
    //声音按钮往复动作
    CCMoveBy *audioMoveBy = CCMoveBy::create(0.5, ccp(-60, 0));
    CCSequence *sequence1 = CCSequence::create(audioMoveBy,audioMoveBy->reverse(),NULL);
    audioMenu1->runAction(sequence1);
    
    
    //商店按钮往复动作
    float distance = (visibleSize.width - shopPoint.x)*5/4;
    CCMoveBy *shopMoveBy = CCMoveBy::create(0.5, ccp(distance, 0));
    CCSequence *sequence2 = CCSequence::create(shopMoveBy, shopMoveBy->reverse(), NULL);
    shopNode->runAction(sequence2);
}



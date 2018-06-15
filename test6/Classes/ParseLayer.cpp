//
//  ParseLayer.cpp
//  AnimalAid
//
//  Created by Jason on 14-11-14.
//
//

#include "ParseLayer.h"
#include "cocos-ext.h"
#include "CommonDefine.h"
#include "BeginScene.h"
#include "ShopScene.h"
#include "YJNotificationCenter.h"
USING_NS_CC_EXT;
bool ParseLayer::init(){
    if (!CCLayer::init()) {
        return false;
    }
    this->setColorLayer();

    SHARED_DIRECTOR->getTouchDispatcher()->addTargetedDelegate(this, -2, true);
    this->setButtonItem();
    return true;
}




/* 设置颜色层 */
void  ParseLayer::setColorLayer(){
    ccColor4B begin = ccc4(139, 26, 26, 255);
    ccColor4B end = ccc4(0, 0, 0, 0);
    CCLayerGradient * gradient = CCLayerGradient::create(begin, end);
    this->addChild(gradient);
}

/*设置按钮 */
void ParseLayer::setButtonItem(){
    
    AudioController::playNormalButtonClick();
    /* 继续按钮 */
    CCScale9Sprite *sprite = CCScale9Sprite::create("uiImage/continue.png");
    CCControlButton *continueButton = CCControlButton::create(sprite);
    continueButton->setPreferredSize(CCSize(61,61));
    continueButton->setPosition(ccp(VISIBLE_SIZE_WIDTH/2 - 100, VISIBLE_SIZE_HEIGHT /2 - 30));
    continueButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ParseLayer::buttonCallback),CCControlEventTouchUpInside);
    continueButton->setTouchPriority(-3);
    continueButton->setTag(1001);
    this->addChild(continueButton);

    /* 返回按钮 */
    CCScale9Sprite *reSprite = CCScale9Sprite::create("uiImage/return.png");
    CCControlButton *button = CCControlButton::create(reSprite);
    button->setPreferredSize(CCSize(61,61));
    button->setPosition(ccp(VISIBLE_SIZE_WIDTH/2 + 100, VISIBLE_SIZE_HEIGHT /2 - 30));
    button->addTargetWithActionForControlEvents(this, cccontrol_selector(ParseLayer::buttonCallback),CCControlEventTouchUpInside);
    button->setTouchPriority(-3);
    button->setTag(1002);
    this->addChild(button);
    
    /* 菜单按钮 */
    CCScale9Sprite *menuSprite = CCScale9Sprite::create("uiImage/menuBG.png");
    CCControlButton *menuButton = CCControlButton::create(menuSprite);
    menuButton->setPreferredSize(CCSize(100,45));
    menuButton->setPosition(ccp(VISIBLE_SIZE_WIDTH - 100, VISIBLE_SIZE_HEIGHT - 40));
    menuButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ParseLayer::buttonCallback),CCControlEventTouchUpInside);
    menuButton->setTouchPriority(-3);
    menuButton->setTag(1003);
    CCSprite *menuLabel = CCSprite::create("uiImage/menuFont.png");
    menuLabel->setScale(0.5);
    menuLabel->setPosition(ccp(50,22));
    menuButton->addChild(menuLabel);
    this->addChild(menuButton);
    
    
    
    CCMenuItemImage *musicOn = CCMenuItemImage::create("uiImage/musicNormal.png", "uiImage/musicNormal.png");
    CCMenuItemImage *musicOff =CCMenuItemImage::create("uiImage/musicHighlight.png", "uiImage/musicHighlight.png");
    CCMenuItemToggle *music = CCMenuItemToggle::createWithTarget(this, menu_selector(ParseLayer::buttonCallback), musicOn,musicOff,NULL);
    music->setPosition(60,VISIBLE_SIZE_HEIGHT - 40);
    music->setTag(1004);
    if (AudioController::getInstance()->m_isBgMusicOn) {
        music->setSelectedIndex(0);
    }else{
        music->setSelectedIndex(1);
    }
    
    CCMenu *menu = CCMenu::create();
    menu->setPosition(CCPointZero);
    menu->addChild(music);
    
    this->addChild(menu);
    
}

/* 回掉函数 Button*/
void ParseLayer::buttonCallback(CCNode *pNode){
    switch (pNode->getTag()) {
        case 1001:{
            CCSequence * sequence = CCSequence::create(CCMoveTo::create(0.2, ccp(0, 320)),CCCallFunc::create(this, callfunc_selector(ParseLayer::removeOutWin)),NULL);
            this->runAction(sequence);
            break;
        }
        case 1002:{
            SIMPLE_AUDIO->stopAllEffects();
            CCTransitionFadeDown *down = CCTransitionFadeDown::create(0.5, ShopScene::CreateScene());
            SHARED_DIRECTOR->replaceScene(down);
            break;
        }
            
        case 1003:{
            SIMPLE_AUDIO->stopAllEffects();
            SIMPLE_AUDIO->stopBackgroundMusic();
            CCTransitionFadeDown *down = CCTransitionFadeDown::create(0.5, BeginScene::scene());
            SHARED_DIRECTOR->replaceScene(down);
            break;
        }
        case 1004:{
            AudioController::parseAllMusic();
            break;
        }
        default:
            break;
    }
    
}

void ParseLayer::removeOutWin(){
    this->resumeGame();
    NOTIFICATION_CENTER->notifyForKey("parse");
    this->removeFromParentAndCleanup(true);
    
}

void ParseLayer::resumeGame(){
    this->getParent()->getChildByTag(1002)->onEnter();
}

void ParseLayer::onExit(){
    CCLayer::onExit();
    SIMPLE_AUDIO->resumeAllEffects();
    SHARED_DIRECTOR->getTouchDispatcher()->removeDelegate(this);
}

void ParseLayer::setParseLabel(){
    
}

/* 点击事件 */
bool ParseLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    
    return true;
}
void ParseLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    
}
void ParseLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    
}
//
//  OverLayer.cpp
//  AnimalAid
//
//  Created by Jason on 14-11-13.
//
//

#include "OverLayer.h"
#include "cocos-ext.h"
#include "GameScene.h"
#include "GameDataCenter.h"
#include "CommonDefine.h"
#include "ShopScene.h"
#include "BeginScene.h"
#include "AudioController.h"
USING_NS_CC_EXT;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif
bool OverLayer::init(){
    if (!CCNode::init()) {
        return false;
    }
    this->initialNode();
    this->setButtonItem();
    
    SHARED_DIRECTOR->getTouchDispatcher()->addTargetedDelegate(this, -3, true);
    
    //写文件 音乐
    DATA_CENTER->saveDataToFile();
    SIMPLE_AUDIO->stopAllEffects();
    AudioController::playGameOver();
    
    return true;
}

void OverLayer::initialNode(){
    m_colorLayer = CCLayerColor::create(ccc4(255, 255, 255,60));
    this->addChild(m_colorLayer);
    
    CCSprite *leftHouse = CCSprite::createWithSpriteFrameName("house.png");
    leftHouse->setScale(0.5);
    leftHouse->setAnchorPoint(ccp(1, 1));
    leftHouse->setPosition(ccp(240,VISIBLE_SIZE_HEIGHT - 30));
    this->addChild(leftHouse,2);
    
    CCSprite *rightHouse = CCSprite::createWithSpriteFrameName("house.png");
    rightHouse->setScale(0.5);
    rightHouse->setFlipX(true);
    rightHouse->setAnchorPoint(ccp(0, 1));
    rightHouse->setPosition(ccp(240,VISIBLE_SIZE_HEIGHT - 30));
    this->addChild(rightHouse,2);
    
    
    ccColor4B begin = ccc4(0, 0, 0, 125);
    ccColor4B end = ccc4(255, 255, 255, 0);
    CCLayerGradient *gradient = CCLayerGradient::create(begin, end);
    gradient->setContentSize(CCSize(240,VISIBLE_SIZE_HEIGHT - 90));
    gradient->setPosition(125, 0);
    this->addChild(gradient,-1);
    
    for (int i = 0 ; i < 4; i++) {
        CCSprite *rightBar = CCSprite::createWithSpriteFrameName("houseBar.png");
        rightBar->setAnchorPoint(ccp(0, 1));
        float y = 120;
        if (i == 2 || i == 1) {
            y = 100;
        }
        rightBar->setScale(0.7);
        rightBar->setPosition(ccp(120 + 80 * i, VISIBLE_SIZE_HEIGHT - y));
        this->addChild(rightBar);
    }
    
    for (int i = 0; i < 3; i++) {
        CCSprite * lantern = CCSprite::createWithSpriteFrame(SPRITE_FRAME_CACHE(CCString::createWithFormat("lantern%d.png",i + 1)->getCString()));
        i == 1 ? lantern->setPosition(ccp(160 + 80 * i, 260)) : lantern->setPosition(ccp(160 + 80 * i, 240));
        lantern->setAnchorPoint(ccp(0.5, 1));
        lantern->setScale(0.5);
        
        float x = i == 1 ? 40.0f : -30.0f;
        if(i == 2) x = 30.0f;
        lantern->setRotation(x);
        CCRotateBy *rotate = CCRotateBy::create(2.0f, 2 * x);
        CCActionInterval *reRotate = rotate->reverse();
        CCRepeatForever * repeat = CCRepeatForever::create(CCSequence::create(reRotate,rotate,NULL));
        lantern->runAction(repeat);
        this->addChild(lantern);
    }
    
    
    CCSprite *overLabel = CCSprite::createWithSpriteFrame(SPRITE_FRAME_CACHE("gameover.png"));
    overLabel->setPosition(ccp(240, 340));
    this->addChild(overLabel, 3);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
	JniMethodInfo minfo;//定义Jni函数信息结构体
	//getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/Tutu/SaveNinja/SaveTheNinja", "showAd", "()V");
    
	if (!isHave) {
		CCLog("jni:此函数不存在");
	}
	else{
		CCLog("jni:此函数存在");
		//调用此函数
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        // minfo.env->DeleteLocalRef(minfo.classID);
	}
	CCLog("jni-java函数执行完毕");
#endif
    
}

void OverLayer::setButtonItem(){
    
    /* PlayAgain按钮 */
    CCScale9Sprite *againSprite = CCScale9Sprite::create("uiImage/menuBG.png");
    CCControlButton *againButton = CCControlButton::create(againSprite);
    againButton->setPreferredSize(CCSize(100,45));
    againButton->setPosition(VISIBLE_SIZE_WIDTH/2, VISIBLE_SIZE_HEIGHT - 300);
    againButton->addTargetWithActionForControlEvents(this, cccontrol_selector(OverLayer::itemCallBack),CCControlEventTouchUpInside);
    againButton->setTouchPriority(-3);
    againButton->setTag(1003);
    
    CCSprite *againLabel = CCSprite::create("uiImage/playAgain.png");
    againLabel->setScale(0.5);
    againLabel->setPosition(ccp(50,22));
    againButton->addChild(againLabel);
    CCScaleBy *scale = CCScaleBy::create(1.5f, 1.2f);
    CCActionInterval *reScale = scale->reverse();
    againButton->runAction(CCRepeatForever::create(CCSequence::create(scale,reScale,NULL)));
    againButton->setTag(1001);
    this->addChild(againButton);
    
    
    /* 菜单按钮 */
    CCScale9Sprite *menuSprite = CCScale9Sprite::create("uiImage/menuBG.png");
    CCControlButton *menuButton = CCControlButton::create(menuSprite);
    menuButton->setPreferredSize(CCSize(100,45));
    menuButton->setPosition(ccp(VISIBLE_SIZE_WIDTH/2 - 150, VISIBLE_SIZE_HEIGHT - 300));
    menuButton->addTargetWithActionForControlEvents(this, cccontrol_selector(OverLayer::itemCallBack),CCControlEventTouchUpInside);
    menuButton->setTouchPriority(-3);
    menuButton->setTag(1003);
    CCSprite *menuLabel = CCSprite::create("uiImage/menuFont.png");
    menuLabel->setScale(0.5);
    menuLabel->setPosition(ccp(50,22));
    menuButton->addChild(menuLabel);
    menuButton->setTag(1002);
    this->addChild(menuButton);
    
    /* 商店按钮 */
    CCScale9Sprite *shopSprite = CCScale9Sprite::create("uiImage/menuBG.png");
    CCControlButton *shopButton = CCControlButton::create(shopSprite);
    shopButton->setPreferredSize(CCSize(100,45));
    shopButton->setPosition(ccp(VISIBLE_SIZE_WIDTH/2 + 150, VISIBLE_SIZE_HEIGHT - 300));
    shopButton->addTargetWithActionForControlEvents(this, cccontrol_selector(OverLayer::itemCallBack),CCControlEventTouchUpInside);
    shopButton->setTouchPriority(-3);
    shopButton->setTag(1003);
    
    CCSprite *shopImage = CCSprite::create("uiImage/shop.png");
    shopImage->setScale(0.5);
    shopImage->setPosition(ccp(90,50));
    shopButton->addChild(shopImage);
    
    CCSprite *shopLabel = CCSprite::create("uiImage/store.png");
    shopLabel->setScale(0.5);
    shopLabel->setPosition(ccp(50,22));
    shopButton->addChild(shopLabel);
    this->addChild(shopButton);
    
    /*分数字体 */
    CCLabelBMFont *font = CCLabelBMFont::create(CCString::createWithFormat("Score:%d",DATA_CENTER->m_score)->getCString(), "uiImage/font.fnt");
    font->setPosition(ccp(VISIBLE_SIZE_WIDTH/2 - 15, VISIBLE_SIZE_HEIGHT/2 - 60));
    this->addChild(font,3);
    
    CCLabelTTF *label = CCLabelTTF::create(CCString::createWithFormat("Top: %d",DATA_CENTER->m_bestScore)->getCString(), "Verdana-Bold", 15);
    label->setColor(ccc3(255, 215, 0));
    label->setPosition(ccp(VISIBLE_SIZE_WIDTH/2 - 15, VISIBLE_SIZE_HEIGHT/2 - 30));
    this->addChild(label);
}


void OverLayer::itemCallBack(CCNode* psender,CCObject *obj){
    switch (psender->getTag()) {
        case 1001:{
            CCTransitionCrossFade * trans = CCTransitionCrossFade::create(0.3f, GameScene::scene());
            DATA_CENTER->resetLevel();
            SHARED_DIRECTOR->replaceScene(trans);
            break;
        }
        case 1002:{
            CCTransitionFadeDown *begin = CCTransitionFadeDown::create(0.5f, BeginScene::scene());
            DIRECTOR_REPLACE(begin);
            break;
            break;
        }
        case 1003:{
            CCTransitionFadeUp *shop = CCTransitionFadeUp::create(0.5f, ShopScene::CreateScene());
            DIRECTOR_REPLACE(shop);
            break;
        }
        default:
            break;
    }
    
}

/* 屏蔽触摸*/
bool OverLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    return true;
}
void OverLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    
}
void OverLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    
}

void OverLayer::onExit(){
    SHARED_DIRECTOR->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void OverLayer::saveScore(){
    
}
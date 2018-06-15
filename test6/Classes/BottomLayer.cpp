//
//  BottomNode.cpp
//  FirstProject
//
//  Created by fly on 14-11-14.
//
//

#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define bottomHeight 30

#include "BottomLayer.h"
#include "CheckNode.h"
#include "AnimateTools.h"
#include "CommonDefine.h"
#include "GameScene.h"

bool BottomLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    this->scheduleUpdate();
    isDown = true;
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, true);
    
    playNode = CCNode::create();
    playNode->setPosition(ccp(0, -80));
    this->addChild(playNode);
    
    //初始化音量、商店按钮
    topNode = AudioAndShopNode::create();
    topNode->setPosition(ccp(0, visibleSize.height*7/10));
    this->addChild(topNode);
    
    //调用飞行的忍者
    this->schedule(schedule_selector(BottomLayer::flyingSprite), 0.8f);
    
    this->bottomMenu();
    this->rotationSprite();
    this->initData();
    return true;
}

#pragma mark - 初始化函数
void BottomLayer::initData()
{
    //初始化四脚标
    checkNode = CheckNode::create();
    checkNode->setPosition(ccp(visibleSize.width/2, visibleSize.height/2 - 40));
    checkNode->setVisible(false);
    this->addChild(checkNode);
    
    
}

void BottomLayer::rotationSprite()
{
    //飞镖和飞镖背景旋转的实现
    /* 左飞镖 */
    CCSprite *sprite1 = CCSprite::create("BeginSceneImage/slice130_@.png");
    sprite1->setPosition(ccp(visibleSize.width/3 - 20, bottomHeight));
    sprite1->setScale(0.5);
    playNode->addChild(sprite1);
    
    //右飞镖
    CCSprite *sprite2 = CCSprite::create("BeginSceneImage/slice130_@.png");
    sprite2->setPosition(ccp(visibleSize.width/3*2 + 20, bottomHeight));
    sprite2->setScale(0.5);
    playNode->addChild(sprite2);
    
    //左飞镖背景
    CCSprite *sprite3 = CCSprite::create("BeginSceneImage/slice508_.png");
    sprite3->setPosition(sprite1->getPosition());
    //sprite3->setScale(2);
    sprite3->setAnchorPoint(ccp(0.45, 0.5));
    playNode->addChild(sprite3,-1);
    
    //右飞镖背景
    CCSprite *sprite4 = CCSprite::create("BeginSceneImage/slice508_.png");
    sprite4->setPosition(sprite2->getPosition());
    //sprite4->setScale(2);
    sprite4->setAnchorPoint(ccp(0.45, 0.5));
    playNode->addChild(sprite4,-1);

    //飞镖旋转动作
    CCRotateBy *rotateBy = CCRotateBy::create(6.0, 360);
    CCRepeatForever *rep1 = CCRepeatForever::create(rotateBy);
    CCRepeatForever *rep2 = CCRepeatForever::create((CCRotateBy *)(rotateBy->reverse()->copy()));
    sprite1->runAction(rep1);
    sprite2->runAction(rep2);
    
    //飞镖背景旋转动作
    CCRotateBy *rotateBy1 = CCRotateBy::create(5.0, 360);
    CCRepeatForever *rep3 = CCRepeatForever::create(rotateBy1);
    CCRepeatForever *rep4 = CCRepeatForever::create((CCRotateBy *)(rotateBy1->reverse()->copy()));
    sprite3->runAction(rep4);
    sprite4->runAction(rep3);
}

void BottomLayer::flyingSprite()
{
    int i = arc4random()%250 + 40;
    CCSprite *sprite = CCSprite::createWithSpriteFrameName("man1run_01.png");
    sprite->setPosition(ccp(0, i));
    int j = arc4random()%290;
    if(0.5 * j / 290 < 0.2)
    {
        sprite->setScale(0.2);
    }else
    {
        sprite->setScale(0.5* j / 290);
    }
    if (sprite->getScale() <0.4) {
        this->addChild(sprite,0);
    }else
    {
        this->addChild(sprite,2);
    }
    
    AnimateTools::runAction(1, 6, "man1run_", sprite, 0.1);
    CCJumpTo *jumpto = CCJumpTo::create(4, ccp(visibleSize.width + 30, i - 40), i%50 + 50, 1);
    CCSequence *sequcne = CCSequence::create(jumpto,CCCallFuncN::create(this, callfuncN_selector(BottomLayer::removeFlyingSprite)),NULL);
    sprite->runAction(sequcne);
}

#pragma mark - 逻辑函数
//底部按钮的实现（play、more ）
void BottomLayer::bottomMenu()
{
    //play按钮初始化
    CCMenuItemImage *playItem = CCMenuItemImage::create("BeginSceneImage/slice19_19.png", "BeginSceneImage/slice19_19.png");
    playItem->setPosition(ccp(visibleSize.width/2, bottomHeight));
    playItem->setScale(0.5);
    playItem->setTarget(this, menu_selector(BottomLayer::moveAndDispier));
    
    //more按钮初始化
    CCMenuItemImage *moreItem = CCMenuItemImage::create("BeginSceneImage/slice15_15.png", "BeginSceneImage/slice15_15.png");
    moreItem->setPosition(ccp(visibleSize.width - 40, bottomHeight - 10));
    moreItem->setScale(0.5);
    moreItem->setTarget(this, menu_selector(BottomLayer::moreButtonCallFunc));
    
    CCMenu* menu = CCMenu::create(playItem,moreItem,NULL);
    menu->setPosition(ccp(0, 0));
    playNode->addChild(menu);
    
    //返回按钮
    CCMenuItemImage *image = CCMenuItemImage::create("BeginSceneImage/back_bottom.png", "BeginSceneImage/back_bottom.png");
    image->setScale(0.6);
    image->setPosition(ccp(0,0));
    image->setTarget(this, menu_selector(BottomLayer::moveAndDispier));
    backMenu = CCMenu::createWithItem(image);
    backMenu->setPosition(ccp(visibleSize.width/2, -60));
    this->addChild(backMenu);
    
}

void BottomLayer::deleteMoreLayer()
{
    moreLayer->removeAllChildren();
    moreLayer->removeFromParent();
    moreLayer = NULL;
     
}

void BottomLayer::moveAndDispier()
{
    //显示checkNode
    if (!checkNode->isVisible()) {
        checkNode->setVisible(true);
    }
    
    //play/back按钮的移入、移出屏幕
    if (isDown) {
        if (moreLayer) {
            CCFadeOut *fadeOut = CCFadeOut::create(0.5);
            moreLayer->runAction(fadeOut);
            CCSequence *seq = CCSequence::create(fadeOut,CCCallFunc::create(this, callfunc_selector(BottomLayer::deleteMoreLayer)),NULL);
            moreLayer->runAction(seq);
        }
        this->playUpAndBackDown();
        checkNode->fadeInOrOut(isDown);
    }else
    {
        this->playDownAndBackUp();
        checkNode->fadeInOrOut(isDown);
    }
    topNode->reciprocate();
}


void BottomLayer::playDownAndBackUp()
{
    if (moreLayer) {
        CCFadeIn *fadeIn = CCFadeIn::create(0.5);
        moreLayer->runAction(fadeIn);
    }
    AudioController::playEnterSelect();
    //play按钮移出屏幕,back按钮进入屏幕，降低play的触摸代理优先级
    CCMoveBy *moveby = CCMoveBy::create(0.6, ccp(0, -80));
    playNode->runAction(moveby);
    backMenu->runAction((CCMoveBy*)(moveby->reverse()->copy()));
    CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(11, this);
    isDown = true;
}

void BottomLayer::playUpAndBackDown()
{
    AudioController::playNormalButtonClick();
    //play按钮进入屏幕,back按钮移出屏幕，提高play的触摸代理优先级
    CCMoveBy *moveby = CCMoveBy::create(0.6, ccp(0, -80));
    playNode->runAction(moveby->reverse());
    backMenu->runAction(moveby);
    CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(-1, this);
    isDown = false;
}

void BottomLayer::moreButtonCallFunc()
{
    this->playDownAndBackUp();
    AudioController::playNormalButtonClick();
    //moreLayer初始化
    moreLayer=CCLayerColor::create(ccc4(255, 255, 255, 100), VISIBLE_SIZE_WIDTH/2, VISIBLE_SIZE_HEIGHT/2 - 10);
    moreLayer->setPosition(ccp(VISIBLE_SIZE_WIDTH/4, VISIBLE_SIZE_HEIGHT/9));
    this->addChild(moreLayer, 3);
    
    //moreLayer标题
    CCLabelTTF *ttfLabel=CCLabelTTF::create("拯救忍者 V 1.0\n \n开发人员\n张亚杰\n李明\n李朋飞", "MarkerFelt-Thin", 20);
    ttfLabel->setPosition(ccp(moreLayer->getContentSize().width/2-ttfLabel->getContentSize().width/2, moreLayer->getContentSize().height-150));
    ttfLabel->setColor(ccc3(0, 0, 0));
    ttfLabel->setAnchorPoint(ccp(0, 0));
    
    moreLayer->addChild(ttfLabel, 1);

}

void BottomLayer::removeFlyingSprite(cocos2d::CCObject *pSender)
{
    CCSprite *temp = static_cast<CCSprite*>(pSender);
    temp->removeFromParent();
}

#pragma mark - OnEnter
void BottomLayer::onEnter()
{
    CCLayer::onEnter();
    CCMoveBy *moveby = CCMoveBy::create(1.0, ccp(0, 80));
    playNode->runAction(moveby);
    topNode->appearAction();
    isDown = false;
}

#pragma mark onExit()`
void BottomLayer::onExit()
{
    CCLayer::onExit();
    SHARED_DIRECTOR->getTouchDispatcher()->removeDelegate(this);
}

#pragma mark - CCTouchDelegate
bool BottomLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void BottomLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void BottomLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}




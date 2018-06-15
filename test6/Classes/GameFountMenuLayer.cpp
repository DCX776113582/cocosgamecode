//
//  GameFountMenuLayer.cpp
//  AnimalAid
//
//  Created by Student_17 on 14-11-5.
//
//

#include "GameFountMenuLayer.h"
#include "AnimateTools.h"
#include "cocos-ext.h"
#include "CommonDefine.h"
#include "GameDataCenter.h"
#include "ParseLayer.h"
#include "OverLayer.h"
#include "YJNotificationCenter.h"

#define ITEM_Y (VISIBLE_SIZE_HEIGHT - 30)

#define SCOR_POINT ccp(400, ITEM_Y)

#define PARSE_POINT ccp(240,ITEM_Y)

USING_NS_CC_EXT;
bool GameFountMenuLayer::init(){
    if (!CCLayer::init()) {
        return false;
    }
    
    m_heartArray = CCArray::create();
    m_heartArray->retain();
    
    AnimateTools::runFountPartical(this,leafPartical);
    this->setInfoLabel();
    this->setMenuItem();
    
    
    
    m_heartNum = DATA_CENTER->m_heartNum;
    
    scheduleUpdate();
    return true;
}

void GameFountMenuLayer::parseGame(){
    SIMPLE_AUDIO->pauseAllEffects();
    this->getParent()->getChildByTag(1002)->onExit();
}

/* 设置分数 */
void GameFountMenuLayer::setInfoLabel(){
    
    m_scoreBM = CCLabelBMFont::create("score: 0", "uiImage/font.fnt");
    m_scoreBM->setPosition(SCOR_POINT);
    this->addChild(m_scoreBM);
    
    for (int i = 0; i < DATA_CENTER->m_heartNum; i++) {
        CCSprite *sprite = CCSprite::create("uiImage/heartFull.png");
        sprite->setPosition(ccp(30 + 25 * i, ITEM_Y));
        sprite->setScale(0.5);
        m_heartArray->addObject(sprite);
        this->addChild(sprite);
        
    }
}

/* 更新心的数量 */
void GameFountMenuLayer::update(float dtime){
    m_scoreBM->setString(CCString::createWithFormat("score: %d",DATA_CENTER->m_score)->getCString());
    if (m_heartNum == DATA_CENTER->m_heartNum) {
        return;
    }
    
    m_heartNum = DATA_CENTER->m_heartNum;
    if (m_heartNum > 0) {
        
        
        for (int i = 0; i < 6; i++) {
           CCSprite* heart = ((CCSprite*)m_heartArray->objectAtIndex(i));
            CCSpriteFrame *frame;
            if (i > m_heartNum -1) {
                frame = CCSpriteFrame::create("uiImage/heartEmpty.png",CCRect(0,0,43,40));
                
            }else{
                frame = CCSpriteFrame::create("uiImage/heartFull.png",CCRect(0,0,43,40));
            }
            heart->setDisplayFrame(frame);
        }
        
    }else if (m_heartNum <= 0){
        this->heartIsOver();
    }
}

/* 暂停按钮 */
void GameFountMenuLayer::setMenuItem(){
   
    CCScale9Sprite *sprite = CCScale9Sprite::create("uiImage/parseBtn.png");
    m_parseBtn = CCControlButton::create(sprite);
    m_parseBtn->setPreferredSize(CCSize(40,36));
    m_parseBtn->setPosition(ccp(240, ITEM_Y));
    m_parseBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameFountMenuLayer::menuItemCallBack),CCControlEventTouchUpInside);
   
     this->addChild(m_parseBtn,3);
}

/* 暂停 */
void GameFountMenuLayer::menuItemCallBack(cocos2d::CCObject *pNode,CCControlEvent event){
//    NOTIFICATION_CENTER->notifyForKey("parse");
    AudioController::playNormalButtonClick();
    this->parseGame();
    ParseLayer *parse = ParseLayer::create();
    parse->setPosition(ccp(0, 320));
    this->getParent()->addChild(parse);
    parse->runAction(CCMoveTo::create(0.2f, ccp(0, 0)));
}

void GameFountMenuLayer::heartIsOver(){
    this->getParent()->addChild(OverLayer::create());
    
    this->removeFromParentAndCleanup(true);
}

/* 退出清除空间 */
void GameFountMenuLayer::onExit(){
    m_heartArray->release();
    CCLayer::onExit();
}
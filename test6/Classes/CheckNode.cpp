//
//  CheckNode.cpp
//  FirstProject
//
//  Created by fly on 14-11-16.
//
//
#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#include "CheckNode.h"

bool CheckNode::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    innerPoint = CCPoint(30, 30);
    outerPoint = CCPoint(50, 50);
    this->initData();
    this->spriteFlying();
    return true;
}

void CheckNode::initData()
{
    CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create("BeginSceneImage/slice124_@.png");
    spriteRT = CCSprite::createWithTexture(batchNode->getTexture());
    spriteRT->setScale(0.5);
    spriteRT->setPosition(innerPoint);
    spriteRT->setRotation(-45);
    this->addChild(spriteRT);
    
    spriteRD = CCSprite::createWithTexture(batchNode->getTexture());
    spriteRD->setScale(0.5);
    spriteRD->setPosition(ccp(innerPoint.x,-innerPoint.y));
    spriteRD->setRotation(45);
    this->addChild(spriteRD);
    
    spriteLD = CCSprite::createWithTexture(batchNode->getTexture());
    spriteLD->setScale(0.5);
    spriteLD->setPosition(ccp(-innerPoint.x,-innerPoint.y));
    spriteLD->setRotation(135);
    this->addChild(spriteLD);
    
    spriteLT = CCSprite::createWithTexture(batchNode->getTexture());
    spriteLT->setScale(0.5);
    spriteLT->setPosition(ccp(-innerPoint.x,innerPoint.y));
    spriteLT->setRotation(-135);
    this->addChild(spriteLT);
    
}

void CheckNode::spriteFlying()
{
    float dit1 = outerPoint.x - innerPoint.x;
    float dit2 = outerPoint.y - innerPoint.y;
    CCMoveBy *moveBy1 = CCMoveBy::create(1.4f, ccp(dit1, dit2));
    CCMoveBy *moveBy2 = CCMoveBy::create(1.4f, ccp(-dit1, dit2));
    
    CCSequence *sequenceLD = CCSequence::create((CCMoveBy*)moveBy2->reverse()->copy(),moveBy2->copy(),NULL);
    CCSequence *sequenceRT = CCSequence::create((CCMoveBy*)moveBy1->copy(),(CCMoveBy*)moveBy1->reverse()->copy(),NULL);
    
    spriteRT->runAction(CCRepeatForever::create(sequenceRT));
    spriteLD->runAction(CCRepeatForever::create(CCSequence::create(moveBy1->reverse(),moveBy1,NULL)));
    spriteLT->runAction(CCRepeatForever::create(CCSequence::create(moveBy2,moveBy2->reverse(),NULL)));
    spriteRD->runAction(CCRepeatForever::create(sequenceLD));
    
    
    
    
}

void CheckNode::fadeInOrOut(bool isFadeIn)
{
    if (isFadeIn) {
        this->resumeSchedulerAndActions();
        CCFadeIn *fadeIn = CCFadeIn::create(0.2f);
        spriteLD->runAction(fadeIn);
        spriteLT->runAction((CCFadeIn*)fadeIn->copy());
        spriteRT->runAction((CCFadeIn*)fadeIn->copy());
        spriteRD->runAction((CCFadeIn*)fadeIn->copy());
    }else
    {
        CCFadeOut *fadeOut = CCFadeOut::create(0.2f);
        spriteLD->runAction(fadeOut);
        spriteLT->runAction((CCFadeOut*)fadeOut->copy());
        spriteRT->runAction((CCFadeOut*)fadeOut->copy());
        spriteRD->runAction((CCFadeOut*)fadeOut->copy());
        this->pauseSchedulerAndActions();
    }
}








//
//  AnimateTools.cpp
//  AnimalAid
//
//  Created by Student_17 on 14-11-3.
//
//

#include "AnimateTools.h"

/* 传入起始的下标，结束的下标，图片名字前缀，精灵，一直执行这个动画*/
void AnimateTools::runAction(int beginIndex, int lastIndex, string picName, cocos2d::CCSprite *sprite ,float delayTime){
    sprite->stopAllActions();
    
    CCArray *plistArray = CCArray::create();
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    char name[20];
    for (int i = beginIndex; i <= lastIndex; i++) {
        sprintf(name, "%s%02d.png",picName.c_str(),i);
        /* 加载到缓存中的图片用这个方法*/
        CCSpriteFrame *frame = cache->spriteFrameByName(name);
        //CCSpriteFrame *frame = CCSpriteFrame::create(name, CCRectMake(0, 0, 39, 42));
        plistArray->addObject(frame);
    }
    CCAnimation *plistAnimation = CCAnimation::createWithSpriteFrames(plistArray,delayTime);
    CCAnimate *plistAniamte = CCAnimate::create(plistAnimation);
    sprite->runAction(CCRepeatForever::create(plistAniamte));
    
}

void AnimateTools::runAction(CCSprite *sprite,int type)
{
    sprite->stopAllActions();
    
    CCAnimate *plistAniamte = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(CCString::createWithFormat("man%d",type)->getCString()));
    sprite->runAction(CCRepeatForever::create(plistAniamte));
    
}

/* 风的效果 */
void AnimateTools::runFountPartical(cocos2d::CCNode *psender , ParticalType type){
    CCString *name;
    switch (type) {
        case leafPartical:{
            name = CCString::create("leafPartical.plist");
            break;
        }
            
        case snowPartical:{
            name = CCString::create("snowPartical.plist");
            break;
        }
            
        default:
            break;
    }
    CCParticleSystemQuad * particale =CCParticleSystemQuad::create(name->getCString());
    psender->addChild(particale,10);
}


void AnimateTools::addAnimationCache(){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shop/manrun.plist");
    for (int i = 1;  i < 6; i ++) {
        CCArray *plistArray = CCArray::create();
        char name[20];
        for (int j = 1; j < 7 ; j++)
        {
            sprintf(name, "man%drun_0%d.png",i,j);
            CCSpriteFrame * frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
            plistArray->addObject(frame);
            
        }
        CCAnimation *plistAnimation = CCAnimation::createWithSpriteFrames(plistArray,0.1f);
        char animationKey[20];
        sprintf(animationKey, "man%d",i);
        CCAnimationCache::sharedAnimationCache()->addAnimation(plistAnimation, animationKey);
        
        //将CCSpriteFrame加到CCAnimationCache缓冲区中
        
    }
}
//
//  AnimateTools.h
//  AnimalAid
//
//  Created by Student_17 on 14-11-3.
//
//

#ifndef __AnimalAid__AnimateTools__
#define __AnimalAid__AnimateTools__

#include "cocos2d.h"
#include "CommonEnum.h"
#include <iostream>
using namespace std;
USING_NS_CC;

class AnimateTools {
    
public:
    /* 类方法:runAction() 用于一直执行某个真动画 
       参数:起始的下标，结束的下标，图片名字前缀，要执行动画的精灵 间隔时间
       功能:精灵一直执行这个动画
     */
    static void runAction(int beginIndex, int lastIndex,string picName ,CCSprite *sprite, float delayTime);
    static void runAction(CCSprite *sprite,int type);
    /* 粒子效果  一个层   */
    static void runFountPartical(CCNode *psender,ParticalType type);
    
    static void addAnimationCache();
};

#endif /* defined(__AnimalAid__AnimateTools__) */

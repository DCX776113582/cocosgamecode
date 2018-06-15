//
//  CheckNode.h
//  FirstProject
//
//  Created by fly on 14-11-16.
//
//

#ifndef __FirstProject__CheckNode__
#define __FirstProject__CheckNode__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class CheckNode:public CCLayer
{
public:
    virtual bool init();
    CREATE_FUNC(CheckNode);
    void initData();
    void spriteFlying();
    void fadeInOrOut(bool isFadeIn);
    
private:
    CCPoint innerPoint;
    CCPoint outerPoint;
    
    //四角的精灵
    CCSprite *spriteLT;
    CCSprite *spriteLD;
    CCSprite *spriteRT;
    CCSprite *spriteRD;
};

#endif /* defined(__FirstProject__CheckNode__) */

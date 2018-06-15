//
//  bird.hpp
//  AngryBird
//
//  Created by mac on 18/4/10.
//
//

#ifndef bird_hpp
#define bird_hpp

#include "cocos2d.h"
using namespace cocos2d;
#include "BaseSprite.hpp"
#define BIRDHP 1000
#include <iostream>
using namespace std;
class BIRD:public BaseSprite {
    
public:
    static BIRD* create(Vec2 pos);//重写create函数，返回值为PIG
    void setBirdSpeed(float x,float y,b2World* world);
    void addAnimation();
protected:
    virtual bool init(Vec2 pos);//重写init
};

#endif /* bird_hpp */

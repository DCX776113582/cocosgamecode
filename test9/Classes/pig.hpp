//
//  pig.hpp
//  AngryBird
//
//  Created by mac on 18/4/10.
//
//

#ifndef pig_hpp
#define pig_hpp

#include "cocos2d.h"
using namespace cocos2d;
#include "BaseSprite.hpp"
#define PIGHP 60
#include <iostream>
using namespace std;
class PIG:public BaseSprite {
    
public:
    static PIG* create(Vec2 pos);//重写create函数，返回值为PIG
    virtual void setBody(b2World *world);//设置刚体与物理世界绑定
protected:
    virtual bool init(Vec2 pos);//重写init
};
#endif /* pig_hpp */

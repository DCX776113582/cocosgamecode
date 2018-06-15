//
//  ice.hpp
//  AngryBird
//
//  Created by mac on 18/4/10.
//
//

#ifndef ice_hpp
#define ice_hpp

#include "cocos2d.h"
using namespace cocos2d;
#include "BaseSprite.hpp"
#define ICEHP 60//血量
#include <iostream>
using namespace std;
class ICE:public BaseSprite {
    
public:
    static ICE* create(Vec2 pos);//重写create，返回值ICE
    virtual void setBody(b2World *world);//设置刚体，与物理世界绑定
protected:
    virtual bool init(Vec2 pos);//重写init
};

#endif /* ice_hpp */

//
//  BaseSprite.hpp
//  AngryBird
//
//  Created by mac on 18/4/10.
//
//

#ifndef BaseSprite_hpp
#define BaseSprite_hpp

#include "cocos2d.h"
USING_NS_CC;
#include <iostream>
using namespace std;
#include "BaseUtils.hpp"
#include "Box2D/Box2D.h"
//猪、冰块、小鸟的父类
class BaseSprite:public Sprite {
public:
    virtual bool init(string fileName,SpriteType typeID,Vec2 pos,int hp);//名字、ID、位置、血量
    //相当于添加get  set  方法
    CC_SYNTHESIZE(SpriteType, typeId, TYPEID);
    CC_SYNTHESIZE(int, hP, HP);
    virtual void destroyBody(b2World* _myWorld);//删除刚体
};

#endif /* BaseSprite_hpp */

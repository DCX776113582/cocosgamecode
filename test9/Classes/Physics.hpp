//
//  Physics.hpp
//  AngryBird
//
//  Created by mac on 18/4/10.
//
//

#ifndef Physics_hpp
#define Physics_hpp

#include <iostream>
using namespace std;
#include "Box2D/Box2D.h"
#include "cocos-ext.h"
#include "cocos2d.h"
#include "BaseSprite.hpp"
USING_NS_CC;
USING_NS_CC_EXT;
class MyContact:public b2ContactListener {
public:
    b2World* _world;//物理世界
    MyContact(){}
    MyContact(b2World* w,Layer* c){_world = w;}
    ~MyContact(){}
    
    virtual void BeginContact(b2Contact* contact);//碰撞开始
    virtual void EndContact(b2Contact* contact);//碰撞结束
    virtual void PreSolve(b2Contact* contact,const b2Manifold* oldManifold);//持续接触时响应
    //b2Manifold结构含有一个法向量和最多两个的接触点。向量和接触点都是相对于局部坐标系。为方便接触求解器处理,每个接触点都存储了法向冲量和切向(摩擦)冲量。
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);//持续接触时响应，调用完preSolve后调用
};

#endif /* Physics_hpp */

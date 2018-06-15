//
//  bird.cpp
//  AngryBird
//
//  Created by mac on 18/4/10.
//
//

#include "bird.hpp"
BIRD* BIRD::create(Vec2 pos)
{
    BIRD * bird = new BIRD();
    if (bird && bird->init(pos))
    {
        bird->autorelease();
        return bird;
    }
    CC_SAFE_DELETE(bird);
    return nullptr;
}
bool BIRD::init(Vec2 pos)
{
    if (!BaseSprite::init("ex-aid-1.png", BirdID, pos, BIRDHP))
    {
        return false;
    }
    this->setScale(0.1f);
    addAnimation();
    return true;
}
void BIRD::setBirdSpeed(float x,float y,b2World* world)
{
    this->stopAllActions();//停止所有动作
    b2BodyDef ballBodydef;//定义
    ballBodydef.type = b2_dynamicBody;//类型
    ballBodydef.position.Set(this->getPosition().x/PTM_RATIO, this->getPosition().y/PTM_RATIO);//设置位置
    ballBodydef.userData = this;//用户数据
    b2Body* ballBody = world->CreateBody(&ballBodydef);//定义并创建刚体
    b2PolygonShape blockShape;//定义多边形的形状
    blockShape.SetAsBox(0.3f, 0.3f);//设置为设置为框
    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &blockShape;
    ballShapeDef.density = 50.0f;//设置密度
    ballShapeDef.friction = 0.5f;//设置摩擦
    ballShapeDef.restitution = 0.2f;//设置恢复
    ballBody->CreateFixture(&ballShapeDef);
    b2Vec2 force = b2Vec2(20*x, 20*y);
    ballBody->ApplyLinearImpulse(force,ballBodydef.position,true);
    
}
void BIRD::addAnimation()
{
    auto rotation = RotateBy::create(0.5f,Vec3(0, 0, 360));
    auto jump = JumpBy::create(0.5, Vec2(0, 0), 50,1);
    Spawn* spawn = Spawn::create(rotation,jump, NULL);
    srand((unsigned)time(NULL));
    float arry[10] = {1,2.3,2,1.1,1.5,1.3,1.6,2.5,1.8,2.1};
    int tt = random(0, 9);
    DelayTime* delay = DelayTime::create(arry[tt]);
    Sequence* seq = Sequence::create(spawn,delay, NULL);
    RepeatForever* forver = RepeatForever::create(seq);
    this->runAction(forver);
}

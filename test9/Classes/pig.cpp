//
//  pig.cpp
//  AngryBird
//
//  Created by mac on 18/4/10.
//
//

#include "pig.hpp"
PIG* PIG::create(Vec2 pos)
{
    PIG * pig = new PIG();
    if (pig && pig->init(pos))
    {
        pig->autorelease();
        return pig;
    }
    CC_SAFE_DELETE(pig);
    return nullptr;
}
bool PIG::init(Vec2 pos)
{
    if (!BaseSprite::init("pig1.png", PigId, pos, PIGHP))
    {
        return false;
    }
    this->setScale(0.3);
    return true;
}
void PIG::setBody(b2World *world)
{
    int x = this->getPositionX();//获取x
    int y = this->getPositionY();//获取y
    
    // Create ball body
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(x / PTM_RATIO, y / PTM_RATIO);
    //    ballBodyDef.userData = this;
    ballBodyDef.bullet = false;
    
    b2Body * ballBody = world->CreateBody(&ballBodyDef);
    ballBody->SetUserData(this);
    
    // Create block shape
    b2PolygonShape blockShape;
    blockShape.SetAsBox(this->getContentSize().width / 7.2 / PTM_RATIO, this->getContentSize().height / 7.2 / PTM_RATIO);
    
    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &blockShape;
    ballShapeDef.density = 1.f;  //设置密度
    ballShapeDef.friction = 1.f;  //设置摩擦
    ballShapeDef.restitution = 0.2; //设置恢复力
    ballBody->CreateFixture(&ballShapeDef);
}

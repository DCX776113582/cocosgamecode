//
//  ice.cpp
//  AngryBird
//
//  Created by mac on 18/4/10.
//
//

#include "ice.hpp"
ICE* ICE::create(Vec2 pos)
{
    ICE * ice = new ICE();//new一个ICE
    if (ice && ice->init(pos))
    {
        ice->autorelease();//自动释放池
        return ice;//返回ice
    }
    CC_SAFE_DELETE(ice);//删除ice
    return nullptr;//返回空指针
}
bool ICE::init(Vec2 pos)
{
    if (!BaseSprite::init("ice1.png", IceID, pos, ICEHP))
    {
        return false;
    }
    this->setScale(0.3);//设置缩放比例
    return true;
}
void ICE::setBody(b2World *world)//设置刚体与物理世界绑定
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

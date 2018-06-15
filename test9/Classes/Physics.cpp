//
//  Physics.cpp
//  AngryBird
//
//  Created by mac on 18/4/10.
//
//

#include "Physics.hpp"
void MyContact::BeginContact(b2Contact* contact)//碰撞开始
{
    log("BeginContact");
}
void MyContact::EndContact(b2Contact* contact)//碰撞结束
{
    log("EndContact");
}
void MyContact::PreSolve(b2Contact* contact,const b2Manifold* oldManifold)//持续接触时响应
{
    log("PreSolve");
}
/*
 B2_NOT_USED(contact); //避免此次碰撞处理
 B2_NOT_USED(oldManifold);
 contact->SetEnabled(false); //避免此次碰撞处理
 
 //超级玛丽游戏中的单面墙，可以通过判断碰撞的方向来决定是否规避此次碰撞。
 
 b2WorldManifold worldManifold;
 contact->GetWorldManifold(&worldManifold);
 if (worldManifold.normal.y > 0.5f) {
 contact->SetEnabled(false);
 }
 */
//Box-2d多线程的，不能在子线程中删除主线程的东西。
void MyContact::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)//持续接触时响应，调用完preSolve后调用
{
    log("PostSolve");
    //Solve计算完成后调用的函数
    float force = impulse->normalImpulses[0];//受到的力
    if (force>1) {
        BaseSprite* spriteA = (BaseSprite*)contact->GetFixtureA()->GetBody()->GetUserData();
        BaseSprite* spriteB = (BaseSprite*)contact->GetFixtureB()->GetBody()->GetUserData();
        if (spriteA && spriteB) {
            if (spriteA->getTYPEID() != BirdID) {
                spriteA->setHP(spriteA->getHP()-force);
            }
            if (spriteB->getTYPEID() != BirdID) {
                spriteB->setHP(spriteB->getHP()-force);
            }
        }
    }
}

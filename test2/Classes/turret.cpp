//
//  turret.cpp
//  DefendTheRadish
//
//  Created by mac on 18/4/17.
//
//

#include "turret.hpp"
#include "VecManger.hpp"
Sprite* Turret::create(Vec2 p,int i)
{
    Turret* turret = new (std::nothrow)Turret();  //new出一个怪物
    if (turret && turret->init(p,i)) {
        turret->autorelease();                //自动调用
        return turret;                        //返回怪物
    }
    CC_SAFE_DELETE(turret);                   //删除
    return nullptr;//nullptr指空指针，NULL既可以代表空指针，也可以代表0
}
bool Turret::init(Vec2 p,int i)
{
    if (!Sprite::init()) {
        return false;
    }
    VecManger::getInstance()->addTurret(this);//将炮添加到容器
    //初始化精灵帧
    isLaunch = false;
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pingzi.plist", "pingzi.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shit.plist", "shit.png");
    if (i==1) {
        setSpriteFrame("Bottle11.png");
    }
    if (i==2) {
        setSpriteFrame("Shit12.png");
    }
    this->setPosition(p);
    return true;
}
//void Turret::onEnter()
//{
//    Sprite::onEnter();
//    this->schedule(schedule_selector(Turret::creatBuilt),1);
//}
//
//void Turret::creatBuilt(float dt)
//{
//    //初始化精灵帧
////    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pingzi.plist", "pingzi.png");
////    setSpriteFrame("PBottle11.png");
////    this->setPosition(p);
////    auto bullet = Sprite::createWithSpriteFrameName("PBottle13.png");
////    bullet->setPosition(Vec2(getPositionX(), getPositionY() + getContentSize().height / 2));
//    auto bullet = Bullet::create(Vec2(getContentSize().width/2,getContentSize().height/2));
////    auto bullet = Bullet::create(getPosition());
//    this->addChild(bullet);
//}

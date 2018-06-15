//
//  bullet.cpp
//  DefendTheRadish
//
//  Created by mac on 18/4/18.
//
//

#include "bullet.hpp"
#include "VecManger.hpp"
#include "TileMap.hpp"
Bullet* Bullet::create(Vec2 turrpos,Vec2 monsterpos,float angle,Size vis)
{
    Bullet* bullet = new (std::nothrow)Bullet();  //new出一个怪物
    if (bullet && bullet->init(turrpos,monsterpos,angle,vis)) {
        bullet->autorelease();                //自动调用
        return bullet;                        //返回怪物
    }
    CC_SAFE_DELETE(bullet);                   //删除
    return nullptr;//nullptr指空指针，NULL既可以代表空指针，也可以代表0
}
//bool Bullet::init(Vec2 p,Vec2 p2,float angle,Size vis)
bool Bullet::init(Vec2 turrpos,Vec2 monsterpos,float angle,Size vis)
{
    if (!Sprite::init()) {
        return false;
    }
//    VecManger::getInstance()->addBullet(this);
    //初始化精灵帧
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pingzi.plist", "pingzi.png");
    setSpriteFrame("PBottle11.png");
    ishit = false;
    this->setPosition(turrpos);
    this->move(turrpos,monsterpos);
    return true;
}
void Bullet::move(Vec2 turrpos,Vec2 monsterpos)
{
//    auto vec = VecManger::getInstance();
//    for (auto mons : vec->getMonsterVec()) {
//        monsterpos = mons->getPosition();
        auto move = MoveTo::create(1,monsterpos);
        auto callf = CallFuncN::create([=](Ref*sender){
            this->removeFromParentAndCleanup(true);
        });
        auto seq = Sequence::create(move,callf, NULL);
        this->runAction(seq);
//    }
    
}
void Bullet::behit(){
    
    //打印字符串到缓存
    string str1 = StringUtils::format("PBottle01.png");
    this->setSpriteFrame(str1);              //设置精灵帧的名字
    Vector<SpriteFrame*>animationFrameVector;//创建动画帧容器
    for (int i = 1; i<=2; ++i) {
        string str = StringUtils::format("PBottle0%d.png",i);//字符串组
        //创建精灵帧缓存
        auto sprFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animationFrameVector.pushBack(sprFrame);//下一个，添加
    }
    //转换成动画
    auto animation = Animation::createWithSpriteFrames(animationFrameVector,0.2f);
    auto animate = Animate::create(animation);          //动画转换成动作
    auto Action = RepeatForever::create(animate);   //创建重复动作
    auto seq = Sequence::create(Action,CallFunc::create([=](){
        this->removeFromParentAndCleanup(true);
    }), NULL);
    this->runAction(seq);
}



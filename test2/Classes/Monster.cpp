//
//  Monster.cpp
//  DefendTheRadish
//
//  Created by mac on 18/4/16.
//
//

#include "Monster.hpp"
#include "VecManger.hpp"

Sprite* Monster::create(int type)//创建对象
{
    Monster* monster = new (std::nothrow)Monster();  //new出一个怪物
    if (monster && monster->init(type)) {
        monster->autorelease();                //自动调用
        return monster;                        //返回怪物
    }
    CC_SAFE_DELETE(monster);                   //删除
    return nullptr;//nullptr指空指针，NULL既可以代表空指针，也可以代表0
}
bool Monster::init(int type)//重写init函数
{
    if (!Sprite::init()) {
        return false;
    }
    VecManger::getInstance()->addMonster(this);//将鱼添加到容器
    //初始化精灵帧
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("monsters.plist", "monsters.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Items02-hd.plist", "Items02-hd.png");
    ob = TileMap::getInstance();
    ob->getGroupObject();
    monsterLevel = type;               //怪物的等级
    hp = 10;
    isHit = false;                //是否抓
    this->setType(type);            //设置等级
    this->setPosition(Vec2(ob->obj1.at(0).x,ob->obj1.at(0).y));
//    this->setScale(0.6);            //设置缩放比例
//    this->setContentSize(this->getContentSize()*0.6);//设置容量大小
    this->run();                    //怪物成功执行动画
    return true;
}
void Monster::setType(int type)//设置类型
{
     //打印字符串到缓存
    string str1 = StringUtils::format("PetBoss11_0%d.png",type);
    this->setSpriteFrame(str1);              //设置精灵帧的名字
    Vector<SpriteFrame*>animationFrameVector;//创建动画帧容器
    for (int i = 1; i<=3; ++i) {
        string str = StringUtils::format("PetBoss1%d_0%d.png",i,type);//字符串组
        //创建精灵帧缓存
        auto sprFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animationFrameVector.pushBack(sprFrame);//下一个，添加
    }
    //转换成动画
    auto animation = Animation::createWithSpriteFrames(animationFrameVector,0.2f);
    auto animate = Animate::create(animation);          //动画转换成动作
    auto fishAction = RepeatForever::create(animate);   //创建重复动作
    this->runAction(fishAction);                        //运行动作
}
const int Monster::getLevel()//获取怪物的等级
{
    return monsterLevel;//返回怪物的等级
}
void Monster::surePath()
{
    float speed = 32;
    Vec2 pos1,pos2;
    float distance;
    Vector<FiniteTimeAction*>action;
    for (int i = 1; i<ob->obj1.size(); ++i) {
        pos1 = Vec2(ob->obj1.at(i).x,ob->obj1.at(i).y);
        pos2 = Vec2(ob->obj1.at(i-1).x,ob->obj1.at(i-1).y);
        distance = pos1.getDistance(pos2);
        auto move1 = MoveTo::create(distance/speed,pos1);
        action.pushBack(move1);
    }
    auto callf = CallFuncN::create([=](Ref*sender){
        Monster* monster = (Monster*)sender;
        VecManger::getInstance()->deleteMonster(monster);
    });
    auto seq = Sequence::create(action.at(0),action.at(1),action.at(2),action.at(3),action.at(4),action.at(5),action.at(6),callf,NULL);
    path = Speed::create(seq,2);
}
void Monster::beHit()//被打
{
    this->setSpriteFrame("air01.png");              //设置精灵帧的名字
    Vector<SpriteFrame*>animationFrameVector;//创建动画帧容器
    for (int i = 1; i<=5; ++i) {
        string str = StringUtils::format("air0%d.png",i);//字符串组
        //创建精灵帧缓存
        auto sprFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animationFrameVector.pushBack(sprFrame);//下一个，添加
    }
    //转换成动画
    auto animation = Animation::createWithSpriteFrames(animationFrameVector,0.2f);
    auto animate = Animate::create(animation);          //动画转换成动作
    auto Action = RepeatForever::create(animate);   //创建重复动作
    auto seq = Sequence::create(Action,CallFuncN::create([=](Ref*sender){
        Monster* monster = (Monster*)sender;
        VecManger::getInstance()->deleteMonster(monster);
    }), NULL);
    this->runAction(seq);
}
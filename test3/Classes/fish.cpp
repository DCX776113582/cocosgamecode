//
//  fish.cpp
//  FishMan
//
//  Created by MAC on 16/6/28.
//
//

#include "fish.hpp"
bool Fish::init()
{
    if (!Sprite::init()) {
        return false;
    }
    isCatch = false;
    fishLevel = 1;
    return true;
}
void Fish::setLevel(int level)
{
    fishLevel = level;
    char str[50];
    sprintf(str,"fish%02d_01.png",fishLevel);
    this->setSpriteFrame(str);
    //鱼的动画
    Vector<SpriteFrame*>_animationFrameVector;
    for (int i = 1;i<=10;++i) {
        std::string str = StringUtils::format("fish%02d_%02d.png",fishLevel,i);
        auto sprFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        _animationFrameVector.pushBack(sprFrame);
    }
    
    //将动画帧转换成动画
    auto animation = Animation::createWithSpriteFrames(_animationFrameVector,0.2f);
    //动画转换成动作
    auto animate = Animate::create(animation);
    //重复动作
    auto fishAction = RepeatForever::create(animate);
    this->runAction(fishAction);
}
const int Fish::getLevel(){
    return fishLevel;
}
void Fish::surePath()
{
    Vec2 startPoint,controlPoint,endPoint;
    float startAngle,endAngle;
    float time = rand()%10+18;
    int i = rand()%TOTALPATH;
    startPoint = Vec2(pathArray[i][0], pathArray[i][1]);
    controlPoint = Vec2(pathArray[i][2],pathArray[i][3] );
    endPoint = Vec2(pathArray[i][4],pathArray[i][5]);
    startAngle = pathArray[i][6]-SPRITE_OFFSET;
    endAngle = pathArray[i][7] - SPRITE_OFFSET;
    this->moveWithBezier(startPoint, endPoint, controlPoint, startAngle, endAngle, time);
}
void Fish::moveWithBezier(Vec2 startP,Vec2 endP,Vec2 controlP,float startA,float endA,float time)
{
    int xchange = rand()%100-50;
    int ychange = rand()%100-50;
    float sx = startP.x+xchange;
    float sy = startP.y+ychange;
    Vec2 sP = Vec2(sx, sy);
    
    int ex = endP.x + rand()%50-25;
    int ey = endP.y + rand()%50-25;
    Vec2 ep =Vec2(ex, ey);  //结束点
    
    int cx = controlP.x + xchange;
    int cy = controlP.y + ychange;
    Vec2 cp = Vec2(cx, cy); //控制点
    
    this->setPosition(sP);
    this->setRotation(startA);
    
    ccBezierConfig bezier;
    bezier.controlPoint_1 = sP;
    bezier.controlPoint_2 = cp;
    bezier.endPosition = ep;
    
    BezierTo* move = BezierTo::create(time, bezier);
    RotateTo* roAction = RotateTo::create(time, endA);
    auto action1 = Spawn::create(move,roAction, NULL);
    auto action2 = CallFuncN::create([=](Ref* pSender){
        this->removeFromParentAndCleanup(true);
    });
    auto action3 = Sequence::create(action1,action2, NULL);
    path = Speed::create(action3, 1.0);
}
    

#pragma mark 是否能被抓住
bool Fish::randomCatch(int cannonLevel){
    if (rand()% odds[fishLevel-1][1]<odds[fishLevel-1][0]*(1+0.1*cannonLevel)) {
        isCatch = true;
        return true;
    }
    else
        return false;
}
void Fish::beCatch()
{
    
    int num = 0;
    if (this->fishLevel < 8)
    {
        num = 3;
    }
    else
    {
        num = 5;
    }
    char str[50];
    sprintf(str, "fish%02d_01.png",fishLevel);
    this->setSpriteFrame(str);
    //使用精灵帧缓存讲大图中的小图读到缓存中去
    Vector<SpriteFrame*>animationFrameVector;
    for (int i = 1; i<num; i++)
    {
        std::string str = StringUtils::format("fish%02d_catch_%02d.png",fishLevel,i);
        auto sprFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animationFrameVector.pushBack(sprFrame);
    }
    auto animation = Animation::createWithSpriteFrames(animationFrameVector,0.2f);
    auto animate = Animate::create(animation);
    //重复动作
    auto action1 = Repeat::create(animate,2);
    auto callfunc = CallFuncN::create([=](Ref* pSender){
        Sprite* fish = (Sprite*)pSender;
        fish->removeFromParentAndCleanup(true);
    });
    auto action = Sequence::create(action1,callfunc, NULL);
    //清除原先所有的动作
    this->stopAllActions();
    this->runAction(action);
     /*
    int number = 0;
    if (this->fishLevel < 8) {
        number = 3;
    } else {
        number = 5;
    }
    
    char str[50];
    sprintf(str,"fish%02d_01.png",fishLevel);
    this->setSpriteFrame(str);
    Vector<SpriteFrame*> _animationFrameVector;
    for (int i = 1;i<number;++i) {
        std::string str = StringUtils::format("fish%02d_catch_%02d.png",fishLevel,i);
        auto sprFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        _animationFrameVector.pushBack(sprFrame);
    }
    auto animation = Animation::createWithSpriteFrames(_animationFrameVector,0.2f);
    auto animate = Animate::create(animation);
    auto action_1 = Repeat::create(animate, 2);
    auto action_2 = CallFuncN::create([=](Ref* sender){
        Sprite* fish = (Sprite*)sender;
        fish->removeFromParentAndCleanup(true);
    });
    auto action  = Sequence::create(action_1,action_2, NULL);
    this->stopAllActions();
    this->runAction(action);
      */
}








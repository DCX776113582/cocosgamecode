//
//  radish.cpp
//  DefendTheRadish
//
//  Created by mac on 18/4/16.
//
//

#include "radish.hpp"

Sprite* Radish::create(int bar)//创建对象
{
    Radish* radish = new (std::nothrow)Radish();  //new出一个怪物
    if (radish && radish->init(bar)) {
        radish->autorelease();                //自动调用
        return radish;                        //返回怪物
    }
    CC_SAFE_DELETE(radish);                   //删除
    return nullptr;//nullptr指空指针，NULL既可以代表空指针，也可以代表0
}

bool Radish:: init(int bar)
{
    if (!Sprite::init()) {
        return false;
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Items01-hd.plist", "Items01-hd.png");
    _bar = bar;
    string str = StringUtils::format("hlb%d.png",_bar);
    setSpriteFrame(str);
    this->setAnchorPoint(Vec2(0.5,1));
    this->setPosition(Vec2(432, 280));
    return true;
}

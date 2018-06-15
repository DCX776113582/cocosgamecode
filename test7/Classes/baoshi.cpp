//
//  baoshi.cpp
//  sanxiao
//
//  Created by admin on 18/5/24.
//
//

#include "baoshi.hpp"
cocos2d::Sprite* Baoshi::create(int x,int y)
{
    Baoshi * baoshi = new (std::nothrow) Baoshi();
    if (baoshi&&baoshi->init(x,y))
    {
        baoshi->autorelease();
        return baoshi;
    }
    else
    {
        CC_SAFE_DELETE(baoshi);
        return nullptr;
    }
    
}
bool Baoshi::init(int x,int y)
{
    if (!Sprite::init())
    {
        return false;
    }
    setType();
    X1 = x;
    Y1 = y;
    
    return true;
}
void Baoshi:: setType()
{
    type = random(1,7);
    string str = StringUtils::format("jewel%d.png",type);
    this->setTexture(str);
}
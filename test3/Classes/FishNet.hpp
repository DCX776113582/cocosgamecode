//
//  FishNet.hpp
//  FishMan
//
//  Created by MAC on 16/6/29.
//
//

#ifndef FishNet_hpp
#define FishNet_hpp

#include <stdio.h>
#include "iostream"
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "ui/CocosGUI.h"
using namespace ui;
class FishNet:public Sprite {
    
public:
    static FishNet* create(const int n)
    {
        FishNet* sprite = new  FishNet();
        if (sprite && sprite->initWithNum(n))
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;
    }
    bool initWithNum(const int n){
        if (!Sprite::init()) {
            return false;
        }
        this->setfishNetLevel(n);
        isHit = false;
        return true;
    }
    const int getFishNetLevel()
    {
        return fishNetLevel;
    }
    void setfishNetLevel(int n)
    {
        if (n>0&&n<=7) {
            fishNetLevel = n;
        }
        char str[50];
        sprintf(str, "net%02d.png",fishNetLevel);
        this->setSpriteFrame(str);
    }
//    bool getisHit()
//    {
//        return isHit;
//    }
//    void setisHit(bool hit)
//    {
//        isHit = hit;
//    }
private:
    int fishNetLevel;
    bool isHit;
};

#endif /* FishNet_hpp */










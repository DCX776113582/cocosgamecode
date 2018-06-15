//
//  bullet.cpp
//  FishMan
//
//  Created by MAC on 16/6/28.
//
//

#include "bullet.hpp"
bool Bullet::init()
{
    if (!Sprite::init()) {
        return false;
    }
    this->setBulletLevel(1);
    isHit = false;
    return true;
}
void Bullet::setBulletLevel(int n)
{
    if (n>0&&n<=7) {
        BulletLevel = n;
        char str[50];
        sprintf(str,"bullet0%d.png",BulletLevel);
        this->setSpriteFrame(str);
    }
}
const int Bullet::getBulletLevel()
{
    return BulletLevel;
}





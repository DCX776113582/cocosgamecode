//
//  Cannon.cpp
//  FishMan
//
//  Created by MAC on 16/6/28.
//
//

#include "Cannon.hpp"
bool Cannon::init()
{
    if (!Sprite::init()) {
        return false;
    }
    this->setCannonLevel(1);
    return true;
}
void Cannon::setCannonLevel(int n)
{
    if (n>0 && n<=7) {
        cannonLevel = n;
        auto _spriteFrameCache = SpriteFrameCache::getInstance();
        /*
         使用指定的 plist 文件内容与纹理加载 SpriteFrame。
           参数
               plist	plist文件路径。
               textureFileName	纹理文件路径
        */
        _spriteFrameCache->addSpriteFramesWithFile("sprites/cannon.plist","sprites/cannon.png");
        char str[50];
        sprintf(str,"actor_cannon1_%d1.png",cannonLevel);
        auto sprFrame = _spriteFrameCache->getSpriteFrameByName(str);
        this->setSpriteFrame(sprFrame);//设置精灵帧
    }
}
const int Cannon::getCannonLevel()
{
    return cannonLevel;
}








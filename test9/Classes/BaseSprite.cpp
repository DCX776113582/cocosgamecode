//
//  BaseSprite.cpp
//  AngryBird
//
//  Created by mac on 18/4/10.
//
//

#include "BaseSprite.hpp"
bool BaseSprite::init(string fileName,SpriteType typeID,Vec2 pos,int hp)//名字、ID、位置、血量
{
    if (!Sprite::initWithFile(fileName)) {
        return false;
    }
    this->setPosition(pos);//设置位置
    typeId = typeID;//类型id
    hP = hp;//血量
    return true;
}
void BaseSprite::destroyBody(b2World* _myWorld)//删除刚体
{
    this->removeFromParentAndCleanup(true);//从父节点删除
}

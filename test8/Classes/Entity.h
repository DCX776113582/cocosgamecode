#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "cocos2d.h"
USING_NS_CC;

//对象类，提供接口
struct Entity {
public:
    Entity() {
        _id = _nextId++;
    }
    
    //获取id
    int GetId() { return _id; }
    //获取位置
    virtual const Vec2& GetPosition() = 0;
    //获取半径
    virtual float GetRadius() = 0;

private:
    int                      _id;
    static int               _nextId;
};

#endif

//
//  bullet.hpp
//  DefendTheRadish
//
//  Created by mac on 18/4/18.
//
//

#ifndef bullet_hpp
#define bullet_hpp

#include "Header.h"
#include "TileMap.hpp"

class Bullet:public Sprite{
public:
    static Bullet* create(Vec2 turrpos,Vec2 monsterpos,float angle,Size vis);    //创建对象
    virtual bool init(Vec2 turrpos,Vec2 monsterpos,float angle,Size vis);        //重写init函数
//    void btn();
    void move(Vec2 turrpos,Vec2 monsterpos);
    void behit();
    bool gethit(){return ishit;}
    void sethit(bool hit){ishit = hit;}
public:
    bool ishit;
private:
    int bulletLevel;
    Speed* path;//路径速度
    TileMap*ob;
};


#endif /* bullet_hpp */

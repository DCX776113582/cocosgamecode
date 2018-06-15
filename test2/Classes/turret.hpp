//
//  turret.hpp
//  DefendTheRadish
//
//  Created by mac on 18/4/17.
//
//

#ifndef turret_hpp
#define turret_hpp

#include "Header.h"
#include "TileMap.hpp"

class Turret:public Sprite{
public:
    static Sprite* create(Vec2 p,int i);    //创建对象
    virtual bool init(Vec2 p,int i);        //重写init函数
//    void onEnter();
//    void creatBuilt(float dt);
    bool getislaunch(){return isLaunch;}
    void setislaunch(bool _launch){isLaunch = _launch;}
public:
    bool isLaunch;
private:
    int monsterLevel;//鱼的等级
    Speed* path;//路径速度
    TileMap*ob;
};

#endif /* turret_hpp */

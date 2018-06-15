//
//  Monster.hpp
//  DefendTheRadish
//
//  Created by mac on 18/4/16.
//
//

#ifndef Monster_hpp
#define Monster_hpp

#include "Header.h"
#include "TileMap.hpp"

class Monster:public Sprite{
public:
    static Sprite* create(int type);    //创建对象
    virtual bool init(int type);        //重写init函数
    void setType(int type);             //设置类型
    void surePath();                    //确定路径
    const int getLevel();               //获取鱼的等级
    void run(){
        this->surePath();               //确定好了path：执行的动作
        this->runAction(path);          //执行动作。
    }
    int getmonsterHP(){return hp;}
    bool getisHit(){return isHit;}
    void setisHit(bool _ishit){isHit=_ishit;}
    void beHit();//被打
//    bool randomCatch(int cannonLevel);//随机抓

public:
    bool isHit;//打
private:
    int hp;
    int monsterLevel;//怪物的等级
    Speed* path;//路径速度
    TileMap*ob;
};

#endif /* Monster_hpp */

//
//  VecManger.hpp
//  DefendTheRadish
//
//  Created by mac on 18/4/16.
//
//

#ifndef VecManger_hpp
#define VecManger_hpp

#include "Header.h"
#include "Monster.hpp"
#include "turret.hpp"
#include "bullet.hpp"
class VecManger{
private:
    static VecManger*vec_Manger;    //容器
    Vector<Monster*>monsterVec;       //怪物容器
    Vector<Turret*>turretVec;
    Vector<Bullet*>bulletVec;       //子弹容器

    VecManger(){}
    ~VecManger(){}
public:
    void addBullet(Bullet*bullet);      //添加子弹
    void deleteBullet(Bullet*bullet);   //删除子弹
    Vector<Bullet*>& getBulletVec();    //获取子弹的容器
    int getBulletVecSize();             //获取子弹容器的大小
    
    void addMonster(Monster*monster);      //添加怪物
    void deleteMonster(Monster*monster);   //删除怪物
    Vector<Monster*>& getMonsterVec();    //获取怪物的容器
    int getMonsterVecSize();             //获取怪物容器的大小
    
    void addTurret(Turret*turret);      //添加怪物
    void deleteTurret(Turret*turret);   //删除怪物
    Vector<Turret*>& getTurretVec();    //获取怪物的容器
    int getTurretVecSize();             //获取怪物容器的大小
    
    static VecManger* getInstance();    //获取实例
    void vecClear();                    //清除容器
};
#endif /* VecManger_hpp */

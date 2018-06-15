//
//  VecManger.cpp
//  DefendTheRadish
//
//  Created by mac on 18/4/16.
//
//

#include "VecManger.hpp"
VecManger* VecManger::vec_Manger = new VecManger();
VecManger* VecManger::getInstance()
{
    return vec_Manger;
}
void VecManger::addMonster(Monster*monster)//添加鱼网
{
    this->monsterVec.pushBack(monster);
}
void VecManger::deleteMonster(Monster*monster)//删除鱼网
{
    this->monsterVec.eraseObject(monster);
    monster->removeFromParentAndCleanup(true);
}
Vector<Monster*>& VecManger::getMonsterVec()//获取鱼网的容器
{
    return monsterVec;
}
int VecManger::getMonsterVecSize()
{
    return monsterVec.size();
}
void VecManger::addBullet(Bullet*bullet)//添加子弹
{
    this->bulletVec.pushBack(bullet);
}
void VecManger::deleteBullet(Bullet*bullet)//删除子弹
{
    this->bulletVec.eraseObject(bullet);
    bullet->removeFromParentAndCleanup(true);
    cout<<"删除子弹后容器的Size："<<VecManger::getInstance()->getBulletVecSize()<<endl;
}
Vector<Bullet*>& VecManger::getBulletVec()//获取子弹容器
{
    return this->bulletVec;//返回子弹容器
}
int VecManger::getBulletVecSize()//获取子弹容器大小
{
    return this->bulletVec.size();//返回子弹容器大小
}

void VecManger::addTurret(Turret*turret)//添加鱼网
{
    this->turretVec.pushBack(turret);
}
void VecManger::deleteTurret(Turret*turret)//删除鱼网
{
    this->turretVec.eraseObject(turret);
    turret->removeFromParentAndCleanup(true);
}
Vector<Turret*>& VecManger::getTurretVec()//获取鱼网的容器
{
    return turretVec;
}
int VecManger::getTurretVecSize()
{
    return turretVec.size();
}

void VecManger::vecClear()
{
    monsterVec.clear();//清除子弹
    turretVec.clear();
    bulletVec.clear();
}
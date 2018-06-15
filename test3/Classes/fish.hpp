//
//  fish.hpp
//  FishMan
//
//  Created by MAC on 16/6/28.
//
//

#ifndef fish_hpp
#define fish_hpp

#include <stdio.h>
#include "iostream"
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "ui/CocosGUI.h"
using namespace ui;
//判断鱼碰撞时的条件
const int odds[][2] = {
    {10,70},
    {20,90},
    {24,100},
    {29,120},
    {30,170},
    {35,220},
    {40,330},
    {45,440},
    {48,450},
    {50,500},
    {40,500}
    
};
const int pathArray[][8]={
    {-200, 100, 240, 320, 560, 240, 150, 190},//0左到右（偏上）
    {-200,-100, 240, 320, 560, 120, 125, 200},//1左到右（偏下）
    {-100, -50, 240, 320, 560,-100, 110, 240},//2左下到右下
    {-100, 330, -20,-100, 550, 380, 270, 130},//3左上到右上
    {  50,-100,  30, 350, 500, 350,  70, 180},//4左下到右上
    { 550, 100, 300, 100,-100, 300, -20,  40},//5右到左（偏上）
    { 550, 300, 300, -50,-150, 160, -60,  25},//7右上到左
    { 600, 240, -20, 350,-150,-100,  10, -30},//8右到左偏下
    { 550,-100, 450, 350,-100, 350,  70,  20},//9右下到左上
    { 400, 400, 150, 420, 100,-100, -20, -80},//10上到下偏左1
    { 300, 400, 600, 100,  50,-100,-130, -35},//11上到下偏右2
    {  50, 400, 600, 150, 250,-100,-160, -60},//12上到下偏右1
    { 300, 450,-100, 100, 100,-100, -50,-105},//13上到下偏左2
    {  25,-100, 350, 200, 100, 400, 150,  60},//14下到上
    { 200,-100,-200, 240, 350, 400,  10, 160},//15下到上
};

#define TOTALPATH 15
#define SPRITE_OFFSET 0
const int moveTime = 15;
class Fish:public Sprite{
public:
    bool init();
    CREATE_FUNC(Fish);
    void setLevel(int level);
    const int getLevel();
    
    void surePath();
    
    void moveWithBezier(Vec2 startP,Vec2 endP,Vec2 controlP,float startA,float endA,float time);
    bool randomCatch(int cannonLevel);
    void beCatch();
    void run(){
    this->surePath();
    this->runAction(path);
    }

public:
    Speed* path;
    int fishLevel;
    bool isCatch;
};

#endif /* fish_hpp */


























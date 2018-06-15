//
//  GameScene.hpp
//  DefendTheRadish
//
//  Created by mac on 18/4/14.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "Header.h"
#include "radish.hpp"
#include "TileMap.hpp"
class GameScene:public Layer{
public:
    static Layer* create(int chapter,int level);
    static Scene* createScene(int chapter,int level);;
    bool init(int chapter,int level);
    void move();
    void pause1();
    void back();
    void updateMonster(float dt);
    void updateWave(float dt);
    void addMonster();
    void updatetime(float dt);
    void addTouch();
    void updateHit(float dat);
    void youLose();
    void youWin();
    void putScore();
    void onEnter();
    void onExit();
    void addtileMap();
    void addbuilt(float dt);
    void builtmove();
    void bulletwithmonsterhit(float dt);
//    float Rotation(Point p1,Point p2);//大炮旋转
    void movePlayer(Vec2 p);


private:
    TileMap*ob;
    vector<Vec2>turretPos;
    Size visableSize;//可视区域大小
    Node* gameScene;
    TMXTiledMap*_tileMap;
    TMXLayer* wallLayer;
    Label* label;
    SpriteFrame*spream;
    Sprite*radishBar;
//    Sprite*bullet;
    Sprite*radish;
    Sprite*sp;
    Text*wave;
    Text*score;
    int turretnum;
    int num,num2,num3;
    int bar;
    int Qian;
    int num1;
    int _chapter;
    int _level;
};


#endif /* GameScene_hpp */

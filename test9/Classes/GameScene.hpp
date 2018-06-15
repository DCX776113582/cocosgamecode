//
//  GameScene.hpp
//  AngryBird
//
//  Created by mac on 18/4/9.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <iostream>
using namespace std;
USING_NS_CC;
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace rapidjson;
#include "Box2D/Box2D.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
#include "Physics.hpp"
#include "ice.hpp"
#include "pig.hpp"
#include "bird.hpp"

struct PosXY{
    int x;
    int y;
};
class GameScene:public Layer{
public:
    static Layer* create(int chapter,int level);//重写create函数，参数为章节数、关卡数
    static Scene* createScene(int chapter,int level);//创建场景，参数为章节数、关卡数
    bool init(int chapter,int level);//重写init，参数为章节数、关卡数
    void parseJSon();//解析文件
    void onEnter()override;//重写onEnter
    void onExit()override;//重写onExit
    //重写onTouchBegan、onTouchMoved、onTouchEnded、onTouchCancelled、update
    bool onTouchBegan(Touch* touch,Event* unused_event)override;
    void onTouchMoved(Touch* touch,Event* unused_event)override;
    void onTouchEnded(Touch* touch,Event* unused_event)override;
    void onTouchCancelled(Touch* touch,Event* unused_event)override{}
    void update(float dt)override;
    void initPhysics();//创建物理世界
    void addPhysicsSprite(Vec2 p);//添加物理精灵
    void addPigBirdIce(int chapter,int level);//添加猪鸟冰，参数为章节数、关卡数
    void addPigBirdIce();//添加猪鸟冰
    void birdJumpToSlingShot();//鸟跳到弹弓上
public:
    int pigNum;//猪的数量
    int iceNum;//冰的数量
    int birdNum;//鸟的数量
    
    struct PosXY BirdPos[20];//鸟的位置数组
    struct PosXY PigPos[20];//猪的位置数组
    struct PosXY IcePos[20];//冰的位置数组
    
    void youWin();//你赢了
    void youFiled();//你输了
    void chushihua();//初始化
private:
    Size visableSize;//可视区域大小
    Vec2 beginPos;//开始触摸的位置
    Vec2 midPos;//弹弓的中心
    MyContact* listener;//碰撞检测
    Node* rootNode;//节点
    b2World* world;//物理世界
    Text* score;//分数字符串
    Text* highScore;//最高分字符串
    int _level;//关卡
    int _chapter;//章节
    int _highScore1;//最高分
    int num;//得分
    int _star;//星星数量
    DrawNode* node1;//线1
    DrawNode* node2;//线2
    
    __Array * iceArray;//冰容器
    __Array * pigArray;//猪容器
    __Array * birdArray;//鸟容器
    
    BIRD* currectBird;//鸟
    
};
#endif /* GameScene_hpp */

//
//  Game.hpp
//  sanxiao
//
//  Created by admin on 18/5/24.
//
//

#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "tinyxml2/tinyxml2.h"
#include "Box2D/Box2D.h"
#include "extensions/cocos-ext.h"
#include "baoshi.hpp"

USING_NS_CC_EXT;
using namespace rapidjson;
using namespace tinyxml2;
using namespace CocosDenshion;
using namespace cocos2d::ui;
using namespace std;

USING_NS_CC;


class Game :public Layer
{
public:
    static Layer* create(int chapter,int Step);
    static Scene* createScene(int chapter,int Step);
    bool init(int chapter,int Step);
//    CREATE_FUNC(Game);
    bool jiancha();
    void buchong();
    void onEnter()override;
    void onExit()override;
    void fun_shanchu();
    void fun_shanchu1();

    void win();
    void lose();
    void updatetime(float dt);
    void updateStep(float dt);
    void parseJSon();//解析文件——修改
    void chushihua();//初始化
    void menu();
    void resetButton();
    void createBaoshi();
    bool onTouchBegan(Touch * touch,Event * unused_event)override;
    void onTouchMoved(Touch * touch,Event * unused_event)override;
    void onTouchEnded(Touch * touch,Event * unused_event)override;
    void onTouchCancelled(Touch * touch,Event * unused_event)override;
//    int tianjiakuai();
private:
    int _chapter,_Step;
    int _highscore;
    int HighScore;
    int TargetScore;
    bool xiugai;
    Baoshi * jihe[8][8];
    Vector<Baoshi*> shanchu;
    Vector<Baoshi*> tianjia;
    bool zhuangtai;
    Sprite * kuang;
    Baoshi * jiaohuan;
    int tag;
    Size virableSize;
    Text * score;
    Text * score1;
    Text * label;
    Text * hinghscore;
    Node * node1;
    Node* node2;
    int _step;
    Text * step;
    int sc;
    int num,num2;
};

#endif /* Game_hpp */

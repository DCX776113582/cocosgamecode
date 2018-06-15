//
//  GuanQia.hpp
//  sanxiao
//
//  Created by MAC on 2018/5/29.
//
//

#ifndef GuanQia_hpp
#define GuanQia_hpp

#include <stdio.h>
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
#include "StartScene.hpp"
#include "Game.hpp"
USING_NS_CC_EXT;
using namespace rapidjson;
using namespace tinyxml2;
using namespace CocosDenshion;
using namespace cocos2d::ui;
using namespace std;

USING_NS_CC;


class xuanguan :public Layer
{
public:

    static Scene* createScene();
    bool init()override;
    CREATE_FUNC(xuanguan);
    void fileCopy();//文件拷贝
    void Jsonjiexi();//解析文件
    void ChooseModule(int chapter);
public:
    Size virableSize;
    bool islock[6];
    int case1[6];
    int _case;//关卡数
    int hightNum;//最高分
};



#endif /* GuanQia_hpp */

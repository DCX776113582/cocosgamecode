//
//  FirstScene.hpp
//  sanxiao
//
//  Created by MAC on 2018/5/29.
//
//

#ifndef FirstScene_hpp
#define FirstScene_hpp

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
//#include "baoshi.hpp"
#include "StartScene.hpp"

USING_NS_CC_EXT;
using namespace rapidjson;
using namespace tinyxml2;
using namespace CocosDenshion;
using namespace cocos2d::ui;
using namespace std;

USING_NS_CC;


class First :public Layer
{
public:
    static Scene* createScene();
    bool init()override;
    CREATE_FUNC(First);
};


#endif /* FirstScene_hpp */

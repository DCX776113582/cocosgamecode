//
//  baoshi.hpp
//  sanxiao
//
//  Created by admin on 18/5/24.
//
//

#ifndef baoshi_hpp
#define baoshi_hpp

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
//#include "Game.hpp"

USING_NS_CC_EXT;
//using namespace rapidjson;
//using namespace tinyxml2;
//using namespace CocosDenshion;
using namespace cocos2d::ui;
using namespace std;

USING_NS_CC;
class Baoshi:public cocos2d::Sprite
{
private:
    int X1;
    int Y1;
    int type;
public:
    static Sprite* create(int x,int y);
    virtual bool init(int x,int y);
    void setType();
    int gettype()
    {
        return type;
    }
    int getX()
    {
        return X1;
    }
    int getY()
    {
        return Y1;
    }
    void settype(int t)
    {
        type = t;
    }
    void setX(int x)
    {
        X1 = x;
    }
    void setY(int y)
    {
        Y1 = y;
    }
};

#endif /* baoshi_hpp */

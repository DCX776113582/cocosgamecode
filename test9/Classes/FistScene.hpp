//
//  FistScene.hpp
//  AngryBird
//
//  Created by mac on 18/4/9.
//
//

#ifndef FistScene_hpp
#define FistScene_hpp

#include <iostream>
using namespace std;
#include "cocos2d.h"
USING_NS_CC;
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
#include "SimpleAudioEngine.h"//简单音频引擎
using namespace CocosDenshion;

class FirstScene:public Layer{
public:
    static Scene* createScene();
    bool init();
    CREATE_FUNC(FirstScene);
    void SetTheBox();//设置模态对话框
private:
    Size visableSize;//可视区域大小
    UserDefault* userDefault;
    SimpleAudioEngine* music;
};

#endif /* FistScene_hpp */

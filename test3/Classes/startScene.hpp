//
//  startScene.hpp
//  FishMan
//
//  Created by MAC on 16/6/28.
//
//

#ifndef startScene_hpp
#define startScene_hpp
#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "ui/CocosGUI.h"
using namespace ui;
class StartScene: public Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void initUI();
    
   
//    void menuCloseCallback(cocos2d::Ref* pSender);
    
        CREATE_FUNC(StartScene);  //宏定义
    
//    void updateZT(float dt);
//    virtual void onEnter();
//    virtual void onExit();
private:
    Size visibleSize;//屏幕大小
    bool isSoundEfect;
    };

#endif /* startScene_hpp */









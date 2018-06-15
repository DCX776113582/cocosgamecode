//
//  logon.hpp
//  MyGame-mobile
//
//  Created by Admin on 2018/5/26.
//

#ifndef logon_hpp
#define logon_hpp

#include "Header.h"
class FirstScene:public Layer{
public:
    static Scene* createScene();
    bool init();
    CREATE_FUNC(FirstScene);
    void help();
    void set();
    void move(){}
    void exitApp();
    void menuCloseCallback(cocos2d::Ref* pSender);
private:
    Size visableSize;//可视区域大小
    UserDefault* userDefault;
    SimpleAudioEngine* music;
};
#endif /* logon_hpp */

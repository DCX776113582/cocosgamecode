//
//  FirstScene.hpp
//  DefendTheRadish
//
//  Created by mac on 18/4/12.
//
//

#ifndef FirstScene_hpp
#define FirstScene_hpp

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


#endif /* FirstScene_hpp */

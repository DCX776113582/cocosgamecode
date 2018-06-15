//
//  Adventure.hpp
//  DefendTheRadish
//
//  Created by mac on 18/4/13.
//
//

#ifndef Adventure_hpp
#define Adventure_hpp

#include "Header.h"

class AdventureModeScene:public Layer{
public:
    static Scene* createScene();
    bool init();
    CREATE_FUNC(AdventureModeScene);
//    void help();
    void back();
    void pageview();
    void Check(int p);
    void check();
    void button();
private:
    Size visableSize;//可视区域大小
    Node* AdventureScene;
    UserDefault* userDefault;
    SimpleAudioEngine* music;
    int page;
    int checknum[6];
    CheckBox* check1;
    CheckBox* check2;
    CheckBox* check3;
    CheckBox* check4;
    CheckBox* check5;
    CheckBox* check6;
    Layout* layout;
    PageView* pageView;
    Button* btn1;
    Button* btn2;

};

#endif /* Adventure_hpp */

//
//  Chapter.hpp
//  AngryBird
//
//  Created by mac on 18/4/9.
//
//

#ifndef Chapter_hpp
#define Chapter_hpp

#include <iostream>
using namespace std;
#include "cocos2d.h"
USING_NS_CC;
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
#include "SimpleAudioEngine.h"//简单音频引擎
using namespace CocosDenshion;
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace rapidjson;
class ChapterScene:public Layer{
public:
    static Scene* createScene();//创建场景
    bool init();//重写init
    CREATE_FUNC(ChapterScene);
    void fileCopy();//文件拷贝
    void Jsonjiexi();//解析文件
    void reset();//重置
private:
    Size visableSize;//可视区域
    PageView* pageView;//页面浏览
    Button* chapter;//关卡按钮
    ImageView* star1;//星星
    Layout* layout;//页面

    int star[2][3];//星星数量
    bool isLock[2][3];//是否解锁
    int HighScore[2][3];//最高分

};
#endif /* Chapter_hpp */

//
//  Chapter.hpp
//  DefendTheRadish
//
//  Created by mac on 18/4/14.
//
//

#ifndef Chapter_hpp
#define Chapter_hpp

#include "Header.h"

class CheckpointScene:public Layer{
public:
    static Layer* create(int chapter);
    static Scene* createScene(int chapter);
    bool init(int chapter);
    void back();
    void pageview();
    void choose();

private:
    Size visableSize;//可视区域大小
    Node* checkpointScene;
    Layout* layout;
    PageView* pageView;
    Sprite* sp1;
    Sprite* sp2;
    Sprite* sp3;
    Sprite* sp4;
    Sprite* sp5;
    Sprite* sp6;
    int page;
    int _chapter;
};
#endif /* Chapter_hpp */

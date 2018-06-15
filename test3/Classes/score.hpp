//
//  score.hpp
//  FishMan
//
//  Created by MAC on 16/6/30.
//
//

#ifndef score_hpp
#define score_hpp

#include <stdio.h>
#include "iostream"
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "ui/CocosGUI.h"
using namespace ui;
class Score:public Label {
    
public:
    static Score* create(const int n)
    {
        Score* label = new  Score();
        if (label && label->initWithNum(n))
        {
            label->autorelease();
            return label;
        }
        CC_SAFE_DELETE(label);
        return nullptr;
    }
    bool initWithNum(const int n){
        if (!Label::init()) {
            return false;
        }
        this->setscoreLevel(n);
        return true;
    }
    void setscoreLevel(int n)
    {
        char str[50];

        if (n>0&&n<=9)
        {
            scoreLevel = n;
            sprintf(str, "＋%d",scoreLevel);
        }
        else if(n>9 && n<12)
        {
            scoreLevel = n;
            sprintf(str, "＋%02d",scoreLevel);
        }
        
        this->setString(str);
    }
    
private:
    int scoreLevel;
};

#endif /* score_hpp */









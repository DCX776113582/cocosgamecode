//
//  number.hpp
//  FishMan
//
//  Created by MAC on 16/6/29.
//
//

#ifndef number_hpp
#define number_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#define HEIGHT 12
#define WIDTH 8
typedef enum{
    NumStyleNormal,
    NumStyleSameTime,
}NumStyle;
class Number:public Sprite {
    
public:
    static Number* creat(NumStyle style = NumStyleNormal)
    {
        Number * sprite = new Number();
        if (sprite && sprite->init(style))
        {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);//释放空间
        return nullptr;
    }
    bool init(NumStyle style);
    void setNumber(int num);
    void onRollDown(float dt);  //下滑
    void onRollUP(float dt);    //上滑
    void setup();               //设置纹理
public:
    Texture2D *m_texture;   //数字的texture
private:
    NumStyle m_style;       //滚动样式
    int m_num;              //显示的数字
    int m_nPosCur;          //当前的位置
    int m_nPosEnd;          //结束的位置
    int m_nMoveLen;         //每次移动的位置

    
};

#endif /* number_hpp */
















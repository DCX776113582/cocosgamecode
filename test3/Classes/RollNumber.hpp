//
//  RollNumber.hpp
//  FishMan
//
//  Created by MAC on 16/7/1.
//
//

#ifndef RollNumber_hpp
#define RollNumber_hpp

#include <stdio.h>
#include "number.hpp"
#include "cocos2d.h"
using namespace cocos2d;
class RollNumber:public Node{
public:
    bool init();
    CREATE_FUNC(RollNumber);
public:
    void rebuildEffect();
    void clearEffect();
    int getNumber();
    void setNumber(int num);
private:
    int m_nNumber;              //显示的数字
    int m_maxCol;               //最大显示位数
    bool  zeroFill;             //是否开启0填充
public:
    Vector<Number*>* numArray;   //存放每个数字的数组
    Vec2 m_point;               //坐标
    NumStyle style;             //滚动样式
    
};

#endif /* RollNumber_hpp */












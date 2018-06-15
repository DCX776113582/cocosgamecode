//
//  radish.hpp
//  DefendTheRadish
//
//  Created by mac on 18/4/16.
//
//

#ifndef radish_hpp
#define radish_hpp

#include "Header.h"
class Radish:public Sprite{
public:
    static Sprite* create(int bar);    //创建对象
    virtual bool init(int bar);        //重写init函数
    
public:
private:
    int _bar;

};
#endif /* radish_hpp */

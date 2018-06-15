//
//  JniTest.hpp
//  TestJava
//
//  Created by LXBig on 17/10/26.
//
//

#ifndef JniTest_hpp
#define JniTest_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
void setPackageName(const char* packageName)//从java层传过来的包名在此处打印出来
{
    printf("packageName = %s \n",packageName);
}
void exitApp()//Java层调用c++层的该函数，关闭程序。
{
    Director::getInstance()->end();
}










#endif /* JniTest_hpp */


























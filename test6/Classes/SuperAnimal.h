//
//  SuperAnimal.h
//  AnimalAid
//
//  Created by Student_17 on 14-11-5.
//
//

#ifndef __AnimalAid__SuperAnimal__
#define __AnimalAid__SuperAnimal__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class SuperAnimal : public CCSprite {
private:
    CC_SYNTHESIZE(int , m_score, Score);
public:
    /* 设置精灵图片 */
    virtual void setSpriteFrame() = 0;
    
    /* 初始化Animal */
    virtual void initializeItem(string iamgeName);
    
    /* 设置分数 */
    virtual void setScore(); 
    
public:
    virtual bool init();
};

#endif /* defined(__AnimalAid__SuperAnimal__) */

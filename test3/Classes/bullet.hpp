//
//  bullet.hpp
//  FishMan
//
//  Created by MAC on 16/6/28.
//
//

#ifndef bullet_hpp
#define bullet_hpp

#include <stdio.h>
#include "iostream"
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "ui/CocosGUI.h"
using namespace ui;
class Bullet:public Sprite {
public:
    CREATE_FUNC(Bullet);
    bool init();
    void setBulletLevel(int n);
    const int getBulletLevel();
    const bool getisHit()
    {
        return isHit;
    }
    void setisHit(bool _isHit)
    {
        isHit = _isHit;
    }
private:
    int BulletLevel;
    bool isHit;
};
#endif /* bullet_hpp */
















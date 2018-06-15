//
//  Cannon.hpp
//  FishMan
//
//  Created by MAC on 16/6/28.
//
//

#ifndef Cannon_hpp
#define Cannon_hpp

#include <stdio.h>
#include "iostream"
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "ui/CocosGUI.h"
using namespace ui;
class Cannon:public Sprite {

public:
    
    CREATE_FUNC(Cannon);
    bool init();
    void setCannonLevel(int n);
    const int getCannonLevel();
    
private:
    int cannonLevel;
};




#endif /* Cannon_hpp */








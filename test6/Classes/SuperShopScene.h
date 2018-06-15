//
//  SuperShopScene.h
//  AnimalAid1
//
//  Created by mac on 14-11-16.
//
//

#ifndef __AnimalAid1__SuperShopScene__
#define __AnimalAid1__SuperShopScene__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class SuperShopScene:public Layer
{
public:
    static Scene * CreateScene();
    virtual bool init()override;
    CREATE_FUNC(SuperShopScene);
    virtual void back();
    void addLantern(Point position);
    
    virtual void keyBackClicked()override;
    
    virtual void onExit()override;
    

protected:
    
};
#endif /* defined(__AnimalAid1__SuperShopScene__) */

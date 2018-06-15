//
//  ShopScene.h
//  AnimalAid
//
//  Created by mac on 14-11-15.
//
//

#ifndef __AnimalAid__ShopScene__
#define __AnimalAid__ShopScene__

#include <iostream>
#include "cocos2d.h"
#include "SuperShopScene.h"

USING_NS_CC;
class ShopScene : public SuperShopScene
{
public:
    
    static CCScene * CreateScene();
    virtual bool init();
    CREATE_FUNC(ShopScene);
    virtual void back();
    void play();
   
    void onExit();
    
    virtual void keyBackClicked(void);

private:
    
    
};
#endif /* defined(__AnimalAid__ShopScene__) */

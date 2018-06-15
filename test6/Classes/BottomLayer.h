//
//  BottomLayer.h
//  FirstProject
//
//  Created by fly on 14-11-14.
//
//

#ifndef __FirstProject__BottomLayer__
#define __FirstProject__BottomLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CheckNode.h"
#include "AudioAndShopNode.h"
USING_NS_CC;
USING_NS_CC_EXT;

class BottomLayer:public CCLayer
{
public:
    virtual bool init();
    CREATE_FUNC(BottomLayer);
    
public:
    void initData();
    void rotationSprite();
    void bottomMenu();
    void moveAndDispier();
    void moreButtonCallFunc();
    void flyingSprite();
    void removeFlyingSprite(CCObject *pSender);
    void playDownAndBackUp();
    void playUpAndBackDown();
    void deleteMoreLayer();
    
public:
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
public:
    void onEnter();
    void onExit();
    
private:
    CCNode *playNode;
    CheckNode *checkNode;
    CCMenu *backMenu;
    CCPoint shopPoint;
    AudioAndShopNode *topNode;
    CCLayerColor *moreLayer;
    
    bool isDown;
    
};

#endif /* defined(__FirstProject__IndexLayer__) */

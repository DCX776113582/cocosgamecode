//
//  AudioAndShopNode.h
//  FirstProject
//
//  Created by fly on 14-11-17.
//
//

#ifndef __FirstProject__AudioAndShopNode__
#define __FirstProject__AudioAndShopNode__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class AudioAndShopNode:public CCNode
{
public:
    virtual bool init();
    CREATE_FUNC(AudioAndShopNode);
    
public:
    void initShopButton();
    void initAudioMenu();
    void callBackMethod();
    void appearAction();
    void audioOnAndOff();
    void reciprocate();

    
private:
    CCPoint shopPoint;
    CCNode *shopNode;
    CCMenu *audioMenu1;
};

#endif /* defined(__FirstProject__AudioAndShopNode__) */

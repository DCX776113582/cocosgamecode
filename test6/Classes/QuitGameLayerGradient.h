//
//  QuitGameLayerGradient.h
//  SaveTheNinja
//
//  Created by fly on 14-11-23.
//
//

#ifndef __SaveTheNinja__QuitGameLayerGradient__
#define __SaveTheNinja__QuitGameLayerGradient__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class QuitGameLayerGradient:public LayerGradient
{
public:
    virtual bool init()override;
    CREATE_FUNC(QuitGameLayerGradient);
    
public:
    void quitGameMethod(Ref *pSender);
    
public:
    void onTouchCancelled(Touch *touch,Event *unused_event)override;
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent)override;
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent)override;
    virtual void onTouchEnded(Touch *pTouch,Event *pEvent)override;
};

#endif /* defined(__SaveTheNinja__QuitGameLayerGradient__) */

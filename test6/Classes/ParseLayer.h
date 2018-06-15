//
//  ParseLayer.h
//  AnimalAid
//
//  Created by Jason on 14-11-14.
//
//

#ifndef __AnimalAid__ParseLayer__
#define __AnimalAid__ParseLayer__

#include "cocos2d.h"
USING_NS_CC;
class ParseLayer : public CCLayer {
public:
    /* 设置渐变色 */
    void setColorLayer();
    
    /* 设置button */
    void setButtonItem();
    
    void buttonCallback(CCNode *pNode);
    
    void removeOutWin();
    
    void setParseLabel();
    
    void resumeGame();
public:
    virtual bool init();
    virtual void onExit();

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    CREATE_FUNC(ParseLayer);
};

#endif /* defined(__AnimalAid__ParseLayer__) */

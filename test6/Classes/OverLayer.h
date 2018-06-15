//
//  OverLayer.h
//  AnimalAid
//
//  Created by Jason on 14-11-13.
//
//

#ifndef __AnimalAid__OverLayer__
#define __AnimalAid__OverLayer__

#include "cocos2d.h"
USING_NS_CC;

class OverLayer : public CCLayer{
public:
    CCLayerColor *m_colorLayer;
    CCNode *m_itemsNode;
    CCMenu *m_menu;
public:
    void initialNode();
    
    /* 设置button */
    void setButtonItem();
    
    void itemCallBack(CCNode* psender,CCObject *obj);
    
    void saveScore();
public:
    virtual bool init();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    CREATE_FUNC(OverLayer);
};

#endif /* defined(__AnimalAid__OverLayer__) */

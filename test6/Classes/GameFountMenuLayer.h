//
//  GameFountMenuLayer.h
//  AnimalAid
//
//  Created by Student_17 on 14-11-5.
//
//

#ifndef __AnimalAid__GameFountMenuLayer__
#define __AnimalAid__GameFountMenuLayer__

#include "cocos2d.h"
USING_NS_CC;
#include "cocos-ext.h"
USING_NS_CC_EXT;

class GameFountMenuLayer : public CCLayer{
private:
    
    CCLabelBMFont *m_scoreBM;
    /* 心数组 */
    CCArray * m_heartArray;
    
    int m_heartNum;
    
    /* button */
    CCControlButton *m_parseBtn;
    
public:
    void setInfoLabel();
    void setMenuItem();
    void menuItemCallBack(cocos2d::CCObject *pNode,CCControlEvent event);
    
    void heartIsOver();
    
    void parseGame();
    
public:
    virtual bool init();
    virtual void onExit();
    virtual void update(float dtime);
    CREATE_FUNC(GameFountMenuLayer);
};

#endif /* defined(__AnimalAid__GameFountMenuLayer__) */

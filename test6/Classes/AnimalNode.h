//
//  AnimalNode.h
//  AnimalAid
//
//  Created by Student_17 on 14-11-3.
//
//

#ifndef __AnimalAid__AnimalNode__
#define __AnimalAid__AnimalNode__

#include "cocos2d.h"
#include "CommonEnum.h"
USING_NS_CC;


class AnimalNode : public CCNode {
protected:
    CC_SYNTHESIZE_READONLY(CCSprite*, m_animalSprite, AnimalSprite);

public:
    bool m_isJumpToBoard;
    
    bool m_isMoveDown;
    
    int m_score;
public:
    /* 节点绑定精灵 */
    void bindAnimalSprite();
    
    /* 设置动物初始位置 跑到起跳点*/
    void runToJumpPoint(BeginLocation type);
    
    /* 动物跳向木板 跑出屏幕 */
    void jumpToBoard();
    
    /* 获得当前节点的boundBox */
    CCRect getBoundingBox();
    
    /* 碰到侧边 跳出 */
    void moveDownOut(int direction);
    
    
public:
    ~AnimalNode();
    virtual bool init();
    virtual void onExit();
    CREATE_FUNC(AnimalNode);
};

#endif /* defined(__AnimalAid__AnimalNode__) */

//
//  PlayBoard.h
//  AnimalAid
//
//  Created by Student_17 on 14-11-4.
//
//

#ifndef __AnimalAid__PlayBoard__
#define __AnimalAid__PlayBoard__
#include "cocos2d.h"
#include "YJNotificationCenter.h"
USING_NS_CC;
using namespace std;

/* 类名 : PlayBoard 游戏下边的木板 
   编码人: 杰
 */

class PlayBoard : public CCNode , public YJObserver{
private:
    /* 木板 精灵 */
    CCSprite *m_boardLeft;
    CCSprite *m_boardRight;
    CCSprite *m_board;
public:
    /* 初始化精灵 */
    void initializeBoard();
    
    /* 根据参数设置木板 */
    void setBoard();
    
    /* 根据参数修改图片 */
    void changeFrame(int boardIndex);
    
    /* 定位边缘两块的位置 */
    void resetBoardEndsLocation();
    
    /* 修改木板的长度 左右各一格 */
    void makeBoardLonger();
    
    void resumeBoardLength();
    /* 获得木板的boundBox */
    CCRect getBoundingBox();
    
    /* 上下移动 */
    void moveUpAndDown();

    
public:
    virtual bool init();
    virtual void onExit();
    virtual void notifyUpdate();
    CREATE_FUNC(PlayBoard);
};

#endif /* defined(__AnimalAid__PlayBoard__) */

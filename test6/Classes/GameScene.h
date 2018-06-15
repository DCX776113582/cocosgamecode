//
//  GameScene.h
//  AnimalAid
//
//  Created by Student_17 on 14-11-4.
//
//

#ifndef __AnimalAid__GameScene__
#define __AnimalAid__GameScene__

#include "cocos2d.h"
#include "YJNotificationCenter.h"
USING_NS_CC;

typedef enum {
    bomb,
    addLength
}AwardType;

typedef enum{
    normalState,
    creazeState
} GameState;

/* 
 类名: GameScene
 功能: 游戏主场景
 编码人: 杰
 */
class PlayBoard;
class OverLayer;
class GameScene : public CCLayer ,public YJObserver{
public:
    ~GameScene();
    
protected:
    /* 点击开始位置 */
    CCPoint m_beginPoint;
    
    /* 木头最后位置 */
    CCPoint m_boardEndPoint;
    
    /* 储存动物数组 */
    CC_SYNTHESIZE_RETAIN(CCArray*, m_animalArr, AnimalArr);
    
    /* 游戏木板 */
    CC_SYNTHESIZE(PlayBoard*, m_board, Board);
    
    OverLayer *m_overNode;
    
    CCSprite *m_gameAward;
    
public:
    /* 设置游戏难度 */
    void setDifficultyLevel(GameState state);
    
    void setBeginCreazy();
    /* 添加一个动物 */
    void addOneAnimal();
    
    /* 初始化木板 */
    void addPlayBoard();
    
    /* 设置单点触摸 */
    void setTargetTouchEnabled();
    
    /* 游戏结束 */
    void gameOverStopUpdate();
    
    /* 设置游戏道具精灵 */
    void setGameAward();
    
    /* 进入狂热状态 */
    void beginCrazeState();
    
    /* 进入普通状态 */
    void beginNormalState();
    
    /* 添加结束层 */
    void addGameOverLayer();
    
    void manDetection();
    
    void addManSoul(Point point);
    
    void removeManSoul(Node* pNode);
public:
    
    /* 点击事件 */
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    
public:
    virtual void notifyUpdate();
    virtual void update(float dtime);
    
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    static CCScene* scene();
    CREATE_FUNC(GameScene);
};

#endif /* defined(__AnimalAid__GameScene__) */

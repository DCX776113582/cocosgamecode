//
//  GameDataCenter.h
//  AnimalAid
//
//  Created by Student_17 on 14-11-1.
//
//

#ifndef __AnimalAid__GameDataCenter__
#define __AnimalAid__GameDataCenter__

#include "cocos2d.h"
#include "CommonEnum.h"
#include <vector>
USING_NS_CC;
using namespace std;

#define MANTYPE_NUM 5
class GameDataCenter {
    
private:
    /* 私有构造函数 */
    GameDataCenter();
    
public:
    /* 关卡数据 */
    CC_SYNTHESIZE(int, m_totalLevelNum, TotalLevelNum);
    
    CC_SYNTHESIZE(int, m_unlockLevel, UnlockLevel);
    
    /* 当前选择的关卡 */
    CC_SYNTHESIZE(int, m_selectLevelNum, SelectLevelNum);
    
    
    
    /* 在商店选择的 游戏木板类型 */
    CC_SYNTHESIZE(BoardType, m_boardType, BoardType);
    
    /* 金币 */
    int m_moneyNum;
    
    int m_score;
    
    int m_bestScore;
    
    int m_heartNum;
    
    bool m_gameIsRun;
    
    vector<int> manVec;
    
public:
    void saveDataToFile();
    
    
public:
    void resetLevel();
    static GameDataCenter* getInstance();
    
    /* 加载所有的图片信息 */
    void loadAllTexture();
    
};

#endif /* defined(__AnimalAid__GameDataCenter__) */

//
//  GameDataCenter.cpp
//  AnimalAid
//
//  Created by Student_17 on 14-11-1.
//
//

#include "GameDataCenter.h"
#include "CommonDefine.h"

#define HIGH_SCORE "HighScore"
#define COIN_NUM "CoinNum"
/* 单例实现 */
static GameDataCenter *sg_instance = NULL;

GameDataCenter* GameDataCenter::getInstance()
{
    if (sg_instance == NULL) {
        sg_instance = new GameDataCenter();
    }
    
    return sg_instance;
}

/* 单例私有构造 */
GameDataCenter::GameDataCenter(){
    m_selectLevelNum = 1;
    m_totalLevelNum = 6;
    m_boardType = normalType;
    m_gameIsRun = true;
    m_heartNum = 6;
    m_score = 0;
    m_bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(HIGH_SCORE);
    m_unlockLevel = m_bestScore / 800 + 1;
    CCLog("un_lock%d",m_unlockLevel);
    m_moneyNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("CoinNum", 100);
}

/* 在程序运行时调用，加载所有的图片 */
void GameDataCenter::loadAllTexture(){
    //CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(<#const char *plist#>, <#const char *textureFileName#>)
}

void GameDataCenter::resetLevel(){
    
    USER_DEFAULT;
    DATA_CENTER->manVec.clear();
    for (int i = 0 ; i < 5; ++ i )
    {
        char keyStr[20];
        sprintf(keyStr, "hitapply%d",i);
        bool state = GET_BOOL(keyStr);
        if (state)
        {
            DATA_CENTER->manVec.push_back(i);
            
        }
        
    }
    USER_FLUSH;
   
    
    m_heartNum = 6;
    m_score = 0;
    m_gameIsRun = true;
    m_bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(HIGH_SCORE);
}

void GameDataCenter::saveDataToFile(){
    if (m_score > m_bestScore) {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("HighScore", DATA_CENTER->m_score);
    }
    CCUserDefault::sharedUserDefault()->setIntegerForKey(COIN_NUM, m_moneyNum);
}
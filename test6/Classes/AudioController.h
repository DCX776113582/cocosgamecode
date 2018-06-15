//
//  AudioController.h
//  AnimalAid
//
//  Created by Jason on 14-11-16.
//
//

#ifndef __AnimalAid__AudioController__
#define __AnimalAid__AudioController__

#include "CommonDefine.h"

class AudioController {
    
public:
    
    
    /* 进入游戏场景 背景音乐 */
    static void playGameBGMusic();
    
    /* 开始界面点击play开始关卡全选择的音效 */
    static void playLevelChoiseButtonClick();
    
    /* 进入游戏音效 */
    static void playEnterGame();
    
    /* 普通按钮的点击音效 */
    static void playNormalButtonClick();
    
    /* 人掉下去的音效 */
    static void playManDieth();
    
    /* 获得一个金币 */
    static void playGetOneCoin();
    
    /* 炸弹出厂音效 */
    static void playBombComing();
    
    /* 炸弹爆炸音效 */
    static void playExplosion();
    
    /* 木板变长道具音效 */
    static void playBoardToLong();
    
    /* 获得生命音效 */
    static void playGetLife();
    
    /* 小人踩木板音效 */
    static void playManOnBoard();
    
    /* 游戏结束音效 */
    static void playGameOver();
    
    /* 进入黑夜模式音效 */
    static void playCrazyState();
    
    /* 进入游戏选择音效 */
    static void playEnterSelect();
public:
    static AudioController* getInstance();
    bool m_isBgMusicOn;
private:
    AudioController();
public:
    static void parseAllMusic();
    
};

#endif /* defined(__AnimalAid__AudioController__) */

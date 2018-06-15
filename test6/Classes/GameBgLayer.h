//
//  GameBgLayer.h
//  AnimalAid
//
//  Created by Student_17 on 14-11-1.
//
//

#ifndef __AnimalAid__GameBgLayer__
#define __AnimalAid__GameBgLayer__

#include "cocos2d.h"
USING_NS_CC;

/* 类功能:游戏背景 和背景动画 层 
   作者: 张亚杰
 */

class GameBgLayer : public Layer {
    
public:
    /* 初始化背景函数，根据选择的关卡来自动选择加载的背景 */
    void initalizeBg();
    
    /* 开始疯狂模式 */
    void goEnterCrazyState();
    
    void goOutCrazyState(Node *pNode);
public:
    virtual bool init();
    CREATE_FUNC(GameBgLayer);
};

#endif /* defined(__AnimalAid__GameBgLayer__) */

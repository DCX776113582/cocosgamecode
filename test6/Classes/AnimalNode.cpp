//
//  AnimalNode.cpp
//  AnimalAid
//
//  Created by Student_17 on 14-11-3.
//
//

#include "AnimalNode.h"
#include "YJNotificationCenter.h"
#include "AnimateTools.h"
#include "CommonDefine.h"
#include "GameDataCenter.h"
#define JUMP_TIME 1.0f
#define MOVE_TIME 1.0f
bool AnimalNode::init(){
    if (!CCNode::init()) {
        return false;
    }
    m_isJumpToBoard = false;
    m_isMoveDown = false;
    this->bindAnimalSprite();
    m_score = 40;
    return true;
}

/* 为节点绑定精灵 */
void AnimalNode::bindAnimalSprite(){
    /* 换成缓存池后 修改 */
       int whitchMan = 0;
       int choose = 0;
        for (int j = 0; j < 100; j ++)
        {
            whitchMan = arc4random() % 5;
//            CCLog("random = %d",whitchMan);
            bool success = false;
            for (int m = 0; m < DATA_CENTER->manVec.size(); m ++)
            {
                
                if (DATA_CENTER->manVec.at(m) == whitchMan)
                {
                    choose = whitchMan;
                    success = true;
                    //CCLog("vec member: =%d  whitchMan= %d",DATA_CENTER->manVec.at(m),whitchMan);
                    break;
                    
                }
            }
                if (success)
                {
                    break;
                }
            }
    
    
    
    m_animalSprite = CCSprite::createWithSpriteFrameName("man1run_01.png");
    m_animalSprite->setAnchorPoint(CCPointZero);
    this->addChild(m_animalSprite);
    char picStr1[30];
    CCLog("man = %d",choose);
    sprintf(picStr1, "man%drun_0",choose + 1);
    AnimateTools::runAction(m_animalSprite,choose + 1);
    //AnimateTools::runAction(1, 6, "manrun_", m_animalSprite, 0.2f);
    
    CCLog("animal whitchMan =%d  vecSize = %lu",choose,DATA_CENTER->manVec.size());
 
}

/* 获得当前节点的boundBox */
CCRect AnimalNode::getBoundingBox(){
    CCRect box = m_animalSprite->boundingBox();
    CCPoint point = m_animalSprite->convertToWorldSpace(ccp(0,0));
    box = CCRect(point.x,point.y - 5,box.size.width,box.size.height);
    return box;
}

/* 设置精灵, 跑到起跳点 */
void AnimalNode::runToJumpPoint(BeginLocation type){
    CCPoint point;
    float jumpX = 30 + arc4random() % 3 * 20;
    if (type == lowPoint) {
        point = CCPoint( jumpX, 120);
    }else{
        point = type == middlePoint ? ccp(jumpX, 200) : ccp(jumpX, 264);
    }
    //设置起始位置
    this->setPosition(ccp(-20,point.y));
    CCMoveTo *move = CCMoveTo::create(MOVE_TIME, point);
    CCJumpTo *jump = CCJumpTo::create(JUMP_TIME, CCPoint(180 + arc4random() % 300, -50), 100, 1 );
    CCSequence *sequence = CCSequence::create(move,jump,NULL);
    this->runAction(sequence);
}

/* 跳到木板 ,跑出屏幕 */
void AnimalNode::jumpToBoard(){
    m_isJumpToBoard = true;
    this->stopAllActions();
    int factor = arc4random() % 3;
    float hight = factor != 2 ? 80 : 72;
    
    CCPoint targetPoint = ccp(480 - arc4random() % 3 * 20, 120 + hight * factor);
    
    CCJumpTo *jump = CCJumpTo::create(JUMP_TIME,targetPoint, 80 , 1);
    CCMoveBy *moveTo = CCMoveBy::create(MOVE_TIME, ccp(100,0));
    CCSequence *sequence = CCSequence::create(jump,moveTo,NULL);
    this->runAction(sequence);
    
}


/* 碰到侧边 跳出 */
void AnimalNode::moveDownOut(int direction){
    m_isMoveDown = true;
    this->stopAllActions();
    int targetX = direction == 0 ? arc4random() % 200 : 260 +arc4random() % 200;
    this->runAction(CCMoveTo::create(0.5, CCPointMake(targetX, -50)));

}
void AnimalNode::onExit(){
    CCNode::onExit();
}

AnimalNode::~AnimalNode(){
    if (m_animalSprite != NULL) {
        m_animalSprite->removeFromParentAndCleanup(true);
    }
}
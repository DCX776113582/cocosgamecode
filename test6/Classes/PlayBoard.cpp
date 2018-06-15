//
//  PlayBoard.cpp
//  AnimalAid
//
//  Created by Student_17 on 14-11-4.
//
//

#include "PlayBoard.h"
#include "CommonEnum.h"
#include "CommonDefine.h"
#include "GameDataCenter.h"

#define LONGER_TIME 5.0f
bool PlayBoard::init(){
    if (!CCNode::init()) {
        return false;
    }
    
    this->initializeBoard();
    this->setBoard();
    this->setScale(0.5);
    NOTIFICATION_CENTER->attachObserver(this, "tolonger");
    return  true;
}

/* 初始化木板精灵*/
void PlayBoard::initializeBoard(){
    m_boardLeft = CCSprite::create();
    m_boardRight = CCSprite::create();
    m_board = CCSprite::create();
}

/* 获得木板Node的boundBox */
CCRect PlayBoard::getBoundingBox(){
    CCRect box = m_board->boundingBox();
    CCPoint point = m_board->convertToWorldSpace(ccp(0,0));
    box = CCRect(point.x,point.y - 5,box.size.width /2,box.size.height / 2);
    return box;
}

#pragma mark - 修改精灵长度 和初始化图片
/* 初始化木板精灵 */
void PlayBoard::setBoard(){
#warning - 换成大图后加载从精灵缓存区加载
    BoardType type = DATA_CENTER->getBoardType();
    switch (type) {
        case normalType:{
            this->changeFrame(1);
            break;
        }
        case typeOne:{
            this->changeFrame(8);
            break;
        }
        case typeTwo:{
            this->changeFrame(2);
            break;
        }
        case typeThree:{
            this->changeFrame(4);
            break;
        }
        case typeFour:{
            this->changeFrame(5);
            break;
        }
        default:
            break;
    }
    this->resetBoardEndsLocation();
    this->addChild(m_board);
    this->addChild(m_boardLeft);
    this->addChild(m_boardRight);
}

/* 根据frame 修改精灵 纹理 */
void PlayBoard::changeFrame(int boardIndex){
    const char *boardName = CCString::createWithFormat("boardImage/board_%02d.png",boardIndex)->getCString();
    CCSpriteFrame *frame = CCSpriteFrame::create(boardName, CCRect(0,0,80,32));
    m_board->setDisplayFrame(frame);
    
    const char *boardLeftName = CCString::createWithFormat("boardImage/board_%02d_left.png",boardIndex)->getCString();
    CCSpriteFrame *leftFrame = CCSpriteFrame::create(boardLeftName, CCRect(0,0,13,36));
    m_boardLeft->setDisplayFrame(leftFrame);
    
    const char *boardRightName = CCString::createWithFormat("boardImage/board_%02d_right.png",boardIndex)->getCString();
    CCSpriteFrame *rightFrame = CCSpriteFrame::create(boardRightName, CCRect(0,0,13,36));
    m_boardRight->setDisplayFrame(rightFrame);
}

#pragma mark - 木板伸长缩短


void PlayBoard::makeBoardLonger(){
    CCSize size = m_board->displayFrame()->getOriginalSize();
    m_board->setTextureRect(CCRect(0.0f, 0.0f, size.width + 40, size.height));
    this->runAction(CCSequence::create(CCDelayTime::create(LONGER_TIME),CCCallFunc::create(this,callfunc_selector(PlayBoard::resumeBoardLength)),NULL));
    this->resetBoardEndsLocation();
}

void PlayBoard::resumeBoardLength(){
    CCSize size = m_board->displayFrame()->getOriginalSize();
    m_board->setTextureRect(CCRect(0.0f, 0.0f, size.width - 40, size.height));
    this->resetBoardEndsLocation();
}

/* 重置边缘两块儿的位置 */
void PlayBoard::resetBoardEndsLocation(){
    CCPoint boardPoint = m_board->getPosition();
    CCSize boardSize = m_board->getContentSize();
    m_boardLeft->setPosition(ccp(boardPoint.x - boardSize.width/2,boardPoint.y));
    m_boardRight->setPosition(ccp(boardPoint.x + boardSize.width/2,boardPoint.y));
}

void PlayBoard::moveUpAndDown(){
    CCMoveBy *moveDown = CCMoveBy::create(0.1f,CCPointMake(0,-2));
    CCActionInterval *moveUp = moveDown->reverse();
    CCSequence *sequence = CCSequence::create(moveDown,moveUp,NULL);
    this->runAction(sequence);
}

void PlayBoard::notifyUpdate(){
    this->makeBoardLonger();
}

void PlayBoard::onExit(){
    CCNode::onExit();
    NOTIFICATION_CENTER->dttachObserver("tolonger");
}


 //
//  GameScene.cpp
//  AnimalAid
//
//  Created by Student_17 on 14-11-4.
//
//

#include "GameScene.h"
#include "GameBgLayer.h"
#include "AnimalNode.h"
#include "CommonDefine.h"
#include "PlayBoard.h"
#include "OverLayer.h"
#include "GameDataCenter.h"
#include "GameFountMenuLayer.h"
#include "AudioController.h"
#include "ParseLayer.h"

#define CRAZY_TIME 10.0f

bool GameScene::init(){
    if (!CCLayer::init()) {
        return false;
    }
    
    
    
    DATA_CENTER->resetLevel();
    
    /* 初始化数组 */
    this->setAnimalArr(CCArray::create());
    
    /* 添加对象 */
    this->setDifficultyLevel(normalState);
    
    /* 添加木板 */
    this->addPlayBoard();
    
    /* 注册点击事件 单点*/
    this->setTargetTouchEnabled();
    
    scheduleUpdate();
    
    if (AudioController::getInstance()->m_isBgMusicOn == true) {
        AudioController::playGameBGMusic();
    }
    AudioController::playEnterGame();
    
    /* 精灵出现的概率 */
    schedule(schedule_selector(GameScene::setGameAward), 5.0f);
    
    this->setBeginCreazy();
    
    return true;
}

/* 返回CCScene */
CCScene* GameScene::scene(){
    CCScene *scene = CCScene::create();
    
    /* 添加背景层 */
    CCLayer *bgLayer = GameBgLayer::create();
    bgLayer->setTag(1003);
    scene->addChild(bgLayer);
    
    /* 游戏层 */
    CCLayer *layer = GameScene::create();
    layer->setTag(1002);
    scene->addChild(layer);
    
    /* 添加前面板层*/
    CCLayer *fountLayer = GameFountMenuLayer::create();
    fountLayer->setTag(1001);
    scene->addChild(fountLayer);
    
    
    return scene;
}

#pragma mark - 添加动物 设置难度

/* 设置游戏难度 */
void GameScene::setDifficultyLevel(GameState state){
    float addAnimalTime = 0.0f;
    if (state == normalState) {
        addAnimalTime = 1.3f;
    }else{
        addAnimalTime = 0.6f - DATA_CENTER->m_score / 1000 /10;
    }
    unschedule(schedule_selector(GameScene::addOneAnimal));
    schedule(schedule_selector(GameScene::addOneAnimal), addAnimalTime);
}

/* 狂热模式时间 */
void GameScene::setBeginCreazy(){
    float time = 20.0f + arc4random()%20;
    unschedule(schedule_selector(GameScene::beginCrazeState));
    schedule(schedule_selector(GameScene::beginCrazeState), time);
}

/* 添加动物 将添加的所有动物放到数组中*/
void GameScene::addOneAnimal(){
    AnimalNode *animal = AnimalNode::create();
    this->addChild(animal);
    m_animalArr->addObject(animal);
    BeginLocation location;
    int x =arc4random()%4;
    if (x == 0 || x == 1) {
        location = lowPoint;
    }else{
        location = x == 2 ? middlePoint : hightPoint;
    }
    animal->runToJumpPoint(location);
}

#pragma mark - 设置游戏木板

/* 添加游戏木板 */
void GameScene::addPlayBoard(){
    m_board = PlayBoard::create();
    m_board->setPosition(ccp(240,100));
    m_boardEndPoint = m_board->getPosition();
    this->addChild(m_board);
}

void GameScene::setGameAward(){
    
    int type = arc4random() % 8;
    switch (type) {
        case 1:{
            m_gameAward = CCSprite::createWithSpriteFrame(SPRITE_FRAME_CACHE("makeLonger.png"));
            m_gameAward->setTag(2);
            break;
        }
        case 2:{
            m_gameAward = CCSprite::createWithSpriteFrame(SPRITE_FRAME_CACHE("addHeart.png"));
            m_gameAward->setTag(3);
            break;
        }
        case 3:{
            m_gameAward = CCSprite::createWithSpriteFrame(SPRITE_FRAME_CACHE("coin.png"));
            m_gameAward->setTag(4);
            break;
        }
        default:{
            CCParticleFire *smoke = CCParticleFire::create();
            smoke->setScale(0.2);
            smoke->setPosition(50, 10);
            m_gameAward = CCSprite::createWithSpriteFrame(SPRITE_FRAME_CACHE("bomb.png"));
            m_gameAward->addChild(smoke);
            AudioController::playBombComing();
            m_gameAward->setTag(1);
            break;
        }
    }
    
    this->addChild(m_gameAward);
    arc4random()%10 > 5 ? m_gameAward->setPosition(ccp(500, 320)) : m_gameAward->setPosition(ccp(-50, 320));
    m_gameAward->setScale(0.6);
    CCJumpTo *jump = CCJumpTo::create(2.5f , ccp(160 + arc4random()%200, -20), 120, 1);
    CCRotateTo *rotate = CCRotateTo::create(2.5f, 800);
    m_gameAward->runAction(CCSpawn::create(jump,rotate,NULL));
    
}


#pragma mark - 碰撞检测 跑出检测 
/* Schedu Update */
void GameScene::update(float dtime){
    this->manDetection();
    /* 炸弹删除 */
    if(m_gameAward != NULL && DATA_CENTER->m_heartNum > 0){
        if (m_gameAward->boundingBox().intersectsRect(m_board->getBoundingBox())) {
            /* 是炸弹 */
            switch (m_gameAward->getTag()) {
                case 1:{
                    CCParticleSystem *ecplosion = CCParticleSystemQuad::create("expotionPartical.plist");
                    ecplosion->setPosition(m_board->getPosition());
                    m_board->removeFromParentAndCleanup(true);
                    
                    this->unscheduleAllSelectors();
                    m_board = NULL;
                    
                    this->runAction(CCSequence::create(CCDelayTime::create(1),CCCallFunc::create(this, callfunc_selector(GameScene::addGameOverLayer)),NULL));
                    
                    this->addChild(ecplosion);
                    SIMPLE_AUDIO->stopAllEffects();
                    AudioController::playExplosion();
                    break;
                }
                case 2:{
                    m_board->makeBoardLonger();
                    AudioController::playBoardToLong();
                    break;
                }
                case 3:{
                    if (DATA_CENTER->m_heartNum < 5) {
                    CCLog("now have %d heart", DATA_CENTER->m_heartNum);
                    DATA_CENTER->m_heartNum += 1;
                    }
                    AudioController::playGetLife();
                }
                case 4:{
                    DATA_CENTER->m_moneyNum++;
                    AudioController::playGetOneCoin();
                    break;
                }
                default:
                    break;
            }
            
            m_gameAward->removeFromParentAndCleanup(true);
            m_gameAward = NULL;
            
        }else if (m_gameAward->getPosition().y < -20){
            m_gameAward->removeFromParentAndCleanup(true);
            m_gameAward = NULL;
            SIMPLE_AUDIO->stopAllEffects();
}
    }
    
    
}


void GameScene::manDetection(){
    /* 遍历 将 跑出屏幕的动物删除 */
    CCObject *obj;
    CCARRAY_FOREACH(m_animalArr, obj){
        AnimalNode * node = (AnimalNode*)(CCNode*)obj;
        CCPoint location = node->getPosition();
        
        /* 与木板发生碰撞 */
        if (m_board->getBoundingBox().intersectsRect(node->getBoundingBox())) {
            CCPoint boardPoint = m_board->getBoundingBox().origin;
            CCPoint animalPoint = node->getBoundingBox().origin;
            if (boardPoint.y > animalPoint.y && node->m_isMoveDown == false) {
                if (boardPoint.x > animalPoint.x ) {
                    node->moveDownOut(0);
                }else{
                    node->moveDownOut(1);
                }
                
            }
            
            if (boardPoint.y  < animalPoint.y && node->m_isJumpToBoard == false) {
                m_board->moveUpAndDown();
                node->jumpToBoard();
                AudioController::playManOnBoard();
                DATA_CENTER->m_score += node->m_score;
            }
        }
        
        if (location.x > 500 || location.y < -40) {
            if (location.y < m_board->getPosition().y) {
                DATA_CENTER->m_heartNum -= 1;
                this->addManSoul(location);
                this->gameOverStopUpdate();
                AudioController::playManDieth();
                
            }
            m_animalArr->removeObject(node);
            node->removeFromParentAndCleanup(true);
        }
    }

}

#pragma mark - 点击事件 滑动 board
void GameScene::setTargetTouchEnabled(){
    SHARED_DIRECTOR->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    
    m_beginPoint = pTouch->getLocation();
    return true;
}

void GameScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    float shiftX = m_boardEndPoint.x + (pTouch->getLocation().x - m_beginPoint.x) * 1.5f;
    if(shiftX < 120 || shiftX > 360){
        return;
    }
    if (m_board == NULL) {
        return;
    }
    m_board->setPosition(ccp(shiftX,100.0f));
}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    if (m_board == NULL) {
        return;
    }
    m_boardEndPoint = m_board->getPosition();
}


#pragma mark - 游戏暂停
/* 通知中心方法 */
void GameScene::notifyUpdate(){
}


void GameScene::gameOverStopUpdate(){
    if (DATA_CENTER->m_heartNum <= 0 || m_board == NULL) {
        this->unschedule(schedule_selector(GameScene::addOneAnimal));
        this->unschedule(schedule_selector(GameScene::setGameAward));
        this->unschedule(schedule_selector(GameScene::beginCrazeState));
        this->unscheduleUpdate();
    }
    if (m_board == NULL) {
        SHARED_DIRECTOR->getTouchDispatcher()->removeDelegate(this);
    }
}

#pragma mark - 难度设定
/* 进入狂热状态 */
void GameScene::beginCrazeState(){
    if (DATA_CENTER->m_heartNum <= 0) {
        this->stopAllActions();
        return;
    }
    AudioController::playCrazyState();
    CCNode *node = this->getParent()->getChildByTag(1003);
    ((GameBgLayer*)node)->goEnterCrazyState();
    YJNotificationCenter::getInstance()->notifyForKey("tolonger");
    this->setDifficultyLevel(creazeState);
    this->runAction(CCSequence::create(CCDelayTime::create(CRAZY_TIME),CCCallFunc::create(this, callfunc_selector(GameScene::beginNormalState)),NULL));
}

void GameScene::beginNormalState(){
    if (DATA_CENTER->m_heartNum > 0) {
        SIMPLE_AUDIO->stopAllEffects();
        if (AudioController::getInstance()->m_isBgMusicOn == true) {
            SIMPLE_AUDIO->resumeBackgroundMusic();
        }
        this->setBeginCreazy();
        this->setDifficultyLevel(normalState);
    }
}


void GameScene::addGameOverLayer(){
    this->getParent()->getChildByTag(1001)->removeFromParentAndCleanup(true);
    this->getParent()->addChild(OverLayer::create());
}

/* 增加灵魂 */
void GameScene::addManSoul(CCPoint point){
    CCSprite *soul = CCSprite::createWithSpriteFrameName("soul.png");
    soul->setPosition(point);
    CCSequence *spa = CCSequence::create(CCMoveBy::create(2,CCPoint(0,320)),CCCallFuncN::create(this, callfuncN_selector(GameScene::removeManSoul)),NULL);
    soul->runAction(CCFadeOut::create(2));
    this->addChild(soul);
    soul->setScale(0.6);
    soul->setOpacity(90);
    soul->runAction(spa);
}

void GameScene::removeManSoul(cocos2d::CCNode *pNode){
    pNode->removeFromParentAndCleanup(true);
}

void GameScene::onEnter(){
    CCLayer::onEnter();
}

void GameScene::onExit(){
    CCLayer::onExit();
}

GameScene::~GameScene(){
    SHARED_DIRECTOR->getTouchDispatcher()->removeDelegate(this);
    m_animalArr->release();
}
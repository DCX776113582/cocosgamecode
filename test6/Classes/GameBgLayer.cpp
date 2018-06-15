//
//  GameBgLayer.cpp
//  AnimalAid
//
//  Created by Student_17 on 14-11-1.
//
//

#include "GameBgLayer.h"
#include "GameDataCenter.h"
bool  GameBgLayer::init(){
    if (!CCLayer::init()) {
        return false;
    }
    this->initalizeBg();
    
    return true;
}

/* 根据当前的选关,选择背景图片 */
void GameBgLayer::initalizeBg(){
    int levelNum = GameDataCenter::getInstance()->getSelectLevelNum();
    auto bgNmame = StringUtils::format("levelBG/levelBG%d.png",levelNum);
    auto bg = Sprite::create(bgNmame);
    bg->setAnchorPoint(Vec2(0, 0));
    this->addChild(bg);
}

void GameBgLayer::goEnterCrazyState(){
    LayerGradient *night = LayerGradient::create(Color4B(0, 0, 0, 180 ), Color4B(0, 0, 0, 60));
    night->setTag(1001);
    night->runAction(FadeIn::create(1.5f));
    this->addChild(night);
    CallFunc::create([](){});
    night->runAction(Sequence::create(DelayTime::create(10),FadeOut::create(1.5f),CallFuncN::create([this](Ref*psender) {
        auto ps = (Node*)psender;
        GameBgLayer::goOutCrazyState(ps);}), nullptr));
}

void GameBgLayer::goOutCrazyState(Node *pNode){
    this->removeChildByTag(1001, true);
}
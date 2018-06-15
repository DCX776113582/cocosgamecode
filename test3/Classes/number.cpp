//
//  number.cpp
//  FishMan
//
//  Created by MAC on 16/6/29.
//
//

#include "number.hpp"
//初始化
bool Number::init(NumStyle style)
{
    if (!Sprite::init()) {
        return false;
    }
    m_texture = nullptr;
    m_style = style;
    m_num = 0;
    m_nPosCur = 0;
    m_nPosEnd = 0;
    this->setup();
    return true;
}
//设置图片的纹理
void Number::setup()
{
    m_texture = Director::getInstance()->getTextureCache()->addImage("sprites/number.png");
    SpriteFrame* frame = SpriteFrame::createWithTexture(m_texture, Rect(0, 0, WIDTH, HEIGHT));
    this->setSpriteFrame(frame);
}
//设置显示的数字
void Number::setNumber(int num)
{
    m_nPosCur = m_num * HEIGHT;
    m_nPosEnd = num * HEIGHT;
    if (NumStyleNormal == m_style)
    {
        m_nMoveLen = 4;
    }
    else if (NumStyleSameTime==m_style){
        m_nMoveLen = (m_nPosEnd - m_nPosCur)/HEIGHT;
    }
    if (m_num>num) {
        this->schedule(schedule_selector(Number::onRollUP), 0.05);
    }
    else
        this->schedule(schedule_selector(Number::onRollDown), 0.05);
    m_num = num;
}
//向上滚动
void Number::onRollUP(float dt){
    m_nPosCur -=m_nMoveLen;
    if (m_nPosCur<=m_nPosEnd) {
        m_nPosCur = m_nPosEnd;
        this->unschedule(schedule_selector(Number::onRollUP));
    }
    
    SpriteFrame* frame = SpriteFrame::createWithTexture(m_texture,Rect(0,m_nPosCur,WIDTH,HEIGHT));
    this->setSpriteFrame(frame);
}

//向下滚动
void Number::onRollDown(float dt){
    m_nPosCur +=m_nMoveLen;
    if (m_nPosCur>=m_nPosEnd) {
        m_nPosCur = m_nPosEnd;
        this->unschedule(schedule_selector(Number::onRollDown));
    }
    SpriteFrame* frame = SpriteFrame::createWithTexture(m_texture,Rect(0,m_nPosCur,WIDTH,HEIGHT));
    this->setSpriteFrame(frame);
}




























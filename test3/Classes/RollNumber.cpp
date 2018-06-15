//
//  RollNumber.cpp
//  FishMan
//
//  Created by MAC on 16/7/1.
//
//

#include "RollNumber.hpp"
bool RollNumber::init(){
    if (!Node::init()) {
        return false;
    }
    m_nNumber = 0;
    m_maxCol = 6;
    numArray = new Vector<Number*>();
    //开启0填充
    zeroFill = true;
    style = NumStyleNormal;
    this->clearEffect();
    return true;
}

/*
 * getNumber 获取显示的数字
 */
int RollNumber::getNumber(){
    return m_nNumber;
}

/*
 * setNumber 设置显示的数字
 * num int 设置的数字
 */
void RollNumber::setNumber(int num){
    if (m_nNumber!=num) {
        m_nNumber = num;
        this->rebuildEffect();
    }
}

/*
 * rebuildEffect 重新设置每位数字
 */
void RollNumber::rebuildEffect(){
    int i =0;
    int num = m_nNumber;
    while (1) {
        if (num<=0)
        {
            if (m_maxCol <= i && zeroFill)
            {
                break;
            }
        }
        //依次是个位、十位、百位、千位、、、、、、
        int showNum = num%10;
        Number* pNumber = numArray->at(i);
        pNumber->setNumber(showNum);
        ++i;
        num = num/10;
    }
}

/*
 * rebuildEffect 清除每位数字
 */
void RollNumber::clearEffect()
{
    for(int i=0;i<numArray->size();++i) {
        
        Number* pNumber = numArray->at(i);
        pNumber->removeFromParentAndCleanup(true);
    }
    numArray->clear();
    
    for (int i=0; i< m_maxCol; i++) {
        Number* pNumber = Number::creat(style);
        numArray->pushBack(pNumber);
        pNumber->setNumber(0);
        pNumber->setPosition(Vec2(0-i*WIDTH,0));
        pNumber->setAnchorPoint(Vec2(1,0.5));
        this->addChild(pNumber,10);
    }
}


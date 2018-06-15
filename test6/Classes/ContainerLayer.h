//
//  ContainerLayer.h
//  SaveTheNinja
//
//  Created by fly on 14-11-22.
//
//

#ifndef __SaveTheNinja__ContainerLayer__
#define __SaveTheNinja__ContainerLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;

class ContainerLayer:public CCLayer
{
public:
    virtual bool init();
    CREATE_FUNC(ContainerLayer);
    void initData();
    
public:
    void buttonCallfunc(CCObject *pSender);
};
#endif /* defined(__SaveTheNinja__ContainerLayer__) */

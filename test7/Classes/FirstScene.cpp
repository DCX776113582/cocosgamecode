//
//  FirstScene.cpp
//  sanxiao
//
//  Created by MAC on 2018/5/29.
//
//

#include "FirstScene.hpp"
Scene* First::createScene()
{
    auto scene = Scene::create();
    auto layer = First::create();
    scene->addChild(layer);
    return scene;
}
bool First::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto node = CSLoader::createNode("Layer1.csb");
    this->addChild(node);
    auto bt1 = node->getChildByName<Button*>("Button_2");
    bt1->addClickEventListener([](Ref*sender){
        auto scene = Start::createScene();//创建章节场景
        auto trans = TransitionFlipX::create(2, scene);//跳转动作
        Director::getInstance()->replaceScene(trans);//跳转场景
    });
    
    return true;
}
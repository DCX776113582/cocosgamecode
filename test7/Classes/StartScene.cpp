//
//  StartScene.cpp
//  sanxiao
//
//  Created by MAC on 2018/5/29.
//
//

#include "StartScene.hpp"
Scene* Start::createScene()
{
    auto scene = Scene::create();
    auto layer = Start::create();
    scene->addChild(layer);
    return scene;
}
bool Start::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto node = CSLoader::createNode("Layer2.csb");
    this->addChild(node);
    auto bt1 = node->getChildByName<Button*>("Button_1");
    bt1->addClickEventListener([](Ref*sender){
        auto scene = xuanguan::createScene();//创建章节场景
        auto trans = TransitionFlipX::create(2, scene);//跳转动作
        Director::getInstance()->replaceScene(trans);//跳转场景
    });
    
    return true;
}
//
//  logon.cpp
//  MyGame-mobile
//
//  Created by Admin on 2018/5/26.
//

#include "logon.hpp"
Scene* FirstScene::createScene()//创建开始场景
{
    auto scene = Scene::create();//创建场景
    auto layer = FirstScene::create();//创建图层
    scene->addChild(layer);//图层添加场景
    return scene;//返回场景
}
bool FirstScene::init(){
    if (!Layer::init()) {
        return false;
    }
    visableSize = Director::getInstance()->getVisibleSize();//获取可视区域大小
    userDefault = UserDefault::getInstance();//获取实例用于保存到本地
    music = SimpleAudioEngine::getInstance();//定义并初始化，获取声音实例
    auto firstScene = CSLoader::createNode("cocos/Logon.csb");
    this->addChild(firstScene);//添加到图层
    return true;
}

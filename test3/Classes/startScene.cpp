//
//  startScene.cpp
//  FishMan
//
//  Created by MAC on 16/6/28.
//
//

#include "startScene.hpp"
#include "GameScene.hpp"
//声音头文件和命名空间
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
Scene* StartScene::createScene()
{
    
    auto scene = Scene::create();  //创建一个场景
    auto layer = StartScene::create();  //创建一个层
    scene->addChild(layer);
    return scene;
}
bool StartScene::init(){
    if (!Layer::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    //设置音效
    isSoundEfect = true;
    SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bg_music01.caf",true);
    //添加背景图片
    auto background = Sprite::create("background/firstbg.png");
    background->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    background->setScale(visibleSize.width/background->getContentSize().width, visibleSize.height/background->getContentSize().height);
    this->addChild(background);
    initUI();
    return true;
}
void StartScene::initUI()
{
//****************************关闭按钮**********************
    auto Buttonback = Button::create("menu/close.png");
    Buttonback->setAnchorPoint(Vec2(0, 1));
    Buttonback->setPosition(Vec2(0, visibleSize.height));
    Buttonback->setScale(0.6);
    Buttonback->addClickEventListener([=](Ref* pSender){
        Director::getInstance()->end();
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    });
    this->addChild(Buttonback);
    
//****************************粒子气泡**********************
   
    
    
    //创建气泡粒子效果
    ParticleSystemQuad* emitter = ParticleSystemQuad::create("effect/qipaom.plist");
    emitter->setPosition(Vec2(visibleSize.width/2, 50));
    //是否自动移除在结束后
    emitter->setAutoRemoveOnFinish(true);
    //每秒几个粒子发出
    emitter->setEmissionRate(2);
    //循环多少秒，－1永久循环
    emitter->setDuration(-1);
    this->addChild(emitter,1);
    
    
    
    
//****************************开始按钮**********************
    auto Buttonstart = Button::create("menu/start.png");
    Buttonstart->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2-30));
    Buttonstart->setScale(2);
    this->addChild(Buttonstart,2);
    Buttonstart->addClickEventListener([=](Ref* pSender){
        //添加Label
        auto label = Label::createWithSystemFont("Load......", "fonts/Marker Felt.ttf", 25);
        label->setPosition(Vec2(visibleSize.width/2+10,visibleSize.height/2 - 70));
        label->setColor(Color3B::RED);
        this->addChild(label);
        //添加进度条
        auto progresstime1 = ProgressTimer::create(Sprite::create("menu/jindutiao.png"));
        progresstime1->setPosition(Vec2(Vec2(visibleSize.width/2, visibleSize.height/2-105)));
        progresstime1->setType(ProgressTimer::Type::BAR);
        progresstime1->setMidpoint(Vec2(0,0.5));
        progresstime1->setBarChangeRate(Vec2(1,0));
        this->addChild(progresstime1);
        auto action1 = ProgressFromTo::create(4,0, 100);
        
        //添加过渡动画
        auto _callFUncN = CallFuncN::create([=](Ref* pSender){
            //TransitionScene场景转换的基类
            TransitionScene* scene = TransitionPageTurn::create(1,GameScene::createScene(),true);
            Director::getInstance()->replaceScene(scene);
        });
        auto action = Sequence::create(action1,_callFUncN, NULL);
        progresstime1->runAction(action);
    });
//****************************音乐按钮**********************
    auto menuitem1 = MenuItemImage::create("menu/bg_music_open.png","menu/bg_music_open.png");
    auto menuitem2 = MenuItemImage::create("menu/bg_music_close.png","menu/bg_music_close.png");
    auto menutoggle = MenuItemToggle::create();
    menutoggle->addSubItem(menuitem1);
    menutoggle->addSubItem(menuitem2);
    menutoggle->setSelectedIndex(0);
    menutoggle->setScale(2);
    menutoggle->setAnchorPoint(Vec2(1, 1));
    menutoggle->setPosition(Vec2(visibleSize.width, visibleSize.height));
    menutoggle->setCallback([=](Ref* pSender){
        auto menuToggle = (MenuItemToggle*)pSender;
        int i = menuToggle->getSelectedIndex();
        switch (i) {
            case 0:
                cout<<"select index is: "<<i<<endl;
                isSoundEfect = true;
                SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bg_music01.caf",true);
                break;
            case 1:
                cout<<"select index is: "<<i<<endl;
                isSoundEfect = false;
                SimpleAudioEngine::getInstance()->stopBackgroundMusic();
                SimpleAudioEngine::getInstance()->stopAllEffects();
                break;
            default:
                break;
        }
    });
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    menu->addChild(menutoggle);
    this->addChild(menu,1);
}



















//
//  Chapter.cpp
//  DefendTheRadish
//
//  Created by mac on 18/4/14.
//
//

#include "Chapter.hpp"
#include "Adventure.hpp"
#include "GameScene.hpp"
Layer* CheckpointScene::create(int chapter)//重写create，参数为章节数、关卡数
{
    CheckpointScene* layer = new CheckpointScene();//new出一个场景
    //如果存在
    if(layer && layer->init(chapter))
    {
        layer->autorelease();//自动释放池
        return layer;//返回图层
    }
    CC_SAFE_DELETE(layer);
    layer = nullptr;
    return nullptr;
}
Scene* CheckpointScene::createScene(int chapter)//创建开始场景
{
    auto scene = Scene::create();//创建场景
    auto layer = CheckpointScene::create(chapter);//创建图层
    scene->addChild(layer);//图层添加场景
    return scene;//返回场景
}
bool CheckpointScene::init(int chapter){
    if (!Layer::init()) {
        return false;
    }
    _chapter = chapter;
    visableSize = Director::getInstance()->getVisibleSize();//获取可视区域大小
    checkpointScene = CSLoader::createNode("Chapter.csb");
    this->addChild(checkpointScene);
    back();
    pageview();
    choose();
    return true;
}
void CheckpointScene::back()
{
    auto back  = checkpointScene->getChildByName<Button*>("Button_1");
    back->addClickEventListener([=](Ref*sender){
        auto scene = AdventureModeScene::createScene();
        auto trans = TransitionCrossFade::create(0.5,scene);
        Director::getInstance()->replaceScene(trans);
    });
}
void CheckpointScene::pageview()
{
    sp1 = checkpointScene->getChildByName<Sprite*>("labelImage1");
    sp2 = checkpointScene->getChildByName<Sprite*>("labelImage2");
    sp3 = checkpointScene->getChildByName<Sprite*>("labelImage3");
    sp4 = checkpointScene->getChildByName<Sprite*>("labelImage4");
    sp5 = checkpointScene->getChildByName<Sprite*>("labelImage5");
    sp6 = checkpointScene->getChildByName<Sprite*>("labelImage6");
    pageView = checkpointScene->getChildByName<PageView*>("PageView_1");
    pageView->addEventListener([=](Ref*sender,PageView::EventType type){
        if (type == PageView::EventType::TURNING) {
            auto count = dynamic_cast<PageView*>(sender);
            page = count->getCurrentPageIndex()+1;
            if (page<=2) {
                sp1->setVisible(true);
            }else{
                sp1->setVisible(false);
            }
            if (page<=4&&page>2) {
                sp2->setVisible(true);
            }else{
                sp2->setVisible(false);
            }
            if (page<=6&&page>4) {
                sp3->setVisible(true);
            }else{
                sp3->setVisible(false);
            }
            if (page<=8&&page>6) {
                sp4->setVisible(true);
            }else{
                sp4->setVisible(false);
            }
            if (page<=10&&page>8) {
                sp5->setVisible(true);
            }else{
                sp5->setVisible(false);
            }
            if (page<=12&&page>10) {
                sp6->setVisible(true);
            }else{
                sp6->setVisible(false);
            }

        }
    });
    
   
}
void CheckpointScene::choose()
{
    auto choose = checkpointScene->getChildByName<Button*>("Button_3");
    choose->addClickEventListener([=](Ref*sender){
        auto scene = GameScene::createScene(_chapter,page);
        auto trans = TransitionCrossFade::create(1,scene);
        Director::getInstance()->replaceScene(trans);
    });
}


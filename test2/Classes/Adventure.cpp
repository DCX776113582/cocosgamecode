//
//  Adventure.cpp
//  DefendTheRadish
//
//  Created by mac on 18/4/13.
//
//

#include "Adventure.hpp"
#include "Chapter.hpp"
#include "FirstScene.hpp"
Scene* AdventureModeScene::createScene()//创建开始场景
{
    auto scene = Scene::create();//创建场景
    auto layer = AdventureModeScene::create();//创建图层
    scene->addChild(layer);//图层添加场景
    return scene;//返回场景
}
bool AdventureModeScene::init(){
    if (!Layer::init()) {
        return false;
    }
    visableSize = Director::getInstance()->getVisibleSize();//获取可视区域大小
    userDefault = UserDefault::getInstance();//获取实例用于保存到本地
    music = SimpleAudioEngine::getInstance();//定义并初始化，获取声音实例
    AdventureScene = CSLoader::createNode("cocoStuio/adventure.csb");
    this->addChild(AdventureScene);//添加到图层
    check1 = AdventureScene->getChildByName<CheckBox*>("CheckBox_1");
    check2 = AdventureScene->getChildByName<CheckBox*>("CheckBox_2");
    check3 = AdventureScene->getChildByName<CheckBox*>("CheckBox_3");
    check4 = AdventureScene->getChildByName<CheckBox*>("CheckBox_4");
    check5 = AdventureScene->getChildByName<CheckBox*>("CheckBox_5");
    check6 = AdventureScene->getChildByName<CheckBox*>("CheckBox_6");
    btn1 = AdventureScene->getChildByName<Button*>("Button_10");
    btn2 = AdventureScene->getChildByName<Button*>("Button_9");
    back();
    pageview();
    check();
    button();
    return true;
}
void AdventureModeScene::back()
{
    auto back  = AdventureScene->getChildByName<Button*>("Button_2");
    back->addClickEventListener([=](Ref*sender){
        auto scene = FirstScene::createScene();
        auto trans = TransitionCrossFade::create(0.5,scene);
        Director::getInstance()->replaceScene(trans);
    });
}
void AdventureModeScene::pageview()
{
    pageView = AdventureScene->getChildByName<PageView*>("PageView_1");
    for (int i = 1; i<=6; ++i) {
        string str = StringUtils::format("Panel_%d",i);
        string str1 =StringUtils::format("Button%d",i);
        layout = pageView->cocos2d::Node::getChildByName<Layout*>(str);
        auto btn = layout->getChildByName<Button*>(str1);
        btn->addClickEventListener([=](Ref*sender){
            auto scene = CheckpointScene::createScene(i);
            auto trans = TransitionCrossFade::create(1,scene);
            Director::getInstance()->replaceScene(trans);
        });
    }
    pageView->addEventListener([=](Ref*sender,PageView::EventType type){
        if (type == PageView::EventType::TURNING) {
            auto count = dynamic_cast<PageView*>(sender);
            page = count->getCurrentPageIndex()+1;
            if (page==1) {
                btn1->setVisible(false);
            }else{
                btn1->setVisible(true);
            }
            if (page==6) {
                btn2->setVisible(false);
            }else{
                btn2->setVisible(true);
            }
            this->Check(page);
        }
    });
}
void AdventureModeScene::Check(int p)
{
    switch (p) {
        case 1:
            check2->setSelected(false);
            check3->setSelected(false);
            check4->setSelected(false);
            check5->setSelected(false);
            check6->setSelected(false);
            check1->setSelected(true);
            break;
        case 2:
            check2->setSelected(true);
            check3->setSelected(false);
            check4->setSelected(false);
            check5->setSelected(false);
            check6->setSelected(false);
            check1->setSelected(false);
            break;
        case 3:
            check2->setSelected(false);
            check3->setSelected(true);
            check4->setSelected(false);
            check5->setSelected(false);
            check6->setSelected(false);
            check1->setSelected(false);
            break;
        case 4:
            check2->setSelected(false);
            check3->setSelected(false);
            check4->setSelected(true);
            check5->setSelected(false);
            check6->setSelected(false);
            check1->setSelected(false);
            break;
        case 5:
            check2->setSelected(false);
            check3->setSelected(false);
            check4->setSelected(false);
            check5->setSelected(true);
            check6->setSelected(false);
            check1->setSelected(false);
            break;
        case 6:
            check2->setSelected(false);
            check3->setSelected(false);
            check4->setSelected(false);
            check5->setSelected(false);
            check6->setSelected(true);
            check1->setSelected(false);
            break;
        default:
            break;
    }
}
void AdventureModeScene::check()
{
    /*for (int i = 1; i<=6; ++i) {
        string str = StringUtils::format("CheckBox_%d",i);
        check1 = AdventureScene->getChildByName<CheckBox*>(str);
        check1->setTag(i);
        checknum[i-1] = check1->getTag();
        check1->addEventListener([=](Ref*sender,CheckBox::EventType type){
            switch (check1->getTag()) {
                case 1:
                    switch (type) {
                        case CheckBox::EventType::SELECTED:
                            if (check1->getTag()==1) {
                                check1->setSelected(true);
                                btn1->setVisible(false);
                                btn2->setVisible(true);
                            }else{
                                check1->setSelected(false);
                            }
                            pageView->setCurrentPageIndex(i-1);
                            
                            break;
                        case CheckBox::EventType::UNSELECTED:
                            check1->setSelected(false);
                            break;
                        default:
                            break;
                    }

                    break;
                    
                default:
                    break;
            }
        });
    }*/
    check1->addEventListener([=](Ref*sender,CheckBox::EventType type){
            switch (type) {
            case CheckBox::EventType::SELECTED:
                check2->setSelected(false);
                check3->setSelected(false);
                check4->setSelected(false);
                check5->setSelected(false);
                check6->setSelected(false);
                check1->setSelected(true);
                pageView->setCurrentPageIndex(0);
                btn1->setVisible(false);
                btn2->setVisible(true);
                break;
            case CheckBox::EventType::UNSELECTED:
                check1->setSelected(false);
                break;
            default:
                break;
        }
    });
    check2->addEventListener([=](Ref*sender,CheckBox::EventType type){
        switch (type) {
            case CheckBox::EventType::SELECTED:
                check2->setSelected(true);
                check3->setSelected(false);
                check4->setSelected(false);
                check5->setSelected(false);
                check6->setSelected(false);
                check1->setSelected(false);
                pageView->setCurrentPageIndex(1);
                btn1->setVisible(true);
                btn2->setVisible(true);
                break;
            case CheckBox::EventType::UNSELECTED:
                check2->setSelected(false);
                break;
            default:
                break;
        }
    });
    check3->addEventListener([=](Ref*sender,CheckBox::EventType type){
        switch (type) {
            case CheckBox::EventType::SELECTED:
                check2->setSelected(false);
                check3->setSelected(true);
                check4->setSelected(false);
                check5->setSelected(false);
                check6->setSelected(false);
                check1->setSelected(false);
                pageView->setCurrentPageIndex(2);
                btn1->setVisible(true);
                btn2->setVisible(true);
                break;
            case CheckBox::EventType::UNSELECTED:
                check3->setSelected(false);
                break;
            default:
                break;
        }
    });
    check4->addEventListener([=](Ref*sender,CheckBox::EventType type){
        switch (type) {
            case CheckBox::EventType::SELECTED:
                check2->setSelected(false);
                check3->setSelected(false);
                check4->setSelected(true);
                check5->setSelected(false);
                check6->setSelected(false);
                check1->setSelected(false);
                pageView->setCurrentPageIndex(3);
                btn1->setVisible(true);
                btn2->setVisible(true);
                break;
            case CheckBox::EventType::UNSELECTED:
                check4->setSelected(false);
                break;
            default:
                break;
        }
    });
    check5->addEventListener([=](Ref*sender,CheckBox::EventType type){
        switch (type) {
            case CheckBox::EventType::SELECTED:
                check2->setSelected(false);
                check3->setSelected(false);
                check4->setSelected(false);
                check5->setSelected(true);
                check6->setSelected(false);
                check1->setSelected(false);
                pageView->setCurrentPageIndex(4);
                btn1->setVisible(true);
                btn2->setVisible(true);
                break;
            case CheckBox::EventType::UNSELECTED:
                check5->setSelected(false);
                break;
            default:
                break;
        }
    });
    check6->addEventListener([=](Ref*sender,CheckBox::EventType type){
        switch (type) {
            case CheckBox::EventType::SELECTED:
                check2->setSelected(false);
                check3->setSelected(false);
                check4->setSelected(false);
                check5->setSelected(false);
                check6->setSelected(true);
                check1->setSelected(false);
                pageView->setCurrentPageIndex(5);
                btn1->setVisible(true);
                btn2->setVisible(false);
                break;
            case CheckBox::EventType::UNSELECTED:
                check6->setSelected(false);
                break;
            default:
                break;
        }
    });
     
}
void AdventureModeScene::button()
{
    btn1->setVisible(false);
    btn2->setVisible(true);
    btn1->addClickEventListener([=](Ref*sender){
        pageView->setCurrentPageIndex(page-1);
        page--;
        if (0 == page) {
            btn1->setVisible(false);
        }
        else{
            btn1->setVisible(true);
            btn2->setVisible(true);
        }
        Check(page+1);
    });
    btn2->addClickEventListener([=](Ref*sender){
        pageView->setCurrentPageIndex(page+1);
        page++;
        if (page == 5) {
            btn2->setVisible(false);
        }
        else {
            btn1->setVisible(true);
            btn2->setVisible(true);
        }
        Check(page+1);
    });
}


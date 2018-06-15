//
//  FirstScene.cpp
//  DefendTheRadish
//
//  Created by mac on 18/4/12.
//
//

#include "FirstScene.hpp"
#include "Adventure.hpp"

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
    //设置背景音乐音量大小
    //创建并初始化第一个场景
    auto firstScene = CSLoader::createNode("cocoStuio/Layer1.csb");
    this->addChild(firstScene);//添加到图层
    auto action = CSLoader::createTimeline("cocoStuio/Layer1.csb");
    action->gotoFrameAndPlay(0, 120, true);
    action->setLastFrameCallFunc(CC_CALLBACK_0(FirstScene::move,this));
    this->runAction(action);
    
    auto btn = firstScene->getChildByName<Button*>("Button_5");//获取help按钮
    //添加点击事件监听器
    btn->addClickEventListener([=](Ref*sender){
        this->help();
    });
    auto set = firstScene->getChildByName<Button*>("Button_6");
    set->addClickEventListener([=](Ref*sender){
        this->set();
    });
    auto adventure = firstScene->getChildByName<Button*>("Button_1");
    adventure->addClickEventListener([=](Ref*sender){
        auto scene = AdventureModeScene::createScene();
        auto trans = TransitionCrossFade::create(0.5,scene);
        Director::getInstance()->replaceScene(trans);
    });
    return true;
}

void FirstScene::help()
{
    auto widget = Widget::create();//创建一个widget对象 ，类似于一个层
    widget->setAnchorPoint(Vec2(0, 0));//设置锚点
    widget->setPosition(Vec2(0, 0));//设置位置
    widget->setContentSize(visableSize);//设置覆盖区域
    widget->setTouchEnabled(true);//开启触摸
    widget->setSwallowTouches(true);//吞噬触摸
    this->addChild(widget,2);//添加子类——控件
    auto node = CSLoader::createNode("cocoStuio/Node.csb");//创建节点
    widget->addChild(node);//添加
    auto pageView1 = node->getChildByName<PageView*>("PageView1");
    pageView1->setVisible(false);
    auto pageView2 = node->getChildByName<PageView*>("PageView2");
    pageView2->setVisible(false);
    auto sp1 = node->getChildByName<ImageView*>("Image_7");
    sp1->setVisible(true);
    
    auto text1 = node->getChildByName<Text*>("Text1");
    auto check1 = node->getChildByName<CheckBox*>("CheckBox_1");
    auto check2 = node->getChildByName<CheckBox*>("CheckBox_2");
    check2->setSelected(true);
    auto check3 = node->getChildByName<CheckBox*>("CheckBox_3");
    check1->addEventListener([=](Ref*sender,CheckBox::EventType type){
        switch (type) {
            case CheckBox::EventType::SELECTED:
            {
                pageView2->setVisible(false);
                sp1->setVisible(false);
                pageView1->setVisible(true);
                check2->setSelected(false);
                check3->setSelected(false);
                string str = StringUtils::format("1/4");
                text1->setString(str);
                pageView1->addEventListener([=](Ref*sender,PageView::EventType type){
                    switch (type) {
                        case PageView::EventType::TURNING:
                        {
                            auto pageView = dynamic_cast<PageView*>(sender);
                            int num = pageView->getCurrentPageIndex()+1;
                            string str = StringUtils::format("%d/4",num);
                            text1->setString(str);
                        }
                            break;
                        default:
                            break;
                    }
                    
                });
                break;}
            case CheckBox::EventType::UNSELECTED:
                pageView1->setVisible(false);
                break;
            default:
                break;
        }
    });
    check2->addEventListener([=](Ref*sender,CheckBox::EventType type){
        switch (type) {
            case CheckBox::EventType::SELECTED:
            {
                check1->setSelected(false);
                check3->setSelected(false);
                pageView1->setVisible(false);
                pageView2->setVisible(false);
                sp1->setVisible(true);
                string str = StringUtils::format("1/1");
                text1->setString(str);
            }
                break;
            case CheckBox::EventType::UNSELECTED:
            {
                sp1->setVisible(false);
            }
                break;
            default:
                break;
        }
    });
    check3->addEventListener([=](Ref*sender,CheckBox::EventType type){
        switch (type) {
            case CheckBox::EventType::SELECTED:
            {
                check1->setSelected(false);
                check2->setSelected(false);
                pageView1->setVisible(false);
                sp1->setVisible(false);
                pageView2->setVisible(true);
                string str = StringUtils::format("1/18");
                text1->setString(str);
                pageView2->addEventListener([=](Ref*sender,PageView::EventType type){
                    switch (type) {
                        case PageView::EventType::TURNING:
                        {
                            auto pageView = dynamic_cast<PageView*>(sender);
                            int num = pageView->getCurrentPageIndex()+1;
                            string str = StringUtils::format("%d/18",num);
                            text1->setString(str);
                        }
                            break;
                        default:
                            break;
                    }
                    
                });
            }
                break;
            case CheckBox::EventType::UNSELECTED:
            {
                pageView2->setVisible(false);
            }
                break;
            default:
                break;
        }
        
    });
    auto home = node->getChildByName<Button*>("Button1");
    //添加单击事件监听器，回调函数，参数为Ref*类
    home->addClickEventListener([=](Ref* sender){
        widget->removeFromParentAndCleanup(true);//删除控件
    });
}
void FirstScene::set()
{
    auto widget = Widget::create();//创建一个widget对象 ，类似于一个层
    widget->setAnchorPoint(Vec2(0, 0));//设置锚点
    widget->setPosition(Vec2(0, 0));//设置位置
    widget->setContentSize(visableSize);//设置覆盖区域
    widget->setTouchEnabled(true);//开启触摸
    widget->setSwallowTouches(true);//吞噬触摸
    this->addChild(widget,2);//添加子类——控件
    auto node = CSLoader::createNode("cocoStuio/Node1.csb");//创建节点
    widget->addChild(node);//添加
    auto bck1 = node->getChildByName<ImageView*>("Image1");
    auto bck2 = node->getChildByName<ImageView*>("Image2");
    auto bck3 = node->getChildByName<ImageView*>("Image3");
    auto check1 = node->getChildByName<CheckBox*>("CheckBox1");
    check1->setSelected(true);
//    auto musicVolume = bck1->getChildByName<CheckBox*>("CheckBox_4");
//    musicVolume->setSelected(userDefault->getBoolForKey("musicCheck"));
//    auto effect = bck1->getChildByName<CheckBox*>("CheckBox_5");
//    effect->setSelected(userDefault->getBoolForKey("effectCheck"));
    auto check2 = node->getChildByName<CheckBox*>("CheckBox2");
    auto check3 = node->getChildByName<CheckBox*>("CheckBox3");
    check1->addEventListener([=](Ref*sender,CheckBox::EventType type){
        switch (type) {
            case CheckBox::EventType::SELECTED:
            {
                check2->setSelected(false);
                check3->setSelected(false);
                bck2->setVisible(false);
                bck3->setVisible(false);
                bck1->setVisible(true);
                
                break;}
            case CheckBox::EventType::UNSELECTED:
                bck1->setVisible(false);
                break;
            default:
                break;
        }
        
    });
    check2->addEventListener([=](Ref*sender,CheckBox::EventType type){
        switch (type) {
            case CheckBox::EventType::SELECTED:
            {
                check1->setSelected(false);
                check3->setSelected(false);
                bck1->setVisible(false);
                bck3->setVisible(false);
                bck2->setVisible(true);

                break;}
            case CheckBox::EventType::UNSELECTED:
                bck2->setVisible(false);
                break;
            default:
                break;
        }
        
    });
    check3->addEventListener([=](Ref*sender,CheckBox::EventType type){
        switch (type) {
            case CheckBox::EventType::SELECTED:
            {
                check2->setSelected(false);
                check1->setSelected(false);
                bck1->setVisible(false);
                bck2->setVisible(false);
                bck3->setVisible(true);
                break;}
            case CheckBox::EventType::UNSELECTED:
                bck3->setVisible(false);
                break;
            default:
                break;
        }
        
    });
    auto home = node->getChildByName<Button*>("Button_1");
    //添加单击事件监听器，回调函数，参数为Ref*类
    home->addClickEventListener([=](Ref* sender){
        widget->removeFromParentAndCleanup(true);//删除控件
    });
}
void FirstScene::exitApp()//退出程序
{
    auto exit = MenuItemImage::create("CloseNormal.png","CloseSelected.png", CC_CALLBACK_1(FirstScene::menuCloseCallback, this));
    exit->setAnchorPoint(Vec2(1,0));
    exit->setPosition(Vec2(visableSize.width,0));
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    menu->addChild(exit);
    this->addChild(menu);
}
void FirstScene::menuCloseCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
}


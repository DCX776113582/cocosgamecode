//
//  FistScene.cpp
//  AngryBird
//
//  Created by mac on 18/4/9.
//
//

#include "FistScene.hpp"
#include "Chapter.hpp"
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
    music->playBackgroundMusic("bg_startgamescene.mp3");//播放背景音乐
    //设置背景音乐音量大小
    music->setBackgroundMusicVolume(userDefault->getDoubleForKey("MusicVolume"));
    //创建并初始化第一个场景
    auto firstScene = CSLoader::createNode("cocoStuio/Layer1.csb");
    this->addChild(firstScene);//添加到图层
    auto btn = firstScene->getChildByName<Button*>("Button_2");//获取菜单按钮
    //添加点击事件监听器
    btn->addClickEventListener([=](Ref*sender){
        this->SetTheBox();//设置模态框
    });
    auto play = firstScene->getChildByName<Button*>("Button_3");//获取play按钮
    //添加点击事件监听器
    play->addClickEventListener([](Ref*sender){
        auto scene = ChapterScene::createScene();//创建章节场景
        auto trans = TransitionFlipX::create(2, scene);//跳转动作
        Director::getInstance()->replaceScene(trans);//跳转场景
    });
    return true;//返回true
}
void FirstScene::SetTheBox()
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
    auto slider1 = node->getChildByName<Slider*>("Slider_1");//从node获取滑动器1
    slider1->setEnabled(userDefault->getBoolForKey("Slider1"));//设置滑动器1是否禁用
    slider1->setPercent(userDefault->getIntegerForKey("Percent1"));//设置滑动器1百分比
    music->playEffect("about.mp3");
    music->setEffectsVolume(slider1->getPercent());
    slider1->addEventListener([=](Ref*sender,Slider::EventType type){
        //如果类型==滑动器类型：：在百分比变化
        if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
            //将Ref*动态转换为Slider*
            Slider*slider = dynamic_cast<Slider*>(sender);
            //设置滑动器百分比
            userDefault->setIntegerForKey("Percent1",slider->getPercent());
            int percent = userDefault->getIntegerForKey("Percent1");//获取滑动器百分比

            music->setEffectsVolume((percent++)*0.01);
            //保存音效大小
            userDefault->setDoubleForKey("EffectsVolume", music->getEffectsVolume());
            userDefault->flush();//保存

        }
    });
    
    auto slider2 = node->getChildByName<Slider*>("Slider_2");//从node获取滑动器2
    slider2->setEnabled(userDefault->getBoolForKey("Slider2"));//设置滑动器2是否禁用
    slider2->setPercent(userDefault->getIntegerForKey("Percent2"));//设置滑动器2百分比
    music->setBackgroundMusicVolume(slider2->getPercent());
    slider2->addEventListener([=](Ref*sender,Slider::EventType type){
        //如果类型==滑动器类型：：在百分比变化
        if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
            //将Ref*动态转换为Slider*
            Slider*slider = dynamic_cast<Slider*>(sender);
            //设置背景音乐音量（0-1）
            userDefault->setIntegerForKey("Percent2",slider->getPercent());//设置滑动器
            int percent = userDefault->getIntegerForKey("Percent2");//获取滑动器百分比
            
            music->setBackgroundMusicVolume((percent++)*0.01);//背景音乐声音
            //设置保存背景音乐音量大小
            userDefault->setDoubleForKey("MusicVolume",music->getBackgroundMusicVolume());
            userDefault->flush();//保存
        }
    });
    
    auto check1 = node->getChildByName<CheckBox*>("CheckBox_1");
        //添加事件监听器，参数为Ref*，复选框::事件类型
    check1->addEventListener([=](Ref*sender,CheckBox::EventType type){
       
        switch (type) {
            case CheckBox::EventType::SELECTED://复选框事件类型：选中
                userDefault->setBoolForKey("Slider1",true);//设置
                slider1->setEnabled(userDefault->getBoolForKey("Slider1"));//滑动器可用
                userDefault->flush();//保存

                break;//跳出switch
            case CheckBox::EventType::UNSELECTED://复选框事件类型：没选中
                userDefault->setBoolForKey("Slider1",false);//设置
                slider1->setEnabled(userDefault->getBoolForKey("Slider1"));//滑动器禁用
                userDefault->flush();//保存

                //简单的音频引擎::获取实例-》设置音效大小（0）
                SimpleAudioEngine::getInstance()->setEffectsVolume(0);
                break;//跳出switch
            default:
                break;//跳出switch
        }
    });
    auto check2 = node->getChildByName<CheckBox*>("CheckBox_2");

    
    //添加事件监听器，参数为Ref*，复选框::事件类型
    check2->addEventListener([=](Ref*sender,CheckBox::EventType type){
            switch (type) {
            case CheckBox::EventType::SELECTED://复选框事件类型：选中
            {
                userDefault->setBoolForKey("Slider2",true);
                slider2->setEnabled(userDefault->getBoolForKey("Slider2"));//滑动器可用
                userDefault->flush();
                //设置背景音乐音量大小为0
                SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);
            }
                break;
            case CheckBox::EventType::UNSELECTED://复选框事件类型：没选中
                userDefault->setBoolForKey("Slider2",false);
                slider2->setEnabled(userDefault->getBoolForKey("Slider2"));//滑动器禁用
                userDefault->flush();
                break;
            default:
                break;
        }
    });
    auto ok = node->getChildByName<Button*>("Button_1");
    //添加单击事件监听器，回调函数，参数为Ref*类
    ok->addClickEventListener([=](Ref* sender){
        cout<<"_btn1"<<endl;//输出到屏幕
        userDefault->flush();
        log("%s",userDefault->getXMLFilePath().c_str());
        widget->removeFromParentAndCleanup(true);//删除控件
    });
}

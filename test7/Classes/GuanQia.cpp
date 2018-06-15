//
//  GuanQia.cpp
//  sanxiao
//
//  Created by MAC on 2018/5/29.
//
//

#include "GuanQia.hpp"
#include "StartScene.hpp"
//using namespace cocos2d::ui;
//using namespace std;
//USING_NS_CC;
Scene* xuanguan::createScene()
{
    auto scene = Scene::create();
    auto layer = xuanguan::create();
    scene->addChild(layer);
    return scene;
}
bool xuanguan::init()
{
    if (!Layer::init())
    {
        return false;
    }
    SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3");
    auto userDefault = UserDefault::getInstance();
    userDefault->setBoolForKey("bool", true);
    userDefault->setIntegerForKey("www", 5);


    Jsonjiexi();
    auto node = CSLoader::createNode("Layer3.csb");
    this->addChild(node);
    virableSize = Director::getInstance()->getVisibleSize();
    auto Bt1 = node->getChildByName<Button*>("Button_15");
    Bt1->addClickEventListener([=](Ref*sender){
        auto widget = Widget::create();
        widget->setAnchorPoint(Vec2(0, 0));//设置锚点
        widget->setPosition(Vec2(0, 0));//设置位置
        widget->setContentSize(virableSize);
        widget->setTouchEnabled(true);
        widget->setSwallowTouches(true);
        this->addChild(widget);

        auto node1 = CSLoader::createNode("Node.csb");
        node1->setPosition(Vec2(virableSize.width/2,virableSize.height/2));
        widget->addChild(node1,5);

        auto slider1 = node1->getChildByName<Slider*>("Slider_1");//创建滑动器
        slider1->setMaxPercent(10);//设置最大百分比
        slider1->setPercent(userDefault->getIntegerForKey("www"));
        slider1->setEnabled(true);//滑动器禁用
        //        userDefault->setBoolForKey("bool",true);
        //添加事件监听器，参数为Ref*，滑动器::事件类型
        slider1->addEventListener([=](Ref*sender,Slider::EventType type){
            //如果类型==滑动器类型：：在百分比变化
            if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
                //将Ref*动态转换为Slider*
                Slider*slider = dynamic_cast<Slider*>(sender);
                userDefault->setBoolForKey("bool", true);
                int percent = slider->getPercent();//获取滑动器的百分比
                int maxPercent = slider->getMaxPercent();//获取滑动器的最大百分比
                //简单的音频引擎::获取实例-》设置音效大小（音量大小0——1）
                SimpleAudioEngine::getInstance()->setEffectsVolume((percent++)*0.1);
                log("Percent %f",10.0*percent/maxPercent);//输出
            }
            userDefault->setIntegerForKey("www", slider1->getPercent());
        });

        auto checkBox1 = node1->getChildByName<CheckBox*>("CheckBox_1");
        checkBox1->setSelected(userDefault->getBoolForKey("bool"));
        //添加事件监听器，参数为Ref*，复选框::事件类型
        checkBox1->addEventListener([=](Ref*sender,CheckBox::EventType type){
            switch (type) {
                case CheckBox::EventType::SELECTED://复选框事件类型：选中
                    slider1->setEnabled(true);//滑动器可用
                    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
                    break;//跳出switch
                case CheckBox::EventType::UNSELECTED://复选框事件类型：没选中
                    slider1->setEnabled(false);//滑动器禁用
                    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
                    //
                    break;//跳出switch
                default:
                    break;//跳出switch
            }
            userDefault->setBoolForKey("bool", checkBox1->isSelected());
        });
        auto Bt2 = node1->getChildByName<Button*>("Button_1");
        Bt2->addClickEventListener([=](Ref*sender){
            widget->removeFromParentAndCleanup(true);
        });
        
    });
    auto back = node->getChildByName<Button*>("Button_16");
    back->addClickEventListener([=](Ref*sender){
        auto scene = Start::createScene();//创建章节场景
        auto trans = TransitionFlipX::create(2, scene);//跳转动作
        Director::getInstance()->replaceScene(trans);//跳转场景
    });
    auto list = node->getChildByName<cocos2d::ui::ScrollView*>("ScrollView_1");
    for (int i = 1; i<=6; ++i) {
        string str = StringUtils::format("Button_%d",i-1);
        auto bt1 = list->cocos2d::Node::getChildByName<Button*>(str);
        bt1->setEnabled(!islock[i-1]);
        bt1->addClickEventListener([=](Ref*sender){
            this->ChooseModule(i);
        });
        cout<<!islock[i-1]<<endl;
    }
    return true;
}
void xuanguan::ChooseModule(int chapter)
{
    auto widget = Widget::create();//创建一个widget对象 ，类似于一个层
    widget->setAnchorPoint(Vec2(0, 0));//设置锚点
    widget->setPosition(Vec2(0, 0));//设置位置
    widget->setContentSize(virableSize);//设置覆盖区域
    widget->setTouchEnabled(true);//开启触摸
    widget->setSwallowTouches(true);//吞噬触摸
    this->addChild(widget,30);//添加子类——控件
    auto node = CSLoader::createNode("Module.csb");
    node->setPosition(Vec2(virableSize.width/2,virableSize.height/2));
    widget->addChild(node);
    auto btnn1 = node->getChildByName<Button*>("Button_1");
    btnn1->addClickEventListener([=](Ref*sender){
        auto seq = Sequence::create(CallFunc::create([=](){
            widget->removeFromParentAndCleanup(true);
        }),CallFunc::create([=](){
            auto scene = Game::createScene(chapter,1);//创建章节场景
            auto trans = TransitionFlipX::create(2, scene);//跳转动作
            Director::getInstance()->replaceScene(trans);//跳转场景
        }),NULL);
        widget->runAction(seq);
    });
    auto btn2 = node->getChildByName<Button*>("Button_2");
    btn2->addClickEventListener([=](Ref*sender){
        auto seq = Sequence::create(CallFunc::create([=](){
            widget->removeFromParentAndCleanup(true);
        }),CallFunc::create([=](){
            auto scene = Game::createScene(chapter,2);//创建章节场景
            auto trans = TransitionFlipX::create(2, scene);//跳转动作
            Director::getInstance()->replaceScene(trans);//跳转场景
            cout<<"跳转场景"<<endl;
        }),NULL);
        widget->runAction(seq);
    });
    auto btn3 = node->getChildByName<Button*>("Button_3");
    btn3->addClickEventListener([=](Ref*Sender){
        widget->removeFromParentAndCleanup(true);
    });
}
void xuanguan::fileCopy()//文件拷贝
{
    string path = FileUtils::getInstance()->getWritablePath();
    //获取可读写路径
    string jsonPath = path+string("charpter1.json");
    //拼接路径
    cout<<"可读写文件路径："<<jsonPath<<endl;
    //获取Resource里的chapter.json的路径
    string path2 = FileUtils::getInstance()->fullPathForFilename("charpter1.json");
    //保存
    if (!FileUtils::getInstance()->isFileExist(jsonPath)) {
        string filecontents = FileUtils::getInstance()->getStringFromFile(path2);
        FILE*file = fopen(jsonPath.c_str(), "w");//打开文件，可写
        if (file) {
            fputs(filecontents.c_str(),file);//从缓存输出到文件
            fclose(file);//关闭文件
        }
    }
}
void xuanguan::Jsonjiexi()//解析文件
{
    fileCopy();
    string path = FileUtils::getInstance()->getWritablePath();
    //获取可读写路径下面charpter.json文件内容
    string jsonPath = path+string("charpter1.json");             //拼接路径

    string data = FileUtils::getInstance()->getStringFromFile(jsonPath);//从文件获取字符串
    Document doc;                                      //文档
    doc.Parse<kParseDefaultFlags>(data.c_str());       //解析文档
    if (doc.HasParseError())//如果解析错误
    {
        log("json error!\n");//输出提示
        return;//返回
    }
    if (doc.HasMember("gameCharpter"))//如果有gameCharpter
    {
        //for循环，外层循环章节数，内层循环关卡数
        for (int i = 0; i<doc["gameCharpter"].Size();++i) {
            rapidjson::Value& _case = doc["gameCharpter"][i]["Case"];//获取Case
            for (int j = 0; j<_case.Size(); ++j) {
                islock[j] = _case[j]["isLock"].GetBool();//获取关卡状态
                cout<<islock[j]<<endl;
            }
        }
    }
}


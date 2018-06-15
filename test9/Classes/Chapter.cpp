//
//  Chapter.cpp
//  AngryBird
//
//  Created by mac on 18/4/9.
//
//

#include "Chapter.hpp"
#include "FistScene.hpp"
#include "GameScene.hpp"
Scene* ChapterScene::createScene()//创建开始场景
{
    auto scene = Scene::create();//创建场景
    auto layer = ChapterScene::create();//创建图层
    scene->addChild(layer);//图层添加场景
    return scene;//返回场景
}
bool ChapterScene::init(){
    if (!Layer::init()) {
        return false;
    }
    Jsonjiexi();//调用文件解析
    visableSize = Director::getInstance()->getVisibleSize();//获取可视区域大小

    auto rootNode = CSLoader::createNode("cocoStuio/Node2.csb");//定义并初始化节点
    this->addChild(rootNode);//添加到图层
    auto back = rootNode->getChildByName<Button*>("Button_1");//从节点获取返回按钮
    //添加点击事件监听器
    back->addClickEventListener([](Ref*sender){
        auto scene = FirstScene::createScene();//创建第一个场景
        auto trans = TransitionMoveInR::create(2, scene);//跳转动作
        Director::getInstance()->replaceScene(trans);//跳转场景
    });
    auto reset = rootNode->getChildByName<Button*>("Button_5");//获取按钮——重置数据
    //添加点击事件监听器
    reset->addClickEventListener([=](Ref*sender){
        this->reset();//调用重置函数
    });

    pageView = rootNode->getChildByName<PageView*>("PageView_1");//从节点获取pageView
    //循环嵌套，外层循环代表章节数，内层循环代表关卡数
    for (int i = 1; i<=2; ++i) {
        string str = StringUtils::format("Panel_%d",i);//字符串——页数
        //从pageView获取layout
        layout = pageView->cocos2d::Node::getChildByName<Layout*>(str);
        for (int j = 1; j<=3; ++j) {
            star1 = ImageView::create("0Star.png");//创建图像
            star1->setPosition(Vec2(140+(j-1)*100,160));//设置位置
            layout->addChild(star1);//添加到当前页面
            int _star = star[i-1][j-1];//获取星星数量
            if (_star==3) {
                star1->removeFromParentAndCleanup(true);//从父节点删除
                star1 = ImageView::create("3Star.png");//创建图像
                star1->setPosition(Vec2(140+(j-1)*100,160));//设置位置
                layout->addChild(star1);//添加到当前页面
            }
            if (_star==2) {
                star1->removeFromParentAndCleanup(true);//从父节点删除
                star1 = ImageView::create("2Star.png");//创建图像
                star1->setPosition(Vec2(140+(j-1)*100,160));//设置位置
                layout->addChild(star1);//添加到当前页面
            }
            if (_star==1) {
                star1->removeFromParentAndCleanup(true);//从父节点删除
                star1 = ImageView::create("1Star.png");//创建图像
                star1->setPosition(Vec2(140+(j-1)*100,160));//设置位置
                layout->addChild(star1);//添加到当前页面
            }

            string str = StringUtils::format("Button%d",j);//关卡按钮字符串
            chapter = layout->getChildByName<Button*>(str);//从layout获取关卡按钮
            chapter->setEnabled(isLock[i-1][j-1]);//设置是否禁用
            //添加点击事件监听器
            chapter->addClickEventListener([=](Ref*sender){
                //创建游戏场景，参数为章节数、关卡数
                auto scene = GameScene::createScene(i,j);
                auto trans = TransitionFadeUp::create(2,scene);//跳转动作
                Director::getInstance()->replaceScene(trans);//跳转场景
            });
        }
    }
    return true;
}
void ChapterScene::reset()//重置
{
    string path = FileUtils::getInstance()->getWritablePath();
    //获取可读写路径下面charpter.json文件内容
    string jsonPath = path+string("charpter2.json");
    //拼接路径
    string data = FileUtils::getInstance()->getStringFromFile(jsonPath);
    //解析
    Document doc;//定义文档
    doc.Parse<kParseDefaultFlags>(data.c_str());//解析
    //外层循环——章节数，内层循环——关卡数
    for (int j = 1; j<=2; ++j) {
        for (int i = 1; i<=3; ++i) {
            //如果章节为1并且关卡小于等于3，第一章第一个关卡为true，其余关卡均为false
            if (j==1&&i<3) {
                doc["gameCharpter"][j-1]["Case"][i]["isLock"].SetBool(false);
            }else{
                doc["gameCharpter"][j-1]["Case"][i-1]["isLock"].SetBool(false);
            }
            //最高分、星星数量设置为0
            doc["gameCharpter"][j-1]["Case"][i-1]["HighScore"].SetInt(0);
            doc["gameCharpter"][j-1]["Case"][i-1]["Star"].SetInt(0);
        }
    }
    StringBuffer buffer;//字符串缓存
    rapidjson::Writer<rapidjson::StringBuffer>writer(buffer);//字符串缓存
    doc.Accept(writer);//写入
    FILE*file = fopen(jsonPath.c_str(), "wb");//打开可写文件
    if (file) {
        fputs(buffer.GetString(),file);//从缓存写入文件
        fclose(file);//关闭文件
    }
    auto scene = ChapterScene::createScene();//创建关卡场景
    Director::getInstance()->replaceScene(scene);//跳转场景
}
void ChapterScene::fileCopy()//文件拷贝
{
    string path = FileUtils::getInstance()->getWritablePath();
    //获取可读写路径
    string jsonPath = path+string("charpter2.json");
    //拼接路径
    cout<<"可读写文件路径："<<jsonPath<<endl;
    //获取Resource里的chapter.json的路径
    string path2 = FileUtils::getInstance()->fullPathForFilename("charpter2.json");
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
void ChapterScene::Jsonjiexi()//解析文件
{
    fileCopy();
    string path = FileUtils::getInstance()->getWritablePath();
    //获取可读写路径下面charpter.json文件内容
    string jsonPath = path+string("charpter2.json");             //拼接路径
    
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
                isLock[i][j] = _case[j]["isLock"].GetBool();//获取关卡状态
                star[i][j] = _case[j]["Star"].GetInt();//获取星星数量
            }
        }
    }
}

//
//  GameScene.cpp
//  DefendTheRadish
//
//  Created by mac on 18/4/14.
//
//

#include "GameScene.hpp"
#include "Chapter.hpp"
#include "Monster.hpp"
#include "VecManger.hpp"
#include "bullet.hpp"
#include "turret.hpp"
#include "curlNet.hpp"
#include "curl/curl.h"

#define MAX_X 15
#define MAX_Y 10

Layer* GameScene::create(int chapter,int level)//重写create，参数为章节数、关卡数
{
    GameScene* layer = new GameScene();//new出一个场景
    //如果存在
    if(layer && layer->init(chapter,level))
    {        layer->autorelease();//自动释放池
        return layer;//返回图层
    }
    CC_SAFE_DELETE(layer);
    layer = nullptr;
    return nullptr;
}
Scene* GameScene::createScene(int chapter,int level)//创建场景，参数为章节数、关卡数
{
    auto scene = Scene::create();//创建场景层
    auto layer = GameScene::create(chapter,level);//创建布景层
    scene->addChild(layer);//将布景添加到场景
    return scene;//返回场景
}
bool GameScene::init(int chapter,int level)//重写init，参数为章节数、关卡数
{
    if (!Layer::init()) {
        return false;
    }
    visableSize = Director::getInstance()->getVisibleSize();
    _chapter = chapter;//初始化章节数
    _level = level;//初始化关卡数
    //设置背景
    auto background = Sprite::create("cocoStuio/luobu/Background/BG1-hd.pvr.png");
    background->setScale(visableSize.width/background->getContentSize().width, visableSize.height/background->getContentSize().height);
    background->setPosition(Vec2(visableSize.width/2, visableSize.height/2));
    this->addChild(background);
    //添加萝卜
    radish = Radish::create(10);
    this->addChild(radish,16);
    
    auto root = CSLoader::createNode("Node2.csb");
    this->addChild(root,15);
    //计时标签
    label = Label::createWithSystemFont("00:00:00", "Marker Felt.ttf",20);
    label->setColor(Color3B::YELLOW);
    label->setAnchorPoint(Vec2(1,0));
    label->setPosition(Vec2(visableSize.width, 0));
    this->addChild(label,16);
    //添加上部标签
    gameScene = CSLoader::createNode("Game.csb");
    this->addChild(gameScene,30);
    wave = gameScene->getChildByName<Text*>("Text_2");//获取波数标签
    score = gameScene->getChildByName<Text*>("Text_3");//获取波数标签
    num1 = 0;//波数
    bar = 10;//萝卜血量
    num=0,num2=0,num3=0;//时分秒
    turretnum = 0;//坐标个数
    Qian = 0;
    auto spr = SpriteFrameCache::getInstance();
    spr->addSpriteFramesWithFile("Items02-hd.plist", "Items02-hd.png");
//    string str = StringUtils::format("BossHP10.png");
//    spream = spr->getSpriteFrameByName(str);
    radishBar = Sprite::createWithSpriteFrameName("BossHP10.png");
    radishBar->setScale(0.5);
    radishBar->setPosition(Vec2(460,250));
    this->addChild(radishBar);
    auto action1 = CSLoader::createTimeline("Node2.csb");//获取动画
    action1->gotoFrameAndPlay(0, 120, false);//设置是否持续动画
    root->runAction(action1);//运行动画
    auto dely = DelayTime::create(2);//延时动作
    auto seq = Sequence::create(dely,CallFunc::create([=](){
        root->removeFromParentAndCleanup(true);//删除节点
    }),NULL);
    this->runAction(seq);//运行动作
    auto pause = gameScene->getChildByName<Button*>("Button_6");//获取暂停按钮
    pause->addClickEventListener([=](Ref*sender){
        this->pause1();//调用函数
    });
    addTouch();//调用函数
    this->addtileMap();//调用函数
    return true;
}
void GameScene::move()
{
}
void GameScene:: putScore()
{
    struct MemoryStruct chunk;
    chunk.memory = (char*)malloc(1);
    chunk.size = 0;
    CURL *curl = curl_easy_init();
    if (curl) {
        string str = "http://123.56.50.222:8050/uploadScore?email=776113582@qq.com";
        string str1 = str+"&score="+score->getString();
        //            curl_easy_setopt(curl,CURLOPT_URL,"http://123.56.50.222:8050/userRegister?email=7761135821@qq.com&password=123456&phoneIdentity=17338142267");
        curl_easy_setopt(curl,CURLOPT_URL,str1.c_str());
        curl_easy_setopt(curl,CURLOPT_WRITEDATA, (void*)&chunk);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WritrMemoryCallback);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (!res) {
            log("%s\n",chunk.memory);
        }else{
            MessageBox("没有网络","提示");
            log("error!");
            log("%d",res);
        }
    }
    {
        Document doc;
        doc.Parse<kParseDefaultFlags>(chunk.memory);
        if (doc.HasParseError()) {
            log("error");
            return;
        }
        rapidjson::Value& rstcode = doc["rstcode"];
        if (strcmp("201", rstcode.GetString())==0) {
            MessageBox(doc["rsttext"].GetString(),"提示");
        }else{
            MessageBox(doc["rsttext"].GetString(),"提示");
        }
    }
}
void GameScene::youLose()
{
    this->stopAllActions();
    this->unschedule(schedule_selector(GameScene::updatetime));
    this->unschedule(schedule_selector(GameScene::updateWave));
    VecManger::getInstance()->vecClear();
    auto widget = Widget::create();//创建一个widget对象 ，类似于一个层
    widget->setAnchorPoint(Vec2(0, 0));//设置锚点
    widget->setPosition(Vec2(0, 0));//设置位置
    widget->setContentSize(visableSize);//设置覆盖区域
    widget->setTouchEnabled(true);//开启触摸
    widget->setSwallowTouches(true);//吞噬触摸
    this->addChild(widget,30);//添加子类——控件
    auto node = CSLoader::createNode("cocoStuio/Node3.csb");//创建节点
    widget->addChild(node);//添加

    auto btn1 = node->getChildByName<Button*>("Button_2");
    btn1->addClickEventListener([=](Ref*sender){
        auto scene = GameScene::createScene(_chapter,_level);
        Director::getInstance()->replaceScene(scene);
    });
    auto btn2 = node->getChildByName<Button*>("Button_3");
    btn2->addClickEventListener([=](Ref*sender){
        auto scene = CheckpointScene::createScene(_chapter);
        Director::getInstance()->replaceScene(scene);
    });
    auto btn3 = node->getChildByName<Button*>("Button_1");
    btn3->addClickEventListener([=](Ref*sender){
        widget->removeFromParentAndCleanup(true);
    });
}
void GameScene::onEnter()
{
    Layer::onEnter();
//    this->schedule(schedule_selector(GameScene::updateMonster),1);//调用时间调度器
    this->schedule(schedule_selector(GameScene::updatetime),1);//调用时间调度器
    if (num1<10) {
        this->schedule(schedule_selector(GameScene::updateWave),0.1);
    }else{
        this->unschedule(schedule_selector(GameScene::updateWave));
    }
    this->schedule(schedule_selector(GameScene::updateHit),1);
    this->schedule(schedule_selector(GameScene::addbuilt),0.5);//调用时间调度器

}
void GameScene::onExit()
{
//    this->unschedule(schedule_selector(GameScene::updateMonster));
    this->unschedule(schedule_selector(GameScene::updatetime));
    this->unschedule(schedule_selector(GameScene::updateWave));
    this->unschedule(schedule_selector(GameScene::updateHit));
    VecManger::getInstance()->vecClear();
    Layer::onExit();
}
void GameScene::addtileMap()//添加瓦片地图
{
    ob = TileMap::getInstance();
    ob->clear();
    _tileMap = ob->addMap();
    ob->getGroupClouds(_tileMap);
    this->addChild(_tileMap,10);//添加瓦片地图到图层
    wallLayer = ob->getLayer4();
    for (int i = 0;i<ob->obj3.size();++i) {
        string str = StringUtils::format("cloud0%d.png",i+1);
        auto sp1 = Sprite::create(str);
        sp1->setPosition(ob->obj3.at(i));
        this->addChild(sp1);
    }
}
 
void GameScene::addTouch()//添加触摸
{
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event){
    this->movePlayer(touch->getLocation());
        
        return true;
    };
    //触摸移动
    listener->onTouchMoved = [=](Touch* touch, Event* event){
//        ob->movePlayer(touch->getLocation());
    };
    //触摸结束
    listener->onTouchEnded = [=](Touch* touch, Event* event){
        Vec2 touchpos = touch->getLocation();
        Vec2 turretpos = Vec2(((int)touchpos.x/32)*32+16,((int)touchpos.y/32)*32+16);
        turretPos.push_back(turretpos);
        auto csn = CSLoader::createNode("Node4.csb");
        csn->setPosition(turretpos);
        this->addChild(csn,20);
        auto btn = csn->getChildByName<Button*>("Button_4");
        btn->addClickEventListener([=](Ref*sender){
            sp = Turret::create(turretpos,1);
            turretnum++;
            this->addChild(sp,2);
            csn->removeAllChildrenWithCleanup(true);
        });
        auto btn2 = csn->getChildByName<Button*>("Button_5");
        btn2->addClickEventListener([=](Ref*sender){
            sp = Turret::create(turretpos,2);
            turretnum++;
            this->addChild(sp,2);
            csn->removeAllChildrenWithCleanup(true);
        });
    };
    //添加事件侦听器与场景图优先级:默认后添加先触发，自定义
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}
/*void GameScene::bulletwithmonsterhit(float dt)
{
    auto _MyVec=VecManger::getInstance();
    
    for (int i = 0; i < _MyVec->getTurretVec().size();i++)
    {
        Turret* _Cannon=(Turret*)_MyVec->getTurretVec().at(i);
        
        for (int j = 0;j < _MyVec->getMonsterVec().size();j++)
        {
            Monster*_monster=(Monster*)_MyVec->getMonsterVec().at(j);
            
            if (_monster->getmonsterHP()==0)
            {
                continue;
            }
            
            float offx=_monster->getPositionX()-_Cannon->getPositionX();
            float offy=_monster->getPositionY()-_Cannon->getPositionY();
            
            float distance=sqrt(offx*offx+offy*offy);
            
            if (distance<=120)
            {
                float ratio=offy/offx;
                float angle=(atanf(ratio))/M_PI*180;//1、求的弧度。2、将弧度转换角度
                
                if (angle>0)
                {
                    if (offy>0)
                    {
                        _Cannon->setRotation(90-angle);
                    }else
                    {
                        _Cannon->setRotation(270-angle);
                    }
                }else if(angle<0)
                {
                    if (offy>0)
                    {
                        _Cannon->setRotation(-90-angle);
                    }else
                    {
                        _Cannon->setRotation(-270-angle);
                    }
                    
                }else if (angle==0)
                {
                    if (offy>0)
                    {
                        _Cannon->setRotation(90);
                    }else
                    {
                        _Cannon->setRotation(-90);
                    }
                }
                
                if (!_Cannon->getislaunch())
                {
                    _Cannon->setislaunch(true);
                    auto bullet=Bullet::create(_Cannon->getPosition(), _monster->getPosition(),_Cannon->getRotation(),visableSize);
                    this->addChild(bullet,10);
                    
                    float t=distance/400;
                    auto move=MoveTo::create(t, _monster->getPosition());
                    
                    auto action_1=CallFunc::create([=]()mutable
                                                   {
                                                       if (_monster)
                                                       {
                                                           
                                                           bullet->setisHit(true);
                                                           bullet->behit();
                                                           _monster->beHit();
                                                           _Cannon->setislaunch(false);
                                                           if (_monster->getmonsterHP()<=0)
                                                           {
//                                                               _monster = nullptr;
//                                                               Qian+=20;
//                                                               textter->setString(StringUtils::format("%d",Qian).c_str());
                                                           }
                                                       }
                                                       
                                                       if (!bullet->getisHit())
                                                       {
                                                           bullet->behit();
                                                           _Cannon->setislaunch(false);
                                                       }
                                                       return ;
                                                   });
                    auto action=Sequence::create(move,action_1, NULL);
                    bullet->runAction(action);
                    break;
                }
                break;
            }
        }
    }
}
 */
void GameScene::addbuilt(float dt)
{
    auto vec = VecManger::getInstance();
    for (int i = 0;i<vec->getTurretVecSize();++i) {
        Turret* tur = (Turret*)vec->getTurretVec().at(i);
        for (int j = 0; j<vec->getMonsterVecSize(); ++j) {
            Monster* mon = (Monster*)vec->getMonsterVec().at(j);
            if (mon->getmonsterHP()==0)
            {
                continue;
            }
            float offx=mon->getPositionX()-tur->getPositionX();
            float offy=mon->getPositionY()-tur->getPositionY();
            float distance=sqrt(offx*offx+offy*offy);
            if (distance<=100)
            {
                float ratio=offy/offx;
                float angle=(atanf(ratio))/M_PI*180;//1、求的弧度。2、将弧度转换角度
                
                if (angle>0)
                {
                    if (offy>0)
                    {
                        tur->setRotation(90-angle);
                    }else
                    {
                        tur->setRotation(270-angle);
                    }
                }else if(angle<0)
                {
                    if (offy>0)
                    {
                        tur->setRotation(-90-angle);
                    }else
                    {
                        tur->setRotation(-270-angle);
                    }
                    
                }else if (angle==0)
                {
                    if (offy>0)
                    {
                        tur->setRotation(90);
                    }else
                    {
                        tur->setRotation(-90);
                    }
                }
            
            if (!tur->getislaunch())
            {
                tur->setislaunch(true);
                Bullet* bullet = Bullet::create(tur->getPosition(),mon->getPosition(),tur->getRotation(),visableSize);
                this->addChild(bullet,20);
                float t=distance/400;
                auto move=MoveTo::create(t, mon->getPosition());
                auto action_1=CallFunc::create([=]()mutable
                {
                    if (mon)
                    {
                        
                        bullet->sethit(true);
                        bullet->behit();
                        mon->beHit();
                        tur->setislaunch(false);
//                        if (mon->getmonsterHP()<=0)
//                        {
//                         mon = nullptr;
                         Qian+=20;
                         score->setString(StringUtils::format("%d",Qian).c_str());
//                        }
                        
                    }
                    
                    if (!bullet->gethit())
                    {
                        bullet->behit();
                        tur->setislaunch(false);
                    }
                    return ;
                });
                auto action=Sequence::create(move,action_1, NULL);
                bullet->runAction(action);
                break;
            }
        }
        }
    }

}
void GameScene::builtmove()
{
    
}
void GameScene::movePlayer(Vec2 p)//玩家移动，且不可穿墙
{
    int x = p.x/_tileMap->getTileSize().width;
    int y = (_tileMap->getTileSize().height * _tileMap->getTileSize().height-p.y)/_tileMap->getTileSize().height;
    Vec2 tiledCoord = Vec2(x,y);
    log("x = %d,y = %d",x,y);
    if (tiledCoord.x<0||tiledCoord.x>=MAX_X||tiledCoord.y<0||tiledCoord.y>=MAX_Y) {
        return;
    }
    int tiled_id = wallLayer->getTileGIDAt(tiledCoord);
    log("%d",tiled_id);
    if (tiled_id) {
        auto _value = _tileMap->getPropertiesForGID(tiled_id);//得到属性GID
        auto _valueStr = _value.getDescription();
        log("Value %s",_valueStr.c_str());
        if (!_value.isNull()) {
            if (_valueStr.find("isHit")!=-1) {
                auto collidableValue = _value.asValueMap().at("isHit").asString().c_str();
                auto strTure = "True";
                log("%s",collidableValue);
                if (collidableValue && strcmp(collidableValue, strTure)) {
                    log("can't move");
                    return;
                }
            }
        }
    }
}
void GameScene::youWin()
{
    this->stopAllActions();
    this->unschedule(schedule_selector(GameScene::updatetime));
    this->unschedule(schedule_selector(GameScene::updateWave));
    VecManger::getInstance()->vecClear();
    auto widget = Widget::create();//创建一个widget对象 ，类似于一个层
    widget->setAnchorPoint(Vec2(0, 0));//设置锚点
    widget->setPosition(Vec2(0, 0));//设置位置
    widget->setContentSize(visableSize);//设置覆盖区域
    widget->setTouchEnabled(true);//开启触摸
    widget->setSwallowTouches(true);//吞噬触摸
    this->addChild(widget,30);//添加子类——控件
    auto node = CSLoader::createNode("cocoStuio/Node3.csb");//创建节点
    widget->addChild(node);//添加
    auto text = node->getChildByName<Text*>("Text_1");
    text->setString("你赢了！！");
    auto btn1 = node->getChildByName<Button*>("Button_2");
    btn1->addClickEventListener([=](Ref*sender){
        auto scene = GameScene::createScene(_chapter,_level);
        Director::getInstance()->replaceScene(scene);
    });
    auto btn2 = node->getChildByName<Button*>("Button_3");
    btn2->addClickEventListener([=](Ref*sender){
        auto scene = CheckpointScene::createScene(_chapter);
        Director::getInstance()->replaceScene(scene);
    });
    auto btn3 = node->getChildByName<Button*>("Button_1");
    btn3->addClickEventListener([=](Ref*sender){
        widget->removeFromParentAndCleanup(true);
    });
    putScore();
}

/*float GameScene::Rotation(Point p1,Point p2)//大炮旋转
{
    //p1 炮台 p2触摸点
    float offx = p1.x-p2.x;                     //炮台到触摸点x
    float offy = p1.y-p2.y;                     //炮台到触摸点y
    if (offy<=0) {
        return -180.0f;                         //返回-180度
    }
    float ratio = offy/offx;                    //tan值
    float angle = (atanf(ratio))/M_PI*180;      //求弧度，将弧度化为角度
    if (angle>0) {
        sp->setRotation(90-angle);          //设置大炮角度
        return 90-angle;                        //返回角度值
    }else{
        sp->setRotation(-90-angle);         //设置大炮角度
        return -90-angle;                       //返回角度值
    }
}
 */
void GameScene::updateHit(float dat)//更新碰撞
{
    //萝卜与怪物是否碰撞
    auto vecManager = VecManger::getInstance();         //创建容器
    for (auto _monster : vecManager->getMonsterVec())     //遍历怪物容器
    {
        auto monster = (Monster*)_monster;                 //将容器类转换为怪物类
        if (monster->getisHit()) {                       //如果没打中，继续
            continue;                                   //继续
        }
        auto monsterpos1 = monster->getPosition();
        auto monsterPos = monster->getBoundingBox();
        auto rect = radish->getBoundingBox();
        if (rect.intersectsRect(monsterPos)) {
            monster->setisHit(true);                 //设置是否打中
            vecManager->deleteMonster(monster);
            bar--;
            if (bar<1) {
                radish->removeFromParentAndCleanup(true);
                youLose();
                continue;
            }else{
//                radishBar->removeFromParentAndCleanup(true);
//                string str = StringUtils::format("BossHP%d.png",bar);
//                radishBar = Sprite::createWithSpriteFrameName(str);
//                radishBar->setScale(0.5);
//                radishBar->setPosition(Vec2(460,250));
//                this->addChild(radishBar);
                radish->removeFromParentAndCleanup(true);
                radish = Radish::create(bar);
                this->addChild(radish,16);
            }
        }
    }
}
void GameScene::updatetime(float dt)
{
    num++;
    if (num == 60) {
        num2++;
        if (num2 == 60) {
            num3++;
            if (num3 == 24) {
                num3=0;
            }
            num2 = 0;
        }
        num = 0;
    }
    string str = StringUtils::format("%02d:%02d:%02d",num3,num2,num);
    label->setString(str);
}
void GameScene::updateMonster(float dt)
{
    if(VecManger::getInstance()->getMonsterVecSize()<5){
        addMonster();
//        static int num = 0;
//        num++;
//        if (num==5) {
//            this->unschedule(schedule_selector(GameScene::updateMonster));
//            this->schedule(schedule_selector(GameScene::updateWave),0.1);
//            num = 0;
//        }
    }
}
void GameScene::updateWave(float dt)
{
    if (VecManger::getInstance()->getMonsterVecSize()<1) {
        num1++;
        if (num1>0&&num1<=10) {
            string str = StringUtils::format("%02d",num1);
            wave->setString(str);
            this->unschedule(schedule_selector(GameScene::updateWave));
            this->schedule(schedule_selector(GameScene::updateMonster),1);
        }else{
            this->unschedule(schedule_selector(GameScene::updateWave));
        }
    }
}
void GameScene::addMonster()
{
    auto monster = Monster::create(num1);
    this->addChild(monster,20);
}
void GameScene::pause1()
{
    this->stopAllActions();
    this->unschedule(schedule_selector(GameScene::updatetime));
    this->unschedule(schedule_selector(GameScene::updateWave));
    this->unschedule(schedule_selector(GameScene::updateHit));

    auto widget = Widget::create();
    widget->setAnchorPoint(Vec2(0, 0));//设置锚点
    widget->setPosition(Vec2(0, 0));//设置位置
    widget->setContentSize(visableSize);//设置覆盖区域
    widget->setTouchEnabled(true);//开启触摸
    widget->setSwallowTouches(true);//吞噬触摸
    this->addChild(widget,20);//添加子类——控件
    auto pause = CSLoader::createNode("Menu.csb");
    widget->addChild(pause);
    auto choose = pause->getChildByName<Button*>("Button_1");
    choose->addClickEventListener([=](Ref*sender){
        auto scene = CheckpointScene::createScene(_chapter);
        auto trans = TransitionCrossFade::create(1,scene);
        Director::getInstance()->replaceScene(trans);
    });
    auto replse = pause->getChildByName<Button*>("Button_2");
    replse->addClickEventListener([=](Ref*sender){
        auto scene = GameScene::createScene(_chapter, _level);
        Director::getInstance()->replaceScene(scene);
    });
    auto continueGame = pause->getChildByName<Button*>("Button_3");
    continueGame->addClickEventListener([=](Ref*sender){
        widget->removeFromParentAndCleanup(true);
        this->schedule(schedule_selector(GameScene::updatetime),1);//调用时间调度器
        this->schedule(schedule_selector(GameScene::updateWave),1);
        this->schedule(schedule_selector(GameScene::updateHit),1);
    });
}


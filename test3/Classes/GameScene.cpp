//
//  GameScene.cpp
//  FishMan
//
//  Created by MAC on 16/6/28.
//
//

#include "GameScene.hpp"
#include "startScene.hpp"
//声音头文件和命名空间
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
static int gold = 100;
Scene* GameScene::createScene()
{
    auto scene = Scene::create();  //创建一个场景
    auto layer = GameScene::create();  //创建一个层
    scene->addChild(layer);
    return scene;
}
bool GameScene::init(){
    if (!Layer::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    //设置音效
    isSoundEfect = true;
    //批处理纹理
    this->loadTexture();
    SimpleAudioEngine::getInstance()->playBackgroundMusic("music/music_blue.mp3",true);
    //添加背景图片
    auto background = Sprite::create("background/gamebg.jpg");
    background->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    background->setScale(visibleSize.width/background->getContentSize().width, visibleSize.height/background->getContentSize().height);
    this->addChild(background);
    initUI();
    return true;
}
void GameScene::initUI()
{
//****************************返回按钮**********************
    auto BtnBack = Button::create("menu/back.png");
    BtnBack->setAnchorPoint(Vec2(0, 1));
    BtnBack->setPosition(Vec2(0, visibleSize.height));
    BtnBack->setScale(2.2);
    BtnBack->addClickEventListener([=](Ref* pSender){
        gold = 100;
        auto scene = StartScene::createScene();
        Director::getInstance()->replaceScene(scene);
    });
    this->addChild(BtnBack);
//****************************音乐按钮**********************
    auto _checkBox = CheckBox::create("menu/bg_music_close.png","menu/bg_music_open.png");
    _checkBox->setAnchorPoint(Vec2(1, 0));
    _checkBox->setPosition(Vec2(visibleSize.width, 0));
    _checkBox->setScale(2);
    _checkBox->setSelected(true);
    _checkBox->addEventListener([=](Ref* pSender,CheckBox::EventType type){
        switch (type) {
            case CheckBox::EventType::SELECTED:
                isSoundEfect = true;
                SimpleAudioEngine::getInstance()->playBackgroundMusic("music/music_blue.mp3",true);
                break;
            case CheckBox::EventType::UNSELECTED:
                isSoundEfect = false;
                SimpleAudioEngine::getInstance()->stopBackgroundMusic();
                SimpleAudioEngine::getInstance()->stopAllEffects();
                break;
            default:
                break;
        }
    });
    this->addChild(_checkBox,3);
//****************************添加边框顶部**********************
    auto topBorder = Sprite::create("menu/ui_box_01.png");
    topBorder->setAnchorPoint(Vec2(0.5,1));
    topBorder->setPosition(Vec2(visibleSize.width/2,visibleSize.height));
    topBorder->setScale(2);
    this->addChild(topBorder,2);
//****************************添加底部边框**********************
    auto bottomBorder = Sprite::create("menu/ui_box_02.png");
    bottomBorder->setAnchorPoint(Vec2(0.5, 0));
    bottomBorder->cocos2d::Node::setPosition(Vec2(visibleSize.width/2,0));
    bottomBorder->setScale(2.15);
    this->addChild(bottomBorder,2);
//****************************添加能量槽**********************
    auto Energyslot = Sprite::create("menu/ui_2p_004.png");
    Energyslot->cocos2d::Node::setPosition(Vec2(visibleSize.width/2, 10));
    Energyslot->setScale(2.15);
    this->addChild(Energyslot,2);
    
//****************************添加能量图标**********************
    EnergyIcon = Sprite::create("menu/ui_2p_005.png");
    EnergyIcon->cocos2d::Node::setPosition(Vec2(visibleSize.width/2, 0));
    EnergyIcon->setScale(2.45);
    this->addChild(EnergyIcon,1);
//****************************添加“＋”“－”按钮**********************
    auto btnAdd = Button::create();
    btnAdd->setTitleText("+");
    btnAdd->setTitleFontSize(30);
    btnAdd->setPosition(Vec2(visibleSize.width/2+30, 10));
    btnAdd->addClickEventListener([=](Ref* pSender){
        ++cannonLevel;
        if (cannonLevel>7) {
            cannonLevel = 7;
            return;
        }
        auto action1 = ScaleTo::create(0.2, 0.2);
        auto callfuncn = CallFuncN::create([=](Ref* pSender){
            cannon->setCannonLevel(cannonLevel);
        });
        auto action2 = ScaleTo::create(0.2, 1.3);
        auto action = Sequence::create(action1,callfuncn,action2, NULL);
        cannon->runAction(action);

    });
    this->addChild(btnAdd,3);
    
    auto btnSub = Button::create();
    btnSub->setTitleText("-");
    btnSub->setTitleFontSize(50);
    btnSub->setPosition(Vec2(visibleSize.width/2-30, 10));
    btnSub->addClickEventListener([=](Ref* pSender){
        --cannonLevel;
        if (cannonLevel<1) {
            cannonLevel = 1;
            return;
        }
        auto action1 = ScaleTo::create(0.2, 0.2);
        auto callfuncn = CallFuncN::create([=](Ref* pSender){
            cannon->setCannonLevel(cannonLevel);
        });
        auto action2 = ScaleTo::create(0.2, 1.3);
        auto action = Sequence::create(action1,callfuncn,action2, NULL);
        cannon->runAction(action);

    });
    this->addChild(btnSub,3);
//****************************添加大炮**********************
    cannon = Cannon::create();
    cannon->setCannonLevel(1);
    cannonLevel = cannon->getCannonLevel();
    cannon->setAnchorPoint(Vec2(0.5, 0));
    cannon->setScale(1.3);
    cannon->setPosition(Vec2(visibleSize.width/2, 0));
    this->addChild(cannon,5);
//****************************添加数字标签**********************
    char str[50];
    sprintf(str,"%06d", gold);
    label1 = Label::createWithSystemFont(str, "",16);
    label1->setAnchorPoint(Vec2(0.5, 0));
    label1->setPosition(Vec2(visibleSize.width/2-99, 1));
    label1->setColor(Color3B::BLACK);
    this->addChild(label1,10);
//****************************添加加分标签**********************
        
}

void GameScene::addgold(int n)
{
    gold = gold + n;
    if (gold>999999)
    {
        gold = 1000;
        char str[30];
        sprintf(str,"%06d", gold);
        label1->setString(str);
    }
    else
    {
        char str[30];
        sprintf(str,"%06d", gold);
        label1->setString(str);
    }
    
}
void GameScene::subgold(int n)
{
    gold = gold-n;
    if (gold < 0)
    {
        gold = 0;
        char str[30];
        sprintf(str,"%06d", gold);
        label1->setString(str);
        
        auto scene2 = Scene::create();
        auto layer2 = LayerColor::create(Color4B(0,255,255,255));
        Size visableSize2 = Director::getInstance()->getVisibleSize();
        scene2->addChild(layer2);
        Director::getInstance()->pushScene(scene2);
        
        Sprite* sp = Sprite::create("menu/bg.jpg");
        sp->setPosition(Vec2(visableSize2.width/2, visableSize2.height/2));
        Size spsize = sp->getContentSize();
        sp->setScale(visableSize2.width/spsize.width, visableSize2.height/spsize.height);
        layer2->addChild(sp,1);
        
        auto prompt = Sprite::create("menu/prompt.jpg");
        prompt->setAnchorPoint(Vec2(0.5, 1));
        prompt->setPosition(Vec2(visableSize2.width/2, visableSize2.height));
        prompt->setScale(0.7);
        layer2->addChild(prompt,2);
        
        std::string ss = "金币不足，请选择回答问题：你感觉你自己是很帅的吗？";
        auto label3 = Label::createWithSystemFont(ss, "", 20);
        label3->setColor(Color3B(244, 221, 30));
        label3->setPosition(Vec2(visableSize2.width/2, visableSize2.height-100));
        layer2->addChild(label3,3);
        
        auto item1 = MenuItemFont::create("我很帅");
        item1->setFontSize(20);
        item1->setCallback([=](Ref * pSender){
            gold = 100;
            char str[30];
            sprintf(str,"%06d", gold);
            label1->setString(str);
            Director::getInstance()->popScene();
            
        });
        item1->setColor(Color3B::BLACK);

        item1->setPosition(Vec2(visableSize2.width/2 - 100,visableSize2.height/2));
        
        auto item2 = MenuItemFont::create("我不帅");
        item2->setFontSize(20);
        item2->setCallback([=](Ref * pSender){
            gold = 100;
            auto scene2 = StartScene::createScene();
            Director::getInstance()->replaceScene(scene2);
            
        });
        item2->setColor(Color3B::BLACK);
        
        item2->setPosition(Vec2(visableSize2.width/2 + 100,visableSize2.height/2));
        auto menu = Menu::create();
        menu->setPosition(Vec2::ZERO);  //vec2(0,0);
        menu->addChild(item1);
        menu->addChild(item2);
        layer2->addChild(menu, 2);
    }
    else
    {
        char str[30];
        sprintf(str,"%06d", gold);
        label1->setString(str);
    }
    
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
    Vec2 touchP = touch->getLocation();
    Vec2 cannonP = cannon->getPosition();
    float pointX = touchP.x - cannonP.x;
    float pointY = touchP.y - cannonP.y;

    float tan = pointY/pointX;
    float angle = atanf(tan)*180/3.1415;
    if (angle > 0)
    {
        cannon->setRotation(90-angle);
    }
    else
    {
        cannon->setRotation(-angle-90);
    }
    return true;
}
void GameScene::onTouchMoved(Touch *touch, Event *unused_event)
{
    Vec2 touchP = touch->getPreviousLocation();
    Vec2 cannonP = cannon->getPosition();
    float pointX = touchP.x - cannonP.x;
    float pointY = touchP.y - cannonP.y;

    float tan = pointY/pointX;
    float angle = atanf(tan)*180/3.1415;
    if (angle > 0)
    {
        cannon->setRotation(90-angle);
    }
    else
    {
        cannon->setRotation(-angle-90);
    }

}
void GameScene::onTouchEnded(Touch *touch, Event *unused_event)
{
    Vec2 touchP = touch->getPreviousLocation();
    Vec2 cannonP = cannon->getPosition();
    float pointX = touchP.x - cannonP.x;
    float pointY = touchP.y - cannonP.y;

    float tan = pointY/pointX;
    float angle = atanf(tan)*180/3.1415;
    if (angle > 0)
    {
        angle = (90-angle);
    }
    else
    {
        angle = (-angle-90);
    }
    
    //子弹发射播放音乐
    if (isSoundEfect) {
        char str[50];
        sprintf(str,"music/sound_fire0%d.mp3",cannonLevel);
        SimpleAudioEngine::getInstance()->playEffect(str);
    }
    //金币变化
    subgold(cannonLevel);
    
    bullet = Bullet::create();
    bullet->setAnchorPoint(Vec2(0.5, -0.5));
    bullet->setPosition(cannon->getPosition());
    bullet->setBulletLevel(cannonLevel);
    bullet->setRotation(angle);
    bullet->setScale(2);
    
    int realY = visibleSize.height+cannonP.y;
    float retio = (float)pointX / (float)pointY;     //余切值
    int realX = (realY - cannonP.y)*retio + cannonP.x;
    
    Vec2 realPoint = Vec2(realX, realY);//子弹到达的位置点
    //计算子弹的飞行时间
    int bulletX = realX - cannonP.x;
    int bulletY = realY - cannonP.y;
    float length = sqrtf((bulletX*bulletX)+(bulletY*bulletY));
    float speed = 240;
    float realMoveDuration = length/speed;
    auto moveto = MoveTo::create(realMoveDuration, realPoint);
    //添加一个瞬时动作
    auto func = CallFuncN::create([=](Ref* sender){
        Sprite* sp = (Sprite*)sender;
        //移除子弹
        sp->removeFromParentAndCleanup(true);
    });
    bullet->runAction(Sequence::create(moveto,func, NULL));
    bulletSheet->addChild(bullet);
}
void GameScene::onTouchCancelled(Touch *touch, Event *unused_event)
{
    
}
void GameScene::onEnter()
{
    Layer::onEnter();
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    //监听鱼
    this->schedule(schedule_selector(GameScene::updateFish), 0.1);
    //监听碰撞
    this->schedule(schedule_selector(GameScene::updateHit), 0.1);
}
void GameScene::onExit()
{
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    Layer::onExit();
}
void GameScene::updateFish(float dt)
{
    //getChildrenCount:返回子节点的总数
    while (fishSheet->getChildrenCount()<30) {
        this->addFish();
    }
}
void GameScene::addFish()
{
    int type = rand()%11+1;
    auto fish = Fish::create();
    cout<<"type"<<type<<endl;
    fish->setLevel(type);
    fish->run();
    fishSheet->addChild(fish,1);
}
void GameScene::loadTexture()
{
    /*
     SpriteBatchNode 是批处理节点:如果它包含子节点，它将通过一次 OpenGL 调用绘制所有子节点。 (通常被称为“批处理绘制”)。
     
     一个 SpriteBatchNode 可以引用一个且只有一个纹理(一个图像文件, 或者一个纹理地图集)。 只
有当 Sprite 使用的纹理与 SpriteBatchNode 一致时才能添加为 SpriteBatchNode 的子节点。 所有
添加到 SpriteBatchNode 的子节点会通过一次 OpenGL 调用全部绘制出来。 如果Sprite 没有添加到 SpriteBatchNode，那么一次 OpenGL 调用只能绘制一个 Sprite，这样效率是很低的。
     限制:
     只有 Sprite 或者 Sprite 子类的实例化对象可以做为 SpriteBatchNode 的子节点。比如：particle，label 和 layer 不能做为 SpriteBatchNode 的子节点。
     所有的子节点要么都有别名，要么都没有别名，不能混合使用。因为“别名”是纹理的属性，而所有的子节点共用同一个纹理。
     */
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/fish.plist", "sprites/fish.png");
    fishSheet = SpriteBatchNode::create("sprites/fish.png",40);
    this->addChild(fishSheet,1);
    
    //初始化子弹的批处理节点
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/bullet.plist", "sprites/bullet.png");
    bulletSheet = SpriteBatchNode::create("sprites/bullet.png",40);
    this->addChild(bulletSheet,4);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/net.plist","sprites/net.png");
    fishNetSheet = SpriteBatchNode::create("sprites/net.png",40);
    this->addChild(fishNetSheet,5);
}
void GameScene::updateHit(float dt)
{
    //范围for语句 for (declaration: expression )
    //getChildren  返回所有的子节点
    for (auto bullet2: bulletSheet->getChildren() )
    {
        auto bullet = (Bullet*) bullet2;
        if (bullet->getisHit())
        {
            continue;
        }
        Vec2 bulletP = bullet->getPosition();
        //子弹出屏幕
        if (bulletP.x>(visibleSize.width+bullet->getContentSize().width/2)||bulletP.x<0-bulletP.x)
        {
            continue;
        }
        //遍历鱼
        for (auto _fish: fishSheet->getChildren())
        {
            Fish* fish = (Fish*)_fish;
            if (bullet->getisHit())
            {
                break;
            }
            //子弹与鱼的点面碰撞
            Rect Rectfish = fish->getBoundingBox();
            
            if (isContains(Rectfish, bulletP))
            {
                bullet->setisHit(true);
                bullet->removeFromParentAndCleanup(true);
                cout<<cannonLevel<<endl;
                //渔网出现
                auto fishnet = FishNet::create(cannonLevel);
                fishnet->setPosition(bulletP);
                fishnet->setScale(1.3);
                auto action1 = ScaleTo::create(0.4,1.2);
                auto action2 = ScaleTo::create(0.4, 0.8);
                auto callfun = CallFuncN::create([=](Ref* pSender){
                    fishnet->removeFromParentAndCleanup(true);
                });
                auto action3 = Sequence::create(action1,action2,action1,action2,callfun, NULL);
                fishnet->runAction(action3);
                fishNetSheet->addChild(fishnet);
            }
        }
    }
    //遍历渔网
    for ( auto net:fishNetSheet->getChildren())
    {
        FishNet* fishnet = (FishNet*) net;
//        if (fishnet->getisHit())
//        {
//            continue;
//        }
        for (auto _fish:fishSheet->getChildren())
        {
            auto fish = (Fish*)_fish;
            if (fish->isCatch)
            {
                break;
            }
            //渔网与鱼的面面碰撞
            Rect Rectfish = fish->getBoundingBox();
            Rect Rectnet = fishnet->getBoundingBox();
            Vec2 point = fish->getPosition();
            if (isContains(Rectnet, point))
            {
                if (!fish->randomCatch(cannonLevel))
                {
                    continue;
                }
                else //鱼被捕，开启音效
                {
                    if (isSoundEfect)
                    {
                        char str[30];
                        sprintf(str, "music/sound_hit0%d.mp3",cannonLevel);
                        SimpleAudioEngine::getInstance()->playEffect(str);
                    }
                    //鱼被捉
                    fish->beCatch();
                    //添加能量
                    addEnergy(fish->getLevel());
                    /*
                    //添加＋5动作
                    auto gold = Sprite::create("sprites/+5.png");
                    gold->setPosition(fish->getPosition());
                    auto action1 = DelayTime::create(0.5);
                    auto action2 = ScaleTo::create(0.3, 1.1);
                    auto action3 = ScaleTo::create(0.3, 0.8);
                    auto action4 = MoveTo::create(0.5, Vec2(visibleSize.width/2-80,30));
                    auto action5 = CallFuncN::create([=](Ref* sender){
                        Sprite* sp = (Sprite*)sender;
                        sp->removeFromParentAndCleanup
                        (true);
                        //金币变化
                        addgold(5);
                    });
                    auto action = Sequence::create(action1,action2,action3,action4,action5, NULL);
                    this->addChild(gold,100);
                    gold->runAction(action);
                     */
                    auto label = Score::create(fish->getLevel());
                    label->setPosition(fish->getPosition());
                    label->setSystemFontSize(25);
                    label->setColor(Color3B(244, 221, 30));
                    auto action1 = DelayTime::create(0.5);
                    auto action2 = ScaleTo::create(0.3, 1.1);
                    auto action3 = ScaleTo::create(0.3, 0.8);
                    auto action4 = MoveTo::create(0.5, Vec2(visibleSize.width/2-80,30));
                    auto action5 = CallFuncN::create([=](Ref* sender){
                        Sprite* sp = (Sprite*)sender;
                        sp->removeFromParentAndCleanup
                        (true);
                        //金币变化
                        int n = fish->getLevel();
                        addgold(n);
                        cout<<"n:"<<n<<endl;
//                        cout<<"gold:"<<gold<<endl;
                    });
                    auto action = Sequence::create(action1,action2,action3,action4,action5, NULL);
                    this->addChild(label,100);
                    label->runAction(action);
                    if (isSoundEfect) {
                        SimpleAudioEngine::getInstance()->playEffect("music/sound_coin.mp3");
                    }
                }
            }
        }
//        fishnet->setisHit(true);
    }
}
void GameScene::addEnergy(int _energy)
{
    energy = energy+_energy;
    if (EnergyIcon->getRotation() >= 180)
    {
        EnergyIcon->setRotation(180);
        cout<<"能量满了"<<endl;
    }
    else
    {
        float rotation = ((float)energy/180)*(180 - 30) + 30;
        EnergyIcon->setRotation(rotation);
    }
    
}
bool GameScene::isContains(Rect& rect,Point& point)
{
    bool result = true;
    if ((point.x >= rect.origin.x && point.x <= rect.origin.x + rect.size.width)  && (point.y >= rect.origin.y && point.y <= rect.origin.y + rect.size.height))
    {
        result = true;
    }
    else
    {
        result = false;
    }
    return result;
}
bool GameScene::isRectHitRect(cocos2d::Rect &rect1, cocos2d::Rect &rect2)
{
    bool result = false;
    Point point1 = Vec2(rect2.origin.x, rect2.origin.y);
    Point point2 = Vec2(rect2.origin.x, rect2.origin.y + rect2.size.height);
    Point point3 = Vec2(rect2.origin.x + rect2.size.width, rect2.origin.y + rect2.size.height);
    Point point4 = Vec2(rect2.origin.x + rect2.size.width, rect2.origin.y);
    
    
    
    
    Point point5 = Vec2(rect1.origin.x, rect1.origin.y);
    Point point6 = Vec2(rect1.origin.x, rect1.origin.y + rect1.size.height);
    Point point7 = Vec2(rect1.origin.x + rect1.size.width, rect1.origin.y + rect1.size.height);
    Point point8 = Vec2(rect1.origin.x + rect1.size.width, rect1.origin.y);
    
    if (isContains(rect1,point1) || (isContains(rect1,point2)) || (isContains(rect1,point3)) || (isContains(rect1,point4)) )
    {
        result = true;
    }
    if (isContains(rect2,point5) || (isContains(rect2,point6)) || (isContains(rect2,point7)) || (isContains(rect2,point8)) )
    {
        result = true;
    }
    return result;

}












//
//  GameScene.cpp
//  AngryBird
//
//  Created by mac on 18/4/9.
//
//

#include "GameScene.hpp"
#include "Chapter.hpp"
#define PTM_RATIO 32

Layer* GameScene::create(int chapter,int level)//重写create，参数为章节数、关卡数
{
    GameScene* layer = new GameScene();//new出一个场景
    //如果存在
    if(layer && layer->init(chapter,level))
    {
        layer->autorelease();//自动释放池
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
    if (_level<=3) {
        //字符串包转化
        string str = StringUtils::format("Chapter%d-%d.csb",_chapter,_level);
        rootNode = CSLoader::createNode(str);//创建节点——载入cocoStudio的.csb
        this->addChild(rootNode);//添加到图层
        //字符串包转化
        string str1 = StringUtils::format("Chapter%d-%d",_chapter,_level);
        //创建标签文字，30号大小
        auto label = Label::createWithSystemFont(str1, "Marker Felt.ttf",30);
        label->setColor(Color3B::YELLOW);//设置颜色为黄色
        label->setAnchorPoint(Vec2(0.5, 1));//设置锚点为（0.5，1）
        //设置位置为可视区域的顶部居中
        label->setPosition(Vec2(visableSize.width/2, visableSize.height));
        this->addChild(label);//添加到图层
        }
    auto back = rootNode->getChildByName<Button*>("Button_1");//从节点获取返回按钮
    //添加点击事件监听器
    back->addClickEventListener([](Ref*sender){
        auto scene = ChapterScene::createScene();//创建关卡场景
        auto trans = TransitionFadeUp::create(2,scene);//跳转动作
        Director::getInstance()->replaceScene(trans);//跳转场景
    });
    //加弹弓
    auto leftSlingShot = Sprite::create("slingshot_front.png");//创建精灵
    leftSlingShot->setScale(0.5);//设置缩放比例
    leftSlingShot->setPosition(Vec2(86, 73));//设置位置
    this->addChild(leftSlingShot,20);//添加到图层，层数：20
    
    auto rightSlingShot = Sprite::create("platform.png");//创建精灵
    rightSlingShot->setScale(0.5);//设置缩放比例
    rightSlingShot->setPosition(Vec2(95, 60));//设置位置
    this->addChild(rightSlingShot);//添加到图层
    
    node1 = DrawNode::create();//初始化
    this->addChild(node1);//添加到图层
    node2 = DrawNode::create();//初始化
    this->addChild(node2);//添加到图层
    node1->drawLine(Vec2(97, 80), Vec2(83, 80),Color4F::MAGENTA);//画线
    node2->drawLine(Vec2(97, 80), Vec2(83, 80),Color4F::MAGENTA);//画线
    beginPos = Vec2(90,80);//开始位置
    midPos = Vec2(90,80);//中心位置
    pigArray = __Array::create();//初始化——创建容器
    pigArray->retain();//+1
    
    iceArray = __Array::create();//初始化——创建容器
    iceArray->retain();//+1
    
    birdArray = __Array::create();//初始化——创建容器
    birdArray->retain();//+1
    chushihua();//调用初始化
    score = rootNode->getChildByName<Text*>("Text_2");//从父节点获取分数文字
    
    initPhysics();//创建物理世界
    addPigBirdIce(_chapter,_level);//添加猪鸟冰
    return true;//返回真
}
void GameScene::onEnter()//进入
{
    Layer::onEnter();//图层：：进入
    auto  touchListener = EventListenerTouchOneByOne::create();//创建单点触摸
    //回调触摸开始，触摸移动，触摸结束，终止触摸
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled,this);
    touchListener->setSwallowTouches(true);//吞噬触摸
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);//设置优先级
    
    this->scheduleUpdate();//调用时间调度器
    
}
void GameScene::onExit()//退出
{
    //删除事件监听器
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    Layer::onExit();//图层退出
}
bool GameScene::onTouchBegan(Touch* touch,Event* unused_event)//触摸开始
{
    //如果鸟的数量大于0
    if (birdArray->count()>0) {
        auto rect = currectBird->getBoundingBox();//鸟的框
        //如果触摸点在鸟的框里面并且中点也在鸟的框里
        if (rect.containsPoint(touch->getLocation())&&rect.containsPoint(midPos)) {
            return true;//返回真
        }
    }
    return false;//返回假
}
void GameScene::onTouchMoved(Touch* touch,Event* unused_event)//触摸移动
{
    Vec2 point = touch->getLocation();//获取触摸点
    //如果触摸点到中点的位置小于等于80并且触摸点的y大于30
    if ((point.distance(midPos)<=80)&&(point.y>30)) {
        node1->clear();//删除线1
        node2->clear();//删除线2
        node1->drawLine(point, Vec2(97, 80), Color4F::MAGENTA);//重新画线1
        node2->drawLine(point, Vec2(83, 80), Color4F::MAGENTA);//重新画线2
        currectBird->setPosition(point);//设置鸟的位置为触摸点的位置
    }
}
void GameScene::onTouchEnded(Touch* touch,Event* unused_event)//触摸结束
{
//    auto point = touch->getLocation();//获取触摸点
//    this->addPhysicsSprite(point);//测试——添加物理精灵
    node1->clear();//删除线1
    node2->clear();//删除线2
    node1->drawLine(Vec2(97, 80), Vec2(83, 80), Color4F::MAGENTA);//重新画线1
    node2->drawLine(Vec2(97, 80), Vec2(83, 80), Color4F::MAGENTA);//重新画线2
    Vec2 endPos = touch->getLocation();//获取触摸点
    float x = midPos.x - endPos.x;//x = 中点x 减 触摸点x
    float y = midPos.y - endPos.y;//y = 中点y 减 触摸点y
    currectBird->setBirdSpeed(x, y, world);//设置鸟的冲量速度
}
void GameScene::update(float dt){
    float timeStep = 1.0/60.0f;//更新时间(物理世界刷新次数)
    int32 velocityIterations = 8;//速度迭代次数
    int32 positionIterations = 3;//位置迭代次数
    //刷新
    world->Step(timeStep, velocityIterations, positionIterations);
    for (b2Body *b = world->GetBodyList(); b; b = b->GetNext())
    {
        //如果用户数据不为空
        if (b->GetUserData()!=nullptr)
        {   //定义并初始化精灵
            BaseSprite* sprite = (BaseSprite*)b->GetUserData();
            //如果精灵获取的类型为鸟的类型
            if (sprite->getTYPEID() == BirdID)
            {
                BIRD* bird = (BIRD*)sprite;
                if (!b->IsAwake()) {
                    bird->destroyBody(world);//删除刚体
                    world->DestroyBody(b);//删除刚体
                    birdArray->removeObject(currectBird);
                    if (birdArray->count() == 0)//鸟没的情况
                    {
                        if (pigArray->count() == 0)//鸟没猪也没
                        {
                            log("You Win!");
                            youWin();
                            parseJSon();
                        }else{
                            log("You Filed!");
                            youFiled();
                        }
                    }
                    //如果鸟的数量大于0并且猪的数量大于0
                    if ((birdArray->count()>0)&&(pigArray->count()>0)) {
                        this->birdJumpToSlingShot();//鸟跳到弹弓上
                    }
                    continue;//继续
                }
            }
            //如果精灵获取的类型为猪的类型
            if (sprite->getTYPEID() == PigId) {
                PIG* pig = (PIG*)sprite;
                //如果猪的血量小于0
                if (pig->getHP() <= 0) {
                    num = num + 100;//得分累加
                    //如果得分大于等于最高分
                    if (num>=_highScore1) {
                        _highScore1 = num;//最高分等于得分
                    }
                    //转化字符串
                    string str1 = StringUtils::format("%d",_highScore1);
                    highScore->setString(str1);//设置字符串
                    string str = StringUtils::format("%d",num);//字符串转化
                    score->setString(str);//设置字符串
                    
                    pig->destroyBody(world);//删除刚体
                    world->DestroyBody(b);//删除刚体
                    pigArray->removeObject(pig);//从容器删除
                    //如果猪的数量等于0
                    if (pigArray->count() == 0) {
                        //如果鸟容器里的对象数量大于0
                        if (birdArray->count()>0) {
                            log("You Win!");//输出
                            youWin();//你赢了
                            parseJSon();//修改文件内容
                        }
                    }else{
                        //如果鸟的数量等于0，且猪的数量大于0
                        if (birdArray->count() == 0) {
                            log("You Filed!");//输出
                            youFiled();//你输了
                        }
                    }
                    continue;//继续
                }
            }
            //如果精灵获取的类型为冰的类型
            if (sprite->getTYPEID() == IceID) {
                ICE* ice = (ICE*)sprite;//将类型转换为冰
                //如果冰的血量小于0
                if (ice->getHP()<0) {
                    num = num + 30;//得分累加
                    string str = StringUtils::format("%d",num);//字符串转化
                    score->setString(str);//设置字符串
                    //如果得分大于等于最高分
                    if (num>=_highScore1) {
                        _highScore1 = num;//最高分等于得分
                    }
                    //转化字符串
                    string str1 = StringUtils::format("%d",_highScore1);
                    highScore->setString(str1);//设置字符串


                    ice->destroyBody(world);//删除刚体
                    world->DestroyBody(b);//删除刚体
                    iceArray->removeObject(ice);//从容器删除对象
                    continue;//继续
                }
            }
            
            sprite->setPosition( Vec2( b->GetPosition().x *PTM_RATIO, b->GetPosition().y * PTM_RATIO) );//设置位置
            sprite->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );//设置角度
        }
    }
}
void GameScene::initPhysics(){
    //1、创建世界
    b2Vec2 gravity;//定义重力矢量
    gravity.Set(0.f, -10.f);//竖直向下
    world = new b2World(gravity);//创建一个物理世界
    world->SetAllowSleeping(true);//允许睡眠
    world->SetContinuousPhysics(true);//允许碰撞
    //2、创建地面盒
    /*
     body用以下步骤来创建：
     1.	用位置(position), 阻尼(damping)等来定义body。
     2.	用world对象来创建body。
     3.	用形状(shape), 摩擦(friction), 密度(density)等来定义fixture。
     4.	在body上来创建fixture。
     */
    //第一步，创建ground body。为此我们需要一个body定义。在定义中，我们指定ground body的初始位置
    b2BodyDef groundBodyDef;//创建地面
    groundBodyDef.position.Set(0.0f, 0.0f);//原点
    //第二步，将body定义传给world对象，用以创建ground body。world对象并不保留body定义的引用。body默认是静态的。静态物体和其它静态物体之间并没有碰撞，它们是固定的。
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    //第三步，创建地面多边形。我们用简便函数SetAsBox使得地面多边形构成一个盒子形状，盒子的中心点就是父body的原点。
    //依次定义盒子的边界
    //foot  盒子的位置点
    b2EdgeShape groundBox;
    groundBox.Set(b2Vec2(0,0.8),b2Vec2(visableSize.width/PTM_RATIO,0.8));//设置地平线  （左下角。右下角）
    //第四步，我们创建shape fixture，以完成ground body
    groundBody->CreateFixture(&groundBox, 0);
    //上
    groundBox.Set(b2Vec2(0,visableSize.height/PTM_RATIO), b2Vec2(visableSize.width/PTM_RATIO,visableSize.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);
    //左
    groundBox.Set(b2Vec2(0,0), b2Vec2(0,visableSize.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    //右
    groundBox.Set(b2Vec2(visableSize.width/PTM_RATIO,0), b2Vec2(visableSize.width/PTM_RATIO,visableSize.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    
    listener=new MyContact(world,this);
    world->SetContactListener(listener);
    
    //  this->addPhysicsSprite(Vec2(100, 100));
    
}
void GameScene::addPhysicsSprite(Vec2 p){
    //创建物理引擎精灵对象
    auto sprite = Sprite::create("bird1.png");
    sprite->setPosition(Vec2(p.x, p.y));
    this->addChild(sprite);
    //物体定义
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
    
    b2Body* body = world->CreateBody(&bodyDef);
    body->SetUserData(sprite);
    
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.5, 0.5);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 1.0f;
    fixtureDef.restitution = 1.0f;
    
    body->CreateFixture(&fixtureDef);

}
void GameScene::addPigBirdIce(int chapter,int level){
    string path = FileUtils::getInstance()->getWritablePath();
    //获取可读写路径下面charpter.json文件内容
    string jsonPath = path+string("charpter2.json");             //拼接路径
    
    string data = FileUtils::getInstance()->getStringFromFile(jsonPath);//从文件获取字符串
    
    Document doc;                                      //定义文档
    doc.Parse<kParseDefaultFlags>(data.c_str());       //解析文档
    if (doc.HasMember("gameCharpter"))//如果有gameCharpter
    {
        //获取关卡数
        rapidjson::Value& _item = doc["gameCharpter"][chapter-1]["Case"][level-1];
        //遍历鸟的点，并将其添加到图层
        for (int k = 0; k<_item["BirdPoint"].Size(); ++k) {
            rapidjson::Value& _pos = _item["BirdPoint"][k];
            string str = StringUtils::format("Point%d",k+1);
            rapidjson::Value& _point = _pos[str.c_str()];
            rapidjson::Value& _Pos = _point[0];

            //创建鸟，参数为从文件解析出的鸟的Point
            auto bird = BIRD::create(Vec2(_Pos["X"].GetInt(),_Pos["Y"].GetInt()));
            this->addChild(bird);//添加到图层
            birdArray->addObject(bird);//添加到容器
        }
        for (int k = 0; k<_item["PigPoint"].Size(); ++k) {
            rapidjson::Value& _pos = _item["PigPoint"][k];
            string str = StringUtils::format("Point%d",k+1);
            rapidjson::Value& _point = _pos[str.c_str()];
            rapidjson::Value& _Pos = _point[0];
            //创建猪，参数为从文件解析出的猪的Point
            auto pig = PIG::create(Vec2(_Pos["X"].GetInt(),_Pos["Y"].GetInt()));
            pig->setBody(world);//与物理世界绑定
            this->addChild(pig);//添加到图层
            pigArray->addObject(pig);//添加到容器
        }
        for (int k = 0; k<_item["IcePoint"].Size(); ++k) {
            rapidjson::Value& _pos = _item["IcePoint"][k];
            string str = StringUtils::format("Point%d",k+1);
            rapidjson::Value& _point = _pos[str.c_str()];
            rapidjson::Value& _Pos = _point[0];
            //创建冰，参数为从文件解析出的冰的Point
            auto ice = ICE::create(Vec2(_Pos["X"].GetInt(),_Pos["Y"].GetInt()));
            ice->setBody(world);//与物理世界绑定
            this->addChild(ice);//添加到图层
            iceArray->addObject(ice);//添加到容器
        }
    }
    birdJumpToSlingShot();//鸟跳到弹弓上
}
void GameScene::addPigBirdIce()//添加猪鸟冰
{
    for (int i = 0; i<birdNum; ++i) {
        auto bird = BIRD::create(Vec2(BirdPos[i].x,BirdPos[i].y));
        this->addChild(bird,5);
        birdArray->addObject(bird);
    }
    for (int i = 0; i<pigNum; ++i) {
        auto pig = PIG::create(Vec2(PigPos[i].x,PigPos[i].y));
        this->addChild(pig,5);
        pigArray->addObject(pig);
    }
    for (int i = 0; i<iceNum; ++i) {
        auto ice = ICE::create(Vec2(IcePos[i].x,IcePos[i].y));
        this->addChild(ice,5);
        iceArray->addObject(ice);
    }
    this->birdJumpToSlingShot();
}
void GameScene::birdJumpToSlingShot()//鸟跳到弹弓上
{
    currectBird = (BIRD*)birdArray->getObjectAtIndex(0);
    currectBird->stopAllActions();
    currectBird->setRotation(0);
    JumpTo* jumpTo = JumpTo::create(0.8,midPos,92,1);
    currectBird->runAction(jumpTo);
}
void GameScene::youWin()//赢了
{
    //定义并初始化文字标签
    auto label = Label::createWithSystemFont("YOU WIN", "Marker Felt.ttf", 50);
    label->setPosition(Vec2(visableSize.width/2, visableSize.height/2));//设置位置
    label->setColor(Color3B::RED);//设置颜色为红色
    this->addChild(label);//添加到图层
    auto scale1 = ScaleTo::create(1, 2);//缩放动作
    auto scale2 = ScaleTo::create(2, 1);//缩放动作
    //瞬时动作
    auto callf = CallFunc::create([=](){
        Scene* scene = ChapterScene::createScene();//创建关卡场景
        auto trans = TransitionCrossFade::create(2, scene);//跳转动作
        Director::getInstance()->replaceScene(trans);//跳转场景
    });
    auto seq = Sequence::create(scale1,scale2,scale1,scale2,callf, NULL);//序列动作
    label->runAction(seq);//文字标签运行动作

//    this->unscheduleUpdate();//停止时间调度器
}
void GameScene::youFiled()//输了
{
    //创建标签
    auto label = Label::createWithSystemFont("YOU Failed", "Marker Felt.ttf", 50);
    label->setPosition(Vec2(visableSize.width/2, visableSize.height/2));//设置位置
    label->setColor(Color3B::RED);//设置颜色为红色
    this->addChild(label);//添加到图层
    auto scale1 = ScaleTo::create(1, 2);//缩放动作
    auto scale2 = ScaleTo::create(2, 1);//缩放动作
    auto callf = CallFunc::create([=](){
        auto root = CSLoader::createNode("Lose.csb");
        this->addChild(root);
        for (int j = 1; j<=3; ++j) {
            string str = StringUtils::format("Button_%d",j);
            auto btn = root->getChildByName<Button*>(str);
            btn->setTag(j);
            btn->addClickEventListener([=](Ref*sender){
                Scene* scene;
                switch (btn->getTag()) {
                    case 1:
                    {
                        if (_level>1&&_chapter>1) {
                            scene = GameScene::createScene(_chapter,_level-1);
                        }else{
                            _level = 1;
                            _chapter = 1;
                            scene = GameScene::createScene(_chapter,_level);
                        }
                        auto trans = TransitionFadeUp::create(2,scene);
                        Director::getInstance()->replaceScene(trans);}
                        break;
                    case 2:
                    {   scene = GameScene::createScene(_chapter,_level);
                        auto trans = TransitionFadeUp::create(2,scene);
                        Director::getInstance()->replaceScene(trans);}
                        break;
                    case 3:
                    {
                        if(_level<3&&_chapter<=2){
                            scene = GameScene::createScene(_chapter,_level+1);
                        }else{
                            _level = 1;
                            _chapter = 2;
                            scene = GameScene::createScene(_chapter,_level);
                        }
                        auto trans = TransitionFadeUp::create(2,scene);
                        Director::getInstance()->replaceScene(trans);
                        break;}
                    default:
                        break;
                }
                
            });
        }
    });
    auto seq = Sequence::create(scale1,scale2,scale1,scale2,callf, NULL);//序列动作
    label->runAction(seq);//文字运行动作
//    this->unscheduleUpdate();//关闭时间调度器
}
void GameScene::chushihua()//初始化
{
    string path = FileUtils::getInstance()->getWritablePath();
    //获取可读写路径下面charpter.json文件内容
    string jsonPath = path+string("charpter2.json");
    //拼接路径
    string data = FileUtils::getInstance()->getStringFromFile(jsonPath);
    //解析
    Document doc;//定义文件
    doc.Parse<kParseDefaultFlags>(data.c_str());
    _highScore1 = doc["gameCharpter"][_chapter-1]["Case"][_level-1]["HighScore"].GetInt();//获取最高分
    //获取猪、冰、鸟的数量
    pigNum = doc["gameCharpter"][_chapter-1]["Case"][_level-1]["PigNum"].GetInt();
    iceNum = doc["gameCharpter"][_chapter-1]["Case"][_level-1]["IceNum"].GetInt();
    birdNum = doc["gameCharpter"][_chapter-1]["Case"][_level-1]["BirdsNum"].GetInt();

    highScore = rootNode->getChildByName<Text*>("Text_4");//从节点获取最高分字符串
    string str1 = StringUtils::format("%d",_highScore1);//字符串包
    highScore->setString(str1);//修改字符串
}
void GameScene::parseJSon()//解析文件——修改
{
        string path = FileUtils::getInstance()->getWritablePath();
        //获取可读写路径下面charpter.json文件内容
        string jsonPath = path+string("charpter2.json");
        //拼接路径
        string data = FileUtils::getInstance()->getStringFromFile(jsonPath);
        //解析
        Document doc;//定义文件
        doc.Parse<kParseDefaultFlags>(data.c_str());
        //如果章节小于等于2并且关卡数小于3
        if (_level<3&&_chapter<=2) {
            //设置下一关开启
            doc["gameCharpter"][_chapter-1]["Case"][_level]["isLock"].SetBool(true);
            doc["gameCharpter"][_chapter-1]["Case"][_level-1]["HighScore"].SetInt(_highScore1);//设置最高分
            //如果最高分为总分的四分之三以上，设置为三颗星
            if ((_highScore1<=(pigNum*100+iceNum*30))&&(_highScore1>(pigNum*100+iceNum*30)*3/4)) {
                doc["gameCharpter"][_chapter-1]["Case"][_level-1]["Star"].SetInt(3);
            }
            //如果最高分为总分的二分之一到四分之三之间，设置为二颗星
            if ((_highScore1<=(pigNum*100+iceNum*30)*3/4)&&(_highScore1>(pigNum*100+iceNum*30)/2)) {
                doc["gameCharpter"][_chapter-1]["Case"][_level-1]["Star"].SetInt(2);
            }
            //如果最高分为总分的四分之一到二分之一之间，设置为一颗星
            if ((_highScore1<=(pigNum*100+iceNum*30)/2)&&(_highScore1>(pigNum*100+iceNum*30)/4)) {
                doc["gameCharpter"][_chapter-1]["Case"][_level-1]["Star"].SetInt(1);
            }
        }else{
            //如果关卡数等于3并且章节为1
            if (_level==3&&_chapter==1) {
                _level = 1;//将关卡数重新赋值为1
                //设置第二章第一关开启
                doc["gameCharpter"][_chapter]["Case"][_level-1]["isLock"].SetBool(true);
                doc["gameCharpter"][_chapter-1]["Case"][_level+1]["HighScore"].SetInt(_highScore1);//设置最高分
                //如果最高分为总分的四分之三以上，设置为三颗星
                if ((_highScore1<=(pigNum*100+iceNum*30))&&(_highScore1>(pigNum*100+iceNum*30)*3/4)) {
                    doc["gameCharpter"][_chapter-1]["Case"][_level+1]["Star"].SetInt(3);
                }
                //如果最高分为总分的二分之一到四分之三之间，设置为二颗星
                if ((_highScore1<=(pigNum*100+iceNum*30)*3/4)&&(_highScore1>(pigNum*100+iceNum*30)/2)) {
                    doc["gameCharpter"][_chapter-1]["Case"][_level+1]["Star"].SetInt(2);
                }
                //如果最高分为总分的四分之一到二分之一之间，设置为一颗星
                if ((_highScore1<=(pigNum*100+iceNum*30)/2)&&(_highScore1>(pigNum*100+iceNum*30)/4)) {
                    doc["gameCharpter"][_chapter-1]["Case"][_level+1]["Star"].SetInt(1);
                }
            }
            //如果关卡数等于3并且章节数为2
            if (_level==3&&_chapter==2) {
                doc["gameCharpter"][_chapter-1]["Case"][_level-1]["HighScore"].SetInt(_highScore1);
                //如果最高分为总分的四分之三以上，设置为三颗星
                if ((_highScore1<=(pigNum*100+iceNum*30))&&(_highScore1>(pigNum*100+iceNum*30)*3/4)) {
                    doc["gameCharpter"][_chapter-1]["Case"][_level-1]["Star"].SetInt(3);
                }
                //如果最高分为总分的二分之一到四分之三之间，设置为二颗星
                if ((_highScore1<=(pigNum*100+iceNum*30)*3/4)&&(_highScore1>(pigNum*100+iceNum*30)/2)) {
                    doc["gameCharpter"][_chapter-1]["Case"][_level-1]["Star"].SetInt(2);
                }
                //如果最高分为总分的四分之一到二分之一之间，设置为一颗星
                if ((_highScore1<=(pigNum*100+iceNum*30)/2)&&(_highScore1>(pigNum*100+iceNum*30)/4)) {
                    doc["gameCharpter"][_chapter-1]["Case"][_level-1]["Star"].SetInt(1);
                }
            }
        }
    //保存
    StringBuffer buffer;//定义字符串缓冲区
    rapidjson::Writer<rapidjson::StringBuffer>writer(buffer);//可写字符串缓冲区
    doc.Accept(writer);//写入数据
    FILE*file = fopen(jsonPath.c_str(), "wb");//打开文件
    if (file) {
        fputs(buffer.GetString(),file);//输出到文件
        fclose(file);//关闭文件
    }
}
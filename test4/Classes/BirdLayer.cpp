#include "BirdLayer.h"
#include "MainLayer.h"
#include "Collision.h"
#include "SimpleAudioEngine.h"
#include "RankBirdLayer.h"
#include <time.h>

using namespace cocos2d;
using namespace cocos2d::extension;

// 初始化
bool BirdLayer::init()
{
	//µ˜”√∏∏¿‡µƒ≥ı ºªØ
    if ( !Layer::init() )
    {
        return false;
    }
    //ªÒ»°ø…º˚«¯”Ú≥ﬂ¥Á
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //ªÒ»°ø…º˚«¯”Ú‘≠µ„◊¯±Í
    Point origin = Director::getInstance()->getVisibleOrigin();
    stopFlag = false;   //暂停标志位
    gameFlag = true;    //游戏开始的标志位
    readyFlag = true;   //游戏准备标志位
    overFlag = false;   //游戏结束标志位

	int i = random();

	if(i%2 == 0)
	{
		//¥¥Ω®±≥æ∞
		background = Sprite::create("morning.png");
	}else
	{
		//¥¥Ω®±≥æ∞
		background = Sprite::create("night.png");
	}
	//…Ë÷√√™µ„
	background->setAnchorPoint(Point(0, 0));
	//…Ë÷√æ´¡È∂‘œÛµƒŒª÷√
	background->setPosition(Point(origin.x,origin.y + visibleSize.height - background->getContentSize().height));
	//Ω´æ´¡ÈÃÌº”µΩ≤ºæ∞÷–
	this->addChild(background, 0);

	//¥¥Ω®“ª∏ˆÕ¯¬ÁΩ⁄µ„∂‘œÛ
	effectNode = NodeGrid::create();   //网络节点
	//Ω´Õ¯∏ÒΩ⁄µ„ÃÌº”µΩ≤ºæ∞
	this->addChild(effectNode, 1);
	//”Œœ∑‘§±∏ΩÁ√Ê
	ready = Sprite::create("readyBird.png");
	//…Ë÷√æ´¡È∂‘œÛµƒŒª÷√
	ready->setPosition(Point(visibleSize.width/2, visibleSize.height*4/7));
	//Ω´æ´¡ÈÃÌº”µΩ≤ºæ∞÷–
	effectNode->addChild(ready, 10);

	//¥¥Ω®µÿ√Êæ´¡È1
	floor = Sprite::create("floor.png");
	//…Ë÷√√™µ„
	floor->setAnchorPoint(Point(0, 0));
	//…Ë÷√æ´¡È∂‘œÛŒª÷√
	floor->setPosition(Point(origin.x, origin.y));
	this->addChild(floor);
	//ªÒ»°µÿ√Êæ´¡È≥ﬂ¥Á¥Û–°
	Size floorSize = floor->getContentSize();
	//µÿ√Êπˆ∂Ø
	floor->runAction(RepeatForever::create(
		Sequence::create(
				MoveTo::create(0.5, Point(-120, 0)),
				MoveTo::create(0, Point(0, 0)),
				NULL
	)));
	//¥¥Ω®“ª∏ˆLabelAtlas∂‘œÛ
	pLabelAtlas = LabelAtlas::create("0","number.png", 48, 64,'0');
	//…Ë÷√LabelAtlas∂‘œÛŒª÷√
	pLabelAtlas->setPosition(Point(visibleSize.width/2,visibleSize.height/5*4));
	//Ω´LabelAtlas∂‘œÛÃÌº”µΩ≤ºæ∞÷–
	this->addChild(pLabelAtlas,4);

	//¥¥Ω®‘›Õ£∞¥≈•æ´¡È
	pause = Sprite::create("pause.png");
	//…Ë÷√æ´¡ÈŒª÷√
	pause->setPosition(Point(32, 928));
	this->addChild(pause,10);

	//¥¥Ω®µ•µ„¥•√˛º‡Ã˝
	EventListenerTouchOneByOne* listenerPause = EventListenerTouchOneByOne::create();
	//…Ë÷√œ¬¥´¥•√˛
	listenerPause->setSwallowTouches(true);
	//ø™ º¥•√˛ ±ªÿµ˜onTouchBegan∑Ω∑®
	listenerPause->onTouchBegan = CC_CALLBACK_2(BirdLayer::onTouchPause, this);
	//ÃÌº”µΩº‡Ã˝∆˜
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerPause, pause);


	//===========≥ı ºªØ–°ƒÒ===========
	initBird();
	//ªÒ»°±≥æ∞≥ﬂ¥Á
	Size backgroundSize = background->getContentSize();
	//¥¥Ω®–°ƒÒæ´¡È
    bird = Sprite::create();
    //…Ë÷√æ´¡ÈŒª÷√
    bird->setPosition(Point(140 + origin.x, origin.y +floorSize.height + backgroundSize.height/2));
    //ÃÌº”µΩ≤ºæ∞÷–
    this->addChild(bird, 2);
    //≤•∑≈∂Øª≠
	bird->runAction(RepeatForever::create(animAc));

    //¥¥Ω®“ª∏ˆµ•µ„¥•√˛º‡Ã˝
	auto listener = EventListenerTouchOneByOne::create();
	//…Ë÷√œ¬¥´¥•√˛
	listener->setSwallowTouches(true);
	//ø™ º¥•√˛ ±ªÿµ˜onTouchBegan∑Ω∑®
	listener->onTouchBegan = CC_CALLBACK_2(BirdLayer::onTouchBegan, this);
	//ÃÌº”µΩº‡Ã˝∆˜
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
//ø™ º”Œœ∑
void BirdLayer::startGame()
{
	//启用/禁用 OpenGL 深度测试
	Director::getInstance()->setDepthTest(false);
	effectNode->runAction(SplitRows::create(0.5f, 30));
	initColumn1(); //初始化第一根柱子
	initColumn2(); //初始化第二根柱子
	birdRun();     //调用小鸟运动方法
	//…Ë÷√∂® ±ªÿµ˜÷∏∂®∑Ω∑®∏…ªÓ
	auto director = Director::getInstance();
	auto sched = director->getScheduler();
	//∂® ±ªÿµ˜update
	sched->schedule(schedule_selector(BirdLayer::update_column), this, 0.05, false);
	sched->schedule(schedule_selector(BirdLayer::update_bird), this, 0.05, false);
}
void BirdLayer::initBird()
{
	//ªÒ»°ª∫≥Â÷°
	SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
	sfc->addSpriteFramesWithFile("bird.plist", "birdP.png");
	//∂Øª≠Õº∆¨µƒ√˚≥∆
	std::string animBird[3] =
	{
			"bird1.png",
			"bird2.png",
			"bird3.png"
	};
	//¥¥Ω®¥Ê∑≈∂Øª≠÷°µƒœÚ¡ø
	Vector<SpriteFrame*> animFrames;
	//ªÒ»°∂Øª≠÷°
	animFrames.pushBack(sfc->getSpriteFrameByName(animBird[0]));
	animFrames.pushBack(sfc->getSpriteFrameByName(animBird[1]));
	animFrames.pushBack(sfc->getSpriteFrameByName(animBird[2]));
	//¥¥Ω®∂Øª≠∂‘œÛ£¨¥”÷°œÚ¡ø≤˙…˙∂Øª≠£¨º‰∏ÙŒ™0.1√Î
	Animation *anim = Animation::createWithSpriteFrames(animFrames, 0.1f);
	//¥¥Ω®∂Øª≠∂Ø◊˜∂‘œÛ
	animAc = Animate::create(anim);
	//“ÚŒ™‘› ±≤ª”√£¨±£≥÷“˝”√£¨∑¿÷π±ª◊‘∂Ø Õ∑≈
	animAc->retain();
}
//…˙≥…ÀÊª˙ ˝
int BirdLayer::random()
{
	srand((unsigned)time(NULL));
	int number = rand()%5+1;
	return number;
}

void BirdLayer::birdRun()
{
	//–°ƒÒŒª÷√
	Point birdPosition = bird->getPosition();
	//µÿ√Ê≥ﬂ¥Á
	Size floorSize = floor->getContentSize();
	float time = (birdPosition.y-240)/135;
    
    //执行动作，让小鸟下落至地面
	bird->runAction(Sequence::create(MoveTo::create(time, Point(birdPosition.x, floorSize.height+40)), NULL));
}

void BirdLayer::setRunFlag1()
{
	runFlag = true;//小鸟运动标志为
}
void BirdLayer::setRunFlag2()
{
	runFlag = false; //小鸟运动标志为
}

void BirdLayer::initColumn1()
{
	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//背景大小
	Size backSize = background->getContentSize();
	//地面尺寸大小
	Size floorSize = floor->getContentSize();
	//随机数
	int i = random();//随机数:1-5
	int height1 = 400/i; //上柱子高度
	int height2 = backSize.height - height1 - 196; //下柱子的高度
	//创建精灵批处理对象1
	SpriteBatchNode* columnNode1 = SpriteBatchNode::create("column1.png");
	//创建精灵批处理对象2
	SpriteBatchNode* columnNode2 = SpriteBatchNode::create("column2.png");
	columnFlag1 = true;    //柱子1的标志位为true
	//创建九宫格对象
	columnUnder1 = Scale9Sprite::create();
	//设置图像操作区域
	columnUnder1->updateWithBatchNode(columnNode1, Rect(0, 0, 96, 400), false, Rect(0, 30, 96, 400));
	//设置批处理对象的锚点
	columnUnder1->setAnchorPoint(Point(0, 0));
	//设置图像伸缩
	columnUnder1->setContentSize(Size(96, height1));
	if(count>0) //判断是否为首次创建（首次）
	{
		//设置位置
		columnUnder1->setPosition(Point(visibleSize.width, floorSize.height));
	}else
	{
		
		columnUnder1->setPosition(Point(visibleSize.width*2, floorSize.height));
	}
	//创建批处理对象
	columnOn1 = Scale9Sprite::create();
	//设置图像操作区域
	columnOn1->updateWithBatchNode(columnNode2, Rect(0, 0, 96, 400), false, Rect(0, 0, 96, 370));
	//设置批处理对象锚点
	columnOn1->setAnchorPoint(Point(0, 0));
	//设置图像伸缩
	columnOn1->setContentSize(Size(96, height2));
	if(count>0)//判断是否为首次创建
	{
		//设置位置
		columnOn1->setPosition(Point(visibleSize.width, visibleSize.height - height2));
	}else
	{
		//设置位置
		columnOn1->setPosition(Point(visibleSize.width*2, visibleSize.height - height2));
	}
	//将批处理对象添加到布景层中
	this->addChild(columnUnder1, 0);
	this->addChild(columnOn1, 0);
    
    //执行向左移动
	columnUnder1->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-25, 0))));
	columnOn1->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-25, 0))));
}

void BirdLayer::initColumn2()
{
	columnFlag2 = true;  //设置柱子2标志位true
	//ªÒ»°ø…º˚«¯”Ú≥ﬂ¥Á
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//ªÒ»°±≥æ∞≥ﬂ¥Á¥Û–°
	Size backSize = background->getContentSize();
	//ªÒ»°µÿ√Ê≥ﬂ¥Á¥Û–°
	Size floorSize = floor->getContentSize();
	//ªÒ»°ÀÊª˙ ˝
	int i = random();
	int height1 = 400/i;
	int height2 = backSize.height - height1 - 196;
	//ªÒ»°÷˘◊”1µƒŒª÷√
	Point columnPosition = columnUnder1->getPosition();
	//¥¥Ω®SpriteBatchNode∂‘œÛ
	SpriteBatchNode* columnNode1 = SpriteBatchNode::create("column1.png");
	//¥¥Ω®SpriteBatchNode∂‘œÛ
	SpriteBatchNode* columnNode2 = SpriteBatchNode::create("column2.png");
	//¥¥Ω®Scale9Sprite∂‘œÛ
	columnUnder2 = Scale9Sprite::create();
	//…Ë÷√ÕºœÒ≤Ÿ◊˜«¯”Ú
	columnUnder2->updateWithBatchNode(columnNode1, Rect(0, 0, 96, 400), false, Rect(0, 30, 96, 400));
	//…Ë÷√√™µ„
	columnUnder2->setAnchorPoint(Point(0, 0));
	//…Ë÷√ÕºœÒ…ÏÀı
	columnUnder2->setContentSize(Size(96, height1));
	//…Ë÷√Œª÷√
	columnUnder2->setPosition(Point(columnPosition.x + 320, floorSize.height));
	//¥¥Ω®Scale9Sprite∂‘œÛ
	columnOn2 = Scale9Sprite::create();
	//…Ë÷√ÕºœÒ≤Ÿ◊˜«¯”Ú
	columnOn2->updateWithBatchNode(columnNode2, Rect(0, 0, 96, 400), false, Rect(0, 0, 96, 370));
	//…Ë÷√√™µ„
	columnOn2->setAnchorPoint(Point(0, 0));
	//…Ë÷√ÕºœÒ…ÏÀı
	columnOn2->setContentSize(Size(96, height2));
	//…Ë÷√Œª÷√
	columnOn2->setPosition(Point(columnPosition.x + 320, visibleSize.height - height2));
	//ÃÌº”µΩ≤ºæ∞÷–
	this->addChild(columnUnder2, 0);
	this->addChild(columnOn2, 0);
	columnUnder2->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-25, 0))));
	columnOn2->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-25, 0))));
}

void BirdLayer::replay()
{
	overFlag = true;
	//Ω±≈∆
	string medal;
	//…æ≥˝∑÷ ˝
	removeChild(pLabelAtlas);
	Sprite* over = Sprite::create("gameOver.png");
	over->setPosition(Point(270, 1200));
	this->addChild(over, 10);

	overRank = Sprite::create("scoreOver.png");
	overRank->setPosition(Point(270, -100));
	this->addChild(overRank, 10);

	//÷ÿ–¬ø™ º
	replayItem = MenuItemImage::create(
		"replay.png",
		"replay_off.png",
		 CC_CALLBACK_1(BirdLayer::menuCallbackItem0, this) //µ„ª˜ ±÷¥––µƒªÿµ˜∑Ω∑®
	);
	replayItem->setPosition(Point(150, -250));
	//∑µªÿ÷˜≤Àµ•
	menuItem = MenuItemImage::create(
		"menu.png",
		"menu_off.png",
		 CC_CALLBACK_1(BirdLayer::menuCallbackItem1, this) //µ„ª˜ ±÷¥––µƒªÿµ˜∑Ω∑®
	);
	menuItem->setPosition(Point(380, -250));

	Menu* menu = Menu::create(replayItem, menuItem, NULL);
	//…Ë÷√≤Àµ•Œª÷√
	menu->setPosition(Point::ZERO);
	this->addChild(menu,10);
	//-----------------------------------------------------------------------------
	RankBirdLayer* rank = RankBirdLayer::create();
	rank->load();
	rank->save(count);
	int i = atoi(rank->scoreBird[0].c_str());
	string tempScore = StringUtils::format("%d", count);
	Label* newScore = Label::createWithTTF (tempScore, "FZKATJW.ttf", 50, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	newScore->setColor(Color3B::YELLOW);
	newScore->enableOutline(Color4B(187, 187, 187, 255),2);
	overRank->addChild(newScore);
	newScore->setPosition(Point(320, 130));
	if(i<count)
	{
		Label* ss = Label::createWithTTF (tempScore, "FZKATJW.ttf", 50, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
		ss->setColor(Color3B::YELLOW);
		ss->enableOutline(Color4B(187, 187, 187, 255),2);
		overRank->addChild(ss);
		ss->setPosition(Point(320, 50));
	}else
	{
		Label* ss = Label::createWithTTF (rank->scoreBird[0], "FZKATJW.ttf", 50, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
		ss->setColor(Color3B::YELLOW);
		ss->enableOutline(Color4B(187, 187, 187, 255),2);
		overRank->addChild(ss);
		ss->setPosition(Point(320, 50));
	}
	if(count>=atoi(rank->scoreBird[2].c_str()))
	{
		medal = "third.png";
		if(count>=atoi(rank->scoreBird[1].c_str()))
		{
			medal = "slider.png";
			if(count>=atoi(rank->scoreBird[0].c_str()))
			{
				medal = "gold.png";
			}
		}
		Sprite* gold = Sprite::create(medal);
		overRank->addChild(gold, 5);
		gold->setPosition(Point(90, 88));
	}
	//÷¥––∂Ø◊˜
	over->runAction(
		Sequence::create(
				MoveTo::create(0.2, Point(270, 750)),
				CallFunc::create(CC_CALLBACK_0(BirdLayer::moveObject, this)),
				NULL
	));
}

void BirdLayer::moveObject()
{
	overRank->runAction(MoveTo::create(0.6, Point(270, 550)));
	replayItem->runAction(MoveTo::create(0.6, Point(150, 380)));
	menuItem->runAction(MoveTo::create(0.6, Point(380, 380)));
}

void BirdLayer::gameOver()
{
	//”Œœ∑Ω· ¯
	gameFlag = false;
	Point birdPosition = bird->getPosition();
	Size birdSize = bird->getContentSize();
	Size floorSize = floor->getContentSize();
	floor->stopAllActions();
	columnUnder1->stopAllActions();
	columnOn1->stopAllActions();
	columnUnder2->stopAllActions();
	columnOn2->stopAllActions();
	bird->stopAllActions();
	bird->runAction(Sequence::create(Spawn::createWithTwoActions(MoveTo::create(0.2, Point(birdPosition.x, floorSize.height+birdSize.width/2)), RotateTo::create(0.2, 90)), NULL));
	if(!overFlag)
	{
		replay();
	}
}

void BirdLayer::update_column(float delta)
{
	//
	Point columnPosition1 = columnUnder1->getPosition();
	Point columnPosition2 = columnUnder2->getPosition();
	//
	Size columnSize = columnUnder1->getContentSize();
    
    //交替执行创建新的管子
	if(columnPosition1.x <= -columnSize.width)
	{
		removeChild(columnUnder1);
		removeChild(columnOn1);
		initColumn1();
	}
	if(columnPosition2.x <= -columnSize.width)
	{
		removeChild(columnUnder2);
		removeChild(columnOn2);
		initColumn2();
	}
}

//–°ƒÒ∂® ±œ¬¬‰
void BirdLayer::update_bird(float delta)
{
	if(gameFlag && !runFlag)//判断小鸟是否正在运动
	{
		birdRun();          //小鸟下落
	}
	//ªÒ»°–°ƒÒµ±«∞Œª÷√
	Point birdPosition = bird->getPosition();
	//ªÒ»°–°ƒÒ≥ﬂ¥Á¥Û–°
	Size birdSize = bird->getContentSize();
	//ªÒ»°µÿ√Ê≥ﬂ¥Á¥Û–°
	Size floorSize = floor->getContentSize();
	//ªÒ»°÷˘◊”Œª÷√
	Point columnPosition1 = columnUnder1->getPosition();
	Point columnPosition2 = columnOn1->getPosition();
	Point columnPosition3 = columnUnder2->getPosition();
	Point columnPosition4 = columnOn2->getPosition();
	//ªÒ»°÷˘◊”≥ﬂ¥Á¥Û–°
	Size columnSize1 = columnUnder1->getContentSize();
	Size columnSize2 = columnOn1->getContentSize();
	Size columnSize3 = columnUnder2->getContentSize();
	Size columnSize4 = columnOn2->getContentSize();

	if(birdPosition.x>columnPosition1.x && columnFlag1)
	{
		count++; //过了柱子1
		string num =StringUtils::toString(count);
		pLabelAtlas->setString(num);
		if(MainLayer::soundFlag)
		{
			pointSound();
		}
		columnFlag1 = false;
	}

	if(birdPosition.x>columnPosition3.x && columnFlag2)
	{
		count++; //过了柱子2
		string num =StringUtils::toString(count);
		pLabelAtlas->setString(num);
		if(MainLayer::soundFlag)
		{
			pointSound();
		}
		columnFlag2 = false;
	}
	//ºÏ≤‚≈ˆ◊≤
	bool check = collision((birdPosition.x - birdSize.width), (birdPosition.y - birdSize.height), (birdPosition.x + birdSize.width), (birdPosition.y + birdSize.height),
			0, 0, floorSize.width, floorSize.height);
	bool check1 = collision((birdPosition.x - birdSize.width/3), (birdPosition.y - birdSize.height/3), (birdPosition.x + birdSize.width/3), (birdPosition.y + birdSize.height/3),
			columnPosition1.x, columnPosition1.y, (columnPosition1.x + columnSize1.width), (columnPosition1.y + columnSize1.height));
	bool check2 = collision((birdPosition.x - birdSize.width/3), (birdPosition.y - birdSize.height/3), (birdPosition.x + birdSize.width/3), (birdPosition.y + birdSize.height/3),
			columnPosition2.x, columnPosition2.y, (columnPosition2.x + columnSize2.width), (columnPosition2.y + columnSize2.height));
	bool check3 = collision((birdPosition.x - birdSize.width/3), (birdPosition.y - birdSize.height/3), (birdPosition.x + birdSize.width/3), (birdPosition.y + birdSize.height/3),
			columnPosition3.x, columnPosition3.y, (columnPosition3.x + columnSize3.width), (columnPosition3.y + columnSize3.height));
	bool check4 = collision((birdPosition.x - birdSize.width/3), (birdPosition.y - birdSize.height/3), (birdPosition.x + birdSize.width/3), (birdPosition.y + birdSize.height/3),
			columnPosition4.x, columnPosition4.y, (columnPosition4.x + columnSize4.width), (columnPosition4.y + columnSize4.height));
	if(check || check1 || check2 || check3 || check4)
	{
		if(gameFlag)// ß∞‹ «Õ£÷π…˘“Ù
		{
			if(MainLayer::soundFlag)
			{
				hitSound();
			}
			if(check1 || check2 || check3 || check4)
			{
				if(MainLayer::soundFlag)
				{
					dieSound();
				}
			}
		}
		gameOver();
	}
}

bool BirdLayer::onTouchPause(Touch* touch, Event* event)
{
	if(!gameFlag)
	{
		return false;
	}
	//ªÒ»°µƒµ±«∞¥•√˛µƒ∂‘œÛ£¨≤¢◊™ªØŒ™æ´¡È¿‡–Õ
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//ªÒ»°µ±«∞◊¯±Í
	auto location = target->convertToNodeSpace(touch->getLocation());
	//ªÒ»°æ´¡Èµƒ¥Û–°
	auto size = target->getContentSize();
	//¥¥Ω®“ª∏ˆæÿ–Œ∂‘œÛ£¨∆‰¥Û–°”Îæ´¡Èœ‡Õ¨
	auto rect = Rect(0, 0, size.width, size.height);
	//≈–∂œ¥•√˛µ„ «∑Ò‘⁄ƒø±Íµƒ∑∂Œßƒ⁄
	if(!stopFlag && rect.containsPoint(location) )
	{
		stopFlag = true;
		pause->setTexture("continue_pause.png"); //换图
		Director::getInstance()->pause();
		//--------------------------------------------
		pauseBack = Sprite::create("setBackground.png");
		pauseBack->setPosition(Point(270, 600));
		this->addChild(pauseBack, 10);

		//“Ù¿÷∞¥≈•
		Sprite* music = Sprite::create("music.png");
		pauseBack->addChild(music, 1);
		music->setPosition(Point(120, 300));

		CheckBox* checkMusic = CheckBox::create(
				"sound_on.png",
				"sound_off.png",
				"sound_off.png",
				"sound_stop.png",
				"sound_stop.png"
		);
		pauseBack->addChild(checkMusic, 1);
		checkMusic->setPosition(Point(350, 300));
		checkMusic->setSelectedState(!MainLayer::musicFlag);
		checkMusic->addEventListener(CC_CALLBACK_2(BirdLayer::selectedEvent0, this));

		//“Ù–ß∞¥≈•
		Sprite* sound = Sprite::create("sound.png");
		pauseBack->addChild(sound, 1);
		sound->setPosition(Point(120, 200));

		CheckBox* checkSound = CheckBox::create(
				"sound_on.png",
				"sound_off.png",
				"sound_off.png",
				"sound_stop.png",
				"sound_stop.png"
		);
		pauseBack->addChild(checkSound, 1);
		checkSound->setPosition(Point(350, 200));
		checkSound->setSelectedState(!MainLayer::soundFlag);
		checkSound->addEventListener(CC_CALLBACK_2(BirdLayer::selectedEvent1, this));

		//ºÃ–¯”Œœ∑
		MenuItemImage* conItem = MenuItemImage::create(
				"continue.png",
				"continue_off.png",
				CC_CALLBACK_1(BirdLayer::menuCallbackItem3, this) //µ„ª˜ ±÷¥––µƒªÿµ˜∑Ω∑®
		);
		conItem->setPosition(Point(80, 80));
		//∑µªÿ÷˜≤Àµ•
		MenuItemImage* backItem = MenuItemImage::create(
			"menu.png",
			"menu_off.png",
			 CC_CALLBACK_1(BirdLayer::menuCallbackItem2, this) //µ„ª˜ ±÷¥––µƒªÿµ˜∑Ω∑®
		);
		backItem->setPosition(Point(225, 80));
		//∑µªÿ÷˜≤Àµ•
		MenuItemImage* againItem = MenuItemImage::create(
			"replay.png",
			"replay_off.png",
			 CC_CALLBACK_1(BirdLayer::menuCallbackItem4, this) //µ„ª˜ ±÷¥––µƒªÿµ˜∑Ω∑®
		);
		againItem->setPosition(Point(370, 80));

		Menu* menu = Menu::create(againItem, conItem, backItem, NULL);
		//…Ë÷√≤Àµ•Œª÷√
		menu->setPosition(Point::ZERO);
		pauseBack->addChild(menu,1);
		return true;
	}
	else
	{
		return false;
	}
}

bool BirdLayer::onTouchBegan(Touch* touch, Event* event)
{
	Point birdPosition = bird->getPosition();
	if(gameFlag)
	{
		if(readyFlag)
		{
			startGame();
			readyFlag = false;
		}
		if(MainLayer::soundFlag)
		{
			wingSound();
		}
		int move = 105;
        //设置小鸟的动作（一边上升，一边旋转）
		auto action = Spawn::createWithTwoActions(MoveTo::create(0.2, Point(birdPosition.x, birdPosition.y + move)), RotateTo::create(0, -30));
		bird->stopAllActions();
		bird->runAction(RepeatForever::create(animAc));
		bird->runAction(
				Sequence::create(
						CallFunc::create(CC_CALLBACK_0(BirdLayer::setRunFlag1, this)),
						action,  //上升
						DelayTime::create(0.05 ), //间隔
						CallFunc::create(CC_CALLBACK_0(BirdLayer::setRunFlag2, this)),
						RotateTo::create(2.0, 90), //旋转
						NULL
		));
	}
	return true;
}
void BirdLayer::menuCallbackItem0(Ref* pSender)
{
	sceneManager->goToFlappyScene(1);  //重新进入游戏场景
}
void BirdLayer::menuCallbackItem1(Ref* pSender)
{
	sceneManager->goToMainScene();
}
//∑µªÿ÷˜≤Àµ•∞¥≈•÷¥––∑Ω∑®
void BirdLayer::menuCallbackItem2(Ref* pSender)
{
	Director::getInstance()->resume();
	sceneManager->goToMainScene();
}
//ºÃ–¯”Œœ∑∞¥≈•÷¥––∑Ω∑®
void BirdLayer::menuCallbackItem3(Ref* pSender)
{
	stopFlag = false;
	this->removeChild(pauseBack);
	pause->setTexture("pause.png");
	Director::getInstance()->resume();
}
//÷ÿ–¬ø™ º”Œœ∑∞¥≈•÷¥––∑Ω∑®
void BirdLayer::menuCallbackItem4(Ref* pSender)
{
	Director::getInstance()->resume();
	sceneManager->goToFlappyScene(1);
}
//±≥æ∞“Ù¿÷∏¥—°øÚ÷¥––∑Ω∑®
void BirdLayer::selectedEvent0(Ref* pSender,CheckBox::EventType type)
{
	 switch (type)
	{
		case CheckBox::EventType::SELECTED:
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			MainLayer::musicFlag = false;
			break;
		case CheckBox::EventType::UNSELECTED:
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			MainLayer::musicFlag = true;
			break;
		default:
			break;
	}
}
//“Ù–ß∏¥—°øÚ÷¥––∑Ω∑®
void BirdLayer::selectedEvent1(Ref* pSender,CheckBox::EventType type)
{
	 switch (type)
	{
		case CheckBox::EventType::SELECTED:
			MainLayer::soundFlag = false;
			break;
		case CheckBox::EventType::UNSELECTED:
			MainLayer::soundFlag = true;
			break;
		default:
			break;
	}
}

void BirdLayer::wingSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
}

void BirdLayer::pointSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");
}

void BirdLayer::hitSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_hit.ogg");
}

void BirdLayer::dieSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_die.ogg");
}

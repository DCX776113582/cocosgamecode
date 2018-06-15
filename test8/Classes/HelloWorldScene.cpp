#include "HelloWorldScene.h"
#include <iostream>
#include "SnakeManager.h"
#include "FoodManager.h"
#include "Snake.h"
#include "ConfigDef.h"
#include "MapRegionManager.h"

USING_NS_CC;

//游戏场景
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
    
	Size size = Director::getInstance()->getWinSize();
    
    //添加背景层
	_mapLayer = LayerColor::create(Color4B(0, 0, 0, 255));
    _mapLayer->setContentSize(Size(MAP_WIDTH, MAP_HEIGHT));
	addChild( _mapLayer, 1 );
    
    //食物层
    Layer* foodLayer = Layer::create();
    _mapLayer->addChild(foodLayer, 0);
    
    //贪吃蛇层
    Layer* snakeLayer = Layer::create();
    _mapLayer->addChild(snakeLayer, 1);

    SnakeManager::GetInstance()->SetBodyParent( snakeLayer);
    
    //创建玩家
	_playerId = SnakeManager::GetInstance()->CreateSnake( Vec2(200, 400 ), Vec2( 1, 0 ), SNAKE_INIT_LENGTH, SnakeType::PLAYER );
    
    //创建AI机器人
    for( int i = 0; i < SNAKE_ENEMY_INIT_NUM; i++ ) {
		float posx = CCRANDOM_0_1() * (MAP_WIDTH - 200);
        SnakeManager::GetInstance()->CreateSnake( Vec2( posx + 100, CCRANDOM_0_1() * (MAP_HEIGHT - 200 ) + 100 ), Vec2( 1, 1 ), SNAKE_INIT_LENGTH, SnakeType::AI );
    }

    FoodManager::GetInstance()->SetBodyParent( foodLayer );
	FoodManager::GetInstance()->InitFoods( 300 );

	schedule(CC_SCHEDULE_SELECTOR(HelloWorld::update), 0.0f);

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2( HelloWorld::onTouchBegan, this );
	listener->onTouchMoved = CC_CALLBACK_2( HelloWorld::onTouchMoved, this );
	listener->onTouchEnded = CC_CALLBACK_2( HelloWorld::onTouchEnded, this );
	getEventDispatcher()->addEventListenerWithSceneGraphPriority( listener, this );

    EventListenerKeyboard* keyboard = EventListenerKeyboard::create();
    keyboard->onKeyPressed = [=]( EventKeyboard::KeyCode keyCode, Event* event ) {
        Snake* snake = SnakeManager::GetInstance()->GetSnake( _playerId );
        if( snake ) {
            snake->SetSpeedScale( 2 );
        }
    };
    keyboard->onKeyReleased = [=]( EventKeyboard::KeyCode keyCode, Event* event ) {
		Snake* snake = SnakeManager::GetInstance()->GetSnake( _playerId );
        if( snake ) {
            snake->SetSpeedScale( 1 );
        }
    };
    getEventDispatcher()->addEventListenerWithSceneGraphPriority( keyboard, this );
    
    

    return true;
}

void HelloWorld::update( float dt ) {
	
    SnakeManager::GetInstance()->Update( dt );
    FoodManager::GetInstance()->Update( dt );

    Snake* snake = SnakeManager::GetInstance()->GetSnake( _playerId );
    if( snake ) {
		Vec2 pos = _mapLayer->convertToNodeSpace( snake->GetWorldPosition() );
        Size size = Director::getInstance()->getWinSize();
        Vec2 offset = pos - Vec2( size.width * 0.5, size.height * 0.5 );
		offset.x = std::max( std::min( float(MAP_WIDTH - size.width), offset.x ), 0.0f );
        offset.y = std::max( std::min( float(MAP_HEIGHT - size.height), offset.y ), 0.0f );
        _mapLayer->setPosition( -offset );

    } else {
        _playerId = SnakeManager::GetInstance()->GetPlayerId();
    }
}

bool HelloWorld::onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* event ) {
	Vec2 touchPos = touch->getLocation();
    Snake* snake = SnakeManager::GetInstance()->GetSnake( _playerId );
    if( snake ) {
        Vec2 dir = convertToNodeSpace( touchPos ) - convertToNodeSpace( snake->GetWorldPosition() );
    	snake->RotateTo( dir.getNormalized() );
    }

	return true;
}

void HelloWorld::onTouchMoved( cocos2d::Touch* touch, cocos2d::Event* event ) {
	Vec2 touchPos = touch->getLocation();
    Snake* snake = SnakeManager::GetInstance()->GetSnake( _playerId );
    if( snake ) {
		Vec2 dir = convertToNodeSpace( touchPos ) - convertToNodeSpace( snake->GetWorldPosition() );
		snake->RotateTo( dir.getNormalized() );
	}
}

void HelloWorld::onTouchEnded( cocos2d::Touch* touch, cocos2d::Event* event ) {

}

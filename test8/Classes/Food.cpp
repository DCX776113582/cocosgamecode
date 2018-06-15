#include "Food.h"
#include "ConfigDef.h"
#include "MapRegionManager.h"

USING_NS_CC;

Food::Food(Node* parent, FoodType type, Vec2 pos):
    _type(type),
    _pos(pos),
    _body(nullptr),
    _active(true),
    _radius(0.0f),
    _die(false),
    _dieCallback(nullptr )
{
    Init( parent );
    MapRegionManager::GetInstance()->AddNodeToRegion( REGION_TYPE_FOOD, this );
}

Food::~Food() {
    MapRegionManager::GetInstance()->RemoveNodeFromRegion( REGION_TYPE_FOOD, this );
}

bool Food::Init( Node* parent ) {
    if( _type == FoodType::INVALID || parent == nullptr ) {
        return false;
    }

    _body = Sprite::create("body.png");
    
    //随机颜色
    auto r = rand()%255;
    auto g = rand()%255;
    auto b = rand()%255;
    _body->setColor(Color3B(r, g, b));
    _body->setPosition(_pos);
    parent->addChild( _body );

    if( _type == FoodType::RANDOM ) {
        _body->setScale( 0.4 );
	} else if( _type == FoodType::DIE_BODY ) {
		_body->setScale( 0.9 );
	} else if( _type == FoodType::STAR ) {
        RandomMove();
        RandomColor();
    }

    _radius = _body->getContentSize().width * 0.5 * _body->getScale();
    return true;
}

void Food::RandomMove() {
    Vec2 aim = Vec2( MAP_WIDTH * CCRANDOM_0_1(), MAP_HEIGHT * CCRANDOM_0_1() );
    float delay = ( aim - GetPosition() ).getLength() / FOOD_STAR_SPEED;
    CallFunc* callfunc = CallFunc::create( CC_CALLBACK_0( Food::RandomMove, this ) );
    _body->runAction( Sequence::create( MoveTo::create( delay, aim ), callfunc, nullptr ) );
}

void Food::RandomColor() {
    const float delay = 0.5f;
    _body->setColor(Color3B( 255 * CCRANDOM_0_1(), 255 * CCRANDOM_0_1(), 255 * CCRANDOM_0_1() ) );
    CallFunc* callfunc = CallFunc::create( CC_CALLBACK_0( Food::RandomColor, this ) );
    _body->runAction( Sequence::create( DelayTime::create( delay ), callfunc, nullptr ) );
}

void Food::beEaten( cocos2d::Vec2 toPos, std::function<void(Food*)> callback ) {
    _body->stopAllActions();

    _active = false;
    _dieCallback = callback;
    MoveTo* moveTo = MoveTo::create( 0.1, toPos );
	CallFunc* callfunc = CallFunc::create( CC_CALLBACK_0( Food::SetDie, this ) );
	_body->runAction( Sequence::create( moveTo, callfunc, nullptr ) );
}

int Food::GetScore() {
    if( _type == FoodType::RANDOM ) {
        return 1;
    } else if( _type == FoodType::DIE_BODY ) {
        return 4;
    } else if( _type == FoodType::STAR ) {
        return 6;
    }
    return 0;
}

void Food::update( float dt ) {
    if( _type == FoodType::STAR ) {
        MapRegionManager::GetInstance()->RefreshNodeRegion( REGION_TYPE_FOOD, this );
    }
}

void Food::SetDie() {
    if( _dieCallback ) {
		_dieCallback( this );
    }
    _active = false;
    _die = true;
}

void Food::Destroy() {
    if( _body ) {
        _body->removeFromParent();
        _body = nullptr;
    }
}

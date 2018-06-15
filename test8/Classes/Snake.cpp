#include "Snake.h"
#include "Food.h"
#include "ConfigDef.h"
#include "FoodManager.h"
#include "SnakeManager.h"
#include "SnakeNode.h"
#include "MapRegionManager.h"

USING_NS_CC;

Snake::Snake(Node* parent, Vec2 pos, Vec2 dir, int length ):
	_parent(nullptr),
	_headPos(pos),
	_dir(dir.getNormalized()),
	_aimDir(_dir),
	_initLength(length),
	_score(LENGTH_TO_SCORE * length ),
	_width(0),
	_rotateSpeed(M_PI * 3 ),
	_moveDelta(0.0f),
	_clipPathDelta(0.0f),
	_viewRange(150.0f),
	_warnRange(50.0f),
	_intervalPathPoint(SNAKE_SCALE_MIN_PATH_INTERVAL),
	_initSpeed(5),
	_curSpeedScale(1),
	_normalAIUpdateDelta(0.0f),
	_normalAIChangeDirDelta(0.0f),
	_changeSizeDelta(0.0f),
	_isChangeSize(false),
	_died(false),
	_type(SnakeType::AI)
{
    srand((unsigned)time(NULL));
    
    //随机颜色
    _color = rand()%5 + 1;
    
    //初始化头和身体
    sprintf(_headName, "sp/skin_%d_head.png", _color);
    sprintf(_bodyName, "sp/skin_%d_body.png", _color);
 
    
	_paths.clear();
    
    //断言
	CCAssert( _initLength > 0, "贪吃蛇初始长度必须大于0!" );
    
	Init(parent);
}

bool Snake::Init( Node* parent) {
	if( parent == nullptr) {
		return false;
	}
	_parent = parent;
	
    
	int initPathNum = _intervalPathPoint * ( _score / LENGTH_TO_SCORE );
    
	Vec2 negativeDir = -_dir;
    //当前身体为0
	int curBody = 0;
	for( int i = 0; i < initPathNum; i++ ) {
        
        //设置身体位置
		Vec2 pos = _headPos - _dir * _initSpeed * i;
		_paths.push_back( pos );
		if( curBody * _intervalPathPoint == i ) {
            
            //添加身体
			SnakeNode* body = new SnakeNode(_parent, GetId(), _bodyName);
			if( curBody != 0 ) {
                body->SetTexture(_bodyName);
			}
			body->SetPosition(pos);
			body->SetLocalZOrder(-i);
			_bodies.push_back(body);

			++curBody;
		}
	}
    
    //贪吃蛇宽度
	_width = _bodies[0]->GetRadius();
    
	return true;
}

void Snake::SetType(SnakeType type) {
	_type = type;
    _bodies[0]->SetTexture(_headName);
//	if( type == SnakeType::PLAYER ) {
//		_bodies[0]->SetTexture(_headName);
//	} else {
//		_bodies[0]->SetTexture(_headName);
//	}
}

void Snake::SetColor(int c3b ) {
	_color = c3b;
}

void Snake::Update( float dt ) {
    
    //判断是否死亡
	bool isDie = CheckDie();
	if( isDie ) {
		return;
	}

	if( _type == SnakeType::AI ) {
		UpdateNormalAI( dt );
	}
	Rotate( dt );
	Move( dt );
	CheckEatFood();
	CheckChangeSize( dt );
}

//困难ai
void Snake::UpdateHardAI( float dt ) {
	
    //获取贪吃蛇
	std::map<int, Snake*> snakes = SnakeManager::GetInstance()->GetSnakes();
    
	Vec2 force = Vec2::ZERO;
	bool isRotate = false;
	for(auto itr = snakes.begin(); itr != snakes.end(); itr++) {
        
        //头部
		if(itr->first == GetId()) {
			continue;
		}
        
        //身体
		const std::vector<SnakeNode*> bodies = itr->second->GetBodies();
        
		for(auto itrBody = bodies.begin(); itrBody != bodies.end(); itrBody++) {
			Vec2 dir = (*itrBody)->GetPosition()- _headPos ;
            
            //调整长度
			if( dir.getLength() < _warnRange ) {
				force += dir.getNormalized() * ( _warnRange - dir.getLength() ) * -1 / _warnRange;
				isRotate = true;
			}
		}
	}
	if( isRotate ) {
		RotateTo( force );
		return;
	}
    
	//发现食物
	const std::map<int, Food*> foods = FoodManager::GetInstance()->GetFoods();
    
	Vec2 minDir = Vec2::ZERO;
	float minLength = 0;
	for( auto itr = foods.begin(); itr != foods.end(); itr++ ) {
		Vec2 dir = itr->second->GetPosition() - _headPos;
		if( dir.getLength() < _viewRange ) {
			if( minDir == Vec2::ZERO || minLength > dir.getLength() ) {
				minDir = dir;
				minLength = dir.getLength();
			}
		}
	}
	if( minDir != Vec2::ZERO ) {
		force += minDir.getNormalized() * ( _viewRange - minLength ) / _viewRange;
		isRotate = true;
	}

	if( isRotate ) {
		RotateTo( force );
	}
}

//普通AI
void Snake::UpdateNormalAI( float dt ) {
	_normalAIUpdateDelta += dt;
	_normalAIChangeDirDelta -= dt;
	if( _normalAIUpdateDelta < NORMAL_AI_UPDATE_INTERVAL ) {
		return;
	}
	_normalAIUpdateDelta -= NORMAL_AI_UPDATE_INTERVAL;

	//躲避敌人
	std::vector<Vec2> regions;
	Vec2 force = Vec2::ZERO;
	float minLength = 0;
	MapRegionManager::GetInstance()->GetCoverRegion( _headPos, _warnRange, regions );
	for( auto itr = regions.begin(); itr != regions.end(); itr++ ) {
		std::list<int> snakebodies = MapRegionManager::GetInstance()->GetSnakeNodesInRegion( (*itr).y, (*itr).x );
		for( auto bItr = snakebodies.begin(); bItr != snakebodies.end(); bItr++ ) {
			SnakeNode* snakeNode = SnakeNode::GetSnakeNode( *bItr );
			if( snakeNode == nullptr || snakeNode->GetParentId() == GetId() ) {
				continue;
			}
			Vec2 dir = _headPos - snakeNode->GetPosition() ;
			float length = dir.getLength();
			if( length < _warnRange && ( minLength == 0 || length < minLength ) ) {
				force = dir;
				minLength = length;
			}
		}
	}
	if( force != Vec2::ZERO ) {
		RotateTo( force );
		return;
	}

	//躲避边界
	if( _headPos.x < _warnRange || MAP_WIDTH - _headPos.x < _warnRange ) {
		force.x = _headPos.x < _warnRange ? 1 : -1;
	}
	if( _headPos.y < _warnRange || MAP_HEIGHT - _headPos.y < _warnRange ) {
		force.y = _headPos.y < _warnRange ? 1 : -1;
	}
	if( force != Vec2::ZERO ) {
		RotateTo( force );
		return;
	}

	//发现死亡尸体
	SetSpeedScale( 1 );
	regions.clear();
	MapRegionManager::GetInstance()->GetCoverRegion( _headPos, _warnRange, regions );
	for( auto itr = regions.begin(); itr != regions.end(); itr++ ) {
		std::list<int> snakebodies = MapRegionManager::GetInstance()->GetFoodsInRegion( (*itr).y, (*itr).x );
		for( auto bItr = snakebodies.begin(); bItr != snakebodies.end(); bItr++ ) {
			Food* food = FoodManager::GetInstance()->GetFood( *bItr );
			if( food && ( food->GetType() == FoodType::DIE_BODY || food->GetType() == FoodType::STAR ) ) {
				Vec2 dir = food->GetPosition() - _headPos;
				float distance = dir.getLength();
				if( distance <= _viewRange && ( minLength == 0 || minLength > distance ) ) {
					force = dir;
					minLength = distance;
				}
			}
		}
	}
	if( force != Vec2::ZERO ) {
		RotateTo( force );
		SetSpeedScale( 2 );
		return;
	}

	//随机移动
	if( _normalAIChangeDirDelta < 0 ) {
		_normalAIChangeDirDelta = CCRANDOM_0_1() * 5;

		float theta = CCRANDOM_0_1() * 100 + 30;
		float prefix = CCRANDOM_0_1() > 0.5 ? 1 : -1;
		RotateTo( Vec2( cos( prefix * theta), sin( prefix * theta ) ) );
		return;
	}
}

//旋转
void Snake::Rotate( float dt ) {
	if( _aimDir != _dir ) {
		float angle = acos( _dir.dot( _aimDir )  );
		if( abs( angle ) <= dt * _rotateSpeed ) {
			_dir = _aimDir;
		} else {
			Vec2 N( _dir.y, -_dir.x );
			_dir.rotate( Vec2::ZERO, dt * _rotateSpeed * ( _aimDir.dot( N ) > 0 ? -1 : 1 ) );
		}
	}
}

//移动
void Snake::Move( float dt ) {
	_moveDelta += dt;
	if( _moveDelta >= SNAKE_MOVE_INTERVAL ) {
		_moveDelta -= SNAKE_MOVE_INTERVAL;

		for( int i = 1; i <= _curSpeedScale; i++ ) {
			_paths.push_front( _headPos + _dir * _initSpeed * i );
		}
		_headPos = _paths.front();

		MoveBodies();
	}

	_clipPathDelta += dt;
	if( _clipPathDelta >= SNAKE_CLIP_PATH_INTERVAL ) {
		_clipPathDelta -= SNAKE_CLIP_PATH_INTERVAL;
		_paths.resize( ( ( _score / LENGTH_TO_SCORE ) + SNAKE_LEFT_MIN_EMPTYBODY_POS ) * _intervalPathPoint );
	}
}

//移动身体
void Snake::MoveBodies() {
	int pathIndex = 0;
	int length = _score / LENGTH_TO_SCORE;
	for( auto itr = _paths.begin(); itr != _paths.end(); itr++, pathIndex++ ) {
		if( pathIndex % _intervalPathPoint == 0 ) {
			int curBody = pathIndex / _intervalPathPoint;
			if( ( curBody + 1 ) > length ) {
				return;
			}
			_bodies[curBody]->SetPosition( *itr );
		}
	}
}

//检查吃食物
void Snake::CheckEatFood() {
	std::vector<Vec2> regions;
    
	MapRegionManager::GetInstance()->GetCoverRegion( _headPos, MAX_EAT_RANGE, regions );
    
	for( auto itr = regions.begin(); itr != regions.end(); itr++ ) {
		std::list<int> foods = MapRegionManager::GetInstance()->GetFoodsInRegion( (*itr).y, (*itr).x );
		for( auto fItr = foods.begin(); fItr != foods.end(); fItr++ ) {
			Food* food = FoodManager::GetInstance()->GetFood( *fItr );
			if( food && food->IsActive() && food->GetPosition().getDistance( _headPos ) <= MAX_EAT_RANGE ) {
				food->beEaten( _headPos, CC_CALLBACK_1( Snake::OnEatFood, this ) );
			}
		}
	}
}

//改变长度
void Snake::CheckChangeSize(float dt) {
	_changeSizeDelta += dt;
	if( _changeSizeDelta < SNAKE_CHANGE_SIZE_INTERVAL ) {
		return;
	}
	_changeSizeDelta -= SNAKE_CHANGE_SIZE_INTERVAL;
	if( _isChangeSize ) {
		int length = _score / LENGTH_TO_SCORE;
		float mix = (float)(length - SNAKE_SCALE_MIN_LENGTH) / SNAKE_SCALE_ADD_MAX_LENGTH;
		float scale = SNAKE_SCALE_MIN_SCALE + SNAKE_SCALE_ADD_MAX_SCALE * mix;
		for( auto itr = _bodies.begin(); itr != _bodies.end(); itr++ ) {
			(*itr)->SetScale( scale );
		}
		_width = _bodies[0]->GetRadius();
		_intervalPathPoint = SNAKE_SCALE_MIN_PATH_INTERVAL + SNAKE_SCALE_ADD_MAX_PATH_INTERVAL * mix;
	}
}

//检查死亡
bool Snake::CheckDie() {
    
	//碰撞敌人
	std::vector<Vec2> *regions = MapRegionManager::GetInstance()->GetEntityRegion(_bodies[0]->GetId());
	for( auto itr = regions->begin(); itr != regions->end(); itr++ ) {
		std::list<int> snakebodies = MapRegionManager::GetInstance()->GetSnakeNodesInRegion( (*itr).y, (*itr).x );
		for( auto bItr = snakebodies.begin(); bItr != snakebodies.end(); bItr++ ) {
			SnakeNode* snakeNode = SnakeNode::GetSnakeNode( *bItr );
			if( snakeNode && snakeNode->GetParentId() != GetId() ) {
				Vec2 dir = snakeNode->GetPosition()  ;
				if( snakeNode->GetPosition().getDistance( _headPos ) < ( _width + snakeNode->GetRadius() ) ) {
					SetDie();
					return true;
				}
			}
		}
	}

	//碰撞边界
	if( _headPos.x < _width || MAP_WIDTH - _headPos.x < _width ) {
		SetDie();
		return true;
	}
	if( _headPos.y < _width || MAP_HEIGHT - _headPos.y < _width ) {
		SetDie();
		return true;
	}
	return false;
}

//吃食物
void Snake::OnEatFood( Food* food ) {
	if( IsDead() ) {
		return;
	}

	int oldScore = _score;
	_score += food->GetScore();
	int oldLength = oldScore / LENGTH_TO_SCORE;
	int newLength = _score / LENGTH_TO_SCORE;
	int addNum = newLength - oldLength;
	if( addNum > 0  ) {
		for( int i = 0; i < addNum; i++ ) {
			SnakeNode* body = new SnakeNode( _parent, GetId(), _bodyName);
			body->SetScale(_bodies[0]->GetScale());
			body->SetLocalZOrder( -newLength );
			_bodies.push_back(body);
		}
	}

	//改变身体大小
	if( newLength > SNAKE_SCALE_MIN_LENGTH && newLength <= ( SNAKE_SCALE_MIN_LENGTH + SNAKE_SCALE_ADD_MAX_LENGTH ) ) {
		_isChangeSize = true;
	}
}

void Snake::SetDie() {
	_died = true;
}

void Snake::Destroy() {
	//改变最大分数
	if( _type == SnakeType::PLAYER ) {
		int maxScore =	UserDefault::getInstance()->getIntegerForKey( "maxSocre" );
		int curScore = GetScore();
		if( curScore > maxScore ) {
			UserDefault::getInstance()->setIntegerForKey( "maxSocre", curScore );
		}
	}

	//增加食物
	for( auto itr = _bodies.begin(); itr != _bodies.end(); itr++ ) {
		if( CCRANDOM_0_1() > 0.5 ) {
			int foodId = FoodManager::GetInstance()->AddFood( FoodType::DIE_BODY, (*itr)->GetPosition() + Vec2( CCRANDOM_0_1() * 10, CCRANDOM_0_1() * 10 ) );
		}
	}

	//移除身体
	for( auto itr = _bodies.begin(); itr != _bodies.end(); itr++ ) {
		delete (*itr);
	}
	_bodies.clear();
}

#include "FoodManager.h"
#include "cocos2d.h"
#include "ConfigDef.h"

USING_NS_CC;

//单例设计模式
FoodManager* FoodManager::_instance = nullptr;
FoodManager* FoodManager::GetInstance() {
    if( _instance == nullptr ) {
        _instance = new FoodManager();
    }
    return _instance;
}

void FoodManager::InitFoods(int num) {
	CCAssert( _parent != nullptr, "父节点不能为空!" );
    
    //求最小值(食物数量不能超过两百)
	num = min(num, MAX_FOOD_NUM);
	for( int i = 0; i < num; i++ ) {
        //CCRANDOM_0_1(),取0-1的随机数
		AddFood(FoodType::RANDOM, Vec2(CCRANDOM_0_1() * MAP_WIDTH, CCRANDOM_0_1() * MAP_HEIGHT));
	}
}

void FoodManager::SetBodyParent(Node* parent ) {
    CCAssert(_parent == nullptr, "父节点必须为空!");
    _parent = parent;
}

Food* FoodManager::GetFood(int id) {
    if( _foods.find(id) == _foods.end() ) {
        return nullptr;
    }
    return _foods[id];
}

int FoodManager::AddFood(FoodType type, Vec2 pos ) {
    Food* food = new Food(_parent, type, pos );
    if( food ) {
        _foods.insert( std::make_pair( food->GetId(), food ) );
        return food->GetId();
    }
    return INVALID_ENTITY_ID;
}

void FoodManager::Update( float dt ) {
    CheckDie();
    RandomFood( dt );

    for( auto itr = _foods.begin(); itr != _foods.end(); itr++ ) {
        //更新食物
        itr->second->update( dt );
    }
}

void FoodManager::CheckDie() {
    auto itr = _foods.begin();
    while( itr != _foods.end() ) {
        if( itr->second->IsDead() ) {
            Food* food = itr->second;
            itr = _foods.erase( itr );
            food->Destroy();
            delete food;
        } else {
            ++itr;
        }
    }
}

void FoodManager::RandomFood( float dt ) {
    _addFoodDelta += dt;
    if( _foods.size() < MAX_FOOD_NUM && _addFoodDelta >= RANDOM_FOOD_INTERVAL ) {
        _addFoodDelta -= RANDOM_FOOD_INTERVAL;
        if( CCRANDOM_0_1() < FOOD_STAR_RANDOM_CHANCE ) {
            AddFood( FoodType::STAR, Vec2( CCRANDOM_0_1() * MAP_WIDTH, CCRANDOM_0_1() * MAP_HEIGHT ) );
        } else {
            AddFood( FoodType::RANDOM, Vec2( CCRANDOM_0_1() * MAP_WIDTH, CCRANDOM_0_1() * MAP_HEIGHT ) );
        }
    }
}

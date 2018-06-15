#include "MapRegionManager.h"
#include "Entity.h"
#include <algorithm>

USING_NS_CC;

//单例设计模式
MapRegionManager* MapRegionManager::_instance = nullptr;
MapRegionManager* MapRegionManager::GetInstance() {
    if( _instance == nullptr ) {
        _instance = new MapRegionManager();
    }
    return _instance;
}

MapRegionManager::MapRegionManager()
{
    //ceil :返回大于或者等于指定表达式的最小整数
	_regionWidth = ceil(MAP_WIDTH/MAP_REGION_WIDTH );
	_regionHeight = ceil(MAP_HEIGHT/MAP_REGION_WIDTH );

	_regionFoods = new list<int>*[_regionHeight];
    _regionSnakes = new list<int>*[_regionHeight];
    
	for( int r = 0; r < _regionWidth; r++ ) {
		_regionFoods[r] = new list<int>[_regionWidth];
        _regionSnakes[r] = new list<int>[_regionWidth];

		for( int c = 0; c < _regionWidth; c++ ) {
			_regionFoods[r][c] = std::list<int>();
			 _regionSnakes[r][c] = std::list<int>();
		}
	}
}

MapRegionManager::~MapRegionManager() {
	for( int r = 0; r < _regionWidth; r++ ) {
		delete[] _regionFoods[r];
        delete[] _regionSnakes[r];
	}
	delete[] _regionFoods;
}

void MapRegionManager::AddNodeToRegion(int type, Entity* node) {
    vector<Vec2> regions;
	GetCoverRegion(node->GetPosition(), node->GetRadius(), regions );
    _entities[node->GetId()] = regions;

    for( auto itr = regions.begin(); itr != regions.end(); itr++ ) {
        AddNodeInRegion( type, node->GetId(), (*itr).y, (*itr).x );
    }
}

void MapRegionManager::RemoveNodeFromRegion( int type, Entity* node ) {

    auto itr = _entities.find( node->GetId() );
    CCAssert( itr != _entities.end(), "" );

    for( auto rItr = itr->second.begin(); rItr != itr->second.end(); rItr++ ) {
        RemoveNodeInRegion( type, node->GetId(), (*rItr).y, (*rItr).x );
    }
    _entities.erase( itr );
}

void MapRegionManager::RefreshNodeRegion( int type, Entity* entity ) {
    int id = entity->GetId();
	auto itr = _entities.find(id);
    CCAssert(itr != _entities.end(), "此区域不存在" );

	std::vector<Vec2> oldRegions(itr->second);
	itr->second.clear();
    
    //获取覆盖区域
	GetCoverRegion(entity->GetPosition(), entity->GetRadius(), _entities[id]);

	auto oItr = oldRegions.begin(), nItr = itr->second.begin();
    while( oItr != oldRegions.end() ) {
        RemoveNodeInRegion( type, id, (*oItr).y, (*oItr).x );
        ++oItr;
    }
	while( nItr != itr->second.end() ) {
        AddNodeInRegion( type, id, (*nItr).y, (*nItr).x );
        ++nItr;
    }
}

void MapRegionManager::GetCoverRegion( const Vec2& pos, float radius,  std::vector<cocos2d::Vec2>& result ) {
    int leftCol = fmax( 0.0f, floor( ( pos.x - radius ) / MAP_REGION_WIDTH ) );
    int rightCol = fmin( (float)_regionWidth, floor( pos.x + radius ) / MAP_REGION_WIDTH );
    int topRow = fmin( (float)_regionHeight, floor( pos.y + radius ) / MAP_REGION_HEIGHT );
    int bottomRow = fmax( 0.0f, floor( pos.y - radius ) / MAP_REGION_HEIGHT );

    for( int r = bottomRow; r <= topRow; r++ ) {
        for( int c = leftCol; c <= rightCol; c++ ) {
            result.push_back( Vec2( c, r ) );
        }
    }
}

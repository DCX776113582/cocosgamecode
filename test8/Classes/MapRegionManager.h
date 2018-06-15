#ifndef _MAPREGION_MANAGER_H_
#define _MAPREGION_MANAGER_H_

#include "ConfigDef.h"
#include <map>
#include <vector>
#include <list>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

//地图区域管理类
class Entity;
class MapRegionManager {
public:
	~MapRegionManager();
	static MapRegionManager* GetInstance();
    
    //增加节点到地图中
    void AddNodeToRegion(int type, Entity* node);
    //移除节点从地图中
	void RemoveNodeFromRegion(int type, Entity* node);
    //获取食物从地图中
    inline list<int> GetFoodsInRegion( int row, int col ) { return _regionFoods[row][col]; }
    //获取贪吃蛇从地图中
    inline list<int> GetSnakeNodesInRegion( int row, int col ) { return _regionSnakes[row][col]; }
    //获取所有的实体类
	vector<cocos2d::Vec2>* GetEntityRegion(int id ) { return &_entities[id]; }
    //刷新地图中的节点
    void RefreshNodeRegion(int type, Entity* entity );

	inline void GetCoverRegion( const cocos2d::Vec2& pos, float radius,  std::vector<cocos2d::Vec2>& result );

	int GetRegionWidthNum() { return _regionWidth; }
	int GetRegionHeightNum() { return _regionHeight; }

private:
    MapRegionManager();
    inline void GetRegion( const cocos2d::Vec2& pos, int& row, int& col ) {
        row = floor( pos.y / MAP_REGION_HEIGHT );
        col = floor( pos.x / MAP_REGION_WIDTH );
    }

    void AddNodeInRegion( int type, int id, int row, int col ) {
        std::list<int>* root = nullptr;
        if( type == REGION_TYPE_FOOD ) {
            root = &_regionFoods[row][col];
        } else if( type == REGION_TYPE_SKANE ) {
            root = &_regionSnakes[row][col];
        }

        (*root).push_back( id );
    }
    void RemoveNodeInRegion( int type, int id, int row, int col ) {
        std::list<int>* root = nullptr;
        if( type == REGION_TYPE_FOOD ) {
            root = &_regionFoods[row][col];
        } else if( type == REGION_TYPE_SKANE ) {
            root = &_regionSnakes[row][col];
        }

        (*root).remove( id );
    }


private:
    static MapRegionManager*        _instance;
    //区域的宽和高
    unsigned int                    _regionWidth;
    unsigned int                    _regionHeight;
    //区域中所有的食物
    list<int>**                     _regionFoods;
    //区域中所有的贪吃蛇
    list<int>**                     _regionSnakes;
    //所有实体
    map<int, vector<cocos2d::Vec2>> _entities;
};

#endif

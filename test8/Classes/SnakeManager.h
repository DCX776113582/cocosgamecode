#ifndef _SNAKEMANAGER_H
#define _SNAKEMANAGER_H

#include <map>
#include "cocos2d.h"
#include "Snake.h"
USING_NS_CC;
using namespace std;

//贪吃蛇管理类

//更新数据
struct RebornData {
    SnakeType type;
    int color;
};

class SnakeManager {
public:
    static SnakeManager* GetInstance();
    //设置父节点
    void SetBodyParent(Node* parent );
    //创建贪吃蛇
    int CreateSnake(Vec2 Pos, Vec2 Dir, int Length, SnakeType type);
    //获取玩家id
    int GetPlayerId();
    //获取贪吃蛇（id）
    Snake* GetSnake(int id ) {
        if( _snakes.find( id ) == _snakes.end() ) {
            return nullptr;
        }
        return _snakes[id];
    }
    //获取所有的贪吃蛇
    const std::map<int, Snake*>& GetSnakes() { return _snakes; }

    void Update( float dt );

private:
    SnakeManager():
    _parent( nullptr ){
    }
    
    //移除死亡的蛇
    void RemoveDeadSnakes(float dt);
    //刷新贪吃蛇
    void UpdateSnakes(float dt);

private:
    //父节点
    Node*                        _parent;
    //更新数据
    vector<RebornData>           _reviveInfo;
    //贪吃蛇
    map<int, Snake*>             _snakes;
    static SnakeManager*         _instance;
};

#endif

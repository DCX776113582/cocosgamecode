#ifndef _FOODMANAGER_H_
#define _FOODMANAGER_H_

#include <map>
#include "cocos2d.h"
#include "Food.h"
USING_NS_CC;
using namespace std;



//食物管理类
class FoodManager {
public:
    static FoodManager* GetInstance();
    
    //设置父节点
    void SetBodyParent(Node* parent);
    //获得食物
    Food* GetFood(int id);
    //添加位置
    int AddFood(FoodType type, Vec2 pos);
    //初始化食物
	void InitFoods(int Num);
    //获取所有的食物
    const std::map<int, Food*>& GetFoods() { return _foods; }

    void Update( float dt );

private:
    FoodManager():
        _parent( nullptr ),
        _addFoodDelta( 0.0f )
    {}
    
    //检查食物是否死亡
    void CheckDie();
    //随机食物
    void RandomFood(float dt);

private:
    //单例设计模式
    static FoodManager*       _instance;
    //父类
    Node*					  _parent;
    //存储食物
    std::map<int, Food*>      _foods;
    //增加食物的间隔
    float                     _addFoodDelta;
};

#endif

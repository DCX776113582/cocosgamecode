#ifndef _FOOD_H_
#define _FOOD_H_

#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;
using namespace std;

//食物类型
enum class FoodType {
    INVALID = -1,       //未知物体
    RANDOM  = 1,        //随机物体
    DIE_BODY,           //死亡物体
    STAR                //星星物体
};

class Food : public Entity {
public:
    //父节点，食物类型，位置
    Food(Node* parent, FoodType type, Vec2 pos);
    ~Food();
    
    void beEaten(Vec2 toPos, function<void(Food*)> callback );
    
    //获取分数
    int GetScore();
    //获取食物类型
	FoodType GetType() { return _type; }
    //获取身体位置
	const Vec2& GetPosition() { return _body->getPosition(); }
    //获取半径
    float GetRadius() { return _radius; }
    //是否活跃
    bool IsActive() { return _active; }
    //销毁
    void Destroy();
    //设置死亡
    void SetDie();
    bool IsDead() { return _die; }
    //更新函数
    void update( float dt );
private:
    //初始化父类
    bool Init(Node* parent );
    
    //随机移动
    void RandomMove();
    //随机颜色
    void RandomColor();

private:
    FoodType              _type;       //食物类型
    Vec2                  _pos;        //位置
    Sprite*               _body;       //身体
    float                 _radius;     //半径
    bool                  _die;        //是否死亡
	bool				  _active;     //是否活跃
    function<void(Food*)> _dieCallback;//死亡回调函数
};

#endif

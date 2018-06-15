#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <vector>
#include <list>
#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;
using namespace std;

//贪吃蛇类

//贪吃蛇类型（玩家，ai）
enum class SnakeType {
	PLAYER = 1,
	AI
};

class Food;
class SnakeNode;
class Snake : public Entity {
public:
    //父节点，位置，动作，长度
	Snake(Node* parent, Vec2 Pos, Vec2 Dir, int Length );
    
    //get
public:
    //获取位置（头位置）
	const Vec2& GetPosition() { return _paths.front(); }
    //获取做游戏世界中的位置
	Vec2 GetWorldPosition() { return _parent->convertToWorldSpace( GetPosition() ); }
    //获取贪吃蛇类型
    const SnakeType& GetType() { return _type; }
    //获取贪吃蛇身体
    const std::vector<SnakeNode*>& GetBodies() { return _bodies; }
    //获取半径
    float GetRadius() { return _width; }
    //获取分数
    int GetScore() { return _score; }
    
    //set
public:
    //设置速度
	void SetSpeedScale(int scale ) { _curSpeedScale = scale; }
    //设置贪吃蛇类型
	void SetType(SnakeType type );
    //设置颜色
	void SetColor(int c3b );
    //获取颜色
	const int& GetColor() { return _color; }
    //判断是否死亡
	bool IsDead() { return _died; }
    //旋转
	void RotateTo( cocos2d::Vec2 dir ) { _aimDir = dir.getNormalized(); }
    //更新函数
	void Update( float dt );
    //设置死亡
	void SetDie();
    //销毁
	void Destroy();
    //检查死亡
	bool CheckDie();

private:
    //初始化
	bool Init(Node* parent);
    //困难Ai
	void UpdateHardAI(float dt);
    //普通Ai
	void UpdateNormalAI(float dt);
    //旋转
	void Rotate(float dt);
    //移动
	void Move(float dt);
    //移动身体
	void MoveBodies();
    //检测食物
	void CheckEatFood();
    //检测长度
	void CheckChangeSize(float dt );
	void OnEatFood(Food* food );

private:
	Node* 			    _parent;
	Vec2			    _headPos;
	Vec2			    _dir;
	Vec2				_aimDir;
    
    //颜色
	int				    _color;
	int 				_initLength;
	int					_score;
	int					_width;
	float				_rotateSpeed;
	float				_moveDelta;
	float 				_clipPathDelta;
	float 				_viewRange;
	float 				_warnRange;
	int					_intervalPathPoint;
	int					_initSpeed;
	int					_curSpeedScale;
	float 				_normalAIUpdateDelta;
	float 				_normalAIChangeDirDelta;
	float 				_changeSizeDelta;
	bool 				_isChangeSize;
	list<Vec2>			_paths;
	vector<SnakeNode*>	_bodies;
	bool				_died;
	SnakeType			_type;
    
    char                _headName[32];
    char                _bodyName[32];
};

#endif

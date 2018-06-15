#ifndef _SNAKENODE_H_
#define _SNAKENODE_H_

#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;

//身体类
class SnakeNode : public Entity {
public:
    //父类，父类ID，节点图片名称
    SnakeNode(Node* parent, int parentId, const char* textureName);
    
    ~SnakeNode();
    
    //get
public:
    //获取id
    static SnakeNode* GetSnakeNode(int id);
    
    //获得半径
    float GetRadius() { return _sprite->getContentSize().width * _sprite->getScale() * 0.5; }
    //获取位置
    const Vec2& GetPosition() { return _sprite->getPosition(); }
    //获取父类id
    int GetParentId() { return _parentId; }
    //获取缩放
    float GetScale() { return _sprite->getScale(); }

public:
    //改变纹理
    void SetTexture(const char* textureName);
    //设置颜色
    void SetColor(Color3B color ) { _sprite->setColor( color ); }
    //设置位置
    void SetPosition(Vec2 pos );
    //设置Z轴
    void SetLocalZOrder( int order ) { _sprite->setLocalZOrder( order ); }
    //设置缩放
    void SetScale( float scale ) { _sprite->setScale( scale ); }
    

private:
    
    Sprite*                    _sprite;
	Label*					   _label;
    int                        _parentId;
};
static std::map<int, SnakeNode*>       _snakeNodes;

#endif

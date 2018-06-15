#include "SnakeNode.h"
#include "MapRegionManager.h"

USING_NS_CC;

SnakeNode* SnakeNode::GetSnakeNode( int id ) {
	auto itr = _snakeNodes.find( id );
    if( itr != _snakeNodes.end() ) {
		return itr->second;
    } else {
        return nullptr;
    }
}

SnakeNode::SnakeNode( cocos2d::Node* parent, int parentId, const char* textureName ):
    _parentId( parentId )
 {
    _sprite = Sprite::create( textureName );
    parent->addChild( _sprite );

	_label = Label::create( "", "Arail", 13 );
	_sprite->addChild( _label );
	_label->setPosition( 15, 15 );

    MapRegionManager::GetInstance()->AddNodeToRegion( REGION_TYPE_SKANE, this );
    _snakeNodes.insert( std::make_pair( GetId(), this ) );
}

SnakeNode::~SnakeNode() {
    MapRegionManager::GetInstance()->RemoveNodeFromRegion( REGION_TYPE_SKANE, this );
    _sprite->removeFromParent();

    _snakeNodes.erase( _snakeNodes.find( GetId() ) );
}

void SnakeNode::SetPosition( Vec2 pos ) {
    _sprite->setPosition( pos );
    MapRegionManager::GetInstance()->RefreshNodeRegion( REGION_TYPE_SKANE, this );
}

void SnakeNode::SetTexture( const char* textureName ) {
    _sprite->setTexture(textureName);
}

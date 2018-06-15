#include "SnakeManager.h"
#include "cocos2d.h"
#include "ConfigDef.h"


USING_NS_CC;

//单例设计模式
SnakeManager* SnakeManager::_instance = nullptr;
SnakeManager* SnakeManager::GetInstance() {
    if( _instance == nullptr ) {
        _instance = new SnakeManager();
    }
    return _instance;
}

void SnakeManager::SetBodyParent(Node* parent ) {
    CCAssert(_snakes.empty(), "需要确保无蛇!");
    _parent = parent;
}

int SnakeManager::CreateSnake(Vec2 Pos, Vec2 Dir, int Length, SnakeType type ) {
    CCAssert( _parent != nullptr, "需要先设置父节点!" );

    Snake* snake = new Snake( _parent, Pos, Dir, Length );
    if( snake != nullptr ) {
        snake->SetType( type );
        _snakes.insert(std::make_pair( snake->GetId(), snake));
        return snake->GetId();
    } else {
        return INVALID_ENTITY_ID;
    }
}


int SnakeManager::GetPlayerId() {
    for(auto itr = _snakes.begin(); itr != _snakes.end(); itr++ ) {
        if( itr->second->GetType() == SnakeType::PLAYER ) {
            return itr->first;
        }
    }
    return INVALID_ENTITY_ID;
}

void SnakeManager::Update( float dt ) {
    
    RemoveDeadSnakes( dt );
    UpdateSnakes( dt );

}

void SnakeManager::RemoveDeadSnakes( float dt ) {
    auto itr = _snakes.begin();
    while( itr != _snakes.end() ) {
        if( itr->second->IsDead() ) {
			RebornData data = { itr->second->GetType(), itr->second->GetColor() };
			_reviveInfo.push_back( data );
            itr->second->Destroy();
            delete (itr->second);
            itr = _snakes.erase( itr );
        } else {
            ++itr;
        }
    }
}

void SnakeManager::UpdateSnakes( float dt ) {
    for( auto itr = _snakes.begin(); itr != _snakes.end(); itr++ ) {
        itr->second->Update( dt );
    }

    for( auto itr = _reviveInfo.begin(); itr != _reviveInfo.end(); itr++ ) {
        int id = CreateSnake( Vec2( CCRANDOM_0_1() * (MAP_WIDTH - 200) + 100, CCRANDOM_0_1() * (MAP_HEIGHT - 200) + 100 ), Vec2( CCRANDOM_0_1(), CCRANDOM_0_1() ), SNAKE_INIT_LENGTH, (*itr).type );
        Snake* snake = SnakeManager::GetInstance()->GetSnake( id );
        if( snake ) {
            snake->SetColor((*itr).color);
        }
    }
    _reviveInfo.clear();
}

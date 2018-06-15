//
//  AStarDemo.hpp
//  ArmatureDemo
//
//  Created by QCJ-Mac on 16/1/12.
//
//

#ifndef AStarDemo_hpp
#define AStarDemo_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "AStar.h"
USING_NS_CC;
class AStarDemo : public Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    
    void goCallback(Ref*);
    void clearCallback(Ref*);
    
    void stepCallback();
    
    bool onTouchBegan(Touch*, Event*);
    
    CREATE_FUNC(AStarDemo);
    
private:
    int    m_row;
    int    m_col;
    Layer* m_obstacles;
    AStar  m_aStar;
    
    Sprite* m_people;
    Sprite* m_target;
    
    int m_routeStep;
    std::vector<ASCOORD> m_route;
    
    Vec2  correctPosition(const Vec2& pos){
        return Vec2(((int)pos.x/40)*40.0f,((int)pos.y/40)*40.0f);
    }
    ASCOORD computeASCOORD(const Vec2& pos){
        return ASCOORD((int)(pos.x/40),(int)(pos.y/40));
    }
};

#endif /* AStarDemo_hpp */

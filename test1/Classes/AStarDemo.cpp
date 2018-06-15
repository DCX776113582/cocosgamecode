//
//  AStarDemo.cpp
//  ArmatureDemo
//
//  Created by QCJ-Mac on 16/1/12.
//
//

#include "AStarDemo.hpp"
USING_NS_CC;
using namespace std;


Scene* AStarDemo::scene()
{
    Scene* scene = Scene::create();
    AStarDemo* layer = AStarDemo::create();
    scene->addChild(layer);
    return scene;
}
#include <Box2D/Box2D.h>

bool AStarDemo::init()
{
    if (!Layer::init() )
    {
        return false;
    }
//    b2PolygonShape
//    b2Body
    
    m_row = 15;
    m_col = 15;
    
    m_aStar.SetMapSize(m_row,m_col);
    m_aStar.ClearObstacles();
    m_aStar.SetDiagonalEnable(false);
    
    Vec2 startPos(100.0f,100.0f);
    m_aStar.SetStart(computeASCOORD(startPos));
    
    m_people = Sprite::create("people.png");
    m_people->setAnchorPoint(Vec2(0.0f,0.0f));
    m_people->setPosition(correctPosition(startPos));
    this->addChild(m_people);
    
    
    Vec2 targetPos(300.0f,300.0f);
    m_aStar.SetTarget(computeASCOORD(targetPos));
    
    m_target = Sprite::create("CloseNormal.png");
    m_target->setAnchorPoint(Vec2(0.0f,0.0f));
    m_target->setPosition(correctPosition(targetPos));
    this->addChild(m_target);
    
    
    m_obstacles = Layer::create();
    m_obstacles->setPosition(0,0);
    this->addChild(m_obstacles);
    
    for(int i = 0 ; i<m_col ; i++)
    {
        Sprite* block = Sprite::create("block.png");
        block->setAnchorPoint(Vec2(0.0f,0.0f));
        block->setPosition(i*40,m_row*40);
        this->addChild(block);
    }
    
    for(int i = 0 ; i<m_col ; i++)
    {
        Sprite*block = Sprite::create("block.png");
        block->setAnchorPoint(Vec2(0.0f,0.0f));
        block->setPosition(m_col*40,i*40);
        this->addChild(block);
    }
    
    
    MenuItemFont* goItem = MenuItemFont::create("GO!",CC_CALLBACK_1(AStarDemo::goCallback,this));
    goItem->setAnchorPoint(Vec2(0.0f,0.0f));
    goItem->setPosition(Vec2((m_col+2)*40,300));
    
    MenuItemFont* clearItem = MenuItemFont::create("RESET!",CC_CALLBACK_1(AStarDemo::clearCallback,this));
    clearItem->setAnchorPoint(Vec2(0.0f,0.0f));
    clearItem->setPosition(Vec2((m_col+2)*40,400));
    
    Menu* menu = Menu::create(goItem,clearItem,NULL);
    
    menu->setPosition(Vec2(0,0));
    this->addChild(menu);
    
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(AStarDemo::onTouchBegan,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    
    
    return true;
}

void AStarDemo::clearCallback(Ref*)
{
    m_aStar.ClearObstacles();
    m_people->stopAllActions();
    
    
    Vec2 startPos(100.0f,100.0f);
    m_aStar.SetStart(computeASCOORD(startPos));
    m_people->setPosition(correctPosition(startPos));
    
    
    this->removeChild(m_obstacles);
    m_obstacles = Layer::create();
    m_obstacles->setPosition(0,0);
    this->addChild(m_obstacles);
}

void AStarDemo::stepCallback()
{
    if(m_routeStep<m_route.size()-1)
    {
        m_people->runAction(Sequence::create(MoveTo::create(0.2f,Vec2(m_route[m_routeStep]._x*40.0f,m_route[m_routeStep]._y*40.0f)),CallFunc::create(CC_CALLBACK_0(AStarDemo::stepCallback,this)),NULL));
        m_routeStep++;
    }
}

void AStarDemo::goCallback(Ref*)
{
    if(m_aStar.ComputeRoute())
    {
        m_route.clear();
        m_routeStep = 0;
        m_aStar.GetRoute(&m_route);
        
        m_people->runAction(Sequence::create(MoveTo::create(0.2f,Vec2(m_route[m_routeStep]._x*40.0f,m_route[m_routeStep]._y*40.0f)),CallFunc::create(CC_CALLBACK_0(AStarDemo::stepCallback,this)),NULL));
        m_routeStep++;
    }
    else
        MessageBox("NO ROUTE!","NO ROUTE!");
}

bool AStarDemo::onTouchBegan(Touch* touch, Event* e)
{
    ASCOORD coord = computeASCOORD(touch->getLocation());
    
    if(coord._x<m_col && coord._y<m_row && coord!=m_aStar.GetStart() && coord!=m_aStar.GetTarget())
    {
        Vec2 pos = correctPosition(touch->getLocation());
        
        Sprite* block = Sprite::create("block.png");
        block->setAnchorPoint(Vec2(0.0f,0.0f));
        block->setPosition(pos);
        m_obstacles->addChild(block);
        
        printf("(%d,%d)\n",coord._x,coord._y);
        m_aStar.SetObstacle(coord);
    }
    
    return false;
}
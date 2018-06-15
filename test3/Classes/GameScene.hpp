//
//  GameScene.hpp
//  FishMan
//
//  Created by MAC on 16/6/28.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp
#include "cocos2d.h"
using namespace cocos2d;
#include "ui/CocosGUI.h"
using namespace ui;
#include "Cannon.hpp"
#include "fish.hpp"
#include "bullet.hpp"
#include "FishNet.hpp"
#include "score.hpp"
#include "startScene.hpp"
class GameScene: public Layer
{
public:
    static Scene* createScene();
    virtual bool init()override;
    void initUI();
    
    
    //    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(GameScene);  //宏定义
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
    virtual void onTouchMoved(Touch *touch, Event *unused_event) override;
    virtual void onTouchEnded(Touch *touch, Event *unused_event) override;
    virtual void onTouchCancelled(Touch *touch, Event *unused_event) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    //updateFish
    void updateFish(float dt);
    void addFish();
    //updateHit
    void updateHit(float dt);
    //加载纹理
    void loadTexture();
    //加载能量条
    void addEnergy(int _energy);
    void addgold(int n);
    void subgold(int n);
    //点面碰撞检测
    bool isContains(Rect& rect,Point& point);
    //面面碰撞
    bool isRectHitRect(Rect& rect1,Rect& rect2);
private:
    Size visibleSize;    //屏幕大小
    bool isSoundEfect;   //声音开关
    Sprite* EnergyIcon;  //能量图标
    int energy = 0;          //能量
    Cannon* cannon;      //武器
    Bullet* bullet;      //子弹
    int cannonLevel;     //武器等级
    Label* label1;       //分数标签：
//    Layer* layer;
    EventListenerTouchOneByOne* touchListener;
    //SpriteBatchNode与批量节点类似
    SpriteBatchNode* fishSheet;  //批处理纹理
    SpriteBatchNode* bulletSheet;
    SpriteBatchNode* fishNetSheet;
};


#endif /* GameScene_hpp */

















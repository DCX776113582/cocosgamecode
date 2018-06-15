#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class ProfileInfoLayer;
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void update( float dt );

	bool onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* event );
	void onTouchMoved( cocos2d::Touch* touch, cocos2d::Event* event );
	void onTouchEnded( cocos2d::Touch* touch, cocos2d::Event* event );

    
    CREATE_FUNC(HelloWorld);

private:
	int							_playerId;
	cocos2d::Layer*				_mapLayer;
	
};

#endif 

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;

class BeginScene : public cocos2d::Layer,public ScrollViewDelegate
{
public:
    virtual bool init()override;
    static cocos2d::Scene* scene();
    void menuCloseCallback(Ref* pSender);
    CREATE_FUNC(BeginScene);
    
public:
    //scrollView代理
    virtual void scrollViewDidScroll(ScrollView* view)override;
    virtual void scrollViewDidZoom(ScrollView* view)override;
    
    //触摸代理
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent)override;
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent)override;
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent)override;
public:
    virtual void keyBackClicked()override;
    void initData();
    void initScrollView();
    void onExit()override;
    
private:
    ScrollView *view;
    Point p1;
    Point scrollViewOffSet;
    SpriteBatchNode *ninjaBatchNode;
    //CCLayerColor *backButtonLayer;
    static float count;
};

#endif // __HELLOWORLD_SCENE_H__

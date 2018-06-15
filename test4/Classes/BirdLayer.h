#ifndef __BirdLayer_H__
#define __BirdLayer_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "GameSceneManager.h"

using namespace cocos2d;
using namespace std;
using namespace cocos2d::extension;
using namespace ui;

class BirdLayer : public Layer
{
public:
	
	
	bool stopFlag;              //暂停标志位
	bool runFlag = false;       //小鸟运动标志为
	
	int count = 0;              //记录分数
	 
	bool columnFlag1;           //穿过柱子的标志位1
	bool columnFlag2;           //穿过柱子的标志位2
	
	bool gameFlag;              //游戏开始的标志位
	bool readyFlag;             //游戏准备标志位
	
	bool overFlag;              //游戏结束标志位
	
	NodeGrid* effectNode;       //网络节点
	LabelAtlas* pLabelAtlas;    //文本标签
	Sprite* overRank;           //记分板精灵
	MenuItemImage* replayItem;  //重新开始菜单
	MenuItemImage* menuItem;    //返回主菜单
	Sprite* pause;              //暂停
	
	Sprite *background;         //背景
	
	Sprite *floor;              //地板
	
	Scale9Sprite* columnUnder1; //指向柱子的九宫格精灵指针
	Scale9Sprite* columnOn1;    //指向柱子的九宫格精灵指针
	Scale9Sprite* columnUnder2; //指向柱子的九宫格精灵指针
	Scale9Sprite* columnOn2;    //指向柱子的九宫格精灵指针
    
	Sprite* bird;               //小鸟
	
	Sprite* ready;              //准备精灵
	Sprite* pauseBack;          //暂停背景精灵
	
	Animate* animAc;            //动画
	
	GameSceneManager* sceneManager;//场景管理
public:
	
	virtual bool init();
	
	void initBird();
	
	void startGame();
	
	void gameOver();
	
	void birdRun();      //小鸟运动
	 
	void wingSound();    //播放即时音效 小鸟飞
	void pointSound();   //播放即时音效 点击屏幕
	void hitSound();     //播放即时音效 碰撞
	void dieSound();     //播放即时音效 死亡
	
	void update_column(float delta); //更新柱子
	
	void update_bird(float delta);   //定时回调，小鸟的碰撞监测
	
	void moveObject();   //游戏结束结束界面运动的方法
	
	void initColumn1();  //初始化柱子的方法一
	void initColumn2();  //初始化柱子的方法二
	
	int random();        //生成随机数
	
	void menuCallbackItem0(Ref* pSender);//重新开始游戏
	void menuCallbackItem1(Ref* pSender);//游戏结束切换到主菜单
	void menuCallbackItem2(Ref* pSender);//游戏暂停切换到主菜单
	void menuCallbackItem3(Ref* pSender);//继续游戏
	void menuCallbackItem4(Ref* pSender);//
	
    //复选框回调
	void selectedEvent0(Ref* pSender,CheckBox::EventType type);
    //复选框回调
	void selectedEvent1(Ref* pSender,CheckBox::EventType type);
	
	void replay();  //游戏结束重玩
	
	bool onTouchBegan(Touch* touch, Event* event);
	bool onTouchPause(Touch* touch, Event* event);
	void setRunFlag1(); //设置小鸟运动标志位1
	void setRunFlag2(); //设置小鸟云顶标志位2

    
    CREATE_FUNC(BirdLayer);
};

#endif

#ifndef __FruitLayer_H__
#define __FruitLayer_H__

#include "cocos2d.h"
#include "GameSceneManager.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace std;
using namespace cocos2d::extension;
using namespace ui;

class FruitLayer : public Layer
{
public:
	int count;      //记录分数
	int boss;       //boss出现次数
	bool stopFlag;  //暂停标志位
	bool bossFlag;  //boss标志位
	bool gameFlag;  //游戏开始标志位
	bool readyFlag; //游戏准备标志位
	bool overFlag;  //游戏结束标志位
	bool actionFlag;//动作标志位
	int height1;    //柱子高度
	int height2;    //柱子高度
	NodeGrid* effectNode; //网格节点
	Sprite* bossSprite;   //boss精灵
	//—™Ãı
	Slider* slider;       //显示boss血条
	LabelAtlas* pLabelAtlas; //显示分数的文本标签
	Sprite* overRank;        //记分板精灵
	MenuItemImage* relayItem;//重新开始菜单
	MenuItemImage* menuItem; //返回主菜单的菜单
	Sprite* pauseBack;       //暂停背景精灵
	//…˘√˜‘›Õ£∞¥≈•æ´¡È
	Sprite* pause;           //暂停精灵
	//
	Sprite* ready;           //准备精灵
	//…˘√˜±≥æ∞æ´¡È
	Sprite* background;      //背景精灵
	//…˘√˜µÿ√Êæ´¡È
	Sprite* floor;           //地板精灵
	//…˘√˜÷˘◊”æ´¡È
	Sprite* columnUnder1;    //柱子精灵
	Sprite* columnOn1;       //柱子
	Sprite* columnUnder2;    //柱子
	Sprite* columnOn2;       //柱子
	//≥°æ∞π‹¿Ì÷∏’Î
	GameSceneManager* sceneManager; //场景管理器
	//¥Ê¥¢ÀÆπ˚∂‘œÛ
	vector<Sprite*>* fruit;  //存储水果精灵
public:
	//≥ı ºªØ≤ºæ∞µƒ∑Ω∑®
	virtual bool init();
	//ø™ º”Œœ∑
	void startGame();
	//…˙≥…ÀÊª˙ ˝∑Ω∑®
	int random();
	//≥ı ºªØ÷˘◊”
	void initColumn1();
	void initColumn2();
	//”Œœ∑Ω· ¯
	void gameOver();
	//”Œœ∑ ß∞‹
	void replay();       //游戏结束重玩界面
	void check();        //碰撞监测
	void moveObject();   //游戏结束界面运动
	//≤•∑≈“Ù–ß
	void wingSound();    //播放夹空音效
	void eatSound();     //播放夹破水果音效
	//∏¸∏ƒ±Í÷æŒª
	void setFlag();      //设置动作标志位
	//∂® ±ªÿµ˜∑Ω∑®
	void update_fruit(float delta);  //定时产生水果
	void update_boss(float delta);   //定时产生boss
	void update_column(float delta); //定时产生柱子
	void menuCallback0(Ref* pSender);
	void menuCallback1(Ref* pSender);
	void menuCallback2(Ref* pSender);
	void menuCallback3(Ref* pSender);
	void menuCallback4(Ref* pSender);
	//∏¥—°øÚªÿµ˜∑Ω∑®
	void selectedEvent0(Ref* pSender,CheckBox::EventType type);
	void selectedEvent1(Ref* pSender,CheckBox::EventType type);
	//ø™ ºµ•µ„¥•øÿ ¬º˛µƒ¥¶¿Ì∑Ω∑®
	bool onTouchBegan(Touch* touch, Event* event); //开始触控事件
	bool onTouchPause(Touch* touch, Event* event); //暂停按钮
	CREATE_FUNC(FruitLayer);
};



#endif

//
//  QuitGameLayerGradient.cpp
//  SaveTheNinja
//
//  Created by fly on 14-11-23.
//
//

#include "QuitGameLayerGradient.h"
#include "CommonDefine.h"

bool QuitGameLayerGradient::init()
{
    if (!LayerGradient::init()) {
        return false;
    }
    this->initWithColor(Color4B(139, 26, 26, 255), Color4B(0, 0, 0, 0));
    
    auto quit = LabelBMFont::create("QUIT", "uiImage/font.fnt");
    
    MenuItemLabel *quitGame = cocos2d::MenuItemLabel::create(quit);
    quitGame->setPosition(Vec2(VISIBLE_SIZE_WIDTH/4, VISIBLE_SIZE_HEIGHT/5*2));
    quitGame->setTag(1);
    quitGame->setTarget(this, menu_selector(QuitGameLayerGradient::quitGameMethod));
    
    auto back = LabelBMFont::create("BACK", "uiImage/font.fnt");
    MenuItemLabel *backGame = MenuItemLabel::create(back);
    backGame->setPosition(VISIBLE_SIZE_WIDTH/4*3 - backGame->getContentSize().width - 10, VISIBLE_SIZE_HEIGHT/5*2);
    backGame->setTag(2);
    backGame->setTarget(this, menu_selector(QuitGameLayerGradient::quitGameMethod));
    
    Menu *menu = Menu::create(quitGame,backGame,NULL);
    menu->setPosition(Vec2(40, 10));
    this->addChild(menu);
    
    
    this->setTouchEnabled(true);
    return true;
}

void QuitGameLayerGradient::quitGameMethod(Ref *pSender)
{
    MenuItemFont *font = static_cast<MenuItemFont*>(pSender);
    int temp = font->getTag();
    if (temp == 1) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
        CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
        Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
#endif
    }else if(temp == 2)
    {
        if (this) {
            this->removeFromParent();
            Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
        }
    }
}

//void QuitGameLayerGradient::registerWithTouchDispatcher()
//{
//    auto touchListener = EventListenerTouchOneByOne::create();
//
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
//}
void QuitGameLayerGradient::onTouchCancelled(Touch * touch,Event * unused_event)
{
    log("touch cancelled\n");
}


bool QuitGameLayerGradient::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    return true;
}

void QuitGameLayerGradient::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    
}

void QuitGameLayerGradient::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    
}




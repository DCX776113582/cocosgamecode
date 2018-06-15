#include "AppDelegate.h"
#include "GameScene.h"
#include "ShopScene.h"
#include "AnimateTools.h"
#include "BeginScene.h"
#include "AudioController.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    Director* pDirector = Director::sharedDirector();
    EGLView* pEGLView = EGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    pEGLView->setDesignResolutionSize(510, 369, kResolutionExactFit);
    
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    AnimateTools::addAnimationCache();
    // create a scene. it's an autorelease object
    CCScene *pScene = BeginScene::scene();
    
   //CCScene * pScene = ShopScene::CreateScene();
    // run
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameImage.plist");
    
    
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
    CCDirector::sharedDirector()->pause();
    
    // if you use SimpleAudioEngine, it must be pause
    AudioController::getInstance()->m_isBgMusicOn = false;
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
    CCDirector::sharedDirector()->resume();
    // if you use SimpleAudioEngine, it must resume here
    if (AudioController::getInstance()->m_isBgMusicOn) {
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    }
    
}

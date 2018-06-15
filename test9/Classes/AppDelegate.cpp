#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "FistScene.hpp"
//#include "TheLogin.hpp"
// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// 如果你想要一个不同的上下文,修改glContextAttrs的价值
// 它将影响所有平台
void AppDelegate::initGLContextAttrs()
{
    // 设置OpenGL上下文属性: 红,绿,蓝,α,深度、模板
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// 如果你想使用包管理器安装更多的包,
// 不修改或删除这个函数
static int register_all_packages()
{
    return 0; //国旗的包管理器
}

bool AppDelegate::applicationDidFinishLaunching() {
    // 初始化主管
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("AngryBird", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("AngryBird");
#endif
        director->setOpenGLView(glview);
    }

    // 打开显示帧
    director->setDisplayStats(false);

    // FPS。默认值是1.0/60如果你不叫这个
    director->setAnimationInterval(1.0f / 60);

    // 设置设计解决方案
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::EXACT_FIT);
//    auto frameSize = glview->getFrameSize();
//    // 如果框架的高度大于中等大小的高度。
//    if (frameSize.height > mediumResolutionSize.height)
//    {
//        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
//    }
//    // 如果框架的高度大于小尺寸的高度。
//    else if (frameSize.height > smallResolutionSize.height)
//    {
//        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
//    }
//    // 如果框架的高度小于中等大小的高度。
//    else
//    {
//        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
//    }

    register_all_packages();
    FileUtils::getInstance()->addSearchPath("cocoStuio");
    FileUtils::getInstance()->addSearchPath("cocoStuio/Default");
    FileUtils::getInstance()->addSearchPath("cocoStuio/Res");

    // 创建一个场景。这是一个生成对象
    auto scene = FirstScene::createScene();

    // 运行
    director->runWithScene(scene);

    return true;
}

// 这个函数将调用应用程序时不活跃。注意,接到电话的时候被调用。
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// 这个函数将调用应用程序时再次活跃
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}

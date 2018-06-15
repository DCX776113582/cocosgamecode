#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <platform/android/jni/JniHelper.h>

extern "C"
{
    //方法名与java类中的包名+方法名，以下划线连接
    void Java_org_cocos2dx_cpp_AppActivity_printt(JNIEnv*  env, jobject thiz)
    {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("bg_music03.mp3");
    }
}
#endif

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width,0));
    closeItem->setAnchorPoint(Vec2(1, 0));
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    
    
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;//定义Jni函数信息结构体
    //getStaticMethodInfo 此函数返回一个bool值表示是否找到此函数
    const char * jniClass = "org/cocos2dx/cpp/AppActivity";//这里写你所要调用的java代码的类名
    bool isHave = JniHelper::getStaticMethodInfo(minfo,jniClass,"callJni","()I");
    if (!isHave) {
        CCLog("jni->%s/callJni:此函数不存在", jniClass);
    }else{
        CCLog("jni->%s/callJni:此函数存在", jniClass);
        //        jstring jdata = minfo.env->NewStringUTF(data);
        //调用此函数
        int num = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);
        char str[20];
        sprintf(str, "num%d",num);
        auto label = Label::createWithSystemFont(str, "fonts/Marker Felt.ttf", 30);
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
        
    }
    CCLog("jni-java函数执行完毕");
#endif
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


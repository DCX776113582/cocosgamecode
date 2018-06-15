#include "BeginScene.h"
#include "BottomLayer.h"
#include "CommonDefine.h"
#include "AudioController.h"
#include "ContainerLayer.h"
#include "QuitGameLayerGradient.h"

USING_NS_CC;

float BeginScene::count = 0;

CCScene* BeginScene::scene()
{
    CCScene *scene = CCScene::create();
    BeginScene *layer = BeginScene::create();
    scene->addChild(layer);
    return scene;
}

bool BeginScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setKeypadEnabled(true);
    SHARED_DIRECTOR->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
    
    if (AudioController::getInstance()->m_isBgMusicOn) {
        PLAY_MUSIC("music/kare-san-sui-demo.mp3", true);
    }
    
    BottomLayer *index = BottomLayer::create();
    index->setContentSize(CCSize(VISIBLE_SIZE_WIDTH, VISIBLE_SIZE_HEIGHT/3.2));
    index->setPosition(ccp(0, 0));
    index->setAnchorPoint(ccp(0, 0));
    this->addChild(index,1);
    
    this->initData();
    this->initScrollView();
    return true;
}

void BeginScene::initData()
{
    //初始化背景
    CCSprite *bg = CCSprite::create("BeginSceneImage/BeginBg.png");
    bg->setPosition(ccp(VISIBLE_SIZE_WIDTH/2, VISIBLE_SIZE_HEIGHT/2));
    this->addChild(bg,-1);
    
    //初始化标题后粒子效果
//    CCParticleFlower *flower = CCParticleFlower::create();
//    flower->cocos2d::CCNode::setScale(1.5);
//    flower->setPosition(ccp(VISIBLE_SIZE_WIDTH/2, VISIBLE_SIZE_HEIGHT/5*4));
//
    
    CCParticleSystemQuad *flower = CCParticleSystemQuad::create("BeginSceneImage/beginStar.plist");
    flower->setPosition(ccp(VISIBLE_SIZE_WIDTH/2, VISIBLE_SIZE_HEIGHT/5*4));
    this->addChild(flower,0);
    
    //设置标题
    CCSprite *gameTitle = CCSprite::create("BeginSceneImage/gameTitle.png");
    gameTitle->setPosition(ccp(VISIBLE_SIZE_WIDTH/2, VISIBLE_SIZE_HEIGHT/4*3));
    gameTitle->setScale(0.5);
    this->addChild(gameTitle,10);
    
}

void BeginScene::initScrollView()
{
    ContainerLayer *layer = ContainerLayer::create();
    layer->setContentSize(CCSize(VISIBLE_SIZE_WIDTH*(LEVEL_COUNT + 1)/2, VISIBLE_SIZE_HEIGHT/5*3));
    layer->setPosition(ccp(0, 0));
    
    view = CCScrollView::create(CCSize(VISIBLE_SIZE_WIDTH,VISIBLE_SIZE_HEIGHT/5*4));
    view->setContainer(layer);
    view->setDirection(kCCScrollViewDirectionHorizontal);
    view->setDelegate(this);
    view->setTouchEnabled(false);
    view->setBounceable(false);
    view->setPosition(ccp(0, 0));
    this->addChild(view,0);
    
}

void BeginScene::keyBackClicked()
{
    QuitGameLayerGradient *layer = QuitGameLayerGradient::create();
    layer->setPosition(0, 0);
    this->addChild(layer,10);
}

void BeginScene::onExit()
{
    SHARED_DIRECTOR->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
    
}

#pragma mark - CCScrollViewDelegate
void BeginScene::scrollViewDidScroll(cocos2d::extension::CCScrollView *view)
{
}

void BeginScene::scrollViewDidZoom(cocos2d::extension::CCScrollView *view)
{
    
}

#pragma mark - CCTouchDelegate 触摸代理
bool BeginScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    p1 = pTouch->getLocation();
    return true;
}

void BeginScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void BeginScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint p = pTouch->getLocation();
    float dis = p.x - p1.x;
    if (count > -VISIBLE_SIZE_WIDTH/2*(LEVEL_COUNT - 1) && count < 0) {
        if (p.x > p1.x && dis > 10) {
            count += VISIBLE_SIZE_WIDTH/2;
        }else if(p.x < p1.x && abs(dis) > 10)
        {
            count -= VISIBLE_SIZE_WIDTH/2;
        }
    }else if (count == 0)
    {
        if(p.x < p1.x && abs(dis) > 10)
        {
            count -= VISIBLE_SIZE_WIDTH/2;
        }
    }else if (count == -VISIBLE_SIZE_WIDTH/2*(LEVEL_COUNT - 1))
    {
        if (p.x > p1.x && abs(dis) > 10) {
            count += VISIBLE_SIZE_WIDTH/2;
        }
    }
    view->setContentOffsetInDuration(ccp(count, scrollViewOffSet.y), 0.5);
}

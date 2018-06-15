//
//  CommonDefine.h
//  AngryBird-1.0
//
//  Created by love on 14-10-16.
//
//

#ifndef AngryBird_1_0_CommonDefine_h
#define AngryBird_1_0_CommonDefine_h

/* CCDirctor 尺寸 */

#define SHARED_DIRECTOR CCDirector::sharedDirector()

#define VISIBLE_SIZE SHARED_DIRECTOR->getVisibleSize()

#define VISIBLE_SIZE_WIDTH VISIBLE_SIZE.width

#define VISIBLE_SIZE_HEIGHT VISIBLE_SIZE.height

#define DIRECTOR_REPLACE(scene) SHARED_DIRECTOR->replaceScene(scene)

#define VSIZE CCSize vsize = CCDirector::sharedDirector()->getVisibleSize()

/* music */
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include "AudioController.h"

#define SIMPLE_AUDIO SimpleAudioEngine::sharedEngine()

#define PLAY_MUSIC(pszFilePath,bLoop) SIMPLE_AUDIO->playBackgroundMusic(pszFilePath,bLoop)

#define PLAY_EFFECT(pszFilePath) SIMPLE_AUDIO->playEffect(pszFilePath)


/* DataCenter */
#define DATA_CENTER GameDataCenter::getInstance()
#define NOTIFICATION_CENTER YJNotificationCenter::getInstance()
#define USER_DEFAULT CCUserDefault * user =    CCUserDefault::sharedUserDefault()
#define SET_INT(k,v)  user->setIntegerForKey(k,v)
#define SET_BOOL(k,v) user->setBoolForKey(k,v)
#define GET_INT(k)    user->getIntegerForKey(k)
#define GET_BOOL(k)   user->getBoolForKey(k)
#define USER_FLUSH    user->flush()

/* BOX2D */
#define PTM_RATIO 48.0f

#define SPRITE_FRAME_CACHE(name) CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name)

#define LEVEL_COUNT 5

#endif

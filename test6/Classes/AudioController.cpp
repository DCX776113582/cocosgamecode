//
//  AudioController.cpp
//  AnimalAid
//
//  Created by Jason on 14-11-16.
//
//

#include "AudioController.h"
#include "GameDataCenter.h"

static AudioController * sg_instance = NULL;
AudioController* AudioController::getInstance(){
    if (sg_instance == NULL) {
        sg_instance = new AudioController();
    }
    return sg_instance;
}

void AudioController::playGameBGMusic(){
    if (AudioController::getInstance()->m_isBgMusicOn) {
        PLAY_MUSIC("music/ChiloutJapan.mp3", true);
    }
}

void AudioController::playEnterGame(){
    PLAY_EFFECT("music/start.mp3");
}

void AudioController::playLevelChoiseButtonClick(){
    PLAY_EFFECT("music/shuriken01.mp3");
}

void AudioController::playNormalButtonClick(){
    int index = 1 + arc4random()%4;
    PLAY_EFFECT(CCString::createWithFormat("music/button0%d.mp3",index)->getCString());
}

void AudioController::playManDieth(){
    PLAY_EFFECT("music/airwwhoosh.mp3");
}

void AudioController::playGetOneCoin(){
    PLAY_EFFECT("music/coin2.mp3");
}

void AudioController::playExplosion(){
    PLAY_EFFECT("music/explosion01.mp3");
}

void AudioController::playBoardToLong(){
    PLAY_EFFECT("music/bonus_long.mp3");
}

void AudioController::playGetLife(){
    PLAY_EFFECT("music/bonus_life.mp3");
}

void AudioController::playBombComing(){
    PLAY_EFFECT("music/bomb1.mp3");
}

void AudioController::playManOnBoard(){
    PLAY_EFFECT("music/jump_c4c.mp3");
}

void AudioController::playGameOver(){
    if (DATA_CENTER->m_bestScore < DATA_CENTER->m_score) {
        PLAY_EFFECT("music/kids.mp3");
    }else{
        PLAY_EFFECT("music/game_over.mp3");
    }
}

void AudioController::parseAllMusic(){
    if (SIMPLE_AUDIO->isBackgroundMusicPlaying()) {
        SIMPLE_AUDIO->stopAllEffects();
        SIMPLE_AUDIO->pauseBackgroundMusic();
        AudioController::getInstance()->m_isBgMusicOn = false;
    }else{
        SIMPLE_AUDIO->resumeBackgroundMusic();
        AudioController::getInstance()->m_isBgMusicOn = true;
    }
    
}

void AudioController::playCrazyState(){
    PLAY_EFFECT("music/nighto01.mp3");
    //PLAY_EFFECT("music/kung_fu.caf");
    SIMPLE_AUDIO->playEffect("music/kung_fu.mp3", true);
    SIMPLE_AUDIO->pauseBackgroundMusic();
}

void AudioController::playEnterSelect(){
    PLAY_EFFECT("music/bonus_metal.mp3");
}

AudioController::AudioController(){
    m_isBgMusicOn = true;
}
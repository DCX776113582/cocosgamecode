#ifndef _CONFIGDEF_H_
#define _CONFIGDEF_H_

//配置数据

const int INVALID_ENTITY_ID = -1;

//敌人初始化长度
const int SNAKE_ENEMY_INIT_NUM = 10;

//初始化长度
const int SNAKE_INIT_LENGTH = 5;

const float SNAKE_MOVE_INTERVAL = 0.03f;
const float SNAKE_CLIP_PATH_INTERVAL = 0.5f;
const int SNAKE_LEFT_MIN_EMPTYBODY_POS = 5;

const float RANDOM_FOOD_INTERVAL = 0.3f;
//最大食物数量
const int MAX_FOOD_NUM = 100;
//普通ai
const float NORMAL_AI_UPDATE_INTERVAL = 0.2f;
//长度改变值
const float SNAKE_CHANGE_SIZE_INTERVAL = 1.0f;

const int SNAKE_SCALE_MIN_LENGTH = 20;
const int SNAKE_SCALE_ADD_MAX_LENGTH = 180;
//最小缩放
const float SNAKE_SCALE_MIN_SCALE = 1.0f;
//每次最大增加
const float SNAKE_SCALE_ADD_MAX_SCALE = 1.0f;
//最小长度
const int SNAKE_SCALE_MIN_PATH_INTERVAL = 6;
//每次增加最大函数
const int SNAKE_SCALE_ADD_MAX_PATH_INTERVAL = 6;

const float FOOD_STAR_RANDOM_CHANCE = 0.02;
const int FOOD_STAR_SPEED = 200;

const float MAX_EAT_RANGE = 30.0f;

//地图大小
const float MAP_WIDTH = 1280*2;
const float MAP_HEIGHT = 960*2;

const int LENGTH_TO_SCORE = 6;

//区域大小
const float MAP_REGION_WIDTH = 400.0f;
const float MAP_REGION_HEIGHT = 400.0f;

const int REGION_TYPE_FOOD = 1;
const int REGION_TYPE_SKANE = 2;

#endif

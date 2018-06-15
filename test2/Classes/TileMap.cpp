//
//  TileMap.cpp
//  DefendTheRadish
//
//  Created by mac on 18/4/16.
//
//

#include "TileMap.hpp"
#define MAX_X 15
#define MAX_Y 10
TileMap* TileMap::tileMaps = new TileMap();
TileMap* TileMap::getInstance()
{
    return tileMaps;
}
TMXTiledMap* TileMap::addMap()
{
    tileMap = TMXTiledMap::create("Level1_1.tmx");
    return tileMap;
}
TMXLayer* TileMap::getLayer1()
{
    layer1 = tileMap->getLayer("block");
    return layer1;
}
TMXLayer* TileMap::getLayer2()
{
    layer2 = tileMap->getLayer("objects");
    return layer2;
}
TMXLayer* TileMap::getLayer3()
{
    layer3 = tileMap->getLayer("clouds");
    return layer3;
}
TMXLayer* TileMap::getLayer4()
{
    layer4 = tileMap->getLayer("mate");
    layer4->setVisible(false);
    return layer4;
}
void TileMap::getGroupObject()
{
    auto obj = tileMap->getObjectGroup("object");
    for (int i = 0; i<8; ++i) {
        string str = StringUtils::format("obj%d",i+1);
        auto object1 = obj->getObject(str);
        auto pos = Vec2(object1.at("x").asFloat(),object1.at("y").asFloat());
        obj1.push_back(pos);
        log("point:(x:%f,y:%f)",obj1.at(i).x,obj1.at(i).y);
    }
}
void TileMap::getGroupObjects()
{
    auto obj = tileMap->getObjectGroup("objects");
    for (int i = 0; i<7; ++i) {
        string str = StringUtils::format("obj%d",i+1);
        auto object1 = obj->getObject(str);
        auto pos = Vec2(object1.at("x").asFloat(),object1.at("y").asFloat());
        obj2.push_back(pos);
        log("point:(x:%f,y:%f)",obj2.at(i).x,obj2.at(i).y);
    }
}
void TileMap::getGroupClouds(TMXTiledMap* _tileMap)
{
    auto obj = _tileMap->getObjectGroup("clouds");
    for (int i = 0; i<3; ++i) {
        string str = StringUtils::format("cloud%d",i+1);
        auto object1 = obj->getObject(str);
        auto pos = Vec2(object1.at("x").asFloat(),object1.at("y").asFloat());
        obj3.push_back(pos);
        log("point:(x:%f,y:%f)",obj3.at(i).x,obj3.at(i).y);
    }
}
void TileMap::clear()
{
    obj1.clear();
    obj2.clear();
    obj3.clear();
}

void TileMap::movePlayer(Vec2 p)//玩家移动，且不可穿墙
{
    //获取目标位置
    int x = p.x / tileMap->getTileSize().width;//每块的宽度 转换成块数
    //_tileMap->getMapSize().height*_tileMap->getTileSize().height总高度  －p.y ：是从下往上的高度
    //getTileSize().height每一块的高度
    int y = (tileMap->getMapSize().height*tileMap->getTileSize().height-p.y)/tileMap->getTileSize().height;
    Vec2 tiledCoord = Vec2(x,y); //块的坐标（哪一块）
    log("x = %d,y = %d",x,y);//输出
    //范围检测
    if (tiledCoord.x<0||tiledCoord.x>=MAX_X||tiledCoord.y<0||tiledCoord.y>=MAX_Y) {
        return;
    }
    //墙的碰撞检测  getTileGIDAt：获取属性值
    int tiled_id = layer2->getTileGIDAt(tiledCoord);
    log("%d",tiled_id);//输出
    if (tiled_id)
    {
        auto _value = tileMap->getPropertiesForGID(tiled_id);//得到属性GID
        auto _valueStr = _value.getDescription();//得到描述
        log("*************Value : %s",_valueStr.c_str());//输出描述
        if (!_value.isNull())
        {
            if (_valueStr.find("isHit")!=-1)
            {
                auto collidableValue = _value.asValueMap().at("isHit").asString().c_str();
                auto strTure = "True";//初始化
                log("%s",collidableValue);//输出
                if (collidableValue&&strcmp(collidableValue, strTure))
                {
                    log("can't move");//输出——不能移动
                    return;
                }
            }
        }
    }
}

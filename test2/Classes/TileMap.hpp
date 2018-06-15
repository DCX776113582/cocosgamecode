//
//  TileMap.hpp
//  DefendTheRadish
//
//  Created by mac on 18/4/16.
//
//

#ifndef TileMap_hpp
#define TileMap_hpp

#include "Header.h"
class TileMap{
private:
    static TileMap* tileMaps;
    TileMap(){}
    ~TileMap(){}
    
    TMXTiledMap* tileMap;
    TMXLayer*layer1;
    TMXLayer*layer2;
    TMXLayer*layer3;
    TMXLayer*layer4;
public:
    vector<Vec2>obj1;
    vector<Vec2>obj2;
    vector<Vec2>obj3;

    TMXTiledMap* addMap();
    TMXLayer*getLayer1();
    TMXLayer*getLayer2();
    TMXLayer*getLayer3();
    TMXLayer*getLayer4();
    void clear();
    void getGroupObject();
    void getGroupObjects();
    void getGroupClouds(TMXTiledMap* _tileMap);
    void movePlayer(Vec2 p);
public:
    static TileMap* getInstance();
};

#endif /* TileMap_hpp */

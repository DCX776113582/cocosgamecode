//
//  YJNotificationCenter.h
//  AngryBird-1.0
//
//  Created by love on 14-10-17.
//
//

#ifndef __AngryBird_1_0__YJNotificationCenter__
#define __AngryBird_1_0__YJNotificationCenter__

#include <iostream>
#include <vector>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class YJObserver;

class YJNotificationCenter {
    

private:
    YJNotificationCenter();
    map<string, YJObserver*> m_observerMap;
    
public:
    static YJNotificationCenter* getInstance();
    
    bool attachObserver(YJObserver *observer, string key);
    
    bool dttachObserver(string key);
    void dttachAllOberserver();
    
    void notifyAll();
    bool notifyForKey(string key);
};


class YJObserver {
    
public:
    virtual void notifyUpdate() = 0;
};
#endif /* defined(__AngryBird_1_0__YJNotificationCenter__) */

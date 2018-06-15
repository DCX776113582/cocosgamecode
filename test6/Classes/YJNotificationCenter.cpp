//
//  YJNotificationCenter.cpp
//  AngryBird-1.0
//
//  Created by love on 14-10-17.
//
//

#include "YJNotificationCenter.h"

static YJNotificationCenter *S_NotifyInstance = NULL;

/* 私有的构造方法 */
YJNotificationCenter::YJNotificationCenter(){
}

/* 单利模式 */
YJNotificationCenter* YJNotificationCenter::getInstance(){
    if (S_NotifyInstance == NULL) {
        S_NotifyInstance = new  YJNotificationCenter();
    }
    
    return S_NotifyInstance;
}


/* 注册到通知中心 */
bool YJNotificationCenter::attachObserver(YJObserver *observer, string key){
    if ((m_observerMap.find(key) == m_observerMap.end())) {
        m_observerMap.insert(map<string, YJObserver*>::value_type(key,observer));
        return true;
    }else{
        return false;
    }
    
}

/* 从通知中心移除 */
bool YJNotificationCenter::dttachObserver(string key){
    if (!(m_observerMap.find(key) == m_observerMap.end())) {
        map<string, YJObserver*>::iterator itor = m_observerMap.find(key);
        m_observerMap.erase(itor);
        return true;
    }else{
        return false;
    }
}

/* 删除所有的观察者 */
void YJNotificationCenter::dttachAllOberserver(){
    m_observerMap.clear();
}

/* 给所有注册者发送消息 */
void YJNotificationCenter::notifyAll(){
    for (map<string, YJObserver*>::iterator iter = m_observerMap.begin(); iter != m_observerMap.end(); iter++) {
        YJObserver *temp = iter->second;
        temp->notifyUpdate();
    }
}

/* 给对应key发送消息 */
bool YJNotificationCenter::notifyForKey(string key){
    if (!(m_observerMap.find(key) == m_observerMap.end())) {
        map<string, YJObserver*>::iterator iter = m_observerMap.find(key);
        YJObserver *temp = iter->second;
        temp->notifyUpdate();
        return true;
    }else{
        return false;
    }
}

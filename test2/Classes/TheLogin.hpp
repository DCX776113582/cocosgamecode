//
//  TheLogin.hpp
//  DefendTheRadish
//
//  Created by mac on 18/4/19.
//
//

#ifndef TheLogin_hpp
#define TheLogin_hpp

#include "Header.h"
class TheLogin:public Layer{
public:
    static Scene* createScene();
    bool init()override;
    CREATE_FUNC(TheLogin);
    void exitApp();
    void menuCloseCallback(cocos2d::Ref* pSender);
//    void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
    
private:
    char*str;
    Size visableSize;
};

#endif /* TheLogin_hpp */

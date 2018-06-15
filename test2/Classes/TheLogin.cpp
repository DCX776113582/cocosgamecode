//
//  TheLogin.cpp
//  DefendTheRadish
//
//  Created by mac on 18/4/19.
//
//

#include "TheLogin.hpp"
#include "curlNet.hpp"
#include "curl/curl.h"
#include "FirstScene.hpp"
Scene* TheLogin::createScene()
{
    Scene* scene = Scene::create();
    Layer* layer = TheLogin::create();
    scene->addChild(layer);
    return scene;
}
bool TheLogin::init()
{
    if (!Layer::init()) {
        return false;
    }
    visableSize = Director::getInstance()->getVisibleSize();
    auto rootNode = CSLoader::createNode("login.csb");
    this->addChild(rootNode);
    auto textd1 = rootNode->getChildByName<TextField*>("TextField_1");
    auto textd2 = rootNode->getChildByName<TextField*>("TextField_2");
    auto textd3 = rootNode->getChildByName<TextField*>("TextField_3");
    auto login = rootNode->getChildByName<Button*>("Button_1");
    login->addClickEventListener([=](Ref*sender){
        struct MemoryStruct chunk;
         chunk.memory = (char*)malloc(1);
         chunk.size = 0;
         CURL *curl = curl_easy_init();
         if (curl) {
             curl_easy_setopt(curl,CURLOPT_URL,"http://123.56.50.222:8050/userLogin");
//         const char* postData = "{email:7761135821@qq.com,password:123456,phoneIdentity:17338142267}";
             string str1 = "{email:"+textd1->getString()+",password:"+textd2->getString()+",phoneIdentity:"+textd3->getString()+"}";
             const char * postData = str1.data();
             curl_easy_setopt(curl,CURLOPT_POSTFIELDS,postData);
             curl_easy_setopt(curl,CURLOPT_WRITEDATA,(void*)&chunk);
             curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WritrMemoryCallback);
             CURLcode res = curl_easy_perform(curl);
             curl_easy_cleanup(curl);
             if (!res) {
                 log("%s\n",chunk.memory);
             }else{
                 MessageBox("没有网络","提示");
                 log("error!");
                 log("%d",res);
             }
         }
         {
             Document doc;
             doc.Parse<kParseDefaultFlags>(chunk.memory);
             if (doc.HasParseError()) {
                 log("error");
                 return;
             }
             rapidjson::Value& rstcode = doc["rstcode"];
             if (strcmp("201", rstcode.GetString())==0) {
                 MessageBox(doc["rsttext"].GetString(),"提示");
             }else{
                 MessageBox(doc["rsttext"].GetString(),"提示");
                 auto scene = FirstScene::createScene();
                 auto trans = TransitionCrossFade::create(1,scene);
                 Director::getInstance()->replaceScene(trans);
             }
         }
    });
    auto registered = rootNode->getChildByName<Button*>("Button_2");
    registered->addClickEventListener([=](Ref*sender){
        struct MemoryStruct chunk;
        chunk.memory = (char*)malloc(1);
        chunk.size = 0;
        CURL *curl = curl_easy_init();
        if (curl) {
            string str1 = "http://123.56.50.222:8050/userRegister?email="+textd1->getString()+"&password="+textd2->getString()+"&phoneIdentity="+textd3->getString();
//            curl_easy_setopt(curl,CURLOPT_URL,"http://123.56.50.222:8050/userRegister?email=7761135821@qq.com&password=123456&phoneIdentity=17338142267");
            curl_easy_setopt(curl,CURLOPT_URL,str1.c_str());
            curl_easy_setopt(curl,CURLOPT_WRITEDATA, (void*)&chunk);
            curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WritrMemoryCallback);
            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            if (!res) {
                log("%s\n",chunk.memory);
            }else{
                MessageBox("没有网络","提示");
                log("error!");
                log("%d",res);
            }
         }
         {
             Document doc;
             doc.Parse<kParseDefaultFlags>(chunk.memory);
             if (doc.HasParseError()) {
                 log("error");
                 return;
             }
             rapidjson::Value& rstcode = doc["rstcode"];
             if (strcmp("201", rstcode.GetString())==0) {
                 MessageBox(doc["rsttext"].GetString(),"提示");
             }else{
                 MessageBox(doc["rsttext"].GetString(),"提示");
             }
         }
    });
    return true;
}
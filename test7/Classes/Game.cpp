//
//  Game.cpp
//  sanxiao
//
//  Created by admin on 18/5/24.
//
//

#include "Game.hpp"
#include "GuanQia.hpp"
Layer* Game::create(int chapter,int Step)//重写create，参数为章节数、关卡数
{
    Game* layer = new Game();//new出一个场景
    //如果存在
    if(layer && layer->init(chapter,Step))
    {
        layer->autorelease();//自动释放池
        return layer;//返回图层
    }
    CC_SAFE_DELETE(layer);
    layer = nullptr;
    return nullptr;
}
Scene* Game::createScene(int chapter,int Step)
{
    auto scene = Scene::create();
    auto layer = Game::create(chapter,Step);
    scene->addChild(layer);
    return scene;
}
bool Game::init(int chapter,int Step)
{
    if (!Layer::init())
    {
        return false;
    }
    virableSize = Director::getInstance()->getVisibleSize();
    _chapter = chapter;_Step = Step;
    string str = StringUtils::format("bground%d.png",chapter);
    auto bg = Sprite::create(str);
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(Vec2(0, 0));
    
    auto bg1 = Sprite::create(str);
    bg1->setAnchorPoint(Vec2(0, 0));
    bg1->setPosition(Vec2(0, 0));
    this->addChild(bg);
    auto qipan = Sprite::create("caijian1.png");
    qipan->setAnchorPoint(Vec2(0, 0));
    qipan->setPosition(Vec2(0, 100));
    
    this->addChild(qipan);
    
    ClippingNode* clippingNode = ClippingNode::create();
    this->addChild(clippingNode,102);
    
    
    clippingNode->setAlphaThreshold(0.05f); //设置alpha闸值
    clippingNode->setInverted(true);     //把周围的给裁剪了
    clippingNode->setStencil(qipan);   //设置模板stencil
    clippingNode->addChild(bg1, 1);
    
//    Baoshi * jihe[8][8];
    /*for (int i = 0; i<8; i++)
    {
        for (int j = 0; j<8; j++)
        {
            jihe[i][j] = (Baoshi*)Baoshi::create(i, j);
            jihe[i][j]->setAnchorPoint(Vec2(0, 0));
            jihe[i][j]->setPosition(Vec2(i*40, 100+j*40));
            this->addChild(jihe[i][j],6);
            //            auto kuang = Sprite::create("kuang1.png");
            //            kuang->setAnchorPoint(Vec2(0, 0));
            //            kuang->setPosition(Vec2(i*40, 100+j*40));
            //            this->addChild(kuang,7);
        }
    }
    fun_shanchu();*/

    createBaoshi();//创建宝石
    zhuangtai = false;
    kuang = Sprite::create("kuang1.png");
    kuang->setAnchorPoint(Vec2(0, 0));
    kuang->setVisible(false);
    kuang->setPosition(Vec2(0, 100));
    this->addChild(kuang,8);
    resetButton();
    this->chushihua();
    node1 = CSLoader::createNode("title.csb");
    this->addChild(node1,300);
    score = node1->getChildByName<Text*>("Text_4");
    label = node1->getChildByName<Text*>("Text_2");
    auto MenuBtn = node1->getChildByName<Button*>("Button_1");
    MenuBtn->addClickEventListener([=](Ref*sender){
        this->menu();
    });
    if (_Step == 2) {
        string str = StringUtils::format("%02d",_step);
        label->setString(str);
    }
    sc = 0;
    num = 0;num2 = 60;
    HighScore = _highscore;

    return true;
}
bool Game:: jiancha()
{
    xiugai = false;
    for (int i = 0; i<8; i++){
        for (int j = 0; j<8; j++){
            if (i-1>=0&&(jihe[i][j]->gettype()==jihe[i-1][j]->gettype()&&!shanchu.contains(jihe[i][j]))){
                if (i-2>=0&&(jihe[i][j]->gettype()==jihe[i-2][j]->gettype())){
                    xiugai = true;
                    for (int k = i-3; k>=0; k--){
                        if (jihe[k][j]->gettype()!=jihe[i][j]->gettype()){
                            break;
                        }
                        shanchu.pushBack(jihe[k][j]);
                    }
                    if (!shanchu.contains(jihe[i][j])) {
                        shanchu.pushBack(jihe[i][j]);
                    }
                    if (!shanchu.contains(jihe[i-2][j])) {
                        shanchu.pushBack(jihe[i-1][j]);
                    }
                    if (!shanchu.contains(jihe[i-2][j])) {
                        shanchu.pushBack(jihe[i-2][j]);
                    }
                }
            }
            if (i+1<8&&(jihe[i][j]->gettype()==jihe[i+1][j]->gettype()&&!shanchu.contains(jihe[i][j]))){
                if (i+2<8&&(jihe[i][j]->gettype()==jihe[i+2][j]->gettype())){
                    xiugai = true;
                    for (int k = i+3; k<8; k++){
                        if (jihe[k][j]->gettype()!=jihe[i][j]->gettype()){
                            break;
                        }
                        shanchu.pushBack(jihe[k][j]);
                    }
                    if (!shanchu.contains(jihe[i][j])) {
                        shanchu.pushBack(jihe[i][j]);
                    }
                    if (!shanchu.contains(jihe[i+1][j])) {
                        shanchu.pushBack(jihe[i+1][j]);
                    }
                    if (!shanchu.contains(jihe[i+2][j])) {
                        shanchu.pushBack(jihe[i+2][j]);
                    }
                }
            }
            if (j+1<8&&(jihe[i][j]->gettype()==jihe[i][j+1]->gettype()&&!shanchu.contains(jihe[i][j]))){
                if (j+2<8&&(jihe[i][j]->gettype()==jihe[i][j+2]->gettype())){
                    xiugai = true;
                    for (int k = j+3; k<8; k++){
                        if (jihe[i][k]->gettype()!=jihe[i][j]->gettype()){
                            break;
                        }
                        shanchu.pushBack(jihe[i][k]);
                    }
                    if (!shanchu.contains(jihe[i][j])) {
                        shanchu.pushBack(jihe[i][j]);
                    }
                    if (!shanchu.contains(jihe[i][j+1])) {
                        shanchu.pushBack(jihe[i][j+1]);
                    }
                    if (!shanchu.contains(jihe[i][j+2])) {
                        shanchu.pushBack(jihe[i][j+2]);
                    }

                }
            }
            if (j-1>=0&&(jihe[i][j]->gettype()==jihe[i][j-1]->gettype()&&!shanchu.contains(jihe[i][j]))){
                if (j-2>=0&&(jihe[i][j]->gettype()==jihe[i][j-2]->gettype())){
                    xiugai = true;
                    for (int k = j-3; k>=0; k--){
                        if (jihe[i][k]->gettype()!=jihe[i][j]->gettype()){
                            break;
                        }
                        shanchu.pushBack(jihe[i][k]);
                    }
                    if (!shanchu.contains(jihe[i][j])) {
                        shanchu.pushBack(jihe[i][j]);
                    }
                    if (!shanchu.contains(jihe[i][j-1])) {
                        shanchu.pushBack(jihe[i][j-1]);
                    }
                    if (!shanchu.contains(jihe[i][j-2])) {
                        shanchu.pushBack(jihe[i][j-2]);
                    }
                }
            }
        }
    }
    return xiugai;
}
void Game::fun_shanchu()
{
    jiancha();
    if (xiugai==true){
        int temp = 0;
        for (auto dd :shanchu){
            temp++;
            auto act1 = ScaleBy::create(1, 1.2);
            auto act2 = CallFunc::create([=](){
                cout<<"删除:"<<jihe[dd->getX()][dd->getY()]<<endl;
                 jihe[dd->getX()][dd->getY()]=nullptr;
                 dd->removeFromParentAndCleanup(true);
                sc+=30;
                string s1 = StringUtils::format("%04d",sc);
                score->setString(s1);
                if (sc>=TargetScore) {
                    this->win();
                    parseJSon();
                }
                SimpleAudioEngine::getInstance()->playEffect("crush.ogg");
            });
            Sequence * seq;
            if (temp == shanchu.size()){
                auto act3 = CallFunc::create([=](){
                     buchong();
                });
                seq = Sequence::create(act1,act2,act3, NULL);
            }
            else{
                seq = Sequence::create(act1,act2, NULL);
            }
            dd->runAction(seq);
        }
        shanchu.clear();
    }
}
void Game::fun_shanchu1()
{
    if (xiugai==true){
        int temp = 0;
        for (auto dd :shanchu){
            temp++;
            auto act1 = ScaleBy::create(1, 1.2);
            auto act2 = CallFunc::create([=](){
                cout<<"删除:"<<jihe[dd->getX()][dd->getY()]<<endl;
                 jihe[dd->getX()][dd->getY()]=nullptr;
                 dd->removeFromParentAndCleanup(true);
                sc+=30;
                string s1 = StringUtils::format("%04d",sc);
                score->setString(s1);
                if (sc>=TargetScore) {
                    this->win();
                    parseJSon();
                }
                SimpleAudioEngine::getInstance()->playEffect("crush.ogg");
            });
            Sequence * seq;
            if (temp == shanchu.size()){
                auto act3 = CallFunc::create([=](){
                     buchong();
                    cout<<"补充"<<endl;
                });
                seq = Sequence::create(act1,act2,act3, NULL);
            }
            else{
                seq = Sequence::create(act1,act2, NULL);
            }
            dd->runAction(seq);
        }
        shanchu.clear();
    }
}
void Game::buchong()
{
    auto act1 = CallFunc::create([=](){
        for (int i = 0; i<8; i++){
            int temp = 0;
            for (int j = 0; j<8; j++){
                if (jihe[i][j]!=NULL){//如果容器元素位置不为空
                    tianjia.pushBack(jihe[i][j]);//将元素添加到tianjia容器
                }
            }
            for (int j = 0; j<8; j++){
                if (jihe[i][j]==NULL){//如果容器元素位置为空
                    temp++;
                    auto fangkuai = Baoshi::create(10, 10);
                    fangkuai->setAnchorPoint(Vec2(0, 0));
                    fangkuai->setPosition(Vec2(i*40, 420+40*(temp-1)));
                    this->addChild(fangkuai,6);
                    tianjia.pushBack((Baoshi*)fangkuai);//将元素添加到tianjia容器
                }
            }
            for (int k = 0; k<8; k++){
                int sudu = 500;
                int lucheng = (int)(tianjia.at(k)->getPositionY())-100+k*40;
                auto act = MoveTo::create(lucheng/sudu, Vec2(i*40, 100+k*40));
                tianjia.at(k)->runAction(act);
                jihe[i][k] = tianjia.at(k);
                jihe[i][k]->setY(k);
                jihe[i][k]->setX(i);
            }
            tianjia.clear();
        }
        
    });
    auto da = DelayTime::create(0.1);
    auto act2 = CallFunc::create([=](){
        for (int i = 0; i<8; i++){
            for (int j = 0; j<8; j++){
             cout<<jihe[i][j]->getX()<<" "<<jihe[i][j]->getY()<<" "<<jihe[i][j]<<endl;
            }
        }
        if (xiugai==true){
         fun_shanchu();
        }

    });
    auto seq = Sequence::create(act1,da,act2, NULL);
    this->runAction(seq);
}
void Game::onEnter()
{
    
    Layer::onEnter();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(Game::onTouchCancelled, this);
    if (_Step == 1) {
        this->schedule(schedule_selector(Game::updatetime),1);//调用时间调度器
    }
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}
void Game::onExit()
{
    if (_Step == 1) {
        this->unschedule(schedule_selector(Game::updatetime));
    }

    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    Layer::onExit();
    
}
void Game::resetButton()
{
    auto node = CSLoader::createNode("REset.csb");
    this->addChild(node,320);
    auto btn = node->getChildByName<Button*>("Button_1");
    btn->addClickEventListener([=](Ref*sender){
        for (int i = 0; i<8; i++)
        {
            for (int j = 0; j<8; j++)
            {
                jihe[i][j]->removeFromParentAndCleanup(true);
            }
        }
        this->createBaoshi();
    });
}
void Game::createBaoshi()
{
    for (int i = 0; i<8; i++)
    {
        for (int j = 0; j<8; j++)
        {
            jihe[i][j] = (Baoshi*)Baoshi::create(i, j);
            jihe[i][j]->setAnchorPoint(Vec2(0, 0));
            jihe[i][j]->setPosition(Vec2(i*40, 100+j*40));
            this->addChild(jihe[i][j],6);
            //            auto kuang = Sprite::create("kuang1.png");
            //            kuang->setAnchorPoint(Vec2(0, 0));
            //            kuang->setPosition(Vec2(i*40, 100+j*40));
            //            this->addChild(kuang,7);
        }
    }
    fun_shanchu();
}
void Game::updatetime(float dt)
{
    num = 0;
    if (num == 0) {
        num2--;
        if (num2 == 0) {
            this->unschedule(schedule_selector(Game::updatetime));
            this->lose();
            log("you lose!");
        }
    }
    string str = StringUtils::format("%02d:%02d",num,num2);
    label->setString(str);
}
void Game::updateStep(float dt)
{
    _step--;
    string str2 = StringUtils::format("%02d",_step);
    label->setString(str2);
    sc = sc+50;
    string str = StringUtils::format("%06d",sc);
    score1->setString(str);
    if (HighScore<sc) {
        _highscore = sc;
    }else{
        _highscore = HighScore;
    }
    string str1 = StringUtils::format("%06d",_highscore);
    hinghscore->setString(str1);
    if(_step==0) {
        this->unschedule(schedule_selector(Game::updateStep));
    }
    parseJSon();
}
void Game::win()
{
    if (_Step == 1) {
        this->unschedule(schedule_selector(Game::updatetime));
    }
    this->stopAllActions();
    auto widget = Widget::create();//创建一个widget对象 ，类似于一个层
    widget->setAnchorPoint(Vec2(0, 0));//设置锚点
    widget->setPosition(Vec2(0, 0));//设置位置
    widget->setContentSize(virableSize);//设置覆盖区域
    widget->setTouchEnabled(true);//开启触摸
    widget->setSwallowTouches(true);//吞噬触摸
    this->addChild(widget,30);//添加子类——控件
    node2 = CSLoader::createNode("Win.csb");
    node2->setPosition(Vec2(virableSize.width/2,virableSize.height/2));
    score1 = node2->getChildByName<Text*>("Text_1");
    if (_step>0&&_Step==2) {
        this->schedule(schedule_selector(Game::updateStep),0.3);//调用时间调度器
    }
    if (_Step == 1) {
        score1->setString(score->getString());
    }
    if (_highscore<sc) {
        _highscore = sc;
    }else{
        _highscore = HighScore;
    }
    hinghscore = node2->getChildByName<Text*>("Text_3");//从节点获取最高分字符串
    string str1 = StringUtils::format("%d",_highscore);//字符串包
    hinghscore->setString(str1);//修改字符串
    auto back = node2->getChildByName<Button*>("Button_3");
    back->addClickEventListener([=](Ref*sender){
        auto scene = xuanguan::createScene();
        auto tran = TransitionCrossFade::create(1,scene);
        Director::getInstance()->replaceScene(tran);

    });
    auto close = node2->getChildByName<Button*>("Button_1");
    close->addClickEventListener([=](Ref*sender){
        widget->removeFromParentAndCleanup(true);
    });
    if (_chapter<6) {
        auto continued = node2->getChildByName<Button*>("Button_2");
        continued->addClickEventListener([=](Ref*Sender){
            auto scene = Game::createScene(_chapter+1,_Step);
            auto tran = TransitionCrossFade::create(1,scene);
            Director::getInstance()->replaceScene(tran);
        });
    }
    widget->addChild(node2);
//    parseJSon();
}
void Game::lose()
{
    this->stopAllActions();
    auto widget = Widget::create();//创建一个widget对象 ，类似于一个层
    widget->setAnchorPoint(Vec2(0, 0));//设置锚点
    widget->setPosition(Vec2(0, 0));//设置位置
    widget->setContentSize(virableSize);//设置覆盖区域
    widget->setTouchEnabled(true);//开启触摸
    widget->setSwallowTouches(true);//吞噬触摸
    this->addChild(widget,300);//添加子类——控件
    auto node = CSLoader::createNode("Lose.csb");
    node->setPosition(Vec2(virableSize.width/2,virableSize.height/2));
    widget->addChild(node);
    auto btn1 = node->getChildByName<Button*>("Button_1");
    btn1->addClickEventListener([=](Ref*sender){
        auto scene = Game::createScene(_chapter,_Step);
        auto tran = TransitionCrossFade::create(1,scene);
        Director::getInstance()->replaceScene(tran);
    });
    auto btn2 = node->getChildByName<Button*>("Button_2");
    btn2->addClickEventListener([=](Ref*sender){
        auto scene = xuanguan::createScene();
        auto tran = TransitionCrossFade::create(1,scene);
        Director::getInstance()->replaceScene(tran);
    });
}
void Game::parseJSon()//解析文件——修改
{
    string path = FileUtils::getInstance()->getWritablePath();
    //获取可读写路径下面charpter.json文件内容
    string jsonPath = path+string("charpter1.json");
    //拼接路径
    cout<<jsonPath<<endl;
    string data = FileUtils::getInstance()->getStringFromFile(jsonPath);
    cout<<data<<endl;
    //解析
    Document doc;//定义文件
    if (doc.HasParseError())//如果解析错误
    {
        log("json error!\n");//输出提示
        return;//返回
    }

    doc.Parse<kParseDefaultFlags>(data.c_str());
        //设置下一关开启
    cout<<_chapter<<endl;
    if (_chapter<6) {
        for (int i = 0; i<doc["gameCharpter"].Size();++i) {
//            rapidjson::Value& _case = doc["gameCharpter"][i]["Case"];//获取Case
//            rapidjson::Value& islock = _case[_chapter]["isLock"];//获取关卡状态
//            islock.SetBool(false);
            doc["gameCharpter"][i]["Case"][_chapter]["isLock"].SetBool(false);
            doc["gameCharpter"][i]["Case"][_chapter-1]["HighScore"].SetInt(_highscore);//设置最高分
        }
    }
    //保存
    StringBuffer buffer;//定义字符串缓冲区
    rapidjson::Writer<rapidjson::StringBuffer>writer(buffer);//可写字符串缓冲区
    doc.Accept(writer);//写入数据
    FILE*file = fopen(jsonPath.c_str(), "wb");//打开文件
    if (file) {
        fputs(buffer.GetString(),file);//输出到文件
        fclose(file);//关闭文件
    }

}
void Game::chushihua()//初始化
{
    string path = FileUtils::getInstance()->getWritablePath();
    //获取可读写路径下面charpter.json文件内容
    string jsonPath = path+string("charpter1.json");
    //拼接路径
    string data = FileUtils::getInstance()->getStringFromFile(jsonPath);
    //解析
    Document doc;//定义文件
    doc.Parse<kParseDefaultFlags>(data.c_str());
    for (int i = 0; i<doc["gameCharpter"].Size(); ++i) {
        _highscore = doc["gameCharpter"][i]["Case"][_chapter-1]["HighScore"].GetInt();//获取最高分
        TargetScore = doc["gameCharpter"][i]["Case"][_chapter-1]["score"].GetInt();//获取目标分
        _step = doc["gameCharpter"][i]["Case"][_chapter-1]["count"].GetInt();
    }
}
void Game::menu()
{
    if (_Step == 1) {
        this->unschedule(schedule_selector(Game::updatetime));
    }
    this->stopAllActions();
    auto widget = Widget::create();//创建一个widget对象 ，类似于一个层
    widget->setAnchorPoint(Vec2(0, 0));//设置锚点
    widget->setPosition(Vec2(0, 0));//设置位置
    widget->setContentSize(virableSize);//设置覆盖区域
    widget->setTouchEnabled(true);//开启触摸
    widget->setSwallowTouches(true);//吞噬触摸
    this->addChild(widget,300);//添加子类——控件

    auto menu = CSLoader::createNode("Menu.csb");
    widget->addChild(menu,320);
    auto back = menu->getChildByName<Button*>("Button_3");
    back->addClickEventListener([=](Ref*sender){
        if (_Step == 1) {
            this->schedule(schedule_selector(Game::updatetime),1);//调用时间调度器
        }
        widget->removeFromParentAndCleanup(true);
    });
    auto back1 = menu->getChildByName<Button*>("Button_2");
    back1->addClickEventListener([=](Ref*sender){
        auto scene = xuanguan::createScene();
        auto tran = TransitionCrossFade::create(1,scene);
        Director::getInstance()->replaceScene(tran);
    });
}
bool Game::onTouchBegan(Touch * touch,Event * unused_event){
    if (zhuangtai == false){
        for (int i = 0; i<8; i++){
            for (int j = 0; j<8; j++){
                if (jihe[i][j]->getBoundingBox().containsPoint(touch->getLocation())){
                    kuang->setPosition(jihe[i][j]->getPosition());//设置位置
                    kuang->setVisible(true);//设置可见
                    zhuangtai = true;
                    jiaohuan = jihe[i][j];
                }
            }
        }
    }
    else{
        for (int i = 0; i<8; i++){
            for (int j = 0; j<8; j++){
                if (jihe[i][j]->getBoundingBox().containsPoint(touch->getLocation())){
                    int a,b,c,d;
                    a = jiaohuan->getX();
                    b = jiaohuan->getY();
                    c = jihe[i][j]->getX();
                    d = jihe[i][j]->getY();
                    kuang->setPosition(jihe[i][j]->getPosition());
                    if ((b==d&&(a-c)==1)||(b==d&&(a-c)==-1)||(a==c&&(b-d)==1)||(a==c&&(b-d)==-1)){
                        auto dian1 = jiaohuan->getPosition();
                        auto dian2 = jihe[i][j]->getPosition();
                        auto act1 = CallFunc::create([=](){
                            kuang->setVisible(false);
                            zhuangtai = false;
                            jihe[c][d]->stopAllActions();
                            jihe[a][b]->stopAllActions();
                            jihe[a][b]->setX(c);
                            jihe[a][b]->setY(d);
                            jihe[c][d]->setX(a);
                            jihe[c][d]->setY(b);
                            auto cc = jihe[a][b];
                            jihe[a][b] = jihe[c][d];
                            jihe[c][d] = cc;
                            jiancha();
                            if (xiugai){
                                auto move1 = MoveTo::create(0.5, dian1);
                                auto move2 = MoveTo::create(0.5, dian2);
                                jihe[c][d]->runAction(move2);
                                jihe[a][b]->runAction(move1);
                                if (_Step == 2) {
                                    _step--;
                                    string str = StringUtils::format("%02d",_step);
                                    label->setString(str);
                                    if (_step == 0) {
                                        this->lose();
                                    }
                                }
                            }
                        });
//                        auto act = DelayTime::create(1.2);
                        auto act2 = CallFunc::create([=](){
                            fun_shanchu1();
                            if (xiugai==false){
                                auto cc = jihe[a][b];
                                jihe[a][b] = jihe[c][d];
                                jihe[c][d] = cc;
                                jihe[a][b]->setX(a);
                                jihe[a][b]->setY(b);
                                jihe[c][d]->setX(c);
                                jihe[c][d]->setY(d);
                            }
                        });
                        auto seq1 = Sequence::create(act1,act2, NULL);
                        this->runAction(seq1);
                        jiaohuan = nullptr;
                    }

                }
                else{
                    zhuangtai = false;
                }
            }
        }

    }
    return true;
}
void Game::onTouchMoved(Touch * touch,Event * unused_event)
{
log("touch onTouchMoved\n");
}
void Game::onTouchEnded(Touch * touch,Event * unused_event)
{
    
    log("touch ended\n");
}
void Game::onTouchCancelled(Touch * touch,Event * unused_event)
{
    log("touch cancelled\n");
}

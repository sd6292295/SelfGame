//
//  HPlayer.cpp
//  SelfGame
//
//  Created by 李枫 on 14-6-5.
//
//

#include "HPlayer.h"




//模仿CREATE_FUNC()函数自己创建一个对象
HPlayer* HPlayer::createPlayer(const char * playerName)
{
    HPlayer * player = new HPlayer();
    if (player&&player->create())
    {
        player->autorelease();
        player->playerInit(playerName);//调用playerInit函数
        return player;
    }
    CC_SAFE_DELETE(player);
    return NULL;
}


void HPlayer::playerInit(const char * playerName)
{
    Size size=Director::getInstance()->getWinSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    
    //设置飞船的位置在屏幕下面
    Sprite *ship=Sprite::create(playerName);
    ship->setPosition(Point(origin.x+150,origin.y+120));
    this->addChild(ship,0,ship_Tag);
    
    
    //设置参数(血量,当前血量,分数,无敌时间)
    hpMax=5;
    hp=5;
    score=0;
    strongTime=2*60;//60帧*2--->2秒
    isStrong=false;//初始不是无敌状态，减血后会有一段时间的无敌状态
    
    //添加右下角的血量Sprite
    for (int i=0; i<5; i++)
    {
        Sprite *shipHp=CCSprite::create("icon_hp.png");
        
        //设置每个血量贴图在屏幕的右下角一次排列,并且从右至左tag分别是值为1，2，3，4，5的枚举类型
        shipHp->setPosition(Point(size.width-20-30*i, shipHp->getContentSize().height*0.5));
        
        if (i==0) {
            shipHp->setTag(tag_playerHP1);
        }else if(i==1){
            shipHp->setTag(tag_playerHP2);
        }else if(i==2){
            shipHp->setTag(tag_playerHP3);
        }else if(i==3){
            shipHp->setTag(tag_playerHP4);
        }else if(i==4){
            shipHp->setTag(tag_playerHP5);
        }
        //将每一个血量贴图添加到HWorld层中
        HWorld::getInstance()->addChild(shipHp,10);
    }
    
    
    //添加分数Label
    Label *label=Label::createWithSystemFont("分数:", "Helvetica-Blood" , 24);
    //分数Label在屏幕位置左上方
    label->setPosition(Point(200, size.height-22));
    HWorld::getInstance()->addChild(label,10);
    
    //添加分数结果Label
    string strScore=Convert2String(score);//将score---转化为string类型
                                                  //此处需要的时char*类型，所以使用c_str()进行转换
    Label * scoreLabel=Label::createWithSystemFont(strScore.c_str(), "Helvetica-Blood" , 24);
    scoreLabel->setPosition(Point(260, size.height-22));
    //设置颜色为黄色
    scoreLabel->setColor(Color3B(255, 255, 0));
    HWorld::getInstance()->addChild(scoreLabel,10,scoreLabel_Tag);
    
    
    
    
    
    //添加杀敌Label
    Label *killLabel=Label::createWithSystemFont("杀敌:", "Helvetica-Blood", 24);
    killLabel->setPosition(Point(200, size.height-52));
    HWorld::getInstance()->addChild(killLabel,10);
    
    //杀敌数结果Label
    string strKillCount=Convert2String(killCount);//将score---转化为string类型
    strKillCount+="/100"; //C++中string可以直接拼接
                                                      //此处需要的时char*类型，所以使用c_str()进行转换
    Label *labelKillCount=Label::createWithSystemFont(strKillCount.c_str(), "Helvetica-Blood", 24);
    labelKillCount->setPosition(Point(260, size.height-52));
    //设置为黄色
    labelKillCount->setColor(Color3B(255, 255, 0));
    HWorld::getInstance()->addChild(labelKillCount,10,killLabel_Tag);
    
    
    //创建一个单点触摸监听
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true); //这个方法是指是否要吞噬触摸事件（也可以称之为是否穿透）
    
    listener1->onTouchBegan = [=](Touch* touch, Event* event)
    {
        //1、首先通过getCurrentTarget获取点击到的对象
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        
        //2、调用getLocation将iOS坐标系转换成cocos2d-x坐标系
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        //3、然后调用convertToNodeSpace将上述cocos2d-x坐标系转换成该对象的本地坐标系
        
        //4、通过调用getContentSize获取该对象的大小
        Size s = target->getContentSize();
        
        //5、创建该对象的frameRect
        Rect rect = Rect(0, 0, s.width, s.height);
        
        //6、将该触摸的本地坐标系与frameRect比较，若包含则表明触摸有效返回
        if (rect.containsPoint(locationInNode))
        {
            ///////////表示触摸到该对象，可进行一系列操作///////
            return true;//表示寻找到该对象，并终止场景图事件监听遍历。—向下执行onTouchMoved, onTouchEnded
        }
        return false;//表示本次遍历不是该触摸对象,继续遍历下一个事件监听对象。
    };
    
    listener1->onTouchMoved = [=](Touch* touch, Event* event)
    {
        
        //强制类型转换
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        
        
        Point original = target->getPosition();
        Point destination=touch->getDelta();
        
        target->setPosition(Point(original.x+destination.x,original.y+destination.y));
        
        
        //边界限定
        float leftBorderLimit = target->getTexture()->getContentSize().width * 0.5f;
        float rightBorderLimit = size.width - target->getTexture()->getContentSize().width * 0.5f;
        float lowBorderLimit = target->getTexture()->getContentSize().width * 0.5f;
        float heightBorderLimit = size.height - target->getTexture()->getContentSize().width * 0.5f;

        if (original.x+destination.x<leftBorderLimit||original.x+destination.x>rightBorderLimit)
        {
            target->setPosition(Point(original.x,original.y+destination.y));
        }
        
        if (original.y+destination.y<lowBorderLimit||original.y+destination.y>heightBorderLimit)
        {
            target->setPosition(Point(original.x+destination.x,original.y));
        }
        
        
        
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event)
    {
        
    };
    
    //将触摸事件监听(listener1)加入到对象（ship）一个监听事件不能被添加给两个对象
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, ship);
    
    
    
    
}

void HPlayer::update(float time)
{
    
    
}



//增加分数
void HPlayer::addScore(float _value)
{
    score+=_value;
    string strScore=Convert2String(score);//将int形转换为string类型
    //根据HWorld获取场景中分数标签并且改变他的值
    Label *temp=(Label *)HWorld::getInstance()->getChildByTag(scoreLabel_Tag);
    temp->setString(strScore.c_str());//将string类型转换为char*类型
    
}


//增加杀敌数
void HPlayer::addKillCount(float _value)
{
    killCount+=_value;
    string strKillCount=Convert2String(killCount);
    strKillCount+="/100";
    //获取HWorld中杀敌数标签,并且改变他的值
    Label *temp=(Label *)HWorld::getInstance()->getChildByTag(killLabel_Tag);
    temp->setString(strKillCount.c_str());
    
    
    //当杀敌过百的时候,游戏胜利
    if (killCount>=100)
    {
        //oldScore-----从.plist文件中获取储存的旧分数
        //atoi--->将char*转换为整形
                                                        //根据"user_score"这个KEY来取值，如果没有值，将值设为-1
        int oldScore=atoi(UserDefault::getInstance()->getStringForKey("user_score","-1").c_str());
        
        //  string.c_str()-->string转化为char*
        //atoi(char*）---->char*转化为int
        
        
        
        if (score>oldScore)
        {                                                 //KEY
            UserDefault::getInstance()->setStringForKey("user_score", Convert2String(score));
            UserDefault::getInstance()->flush(); //必须要写,刷新数据
        }
        

        
        
        //调用胜利界面
        HWorld::getInstance()->winGame();
    }
}





//让主角掉血的方法,分为死亡和非死亡两种情况来分析
void HPlayer::downHp()
{
    //如果还处于无敌状态则不需要掉血
    if (isStrong)
    {
        return;
    }
    
    //如果已经不是无敌状态
    //血量减少1
    hp-=1;
    
    //如果血量少于0,则将主角设置不可见并且设置他已经死亡
    if (hp<=0)
    {
        this->setVisible(false);
        isDead=true;
        //取出旧的分数      //getInstance()获取的是一个.plist文件
        int oldScore=atoi(UserDefault::getInstance()->getStringForKey("user_score","-1").c_str());
        //当有新的分数，就将新的分数保存到数据中,并且要刷新保存
        if (oldScore!=-1&&score>oldScore)
        {
            UserDefault::getInstance()->setStringForKey("user_score", Convert2String(score));
            UserDefault::getInstance()->flush();
        }
        HWorld::getInstance()->lostGame();
    }
    //如果主角还未死亡然后移除相应界面中的血量贴图
    else
    {
        switch (hp)
        {
            case 1:
                HWorld::getInstance()->removeChildByTag(tag_playerHP2, true);
                break;
            case 2:
                HWorld::getInstance()->removeChildByTag(tag_playerHP3, true);
                break;
            case 3:
                HWorld::getInstance()->removeChildByTag(tag_playerHP4, true);
                break;
            case 4:
                HWorld::getInstance()->removeChildByTag(tag_playerHP5, true);
                break;
        }
        
        //减血后会有一段时间的无敌状态
        //将无敌状态开启,并且开启无敌状态的定时器
        isStrong=true;
        strongCount=0;//无敌时间的计数
        
        
        this->schedule(schedule_selector(HPlayer::strongIng));
    }
}


//处理无敌时间的处理函数
void HPlayer::strongIng(float time)//每帧调用一次
{
    strongCount++;//每帧+1
    
    //当无敌状态时间到的时候
    if (strongCount%strongTime==0)
    {
        this->setVisible(true);//设置为可见
        isStrong=false;//取消无敌状态
        this->unschedule(schedule_selector(HPlayer::strongIng));//取消定时器
    }
    else//如果是无敌状态，让他不断的闪烁
    {
        if (strongCount%3==0)
        {
            this->setVisible(false);
        }
        else
        {
            this->setVisible(true);
        }
        
    }
    
}















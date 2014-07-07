//
//  HWorld.cpp
//  SelfGame
//
//  Created by 李枫 on 14-6-5.
//
//

#include "HWorld.h"

static HWorld * worldLayer = nullptr;

HWorld* HWorld::getInstance()
{
    return worldLayer;
    
}


Scene* HWorld::createScene()
{
    
    auto scene = Scene::create();
    
    auto layer = HWorld::create();
    
    scene->addChild(layer);
    
    
    
    return scene;
}



// on "init" you need to initialize your instance
bool HWorld::init()
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    worldLayer=this;
    
    
    //创建返回按钮
    auto goBackItem = MenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(HWorld::goBack, this));
    
	goBackItem->setPosition(Point(origin.x + goBackItem->getContentSize().width/2 ,
                                  visibleSize.height - goBackItem->getContentSize().height/2));
    
    //创建菜单（也是一个Layer）
    auto menu = Menu::create(goBackItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 10);

    
    //创建Map层
    auto mapLayer=HMap::createMap("map.png");
    this->addChild(mapLayer,0,map_s_Tag);
    
    //创建Player层
    auto playerLayer=HPlayer::createPlayer("player.png");
    this->addChild(playerLayer,0,player_s_Tag);

    //会在getTexture（）这里内存报错
//    //获取精灵帧
//    SpriteFrame *bulletFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("p_bullet.png");
//    //生成子弹集合batch
//    SpriteBatchNode *batch = SpriteBatchNode::createWithTexture(bulletFrame->getTexture());
//    //将子弹集合batch添加到world层内
//    this->addChild(batch, 1, GameSceneNodeTagBulletSpriteBatch);
    
//    
//    //生成子弹集合batch
//    SpriteBatchNode *batch = SpriteBatchNode::create("p_bullet.png");
//     //将子弹集合batch添加到world层内
//    this->addChild(batch, 1, GameSceneNodeTagBulletSpriteBatch);
//

    
    
    
    //创建敌人---1秒调用一次
    this->schedule(schedule_selector(HWorld::autoCreateEnemy),1);
    
    //创建子弹---0.3秒调用一次
    this->schedule(schedule_selector(HWorld::autoCreateBuller),0.1);
    
    
    
    return true;
}

void HWorld::goBack(cocos2d::Ref* pSender)
{
    
    Director::getInstance()->replaceScene(HMenu::createScene());
    
}



//游戏胜利场景
void HWorld::winGame()
{
    
    
    Size size = Director::getInstance()->getWinSize();
    
    //创建一个带有颜色的层
    LayerColor *layer = LayerColor::create(Color4B(0, 0, 0, 190),size.width,size.height);
    
    //创建背景图片精灵
    Sprite * sp = Sprite::create("game_win.png");
    sp->setPosition(Point(size.width/2, size.height/2));
    layer->addChild(sp);
    this->addChild(layer,100);
    
    
    //设置菜单项字体
    MenuItemFont::setFontName("Arial");
    //设置菜单项字体大小
    MenuItemFont::setFontSize(26);
    //创建一个只有字体的Menu按钮
    MenuItemFont *item1 = MenuItemFont::create("返回主菜单", CC_CALLBACK_1(HWorld::backMenu, this));
    //菜单选项卡在Menu中的坐标系是以屏幕的中点为原点
    item1->setPosition(Point(0 , -200));
    
    Menu * menu = Menu::create(item1,NULL);
    this->addChild(menu,100);
    
    //游戏暂停
    Director::getInstance()->pause();
    
}



//游戏失败场景
void HWorld::lostGame()
{
    
    
    Size size = Director::getInstance()->getWinSize();
    
    //创建一个带有颜色的层
    LayerColor *layer = LayerColor::create(Color4B(0, 0, 0, 190),size.width,size.height);
    
    //创建背景图片精灵
    Sprite * sp = Sprite::create("game_lost.png");
    sp->setPosition(Point(size.width/2, size.height/2));
    layer->addChild(sp);
    this->addChild(layer,100);
    
    
    //设置菜单项字体
    MenuItemFont::setFontName("Arial");
    //设置菜单项字体大小
    MenuItemFont::setFontSize(26);
    //创建一个只有字体的Menu按钮
    MenuItemFont *item1 = MenuItemFont::create("返回主菜单", CC_CALLBACK_1(HWorld::backMenu, this));
    //菜单选项卡在Menu中的坐标系是以屏幕的中点为原点
    item1->setPosition(Point(0 , -200));
    
    Menu * menu = Menu::create(item1,NULL);
    this->addChild(menu,100);
    
    //游戏暂停
    Director::getInstance()->pause();
    
}




//返回Menu选择菜单
void HWorld::backMenu(Ref* sender)
{
    //停止所有计时器
    this->unscheduleAllSelectors();
    //还原所有计时器, 动作和时间监听
    Director::getInstance()->resume();
    //
    Director::getInstance()->replaceScene(HMenu::createScene());
}



void HWorld::autoCreateEnemy(float time)//创建敌人---1秒调用一次
{
    
    
    
        int random=CCRANDOM_0_1()*10;
        
        int randomType;
        
        const char *name;
        if (random>=0&&random<=2)
        {
            randomType=0;
            name="enemy_bug.png";
        }else if(random>=3&&random<=6)
        {
            randomType=1;
            name="enemy_duck.png";
        }else if(random>=7&&random<=10)
        {
            randomType=2;
            name="enemy_pig.png";
        }
        
        
        
        
        HEnemy *enemy=NULL;//防止循环时再次调用同样的指针
        enemy=HEnemy::createEnemy(name, randomType);//创建一个怪物精灵
        
        arrayEnemy->pushBack(enemy);//将怪物精灵放入数组
        
        this->addChild(enemy);//将怪物精灵添加到world层中
        
    
}


void HWorld::autoCreateBuller(float time)//创建子弹---0.3秒调用一次
{
    //获取飞船坐标
    Point _position=this->getChildByTag(player_s_Tag)->getChildByTag(ship_Tag)->getPosition();

    //创建left子弹精灵
    Hbullet * bulletL = Hbullet::createBullet("p_bullet.png",0.3f, _position,bulletLeft);
    bulletL->setVisible(false);
    this->addChild(bulletL);
    
    
    //创建middle子弹精灵
    Hbullet * bulletM = Hbullet::createBullet("p_bullet.png",0.3f, _position,bulletMiddle);
    bulletM->setVisible(false);
    this->addChild(bulletM);

    
    //创建right子弹精灵
    Hbullet * bulletR = Hbullet::createBullet("p_bullet.png",0.3f, _position,bulletRight);
    bulletR->setVisible(false);
    this->addChild(bulletR);
    
    
}







std::shared_ptr<Vector<Sprite*>> HWorld::getVectorForEnemy()//通过Hworld实例获取arrayEnemy数组
{
    
    return arrayEnemy;
}
















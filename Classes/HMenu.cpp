//
//  HMenu.cpp
//  SelfGame
//
//  Created by 李枫 on 14-6-5.
//
//

#include "HMenu.h"

Scene* HMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    
    // play按钮
    auto playItem = MenuItemImage::create(
                                           "play_nor.png",
                                           "play_pre.png",
                                           CC_CALLBACK_1(HMenu::playTheGame, this));
    
	playItem->setPosition(Point(visibleSize.width*0.5f , visibleSize.height*0.5f));
    
    //score按钮
    auto scoreItem = MenuItemImage::create(
                                          "score_nor.png",
                                          "score_pre.png",
                                          CC_CALLBACK_1(HMenu::scoreIsPressed, this));
    
	scoreItem->setPosition(Point(visibleSize.width*0.5f , visibleSize.height*0.5f-60));

    //about按钮
    auto aboutItem = MenuItemImage::create(
                                           "about_nor.png",
                                           "about_pre.png",
                                           CC_CALLBACK_1(HMenu::aboutIsPressed, this));
    
	aboutItem->setPosition(Point(visibleSize.width*0.5f , visibleSize.height*0.5f-120));

    
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(playItem, scoreItem, aboutItem,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    
    //添加背景精灵
    auto sprite = Sprite::create("menu_bg.png");
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    return true;
}

//进入玩游戏主场景
void HMenu::playTheGame(Ref* pSender)
{
    Director::getInstance()->replaceScene(HWorld::createScene());
    
}

//进入分数显示场景
void HMenu::scoreIsPressed(cocos2d::Ref* pSender)
{
    Director::getInstance()->replaceScene(HScore::createScene());
    
}

//进入关于作者场景
void HMenu::aboutIsPressed(cocos2d::Ref* pSender)
{
    
    Director::getInstance()->replaceScene(HAbout::createScene());
    
}














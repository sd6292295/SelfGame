//
//  HAbout.cpp
//  SelfGame
//
//  Created by 李枫 on 14-6-5.
//
//

#include "HAbout.h"
USING_NS_CC;

Scene* HAbout::createScene()
{
    
    auto scene = Scene::create();
    
    
    auto layer = HAbout::create();
    
    
    scene->addChild(layer);
    
    
    return scene;
}


bool HAbout::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto goBackItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HAbout::goBack, this));
    
	goBackItem->setPosition(Point(origin.x + goBackItem->getContentSize().width/2 ,
                                 visibleSize.height - goBackItem->getContentSize().height/2));
    
    
    auto menu = Menu::create(goBackItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    
    auto sprite = Sprite::create("about_bg.png");
    
    
    sprite->setPosition(Point(visibleSize.width/2 , visibleSize.height/2 ));
    
    
    this->addChild(sprite, 0);
    
    return true;
}


void HAbout::goBack(Ref* pSender)
{
    //翻页切换
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, HMenu::createScene(), true));
    
}

//
//  HScore.cpp
//  SelfGame
//
//  Created by 李枫 on 14-6-5.
//
//

#include "HScore.h"


USING_NS_CC;

Scene* HScore::createScene()
{
    
    auto scene = Scene::create();
    
    
    auto layer = HScore::create();
    
    
    scene->addChild(layer);
    
    
    return scene;
}


bool HScore::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    //返回主菜单按钮
    auto goBackItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HScore::goBack, this));
    
	goBackItem->setPosition(Point(origin.x + goBackItem->getContentSize().width/2 ,
                                 visibleSize.height - goBackItem->getContentSize().height/2));
    
    
    auto menu = Menu::create(goBackItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 10);
    
    //背景图片
    auto sprite = Sprite::create("score_bg.png");
    sprite->setPosition(Point(visibleSize.width/2, visibleSize.height/2 ));
    this->addChild(sprite, 0);
    
    
    
    //添加一个文本(获取存储的积分)
    std::string scoreStr="";
    //获取存储的积分
    std::string score =UserDefault::getInstance()->getStringForKey("user_score","-1");
    //判断当前是否有最高分的记录
    if(atoi(score.c_str())!=-1)
    {
        //如有有最高分的记录
        scoreStr+=score;
    }
    else
    {
        scoreStr="0";
    }
    //将分数以Lable添加到layer并显示出来
    Label* ttfAbout = Label::createWithSystemFont(scoreStr.c_str(), "Helvetica", 23);
    ttfAbout->setPosition(Point(visibleSize.width*0.5-50,visibleSize.height*0.5+40));
    ttfAbout->setColor(Color3B(255, 0, 0));
    addChild(ttfAbout);

    
    
    
    
    
    return true;
}


void HScore::goBack(Ref* pSender)
{

    //翻页切换
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, HMenu::createScene(), true));


}

//
//  HMenu.h
//  SelfGame
//
//  Created by 李枫 on 14-6-5.
//
//

#ifndef __SelfGame__HMenu__
#define __SelfGame__HMenu__

#include "cocos2d.h"
#include "HWorld.h"
#include "HScore.h"
#include "HAbout.h"


USING_NS_CC;
class HMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    //menuCallBack
    void playTheGame(cocos2d::Ref* pSender);//开始游戏
    
    void scoreIsPressed(cocos2d::Ref* pSender);//分数显示
    
    void aboutIsPressed(cocos2d::Ref* pSender);//关于作者
    
    // implement the "static create()" method manually
    CREATE_FUNC(HMenu);
};

#endif /* defined(__SelfGame__HMenu__) */

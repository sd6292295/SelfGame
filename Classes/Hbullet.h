//
//  Hbullet.h
//  SelfGame
//
//  Created by 李枫 on 14-6-6.
//
//

#ifndef __SelfGame__Hbullet__
#define __SelfGame__Hbullet__

#include <iostream>
#include "cocos2d.h"
#include "HWorld.h"
#include "HPlayer.h"

#include <SimpleAudioEngine.h>

USING_NS_CC;


typedef enum
{
    bulletLeft,
    bulletMiddle,
    bulletRight,
    
}bulletTag;


class Hbullet:public Sprite
{
public:
    //创建bullet精灵
    static Hbullet* createBullet(const char *_fileName, float _speed , Point _position ,bulletTag type);
    
private:
    
    void bulletInit(float _speed,Point _position,bulletTag type);//子弹初始化
    
    void update(float time);
    
    float speed;
    
    int bulletType;
    
    void onExit();
    

};
#endif /* defined(__SelfGame__Hbullet__) */

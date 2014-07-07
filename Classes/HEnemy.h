//
//  HEnemy.h
//  SelfGame
//
//  Created by 李枫 on 14-6-6.
//
//

#ifndef __SelfGame__HEnemy__
#define __SelfGame__HEnemy__

#include <iostream>
#include "cocos2d.h"
#include "HWorld.h"


USING_NS_CC;
class HEnemy:public Sprite
{
public:
    //创建Enemy
    static HEnemy* createEnemy(const char *fileName,int _type);
    //怪物的分值
    int scoreValue;
private:
    
    void enemyInit(const char * fileName,int _type);//怪物初始化
    
    void createAnimate(const char *fileName,int allCount);//创建动画
    
    void update(float time);
    
    //是否行动
    bool isActed;//初始默认为false
    
    int type;
};
#endif/* defined(__SelfGame__HEnemy__) */

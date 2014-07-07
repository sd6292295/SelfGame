//
//  HPlayer.h
//  SelfGame
//
//  Created by 李枫 on 14-6-5.
//
//

#ifndef __SelfGame__HPlayer__
#define __SelfGame__HPlayer__

#include <iostream>
#include "cocos2d.h"
#include "HWorld.h"


USING_NS_CC;
using namespace std; //导入C++命名空间

//模板,将任意类型转化成string类型
template <typename T>
string Convert2String(const T &value)
{
    stringstream ss;
    ss<<value;
    return ss.str();
}


typedef enum
{
    ship_Tag,
    tag_playerHP1,tag_playerHP2,tag_playerHP3,tag_playerHP4,tag_playerHP5,
    scoreLabel_Tag,killLabel_Tag,
        
}playerTag;


class HPlayer : public cocos2d::Layer
{
public:
    //创建一个map
    static HPlayer* createPlayer(const char * playerName);
    
    //当前血量
    int hp;
    //最大血量
    int hpMax;
    //分数
    int score;
    //杀敌数
    int killCount;
    //判断是否死亡
    bool isDead;
    
    
    //掉血
    void downHp();
    //添加分数
    void addScore(float _value);
    //添加杀敌数
    void addKillCount(float _value);

    
    
    
private:
    //无敌状态的时间
    int strongTime;
    //是否无敌状态
    bool isStrong;
    //无敌时间计数
    int strongCount;
    //无敌状态函数
    void strongIng(float time);
    
    
    void playerInit(const char * playerName);
    
    void update(float time);
};

#endif
 /* defined(__SelfGame__HPlayer__) */

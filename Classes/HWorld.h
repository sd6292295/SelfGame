//
//  HWorld.h
//  SelfGame
//
//  Created by 李枫 on 14-6-5.
//
//

#ifndef __SelfGame__HWorld__
#define __SelfGame__HWorld__

#include <iostream>
#include "cocos2d.h"
#include "HMap.h"
#include "HPlayer.h"
#include "HMenu.h"
#include "HEnemy.h"
#include "Hbullet.h"


USING_NS_CC;

typedef enum
{
    map_s_Tag,
    player_s_Tag,
    enemy_Tag,
    GameSceneNodeTagBulletSpriteBatch,
    boss_Tag,
}worldTag;


class HWorld : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    
    static HWorld* getInstance();//静态函数，获取world实例
    
    virtual bool init();
    
    CREATE_FUNC(HWorld);
    
    
    
    void winGame();
    
    void lostGame();
    
    void goBack(cocos2d::Ref* pSender);
    
    void backMenu(Ref* sender);
    
    void autoCreateEnemy(float time);
    
    void autoCreateBuller(float time);
    
    //Vector<Sprite*>arrayEnemy;//怪物数组，碰撞检测遍历怪物时使用
    std::shared_ptr<Vector<Sprite*>>  arrayEnemy = std::make_shared<Vector<Sprite*>>();
    
    std::shared_ptr<Vector<Sprite*>> getVectorForEnemy();//通过Hworld实例获取arrayEnemy数组
    
    

    
};

#endif /* defined(__SelfGame__HWorld__) */

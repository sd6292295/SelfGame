//
//  Hbullet.cpp
//  SelfGame
//
//  Created by 李枫 on 14-6-6.
//
//

#include "Hbullet.h"
Hbullet* Hbullet::createBullet(const char *_fileName,float _speed,Point _position,bulletTag type)
{
    Hbullet * bullet = new Hbullet();
    
    //从本地文件系统中找到_fileName,Texture2D加载它的内容,然后使用Texture2D创建一个Sprite
    if (bullet && bullet->initWithFile(_fileName))
    {
        bullet->autorelease();
        bullet->bulletInit(_speed, _position,type);//对创建的bullet精灵进行初始化,将长条图片转化为动画帧
        return bullet;
    }
    
    
    CC_SAFE_DELETE(bullet);
    

    
    
    return NULL;
}


void Hbullet::bulletInit(float _speed,Point _position,bulletTag type)
{
    
    speed=_speed;
    this->bulletType=type;
    this->setPosition(_position);
    this->setVisible(false);//起始时，子弹为隐藏状态
    this->unscheduleUpdate();//先停止所有的计时器，以免产生异常
    this->scheduleUpdate();
    
    
    
}


//碰撞检测
void Hbullet::update(float time)
{
    switch (this->bulletType)
    {
        case 0:
        {
            //不断的改变子弹的位置(当前坐标+子弹的速度)
            this->setPosition(this->getPosition() + Point(-speed*500*time*0.5, speed*500*time));
            break;
        }
            
        case 1:
        {
            //不断的改变子弹的位置(当前坐标+子弹的速度)
            this->setPosition(this->getPosition() + Point(0, speed*500*time));
            break;
        }
           
        case 2:
        {
            //不断的改变子弹的位置(当前坐标+子弹的速度)
            this->setPosition(this->getPosition() + Point(speed*500*time*0.5, speed*500*time));
            break;
        }
        default:
            break;
    }
    
    this->setVisible(true);
    
    
    
    
    //获取敌人对象数组
    std::shared_ptr<Vector<Sprite*>> enemyArray=HWorld::getInstance()->getVectorForEnemy();
    //依次的遍历敌人进行碰撞检测
    for (int i=0; i<enemyArray->size(); i++)
    {
        
        
        
        
        
        //获取一个敌人对象
        HEnemy *enemy=(HEnemy *)enemyArray->at(i);
        //如果两个有碰撞
        if (enemy->getBoundingBox().intersectsRect(this->getBoundingBox()))
        {
            //调用击中音效
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("effect_boom.mp3");
            
            //播放击中的爆破效果----粒子效果
            ParticleSystemQuad *particle=ParticleSystemQuad::create("particle_boom.plist");
            particle->setPosition(enemy->getPosition());
            //将爆破效果执行结束后移除
            particle->setAutoRemoveOnFinish(true);
            //将爆破效果添加到主场景中
            HWorld::getInstance()->addChild(particle);
            
            //调用主场景中获取主角的方法并调用他的addScore方法和addKillCount方法
            HPlayer* playerLayer =(HPlayer*) HWorld::getInstance()->getChildByTag(player_s_Tag);
            playerLayer->addScore(enemy->scoreValue);
            playerLayer->addKillCount(1);
            
            //从数组中移除掉当前的敌人
            enemyArray->eraseObject(enemy);
            
            //从界面中移除敌人精灵
            HWorld::getInstance()->removeChild(enemy, true);
            
            //移除当前的bullet精灵
            HWorld::getInstance()->removeChild(this, true);
            
            break;
        }
    }
    
    
}

//退出的时候将子弹的Update方法取消
void Hbullet::onExit()//------->当节点被移除时使用
{
    
   this->unscheduleUpdate();
    //注意要调用父类的退出方法
    Sprite::onExit();
    
}
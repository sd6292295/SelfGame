//
//  HEnemy.cpp
//  SelfGame
//
//  Created by 李枫 on 14-6-6.
//
//

#include "HEnemy.h"


//创建Enemy精灵
HEnemy* HEnemy::createEnemy(const char *fileName, int _type)
{
    HEnemy * enemy = new HEnemy();
    
    //从本地文件系统中找到fileName,Texture2D加载它的内容,然后使用Texture2D创建一个Sprite
    if (enemy && enemy->initWithFile(fileName))
    {
        enemy->autorelease();
        enemy->enemyInit(fileName, _type);//对创建的enemy精灵进行初始化,并调用createAnimate方法将长条图片转化为动画帧
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return NULL;
}



//初始化
void HEnemy::enemyInit(const char *fileName, int _type)
{
    
    type = _type;
                         //allCount==10
    createAnimate(fileName, 10);//调用创建动画函数
    
    Size size = Director::getInstance()->getWinSize();
    
    if (_type == 0) {
        scoreValue = 198;
    }
    else if(_type == 1)
    {
        scoreValue = 428;
    }
    else if(_type == 2)
    {
        scoreValue = 908;
    }
    
    
    //X在屏幕内随机位置
    this->setPosition(Point(CCRANDOM_0_1()*size.width, size.height+this->getContentSize().height));
    
    //敌人移动逻辑
    this->scheduleUpdate();
}



//三种不同的移动逻辑
void HEnemy::update(float time)
{
    HPlayer *playerlayer=(HPlayer*)HWorld::getInstance()->getChildByTag(player_s_Tag);//获取player层
    
    Sprite *ship=(Sprite*)playerlayer->getChildByTag(ship_Tag);//获取飞船精灵
    
    switch (type)//根据不同的怪物精灵类型，有不同的下落方式（怪物AI）
    {
        case 0:
        {
            this->setPosition(this->getPosition()+Point(0,-3));
            break;
        }
        case 1:
        case 2:
        {
            if (isActed)//初始为false,一旦开始移动就为true
            {
                break;
            }
            isActed = true;
            
            FiniteTimeAction *moveto = MoveTo::create(1.6, ship->getPosition());
            
            FiniteTimeAction *wait = DelayTime::create(1.0);
            
            FiniteTimeAction *moveGO=MoveTo::create(1, Point(200,-this->getContentSize().height));
            
            Sequence *sequence=Sequence::create(moveto , wait, moveGO,NULL);
            
            this->runAction(sequence);
            
            break;
        }
    }
    
    
    if (this->getPositionY()<= -this->getContentSize().height)
    {
                            //获取怪物数组            //将这个怪物精灵从数组中移除
        HWorld::getInstance()->getVectorForEnemy()->eraseObject(this);
        
        this->getParent()->removeChild(this,true);//将怪物精灵从父节点中移除，并同时停止动作
    }
    
    

    
    if (!playerlayer->isDead)//调用playerlayer内的数据成员
    {
        if (ship->boundingBox().intersectsRect(this->boundingBox()))
        {
            playerlayer->downHp();
        }
    }
}

//创建动画
void HEnemy::createAnimate(const char *fileName, int allCount)
{
    Animation *animation = Animation::create();//创建一个动画
    
    //向Texture缓存中加入一张图片
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(fileName);
    
    int eachwidth = this->getContentSize().width/allCount;//每张图片的宽
    
    //遍历长条图片并进行切割
    for (int i = 0; i<allCount; i++)
    {
        //使用长条图片来创建动画帧
        animation->addSpriteFrameWithTexture(texture, Rect(i*eachwidth, 0, eachwidth, this->getContentSize().height));
    }
    animation->setDelayPerUnit(0.03f);//动画帧间隔
    
    animation->setRestoreOriginalFrame(true);//动画结束后是否回到第一帧（第一张图片）,不写这个方法则显示最后一张
    
    animation->setLoops(-1);//重复次数（-1无线循环）
    
    FiniteTimeAction *animate = Animate::create(animation);//通过动画帧来创建一个动画
    
    this->runAction(animate);//由怪物精灵来运行动画
}
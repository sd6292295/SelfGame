//
//  HMap.cpp
//  SelfGame
//
//  Created by 李枫 on 14-6-5.
//
//

#include "HMap.h"
USING_NS_CC;


//模仿CREATE_FUNC()函数自己创建一个对象
HMap* HMap::createMap(const char * fileName)
{
    HMap * map = new HMap();
    if (map&&map->create())
    {
        map->autorelease();
        map->mapInit(fileName);//调用mapInit函数
        return map;
    }
    CC_SAFE_DELETE(map);
    return NULL;
}

// on "init" you need to initialize your instance
void HMap::mapInit(const char * fileName)
{
    
    
    
    //setPosition-->获得的时精灵锚点所在的位置
    Sprite *map1=Sprite::create(fileName);
    map1->setPosition(Point(map1->getContentSize().width*0.5f,map1->getContentSize().height*0.5f));
    this->addChild(map1,0,map_TagOne);
    
    Sprite *map2=Sprite::create(fileName);
    map2->setPosition(Point(map1->getContentSize().width*0.5f,map1->getContentSize().height*1.5f));
    this->addChild(map2,0,map_TagTwo);
    
    this->scheduleUpdate();
    
    
   
    
}


void HMap::update(float time)
{
    Sprite *map1=static_cast<Sprite *>(this->getChildByTag(map_TagOne));
    
    //如果第一张背景图的中点到达屏幕下方背景图高度的一半的时候(也就是第一张图片移动到屏幕下面的时候)
    //重新设置他的位置到屏幕上面，图片下边缘跟手机屏幕上边缘重合-1个像素
    if (map1->getPosition().y<=-map1->getContentSize().height*0.5f)//0.5~-0.5正好是一张图片的长度,0是图片的一半
    {
        map1->setPosition(Point(map1->getContentSize().width*0.5f,map1->getContentSize().height*1.5f-1));
    }
    else//如果第二张背景图移出屏幕最下方则重新设置他的位置在屏幕的最上方
    {
        map1->setPosition(Point(map1->getPosition().x,map1->getPosition().y-1));
    }
    
    
    
    Sprite *map2=static_cast<Sprite *>(this->getChildByTag(map_TagTwo));
    
    if (map2->getPosition().y<=-map2->getContentSize().height*0.5f)
    {
        map2->setPosition(Point(map2->getContentSize().width*0.5f,map2->getContentSize().height*1.5f-1));
    }
    else//如果第二张背景图移出屏幕最下方则重新设置他的位置在屏幕的最上方
    {
        map2->setPosition(Point(map2->getPosition().x,map2->getPosition().y-1));
    }
    
    
}


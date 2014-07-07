//
//  HMap.h
//  SelfGame
//
//  Created by 李枫 on 14-6-5.
//
//

#ifndef __SelfGame__HMap__
#define __SelfGame__HMap__

#include "cocos2d.h"

typedef enum
{
    map_TagOne,
    map_TagTwo,
    
}mapTag;


class HMap : public cocos2d::Layer
{
public:
    //创建一个map
    static HMap* createMap(const char * fileName);
    
    
    
private:
    void mapInit(const char * fileName);
    
    void update(float time);
};

#endif  /* defined(__SelfGame__HMap__) */

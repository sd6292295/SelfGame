//
//  HScore.h
//  SelfGame
//
//  Created by 李枫 on 14-6-5.
//
//

#ifndef __SelfGame__HScore__
#define __SelfGame__HScore__

#include <iostream>
#include "cocos2d.h"
#include "HMenu.h"

class HScore : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    
    virtual bool init();
    
    
    void goBack(cocos2d::Ref* pSender);
    
    
    CREATE_FUNC(HScore);
};


#endif /* defined(__SelfGame__HScore__) */

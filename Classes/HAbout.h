//
//  HAbout.h
//  SelfGame
//
//  Created by 李枫 on 14-6-5.
//
//

#ifndef __SelfGame__HAbout__
#define __SelfGame__HAbout__

#include <iostream>
#include "cocos2d.h"
#include "HMenu.h"

class HAbout : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    
    virtual bool init();
    
    
    void goBack(cocos2d::Ref* pSender);
    
    
    CREATE_FUNC(HAbout);
};


#endif /* defined(__SelfGame__HAbout__) */

//
//  AnimationManager.h
//  CatDressUp
//
//  Created by LiXiaofei on 2017/6/11.
//
//

#ifndef AnimationManager_h
#define AnimationManager_h

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class AnimationManager : public CCObject {
    
public:
    static AnimationManager* sharedManager();
    
    AnimationManager();
    virtual ~AnimationManager();
    
    
};

#endif /* AnimationManager_h */

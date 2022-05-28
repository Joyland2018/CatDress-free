//
//  AnimationManager.cpp
//  CatDressUp
//
//  Created by LiXiaofei on 2017/6/11.
//
//

#include "AnimationManager.h"

static AnimationManager* _sharedManager;

AnimationManager* AnimationManager::sharedManager(){
    if (!_sharedManager) {
        _sharedManager = new AnimationManager();
        _sharedManager->autorelease();
    }
    
    return _sharedManager;
}

AnimationManager::AnimationManager(){
    
}

AnimationManager::~AnimationManager(){
    
}


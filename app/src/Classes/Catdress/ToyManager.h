//
//  ToyManager.h
//  CatDressUp
//
//  Created by LiXiaofei on 2017/6/12.
//
//

#ifndef ToyManager_h
#define ToyManager_h

#include <stdio.h>
#include "cocos2d.h"
#include "CatDressManager.h"
#include "GameManager.h"

using namespace cocos2d;

class ToyManager : public CCObject {
    
public:
    static ToyManager* sharedManager();
    
    ToyManager();
    virtual ~ToyManager();
    
    CCSprite* getSpiderToy();
    
    void showToyAnim(int _toyIndex,CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    void spiderAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    void watergunAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    
    void foldLineAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    
    void scaleAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    void spaceshipAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    
    void anyCarAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    
    void shieldAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    
    void flyAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    
    void rotateFlyAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    
    void rotateAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    
    void fanAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    
    void jumpAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    
    void rockAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    
    void updownAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    
    void dragonAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    
    void rocketAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback);
    
};

#endif /* ToyManager_h */

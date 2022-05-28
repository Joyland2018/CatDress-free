//
//  BeginScene.h
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-4.
//
//

#ifndef CatDressUp_BeginScene_h
#define CatDressUp_BeginScene_h

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
//#include "SelectScene.h"
//#include "DeviceManager.h"
#include "GameManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

class BeginScene : public CCLayer{
public:
    static CCScene* scene();
    virtual bool init();
    
    BeginScene();
    ~BeginScene();
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
//    virtual bool touchGame(CCPoint touchLocation);
    void touchStar(CCSprite* _sprite);
    void revertStar(CCNode* sender,int _tag);
    
    void createParentsLock(cocos2d::CCObject *sender);
    void parentsLockCallback(cocos2d::CCObject *sender);
    
    CREATE_FUNC(BeginScene);
public:
    CCSprite* touchSprite;
    CCDictionary* starInfo;
    CCSprite *bt_wordblock;
    CCSprite *bt_wordbreak;
    CCSprite *bt_shapepuzzle;
    CCSprite *bt_firstword;
    CCSprite *bt_background;
    CCSprite *bt_Jorland;
    CCSprite *bt_Match;
    CCSprite *bt_ad;
    
    int locknum[3];
    int accessnum[3];
    int accessIndex;
    
    int moreGameTag;
};

#endif

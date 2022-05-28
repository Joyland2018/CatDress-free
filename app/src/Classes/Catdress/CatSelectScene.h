//
//  CatSelectScene.h
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-4.
//
//

#ifndef CatDressUp_CatSelectScene_h
#define CatDressUp_CatSelectScene_h

#include "cocos2d.h"
#include "BathScene.h"
#include "ClipScene.h"
#include "DressScene.h"
#include "CatDressManager.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "BuyLayer.h"
#else
//#include "BuyPage.h"
#endif
#include "GameManager.h"
//#include "LandScene.h"
//#include "ShiningScene.h"
//#include "SimpleAudioEngine.h"

using namespace cocos2d;
//using namespace CocosDenshion;

class CatSelectScene : public CCLayer,CCScrollViewDelegate{
public:
    static CCScene* sceneWithID(int _catID);
    static CatSelectScene* nodeWithID(int _animalID);
    bool initWithID(int _animalID);
    
    CatSelectScene();
    ~CatSelectScene();
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view);
    
    void adjustScrollView();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    void showGameMenu();
    void removeGameMenu();
    void removeSprite(CCNode* sender);
    void isTouchMenu(CCNode* sender);
    void goHome();
    void warningGameMenu();
    void addLock(CCSprite* item,CCSize itemSize);
    void goInStore();
    void resetTouchScroll();
    void showMenuAnim(CCNode* sender,int _tag);
    void goToShowInterstitial();

    void clickBuy();
public:
    CCScrollView* scrollView;
    int _curCatTag;
    bool isTouchHome;
    bool isCanSelCat;
    CCSprite* touchSprite;


    double scrollInitX;
    
private:
    CCSprite *bt_wordblock;
    CCSprite *bt_wordbreak;
    CCSprite *bt_shapepuzzle;
    CCSprite *bt_firstword;
    CCSprite *bt_background;
    CCSprite *bt_Jorland;
    CCSprite *bt_Match;
    CCSprite *bt_ad;

    int select;
    void openIAPPage();
    
    void showIAPPage(int _index);
    
    void checkIAP();
};


#endif

//
//  BathScene.h
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-3.
//
//

#ifndef CatDressUp_BathScene_h
#define CatDressUp_BathScene_h

#include "cocos2d.h"
#include "CatSelectScene.h"
#include "CatDressManager.h"
//#include "SimpleAudioEngine.h"

using namespace cocos2d;
//using namespace CocosDenshion;

class BathScene : public CCLayer{
public:
    
    static CCScene* sceneWithID(int _catID);
    static BathScene* nodeWithID(int _animalID);
    bool initWithID(int _animalID);
    
    BathScene();
    virtual ~BathScene();

    virtual void onEnter();

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    void touchSwitch(int _tag);
    void completeSwitch(CCNode* sender,int _tag);
    void openSink();
    void openShower();
    void openHairDryer(bool _isTurnOn);
    void touchBottle(int _tag);
    void showBottleWater(CCNode* sender,int _tag);
    void completeBottle(CCNode* sender,int _tag);
    void setAnotherFrame(CCSprite* pSprite, const char* frameName);
    void warningBrush();
    void showBubble();
    void bubbleMove(CCNode* sender,int _tag);
    void removeSelf(CCNode* sender);
    void showBubbleBreak(CCNode* sender);
    void catAnimation(CCTime* dt);
    void catEyeAnim(CCTime* dt);
    void catMouthAnim(CCTime* dt);
    void completedBottleAction(CCNode* sender,int _tag);
    void changeBodyWater(bool isInView);
    void setSpriteVisible(CCNode* sender,int _tag);
    void changeBodyFoam(bool isInView,CCPoint location);
    void setSpriteInitPos(CCNode* sender, int _tag);
    void returnLastScene();
    void brushDirty(CCPoint location);
    void warningBrushSound();
    void showSpraySound();
    void showWaterSound(CCNode* sender,int _tag);
    void showHairDryerSound();
    void clickCatSound();
    void showPoolWaterAnim();
    
    void completeEyeAnim();
    void completeMouthAnim();
    
    void eyeMove(CCPoint location);
    void eyeRevert();


    void goToShowInterstitial();

public:
    CCSprite* touchSprite;
    CCPoint touchSpriteInPos;
    CCPoint brushInPos;
    CCPoint eyeLInPos;
    CCPoint eyeRInPos;
    bool isOpenHot;
    bool isOpenCold;
    bool isRotateHot;
    bool isRotateCold;
    bool isTouchedBath;
    bool isTouchedHair;
    bool isRunBrush;
    bool isCanFoam;
    bool isTouchHome;
    bool isWaterToPool;
    bool isDryer;
    int bubbleTag;
    int catAnimTag;
    int catEyeAnimTag;
    int catMouthAnimTag;
    int eyeRadius;
    int foamMax;
    CCArray* bubbleArray;
    int animalTag;
    int curCatTag;
    int brushNum;
    int brushFoamCount;
    int poolAnimTag;


//    CCArray* foamArray;
};


#endif

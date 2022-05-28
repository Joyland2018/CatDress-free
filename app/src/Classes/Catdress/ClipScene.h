//
//  ClipScene.h
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-4.
//
//

#ifndef CatDressUp_ClipScene_h
#define CatDressUp_ClipScene_h

#include "cocos2d.h"
#include "CatDressManager.h"
#include "GameManager.h"
#include "DrawSprite.h"
//#include "CatSelectScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class ClipScene : public CCLayer,CCScrollViewDelegate{
public:
    static CCScene* sceneWithID(int _catID);
    static ClipScene* nodeWithID(int _animalID);
    bool initWithID(int _animalID);
//    virtual bool init();
//    static cocos2d::CCScene* scene();
    CREATE_FUNC(ClipScene) ;//启动并初始化HospitalScene 这个类

    ClipScene();
    ~ClipScene();
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view);
    
    void adjustScrollView();
    
    void clearItem(CCPoint location,int itemTag);
    void removeSelf(CCNode* sender);
    void setNewTexture(CCTime* dt);
    void setAnotherFrame(CCSprite* _sprite, const char* frameName);
    void brushNail(CCSprite* _sprite, CCPoint location);
    void setNailFlower(CCPoint location,int _tag,int _viewTag);
    void moveLayer();
    void reverseScrollView();
    void returnLastScene();
    void warningItem(int itemTag);
    void setItemVisible(CCNode* sender);
    void cleanFlower();
    void cleanPolish();

    void goToShowInterstitial();

    CCSize winsize;
    CCPoint poszero;
    CCTexture2D* maskedWithSpriteTexture(CCSprite* texturesp, CCSprite* masksp,CCPoint location);
    CCTexture2D* anotherMaskedWithSpriteTexture(CCSprite* texturesp,CCSprite* masksp,CCPoint texturePos,CCPoint maskPos);
    
//    CREATE_FUNC(ClipScene);
public:
    CCScrollView* scrollView;
    CCSprite* touchSprite;
    CCPoint touchSpriteInPos;
    CCPoint forcepsInPos;
    CCPoint nailInPos;
    int thornNum;
    int pawNum;
    int nailPolishNum;
    int collisionAreaNum;
    int flowerColNum;
    int touchNailPolishTag;
    int touchNailFlowerTag;
    int thornCount;
    int pawCount;
    int curCatID;
    int colPointTag;
    int curLayerTag;
    bool isCutting;
    bool isTouchHome;
    bool isPlayPolishSound;
    CCDictionary* nailPolishInfo;
    CCRenderTexture* rendertexture;

//    bool isRecording;
};

#endif

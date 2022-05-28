//
//  DressScene.h
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-4.
//
//

#ifndef CatDressUp_DressScene_h
#define CatDressUp_DressScene_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameManager.h"
#include "CatDressManager.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "DeviceManager.h"
#else
#endif
#include "CatSelectScene.h"
#include "SimpleAudioEngine.h"
#include "ToyManager.h"

using namespace cocos2d;
using namespace extension;
using namespace CocosDenshion;

class DressScene : public CCLayer,CCBSelectorResolver,CCNodeLoaderListener,public CCScrollViewDelegate{
public:
    static cocos2d::CCScene* sceneWithID(int _catID);
    static DressScene* nodeWithID(int _catID);
    bool initWithID(int _catID);
    
    DressScene();
    ~DressScene();
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view);
    
    virtual void onEnter();
    virtual void onExit();
    
    void catAnimation(CCTime* dt);
    void catEyeAnim(CCTime* dt);
    void catMouthAnim(CCTime* dt);
    
    void completeEyeAnim();
    void completeMouthAnim();
    
    void eyeMove(CCPoint location);
    void eyeRevert();
    
    void onClotheClick(CCObject* pSender);
    void onHatClick(CCObject* pSender);
    void onShoesClick(CCObject* pSender);
    void onNecklaceClick(CCObject* pSender);
    void onGlassesClick(CCObject* pSender);
    void onToyClick(CCObject* pSender);
    void onSetClick(CCObject* pSender);
    void onCleanClick(CCObject* pSender);
    
    void showChest(int selectTag,const char *pFileName,CCObject* pSender);
    void showItemScroll(const char *pFileName,CCSize scrollSize,CCPoint scrollPos,CCSprite* pLayer,int itemNum);
    void wearItem(int selectTag,CCPoint selItemPos,bool isGoMove);
    void wearSet(int tag);
    void wearItemInSet(int tag, const char *pSelType);
    void setSprColor(int tag,const char* pSelType,bool isWeared);
    void moveItem(cocos2d::CCSprite *moveSpr,CCPoint toPos,const char* fileName);
    void completeMove(CCSprite* moveSpr);
    void showStandbyAnim();
    void removeStandbyAnim();
    void teachPlayToy(cocos2d::CCTime *dt);
    void teachAnimation(cocos2d::CCPoint sprPoint);
    void teachChangeVisible();
    void teachChangeFrame();
    void teachAnotherFrame();
    void showTeachCircle();
    void removeTeachHand();
    void catStandbySound(cocos2d::CCTime *dt);
    void animalAnimation(cocos2d::CCTime *dt);
    void completeToyAnim();
    void showCCBToyAnim();
    void setParticle();
    CCImage* getRenderUImage(CCSprite* picLayer);
    void completedMenuAnim();
    void setMenuBtnInVis();
    void touchMenuBtn(cocos2d::CCPoint location);
    void goInStore(int tag);
    void selectMenuBtn(int btnTag);
    void returnLastScene();
    void goScreenShot();
    void removeFlash();
    void controlSound();
    void clickCatSound();
    void removeItemSpr(int tag);
    void removeAllItem();
    void removeSprite();
    void isTouchBtn();
    void addLock(CCSprite* item,CCSize itemSize);
    
    void changeBg(int _tag);
    void goCamera(CCImage* picLayer);
    void goRecord();
    void beginRecord(float dt);
    void setAnotherFrame(CCSprite* pSprite,const char* pFileName);
    CCString* getItemType(int tag);
    
    void runMenuAnim(bool _isReverse);

    void goToShowInterstitial();

public:
    CCPoint eyeLInPos;
    CCPoint eyeRInPos;
    CCPoint toyInPos;
    float eyeRadius;
    bool isCanTouchMenu;
    bool isShowSysMenu;
    bool isRecording;
    int animRandom;

    double scrollInitY;
private:
    void openIAPPage();
    
    void showIAPPage(int _index);
    
    void checkIAP();
    
};


#endif

#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "LogoScene.h"
//#include "HospitalScene.h"
//#include "ShapePuzzleScene.h"
//#include "ShapePuzzleManager.h"
//#include "MatchScene.h"
//#include "GameInf.h"
//#include "SpellWordsScene.h"
//#include "SpellWordsInf.h"
//#include "LandScene.h"
//#include "JigsawPuzzleScene.h"
//#include "TrainScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "DeviceManager.h"
#endif
#include "GameManager.h"                         //#include "HospitalScene.h" //#include "TestScene.h"
//#include "TestScene.h"Scene.h
#include "LogoScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    //CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1136, 640, kResolutionExactFit);
    pDirector->setOpenGLView(pEGLView);

    CCLOG("width = %f,height = %f",CCEGLView::sharedOpenGLView()->getVisibleSize().width,CCEGLView::sharedOpenGLView()->getVisibleSize().height);
    float with = CCEGLView::sharedOpenGLView()->getVisibleSize().width ;
    float  hight =CCEGLView::sharedOpenGLView()->getVisibleSize().height ;
    if ((with/hight) >=2.0) {
        GameManager::sharedManager()->isiphoneX = true;
    }

    if ((with/hight) < 1.4) {
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1136, 640, kResolutionNoBorder);
    }else{
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1136, 640, kResolutionFixedHeight);
    }
    
  //  CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1136, 640, kResolutionNoBorder);
    
//    ShapePuzzleManager::shareGameManger()->setSceneIndex(6) ;
//    ShapePuzzleManager::shareGameManger()->setSceneIndex(6) ;
    
//    GameInf::initGameInf();
    
//    SpellWordsInf::initSpellInf();
    
   GameManager::sharedManager()->initGameSystem();
    GameManager::sharedManager()->requestInitAds();
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCUserDefault::sharedUserDefault()->setBoolForKey("isBegin", true);

    // create a scene. it's an autorelease object
//    CCScene *pScene = HelloWorld::scene();
//    CCScene *pScene = ShapePuzzleScene::scene();
//    CCScene *pScene = MatchScene::scene();
//    CCScene *pScene = SpellWordsScene::scene();
//    CCScene *pScene = LandScene::scene();
//    CCScene *pScene = JigsawPuzzleScene::scene("jigsawpuzzle/puzzleimage/Animal_Hd_01.png",2);
//    CCScene *pScene = TrainScene::sceneWithId(1);
//    CCScene *pScene = SecondScene::scene(); //   CCScene *pScene = LogoScene::scene();
  CCScene *pScene = LogoScene::scene();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    DeviceManager::sharedManager()->shareMixpanel();
    DeviceManager::sharedManager()->uploadiAdInfo();
#endif

    // run
 pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        CCUserDefault::sharedUserDefault()->setBoolForKey("isPauseBM", true);
    }
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    CCDirector::sharedDirector()->pause();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    if (CCUserDefault::sharedUserDefault()->getBoolForKey("isPauseBM")) {
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        CCUserDefault::sharedUserDefault()->setBoolForKey("isPauseBM", false);
    }
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    CCDirector::sharedDirector()->resume();
    
//    GameManager::sharedManager()->setLastTime();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

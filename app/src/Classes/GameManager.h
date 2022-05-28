//
//  GameManager.h
//  GameGarden
//
//  Created by LiXiaofei on 2017/2/4.
//
//

#ifndef GameManager_h
#define GameManager_h

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

//typedef enum GameType {
//    kTimeTag = 14,
//    kMathTag = 10,
//    kNumbersTag = 1,
//    kCircusTag = 0,
//    kShapePuzzleTag = 5,
//    kJigsawPuzzleTag = 9,
//    kMatchTag = 3,
//    kSpellWordsTag = 12,
//    kAnimalTag = 7,
//    kHospitalTag = 2,
//    kCoinTag = 6,
//    kUnitedStatesTag = 8,
//    kCatDressTag = 4,
//    kWordFamilyTag = 13,
//    kWorldTag = 11,
//} gameType;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
typedef enum GameType {
    kMathTag = 6,
    kNumbersTag = 10,
    kCircusTag = 7,
    kShapePuzzleTag = 9,
    kMatchTag = 4,
    kSpellWordsTag = 13,
    kAnimalTag = 12,
    kHospitalTag = 0,
    kCoinTag = 1,
    kUnitedStatesTag = 5,
    kCatDressTag = 3,
    kWordFamilyTag = 11,
    kWorldTag = 8,
    kCodingGameTag = 2,
} gameType;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
typedef enum GameType {
    kTimeTag = 6,
    kMathTag = 8,
    kNumbersTag = 12,
    kCircusTag = 9,
    kShapePuzzleTag = 11,
    kJigsawPuzzleTag = 7,
    kMatchTag = 0,
    kSpellWordsTag = 15,
    kAnimalTag = 14,
    kHospitalTag = 1,
    kCoinTag = 5,
    kUnitedStatesTag = 4,
    kCatDressTag = 2,
    kWordFamilyTag = 13,
    kWorldTag = 10,
    kCodingGameTag = 3,
} gameType;
#endif
////first words
//typedef enum GameType {
//    kTimeTag = 12,
//    kMathTag = 11,
//    kNumbersTag = 14,
//    kCircusTag = 8,
//    kShapePuzzleTag = 4,
//    kJigsawPuzzleTag = 9,
//    kMatchTag = 3,
//    kSpellWordsTag = 0,
//    kAnimalTag = 10,
//    kHospitalTag = 2,
//    kCoinTag = 5,
//    kUnitedStatesTag = 7,
//    kCatDressTag = 6,
//    kWordFamilyTag = 1,
//    kWorldTag = 13,
//} gameType;

typedef struct GAMEMANAGER_INF
{
    bool openGameTag;
}GAMEMANAGER_INF;

class GameManager {
    
public:
    
    CCArray* sceneKeys;
    CCArray* sceneIndexKeys;
    CCArray* hippoInfo;
    CCDictionary* curGameInfo;
    CCDictionary* curResourceInfo;
    int CatIndex;
    int lastTime;
    int iapDisplayCount;
    
    static GameManager* sharedManager();
    
    static CCPoint getLeftTopPos();
    static CCPoint getLeftBottomPos();
    static CCPoint getRightTopPos();
    static CCPoint getRightBottomPos();
    static CCPoint getCenter();
    static CCPoint getViewInitPos();
    static CCSize getViewVisibleSize();

    static bool getOpenGameTag();
    
    static void initGameSystem();//初始化游戏配置
    
    void setGameSystem(int _gameType,int _sceneId);//根据_gameType调用不同玩法的设置函数

    static void replaceToGameScenes();
    void setCurrentGameInfo(int _gameType);
    
    CCSprite* getIconSprite(int _iconId);
    void playIconRead(int _soundId);
    
    int getCurTime();
    
    CCString* getCurrentTime();
    
    void setLastTime();
    
    bool isNeedShowIAP();

    bool isiphoneX = false ;
    bool isIphoneX() ;
    
    void testSchedule();
    
    void setResourceInfo(int _gameType);

    const char* getDownloadUrl(int _index);
    const char* getVersionUrl(int _index);
    void setResourceVersion(int _index,std::string _version);
    std::string getResourceVersion(int _index);
    bool isHaveResources();
    void noBanner();
    void showBanner();
    void showInterstitial();
    void showReward();
    void changeToGameScene();
    void otherGame(int _gameIndex);

    void requestInitAds();
    void goToBuyIAP(int _buyIndex);
private:
    void setMathInfo(int _sceneId);//设置match的配置信息
    void setShapePuzzleInfo(int _sceneId);//设置shapepuzzle的配置信息
    void setJigsawPuzzleInfo(int _sceneId);//设置jigsawpuzzle的配置信息
    void setSpellWordsInfo(int _sceneId);//设置spellwords的配置信息
    void setMatchInfo(int _sceneId);//设置match的配置信息
    void setCircusInfo(int _sceneId);//设置circus的配置信息
    
};

#endif /* GameManager_h */

//
//  GameManager.cpp
//  GameGarden
//
//  Created by LiXiaofei on 2017/2/4.
//
//

#include "GameManager.h"
#include "DressScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni.h"
#include "platform/android/jni/JniHelper.h"
#include "android/log.h"
#endif


static GameManager* gm = NULL ;
GAMEMANAGER_INF gameManagerInf = {0};

GameManager* GameManager::sharedManager()
{
    if (!gm) {
        gm = new GameManager() ;
        gm->isiphoneX = false ;
//        gm->lastTime = 0;
//        gm->iapDisplayCount = 0;
    }
    
    
    return gm ;
}
bool GameManager::isIphoneX(){
    return isiphoneX;
}
CCPoint GameManager::getViewInitPos(){
    return CCPoint(CCEGLView::sharedOpenGLView()->getVisibleOrigin().x, CCEGLView::sharedOpenGLView()->getVisibleOrigin().y);
}

CCSize GameManager::getViewVisibleSize(){
    return CCSize(CCEGLView::sharedOpenGLView()->getVisibleSize().width, CCEGLView::sharedOpenGLView()->getVisibleSize().height);
}

CCPoint GameManager::getLeftTopPos(){
    CCPoint leftTopPos = CCPointZero;
    leftTopPos = CCPoint(getViewInitPos().x, getViewInitPos().y+getViewVisibleSize().height);
    return leftTopPos;
}

CCPoint GameManager::getLeftBottomPos(){
    CCPoint leftBottomPos = CCPointZero;
    leftBottomPos = CCPoint(getViewInitPos().x, getViewInitPos().y);
    return leftBottomPos;
}

CCPoint GameManager::getRightTopPos(){
    CCPoint rightTopPos = CCPointZero;
    rightTopPos = CCPoint(getViewInitPos().x+getViewVisibleSize().width, getViewInitPos().y+getViewVisibleSize().height);
    return rightTopPos;
}

CCPoint GameManager::getRightBottomPos(){
    CCPoint rightBottomPos = CCPointZero;
    rightBottomPos = CCPoint(getViewInitPos().x+getViewVisibleSize().width, getViewInitPos().y);
    return rightBottomPos;
}

CCPoint GameManager::getCenter(){
    CCPoint centerPos = CCPointZero;
    centerPos = CCPoint(getViewInitPos().x+getViewVisibleSize().width/2, getViewInitPos().y+getViewVisibleSize().height/2);
    return centerPos;
}

void GameManager::setResourceInfo(int _gameType){
    
    const char* filePath = "";
    
    const char* infoKey = "";
    
    switch (_gameType) {
        case kMatchTag:
            filePath = "universal/matchResourceInfo.plist";
            break;
        case kShapePuzzleTag:
            filePath = "universal/shapeResourceInfo.plist";
            break;
        case kSpellWordsTag:
            filePath = "universal/spellResourceInfo.plist";
            break;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        case kJigsawPuzzleTag:
            filePath = "universal/jigsawResourceInfo.plist";
            break;
#endif
        default:
            break;
    }
    
    curResourceInfo = CCDictionary::createWithContentsOfFile(filePath);
    CC_SAFE_RETAIN(curResourceInfo);

}

void GameManager::goToBuyIAP(int _buyIndex) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;

    bool isHave = JniHelper::getStaticMethodInfo(minfo,"cat/game/collector/kitty/free/pet/JoyPreschool","rtnActivity","()Lcat/game/collector/kitty/free/pet/JoyPreschool;");

    if (!isHave){
        CCLOG("jni:不能获取单例");
    } else{
        CCLOG("jni:可以获取单例");

        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);

        bool isHaveNoStaticMethodInfo = JniHelper::getMethodInfo(minfo,"cat/game/collector/kitty/free/pet/JoyPreschool","onBuyProduct","(I)V");
        if (!isHaveNoStaticMethodInfo){
            CCLOG("jni:alertDiaShowt方法不存在");
        } else{
            CCLOG("jni:alertDiaShow方法存在");
            minfo.env->CallVoidMethod(jobj,minfo.methodID,_buyIndex);
        }
    }
#endif
}


void GameManager::requestInitAds() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "cat/game/collector/kitty/free/pet/JoyPreschool",
                                                 "rtnActivity",
                                                 "()Lcat/game/collector/kitty/free/pet/JoyPreschool;");
    if (!isHave) {
        CCLOG("jni:不能获取单例");
    } else {
        CCLOG("jni:可以获取单例");
        jobject jobject1 = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
        bool isHaveNoStaticMethod = JniHelper::getMethodInfo(minfo,
                                                             "cat/game/collector/kitty/free/pet/JoyPreschool",
                                                             "initAds", "()V");
        if (!isHaveNoStaticMethod) {
            CCLOG("jni:不能获取单例");
        } else {
            CCLOG("jni:可以获取单例");
            minfo.env->CallVoidMethod(jobject1, minfo.methodID);
        }
        CCLOG("jni-java函数执行完毕");
    }
#endif
}

//banner
void GameManager::showBanner() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"cat/game/collector/kitty/free/pet/JoyPreschool","rtnActivity","()Lcat/game/collector/kitty/free/pet/JoyPreschool;");

    if (!isHave){
        CCLOG("jni:不能获取单例");
    } else{
        CCLOG("jni:可以获取单例");
        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);         //获取单例对象
        bool isHaveNoStaticMethod = JniHelper::getMethodInfo(minfo,"cat/game/collector/kitty/free/pet/JoyPreschool","onShowBannerAds","()V");
        if (!isHaveNoStaticMethod){
            CCLOG("jni:alertDiaShowt方法不存在");
        } else{
            CCLOG("jni:alertDiaShow方法存在");
            minfo.env->CallVoidMethod(jobj,minfo.methodID);
        }
    }
    CCLOG("jni-java函数执行完毕");
#endif
}

void GameManager::noBanner() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"cat/game/collector/kitty/free/pet/JoyPreschool","rtnActivity","()Lcat/game/collector/kitty/free/pet/JoyPreschool;");

    if (!isHave){
        CCLOG("jni:不能获取单例");
    } else{
        CCLOG("jni:可以获取单例");
        jobject jobj = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);         //获取单例对象
        bool isHaveNoStaticMethod = JniHelper::getMethodInfo(minfo,"cat/game/collector/kitty/free/pet/JoyPreschool","noBannerAds","()V");
        if (!isHaveNoStaticMethod){
            CCLOG("jni:alertDiaShowt方法不存在");
        } else{
            CCLOG("jni:alertDiaShow方法存在");
            minfo.env->CallVoidMethod(jobj,minfo.methodID);
        }
    }
    CCLOG("jni-java函数执行完毕");
#endif
}

//插页广告
void GameManager::showInterstitial() {
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo minfo;
        bool isHave = JniHelper::getStaticMethodInfo(minfo,"cat/game/collector/kitty/free/pet/JoyPreschool","rtnActivity","()Lcat/game/collector/kitty/free/pet/JoyPreschool;");
        if (!isHave){
            CCLOG("jni:不能获取单例");
        } else{
            CCLOG("jni:可以获取单例");
            jobject jobject1 = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
            bool isHaveNoStaticMethod = JniHelper::getMethodInfo(minfo,"cat/game/collector/kitty/free/pet/JoyPreschool","onShowInterstitial","()V");
            if (!isHaveNoStaticMethod){
                CCLOG("jni:不能获取单例");
            } else{
                CCLOG("jni:可以获取单例");
                minfo.env->CallVoidMethod(jobject1,minfo.methodID);
            }
        }
    CCLOG("jni-java函数执行完毕");
    #endif
}

//激励广告
void GameManager::showReward() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"cat/game/collector/kitty/free/pet/JoyPreschool","rtnActivity","()Lcat/game/collector/kitty/free/pet/JoyPreschool;");
    if (!isHave){
        CCLOG("jni:不能获取单例");
    } else{
        CCLOG("jni:可以获取单例");
        jobject jobject1 = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
        bool isHaveNoStaticMethod = JniHelper::getMethodInfo(minfo,"cat/game/collector/kitty/free/pet/JoyPreschool","showRewardAds","()V");
        if (!isHaveNoStaticMethod){
            CCLOG("jni:不能获取单例");
        } else{
            CCLOG("jni:可以获取单例");
            minfo.env->CallVoidMethod(jobject1,minfo.methodID);
        }
    }
    CCLOG("jni-java函数执行完毕");
#endif
}
void GameManager::changeToGameScene() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, DressScene::sceneWithID(CatIndex+1), ccWHITE));
}

//导量
void GameManager::otherGame(int _gameIndex) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"cat/game/collector/kitty/free/pet/JoyPreschool","rtnActivity","()Lcat/game/collector/kitty/free/pet/JoyPreschool;");
    if (!isHave){
        CCLOG("jni:不能获取单例");
    } else{
        CCLOG("jni:可以获取单例");
        jobject jobject1 = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
        bool isHaveNoStaticMethod = JniHelper::getMethodInfo(minfo,"cat/game/collector/kitty/free/pet/JoyPreschool","goToMarket","(I)V");
        if (!isHaveNoStaticMethod){
            CCLOG("jni:不能获取单例");
        } else{
            CCLOG("jni:可以获取单例");
            minfo.env->CallVoidMethod(jobject1,minfo.methodID,_gameIndex);
        }
    }
    CCLOG("jni-java函数执行完毕");
#endif
}

void GameManager::initGameSystem(){
    gameManagerInf.openGameTag = true;

    
//    CCUserDefault::sharedUserDefault()->setBoolForKey("UnlockAll",true);
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("ClockIndex", 1);
    
    int clock = CCUserDefault::sharedUserDefault()->getIntegerForKey("ClockIndex");
    if (clock == 0) {
        clock = 1;
        CCUserDefault::sharedUserDefault()->setIntegerForKey("ClockIndex", clock);
    }
    
    if (!CCUserDefault::sharedUserDefault()->getIntegerForKey("GameLevel")) {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("GameLevel", 2);
    }
}

bool GameManager::getOpenGameTag(){
    return gameManagerInf.openGameTag;
}

void GameManager::setCurrentGameInfo(int _gameType){
    const char* filePath = "";
    
    const char* infoKey = "";
    
    switch (_gameType) {
        case kMatchTag:
            filePath = "universal/matchInfo.plist";
            infoKey = "match";
            break;
        case kShapePuzzleTag:
            filePath = "mainscenes/scenesIcon/shapePuzzleInfo.plist";
            infoKey = "shapepuzzle";
            break;
        case kSpellWordsTag:
            filePath = "mainscenes/scenesIcon/spellWordsInfo.plist";
            infoKey = "spellwords";
            break;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        case kJigsawPuzzleTag:
//            filePath = "mainscenes/scenesIcon/jigsawPuzzleInfo.plist";
//            infoKey = "jigsawpuzzle";
//            break;
#endif
        default:
            break;
    }
    
    curGameInfo = CCDictionary::createWithContentsOfFile(filePath);
    CC_SAFE_RETAIN(curGameInfo);
    
//    CCDictionary* curScenesInfo  = CCDictionary::createWithContentsOfFile("mainscenes/scenesIcon/scenesInfo.plist");
//
//    sceneKeys = (CCArray*)curScenesInfo->objectForKey(infoKey);
//    CC_SAFE_RETAIN(sceneKeys);
//
//    CCDictionary* curScenesKeyInfo  = CCDictionary::createWithContentsOfFile("mainscenes/scenesInfo.plist");
//
//    sceneIndexKeys = (CCArray*)curScenesKeyInfo->objectForKey(infoKey);
//    CC_SAFE_RETAIN(sceneIndexKeys);
//
//    for (int i = 0; i < sceneKeys->count(); i++) {
//        CCLog("=====index = %d,key = %s=====",i,((CCString*)sceneKeys->objectAtIndex(i))->getCString());
//    }
//
//    CCDictionary* curHippoInfo  = CCDictionary::createWithContentsOfFile("mainscenes/hippoAnim/hippoInfo.plist");
//
//    hippoInfo = (CCArray*)curHippoInfo->objectForKey(infoKey);
//    CC_SAFE_RETAIN(hippoInfo);
}

bool GameManager::isHaveResources(){
    std::string _str = "assets/catdress/background/selectBg.png";
    if (CCFileUtils::sharedFileUtils()->isFileExist(_str))
    {
        return true;
    }

    return false;
}

const char* GameManager::getDownloadUrl(int _index){
    const char* _downloadUrl = NULL;
    
    switch (_index) {
        case kCatDressTag:
            _downloadUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/catdress/catdress.zip";
            break;
        case kMatchTag:
            _downloadUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/match/match.zip";
            break;
        case kUnitedStatesTag:
            _downloadUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/unitedstates/unitedstates.zip";
            break;
        case kCircusTag:
            _downloadUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/circus/circus.zip";
            break;
        case kMathTag:
            _downloadUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/circus/circus.zip";
            break;
        case kShapePuzzleTag:
            _downloadUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/shapepuzzle/shapepuzzle.zip";
            break;
        case kWorldTag:
            _downloadUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/world/world.zip";
            break;
        case kNumbersTag:
            _downloadUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/circus/circus.zip";
            break;
        case kWordFamilyTag:
            _downloadUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/wordfamily/wordfamily.zip";
            break;
        case kAnimalTag:
            _downloadUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/circus/circus.zip";
            break;
        case kSpellWordsTag:
            _downloadUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/spellwords/spellwords.zip";
            break;
        default:
            break;
        // case kCatDressTag:
        //     _downloadUrl = "http://pg7n7pwcj.bkt.clouddn.com/catdress.zip";
        //     break;
        // case kMatchTag:
        //     _downloadUrl = "http://pg7n7pwcj.bkt.clouddn.com/match.zip";
        //     break;
        // case kUnitedStatesTag:
        //     _downloadUrl = "http://pg7n7pwcj.bkt.clouddn.com/unitedstates.zip";
        //     break;
        // case kCircusTag:
        //     _downloadUrl = "http://pg7n7pwcj.bkt.clouddn.com/circus.zip";
        //     break;
        // case kMathTag:
        //     _downloadUrl = "http://pg7n7pwcj.bkt.clouddn.com/circus.zip";
        //     break;
        // case kShapePuzzleTag:
        //     _downloadUrl = "http://pg7n7pwcj.bkt.clouddn.com/shapepuzzle.zip";
        //     break;
        // case kWorldTag:
        //     _downloadUrl = "http://pg7n7pwcj.bkt.clouddn.com/world.zip";
        //     break;
        // case kNumbersTag:
        //     _downloadUrl = "http://pg7n7pwcj.bkt.clouddn.com/circus.zip";
        //     break;
        // case kWordFamilyTag:
        //     _downloadUrl = "http://pg7n7pwcj.bkt.clouddn.com/wordfamily.zip";
        //     break;
        // case kAnimalTag:
        //     _downloadUrl = "http://pg7n7pwcj.bkt.clouddn.com/circus.zip";
        //     break;
        // case kSpellWordsTag:
        //     _downloadUrl = "http://pg7n7pwcj.bkt.clouddn.com/spellwords.zip";
        //     break;
        // default:
        //     break;
    }

    CCLog("downloadUrl =============> %s",_downloadUrl);
    
    return _downloadUrl;
}

const char* GameManager::getVersionUrl(int _index){
    const char* _downloadVersionUrl = NULL;
    
    // switch (_index) {
    //     case kCatDressTag:
    //         _downloadVersionUrl = "http://pg7n7pwcj.bkt.clouddn.com/catversion";
    //         break;
    //     case kMatchTag:
    //         _downloadVersionUrl = "http://pg7n7pwcj.bkt.clouddn.com/matchversion";
    //         break;
    //     case kUnitedStatesTag:
    //         _downloadVersionUrl = "http://pg7n7pwcj.bkt.clouddn.com/unitedversion";
    //         break;
    //     case kCircusTag:
    //         _downloadVersionUrl = "http://pg7n7pwcj.bkt.clouddn.com/circusversion";
    //         break;
    //     case kMathTag:
    //         _downloadVersionUrl = "http://pg7n7pwcj.bkt.clouddn.com/circusversion";
    //         break;
    //     case kShapePuzzleTag:
    //         _downloadVersionUrl = "http://pg7n7pwcj.bkt.clouddn.com/shapeversion";
    //         break;
    //     case kWorldTag:
    //         _downloadVersionUrl = "http://pg7n7pwcj.bkt.clouddn.com/worldversion";
    //         break;
    //     case kNumbersTag:
    //         _downloadVersionUrl = "http://pg7n7pwcj.bkt.clouddn.com/circusversion";
    //         break;
    //     case kWordFamilyTag:
    //         _downloadVersionUrl = "http://pg7n7pwcj.bkt.clouddn.com/wordfamilyversion";
    //         break;
    //     case kAnimalTag:
    //         _downloadVersionUrl = "http://pg7n7pwcj.bkt.clouddn.com/circusversion";
    //         break;
    //     case kSpellWordsTag:
    //         _downloadVersionUrl = "http://pg7n7pwcj.bkt.clouddn.com/spellversion";
    //         break;
    //     default:
    //         break;
    // }
    switch (_index) {
        case kCatDressTag:
            _downloadVersionUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/catdress/catversion";
            break;
        case kMatchTag:
            _downloadVersionUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/match/matchversion";
            break;
        case kUnitedStatesTag:
            _downloadVersionUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/unitedstates/unitedversion";
            break;
        case kCircusTag:
            _downloadVersionUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/circus/circusversion";
            break;
        case kMathTag:
            _downloadVersionUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/circus/circusversion";
            break;
        case kShapePuzzleTag:
            _downloadVersionUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/shapepuzzle/shapeversion";
            break;
        case kWorldTag:
            _downloadVersionUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/world/worldversion";
            break;
        case kNumbersTag:
            _downloadVersionUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/circus/circusversion";
            break;
        case kWordFamilyTag:
            _downloadVersionUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/wordfamily/wordfamilyversion";
            break;
        case kAnimalTag:
            _downloadVersionUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/circus/circusversion";
            break;
        case kSpellWordsTag:
            _downloadVersionUrl = "https://s3-us-west-1.amazonaws.com/joylands3/Resources/spellwords/spellversion";
            break;
        default:
            break;
    }
    
    return _downloadVersionUrl;
}

void GameManager::setResourceVersion(int _index,std::string _version){
    CCLog("<============set resource version============> %s",_version.c_str());
    // _index = _index+1;
    switch (_index) {
        case kCatDressTag:
            CCUserDefault::sharedUserDefault()->setStringForKey("CatVersion",_version.c_str());
            break;
        case kMatchTag:
            CCUserDefault::sharedUserDefault()->setStringForKey("MatchVersion",_version.c_str());
            break;
        case kUnitedStatesTag:
            CCUserDefault::sharedUserDefault()->setStringForKey("UnitedVersion",_version.c_str());
            break;
        case kCircusTag:
            CCUserDefault::sharedUserDefault()->setStringForKey("CircusVersion",_version.c_str());
            break;
        case kMathTag:
            CCUserDefault::sharedUserDefault()->setStringForKey("CircusVersion",_version.c_str());
            break;
        case kShapePuzzleTag:
            CCUserDefault::sharedUserDefault()->setStringForKey("ShapeVersion",_version.c_str());
            break;
        case kWorldTag:
            CCUserDefault::sharedUserDefault()->setStringForKey("WorldVersion",_version.c_str());
            break;
        case kNumbersTag:
            CCUserDefault::sharedUserDefault()->setStringForKey("CircusVersion",_version.c_str());
            break;
        case kWordFamilyTag:
            CCUserDefault::sharedUserDefault()->setStringForKey("WordFamilyVersion",_version.c_str());
            break;
        case kAnimalTag:
            CCUserDefault::sharedUserDefault()->setStringForKey("CircusVersion",_version.c_str());
            break;
        case kSpellWordsTag:
            CCUserDefault::sharedUserDefault()->setStringForKey("SpellVersion",_version.c_str());
            break;
        default:
            break;
    }
}

std::string GameManager::getResourceVersion(int _index){
    std::string _version = "";

    CCLog("<===========get resource version=============> %d",_index);
    _index = _index - 1;
    switch (_index) {
        case kCatDressTag:
            _version = CCUserDefault::sharedUserDefault()->getStringForKey("CatVersion");
            break;
        case kMatchTag:
            _version = CCUserDefault::sharedUserDefault()->getStringForKey("MatchVersion");
            break;
        case kUnitedStatesTag:
            _version = CCUserDefault::sharedUserDefault()->getStringForKey("UnitedVersion");
            break;
        case kCircusTag:
            _version = CCUserDefault::sharedUserDefault()->getStringForKey("CircusVersion");
            break;
        case kMathTag:
            _version = CCUserDefault::sharedUserDefault()->getStringForKey("CircusVersion");
            break;
        case kShapePuzzleTag:
            _version = CCUserDefault::sharedUserDefault()->getStringForKey("ShapeVersion");
            break;
        case kWorldTag:
            _version = CCUserDefault::sharedUserDefault()->getStringForKey("WorldVersion");
            break;
        case kNumbersTag:
            _version = CCUserDefault::sharedUserDefault()->getStringForKey("CircusVersion");
            break;
        case kWordFamilyTag:
            _version = CCUserDefault::sharedUserDefault()->getStringForKey("WordFamilyVersion");
            break;
        case kAnimalTag:
            _version = CCUserDefault::sharedUserDefault()->getStringForKey("CircusVersion");
            break;
        case kSpellWordsTag:
            _version = CCUserDefault::sharedUserDefault()->getStringForKey("SpellVersion");
            break;
        default:
            break;
    }

    return _version;
}

CCSprite* GameManager::getIconSprite(int _iconId){
    
    const char* iconFile = ((CCString*)sceneKeys->objectAtIndex(_iconId))->getCString();
    
    CCString* filePath = CCString::createWithFormat("mainscenes/scenesIcon/%s.png",iconFile);
    
    CCLog("------index = %d,imageName = %s------",_iconId,iconFile);
    
    CCSprite* trainIcon = CCSprite::create(filePath->getCString());
    
    if (trainIcon != NULL) {
        return trainIcon;
    } else {
        return NULL;
    }
    
}

void GameManager::playIconRead(int _soundId){
    const char* iconFile = ((CCString*)sceneIndexKeys->objectAtIndex(_soundId))->getCString();
    
    CCString* filePath = CCString::createWithFormat("mainscenes/scenesIcon/sound/%s.mp3",iconFile);
    
    CCLog("------index = %d,imageName = %s------",_soundId,iconFile);
    

}

int GameManager::getCurTime(){
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    
    struct tm *tm;
    time_t timep = now.tv_sec;
    tm = localtime(&timep);
    int min=tm->tm_min;
    
    return min;
    
}

bool GameManager::isNeedShowIAP(){
    
    if (iapDisplayCount < 1) {
        
        int curMin = this->getCurTime();
        
        int duration = curMin - lastTime;
        
        if (iapDisplayCount == 0 && duration >= 5) {
            lastTime = curMin;
            iapDisplayCount++;
            return true;
//        }else if (iapDisplayCount == 1 && duration >= 15){
//            lastTime = curMin;
//            iapDisplayCount++;
//            return true;
        }
    }
    
    return false;
}

void GameManager::testSchedule(){
    
    bool isShow = this->isNeedShowIAP();
    
    if (isShow) {
        CCLog("----------true----------");
    } else {
        CCLog("----------false----------");
    }
}

void GameManager::setLastTime(){
    lastTime = this->getCurTime();
}

CCString* GameManager::getCurrentTime(){
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    
    struct tm *tm;
    time_t timep = now.tv_sec+7*24*60*60;
    tm = localtime(&timep);
    int year = tm->tm_year + 1900;
    int month = tm->tm_mon;
    int day = tm->tm_mday;
    
    const char* curMonth = "";
    //Jan. Feb. Mar. Apr. May. Jun. Jul. Aug. Sep. Oct. Nov. Dec.
    switch (month) {
        case 0:
            curMonth = "Jan.";
            break;
        case 1:
            curMonth = "Feb.";
            break;
        case 2:
            curMonth = "Mar.";
            break;
        case 3:
            curMonth = "Apr.";
            break;
        case 4:
            curMonth = "May";
            break;
        case 5:
            curMonth = "Jun.";
            break;
        case 6:
            curMonth = "Jul.";
            break;
        case 7:
            curMonth = "Aug.";
            break;
        case 8:
            curMonth = "Sep.";
            break;
        case 9:
            curMonth = "Oct.";
            break;
        case 10:
            curMonth = "Nov.";
            break;
        case 11:
            curMonth = "Dec.";
            break;
        default:
            break;
    }
    
    CCString* curTime = CCString::createWithFormat("%s %d, %d",curMonth,day,year);
    
    return curTime;
}

void GameManager::setGameSystem(int _gameType,int _sceneId){
    switch (_gameType) {
        case kSpellWordsTag:
        {
            setSpellWordsInfo(_sceneId);
        }
            break;
        case kMatchTag:
        {
            setMatchInfo(_sceneId);
        }
            break;
        case kCircusTag:
        {
            setCircusInfo(_sceneId);
        }
            break;
        case kAnimalTag:
        {
            setMathInfo(_sceneId);
        }
            break;
        case kShapePuzzleTag:
        {
            setShapePuzzleInfo(_sceneId);
        }
            break;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        case kJigsawPuzzleTag:
        {
            setJigsawPuzzleInfo(_sceneId);
        }
            break;
#endif
        default:
            break;
    }
}

void GameManager::setMathInfo(int _sceneId){
    
}

void GameManager::setCircusInfo(int _sceneId){
    
}

void GameManager::setShapePuzzleInfo(int _sceneId){
    
    CCString* infoKey = (CCString*)sceneIndexKeys->objectAtIndex(_sceneId);
    
    CCDictionary* info = (CCDictionary*)curGameInfo->objectForKey(infoKey->getCString());
    
    int sceneIndex = info->valueForKey("currentSceneIndex")->intValue();
    int itemIndex = info->valueForKey("currentItemIndex")->intValue();
    

    
}

void GameManager::setMatchInfo(int _sceneId){
    
    CCString* infoKey = (CCString*)sceneIndexKeys->objectAtIndex(_sceneId);
    
    CCDictionary* info = (CCDictionary*)curGameInfo->objectForKey(infoKey->getCString());
    

    
}

void GameManager::setSpellWordsInfo(int _sceneId){

    
    CCString* infoKey = (CCString*)sceneIndexKeys->objectAtIndex(_sceneId);
    
    CCDictionary* info = (CCDictionary*)curGameInfo->objectForKey(infoKey->getCString());
    
    int curSceneIndex = info->valueForKey("currentSceneIndex")->intValue();
    int curNum = info->valueForKey("currentNum")->intValue();
    
   ;
    
}

void GameManager::setJigsawPuzzleInfo(int _sceneId){
    
    CCString* infoKey = (CCString*)sceneIndexKeys->objectAtIndex(_sceneId);
    

    
    CCDictionary* info = (CCDictionary*)curGameInfo->objectForKey(infoKey->getCString());
    

}

void GameManager::replaceToGameScenes(){
    
}






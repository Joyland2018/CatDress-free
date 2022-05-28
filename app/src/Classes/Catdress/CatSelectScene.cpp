//
//  CatSelectScene.cpp
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-4.
//
//

#include "CatSelectScene.h"
#include "BeginScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "BuyPage.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif
#define ADJUST_ANIM_VELOCITY 800;

enum{
    kScrollLayerTag = 1,
    kScrollViewTag = 60,
    kHomeBtnTag = 4,
    kBuyLayerTag = 2,
    kLockTag = 3,
    kPointTag = 49,
    kPointBgTag = 50,
    kCatTag = 100,
    kBathBtnTag = 200,
    kDressBtnTag = 201,
    kClipBtnTag = 202,
};

CCScene* CatSelectScene::sceneWithID(int _catID){
    CCScene* scene = CCScene::create();
    
    CatSelectScene* layer = CatSelectScene::nodeWithID(_catID);
    
    scene->addChild(layer);
    
    return scene;
}

CatSelectScene* CatSelectScene::nodeWithID(int _animalID){
    CatSelectScene* layer = new CatSelectScene();
    if (layer->initWithID(_animalID)) {
        layer->autorelease();
        
        return layer;
    }else {
        return NULL;
    }
}

bool CatSelectScene::initWithID(int _animalID){
    if (!CCLayer::init()) {
        return false;
    }
    _curCatTag = _animalID;

    return true;
}

void CatSelectScene::addLock(CCSprite* item, cocos2d::CCSize itemSize){
    CCSprite* lock = CCSprite::create("ui/lock.png");
    lock->setPosition(ccp(itemSize.width/2, itemSize.height/2));
    lock->setTag(kLockTag);
    item->addChild(lock);
}

void CatSelectScene::onEnter(){
    CCLayer::onEnter();

    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();

    CCPoint rightBottom = GameManager::sharedManager()->getRightBottomPos();

    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui/clipAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui/bathAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui/dressAnim.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("ui/clipAnim.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("ui/bathAnim.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("ui/dressAnim.png");

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/clipAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/bathAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/dressAnim.plist");


    isTouchHome = false;
    touchSprite = NULL;
    bt_firstword = NULL;
    bt_wordbreak = NULL;
    bt_wordblock = NULL;
    bt_shapepuzzle = NULL;
    bt_Jorland = NULL;
    bt_Match = NULL;

    CCLayer* scrollLayer = CCLayer::create();

    CCDictionary* selectInfo = CatDressManager::sharedManager()->getDictionary("selectInformation.plist", NULL);

    CCSprite* background = CCSprite::create("background/selectBg.png");
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background);

    //导量
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") == false){



        bt_ad = CCSprite::create("ad.png");
        bt_background = CCSprite::create("background.png");
        this->addChild(bt_background,1);
        bt_background->setPosition(ccp(leftBottom.x+bt_background->getContentSize().width/2.0-22,leftBottom.y+bt_background->getContentSize().height/2.0-22));
        bt_ad->setPosition(ccp(leftBottom.x+bt_ad->getContentSize().width/2.0-2,leftBottom.y+bt_ad->getContentSize().height/2.0-2));
        bt_background->setScale(0.7);
        bt_ad->setScale(0.7);
        select = arc4random()%8;
        switch (select){
            case 0:{
                bt_firstword = CCSprite::create("firstword.png");
                this->addChild(bt_firstword,1);
                bt_firstword->setPosition(ccp(leftBottom.x+bt_firstword->getContentSize().width/2.0-50,leftBottom.y+bt_firstword->getContentSize().height/2.0-40));
                bt_firstword->setScale(0.7);
            }
                break;
            case 1:{
                bt_shapepuzzle = CCSprite::create("shapepuzzle.png");
                this->addChild(bt_shapepuzzle,1);
                bt_shapepuzzle->setPosition(ccp(leftBottom.x+bt_shapepuzzle->getContentSize().width/2.0-50,leftBottom.y+bt_shapepuzzle->getContentSize().height/2.0-40));
                bt_shapepuzzle->setScale(0.7);
            }
                break;
            case 2:{
                bt_wordblock = CCSprite::create("otherGame_WordBlock.png");
                this->addChild(bt_wordblock,1);
                bt_wordblock->setPosition(ccp(leftBottom.x+bt_wordblock->getContentSize().width/2.0-14,leftBottom.y+bt_wordblock->getContentSize().height/2.0-12));
                bt_wordblock->setScale(0.6);
            }
                break;
            case 3:{
                bt_wordbreak = CCSprite::create("otherGame_WordBreak.png");
                this->addChild(bt_wordbreak,1);
                bt_wordbreak->setPosition(ccp(leftBottom.x+bt_wordbreak->getContentSize().width/2.0-14,leftBottom.y+bt_wordbreak->getContentSize().height/2.0-12));
                bt_wordbreak->setScale(0.6);
            }
                break;
            case 4:{
                bt_firstword = CCSprite::create("otherGame_FirstWords.png");
                this->addChild(bt_firstword,1);
                bt_firstword->setPosition(ccp(leftBottom.x+bt_firstword->getContentSize().width/2.0-17,leftBottom.y+bt_firstword->getContentSize().height/2.0-12));
                bt_firstword->setScale(0.6);
            }
                break;
            case 5:{
                bt_shapepuzzle = CCSprite::create("otherGame_ShapePuzzle.png");
                this->addChild(bt_shapepuzzle,1);
                bt_shapepuzzle->setPosition(ccp(leftBottom.x+bt_shapepuzzle->getContentSize().width/2.0-17,leftBottom.y+bt_shapepuzzle->getContentSize().height/2.0-12));
                bt_shapepuzzle->setScale(0.6);
            }
                break;
            case 6:{
                bt_Jorland = CCSprite::create("otherGame_Joyland.png");
                this->addChild(bt_Jorland,1);
                bt_Jorland->setPosition(ccp(leftBottom.x+bt_Jorland->getContentSize().width/2.0-17,leftBottom.y+bt_Jorland->getContentSize().height/2.0-12));
                bt_Jorland->setScale(0.6);
            }
                break;
            case 7:{
                bt_Match = CCSprite::create("otherGame_Match.png");
                this->addChild(bt_Match,1);
                bt_Match->setPosition(ccp(leftBottom.x+bt_Match->getContentSize().width/2.0-17,leftBottom.y+bt_Match->getContentSize().height/2.0-12));
                bt_Match->setScale(0.6);
            }
                break;
            default:
                break;
        }
        this->addChild(bt_ad,1);


        CCMenuItemImage* noadsItem = CCMenuItemImage::create("noAds.png", "noAds.png", this, menu_selector(CatSelectScene::clickBuy));
        noadsItem->setScale(1.2);
        CCMenu* noadsMenu = CCMenu::create(noadsItem,NULL);
//    reviewMenu->setPosition(ccp(homeMenu->getPosition().x+homeItem->getContentSize().width/2+reviewItem->getContentSize().width/2, homeMenu->getPosition().y));
        noadsMenu->setPosition(ccp(rightBottom.x-noadsItem->getContentSize().width,leftBottom.y+noadsItem->getContentSize().height-40));
        this->addChild(noadsMenu, 110);

    }
    if (GameManager::sharedManager()->isIphoneX()) {
        background->setScale(1.3);
    }

    CCSprite* homeBtn = CCSprite::create("universal/back.png");
    homeBtn->setPosition(ccp(leftBottom.x+winSize.width/16, leftBottom.y+winSize.height*11/12));
    homeBtn->setTag(kHomeBtnTag);
    this->addChild(homeBtn);

    scrollLayer->setPosition(ccp(winSize.width/2, winSize.height/2));

    int catTag;

    CCPoint initPointPos;

    for (int i = 0; i < selectInfo->count(); i++) {
        catTag = selectInfo->valueForKey(CCString::createWithFormat("select%d",i+1)->getCString())->intValue();
        CCSprite* cat = CCSprite::create(CCString::createWithFormat("selectCat/selCat%d.png",catTag)->getCString());
        cat->setPosition(ccp(winSize.width/2+i*winSize.width/2, winSize.height*0.40));
        cat->setScale(0.8);
        cat->setTag(i+kCatTag);
        scrollLayer->addChild(cat);

//        if (i>0 && CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") == false) {
//            this->addLock(cat, cat->getContentSize());
//        }

        CCSprite* pointBg = CCSprite::create("ui/pointBg.png");
        pointBg->setPosition(ccp(leftBottom.x+winSize.width/2.8+i*winSize.width/45, winSize.height/20));
        if (i == _curCatTag) {
            initPointPos = pointBg->getPosition();
        }
        pointBg->setTag(i+kPointBgTag);

        this->addChild(pointBg);
    }

    CCSprite* point = CCSprite::create("ui/point.png");
    point->setPosition(initPointPos);
    point->setTag(kPointTag);
    this->addChild(point);

    scrollLayer->setTag(kScrollLayerTag);
    scrollLayer->setContentSize(CCSizeMake(winSize.width*7, winSize.height));

    scrollView = CCScrollView::create(CCSizeMake(winSize.width, winSize.height),scrollLayer);
    scrollView->setPosition(leftBottom);
    scrollView->setTag(kScrollViewTag);
    scrollView->setTouchEnabled(true);
    scrollView->setDelegate(this);
    scrollView->setDirection(kCCScrollViewDirectionHorizontal);
    scrollView->setContentSize(CCSizeMake(winSize.width*7, winSize.height));
    scrollView->setContentOffset(ccp(-_curCatTag*winSize.width/2, 0));

    this->addChild(scrollView,2);

    this->showGameMenu();

//    if (CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") == false) {
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("isShownReview") == false) {
        this->checkIAP();
        this->schedule(schedule_selector(CatSelectScene::checkIAP), 10.0);
    }

    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/background/selectBg.mp3", true);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    DeviceManager::sharedManager()->setTimeEvent("Cat Dressup Duration");
#else
#endif

    this->setTouchEnabled(true);
}

void CatSelectScene::clickBuy(){
    GameManager::sharedManager()->goToBuyIAP(0);
}

void CatSelectScene::onExit(){
    CCLayer::onExit();

}

CatSelectScene::CatSelectScene(){
    
}

CatSelectScene::~CatSelectScene(){
    scrollView->stopAllActions();
    scrollView->removeAllChildrenWithCleanup(true);
    this->stopAllActions();
    this->removeAllChildrenWithCleanup(true);
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}

void CatSelectScene::adjustScrollView(){
    if(scrollView!=NULL){
    scrollView->unscheduleAllSelectors();
    
//    int winHalf = CCDirector::sharedDirector()->getWinSize().width/2;
    int winHalf = GameManager::sharedManager()->getViewVisibleSize().width/2;
    int x = scrollView->getContentOffset().x;
    float minX = scrollView->minContainerOffset().x;
    float maxX = scrollView->maxContainerOffset().x;
    int offset = (int)x%winHalf;
    
    CCPoint adjustPos;
    // 调整动画时间
    float adjustAnimDelay;
    
    if (offset < -winHalf/2 && x < maxX && x > minX) {
        // 计算下一页位置，时间
        adjustPos = ccpSub(scrollView->getContentOffset(), ccp(winHalf + offset, 0));
        adjustAnimDelay = (float) (winHalf + offset) / ADJUST_ANIM_VELOCITY;
    }
    else {
        // 计算当前页位置，时间
        adjustPos = ccpSub(scrollView->getContentOffset(), ccp(offset, 0));
        // 这里要取绝对值，否则在第一页往左翻动的时，保证adjustAnimDelay为正数
        adjustAnimDelay = (float) abs(offset) / ADJUST_ANIM_VELOCITY;
    }

        if (x > maxX){
            adjustPos = scrollView->maxContainerOffset();
        } else if (x < minX){
            adjustPos = scrollView->minContainerOffset();
        }
    // 调整位置
    int curCatIndex = adjustPos.x/-winHalf;
//    if (curCatIndex < 0){
//
//    }
        scrollView->setContentOffsetInDuration(adjustPos, adjustAnimDelay);
        CCSprite* pointBg = (CCSprite*)this->getChildByTag(curCatIndex+kPointBgTag);
        if (pointBg != NULL) {
            CCSprite *point = (CCSprite *) this->getChildByTag(kPointTag);
            point->setPosition(pointBg->getPosition());
        }
    _curCatTag = curCatIndex;
    
    SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mp3/cat/cat%d.mp3",_curCatTag+1)->getCString());
    this->removeGameMenu();
    
    CCLayer* scrollLayer = (CCLayer*)scrollView->getChildByTag(kScrollLayerTag);
    CCSprite* cat = (CCSprite*)scrollLayer->getChildByTag(kCatTag+curCatIndex);
    CCSprite* lock = (CCSprite*)cat->getChildByTag(kLockTag);
    if (lock == NULL) {
        this->showGameMenu();
    }
//    if (changeSoundTag!=0) {
//    }
//    
//    CCDictionary* changeDogSoundInfo = GameManager::sharedManager()->getDictionary("dogSoundInformation.plist", NULL);
//    int soundIndex = changeDogSoundInfo->valueForKey(CCString::createWithFormat("select%d",curDogIndex+1)->getCString())->intValue();
//    if (isPlayDogSound == true) {
//        SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("dogShout%d.mp3",soundIndex)->getCString());
//        isPlayDogSound = false;
//    }
//    changeSoundTag = soundIndex;
    }
}

void CatSelectScene::showGameMenu(){
//    CCSprite* curCat = (CCSprite*)this->getChildByTag(_catTag+kCatTag);
//    if (curCat != NULL) {
        CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
        
        CCSprite* bathBtn = CCSprite::createWithSpriteFrameName("bath_0001.png");
        bathBtn->setPosition(ccp(leftBottom.x+winSize.width/2, leftBottom.y+winSize.height*0.55));
        bathBtn->setTag(kBathBtnTag);
        bathBtn->setScale(0.3);
        this->addChild(bathBtn);
        
//        CCScaleTo* scaleTo = CCScaleTo::create(0.5, 1);
    
        CCMoveTo* bathMov = CCMoveTo::create(0.5, ccp(leftBottom.x+winSize.width*0.25, leftBottom.y+winSize.height*0.75));
    bathBtn->runAction(CCSequence::createWithTwoActions(CCSpawn::createWithTwoActions(bathMov, CCScaleTo::create(0.5, 1.0)), CCCallFuncND::create(this, callfuncND_selector(CatSelectScene::showMenuAnim), (void*)kBathBtnTag)));
    
        CCSprite* dressBtn = CCSprite::createWithSpriteFrameName("dress_0001.png");
        dressBtn->setPosition(ccp(leftBottom.x+winSize.width/2, leftBottom.y+winSize.height*0.6));
        dressBtn->setTag(kDressBtnTag);
        dressBtn->setScale(0.3);
        this->addChild(dressBtn);

        if (_curCatTag>0 && CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") == false) {
            this->addLock(dressBtn, dressBtn->getContentSize());
        }
        CCMoveTo* dressMov = CCMoveTo::create(0.5, ccp(leftBottom.x+winSize.width/2, leftBottom.y+winSize.height*0.8));
    dressBtn->runAction(CCSequence::createWithTwoActions(CCSpawn::createWithTwoActions(dressMov, CCScaleTo::create(0.5, 1.0)), CCCallFuncND::create(this, callfuncND_selector(CatSelectScene::showMenuAnim), (void*)kDressBtnTag)));
    
        CCSprite* clipBtn = CCSprite::createWithSpriteFrameName("clip_0001.png");
        clipBtn->setPosition(ccp(leftBottom.x+winSize.width/2, leftBottom.y+winSize.height*0.6));
        clipBtn->setTag(kClipBtnTag);
    clipBtn->setScale(0.3);
        this->addChild(clipBtn);
        
        CCMoveTo* clipMov = CCMoveTo::create(0.5, ccp(leftBottom.x+winSize.width*0.75, leftBottom.y+winSize.height*0.75));
    clipBtn->runAction(CCSequence::createWithTwoActions(CCSpawn::createWithTwoActions(clipMov, CCScaleTo::create(0.5, 1.0)), CCCallFuncND::create(this, callfuncND_selector(CatSelectScene::showMenuAnim), (void*)kClipBtnTag)));
    
//    }
}

void CatSelectScene::showMenuAnim(cocos2d::CCNode *sender,int _tag){
    const char* fileName = NULL;
    int frameNum = 0;
    switch (_tag) {
        case kBathBtnTag:
        {
            fileName = "bath";
            frameNum = 7;
        }
            break;
        case kDressBtnTag:
        {
            fileName = "dress";
            frameNum = 10;

        }
            break;
        case kClipBtnTag:
        {
            fileName = "clip";
            frameNum = 8;
        }
            break;
        default:
            break;
    }
    
    CCAnimate* btnAnim = CatDressManager::sharedManager()->getSpriteAnimate(0, frameNum, fileName, false);
    CCRepeatForever* repeat = CCRepeatForever::create(CCSequence::createWithTwoActions(btnAnim, CCDelayTime::create(0.3)));
    sender->runAction(repeat);
}

void CatSelectScene::removeGameMenu(){
    CCSprite* bathBtn = (CCSprite*)this->getChildByTag(kBathBtnTag);
    CCSprite* dressBtn = (CCSprite*)this->getChildByTag(kDressBtnTag);
    CCSprite* clipBtn = (CCSprite*)this->getChildByTag(kClipBtnTag);
    
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
    
    
    if (bathBtn != NULL) {
//        bathBtn->stopAllActions();
        CCMoveTo* moveTo = CCMoveTo::create(0.2, ccp(leftBottom.x+winSize.width/2, leftBottom.y+winSize.height*0.6));
        CCScaleTo* scaleTo = CCScaleTo::create(0.2, 0.3);
        bathBtn->runAction(CCSequence::createWithTwoActions(CCSpawn::createWithTwoActions(moveTo, scaleTo), CCCallFuncN::create(this, callfuncN_selector(CatSelectScene::removeSprite))));
    }
    if (dressBtn != NULL) {
//        dressBtn->stopAllActions();
        CCMoveTo* moveTo = CCMoveTo::create(0.2, ccp(leftBottom.x+winSize.width/2, leftBottom.y+winSize.height*0.6));
        CCScaleTo* scaleTo = CCScaleTo::create(0.2, 0.3);
        dressBtn->runAction(CCSequence::createWithTwoActions(CCSpawn::createWithTwoActions(moveTo, scaleTo), CCCallFuncN::create(this, callfuncN_selector(CatSelectScene::removeSprite))));
    }
    if (clipBtn != NULL) {
//        clipBtn->stopAllActions();
        CCMoveTo* moveTo = CCMoveTo::create(0.2, ccp(leftBottom.x+winSize.width/2, leftBottom.y+winSize.height*0.6));
        CCScaleTo* scaleTo = CCScaleTo::create(0.2, 0.3);
        clipBtn->runAction(CCSequence::createWithTwoActions(CCSpawn::createWithTwoActions(moveTo, scaleTo), CCCallFuncN::create(this, callfuncN_selector(CatSelectScene::removeSprite))));
    }
}

void CatSelectScene::removeSprite(cocos2d::CCNode *sender){
    if (sender != NULL) {
        sender->stopAllActions();
        sender->removeFromParentAndCleanup(true);
        sender = NULL;
    }
}

void CatSelectScene::isTouchMenu(cocos2d::CCNode *sender){
    
}

void CatSelectScene::scrollViewDidScroll(CCScrollView* view){
    
}

void CatSelectScene::scrollViewDidZoom(CCScrollView* view){
    
}

void CatSelectScene::goInStore(){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    this->openIAPPage();
    
//    CCLayer* buyLayer = (CCLayer*)BuyLayer::nodeWithID(1);
//    buyLayer->setTag(kBuyLayerTag);
//    this->addChild(buyLayer,100);
    scrollView->setTouchEnabled(false);
}

void CatSelectScene::openIAPPage(){
    
//    this->showIAPPage(1);
}

void CatSelectScene::checkIAP(){
//    bool isShowIAP = GameManager::sharedManager()->isNeedShowIAP();
//    if (isShowIAP) {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        DeviceManager::sharedManager()->goToReview();
//#else
//#endif
//        this->unschedule(schedule_selector(CatSelectScene::checkIAP));
//    }
//    CCLayer* buyLayer = (CCLayer*)this->getChildByTag(kBuyLayerTag);
//    if (buyLayer == NULL) {
//        if (CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") == false) {
//            bool isShowIAP = GameManager::sharedManager()->isNeedShowIAP();
//
//            if(isShowIAP){
//                this->showIAPPage(2);
//            }
//            if (GameManager::sharedManager()->iapDisplayCount >= 2) {
//                this->unschedule(schedule_selector(CatSelectScene::checkIAP));
//            }
//        }
//    }
}

//void CatSelectScene::showIAPPage(int _index){
//    CCPoint center = GameManager::getCenter();
//
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//
//    CCLayer* buyLayer = (CCLayer*)this->getChildByTag(kBuyLayerTag);
//    if (buyLayer == NULL) {
//        SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        buyLayer = (CCLayer*)BuyLayer::nodeWithID(_index);
//#else
//        buyLayer = (CCLayer*)BuyPage::nodeWithID(_index);
//        buyLayer->setInitPageIndex(15);
//#endif
//        buyLayer->setTag(kBuyLayerTag);
//        this->addChild(buyLayer, 100);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        BuyLayer::setPageIndex(15);
//#else
//        BuyPage::setPageIndex(15);
//#endif
//        CCLayerColor *blacklayer = CCLayerColor::create(ccc4(0, 0, 0, 180), winSize.width, winSize.height);
//        blacklayer->ignoreAnchorPointForPosition(false);
//        blacklayer->setPosition(center);
//        buyLayer->addChild(blacklayer,-1);
//
//    }
//}
void CatSelectScene::goToShowInterstitial() {
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") == false){
        GameManager::sharedManager()->showInterstitial();
    }

}

void CatSelectScene::goHome(){
    SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");
    CCSprite* homeBtn = (CCSprite*)this->getChildByTag(kHomeBtnTag);
    if (homeBtn != NULL) {
        homeBtn->stopAllActions();
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    DeviceManager::sharedManager()->setTrack("Cat Dressup Duration");
#else
#endif
    this->goToShowInterstitial();
    this->unschedule(schedule_selector(CatSelectScene::checkIAP));
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, BeginScene::scene(), ccWHITE));
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ShiningScene::sceneWithId(kCatDressTag+1), ccWHITE));
}

void CatSelectScene::warningGameMenu(){
    CCSprite* bathBtn = (CCSprite*)this->getChildByTag(kBathBtnTag);
    CCSprite* dressBtn = (CCSprite*)this->getChildByTag(kDressBtnTag);
    CCSprite* clipBtn = (CCSprite*)this->getChildByTag(kClipBtnTag);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    
    if (bathBtn != NULL) {
        
        CCScaleTo* scaleTo = CCScaleTo::create(0.2, 1.2);
        CCScaleTo* reScaleTo = CCScaleTo::create(0.2, 1.0);
        CCSequence* sequence = CCSequence::createWithTwoActions(scaleTo, reScaleTo);
        CCRepeat* repeat = CCRepeat::create(sequence, 2);
        bathBtn->runAction(repeat);
    }
    if (dressBtn != NULL) {
        
        CCScaleTo* scaleTo = CCScaleTo::create(0.2, 1.2);
        CCScaleTo* reScaleTo = CCScaleTo::create(0.2, 1.0);
        CCSequence* sequence = CCSequence::createWithTwoActions(scaleTo, reScaleTo);
        CCRepeat* repeat = CCRepeat::create(sequence, 2);
        dressBtn->runAction(repeat);
    }
    if (clipBtn != NULL) {
        
        CCScaleTo* scaleTo = CCScaleTo::create(0.2, 1.2);
        CCScaleTo* reScaleTo = CCScaleTo::create(0.2, 1.0);
        CCSequence* sequence = CCSequence::createWithTwoActions(scaleTo, reScaleTo);
        CCRepeat* repeat = CCRepeat::create(sequence, 2);
        clipBtn->runAction(repeat);
    }
}

void CatSelectScene::resetTouchScroll(){
    scrollView->setTouchEnabled(true);
}



void CatSelectScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();

    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

    CCSprite* bathBtn = (CCSprite*)this->getChildByTag(kBathBtnTag);
    CCSprite* dressBtn = (CCSprite*)this->getChildByTag(kDressBtnTag);
    CCSprite* clipBtn = (CCSprite*)this->getChildByTag(kClipBtnTag);
    CCSprite* homeBtn = (CCSprite*)this->getChildByTag(kHomeBtnTag);
//    CCLayer* buyLayer = (CCLayer*)this->getChildByTag(kBuyLayerTag);
//    if (buyLayer == NULL) {
        if (bathBtn != NULL && bathBtn->boundingBox().containsPoint(location)) {
            this->unschedule(schedule_selector(CatSelectScene::checkIAP));
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchButton.mp3");
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.8, BathScene::sceneWithID(_curCatTag+1), ccWHITE));
        }
        if (dressBtn != NULL && dressBtn->boundingBox().containsPoint(location)){
            CCSprite* lock = (CCSprite*)dressBtn->getChildByTag(kLockTag);
            if (lock == NULL) {
                CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.8, DressScene::sceneWithID(_curCatTag+1), ccWHITE));
            }else{
                GameManager::sharedManager()->CatIndex = _curCatTag;
                GameManager::sharedManager()->showReward();
            }
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchButton.mp3");
        }
        if (clipBtn != NULL && clipBtn->boundingBox().containsPoint(location)){
            this->unschedule(schedule_selector(CatSelectScene::checkIAP));
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchButton.mp3");
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.8, ClipScene::sceneWithID(_curCatTag+1), ccWHITE));
        }
        if (homeBtn != NULL && homeBtn->boundingBox().containsPoint(location) && isTouchHome == false) {
            isTouchHome = true;
            CCScaleTo* scaleBy = CCScaleTo::create(0.1, 1.2);
            CCScaleTo* rescaleBy = CCScaleTo::create(0.1, 1.0);
            CCSequence* seqScale = CCSequence::createWithTwoActions(scaleBy, rescaleBy);
            homeBtn->runAction(CCSequence::createWithTwoActions(seqScale, CCCallFunc::create(this, callfunc_selector(CatSelectScene::goHome))));
            //        touchSprite = homeBtn;
        }

        CCLayer* scrollLayer = (CCLayer*)scrollView->getChildByTag(kScrollLayerTag);
        CCPoint scrollPoint = scrollLayer->convertToNodeSpace(location);
        for (int i = 0; i < 13; i++) {
            CCSprite* cat = (CCSprite*)scrollLayer->getChildByTag(i+kCatTag);
            if (cat != NULL && cat->boundingBox().containsPoint(scrollPoint)) {
                touchSprite = cat;
                scrollInitX = location.x;
            }
        }
    //导量
    if (bt_firstword != NULL && bt_firstword->boundingBox().containsPoint(location)){

        SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

        GameManager::sharedManager()->otherGame(3);
    }
    if (bt_shapepuzzle != NULL && bt_shapepuzzle->boundingBox().containsPoint(location)){
        SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

        GameManager::sharedManager()->otherGame(2);
    }
    if (bt_wordblock != NULL && bt_wordblock->boundingBox().containsPoint(location)){

        SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

        GameManager::sharedManager()->otherGame(1);
    }
    if (bt_wordbreak != NULL && bt_wordbreak->boundingBox().containsPoint(location)){

        SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

        GameManager::sharedManager()->otherGame(0);
    }
    if (bt_Jorland != NULL && bt_Jorland->boundingBox().containsPoint(location)){

        SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

        GameManager::sharedManager()->otherGame(4);
    }
    if (bt_Match != NULL && bt_Match->boundingBox().containsPoint(location)){

        SimpleAudioEngine::sharedEngine()->playEffect("universal/pressBt.mp3");

        GameManager::sharedManager()->otherGame(5);
    }
//    }

}

void CatSelectScene::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
    
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCLayer* buyLayer = (CCLayer*)this->getChildByTag(kBuyLayerTag);
    if (buyLayer == NULL) {
        
        double disX = fabs(scrollInitX-location.x);
        
        if (scrollView!=NULL && scrollView->boundingBox().containsPoint(location) && disX > 50.00) {
            this->removeGameMenu();
            touchSprite = NULL;
        }
    }
}

void CatSelectScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
    
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCLayer* buyLayer = (CCLayer*)this->getChildByTag(kBuyLayerTag);
    if (buyLayer == NULL) {
        if (isTouchHome == false && touchSprite == NULL) {
            
            this->adjustScrollView();
        }else if(touchSprite != NULL){
            this->warningGameMenu();
            CCSprite* lock = (CCSprite*)touchSprite->getChildByTag(kLockTag);
            if (lock != NULL) {
                this->goInStore();
            }
            touchSprite = NULL;
        }
    }
    
}

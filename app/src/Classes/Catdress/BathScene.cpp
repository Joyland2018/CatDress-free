//
//  BathScene.cpp
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-3.
//
//

#include "BathScene.h"
#include "GameManager.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "BuyPage.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif
enum{
    kSoapTag = 10,
    kHotSwitchTag = 11,
    kColdSwitchTag = 12,
    kBrushTag = 13,
    kHairDryerTag = 14,
    kBathBottleTag = 15,
    kHairBottleTag = 16,
    kShowerTag = 17,
    kSinkWaterTag = 18,
    kShowerWaterTag = 19,
    kWindTag = 20,
    kCatMouthAnimTag = 77,
    kCatEyeAnimTag = 78,
    kCatLayerTag = 79,
    kTailTag = 80,
    kBodyTag = 81,
    kHeadTag = 82,
    kEyeBgTag = 83,
    kEyeLTag = 84,
    kEyeRTag = 85,
    kMouthTag = 86,
    kHeadWaterTag = 87,
    kBodyWaterTag = 88,
    kHeadFoamTag = 89,
    kBodyFoamTag = 90,
    kBodyDirtyTag = 999,
    kBubbleTag = 100,
    kHomeBtnTag = 9999,
    kBehindWaterTag = 5000,
    kFrontWaterTag = 6000,
    kClickTag = 9999999,
};

CCScene* BathScene::sceneWithID(int _catID){
    CCScene* scene = CCScene::create();
    
    BathScene* layer = BathScene::nodeWithID(_catID);
    
    scene->addChild(layer);
    
    return scene;
}

BathScene* BathScene::nodeWithID(int _animalID){
    BathScene* layer = new BathScene();
    if (layer->initWithID(_animalID)) {
        layer->autorelease();
        
        return layer;
    }else {
        return NULL;
    }
}

bool BathScene::initWithID(int _animalID){
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bath/waterAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bath/bubblePool.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bath/smallBubbleBreak.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bath/poolWaterAnim.plist");
    
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
    
    CCDictionary* selectInfo = CatDressManager::sharedManager()->getDictionary("selectInformation.plist", NULL);
    
    animalTag = selectInfo->valueForKey(CCString::createWithFormat("select%d",_animalID)->getCString())->intValue();
    curCatTag = _animalID;
    
    CCDictionary* catPlist = CatDressManager::sharedManager()->getDictionary("bath/catInformation.plist", NULL);
    CCDictionary* catInfo = CatDressManager::sharedManager()->getDictionary(CCString::createWithFormat("cat%d",animalTag)->getCString(), catPlist);
    
    eyeLInPos = CatDressManager::sharedManager()->getPos("lEyeInPos", catInfo);
    eyeRInPos = CatDressManager::sharedManager()->getPos("rEyeInPos", catInfo);
    eyeRadius = catInfo->valueForKey("radius")->intValue();
    
    isOpenHot = false;
    isOpenCold = false;
    isRotateHot = false;
    isRotateCold = false;
    isTouchedBath = false;
    isTouchedHair = false;
    isRunBrush = false;
    isCanFoam = false;
    isTouchHome = false;
    isWaterToPool = false;
    isDryer = false;
    poolAnimTag = 2;
    
    bubbleArray = CCArray::create();
    bubbleArray->retain();
//    foamArray = CCArray::create();
//    foamArray->retain();
    
    bubbleTag = 0;
    catAnimTag = 0;
    catEyeAnimTag = 0;
    catMouthAnimTag = 0;
    brushNum = 0;
    brushFoamCount = 0;
    
    touchSprite = NULL;

    CCSprite* background = CCSprite::create("background/bath_background.png");
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background);
    if (GameManager::sharedManager()->isIphoneX()) {
        background->setScale(1.3);
    }
    
    CCSprite* bathPool = CCSprite::create("bath/bathPool.png");
    bathPool->setPosition(ccp(leftBottom.x+winSize.width*0.507, leftBottom.y+winSize.height*0.224));
    bathPool->setScale(0.8);
    this->addChild(bathPool);
    
    CCSprite* behindWater = CCSprite::createWithSpriteFrameName("behindWater_0001.png");
    behindWater->setPosition(ccp(leftBottom.x+winSize.width/2,leftBottom.y+winSize.height*0.225));
    behindWater->setTag(kBehindWaterTag);
    behindWater->setScale(0.8);
    this->addChild(behindWater);
    
//    CCLayer* catLayer = (CCLayer*)GameManager::sharedManager()->getCCBNode(CCString::createWithFormat("ccbi/cat/cat%d.ccbi",animalTag)->getCString(), NULL, NULL);
    CCLayer* catLayer = CatDressManager::sharedManager()->getCatSprite(animalTag,eyeLInPos,eyeRInPos);
    if (catLayer != NULL) {
        
        catLayer->setScale(0.8);
        catLayer->setPosition(ccp(leftBottom.x, leftBottom.y-winSize.height/10));
        catLayer->setTag(kCatLayerTag);
        this->addChild(catLayer);
        
        CCSprite* head = (CCSprite*)catLayer->getChildByTag(kHeadTag);
        CCSprite* body = (CCSprite*)catLayer->getChildByTag(kBodyTag);

        CCSprite* mouth = (CCSprite*)head->getChildByTag(kMouthTag);
        mouth->setZOrder(5);
        
        CCSprite* bodyDirty = CCSprite::create("bath/dirty.png");
        bodyDirty->setPosition(ccp(133, 159));
        bodyDirty->setTag(kBodyDirtyTag);
        body->addChild(bodyDirty);
        
        CCSprite* headWater = CCSprite::create("bath/headWater.png");
        headWater->setPosition(ccp(head->getContentSize().width*0.5, head->getContentSize().height*0.868-50));
        headWater->setAnchorPoint(ccp(0.5, 1));
        headWater->setTag(kHeadWaterTag);
        headWater->setOpacity(0);
        head->addChild(headWater);
        
        CCSprite* bodyWater = CCSprite::create("bath/bodyWater.png");
        bodyWater->setPosition(ccp(140, 160));
        bodyWater->setTag(kBodyWaterTag);
        bodyWater->setOpacity(0);
        body->addChild(bodyWater);
        
        CCSprite* headFoam = CCSprite::create("bath/headFoam.png");
        headFoam->setPosition(ccp(head->getContentSize().width*0.5, head->getContentSize().height*0.96));
        headFoam->setAnchorPoint(ccp(0.5, 1));
        headFoam->setOpacity(0);
        headFoam->setTag(kHeadFoamTag);
        head->addChild(headFoam);
        
        CCDictionary* foamInfo = CatDressManager::sharedManager()->getDictionary("bath/foamInformation.plist", NULL);
        
        foamMax = foamInfo->count();
        
        for (int i = 0; i < foamInfo->count(); i++) {
            CCSprite* bodyFoam = CCSprite::create("bath/bodyFoam.png");
            
            bodyFoam->setPosition(CatDressManager::sharedManager()->getPos(CCString::createWithFormat("foam%d",i+1)->getCString(), foamInfo));
            bodyFoam->setTag(kBodyFoamTag+i);
            bodyFoam->setOpacity(0);
            body->addChild(bodyFoam);
//            foamArray->addObject(bodyFoam);
        }
    }
    
    CCSprite* bathWater = CCSprite::createWithSpriteFrameName("frontWater_0001.png");
    bathWater->setPosition(ccp(leftBottom.x+winSize.width/2, leftBottom.y+winSize.height*0.225));
    bathWater->setTag(kFrontWaterTag);
    bathWater->setScale(0.8);
    this->addChild(bathWater,4);
    
    CCSprite* bathtub = CCSprite::create("bath/bathtub.png");
//    if (winSize.width == 1363) {
    
        bathtub->setPosition(ccp(leftBottom.x+winSize.width*0.507, leftBottom.y+winSize.height*0.224));
//    }else if (winSize.width == 1152){
//        
//        bathtub->setPosition(ccp(winSize.width*0.507, winSize.height*0.224));
//    }else{
//    
//        bathtub->setPosition(ccp(winSize.width*0.50, winSize.height*0.224));
//    }
    bathtub->setScale(0.8);
    this->addChild(bathtub,4);
    
    CCSprite* shower = CCSprite::create("bath/shower.png");
    shower->setPosition(ccp(leftBottom.x+winSize.width/2, leftBottom.y+winSize.height*0.91-30));
    shower->setTag(kShowerTag);
    shower->setScale(1.3);
    this->addChild(shower,2);
    
    CCSprite* faucet = CCSprite::create("bath/faucet.png");
    faucet->setPosition(ccp(leftBottom.x+winSize.width/2+9, leftBottom.y+winSize.height*0.16));
    faucet->setScale(0.8);
    this->addChild(faucet,5);
    
    CCSprite* hotSwitch = CCSprite::create("bath/hotSwitch.png");
    hotSwitch->setPosition(ccp(leftBottom.x+winSize.width/2-(51*0.8), leftBottom.y+winSize.height*0.11));
    hotSwitch->setTag(kHotSwitchTag);
    hotSwitch->setScale(0.8);
    this->addChild(hotSwitch,5);
    
    CCSprite* coldSwitch = CCSprite::create("bath/coldSwitch.png");
    coldSwitch->setPosition(ccp(leftBottom.x+winSize.width/2+(72*0.8), leftBottom.y+winSize.height*0.11));
    coldSwitch->setTag(kColdSwitchTag);
    coldSwitch->setScale(0.8);
    this->addChild(coldSwitch,5);
    
    CCSprite* soap = CCSprite::create("bath/soap.png");
    soap->setPosition(ccp(leftBottom.x+winSize.width/2-(195*0.8), leftBottom.y+winSize.height*0.12));
    soap->setTag(kSoapTag);
    soap->setScale(0.8);
    this->addChild(soap,8);
    
    CCSprite* soapBox = CCSprite::create("bath/soapbox.png");
    soapBox->setPosition(ccp(leftBottom.x+winSize.width/2-(194*0.8), leftBottom.y+winSize.height*0.09));
    soapBox->setScale(0.8);
    this->addChild(soapBox,9);
    
    CCSprite* brush = CCSprite::create("bath/brush.png");
    brush->setPosition(ccp(leftBottom.x+winSize.width/2-(360*0.8), leftBottom.y+winSize.height*0.12));
    brush->setTag(kBrushTag);
    brush->setScale(0.8);
    this->addChild(brush,10);
    
    brushInPos = brush->getPosition();
    
    CCSprite* hairDryer = CCSprite::create("bath/hairDryer.png");
    hairDryer->setPosition(ccp(leftBottom.x+winSize.width*0.86, leftBottom.y+winSize.height*0.51));
    hairDryer->setAnchorPoint(ccp(0.12, 0.7));
    hairDryer->setTag(kHairDryerTag);
    hairDryer->setScale(0.8);
    this->addChild(hairDryer,10);
    

    
    CCSprite* homeBtn = CCSprite::create("universal/back.png");
    homeBtn->setPosition(ccp(leftBottom.x+winSize.width/16, leftBottom.y+winSize.height*11/12));
    homeBtn->setTag(kHomeBtnTag);
//    homeBtn->setScale(0.8);
    this->addChild(homeBtn);
    
    CCSprite* clickLayer = CCSprite::create("ui/click.png");
    clickLayer->setPosition(ccp(leftBottom.x+winSize.width/2, leftBottom.y+winSize.height/2));
    clickLayer->setTag(kClickTag);
    clickLayer->setScale(0.8);
    this->addChild(clickLayer,5);
    
//    this->schedule(schedule_selector(BathScene::catAnimation),3);
//    this->schedule(schedule_selector(BathScene::catEyeAnim),4);
//    this->schedule(schedule_selector(BathScene::catMouthAnim),5);
    
    this->setTouchEnabled(true);
    
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/background/bathBg.mp3", true);
    
    return true;
}

void BathScene::onEnter() {
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
    CCLayer::onEnter();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bath/bottleAnim.plist");
    CCSprite* bathBottle = CCSprite::createWithSpriteFrameName("bathBottle_0001.png");
    bathBottle->setPosition(ccp(leftBottom.x+winSize.width/2+(338*0.8), leftBottom.y+winSize.height*0.19));
    bathBottle->setTag(kBathBottleTag);
    bathBottle->setScale(0.8);
    this->addChild(bathBottle,4);

    CCSprite* hairBottle = CCSprite::createWithSpriteFrameName("hairBottle_0001.png");
    hairBottle->setPosition(ccp(leftBottom.x+winSize.width/2+(202*0.8), leftBottom.y+winSize.height*0.19));
    hairBottle->setTag(kHairBottleTag);
    hairBottle->setScale(0.8);
    this->addChild(hairBottle,4);
}

BathScene::BathScene(){
    
}

BathScene::~BathScene(){
    bubbleArray->removeAllObjects();
    bubbleArray->release();
//    foamArray->removeAllObjects();
//    foamArray->release();
    this->stopAllActions();
    this->removeAllChildrenWithCleanup(true);
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("bath/waterAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("bath/bottleAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("bath/bubblePool.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("bath/smallBubbleBreak.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("bath/poolWaterAnim.plist");
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void BathScene::goToShowInterstitial() {
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") == false){
        GameManager::sharedManager()->showInterstitial();
    }

}

void BathScene::catAnimation(cocos2d::CCTime *dt){
    CCLayer* catLayer = (CCLayer*)this->getChildByTag(kCatLayerTag);
    
    if (catLayer != NULL) {
        CCBAnimationManager* animManager = (CCBAnimationManager*)catLayer->getUserObject();
        if (catAnimTag == 0) {
            animManager->runAnimationsForSequenceNamed("head");
            
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/shakeHead.mp3");
            catAnimTag++;
        }else{
            animManager->runAnimationsForSequenceNamed("tail");
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/shakeTail.mp3");
            catAnimTag = 0;
        }
    }
}

void BathScene::catEyeAnim(cocos2d::CCTime *dt){
    CCLayer* catLayer = (CCLayer*)this->getChildByTag(kCatLayerTag);
    if (catLayer != NULL) {
        catEyeAnimTag = arc4random()%3+1;
        CCSprite* head = (CCSprite*)catLayer->getChildByTag(kHeadTag);
        CCSprite* eyeBg = (CCSprite*)head->getChildByTag(kEyeBgTag);
        CCSprite* eyeL = (CCSprite*)head->getChildByTag(kEyeLTag);
        CCSprite* eyeR = (CCSprite*)head->getChildByTag(kEyeRTag);
        
        if (eyeBg != NULL && eyeBg->isVisible() == true) {
            eyeBg->setVisible(false);
        }
        if (eyeL != NULL && eyeL->isVisible() == true) {
            eyeL->setVisible(false);
        }
        if (eyeR != NULL && eyeR->isVisible() == true) {
            eyeR->setVisible(false);
        }
        
        CCSprite* catEyeAnim = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("mao%d_yanjing_%d_0001.png",animalTag,catEyeAnimTag)->getCString());
        catEyeAnim->setPosition(eyeBg->getPosition());
        catEyeAnim->setTag(kCatEyeAnimTag);
        head->addChild(catEyeAnim);
        
        CCAnimate* eyeAnim = CatDressManager::sharedManager()->getSpriteAnimate(0, 3, CCString::createWithFormat("mao%d_yanjing_%d",animalTag,catEyeAnimTag)->getCString(), false);
        catEyeAnim->runAction(CCSequence::createWithTwoActions(eyeAnim, CCCallFunc::create(this, callfunc_selector(BathScene::completeEyeAnim))));
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/wink.mp3");
    }
}

void BathScene::catMouthAnim(cocos2d::CCTime *dt){
    CCLayer* catLayer = (CCLayer*)this->getChildByTag(kCatLayerTag);
    if (catLayer != NULL) {
        catMouthAnimTag = arc4random()%4+2;
        CCSprite* head = (CCSprite*)catLayer->getChildByTag(kHeadTag);
        CCSprite* mouth = (CCSprite*)head->getChildByTag(kMouthTag);
        
        if (mouth != NULL && mouth->isVisible() == true) {
            mouth->setVisible(false);
        }
        
        CCSprite* catMouthAnim = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("mao%d_zui_%d_0001.png",animalTag,catMouthAnimTag)->getCString());
        catMouthAnim->setPosition(mouth->getPosition());
        catMouthAnim->setTag(kCatMouthAnimTag);
        head->addChild(catMouthAnim,5);
        
        int framNum = 0;
        
        if (catMouthAnimTag == 2) {
            framNum = 2;
        }else{
            framNum = 1;
        }
        CCSequence* mouthAnimSeq = CCSequence::createWithTwoActions(CCDelayTime::create(1), CCCallFunc::create(this, callfunc_selector(BathScene::completeMouthAnim)));
        
        CCAnimate* mouthAnim = CatDressManager::sharedManager()->getSpriteAnimate(0, framNum, CCString::createWithFormat("mao%d_zui_%d",animalTag,catMouthAnimTag)->getCString(), false);
        catMouthAnim->runAction(CCSequence::createWithTwoActions(mouthAnim, mouthAnimSeq));
        
//        SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mouth%d.mp3",catMouthAnimTag)->getCString());
        if (catMouthAnimTag == 2) {
            SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mp3/cat/cat%d.mp3",curCatTag)->getCString());
        }else if (catMouthAnimTag == 5){
            
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/cat/cat8.mp3");
        }
    }
}

void BathScene::completeEyeAnim(){
    CCLayer* catLayer = (CCLayer*)this->getChildByTag(kCatLayerTag);
    if (catLayer != NULL) {
        CCSprite* head = (CCSprite*)catLayer->getChildByTag(kHeadTag);
        CCSprite* eyeAnim = (CCSprite*)head->getChildByTag(kCatEyeAnimTag);
        CCSprite* eyeBg = (CCSprite*)head->getChildByTag(kEyeBgTag);
        CCSprite* eyeL = (CCSprite*)head->getChildByTag(kEyeLTag);
        CCSprite* eyeR = (CCSprite*)head->getChildByTag(kEyeRTag);
        
        if (eyeAnim != NULL) {
            eyeAnim->stopAllActions();
            eyeAnim->removeFromParentAndCleanup(true);
            eyeAnim = NULL;
        }
        
        if (eyeBg != NULL && eyeBg->isVisible() == false) {
            eyeBg->setVisible(true);
        }
        if (eyeL != NULL && eyeL->isVisible() == false) {
            eyeL->setVisible(true);
        }
        if (eyeR != NULL && eyeR->isVisible() == false) {
            eyeR->setVisible(true);
        }
        
    }
}

void BathScene::completeMouthAnim(){
    CCLayer* catLayer = (CCLayer*)this->getChildByTag(kCatLayerTag);
    if (catLayer != NULL) {
        CCSprite* head = (CCSprite*)catLayer->getChildByTag(kHeadTag);
        CCSprite* mouthAnim = (CCSprite*)head->getChildByTag(kCatMouthAnimTag);
        CCSprite* mouth = (CCSprite*)head->getChildByTag(kMouthTag);
        
        if (mouthAnim != NULL) {
            mouthAnim->stopAllActions();
            mouthAnim->removeFromParentAndCleanup(true);
            mouthAnim = NULL;
        }
        if (mouth != NULL && mouth->isVisible() == false) {
            mouth->setVisible(true);
        }
        
    }
}

void BathScene::eyeMove(cocos2d::CCPoint location){
    CCLayer* catLayer = (CCLayer*)this->getChildByTag(kCatLayerTag);
    if (catLayer != NULL) {
        CCSprite* head = (CCSprite*)catLayer->getChildByTag(kHeadTag);
        CCSprite* eyeL = (CCSprite*)head->getChildByTag(kEyeLTag);
        CCSprite* eyeR = (CCSprite*)head->getChildByTag(kEyeRTag);
        
        location = head->convertToNodeSpace(location);
        
        float dis1 = ccpDistance(location, eyeLInPos);
        float dis2 = ccpDistance(location, eyeRInPos);
        
        eyeL->setPosition(ccp(eyeLInPos.x+eyeRadius/dis1*(location.x-eyeLInPos.x), eyeLInPos.y+eyeRadius/dis1*(location.y-eyeLInPos.y)));
        eyeR->setPosition(ccp(eyeRInPos.x+eyeRadius/dis2*(location.x-eyeRInPos.x), eyeRInPos.y+eyeRadius/dis2*(location.y-eyeRInPos.y)));
    }
}

void BathScene::eyeRevert(){
    CCLayer* catLayer = (CCLayer*)this->getChildByTag(kCatLayerTag);
    if (catLayer != NULL) {
        
        CCSprite* head = (CCSprite*)catLayer->getChildByTag(kHeadTag);
        CCSprite* eyeL = (CCSprite*)head->getChildByTag(kEyeLTag);
        CCSprite* eyeR = (CCSprite*)head->getChildByTag(kEyeRTag);
        
        eyeL->setPosition(eyeLInPos);
        eyeR->setPosition(eyeRInPos);
    }
}

void BathScene::touchSwitch(int _tag){
    CCSprite* anySwitch = (CCSprite*)this->getChildByTag(_tag);
    float rotateAngle = 0;
    switch (_tag) {
        case kHotSwitchTag:
        {
            if (isOpenHot == false) {
                rotateAngle = 180;
            }else{
                rotateAngle = -360;
            }
        }
            break;
        case kColdSwitchTag:
        {
            if (isOpenCold == false) {
                rotateAngle = -180;
            }else{
                rotateAngle = 360;
            }
        }
            break;
        default:
            break;
    }
    CCRotateTo* rotateBy = CCRotateTo::create(0.5, rotateAngle);
    anySwitch->runAction(CCSequence::createWithTwoActions(rotateBy, CCCallFuncND::create(this, callfuncND_selector(BathScene::completeSwitch), (int*)(intptr_t)_tag)));
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/turn.mp3");
}

void BathScene::completeSwitch(CCNode* sender,int _tag){
    switch (_tag) {
        case kHotSwitchTag:
        {
            if (isOpenHot == false) {
                isOpenHot = true;
            }else{
                isOpenHot = false;
            }
            isRotateHot = false;
        }
            break;
        case kColdSwitchTag:
        {
            if (isOpenCold == false) {
                isOpenCold = true;
            }else{
                isOpenCold = false;
            }
            isRotateCold = false;
        }
            break;
        default:
            break;
    }
    this->openSink();
}

void BathScene::showWaterSound(cocos2d::CCNode *sender, int _tag){
    
    SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mp3/bath/water%d.mp3",_tag)->getCString());
}

void BathScene::openSink(){
    CCSprite* sinkWater = (CCSprite*)this->getChildByTag(kSinkWaterTag);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    const char* fileName = NULL;
    CCPoint waterPos = CCPointZero;
    int soundTag = 0;
    if (sinkWater != NULL) {
        sinkWater->stopAllActions();
        sinkWater->removeFromParentAndCleanup(true);
        sinkWater = NULL;
        SimpleAudioEngine::sharedEngine()->unloadEffect("mp3/bath/water2.mp3");
        SimpleAudioEngine::sharedEngine()->unloadEffect("mp3/bath/water1.mp3");
        this->unschedule(schedule_selector(BathScene::showPoolWaterAnim));
    }
    if (isOpenCold == true && isOpenHot == true) {
        fileName = "water2";
        waterPos = CCPoint(winSize.width/2+(63*0.8), winSize.height*0.16);
        soundTag = 2;
    }else if (isOpenCold == true || isOpenHot == true){
        fileName = "water1";
        waterPos = CCPoint(winSize.width/2+(56*0.8), winSize.height*0.16);
        soundTag = 1;
    }
    if (sinkWater == NULL && fileName != NULL) {
        sinkWater = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%s_0001.png",fileName)->getCString());
        sinkWater->setPosition(waterPos);
        sinkWater->setTag(kSinkWaterTag);
        sinkWater->setScale(0.8);
        this->addChild(sinkWater,4);
        CCAnimate* waterAnimate = CatDressManager::sharedManager()->getSpriteAnimate(0, 2, fileName,false);
        CCRepeatForever* repeatFor = CCRepeatForever::create(CCSpawn::createWithTwoActions(waterAnimate, CCCallFuncND::create(this, callfuncND_selector(BathScene::showWaterSound), (int*)(intptr_t)soundTag)));
        sinkWater->runAction(repeatFor);
        if (poolAnimTag <= 4) {
            this->schedule(schedule_selector(BathScene::showPoolWaterAnim),2);
        }
    }
    
}

void BathScene::showPoolWaterAnim(){
    CCSprite* behindWater = (CCSprite*)this->getChildByTag(kBehindWaterTag);
    CCSprite* frontWater = (CCSprite*)this->getChildByTag(kFrontWaterTag);
    if (behindWater != NULL && frontWater != NULL) {
//        CCAnimate* behindAnim = GameManager::sharedManager()->getSpriteAnimate(0, 4, "behindWater", false);
//        CCAnimate* frontAnim = GameManager::sharedManager()->getSpriteAnimate(0, 4, "frontWater", false);
//        behindWater->runAction(behindAnim);
//        frontWater->runAction(frontAnim);
        this->setAnotherFrame(behindWater, CCString::createWithFormat("behindWater_000%d",poolAnimTag)->getCString());
        this->setAnotherFrame(frontWater, CCString::createWithFormat("frontWater_000%d",poolAnimTag)->getCString());
    }
    if (poolAnimTag < 4) {
        poolAnimTag++;
    }else{
        this->unschedule(schedule_selector(BathScene::showPoolWaterAnim));
    }
}

void BathScene::showSpraySound(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/spray.mp3");
}

void BathScene::openShower(){
    CCSprite* showerWater = (CCSprite*)this->getChildByTag(kShowerWaterTag);
    if (showerWater != NULL) {
        SimpleAudioEngine::sharedEngine()->unloadEffect("mp3/bath/spray.mp3");
        showerWater->stopAllActions();
        showerWater->removeFromParentAndCleanup(true);
        showerWater = NULL;
        isDryer = false;
    }else{
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        showerWater = CCSprite::createWithSpriteFrameName("spray_0001.png");
        showerWater->setPosition(ccp(winSize.width/2, winSize.height*0.47-60));
        showerWater->setTag(kShowerWaterTag);
        showerWater->setScale(0.8);
        this->addChild(showerWater,2);
        CCAnimate* sprayAnimate = CatDressManager::sharedManager()->getSpriteAnimate(0, 3, "spray",false);
        CCRepeatForever* repeatFor = CCRepeatForever::create(CCSpawn::createWithTwoActions(sprayAnimate, CCCallFunc::create(this, callfunc_selector(BathScene::showSpraySound))));
        showerWater->runAction(repeatFor);
        
        this->changeBodyWater(false);
        this->changeBodyFoam(true, CCPointZero);
        isCanFoam = false;
        isDryer = true;
    }
}

void BathScene::changeBodyWater(bool isInView){
    CCSprite* catLayer = (CCSprite*)this->getChildByTag(kCatLayerTag);
    CCSprite* catHead = (CCSprite*)catLayer->getChildByTag(kHeadTag);
    CCSprite* catBody = (CCSprite*)catLayer->getChildByTag(kBodyTag);
    CCSprite* headWater = (CCSprite*)catHead->getChildByTag(kHeadWaterTag);
    CCSprite* bodyWater = (CCSprite*)catBody->getChildByTag(kBodyWaterTag);
    
    if (isInView == false) {
        
        if (headWater != NULL && headWater->getOpacity() == 0) {
            headWater->stopAllActions();
            CCFadeIn* fadeIn = CCFadeIn::create(1);
            headWater->runAction(CCSequence::createWithTwoActions(fadeIn, CCCallFuncND::create(this, callfuncND_selector(BathScene::setSpriteVisible), (void*)0)));
        }
        if (bodyWater != NULL && bodyWater->getOpacity() == 0) {
            bodyWater->stopAllActions();
            CCFadeIn* fadeIn = CCFadeIn::create(1);
            bodyWater->runAction(CCSequence::createWithTwoActions(fadeIn, CCCallFuncND::create(this, callfuncND_selector(BathScene::setSpriteVisible), (void*)0)));
        }
    }else{
        if (headWater != NULL && headWater->getOpacity() >= 200) {
            headWater->stopAllActions();
            CCFadeOut* fadeOut = CCFadeOut::create(2);
            headWater->runAction(CCSequence::createWithTwoActions(fadeOut, CCCallFuncND::create(this, callfuncND_selector(BathScene::setSpriteVisible), (void*)1)));
        }
        if (bodyWater != NULL && bodyWater->getOpacity() >= 200) {
            bodyWater->stopAllActions();
            CCFadeOut* fadeOut = CCFadeOut::create(2);
            bodyWater->runAction(CCSequence::createWithTwoActions(fadeOut, CCCallFuncND::create(this, callfuncND_selector(BathScene::setSpriteVisible), (void*)1)));
        }
    }
}

void BathScene::changeBodyFoam(bool isInView,CCPoint location){
    CCSprite* catLayer = (CCSprite*)this->getChildByTag(kCatLayerTag);
    CCSprite* catHead = (CCSprite*)catLayer->getChildByTag(kHeadTag);
    CCSprite* catBody = (CCSprite*)catLayer->getChildByTag(kBodyTag);
    CCSprite* headFoam = (CCSprite*)catHead->getChildByTag(kHeadFoamTag);
    if (isInView == false) {
        CCPoint headPoint = catHead->convertToNodeSpace(location);
        CCPoint bodyPoint = catBody->convertToNodeSpace(location);
        if (headFoam != NULL && headFoam->boundingBox().containsPoint(headPoint) && headFoam->getOpacity() == 0) {
            CCFadeIn* fadeIn = CCFadeIn::create(1);
            headFoam->runAction(CCSequence::createWithTwoActions(fadeIn, CCCallFuncND::create(this, callfuncND_selector(BathScene::setSpriteVisible), (void*)0)));
            
            if (brushFoamCount == 5) {
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/showFoam.mp3");
                brushFoamCount = 0;
            }else{
                brushFoamCount++;
            }
        }
        
        for (int i = 0; i < foamMax; i++) {
            CCSprite* bodyFoam = (CCSprite*)catBody->getChildByTag(kBodyFoamTag+i);
            if (bodyFoam != NULL && bodyFoam->boundingBox().containsPoint(bodyPoint) && bodyFoam->getOpacity() == 0) {
                CCFadeIn* fadeIn = CCFadeIn::create(1);
                bodyFoam->runAction(CCSequence::createWithTwoActions(fadeIn, CCCallFuncND::create(this, callfuncND_selector(BathScene::setSpriteVisible), (void*)0)));
//                foamArray->addObject(bodyFoam);
                if (brushFoamCount == 5) {
                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/showFoam.mp3");
                    brushFoamCount = 0;
                }else{
                    brushFoamCount++;
                }
            }
        }
    }else{
        if (headFoam != NULL && headFoam->getOpacity() >= 100) {
            headFoam->stopAllActions();
            CCFadeOut* fadeOut = CCFadeOut::create(1);
            CCMoveBy* moveBy = CCMoveBy::create(1, ccp(0, -10));
            CCSpawn* spawn = CCSpawn::createWithTwoActions(fadeOut, moveBy);
            CCSpawn* spawnT = CCSpawn::createWithTwoActions(CCCallFuncND::create(this, callfuncND_selector(BathScene::setSpriteInitPos),(int*)(intptr_t)10), CCCallFuncND::create(this, callfuncND_selector(BathScene::setSpriteVisible), (int*)(intptr_t)1));
            headFoam->runAction(CCSequence::createWithTwoActions(spawn, spawnT));
        }
        
        for (int i = 0; i < foamMax; i++) {
            CCSprite* bodyFoam = (CCSprite*)catBody->getChildByTag(kBodyFoamTag+i);
            if (bodyFoam != NULL && bodyFoam->getOpacity() >= 100) {
                bodyFoam->stopAllActions();
                CCFadeOut* fadeOut = CCFadeOut::create(1);
                CCMoveBy* moveBy = CCMoveBy::create(1, ccp(0, -10));
                CCSpawn* spawn = CCSpawn::createWithTwoActions(fadeOut, moveBy);
                CCSpawn* spawnT = CCSpawn::createWithTwoActions(CCCallFuncND::create(this, callfuncND_selector(BathScene::setSpriteInitPos),(int*)(intptr_t)i), CCCallFuncND::create(this, callfuncND_selector(BathScene::setSpriteVisible), (int*)(intptr_t)1));
                bodyFoam->runAction(CCSequence::createWithTwoActions(spawn, spawnT));
            }
        }
    }
}

void BathScene::brushDirty(CCPoint location){
    CCSprite* catLayer = (CCSprite*)this->getChildByTag(kCatLayerTag);
    CCSprite* catBody = (CCSprite*)catLayer->getChildByTag(kBodyTag);
    CCPoint bodyPoint = catBody->convertToNodeSpace(location);
    
    CCSprite* bodyDirty = (CCSprite*)catBody->getChildByTag(kBodyDirtyTag);
    if (bodyDirty != NULL && bodyDirty->boundingBox().containsPoint(bodyPoint) && bodyDirty->getOpacity() == 255) {
        CCFadeTo* fadeOut = CCFadeTo::create(1.0, 0);
        bodyDirty->runAction(CCSequence::createWithTwoActions(fadeOut, CCCallFuncN::create(this, callfuncN_selector(BathScene::removeSelf))));
    }
}

void BathScene::setSpriteVisible(cocos2d::CCNode *sender, int _tag){
    CCSprite* sprite = (CCSprite*)sender;
    switch (_tag) {
        case 0:
        {
            sprite->stopAllActions();
            sprite->setOpacity(255);
        }
            break;
        case 1:
        {
            sprite->stopAllActions();
            sprite->setOpacity(0);
        }
            break;
        default:
            break;
    }
}

void BathScene::setSpriteInitPos(cocos2d::CCNode *sender, int _tag){
    sender->setPosition(ccp(sender->getPositionX(), sender->getPositionY()+10));
//    if (_tag != 10) {
//        foamArray->removeObjectAtIndex(_tag);
//    }
}

void BathScene::showHairDryerSound(){
    
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/hairDryer.mp3");
}

void BathScene::openHairDryer(bool isTurnOn){
    CCSprite* hairDryer = (CCSprite*)this->getChildByTag(kHairDryerTag);
    CCSprite* wind = (CCSprite*)hairDryer->getChildByTag(kWindTag);
    if (hairDryer != NULL) {

        if (isTurnOn == true && wind == NULL) {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bath/windAnim.plist");
            wind = CCSprite::createWithSpriteFrameName("wind_0001.png");
            wind->setPosition(ccp(hairDryer->getContentSize().width*(-0.14), hairDryer->getContentSize().height*0.27));
            wind->setTag(kWindTag);
            hairDryer->addChild(wind,-1);
            CCAnimate* windAnimate = CatDressManager::sharedManager()->getSpriteAnimate(0, 3, "wind",false);
            CCRepeatForever* repeatFor = CCRepeatForever::create(CCSpawn::createWithTwoActions(windAnimate, CCCallFunc::create(this, callfunc_selector(BathScene::showHairDryerSound))));
            wind->runAction(repeatFor);
            if (isDryer == false) {
                this->changeBodyWater(true);
            }
        }else{
            SimpleAudioEngine::sharedEngine()->unloadEffect("mp3/bath/hairDryer.mp3");
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/returnDryer.mp3");
            if (wind != NULL){
                wind->stopAllActions();
                wind->removeFromParentAndCleanup(true);
                wind = NULL;
            }
            CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("bath/windAnim.plist");
        }
    }
}

void BathScene::touchBottle(int _tag){
    CCSprite* anyBottle = (CCSprite*)this->getChildByTag(_tag);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint arrivePoint = CCPointZero;
    float rotateAngle = 0;
    const char* fileName = NULL;
    switch (_tag) {
        case kBathBottleTag:
        {
            arrivePoint = ccp(winSize.width/2+(338*0.8), winSize.height*0.31);
            fileName = "bathBottle";
            rotateAngle = -35;
        }
            break;
        case kHairBottleTag:
        {
            arrivePoint = ccp(winSize.width/2+(82*0.8), winSize.height*0.57);
            fileName = "hairBottle";
            rotateAngle = -45;
        }
            break;
        default:
            break;
    }
    CCMoveTo* moveTo = CCMoveTo::create(0.3, arrivePoint);
    CCMoveTo* reMoveTo = CCMoveTo::create(0.3, anyBottle->getPosition());
    CCRotateTo* rotateTo = CCRotateTo::create(0.3, rotateAngle);
    CCRotateTo* reRotateTo = CCRotateTo::create(0.3, 0);
    CCAnimate* bottleAnimate = CatDressManager::sharedManager()->getSpriteAnimate(0, 2, fileName,true);
    CCSpawn* spawnOne = CCSpawn::createWithTwoActions(moveTo, rotateTo);
    CCSpawn* spawnTwo = CCSpawn::createWithTwoActions(bottleAnimate, CCCallFuncND::create(this, callfuncND_selector(BathScene::showBottleWater), (int*)(intptr_t)_tag));
    CCSpawn* spawnThree = CCSpawn::createWithTwoActions(reMoveTo, CCSequence::createWithTwoActions(reRotateTo, CCCallFuncND::create(this, callfuncND_selector(BathScene::completedBottleAction), (int*)(intptr_t)_tag)));
    
    anyBottle->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(spawnOne, spawnTwo),CCSequence::createWithTwoActions(CCDelayTime::create(0.5), spawnThree)));
}

void BathScene::completedBottleAction(CCNode* sender, int _tag){
    switch (_tag) {
        case kBathBottleTag:
            isTouchedBath = false;
            break;
        case kHairBottleTag:
            isTouchedHair = false;
            break;
        default:
            break;
    }
}

void BathScene::showBottleWater(cocos2d::CCNode *sender, int _tag){
    CCSprite* bottleWater = CCSprite::createWithSpriteFrameName("dropWater.png");
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    switch (_tag) {
        case kBathBottleTag:
        {
            bottleWater->setPosition(ccp(winSize.width/2+(266*0.8), winSize.height*0.37));
        }
            break;
        case kHairBottleTag:
        {
            bottleWater->setPosition(ccp(winSize.width/2+(10*0.8), winSize.height*0.61));
        }
            break;
        default:
            break;
    }
    bottleWater->setScale(0.8);
    this->addChild(bottleWater,4);
    
    CCMoveBy* moveBy = CCMoveBy::create(0.2, ccp(0, -50));
    bottleWater->runAction(CCSequence::createWithTwoActions(moveBy, CCCallFuncND::create(this, callfuncND_selector(BathScene::completeBottle), (int*)(intptr_t)_tag)));
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/drop.mp3");
}

void BathScene::completeBottle(cocos2d::CCNode *sender, int _tag){
    if (sender != NULL) {
        sender->stopAllActions();
        sender->removeFromParentAndCleanup(true);
        sender = NULL;
        
        switch (_tag) {
            case kBathBottleTag:
            {
                this->schedule(schedule_selector(BathScene::showBubble), 0.5);
            }
                break;
            case kHairBottleTag:
            {
                this->warningBrush();
                if (isCanFoam == false) {
                    isCanFoam = true;
                }
            }
                break;
            default:
                break;
        }
    }
}

void BathScene::warningBrush(){
    if (isRunBrush == false) {
        isRunBrush = true;
        
        CCSprite* brush = (CCSprite*)this->getChildByTag(kBrushTag);
        CCJumpBy* jumpBy = CCJumpBy::create(0.6, CCPointZero, 60, 1);
        CCRepeatForever* repeatFor = CCRepeatForever::create(CCSequence::createWithTwoActions(CCSpawn::createWithTwoActions(jumpBy, CCCallFunc::create(this, callfunc_selector(BathScene::warningBrushSound))), CCDelayTime::create(1)));
        
        brush->runAction(repeatFor);
    }
}

void BathScene::warningBrushSound(){
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/returnBrush.mp3");
}

void BathScene::showBubble(){
    CCDictionary* bubbleInfo = CatDressManager::sharedManager()->getDictionary("bath/bubbleInfo.plist", NULL);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    for (int i = 0; i < bubbleInfo->count(); i++) {
        CCDictionary* bubblePosInfo = CatDressManager::sharedManager()->getDictionary(CCString::createWithFormat("bubble%d",bubbleTag+1)->getCString(), bubbleInfo);
        CCSprite* bubble = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("bubble%d.png",bubbleTag+1)->getCString());
        CCPoint bubbleInPos = CatDressManager::sharedManager()->getPos("initPos", bubblePosInfo);
        bubble->setPosition(ccp(winSize.width*bubbleInPos.x, winSize.height*bubbleInPos.y));
        bubble->setTag(kBubbleTag+bubbleTag);
    bubble->setScale(0.8);
        this->addChild(bubble,2);
        
        this->bubbleMove(bubble, bubbleTag);
    
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/bubbleUp.mp3");
//    }
}

void BathScene::bubbleMove(CCNode* sender, int _tag){
    CCDictionary* bubbleInfo = CatDressManager::sharedManager()->getDictionary("bath/bubbleInfo.plist", NULL);
    CCDictionary* bubblePosInfo = CatDressManager::sharedManager()->getDictionary(CCString::createWithFormat("bubble%d",_tag+1)->getCString(), bubbleInfo);
    
    ccBezierConfig bezier;
    bezier.controlPoint_1 = CatDressManager::sharedManager()->getPos("cp1Pos", bubblePosInfo);
    bezier.controlPoint_2 = CatDressManager::sharedManager()->getPos("cp2Pos", bubblePosInfo);
    bezier.endPosition = CatDressManager::sharedManager()->getPos("endPos", bubblePosInfo);
    
    CCBezierBy* bezierBy = CCBezierBy::create(2, bezier);
    CCRepeat* repeat = CCRepeat::create(bezierBy, 2);
    
    float bubbleDelay = 0;
    sender->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(CCDelayTime::create(bubbleDelay), repeat), CCCallFuncN::create(this, callfuncN_selector(BathScene::removeSelf))));
    bubbleArray->addObject(sender);
    if (bubbleTag == 6) {
        bubbleTag = 0;
        this->unschedule(schedule_selector(BathScene::showBubble));
    }else{
        bubbleTag++;
    }
}

void BathScene::removeSelf(cocos2d::CCNode *sender){
    if (sender != NULL) {
        sender->stopAllActions();
        bubbleArray->removeObject(sender);
        sender->removeFromParentAndCleanup(true);
        sender = NULL;
    }
}

void BathScene::setAnotherFrame(cocos2d::CCSprite *pSprite, const char *pFileName){
    CCString* imageName = CCString::createWithFormat("%s.png",pFileName);
    CCSpriteFrame* sprFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName->getCString());
    pSprite->setDisplayFrame(sprFrame);
}

void BathScene::showBubbleBreak(cocos2d::CCNode *sender){
    CCAnimate* bubbleAnim = CatDressManager::sharedManager()->getSpriteAnimate(0, 7, "bubbleBreak", false);
    sender->runAction(CCSequence::createWithTwoActions(bubbleAnim, CCCallFuncN::create(this, callfuncN_selector(BathScene::removeSelf))));
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/bubbleBreak.mp3");
}

void BathScene::returnLastScene(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.8, CatSelectScene::sceneWithID(curCatTag-1),ccWHITE));
}

void BathScene::clickCatSound(){
    int ranCatSound = arc4random()%2+1;
    SimpleAudioEngine::sharedEngine()->unloadEffect(CCString::createWithFormat("mp3/cat/cat%d.mp3",curCatTag)->getCString());
    SimpleAudioEngine::sharedEngine()->unloadEffect("mp3/standby/standbySound.mp3");
    if (ranCatSound == 1) {
        SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("cat%d.mp3",curCatTag)->getCString());
    }else{
        
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/cat/cat8.mp3");
    }
}

void BathScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
    
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    this->eyeMove(location);
    
    CCSprite* soap = (CCSprite*)this->getChildByTag(kSoapTag);
    CCSprite* brush = (CCSprite*)this->getChildByTag(kBrushTag);
    CCSprite* hairDryer = (CCSprite*)this->getChildByTag(kHairDryerTag);
    CCSprite* hotSwitch = (CCSprite*)this->getChildByTag(kHotSwitchTag);
    CCSprite* coldSwitch = (CCSprite*)this->getChildByTag(kColdSwitchTag);
    CCSprite* shower = (CCSprite*)this->getChildByTag(kShowerTag);
    CCSprite* bathBottle = (CCSprite*)this->getChildByTag(kBathBottleTag);
    CCSprite* hairBottle = (CCSprite*)this->getChildByTag(kHairBottleTag);
    CCSprite* homeBtn = (CCSprite*)this->getChildByTag(kHomeBtnTag);
    if (soap != NULL && soap->boundingBox().containsPoint(location)) {
        touchSpriteInPos = soap->getPosition();
        soap->setPosition(location);
        touchSprite = soap;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/takeSoap.mp3");
    }else if (brush != NULL && brush->boundingBox().containsPoint(location)) {
        brush->stopAllActions();
        touchSpriteInPos = brush->getPosition();
        brush->setPosition(location);
        touchSprite = brush;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/jumpBrush.mp3");
        isRunBrush = false;
    }else if (hairDryer != NULL && hairDryer->boundingBox().containsPoint(location)){
        this->openHairDryer(true);
        touchSpriteInPos = hairDryer->getPosition();
        hairDryer->setPosition(location);
        touchSprite = hairDryer;
    }else if (hotSwitch != NULL && hotSwitch->boundingBox().containsPoint(location) && isRotateHot == false){
        isRotateHot = true;
        this->touchSwitch(kHotSwitchTag);
    }else if (coldSwitch != NULL && coldSwitch->boundingBox().containsPoint(location) && isRotateCold == false){
        isRotateCold = true;
        this->touchSwitch(kColdSwitchTag);
    }else if (shower != NULL && shower->boundingBox().containsPoint(location)){
        this->openShower();
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/touchShower.mp3");
    }else if (bathBottle != NULL && bathBottle->boundingBox().containsPoint(location) && isTouchedBath == false){
        isTouchedBath = true;
        this->touchBottle(kBathBottleTag);
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/takeBottle.mp3");
    }else if (hairBottle != NULL && hairBottle->boundingBox().containsPoint(location) && isTouchedHair == false){
        isTouchedHair = true;
        this->touchBottle(kHairBottleTag);
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/takeBottle.mp3");
    }else if (homeBtn != NULL && homeBtn->boundingBox().containsPoint(location) && isTouchHome == false){
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        //            homeBtn->setScale(1.2);
        //            touchSprite = homeBtn;
        //            SimpleAudioEngine::sharedEngine()->playEffect("touchItem.mp3");
        //插页广告
        this->goToShowInterstitial();

        homeBtn->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(BathScene::returnLastScene))));
        //            _gameScene->selectMenuBtn(158);
        isTouchHome = true;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchButton.mp3");
    }
    
    for (int i = 0; i < bubbleArray->count(); i++) {
        CCSprite* bubble = (CCSprite*)bubbleArray->objectAtIndex(i);
        if (bubble != NULL && bubble->boundingBox().containsPoint(location)) {
            this->showBubbleBreak(bubble);
        }
    }
    CCSprite* clickLayer = (CCSprite*)this->getChildByTag(kClickTag);
    if (clickLayer != NULL && clickLayer->boundingBox().containsPoint(location)) {
        this->clickCatSound();
    }
}

void BathScene::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
    
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCSprite* catLayer = (CCSprite*)this->getChildByTag(kCatLayerTag);
    CCSprite* catHead = (CCSprite*)catLayer->getChildByTag(kHeadTag);
    CCSprite* catBody = (CCSprite*)catLayer->getChildByTag(kBodyTag);
    
    this->eyeMove(location);
    
    if (touchSprite != NULL) {
        if (touchSprite->getTag() == kSoapTag) {
            touchSprite->setPosition(location);
            if (catHead->boundingBox().containsPoint(location) || catBody->boundingBox().containsPoint(location)) {
                
                if (brushNum != 10) {
                    brushNum++;
                }else if (brushNum == 10){
                    brushNum = 0;
                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/brushSoap.mp3");
                }
            }
            this->brushDirty(location);
        }else if (touchSprite->getTag() == kBrushTag){
            touchSprite->setPosition(location);
            CCSprite* showerWater = (CCSprite*)this->getChildByTag(kShowerWaterTag);
            if (isCanFoam == true && showerWater == NULL) {
                this->changeBodyFoam(false, location);
            }
            if (catHead->boundingBox().containsPoint(location) || catBody->boundingBox().containsPoint(location)) {
                
                if (brushNum != 10) {
                    brushNum++;
                }else if (brushNum == 10){
                    brushNum = 0;
                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/brushSoap.mp3");
                }
            }
        }else if (touchSprite->getTag() == kHairDryerTag){
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            if (location.x < winSize.width/2) {
                touchSprite->setPosition(ccp(touchSprite->getPosition().x, location.y));
            }else{
                touchSprite->setPosition(location);
            }
        }
    }
}

void BathScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
    
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    this->eyeRevert();
    
    if (touchSprite != NULL) {
        if (touchSprite->getTag() == kHairDryerTag) {
            this->openHairDryer(false);
            touchSprite->setPosition(touchSpriteInPos);
        }else if (touchSprite->getTag() == kBrushTag){
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/returnBrush.mp3");
            SimpleAudioEngine::sharedEngine()->unloadEffect("mp3/bath/showFoam.mp3");
            touchSprite->setPosition(brushInPos);
        }else if (touchSprite->getTag() == kSoapTag){
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/bath/returnSoap.mp3");
            SimpleAudioEngine::sharedEngine()->unloadEffect("mp3/bath/showFoam.mp3");
            touchSprite->setPosition(touchSpriteInPos);
        }
        touchSprite = NULL;
        brushNum = 0;
    }
}

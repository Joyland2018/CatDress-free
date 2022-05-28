//
//  DressScene.cpp
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-4.
//
//

#include "DressScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "BuyPage.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif
#define kCLOTHE 10
#define kHAT 11
#define kSHOES 12
#define kBACKGROUND 13
#define kGLASSES 14
#define kTOY 15
#define kSET 16
#define kCLEAN 17
#define kCHEST 20

enum{
    kCatLayerTag = 1,
    kMenuLayerTag = 2,
    kChestLayerTag = 21,
    kBgTag = 22,
    kCatMouthAnimTag = 77,
    kCatEyeAnimTag = 78,
    kTailTag = 80,
    kBodyTag = 81,
    kHeadTag = 82,
    kEyeBgTag = 83,
    kEyeLTag = 84,
    kEyeRTag = 85,
    kMouthTag = 86,
    kToyTag = 101,
    kToyLayerTag = 102,
    kScrollViewTag = 110,
    kScrollLayerTag = 111,
    kFlashTag = 112,
    kStandbySetTag = 113,
    kStandbyToyTag = 114,
    kStandbyClothesTag = 115,
    kStandbycat1Tag = 116,
    kStandbycat2Tag = 117,
    kStandbycat3Tag = 118,
    kStandbyAnimTag = 119,
    kSysMenuLayerTag = 149,
    kMenuGroupTag = 150,
    kScreenshotTag = 151,
    kHomeTag = 158,
    kRecordTag = 153,
//    kChangeBgTag = 152,
    kControlSoundTag = 154,
    kGoInIAPTag = 156,
    kCameraTag = 152,
    kRateTag = 155,
    kScrollSideTag = 159,
    kScrollItemTag = 160,
    kFrameToyAnimTag = 161,
    kItemTag = 200,
    kSprActionTag = 300,
    kBuyLayerTag = 400,
    kChangeItemParTag = 401,
    kLockTag = 402,
    kClickTag = 600,
    kTeachHandTag = 700,
};

static DressScene* _dressScene;
int deviceType;
CCSprite* curChest;
int curItemNum;
int animalID;
CCLayer* beforeChest;
int beforeTypeTag;
CCSprite* touchSprite;
CCDictionary* weardGroup;
CCDictionary* curWearGroup;
CCDictionary* selItemGroup;
CCDictionary* movingGroup;
CCDictionary* itemInfoGroup;
CCPoint curToyPos;
int selectedType;
int curSelType;
bool isResetScroll;
int beforeChestType;
const char* deviceName;
int headTag;
int toyTag;
bool isCanTouchItem;
CCSprite* beforeBtn;
int bgTag;
bool isRunToy;
int selTag;
int selectedToyTag;
int curCatID;
int beforeY;
int scrItemInPos;
bool isFlash;
const char* standbyName;
bool isTouchBtnTag;
int selectedTag;
bool isHaveSound;
int changeSoundTag;
int clotheIAPTag;
int everyIAPTag;
int suitIAPTag;
int toyIAPTag;
int accessaryIAPTag;
int setSoundTag;
CCSprite* movingSpr;
bool isTouchHome;
int lastStandbySound;

int catEyeAnimTag;
int catMouthAnimTag;

CCScene* DressScene::sceneWithID(int _catID){
    CCScene* scene = CCScene::create();
    //    CC_BREAK_IF(!scene);
    
    DressScene* layer = DressScene::nodeWithID(_catID);
    //    CC_BREAK_IF(! layer);
    
    scene->addChild(layer);
    
    return scene;
}

DressScene* DressScene::nodeWithID(int _catID){
    _dressScene = new DressScene();
    if (_dressScene && _dressScene->initWithID(_catID)) {
        _dressScene->autorelease();
        
        return _dressScene;
    }else {
        CC_SAFE_DELETE(_dressScene);
        return NULL;
    }
}

bool DressScene::initWithID(int _catID){
    if (!CCLayer::init()) {
        return false;
    }
    curCatID = _catID;
    return true;
}

void DressScene::catAnimation(cocos2d::CCTime *dt){
//    CCLayer* catLayer = (CCLayer*)this->getChildByTag(kCatLayerTag);
//    
//    if (catLayer != NULL) {
//        CCBAnimationManager* animManager = (CCBAnimationManager*)catLayer->getUserObject();
//        if (catAnimTag == 0) {
//            animManager->runAnimationsForSequenceNamed("head");
//            catAnimTag++;
//        }else{
//            animManager->runAnimationsForSequenceNamed("tail");
//            catAnimTag = 0;
//        }
//    }
}

void DressScene::onEnter(){
    CCLayer::onEnter();
    touchSprite = NULL;
    beforeTypeTag = 0;
    beforeChest = NULL;
    selectedType = 0;
    curChest = NULL;
    isTouchHome = false;
    lastStandbySound = 0;
    CCDictionary* selectInfo = CatDressManager::sharedManager()->getDictionary("selectInformation.plist", NULL);

    animalID = selectInfo->valueForKey(CCString::createWithFormat("select%d",curCatID)->getCString())->intValue();


    weardGroup = CCDictionary::create();
    weardGroup->retain();
    curWearGroup = CCDictionary::create();
    curWearGroup->retain();
    selItemGroup = CCDictionary::create();
    selItemGroup->retain();
    movingGroup = CCDictionary::create();
    movingGroup->retain();
    itemInfoGroup = CatDressManager::sharedManager()->getDictionary("selItemInformation.plist", NULL);
    itemInfoGroup->retain();

    int backGTag = arc4random()%12+1;
    selTag = 0;
    selectedTag = 0;
    setSoundTag = 0;
    isShowSysMenu = false;

    isRecording = false;
    toyTag = 0;
    isRunToy = false;
    curSelType = 0;
    isCanTouchMenu = true;
    isResetScroll = false;
    beforeChestType = 0;
    isFlash = false;
    standbyName = NULL;
    isTouchBtnTag = true;
    changeSoundTag = 0;
    curToyPos = CCPointZero;

    catEyeAnimTag = 0;
    catMouthAnimTag = 0;

    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint center = GameManager::sharedManager()->getCenter();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();


    isCanTouchMenu = true;
    isShowSysMenu = false;

    bool isSilence = CCUserDefault::sharedUserDefault()->getBoolForKey("isSound");
    bool isChangeSound = CCUserDefault::sharedUserDefault()->getBoolForKey("isChangeSound");

    CCDictionary* catPlist = CatDressManager::sharedManager()->getDictionary("bath/catInformation.plist", NULL);
    CCDictionary* catInfo = CatDressManager::sharedManager()->getDictionary(CCString::createWithFormat("cat%d",animalID)->getCString(), catPlist);

    eyeLInPos = CatDressManager::sharedManager()->getPos("lEyeInPos", catInfo);
    eyeRInPos = CatDressManager::sharedManager()->getPos("rEyeInPos", catInfo);
    eyeRadius = catInfo->valueForKey("radius")->intValue();

    animRandom = 0;

    _dressScene->changeBg(backGTag);

//    _dressScene->setSprColor(1, "background",true);

//    CCString* fileName = CCString::createWithFormat("ccbi/cat/cat%d.ccbi",animalID);

    CCLayer* catLayer = CatDressManager::sharedManager()->getCatSprite(animalID,eyeLInPos,eyeRInPos);

    CCLayer* menuLayer = CatDressManager::sharedManager()->getMenuLayer();

    if (menuLayer!=NULL) {
//        menuLayer->setTag(kMenuLayerTag);
        menuLayer->setScale(0.8);
        _dressScene->addChild(menuLayer,5);

        CCMenuItemImage* clothItem = CCMenuItemImage::create("ui/menuItem1_Hd.png", "ui/menuItem1_Hd.png", this, menu_selector(DressScene::onClotheClick));
        clothItem->setPosition(ccp(leftBottom.x+clothItem->getContentSize().width/2*0.8, leftBottom.y+clothItem->getContentSize().height/2*0.8));
        clothItem->setScale(0.8);

        CCMenuItemImage* hatItem = CCMenuItemImage::create("ui/menuItem2_Hd.png", "ui/menuItem2_Hd.png", this, menu_selector(DressScene::onHatClick));
        hatItem->setPosition(ccp(clothItem->getPosition().x+clothItem->getContentSize().width*0.8, leftBottom.y+clothItem->getContentSize().height/2*0.8));
        hatItem->setScale(0.8);

        CCMenuItemImage* necklaceItem = CCMenuItemImage::create("ui/menuItem3_Hd.png", "ui/menuItem3_Hd.png", this, menu_selector(DressScene::onNecklaceClick));
        necklaceItem->setPosition(ccp(hatItem->getPosition().x+clothItem->getContentSize().width*0.8, leftBottom.y+clothItem->getContentSize().height/2*0.8));
        necklaceItem->setScale(0.8);

        CCMenuItemImage* glassesItem = CCMenuItemImage::create("ui/menuItem4_Hd.png", "ui/menuItem4_Hd.png", this, menu_selector(DressScene::onGlassesClick));
        glassesItem->setPosition(ccp(necklaceItem->getPosition().x+clothItem->getContentSize().width*0.8, leftBottom.y+clothItem->getContentSize().height/2*0.8));
        glassesItem->setScale(0.8);

        CCMenuItemImage* shoesItem = CCMenuItemImage::create("ui/menuItem5_Hd.png", "ui/menuItem5_Hd.png", this, menu_selector(DressScene::onShoesClick));
        shoesItem->setPosition(ccp(glassesItem->getPosition().x+clothItem->getContentSize().width*0.8, leftBottom.y+clothItem->getContentSize().height/2*0.8));
        shoesItem->setScale(0.8);

        CCMenuItemImage* toyItem = CCMenuItemImage::create("ui/menuItem6_Hd.png", "ui/menuItem6_Hd.png", this, menu_selector(DressScene::onToyClick));
        toyItem->setPosition(ccp(shoesItem->getPosition().x+clothItem->getContentSize().width*0.8, leftBottom.y+clothItem->getContentSize().height/2*0.8));
        toyItem->setScale(0.8);

        CCMenuItemImage* setItem = CCMenuItemImage::create("ui/anniu1_Hd.png", "ui/anniu1_Hd.png", this, menu_selector(DressScene::onSetClick));
        setItem->setPosition(ccp(toyItem->getPosition().x+clothItem->getContentSize().width*0.8, leftBottom.y+setItem->getContentSize().height/2*0.8));
        setItem->setScale(0.8);

        CCMenuItemImage* clearItem = CCMenuItemImage::create("ui/anniu2_Hd.png", "ui/anniu2_Hd.png", this, menu_selector(DressScene::onCleanClick));
        clearItem->setPosition(ccp(setItem->getPosition().x+clothItem->getContentSize().width*0.8, leftBottom.y+setItem->getContentSize().height/2*0.8));
        clearItem->setScale(0.8);

        CCMenu* menu = CCMenu::create(clothItem,hatItem,necklaceItem,glassesItem,shoesItem,toyItem,setItem,clearItem,NULL);
        menu->setPosition(CCPointZero);
        menu->setTag(kMenuLayerTag);
//        menu->setScale(0.8);
        _dressScene->addChild(menu,5);
    }

    if (catLayer!=NULL) {
        catLayer->setTag(kCatLayerTag);
        catLayer->setScale(0.8);
//        catLayer->setPosition(ccp(center.x, leftBottom.y+winSize.height/3));
        catLayer->setPosition(leftBottom);
        _dressScene->addChild(catLayer,1);

        CCSprite* head = (CCSprite*)catLayer->getChildByTag(kHeadTag);
        CCSprite* mouth = (CCSprite*)head->getChildByTag(kMouthTag);
        mouth->setZOrder(5);
    }

    CCLayer* systemMenuLayer = CCLayer::create();

#if defined(PAID) || defined(NEW_PAID)

    //    CCLayer* systemMenuLayer = (CCLayer*)GameManager::sharedManager()->getCCBNode("ccbi/paidMenu/systemMenu.ccbi", NULL, NULL);
#else
//    CCLayer* systemMenuLayer = (CCLayer*)GameManager::sharedManager()->getCCBNode("ccbi/systemMenu.ccbi", NULL, NULL);
#endif
    if (systemMenuLayer != NULL) {
        systemMenuLayer->setTag(kSysMenuLayerTag);
        systemMenuLayer->setContentSize(winSize);

//        systemMenuLayer->setScale(0.8);

        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/systemMenu.plist");

//        const char* fileNameArr[7] = {"menuGroup.png","screenShot.png","camera.png","record.png","soundOff.png","rate.png","gift.png"};
        const char* fileNameArr[6] = {"menuGroup.png","record.png","camera.png","soundOff.png","rate.png","gift.png"};

        for (int i = 0; i < 6; i++) {
            CCSprite* systemItem = CCSprite::createWithSpriteFrameName(fileNameArr[i]);

//            if (i < 4) {
//                systemItem->setPosition(ccp(leftTop.x+systemItem->getContentSize().width/2+i*systemItem->getContentSize().width, leftTop.y-systemItem->getContentSize().height/2));
//            } else {
//                systemItem->setPosition(ccp(leftTop.x+systemItem->getContentSize().width/2, leftTop.y-systemItem->getContentSize().height/2-(i-3)*systemItem->getContentSize().height));
//            }
            systemItem->setPosition(ccp(leftTop.x+systemItem->getContentSize().width/2+(10), leftTop.y-systemItem->getContentSize().height/2-(10)));
            switch (i) {
                case 0:
                    systemItem->setScale(1.1);
                    systemItem->setTag(kMenuGroupTag);
                    break;
//                case 1:
//                    systemItem->setTag(kCameraTag);
//                    break;
                case 1:
                    systemItem->setTag(kRecordTag);
//                    systemItem->setScale(0.8);
                    break;
                case 2:
                    systemItem->setTag(kScreenshotTag);
                    systemItem->setVisible(false);
//                    systemItem->setScale(0.8);
                    break;
                case 3:
                    systemItem->setTag(kControlSoundTag);
                    systemItem->setVisible(false);
//                    systemItem->setScale(0.8);
                    break;
                case 4:
                    systemItem->setTag(kRateTag);
                    systemItem->setVisible(false);
//                    systemItem->setScale(0.8);
                    break;
                case 5:
                    systemItem->setTag(kGoInIAPTag);
//                    systemItem->setScale(0.8);
//#if defined(PAID) || defined(NEW_PAID)
                    systemItem->setVisible(false);
//#endif
                    break;
                default:
                    break;
            }

            systemMenuLayer->addChild(systemItem,6-i);
        }

        CCSprite* soundBtn = (CCSprite*)systemMenuLayer->getChildByTag(kControlSoundTag);
        if (soundBtn != NULL) {
            if (isSilence == false && isChangeSound == true) {
                isHaveSound = false;
                _dressScene->setAnotherFrame(soundBtn, "soundOff");
            }else{
                isHaveSound = true;
                _dressScene->setAnotherFrame(soundBtn, "soundOn");
            }
        }
        isCanTouchMenu = false;
        isShowSysMenu = true;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        _dressScene->addChild(systemMenuLayer,10);
#endif
    }

    CCSprite* homeBtn = CCSprite::create("universal/back.png");
    homeBtn->setPosition(ccp(leftBottom.x+winSize.width/16, leftBottom.y+winSize.height*11/12));
    homeBtn->setTag(kHomeTag);
//    homeBtn->setScale(0.8);
    _dressScene->addChild(homeBtn,99);

    CCSprite* clickLayer = CCSprite::create("ui/click.png");
    clickLayer->setPosition(ccp(leftBottom.x+winSize.width/2, leftBottom.y+winSize.height/2));
    clickLayer->setTag(kClickTag);
    clickLayer->setScale(0.8);
    _dressScene->addChild(clickLayer,5);

//    _dressScene->schedule(schedule_selector(DressScene::animalAnimation),3);
//    _dressScene->schedule(schedule_selector(DressScene::catEyeAnim),4);
//    _dressScene->schedule(schedule_selector(DressScene::catMouthAnim),5);
    _dressScene->setTouchEnabled(true);


    //    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(_gameScene, 2);
    //    _gameScene->setTouchEnabled(true);
//    SimpleAudioEngine::sharedEngine()->playEffect("showMenu.mp3");
    _dressScene->runMenuAnim(true);
}

void DressScene::runMenuAnim(bool _isReverse){
    CCLayer* sysMenuLayer = (CCLayer*)_dressScene->getChildByTag(kSysMenuLayerTag);
    if (sysMenuLayer != NULL) {
        CCSprite* menuGroup = (CCSprite*)sysMenuLayer->getChildByTag(kMenuGroupTag);
        //        CCBAnimationManager* animation = (CCBAnimationManager*)sysMenuLayer->getUserObject();
        //        animation->setAnimationCompletedCallback(_dressScene, callfunc_selector(DressScene::completedMenuAnim));
        //        animation->runAnimationsForSequenceNamed("menuGroupAnim");
        _dressScene->setAnotherFrame(menuGroup, "cancel");
        
        CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
        CCPoint center = GameManager::sharedManager()->getCenter();
        CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
        CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
        
        for (int i = 151; i < 157; i++) {
            CCSprite* menuBtn = (CCSprite*)sysMenuLayer->getChildByTag(i);
            if (menuBtn != NULL && i != kCameraTag) {
                CCPoint movePos;
                
                int index = i-150;
                
                if (i == kRecordTag) {
                    index = index-2;
                }else if (i == kGoInIAPTag){
                    index = index-1;
                }
                
                if (!_isReverse) {
                    movePos = ccp(leftTop.x+menuBtn->getContentSize().width/2+(10), leftTop.y-menuBtn->getContentSize().height/2-(10));
                    
                    CCDelayTime* delay;
                    
                    if (index < 4) {
                        delay = CCDelayTime::create(0.4*(2-index));
                        menuBtn->runAction(CCSequence::create(delay,CCMoveTo::create(0.4*index, movePos),NULL));
                    } else {
                        
                        delay = CCDelayTime::create(0.4*(5-index));
                        menuBtn->runAction(CCSequence::create(delay,CCMoveTo::create(0.4*(index-3), movePos),NULL));
                    }
//                    _dressScene->setMenuBtnInVis();
                }else{
                
                if (index < 4) {
                    movePos = ccp(leftTop.x+menuBtn->getContentSize().width/2+index*menuBtn->getContentSize().width+(10), leftTop.y-menuBtn->getContentSize().height/2-(10));
                    
                    menuBtn->runAction(CCMoveTo::create(0.4*index, movePos));
                } else {
                    movePos = ccp(leftTop.x+menuBtn->getContentSize().width/2+(10), leftTop.y-menuBtn->getContentSize().height/2-(index-3)*menuBtn->getContentSize().height-(10));
                    
                    menuBtn->runAction(CCMoveTo::create(0.4*(index-3), movePos));
                }
                    
                }
            }
        }
        _dressScene->scheduleOnce(schedule_selector(DressScene::completedMenuAnim), 1.2);
        //        _dressScene->setMenuBtnInVis();
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/sysMenuAnim.mp3");
    }
}

void DressScene::onExit(){
    CCLayer::onExit();
    _dressScene->unscheduleAllSelectors();
    _dressScene->unscheduleUpdate();
    CCSprite* background = (CCSprite*)_dressScene->getChildByTag(kBgTag);
    if (background!=NULL) {
        background->removeFromParentAndCleanup(true);
    }
    CCSprite* sprite = (CCSprite*)_dressScene->getChildByTag(kStandbyAnimTag);
    if (sprite != NULL) {
        sprite->stopAllActions();
        sprite->removeFromParentAndCleanup(true);
        sprite = NULL;
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(CCString::createWithFormat("standby/standby%s.plist",standbyName)->getCString());
        CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("standby/standby%s.png",standbyName)->getCString());
        _dressScene->unschedule(schedule_selector(DressScene::animalAnimation));
    }
    weardGroup->removeAllObjects();
    weardGroup->release();
    curWearGroup->removeAllObjects();
    curWearGroup->release();
    selItemGroup->removeAllObjects();
    selItemGroup->release();
    movingGroup->removeAllObjects();
    movingGroup->release();
    itemInfoGroup->removeAllObjects();
    itemInfoGroup->release();
    //    _gameScene->retainCount();
    
    //    if (beforeChest != NULL) {
    //        beforeChest->release();
    //        beforeChest = NULL;
    //    }
    //    if (_gameScene != NULL) {
    //        _gameScene->release();
    //    }
    
    //    _gameScene->release();
    
    CCLayer* chest = (CCLayer*)_dressScene->getChildByTag(kChestLayerTag);
    if (chest != NULL) {
        CCSprite* chestSpr = (CCSprite*)chest->getChildByTag(kCHEST);
        chestSpr->stopAllActions();
        CC_SAFE_DELETE(chestSpr);
    }
    CCLayer* menuLayer = (CCLayer*)_dressScene->getChildByTag(kMenuLayerTag);
    if (menuLayer != NULL) {
        menuLayer->stopAllActions();
        CC_SAFE_DELETE(menuLayer);
    }
    CCLayer* catLayer = (CCLayer*)_dressScene->getChildByTag(kCatLayerTag);
    if (catLayer != NULL) {
        CCLayer* toyLayer = (CCLayer*)catLayer->getChildByTag(kToyLayerTag);
//        CCSprite* catHead = (CCSprite*)catLayer->getChildByTag(kHeadTag);
//        if (catHead != NULL) {
//            catHead->stopAllActions();
//            catHead->removeAllChildrenWithCleanup(true);
//            catHead->removeFromParentAndCleanup(true);
//            //        CC_SAFE_DELETE(catHead);
//        }
        if (toyLayer != NULL) {
            CCSprite* toy = (CCSprite*)toyLayer->getChildByTag(kToyTag);
            toy->stopAllActions();
            toyLayer->stopAllActions();
            toy->removeAllChildrenWithCleanup(true);
            toy->removeFromParentAndCleanup(true);
//            CC_SAFE_DELETE(toy);
            //        toy->release();
            toyLayer->removeAllChildrenWithCleanup(true);
            toyLayer->removeFromParentAndCleanup(true);
            //        toyLayer->release();
            //        CCLOG("toy---->%d",toy->retainCount());
            CCLOG("toyL--->%d",toyLayer->retainCount());
            //        toy = NULL;
            //        toyLayer = NULL;
        }
        catLayer->stopAllActions();
        CC_SAFE_DELETE(catLayer);
    }
    
    CCLayer* systemMenuLayer = (CCLayer*)_dressScene->getChildByTag(kSysMenuLayerTag);
    if (systemMenuLayer != NULL) {
        systemMenuLayer->stopAllActions();
        CC_SAFE_DELETE(systemMenuLayer);
    }
    //    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("cat1.plist");
    //    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("systemMenu.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("catItems/cat%d.png",animalID)->getCString());
    //    CCTextureCache::sharedTextureCache()->removeTextureForKey("systemMenu.png");
    //    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
//    SimpleAudioEngine::sharedEngine()->unloadEffect("showMenu.mp3");
    //    SimpleAudioEngine::sharedEngine()->unloadEffect("nextScene.mp3");
    if (selectedToyTag != 0 && (selectedToyTag == 46 || selectedToyTag < 11)) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(CCString::createWithFormat("toy/toy%dAnim.plist",selectedToyTag)->getCString());
        CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("toy/toy%dAnim.png",selectedToyTag)->getCString());
    }
    _dressScene->stopAllActions();
    _dressScene->removeChildByTag(kBgTag, true);
    //    CC_SAFE_DELETE(_gameScene);
    //    _gameScene->release();
    CCLOG("again!!");
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}

void DressScene::beginRecord(float dt){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    DeviceManager::sharedManager()->recordTimer(dt);
#else
#endif
}

void DressScene::goRecord(){
    CCLayer* sysMenuLayer = (CCLayer*)_dressScene->getChildByTag(kSysMenuLayerTag);
    CCSprite* recordBtn = (CCSprite*)sysMenuLayer->getChildByTag(kRecordTag);
    if (isRecording == false) {
        if (isHaveSound == true) {
            SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
            SimpleAudioEngine::sharedEngine()->setEffectsVolume(2);
        }
        _dressScene->setAnotherFrame(recordBtn, "recording");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        DeviceManager::sharedManager()->startRecord();
#else
#endif
        _dressScene->schedule(schedule_selector(DressScene::beginRecord));
        isRecording = true;
        CCUserDefault::sharedUserDefault()->setBoolForKey("isRecording", isRecording);
        CCUserDefault::sharedUserDefault()->setBoolForKey("isGameing", true);
    }else if (isRecording == true) {
        _dressScene->unschedule(schedule_selector(DressScene::beginRecord));
        _dressScene->setAnotherFrame(recordBtn, "record");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        DeviceManager::sharedManager()->stopRecord();
#else
#endif
        isRecording = false;
        CCUserDefault::sharedUserDefault()->setBoolForKey("isRecording", isRecording);
        if (isHaveSound == true) {
            SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
            SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
        }
    }
}

void DressScene::goCamera(cocos2d::CCImage *picLayer){
    _dressScene->eyeRevert();
    if (isRecording == true) {
        _dressScene->goRecord();
    }
//    DeviceManager::shareManager()->getPicture(picLayer);
}

DressScene::DressScene(){
    
}

DressScene::~DressScene(){
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}

void DressScene::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader){
    
}

SEL_MenuHandler DressScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(pTarget, "onClotheClick", DressScene::onClotheClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(pTarget, "onHatClick", DressScene::onHatClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(pTarget, "onShoesClick", DressScene::onShoesClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(pTarget, "onNecklaceClick", DressScene::onNecklaceClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(pTarget, "onGlassesClick", DressScene::onGlassesClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(pTarget, "onToyClick", DressScene::onToyClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(pTarget, "onSetClick", DressScene::onSetClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(pTarget, "onCleanClick", DressScene::onCleanClick);
    return NULL;
}

SEL_CCControlHandler DressScene::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
    return NULL;
}

void DressScene::onClotheClick(cocos2d::CCObject *pSender){
    CCLayer* buyLayer = (CCLayer*)_dressScene->getChildByTag(kBuyLayerTag);
    if (isTouchBtnTag == true && !buyLayer) {
        
        _dressScene->showChest(kCLOTHE,"clothes",pSender);
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
    }
}

void DressScene::onHatClick(cocos2d::CCObject *pSender){
    CCLayer* buyLayer = (CCLayer*)_dressScene->getChildByTag(kBuyLayerTag);
    if (isTouchBtnTag == true && !buyLayer) {
        
        _dressScene->showChest(kHAT,"hat",pSender);
        headTag = kHeadTag;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
    }
}

void DressScene::onShoesClick(cocos2d::CCObject *pSender){
    CCLayer* buyLayer = (CCLayer*)_dressScene->getChildByTag(kBuyLayerTag);
    if (isTouchBtnTag == true && !buyLayer) {
        
        _dressScene->showChest(kSHOES, "shoes",pSender);
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
    }
}

void DressScene::onNecklaceClick(cocos2d::CCObject *pSender){
    CCLOG("Necklace OK!");
    CCLayer* buyLayer = (CCLayer*)_dressScene->getChildByTag(kBuyLayerTag);
    if (isTouchBtnTag == true && !buyLayer) {
//        _dressScene->changeBg();
        
        _dressScene->showChest(kBACKGROUND,"background",pSender);
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
    }
    CCLOG("click--------->%d",deviceType);
}

void DressScene::onGlassesClick(cocos2d::CCObject *pSender){
    CCLayer* buyLayer = (CCLayer*)_dressScene->getChildByTag(kBuyLayerTag);
    if (isTouchBtnTag == true && !buyLayer) {
        
        _dressScene->showChest(kGLASSES,"glasses",pSender);
        headTag = kHeadTag;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
    }
}

void DressScene::onToyClick(cocos2d::CCObject *pSender){
    CCLayer* buyLayer = (CCLayer*)_dressScene->getChildByTag(kBuyLayerTag);
    if (isTouchBtnTag == true && !buyLayer) {
        
        _dressScene->showChest(kTOY,"toy",pSender);
        toyTag = kToyTag;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
    }
}

void DressScene::onSetClick(cocos2d::CCObject *pSender){
    CCLayer* buyLayer = (CCLayer*)_dressScene->getChildByTag(kBuyLayerTag);
    if (isTouchBtnTag == true && !buyLayer) {
        
        _dressScene->showChest(kSET,"set",pSender);
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
    }
}

void DressScene::onCleanClick(cocos2d::CCObject *pSender){
//插页广告
    this->goToShowInterstitial();
    CCLayer* buyLayer = (CCLayer*)_dressScene->getChildByTag(kBuyLayerTag);
    if (!buyLayer) {
        _dressScene->removeAllItem();
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
        selTag = 0;
    }

}

void DressScene::changeBg(int _tag){
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint center = GameManager::sharedManager()->getCenter();
    CCSprite* background = (CCSprite*)_dressScene->getChildByTag(kBgTag);
    
    if (bgTag==13) {
        bgTag = 1;
    }
    
    CCString* bgName = CCString::createWithFormat("background/background%d.png",_tag);
    if (background!=NULL) {
        //        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        background->removeFromParentAndCleanup(true);
        background = NULL;
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
    background = CCSprite::create(bgName->getCString());
    background->setPosition(center);
    background->setTag(kBgTag);
    _dressScene->addChild(background,-1);
    if (GameManager::sharedManager()->isIphoneX()) {
        background->setScale(1.3);
    }
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCString::createWithFormat("mp3/background/background%d.mp3",_tag)->getCString(), true);
//    CCUserDefault::sharedUserDefault()->setStringForKey("backgroundSound", CCString::createWithFormat("background%d.mp3",bgTag)->getCString());
//    bgTag++;
}

void DressScene::showChest(int selectTag, const char *pFileName, cocos2d::CCObject *pSender){
    CCSprite* chestBtn = (CCSprite*)pSender;
    bool isShowItem = true;
    toyTag = 0;
    
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
    
    int btnOffset;
    
    btnOffset = 10;
    if (beforeChest!=NULL) {
        isResetScroll = true;
        beforeBtn->runAction(CCMoveBy::create(0.1, ccp(0, -btnOffset)));
//        CCBAnimationManager* anim = (CCBAnimationManager*)beforeChest->getUserObject();
//        anim->setAnimationCompletedCallback(_dressScene, callfunc_selector(DressScene::removeSprite));
//        anim->runAnimationsForSequenceNamed("ReMove");
        
        CCSprite* chestSpr = (CCSprite*)beforeChest->getChildByTag(kCHEST);
        
        CCMoveTo* reChestMove = CCMoveTo::create(0.5, ccp(leftBottom.x+winSize.width+chestSpr->getContentSize().width/2*0.8, leftBottom.y+winSize.height/2));
        chestSpr->runAction(CCSequence::create(reChestMove,CCCallFunc::create(_dressScene, callfunc_selector(DressScene::removeSprite)),NULL));
        
        headTag = 0;
    }
    
    if (beforeTypeTag!=selectTag && isShowItem == true) {
        
        chestBtn->runAction(CCMoveBy::create(0.1, ccp(0, btnOffset)));
        isCanTouchItem = true;
//        CCString* ccbFileName = CCString::createWithFormat("ccbi/chest/%sChest.ccbi",pFileName);
        CCString* itemFile = CCString::createWithFormat("%s",pFileName);
        CCDictionary* itemInfo = CatDressManager::sharedManager()->getDictionary("itemInformation.plist", NULL);
        
        CCDictionary* curItemInfo = CatDressManager::sharedManager()->getDictionary(pFileName, itemInfo);
        int itemNum;
        itemNum = curItemInfo->valueForKey("num")->intValue();
        
//        CCLayer* chest = (CCLayer*)GameManager::sharedManager()->getCCBNode(ccbFileName->getCString(), NULL, NULL);
        CCLayer* chest = CCLayer::create();
        
        
        if (chest) {
            chest->setTag(kChestLayerTag);
            
            chest->setContentSize(winSize);
            
            CCSprite* chestItem = CCSprite::create("chest/chest6_Hd.png");
            chestItem->setPosition(ccp(leftBottom.x+winSize.width+chestItem->getContentSize().width/2, leftBottom.y+winSize.height/2));
            chestItem->setTag(kCHEST);
//            chestItem->setScale(0.8);
            chest->addChild(chestItem);
//            chest->setScale(0.8);
            _dressScene->addChild(chest,5);
        }
        
        CCSprite* chestSpr = (CCSprite*)chest->getChildByTag(kCHEST);
        chestSpr->setScale(0.8);
        
        _dressScene->showItemScroll(itemFile->getCString(), chestSpr->getContentSize(), chestSpr->getPosition(),chestSpr,itemNum+1);
//        CCBAnimationManager* anim = (CCBAnimationManager*)chest->getUserObject();
//        anim->setAnimationCompletedCallback(_dressScene, callfunc_selector(DressScene::isTouchBtn));
//        anim->runAnimationsForSequenceNamed("Move");
        
        CCMoveTo* chestMove = CCMoveTo::create(0.5, ccp(leftBottom.x+winSize.width-chestSpr->getContentSize().width/2*0.8, leftBottom.y+winSize.height/2));
        chestSpr->runAction(CCSequence::create(chestMove,CCCallFunc::create(_dressScene, callfunc_selector(DressScene::isTouchBtn)),NULL));
        
        beforeTypeTag = selectTag;
        beforeChest = chest;
        beforeBtn = chestBtn;
        
        curChest = chestSpr;
        selectedType = selectTag;
        isTouchBtnTag = false;
    }else if (beforeTypeTag == selectTag) {
        beforeChest = NULL;
        curChest = NULL;
        beforeBtn = NULL;
        selectedType = 0;
        beforeTypeTag = 0;
    }
}

void DressScene::showItemScroll(const char *pFileName,CCSize scrollSize,CCPoint scrollPos,CCSprite* pLayer,int itemNum){
    CCLayer* itemLayer = CCLayer::create();
    
    CCString* fileName = CCString::create(pFileName);
    CCString* className = CCString::create("set");
    
    //    CCString* target = CCString::createWithFormat("%s",CCFileUtils::sharedFileUtils()->getResourceDirectory());
    int scrollOffset;
    int scrollAnotherOffset;
    
    int initTag = 0;
    
    if (strcmp(pFileName, "background") == 0) {
        initTag = 1;
    }
    
//#if defined(PAID) || defined(NEW_PAID)
//    itemNum--;
//#endif
    
    scrollOffset = 27;
    scrollAnotherOffset = 20;
//    bool isUnlockEverything = CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll");
//
//    if (isUnlockEverything) {
//        itemNum--;
//    }
    
    CCSize itemSize;
    for (int i = initTag; i<itemNum; i++) {
        CCSprite* item = NULL;
        int itemIndex;
        if (i == 0) {
            item = CCSprite::create("ui/remove.png");
            item->setTag(i+kItemTag);
        }
//#if defined(NEW_ID) || defined(OLD)
//        else if (i == itemNum-1 && isUnlockEverything == false) {
//            item = CCSprite::create("ui/buy.png");
//            item->setTag(i+kItemTag);
//        }
//#endif
        else {
            if (strcmp(pFileName, "necklace") == 0) {
                item = CCSprite::create(CCString::createWithFormat("%s_mini/%s_%d_mini.png",pFileName,pFileName,i)->getCString());
                item->setTag(i+kItemTag);
            }else {
                CCDictionary* itemElemInfo = CatDressManager::sharedManager()->getDictionary(pFileName, itemInfoGroup);
                itemIndex = itemElemInfo->valueForKey(CCString::createWithFormat("%d",i)->getCString())->intValue();
                if (itemIndex != 0) {
                    
                    item = CCSprite::create(CCString::createWithFormat("%s_mini/%s_%d_mini.png",pFileName,pFileName,itemIndex)->getCString());
                    if (item != NULL) {
                        item->setTag(i+kItemTag);
                    }
                }
            }
        }
        
        if (item != NULL) {
//            if (isUnlockEverything == false) {
//                if (fileName->isEqual(className) && i > 2 && i < itemNum - 1 ) {
//                    _dressScene->addLock(item, itemSize);
//                }
//                if ((strcmp(fileName->getCString(), "clothes") == 0) && i > 26 && i < itemNum - 1) {
//                    _dressScene->addLock(item, itemSize);
//                }
//                if ((strcmp(fileName->getCString(), "hat") == 0) && i > 19 && i < itemNum - 1) {
//                    _dressScene->addLock(item, itemSize);
//                }
//                if ((strcmp(fileName->getCString(), "shoes") == 0) && i > 18 && i < itemNum - 1) {
//                    _dressScene->addLock(item, itemSize);
//                }
//                if ((strcmp(fileName->getCString(), "toy") == 0) && i > 22 && i < itemNum - 1) {
//                    _dressScene->addLock(item, itemSize);
//                }
//            }
            
            if (fileName->isEqual(className) && i == 1) {
                
                itemSize = item->getContentSize();
                
            }else if (!fileName->isEqual(className)) {
                itemSize = item->getContentSize();
            }
            if (strcmp(pFileName, "background") == 0) {
                item->setPosition(ccp(itemSize.width*4/7, itemSize.height*itemNum*35/34-i*itemSize.height*35/34-itemSize.height/2-10));
            }else{
                
                item->setPosition(ccp(itemSize.width*4/7, itemSize.height*itemNum*35/34-i*itemSize.height*35/34-itemSize.height/2-5));
            }
            
            itemLayer->addChild(item);
        }
        
    }
    //    }
    if (fileName->isEqual(className)) {
        CCSprite* removeSpr = (CCSprite*)itemLayer->getChildByTag(kItemTag);
        removeSpr->setPosition(ccp(itemSize.width*4/7, itemSize.height*itemNum*35/34-itemSize.height/2-5));
    }
    
    int selecedItemTag = selItemGroup->valueForKey(pFileName)->intValue();
    if (selecedItemTag) {
        CCSprite* item = (CCSprite*)itemLayer->getChildByTag(selecedItemTag);
        if (item != NULL) {
            item->setColor(ccGRAY);
        }
    }
    curItemNum = itemNum;
    if (strcmp(pFileName, "background") == 0) {
        itemNum--;
    }
    
    if (fileName->isEqual(className)) {
        itemLayer->setContentSize(CCSizeMake(scrollSize.width, itemSize.height*itemNum+itemSize.height/4));
    }else {
        itemLayer->setContentSize(CCSizeMake(scrollSize.width, scrollSize.height*itemNum*2/11-itemNum*scrollOffset-scrollAnotherOffset));
    }
    itemLayer->setTag(kScrollLayerTag);
    itemLayer->setTouchPriority(1);
    
    CCScrollView* scrollView = CCScrollView::create(CCSizeMake(scrollSize.width, scrollSize.height*11/15),itemLayer);
    
    scrollView->setPosition(scrollSize.width/6,scrollSize.height/20);
    scrollView->setTouchEnabled(true);
    scrollView->setDelegate(_dressScene);
    scrollView->setDirection(kCCScrollViewDirectionVertical);
    
    if (fileName->isEqual(className)) {
        scrollView->setContentSize(CCSizeMake(scrollSize.width, itemSize.height*itemNum+itemSize.height/4+30));
        //        scrollView->setContentOffset(CCPointMake(0, -itemSize.height*itemNum+itemSize.height*3-25));
        scrollView->setContentOffset(scrollView->minContainerOffset());
    }else {
        scrollView->setContentSize(CCSizeMake(scrollSize.width, scrollSize.height*itemNum*2/11-itemNum*scrollOffset-scrollAnotherOffset));
        //        scrollView->setContentOffset(CCPointMake(0, -itemSize.height*itemNum*35/34+itemSize.height*9/2+75));
        scrollView->setContentOffset(scrollView->minContainerOffset());
    }
    scrollView->setTouchPriority(-1);
    
    scrollView->setTag(kScrollViewTag);
    scrollView->updateInset();
    
    beforeY = scrollView->getContentOffset().y;
    
    pLayer->addChild(scrollView);
    
    CCSprite* scrollSide = CCSprite::create("ui/scroll.png");
    scrollSide->setPosition(ccp(scrollSize.width/5, scrollSize.height*3/7));
    scrollSide->setTag(kScrollSideTag);
    pLayer->addChild(scrollSide);
    
    CCSize scrollConSize = scrollView->getContentSize();
    CCSize scrollViewSize = scrollView->getViewSize();
    
    float scaleNumH = scrollConSize.height/scrollViewSize.height;
    float scaleNumY = scaleNumH*4;
    
    CCSize scrollSideSize = scrollSide->getContentSize();
    
    CCSprite* scrollItem = CCSprite::create("ui/scrollItem.png");
    scrollItem->setPosition(ccp(scrollSideSize.width/2, scrollSideSize.height-scrollSideSize.height/scaleNumY));
    
    int finalScaleNumY = scrollSideSize.height/scrollItem->getContentSize().height/2;
    
    scrItemInPos = scrollItem->getPosition().y+1;
    
    scrollItem->setScaleY(finalScaleNumY/scaleNumH);
    scrollItem->setTag(kScrollItemTag);
    scrollSide->addChild(scrollItem);
    
    CCString* coverName = CCString::createWithFormat("chest/Chest%s.png",pFileName);
    CCSprite* chestCover = CCSprite::create(coverName->getCString());
    chestCover->setPosition(ccp(scrollSize.width/2, scrollSize.height/2));
//    chestCover->setScale(0.8);
    pLayer->addChild(chestCover);
}

void DressScene::addLock(CCSprite* item, cocos2d::CCSize itemSize){
//    CCSprite* lock = CCSprite::create("ui/lock.png");
//    lock->setPosition(ccp(itemSize.width/2, itemSize.height/2.5));
//    lock->setTag(kLockTag);
//    item->addChild(lock);
}

CCString* DressScene::getItemType(int tag){
    CCString* selectName;
    switch (tag) {
        case kCLOTHE:
            selectName = CCString::create("clothes");
            break;
        case kHAT:
            selectName = CCString::create("hat");
            break;
        case kBACKGROUND:
            selectName = CCString::create("background");
            break;
        case kSHOES:
            selectName = CCString::create("shoes");
            break;
        case kGLASSES:
            selectName = CCString::create("glasses");
            break;
        case kTOY:
            selectName = CCString::create("toy");
            break;
        case kSET:
            selectName = CCString::create("set");
            break;
        default:
            break;
    }
    return selectName;
}

void DressScene::wearItem(int selectTag, cocos2d::CCPoint selItemPos, bool isGoMove){
    selTag = selectTag;
    
    int selItemTag = selectTag - kItemTag;
    CCString* selectName = _dressScene->getItemType(selectedType);
    CCDictionary* itemElemInfo = CatDressManager::sharedManager()->getDictionary(selectName->getCString(), itemInfoGroup);
    int itemIndex = itemElemInfo->valueForKey(CCString::createWithFormat("%d",selItemTag)->getCString())->intValue();
    
    _dressScene->setSprColor(selectTag, selectName->getCString(),true);
    selItemGroup->setObject(CCString::createWithFormat("%d",selectTag), selectName->getCString());
    
    SimpleAudioEngine::sharedEngine()->unloadEffect(CCString::createWithFormat("mp3/toy/toy_%d.mp3",selectedToyTag)->getCString());
    
    CCString* fileName;
    CCDictionary* itemInfo = CatDressManager::sharedManager()->getDictionary("itemInformation.plist", NULL);
    
    CCSprite* sprite;
    CCSprite* parentSpr;
    CCPoint itemPos;
    
    CCLayer* catLayer = (CCLayer*)_dressScene->getChildByTag(kCatLayerTag);
    CCDictionary* curItemInfo = CatDressManager::sharedManager()->getDictionary(selectName->getCString(), itemInfo);
    
    int itemZ = curItemInfo->valueForKey("zone")->intValue();
    if (catLayer != NULL) {
        if (selectedType == kHAT || selectedType == kGLASSES) {
            if ((itemIndex == 8 || itemIndex == 20 || itemIndex == 22 || itemIndex == 32) && selectedType == kHAT) {
                fileName = CCString::createWithFormat("%s/mao%d/%s_cat%d_%d.png",selectName->getCString(),animalID,selectName->getCString(),animalID,itemIndex);
            }else if (selectedType == kGLASSES){
                fileName = CCString::createWithFormat("%s/mao8/%s_cat8_%d.png",selectName->getCString(),selectName->getCString(),itemIndex);
            } else {
                fileName = CCString::createWithFormat("%s/mao9/%s_cat9_%d.png",selectName->getCString(),selectName->getCString(),itemIndex);
            }
            sprite = CCSprite::create(fileName->getCString());
            parentSpr = (CCSprite*)catLayer->getChildByTag(kHeadTag);
            selItemPos = parentSpr->convertToNodeSpace(selItemPos);
            
            CCString* infoName = CCString::createWithFormat("cat%d",animalID);
            CCDictionary* catInfo = CatDressManager::sharedManager()->getDictionary("position", curItemInfo);
            itemPos = CatDressManager::sharedManager()->getPos(infoName->getCString(), catInfo);
            
            sprite->setPosition(selItemPos);
            parentSpr->addChild(sprite,itemZ);
            sprite->setScale(0.3);
            _dressScene->moveItem(sprite, itemPos,selectName->getCString());
        }else if (selectedType == kTOY) {
            CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
            if (itemIndex >= 11 && itemIndex != 46 && itemIndex != 44) {
                
//                fileName = CCString::createWithFormat("ccbi/%s/%s%d.ccbi",selectName->getCString(),selectName->getCString(),itemIndex);
//                sprite = (CCSprite*)GameManager::sharedManager()->getCCBNode(fileName->getCString(), NULL, NULL);
                sprite = CatDressManager::sharedManager()->getToySpr(itemIndex);
                CCSprite* toy = (CCSprite*)sprite->getChildByTag(kToyTag);
                selItemPos = sprite->convertToNodeSpace(selItemPos);
                
//                itemPos = toy->getPosition();
                itemPos = CatDressManager::sharedManager()->getPos("position", curItemInfo);
                itemPos = ccp(itemPos.x*0.8, itemPos.y*0.8);
                toy->setPosition(selItemPos);
                toy->setScale(0.3);
                
                CCPoint center = GameManager::sharedManager()->getCenter();
                CCSize winSize = CCDirector::sharedDirector()->getWinSize();
                
                sprite->setTag(kToyLayerTag);
                sprite->setPosition(center);
                catLayer->addChild(sprite,5);
                _dressScene->moveItem(toy, itemPos,selectName->getCString());
            }else {
                fileName = CCString::createWithFormat("%s/%s_%d.png",selectName->getCString(),selectName->getCString(),itemIndex);
                sprite = CCSprite::create(fileName->getCString());
                selItemPos = catLayer->convertToNodeSpace(selItemPos);
                
                itemPos = CatDressManager::sharedManager()->getPos("position", curItemInfo);
                itemPos = ccp(itemPos.x*0.8, itemPos.y*0.8);
                sprite->setPosition(selItemPos);
                sprite->setTag(kToyTag);
                catLayer->addChild(sprite,5);
                sprite->setScale(0.3);
                _dressScene->moveItem(sprite, itemPos,selectName->getCString());
            }
            isRunToy = true;
            selectedToyTag = itemIndex;
            if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFirst") == true) {
            }
        }else if (selectedType == kSET) {
            _dressScene->wearSet(itemIndex);
        }else if (selectedType == kBACKGROUND){
            _dressScene->changeBg(itemIndex);
        }else {
            fileName = CCString::createWithFormat("%s/%s_%d.png",selectName->getCString(),selectName->getCString(),itemIndex);
            sprite = CCSprite::create(fileName->getCString());
            parentSpr = (CCSprite*)catLayer->getChildByTag(kBodyTag);
            selItemPos = parentSpr->convertToNodeSpace(selItemPos);
            
            itemPos = CatDressManager::sharedManager()->getPos("position", curItemInfo);
            
            sprite->setPosition(selItemPos);
            if (selectedType == kSHOES) {
                sprite->setAnchorPoint(CCPointZero);
            }
            parentSpr->addChild(sprite,itemZ);
            sprite->setScale(0.3);
            _dressScene->moveItem(sprite, itemPos,selectName->getCString());
        }
        //    if (selectedType != kTOY) {
        curSelType = selectedType;
        if (selectedType != kSET && selectedType != kBACKGROUND) {
            
            curWearGroup->setObject(sprite, selectName->getCString());
        }
    }
}

void DressScene::openIAPPage(){
    
    this->showIAPPage(1);
}

void DressScene::checkIAP(){
    bool isShowIAP = GameManager::sharedManager()->isNeedShowIAP();
    if (isShowIAP) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        DeviceManager::sharedManager()->goToReview();
#else
#endif
        this->unschedule(schedule_selector(DressScene::checkIAP));
    }
//    CCLayer* buyLayer = (CCLayer*)this->getChildByTag(kBuyLayerTag);
//    if (buyLayer == NULL) {
//        if (CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") == false) {
//            bool isShowIAP = GameManager::sharedManager()->isNeedShowIAP();
//
//            if(isShowIAP){
//                this->showIAPPage(2);
//            }
//            if (GameManager::sharedManager()->iapDisplayCount >= 2) {
//                this->unschedule(schedule_selector(DressScene::checkIAP));
//            }
//        }
//    }
}

void DressScene::showIAPPage(int _index){
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
//        buyLayer->setInitPageIndex(16);
//#endif
//        buyLayer->setTag(kBuyLayerTag);
//        this->addChild(buyLayer, 100);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        BuyLayer::setPageIndex(16);
//#else
////        BuyPage::setPageIndex(16);
//#endif
//        CCLayerColor *blacklayer = CCLayerColor::create(ccc4(0, 0, 0, 180), winSize.width, winSize.height);
//        blacklayer->ignoreAnchorPointForPosition(false);
//        blacklayer->setPosition(center);
//        buyLayer->addChild(blacklayer,-1);
//
//    }
}

void DressScene::wearSet(int tag){
    CCDictionary* setInfo = CatDressManager::sharedManager()->getDictionary("setInformation.plist", NULL);
    CCDictionary* itemSetInfo = CatDressManager::sharedManager()->getDictionary(CCString::createWithFormat("set%d",tag)->getCString(), setInfo);
    
    //    _gameScene->removeAllItem();
    
    SimpleAudioEngine::sharedEngine()->unloadEffect(CCString::createWithFormat("mp3/toy/toy_%d.mp3",selectedToyTag)->getCString());
    SimpleAudioEngine::sharedEngine()->unloadEffect(CCString::createWithFormat("mp3/set/set%d.mp3",setSoundTag)->getCString());
    CCArray* keys = itemSetInfo->allKeys();
    if (keys != NULL) {
        for (int i = 0; i < keys->count(); i++) {
            CCString* key = (CCString*)keys->objectAtIndex(i);
            int itemIndex = itemSetInfo->valueForKey(key->getCString())->intValue();
            
            _dressScene->wearItemInSet(itemIndex, key->getCString());
        }
    }
    weardGroup->setObject(CCString::createWithFormat("%d",tag), "set");
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCParticleSystem* changePar = CCParticleSystemQuad::create("particle/changeItem.plist");
    //    if (target->isEqual(CCString::create("hd/"))) {
    //        changePar = CCParticleSystemQuad::create("changeItem_hd.plist");
    //    }else if (target->isEqual(CCString::create("iphone/"))) {
    //        changePar = CCParticleSystem::create("changeItem_ip.plist");
    //    }
    changePar->setPosition(ccp(winSize.width/2, winSize.height/2));
    changePar->setTag(kChangeItemParTag);
    changePar->setAutoRemoveOnFinish(true);
    changePar->setScale(0.8);
    _dressScene->addChild(changePar,-1);
    curSelType = selectedType;
    //    int random = rand()%7+1;
    //    SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("change0%d.mp3",random)->getCString());
    //    changeSoundTag = random;
    if (isRecording == false) {
        SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mp3/set/set%d.mp3",tag)->getCString());
    }
    setSoundTag = tag;
    CCUserDefault::sharedUserDefault()->setBoolForKey("isHaveToy", true);
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFirst") == true) {
        _dressScene->unschedule(schedule_selector(DressScene::teachPlayToy));
        _dressScene->schedule(schedule_selector(DressScene::teachPlayToy), 1.2);
    }
}

void DressScene::wearItemInSet(int tag, const char *pSelType){
    CCLayer* catLayer = (CCLayer*)_dressScene->getChildByTag(kCatLayerTag);
    
    if (catLayer != NULL) {
        CCDictionary* itemInfo = CatDressManager::sharedManager()->getDictionary("itemInformation.plist", NULL);
        CCDictionary* curItemInfo = CatDressManager::sharedManager()->getDictionary(pSelType, itemInfo);
        int itemZ = curItemInfo->valueForKey("zone")->intValue();
        
        CCSprite* wearSprite = (CCSprite*)weardGroup->objectForKey(pSelType);
        
        if (wearSprite != NULL) {
            CCSprite* toy = (CCSprite*)wearSprite->getChildByTag(kToyTag);
            if (toy != NULL) {
                toy->removeAllChildrenWithCleanup(true);
                toy->removeFromParentAndCleanup(true);
                //            toy->release();
                //            CCLOG("toy---->%d",toy->retainCount());
                //            toy = NULL;
//                CC_SAFE_DELETE(toy);
            }
            CCLOG("sprite--->%d",wearSprite->retainCount());
            CCLOG("sprite--->%d",wearSprite->getChildrenCount());
            wearSprite->removeAllChildrenWithCleanup(true);
            wearSprite->removeFromParentAndCleanup(true);
            wearSprite = NULL;
            weardGroup->removeObjectForKey(pSelType);
            CCSprite* wearedFrame = (CCSprite*)catLayer->getChildByTag(kFrameToyAnimTag);
            if (wearedFrame != NULL) {
                wearedFrame->removeFromParentAndCleanup(true);
                wearedFrame = NULL;
            }
            CCTextureCache::sharedTextureCache()->removeUnusedTextures();
        }
        
        CCString* fileName;
        CCSprite* parentSpr;
        CCSprite* sprite;
        CCPoint itemPos;
        if (strcmp(pSelType, "hat") == 0) {
            if (tag == 8 || tag == 20 || tag == 22 || tag == 32) {
                fileName = CCString::createWithFormat("%s/mao%d/%s_cat%d_%d.png",pSelType,animalID,pSelType,animalID,tag);
            }else {
                fileName = CCString::createWithFormat("%s/mao9/%s_cat9_%d.png",pSelType,pSelType,tag);
            }
            sprite = CCSprite::create(fileName->getCString());
            parentSpr = (CCSprite*)catLayer->getChildByTag(kHeadTag);
            
            CCString* infoName = CCString::createWithFormat("cat%d",animalID);
            CCDictionary* catInfo = CatDressManager::sharedManager()->getDictionary("position", curItemInfo);
            itemPos = CatDressManager::sharedManager()->getPos(infoName->getCString(), catInfo);
            
            sprite->setPosition(itemPos);
            parentSpr->addChild(sprite,itemZ);
        }else if (strcmp(pSelType, "toy") == 0) {
            CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
            
            if (tag >= 11 && tag != 46) {
//                
//                fileName = CCString::createWithFormat("ccbi/%s/%s%d.ccbi",pSelType,pSelType,tag);
//                sprite = (CCSprite*)GameManager::sharedManager()->getCCBNode(fileName->getCString(), NULL, NULL);
//                CCSprite* toy = (CCSprite*)sprite->getChildByTag(kToyTag);
//                
//                itemPos = toy->getPosition();
//                toy->setPosition(itemPos);
//                
//                sprite->setTag(kToyLayerTag);
//                catLayer->addChild(sprite,5);
                sprite = CatDressManager::sharedManager()->getToySpr(tag);
                CCSprite* toy = (CCSprite*)sprite->getChildByTag(kToyTag);
                
                //                itemPos = toy->getPosition();
                itemPos = CatDressManager::sharedManager()->getPos("position", curItemInfo);
                itemPos = ccp(itemPos.x*0.8, itemPos.y*0.8);
                toy->setPosition(itemPos);
                
                CCPoint center = GameManager::sharedManager()->getCenter();
                
                sprite->setTag(kToyLayerTag);
                sprite->setPosition(center);
                catLayer->addChild(sprite,5);
            }else {
                fileName = CCString::createWithFormat("%s/%s_%d.png",pSelType,pSelType,tag);
                sprite = CCSprite::create(fileName->getCString());
                
                itemPos = CatDressManager::sharedManager()->getPos("position", curItemInfo);
                itemPos = ccp(itemPos.x*0.8, itemPos.y*0.8);
                sprite->setPosition(itemPos);
                sprite->setTag(kToyTag);
                catLayer->addChild(sprite,5);
            }
            selectedToyTag = tag;
            curToyPos = itemPos;
        }else {
            fileName = CCString::createWithFormat("%s/%s_%d.png",pSelType,pSelType,tag);
            sprite = CCSprite::create(fileName->getCString());
            parentSpr = (CCSprite*)catLayer->getChildByTag(kBodyTag);
            
            itemPos = CatDressManager::sharedManager()->getPos("position", curItemInfo);
            sprite->setPosition(itemPos);
            if (strcmp(pSelType, "shoes") == 0) {
                sprite->setAnchorPoint(CCPointZero);
            }
            parentSpr->addChild(sprite,itemZ);
        }
        CCLayer* tLayer = (CCLayer*)catLayer->getChildByTag(kToyLayerTag);
        if (tLayer != NULL) {
            CCLOG("toy---->%d",tLayer->retainCount());
        }
        weardGroup->setObject(sprite, pSelType);
        selItemGroup->setObject(CCString::createWithFormat("%d",tag+kItemTag), pSelType);
        isRunToy = false;
    }
}

void DressScene::setSprColor(int tag,const char* pSelType,bool isWeared){
    if (curChest!=NULL) {
        
        CCScrollView* scroll = (CCScrollView*)curChest->getChildByTag(kScrollViewTag);
        CCLayer* scrollLayer = (CCLayer*)scroll->getChildByTag(kScrollLayerTag);
        CCSprite* item = (CCSprite*)scrollLayer->getChildByTag(tag);
        if (item != NULL && isWeared == true) {
            item->setColor(ccGRAY);
        }
        
        int beforeItemTag = selItemGroup->valueForKey(pSelType)->intValue();
        if (beforeItemTag != 0) {
            CCSprite* beforeItem = (CCSprite*)scrollLayer->getChildByTag(beforeItemTag);
            if (beforeItem != NULL) {
                beforeItem->setColor(ccWHITE);
            }
        }
    }
}

void DressScene::moveItem(cocos2d::CCSprite *moveSpr,CCPoint toPos,const char* fileName){
    CCMoveTo* moveTo = CCMoveTo::create(0.5, toPos);
    curToyPos = toPos;
    CCEaseRateAction* easeOut = CCEaseOut::create(moveTo, 0.5F);
    CCScaleTo* scaleTo = CCScaleTo::create(0.5, 1.0);
    CCSpawn* spawn = CCSpawn::createWithTwoActions(easeOut, scaleTo);
    CCSequence* sequence = CCSequence::createWithTwoActions(spawn, CCCallFuncN::create(_dressScene, callfuncN_selector(DressScene::completeMove)));
    sequence->setTag(kSprActionTag);
    moveSpr->runAction(sequence);
    movingSpr = moveSpr;
    movingGroup->setObject(moveSpr, fileName);
}

void DressScene::completeMove(CCSprite* moveSpr){
    CCSize sprSize = moveSpr->getContentSize();
    
    //    CCString* target = CCString::createWithFormat("%s",CCFileUtils::sharedFileUtils()->getResourceDirectory());
    
    CCParticleSystem* changePar = CCParticleSystemQuad::create("particle/changeItem.plist");
    //    if (target->isEqual(CCString::create("hd/"))) {
    //        changePar = CCParticleSystemQuad::create("changeItem_hd.plist");
    //    }else if (target->isEqual(CCString::create("iphone/"))) {
    //        changePar = CCParticleSystem::create("changeItem_ip.plist");
    //    }
    changePar->setPosition(ccp(sprSize.width/2, sprSize.height/2));
    changePar->setTag(kChangeItemParTag);
    changePar->setAutoRemoveOnFinish(true);
    moveSpr->addChild(changePar,-1);
    
    CCString* selectName = _dressScene->getItemType(curSelType);
    CCSprite* wearedSprite = (CCSprite*)weardGroup->objectForKey(selectName->getCString());
    
    if (wearedSprite != NULL) {
        
        _dressScene->unschedule(schedule_selector(DressScene::setParticle));
        CCSprite* toy = (CCSprite*)wearedSprite->getChildByTag(kToyTag);
        if (toy != NULL) {
            toy->removeAllChildrenWithCleanup(true);
            toy->removeFromParentAndCleanup(true);
            toy = NULL;
        }
        wearedSprite->removeAllChildrenWithCleanup(true);
        wearedSprite->removeFromParentAndCleanup(true);
        wearedSprite = NULL;
        weardGroup->removeObjectForKey(selectName->getCString());
        CCLayer* catLayer = (CCLayer*)_dressScene->getChildByTag(kCatLayerTag);
        if (catLayer != NULL) {
            
            CCSprite* wearedFrame = (CCSprite*)catLayer->getChildByTag(kFrameToyAnimTag);
            if (wearedFrame != NULL) {
                wearedFrame->removeFromParentAndCleanup(true);
                wearedFrame = NULL;
            }
        }
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
    
    CCString* curSelName = _dressScene->getItemType(curSelType);
    //    CCSprite* curWearSprite = (CCSprite*)curWearGroup->objectForKey(curSelName->getCString());
    //    if (curWearSprite != NULL) {
    if (curSelType == kTOY) {
        CCLayer* catLayer = (CCLayer*)_dressScene->getChildByTag(kCatLayerTag);
        if (catLayer != NULL) {
            
            CCSprite* sprite = (CCSprite*)catLayer->getChildByTag(kToyLayerTag);
            CCSprite* toyLayer;
            if (moveSpr->getParent()->getTag() == kToyLayerTag) {
                toyLayer = (CCSprite*)moveSpr->getParent();
                weardGroup->setObject(sprite, curSelName->getCString());
            }else {
                weardGroup->setObject(moveSpr, curSelName->getCString());
            }
        }
        isRunToy = false;
        CCUserDefault::sharedUserDefault()->setBoolForKey("isHaveToy", true);
        if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFirst") == true) {
            _dressScene->unschedule(schedule_selector(DressScene::teachPlayToy));
            _dressScene->schedule(schedule_selector(DressScene::teachPlayToy), 1.2);
        }
    }else {
        weardGroup->setObject(moveSpr, curSelName->getCString());
    }
    selectedTag = selTag;
    //    CCSprite* movingSpr = (CCSprite*)movingGroup->objectForKey(selectName->getCString());
    CCAction* moveAction = movingSpr->getActionByTag(kSprActionTag);
    if (movingSpr != NULL && moveAction->isDone()) {
        movingGroup->removeObjectForKey(selectName->getCString());
        movingSpr = NULL;
    }
    
    int changeRandom = arc4random()%6+1;
    if (isRecording == false) {
        SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mp3/changeItem/change0%d.mp3",changeRandom)->getCString());
    }
    changeSoundTag = changeRandom;
}

void DressScene::showStandbyAnim(){
    int random = arc4random()%6+113;
    int soundRandom = arc4random()%3+1;
    const char* animName;
    switch (random) {
        case kStandbySetTag:
            animName = "Set";
            break;
        case kStandbyToyTag:
            animName = "Toy";
            break;
        case kStandbyClothesTag:
            animName = "Clothes";
            break;
        case kStandbycat1Tag:
            animName = "Cat1";
            break;
        case kStandbycat2Tag:
            animName = "Cat2";
            break;
        case kStandbycat3Tag:
            animName = "Cat3";
            break;
        default:
            break;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CCString::createWithFormat("standby/standby%s.plist",animName)->getCString());
    
    standbyName = animName;
    
    CCSprite* standbySpr = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("standby%s_0001.png",animName)->getCString());
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    standbySpr->setPosition(ccp(winSize.width*1/4, winSize.height*3/4));
    standbySpr->setTag(kStandbyAnimTag);
    standbySpr->setScale(0.8);
    _dressScene->addChild(standbySpr);
    
    CCAnimate* standbyAnim = CatDressManager::sharedManager()->getSpriteAnimate(1, 14, CCString::createWithFormat("standby%s",animName)->getCString(),false);
    
    CCSequence* standbySeq = CCSequence::createWithTwoActions(standbyAnim,CCDelayTime::create(2));
    
    standbySpr->runAction(CCSequence::createWithTwoActions(standbySeq,CCCallFunc::create(_dressScene, callfunc_selector(DressScene::removeStandbyAnim))));
    _dressScene->unschedule(schedule_selector(DressScene::animalAnimation));
    if (isRecording == false) {
        SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mp3/standby/showThink%d.mp3",soundRandom)->getCString());
    }
}

void DressScene::removeStandbyAnim(){
    CCSprite* sprite = (CCSprite*)_dressScene->getChildByTag(kStandbyAnimTag);
    if (sprite != NULL) {
        sprite->removeFromParentAndCleanup(true);
        sprite = NULL;
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(CCString::createWithFormat("standby/standby%s.plist",standbyName)->getCString());
        CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("standby/standby%s.png",standbyName)->getCString());
        _dressScene->schedule(schedule_selector(DressScene::animalAnimation),3);
    }
}

void DressScene::teachPlayToy(cocos2d::CCTime *dt){
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFirst") == true || CCUserDefault::sharedUserDefault()->getBoolForKey("isHaveToy") == true) {
        CCLayer* catLayer = (CCLayer*)_dressScene->getChildByTag(kCatLayerTag);
        if (catLayer != NULL) {
            CCLayer* toyLayer = (CCLayer*)catLayer->getChildByTag(kToyLayerTag);
            CCSprite* toy = NULL;
            if (toyLayer!=NULL) {
                toy = (CCSprite*)toyLayer->getChildByTag(kToyTag);
            }else {
                toy = (CCSprite*)catLayer->getChildByTag(kToyTag);
            }
            if (toy != NULL) {
                _dressScene->unschedule(schedule_selector(DressScene::teachPlayToy));
                CCUserDefault::sharedUserDefault()->setBoolForKey("isFirst", false);
                _dressScene->teachAnimation(curToyPos);
            }
        }
    }
}

void DressScene::teachAnimation(cocos2d::CCPoint sprPoint){
    
    CCLayer* catLayer = (CCLayer*)_dressScene->getChildByTag(kCatLayerTag);
    
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/teachHandAnim.plist");
    CCSprite* teachHand = CCSprite::createWithSpriteFrameName("teach_hand2.png");
    teachHand->setPosition(ccp(sprPoint.x+winSize.width/3, sprPoint.y));
    teachHand->setTag(kTeachHandTag);
    teachHand->setOpacity(0);
    catLayer->addChild(teachHand,100);
    
    CCFadeIn* fadeIn = CCFadeIn::create(0.5);
    CCMoveTo* moveTo = CCMoveTo::create(1, ccp(sprPoint.x+teachHand->getContentSize().width/2, sprPoint.y-20));
    //    CCMoveTo* clickTo = CCMoveTo::create(0.2, ccp(sprPoint.x, sprPoint.y-5));
    //    CCMoveTo* reClickTo = CCMoveTo::create(0.2, ccp(sprPoint.x, sprPoint.y));
    CCFadeOut* fadeOut = CCFadeOut::create(0.3);
    CCArray* frames = CCArray::create();
    for (int i = 0; i < 2; i++) {
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("teach_hand%d.png",i+1)->getCString());
        frames->addObject(frame);
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames,1.0/5.0);
    CCAnimate* anim = CCAnimate::create(animation);
    
    CCSpawn* seqClick = CCSpawn::createWithTwoActions(anim,CCCallFunc::create(_dressScene, callfunc_selector(DressScene::showTeachCircle)));
    CCRepeat* repeat = CCRepeat::create(seqClick, 6);
    CCSequence* seqFade = CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(repeat, CCDelayTime::create(0.8)), fadeOut);
    CCSequence* seqFadeIn = CCSequence::createWithTwoActions(fadeIn, CCCallFunc::create(_dressScene, callfunc_selector(DressScene::teachChangeVisible)));
    CCSequence* seqMove = CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(seqFadeIn, moveTo), seqFade);
    
    teachHand->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(seqMove, CCDelayTime::create(0)), CCCallFunc::create(_dressScene, callfunc_selector(DressScene::removeTeachHand))));
}

void DressScene::teachChangeVisible(){
    CCSprite* teachHand = (CCSprite*)_dressScene->getChildByTag(kTeachHandTag);
    if (teachHand != NULL && teachHand->isVisible() == false) {
        teachHand->setOpacity(255);
    }
}

void DressScene::teachChangeFrame(){
    CCSprite* teachHand = (CCSprite*)_dressScene->getChildByTag(kTeachHandTag);
    if (teachHand != NULL) {
        CCArray* frames = CCArray::create();
        for (int i = 0; i < 2; i++) {
            CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("teach_hand%d.png",i+1)->getCString());
            frames->addObject(frame);
        }
//        CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames,1.0/12.0);
//        CCAnimate* anim = CCAnimate::create(animation);
    }
}

void DressScene::teachAnotherFrame(){
    CCSprite* teachHand = (CCSprite*)_dressScene->getChildByTag(kTeachHandTag);
    if (teachHand != NULL) {
        _dressScene->setAnotherFrame(teachHand, "teach_hand2");
    }
}

void DressScene::showTeachCircle(){
    CCSprite* teachHand = (CCSprite*)_dressScene->getChildByTag(kTeachHandTag);
    if (teachHand != NULL) {
        CCSprite* teachCircle = CCSprite::create("ui/teachCircle.png");
        teachCircle->setPosition(ccp(10, 125));
        teachHand->addChild(teachCircle,-1);
        
        CCScaleTo* scaleTo = CCScaleTo::create(0.5, 2.5);
        CCFadeOut* fadeOut = CCFadeOut::create(0.5);
        
        teachCircle->runAction(CCSpawn::createWithTwoActions(scaleTo, fadeOut));
    }
}

void DressScene::removeTeachHand(){
    CCSprite* teachHand = (CCSprite*)_dressScene->getChildByTag(kTeachHandTag);
    if (teachHand != NULL) {
        teachHand->removeFromParentAndCleanup(true);
        teachHand = NULL;
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui/teachHandAnim.plist");
        CCTextureCache::sharedTextureCache()->removeTextureForKey("ui/teachHandAnim.png");
    }
}

void DressScene::catStandbySound(cocos2d::CCTime *dt){
    int standbySound = arc4random()%4+1;
    if (isRecording == false) {
        SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mp3/standby/standbySound%d.mp3",standbySound)->getCString());
    }
    lastStandbySound = standbySound;
}

void DressScene::catEyeAnim(cocos2d::CCTime *dt){
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
        
        CCSprite* catEyeAnim = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("mao%d_yanjing_%d_0001.png",animalID,catEyeAnimTag)->getCString());
        catEyeAnim->setPosition(eyeBg->getPosition());
        catEyeAnim->setTag(kCatEyeAnimTag);
        head->addChild(catEyeAnim);
        
        CCAnimate* eyeAnim = CatDressManager::sharedManager()->getSpriteAnimate(0, 3, CCString::createWithFormat("mao%d_yanjing_%d",animalID,catEyeAnimTag)->getCString(), false);
        catEyeAnim->runAction(CCSequence::createWithTwoActions(eyeAnim, CCCallFunc::create(this, callfunc_selector(DressScene::completeEyeAnim))));
        
        if (isRecording == false) {
            
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/standby/wink.mp3");
        }
    }
}

void DressScene::catMouthAnim(cocos2d::CCTime *dt){
    CCLayer* catLayer = (CCLayer*)this->getChildByTag(kCatLayerTag);
    if (catLayer != NULL) {
        catMouthAnimTag = arc4random()%4+2;
        CCSprite* head = (CCSprite*)catLayer->getChildByTag(kHeadTag);
        CCSprite* mouth = (CCSprite*)head->getChildByTag(kMouthTag);
        
        if (mouth != NULL && mouth->isVisible() == true) {
            mouth->setVisible(false);
        }
        
        CCSprite* catMouthAnim = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("mao%d_zui_%d_0001.png",animalID,catMouthAnimTag)->getCString());
        catMouthAnim->setPosition(mouth->getPosition());
        catMouthAnim->setTag(kCatMouthAnimTag);
        head->addChild(catMouthAnim,5);
        
        int framNum = 0;
        
        if (catMouthAnimTag == 2) {
            framNum = 2;
        }else{
            framNum = 1;
        }
        CCSequence* mouthAnimSeq = CCSequence::createWithTwoActions(CCDelayTime::create(1), CCCallFunc::create(this, callfunc_selector(DressScene::completeMouthAnim)));
        
        CCAnimate* mouthAnim = CatDressManager::sharedManager()->getSpriteAnimate(0, framNum, CCString::createWithFormat("mao%d_zui_%d",animalID,catMouthAnimTag)->getCString(), false);
        catMouthAnim->runAction(CCSequence::createWithTwoActions(mouthAnim, mouthAnimSeq));
        if (isRecording == false) {
            
//            SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mouth%d.mp3",catMouthAnimTag)->getCString());
            if (catMouthAnimTag == 2) {
                SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mp3/cat/cat%d.mp3",curCatID)->getCString());
            }else if (catMouthAnimTag == 5){
                
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/cat/cat8.mp3");
            }
        }
    }
}

void DressScene::completeEyeAnim(){
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

void DressScene::completeMouthAnim(){
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

void DressScene::animalAnimation(cocos2d::CCTime *dt){
    CCLayer* catLayer = (CCLayer*)_dressScene->getChildByTag(kCatLayerTag);
    
    
    if (catLayer!=NULL) {
        if (animRandom == 6) {
            animRandom = 0;
//#if defined(NEW_ID) || defined(OLD)
            _dressScene->showStandbyAnim();
//#endif
        }else if (animRandom == 1 || animRandom == 3 || animRandom == 5) {
            CCBAnimationManager* animManager = (CCBAnimationManager*)catLayer->getUserObject();
            animManager->runAnimationsForSequenceNamed("tail");
            animRandom++;
            if (isRecording == false) {
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/standby/shakeTail.mp3");
            }
        }else {
            CCBAnimationManager* animManager = (CCBAnimationManager*)catLayer->getUserObject();
            animManager->runAnimationsForSequenceNamed("head");
            animRandom++;
            if (isRecording == false) {
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/standby/shakeHead.mp3");
            }
        }
    }
}

void DressScene::completeToyAnim(){
    isRunToy = false;
    CCLayer* catLayer = (CCLayer*)_dressScene->getChildByTag(kCatLayerTag);
    if (catLayer != NULL) {
        CCLayer* toyLayer = (CCLayer*)catLayer->getChildByTag(kToyLayerTag);
        if (toyLayer!=NULL) {
            CCSprite* toy = (CCSprite*)toyLayer->getChildByTag(kToyTag);
            toy->setAnchorPoint(ccp(0.5, 0.5));
            toy->setPosition(toyInPos);
            _dressScene->unschedule(schedule_selector(DressScene::setParticle));
            if (selectedToyTag == 13) {
                CatDressManager::sharedManager()->selectPar(toy, 13, toyInPos);
            }
        }else {
            CCSprite* selectToy = (CCSprite*)catLayer->getChildByTag(kFrameToyAnimTag);
            CCSprite* toy = (CCSprite*)catLayer->getChildByTag(kToyTag);
            if (toy != NULL && !toy->isVisible()) {
                toy->setVisible(true);
            }
            
            if (selectToy!=NULL) {
                selectToy->removeFromParentAndCleanup(true);
                selectToy = NULL;
                
                CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(CCString::createWithFormat("toy/toy%dAnim.plist",selectedToyTag)->getCString());
                CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("toy/toy%dAnim.png",selectedToyTag)->getCString());
            }
        }
    }
}

void DressScene::showCCBToyAnim(){
    CCLayer* catLayer = (CCLayer*)_dressScene->getChildByTag(kCatLayerTag);
    if (catLayer != NULL) {
        
        CCLayer* toyLayer = (CCLayer*)catLayer->getChildByTag(kToyLayerTag);
        if (toyLayer != NULL) {
            CCSprite* toy = (CCSprite*)toyLayer->getChildByTag(kToyTag);
            toyInPos = toy->getPosition();
////            CCBAnimationManager* anim = (CCBAnimationManager*)toyLayer->getUserObject();
////            anim->setAnimationCompletedCallback(_dressScene, callfunc_selector(DressScene::completeToyAnim));
////            anim->runAnimationsForSequenceNamed("ToyAnim");
            
            ToyManager::sharedManager()->showToyAnim(selectedToyTag, toy, _dressScene, callfunc_selector(DressScene::completeToyAnim));
            
            if (selectedToyTag == 14 || selectedToyTag == 17 || selectedToyTag == 41 || selectedToyTag == 51) {
                _dressScene->schedule(schedule_selector(DressScene::setParticle));
            }else if (selectedToyTag == 13) {
                CCPoint toyPos = toy->getPosition();
                CatDressManager::sharedManager()->selectPar(toy, 13, toyPos);
            }
            if (isRecording == false) {
                if (selectedToyTag == 23) {
                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/toy/toy_22.mp3");
                }else {
                    SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mp3/toy/toy_%d.mp3",selectedToyTag)->getCString());
                }
            }
        }else {
            CCSprite* toy = (CCSprite*)catLayer->getChildByTag(kToyTag);
            if (toy != NULL) {
                CCString* toyName = CCString::createWithFormat("toy%d",selectedToyTag);
                CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CCString::createWithFormat("toy/toy%dAnim.plist",selectedToyTag)->getCString());
                CCSprite* selectToy = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%s_0001.png",toyName->getCString())->getCString());
                selectToy->setPosition(toy->getPosition());
                selectToy->setTag(kFrameToyAnimTag);
                toy->setVisible(false);
                
                int maxFraNum;
                if (selectedToyTag == 46) {
                    maxFraNum = 20;
                }else if (selectedToyTag == 44) {
                    maxFraNum = 13;
                }else {
                    maxFraNum = 5;
                }
                
                catLayer->addChild(selectToy,5);
                CCAnimate* toyAnim = CatDressManager::sharedManager()->getSpriteAnimate(0,maxFraNum, toyName->getCString(), false);
                
                selectToy->runAction(CCSequence::createWithTwoActions(toyAnim,CCCallFunc::create(_dressScene, callfunc_selector(DressScene::completeToyAnim))));
                
                if (isRecording == false) {
                    if (selectedToyTag < 11) {
                        SimpleAudioEngine::sharedEngine()->playEffect("mp3/toy/toy_1.mp3");
                    }else {
                        SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mp3/toy/toy_%d.mp3",selectedToyTag)->getCString());
                    }
                }
            }
        }
    }
}

void DressScene::setParticle(){
    CCLayer* catLayer = (CCLayer*)_dressScene->getChildByTag(kCatLayerTag);
    if (catLayer != NULL) {
        
        CCLayer* toyLayer = (CCLayer*)catLayer->getChildByTag(kToyLayerTag);
        if (toyLayer != NULL) {
            CCSprite* toy = (CCSprite*)toyLayer->getChildByTag(kToyTag);
            CCPoint toyPos = toy->getPosition();
            
            CatDressManager::sharedManager()->selectPar(toy, selectedToyTag, toyPos);
        }
    }
}

void DressScene::completedMenuAnim(){
    isCanTouchMenu = true;
    if (isShowSysMenu == false) {
        CCLayer* sysMenuLayer = (CCLayer*)_dressScene->getChildByTag(kSysMenuLayerTag);
        if (sysMenuLayer != NULL) {
            CCSprite* menuGroup = (CCSprite*)sysMenuLayer->getChildByTag(kMenuGroupTag);
            _dressScene->setAnotherFrame(menuGroup, "menuGroup");
            _dressScene->setMenuBtnInVis();
        }
    }
}

void DressScene::setMenuBtnInVis(){
    CCLayer* sysMenuLayer = (CCLayer*)_dressScene->getChildByTag(kSysMenuLayerTag);
    if (sysMenuLayer != NULL) {
        
        for (int i = 151; i < 157; i++) {
            CCSprite* menuBtn = (CCSprite*)sysMenuLayer->getChildByTag(i);
            if (menuBtn != NULL && menuBtn->isVisible()) {
                menuBtn->setVisible(false);
            }else if (menuBtn != NULL && !menuBtn->isVisible()){
                menuBtn->setVisible(true);
            }
        }
    }
}

void DressScene::touchMenuBtn(cocos2d::CCPoint location){
    CCLayer* sysMenuLayer = (CCLayer*)_dressScene->getChildByTag(kSysMenuLayerTag);
    if (sysMenuLayer != NULL) {
        
        for (int i = 151; i < 158; i++) {
            CCSprite* menuBtn = (CCSprite*)sysMenuLayer->getChildByTag(i);
            if (menuBtn != NULL && menuBtn->isVisible() && menuBtn->boundingBox().containsPoint(location) && isCanTouchMenu == true) {
                CCScaleTo* scaleTo = CCScaleTo::create(0.1, 1.1);
                CCScaleTo* reScaleTo = CCScaleTo::create(0.1, 1.0);
                menuBtn->runAction(CCSequence::create(scaleTo,reScaleTo,NULL));
                _dressScene->selectMenuBtn(i);
                break;
            }
        }
    }
}

void DressScene::goInStore(int tag){
    CCLayer* layer = (CCLayer*)_dressScene->getChildByTag(kBuyLayerTag);
    if (layer == NULL) {
//        layer = (CCLayer*)BuyLayer::nodeWithID(tag);
//        layer->setTag(kBuyLayerTag);
//        _dressScene->addChild(layer,1000);
        this->showIAPPage(1);
        if (curChest!=NULL) {
            
            //            CCScrollView* scroll = (CCScrollView*)curChest->getChildByTag(kScrollViewTag);
            //            scroll->setTouchEnabled(false);
            curChest = NULL;
        }
    }
    if (beforeChest != NULL) {
        //        CCString* target = CCString::createWithFormat("%s",CCFileUtils::sharedFileUtils()->getResourceDirectory());
        int btnOffset;
        //        if (target->isEqual(CCString::create("hd/"))) {
        //            btnOffset = 10;
        //        }else if (target->isEqual(CCString::create("ip/"))) {
        //            btnOffset = 5;
        //        }
        
        btnOffset = 10;
        isResetScroll = true;
        beforeBtn->runAction(CCMoveBy::create(0.1, ccp(0, -btnOffset)));
//        CCBAnimationManager* anim = (CCBAnimationManager*)beforeChest->getUserObject();
//        anim->setAnimationCompletedCallback(_dressScene, callfunc_selector(DressScene::removeSprite));
//        anim->runAnimationsForSequenceNamed("ReMove");
        CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
        CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
        
        CCSprite* chestSpr = (CCSprite*)beforeChest->getChildByTag(kCHEST);
        
        CCMoveTo* reChestMove = CCMoveTo::create(0.5, ccp(leftBottom.x+winSize.width+chestSpr->getContentSize().width/2, leftBottom.y+winSize.height/2));
        chestSpr->runAction(CCSequence::create(reChestMove,CCCallFunc::create(_dressScene, callfunc_selector(DressScene::removeSprite)),NULL));
        beforeChest = NULL;
        curChest = NULL;
        beforeBtn = NULL;
        selectedType = 0;
        beforeTypeTag = 0;
    }
    CCLayer* sysMenuLayer = (CCLayer*)_dressScene->getChildByTag(kSysMenuLayerTag);
//    CCBAnimationManager* animation = (CCBAnimationManager*)sysMenuLayer->getUserObject();
    if (isShowSysMenu) {
        isShowSysMenu = false;
        _dressScene->runMenuAnim(false);
//        animation->runAnimationsForSequenceNamed("reMenuGroupAnim");
    }
}

void DressScene::selectMenuBtn(int btnTag){
    switch (btnTag) {
        case kControlSoundTag:
            _dressScene->controlSound();
            break;
        case kHomeTag:
            _dressScene->returnLastScene();
            break;
        case kGoInIAPTag:
            _dressScene->goInStore(2);
            break;
        case kScreenshotTag:
            _dressScene->goScreenShot();
            break;
        case kCameraTag:
        {
            CCSprite* catLayer = (CCSprite*)_dressScene->getChildByTag(kCatLayerTag);
            if (catLayer != NULL) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                CCImage* catImage = DeviceManager::sharedManager()->getRenderUImage(catLayer);
                _dressScene->goCamera(catImage);
#else
#endif
            }
        }
            break;
        case kRecordTag:
            _dressScene->goRecord();
            break;
//        case kChangeBgTag:
//            _dressScene->changeBg();
//            break;
        case kRateTag:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            DeviceManager::sharedManager()->goToReview();
#else
#endif
            break;
        default:
            break;
    }
}

CCImage* DressScene::getRenderUImage(cocos2d::CCSprite *picLayer){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCRenderTexture* renderTexture = CCRenderTexture::create(winSize.width, winSize.height);
    renderTexture->begin();
    picLayer->visit();
    renderTexture->end();
    renderTexture->cleanup();
    CCImage* image = renderTexture->newCCImage();
    image->autorelease();
    return image;
}

void DressScene::eyeMove(CCPoint location){
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

void DressScene::eyeRevert(){
    CCLayer* catLayer = (CCLayer*)this->getChildByTag(kCatLayerTag);
    if (catLayer != NULL) {
        
        CCSprite* head = (CCSprite*)catLayer->getChildByTag(kHeadTag);
        CCSprite* eyeL = (CCSprite*)head->getChildByTag(kEyeLTag);
        CCSprite* eyeR = (CCSprite*)head->getChildByTag(kEyeRTag);
        
        eyeL->setPosition(eyeLInPos);
        eyeR->setPosition(eyeRInPos);
    }
}

void DressScene::returnLastScene(){
    if (isRecording == true) {
        _dressScene->goRecord();
    }
    CCUserDefault::sharedUserDefault()->setBoolForKey("isGameing", false);
    //    SimpleAudioEngine::sharedEngine()->unloadEffect(CCString::createWithFormat("standbySound%d.mp3",lastStandbySound)->getCString());
    SimpleAudioEngine::sharedEngine()->unloadEffect(CCString::createWithFormat("mp3/changeItem/change0%d.mp3",changeSoundTag)->getCString());
    SimpleAudioEngine::sharedEngine()->unloadEffect(CCString::createWithFormat("mp3/toy/toy_%d.mp3",selectedToyTag)->getCString());
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.8, CatSelectScene::sceneWithID(curCatID-1),ccWHITE));

}

void DressScene::goScreenShot(){
    if (isFlash == false) {
        isFlash = true;
        CCLayer* menuLayer = (CCLayer*)_dressScene->getChildByTag(kMenuLayerTag);
        CCLayer* sysMenuLayer = (CCLayer*)_dressScene->getChildByTag(kSysMenuLayerTag);
        CCSprite* homeBtn = (CCSprite*)_dressScene->getChildByTag(kHomeTag);
        
        _dressScene->eyeRevert();
        menuLayer->setVisible(false);
        sysMenuLayer->setVisible(false);
        homeBtn->setVisible(false);
        if (beforeChest != NULL) {
            beforeChest->setVisible(false);
        }
        CCSprite* curLayer = (CCSprite*)_dressScene;
//        curLayer->autorelease();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCImage* image = DeviceManager::sharedManager()->getRenderUImage(curLayer);
#else
#endif
        menuLayer->setVisible(true);
        sysMenuLayer->setVisible(true);
        homeBtn->setVisible(true);
        if (beforeChest != NULL) {
            beforeChest->setVisible(true);
        }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        DeviceManager::sharedManager()->cameraSelf(image);
#else
#endif
        
        CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
        CCSprite* flash = CCSprite::create("flash.png");
        flash->setPosition(ccp(winSize.width/2, winSize.height/2));
        //        flash->setRotation(50);
        flash->setTag(kFlashTag);
//        flash->setScale(0.8);
        _dressScene->addChild(flash,100);
        
        CCFadeOut* fadeOut = CCFadeOut::create(0.5);
        flash->runAction(CCSequence::createWithTwoActions(fadeOut, CCCallFunc::create(_dressScene, callfunc_selector(DressScene::removeFlash))));
        if (isRecording == false) {
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/camera.mp3");
        }
    }
}

void DressScene::removeFlash(){
    CCSprite* flash = (CCSprite*)_dressScene->getChildByTag(kFlashTag);
    if (flash != NULL) {
//        flash->setVisible(false);
        flash->removeFromParentAndCleanup(true);
        flash = NULL;
        isFlash = false;
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
}

void DressScene::controlSound(){
    CCLayer* sysMenuLayer = (CCLayer*)_dressScene->getChildByTag(kSysMenuLayerTag);
    CCSprite* soundBtn = (CCSprite*)sysMenuLayer->getChildByTag(kControlSoundTag);
    if (isHaveSound == true) {
        _dressScene->setAnotherFrame(soundBtn, "soundOff");
        isHaveSound = false;
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
    }else if (isHaveSound == false) {
        _dressScene->setAnotherFrame(soundBtn, "soundOn");
        if (isRecording == false) {
            SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
        }
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
        isHaveSound = true;
    }
    CCUserDefault::sharedUserDefault()->setBoolForKey("isTouchSilence", true);
    CCUserDefault::sharedUserDefault()->setBoolForKey("isSound", isHaveSound);
    CCUserDefault::sharedUserDefault()->setBoolForKey("isChangeSound", true);
}

void DressScene::clickCatSound(){
    if (isRecording == false) {
        int ranCatSound = arc4random()%2+1;
        SimpleAudioEngine::sharedEngine()->unloadEffect(CCString::createWithFormat("mp3/cat/cat%d.mp3",curCatID)->getCString());
        SimpleAudioEngine::sharedEngine()->unloadEffect("mp3/standby/standbySound.mp3");
        if (ranCatSound == 1) {
            SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mp3/cat/cat%d.mp3",curCatID)->getCString());
        }else{
            
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/standby/cat8.mp3");
        }
    }
}

void DressScene::setAnotherFrame(cocos2d::CCSprite *pSprite, const char *pFileName){
    CCString* imageName = CCString::createWithFormat("%s.png",pFileName);
    CCSpriteFrame* sprFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName->getCString());
    pSprite->setDisplayFrame(sprFrame);
}

void DressScene::removeSprite(){
    CCLayer* chest = (CCLayer*)_dressScene->getChildByTag(kChestLayerTag);
    if (chest != NULL) {
        CCSprite* chestSpr = (CCSprite*)chest->getChildByTag(kCHEST);
        chestSpr->removeAllChildrenWithCleanup(true);
        //        chest->removeAllChildrenWithCleanup(true);
        chest->removeFromParentAndCleanup(true);
//        CC_SAFE_DELETE(chestSpr);
//        CCLOG("chest---->%d",chest->retainCount());
        chest = NULL;
        isResetScroll = false;
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
        CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
    }
}

void DressScene::isTouchBtn(){
    isTouchBtnTag = true;
}

void DressScene::scrollViewDidScroll(cocos2d::extension::CCScrollView *view){
    if (curChest!=NULL && isResetScroll!=true) {
        CCSprite* scrollSide = (CCSprite*)curChest->getChildByTag(kScrollSideTag);
        
        CCSprite* scrollItem = (CCSprite*)scrollSide->getChildByTag(kScrollItemTag);
        CCSize scrollConSize = view->getContentSize();
        CCSize scrollViewSize = view->getViewSize();
        //        CCSize scrollSideSize = scrollSide->getContentSize();
        CCSize scrollItemSize = scrollItem->getContentSize();
        float scrollScale = scrollItem->getScaleY();
        CCLOG("offsetY----->%f",scrollScale);
        
        //        float scaleNumH = scrollConSize.height/scrollViewSize.height;
        //        float scaleNumY = scaleNumH*scrollScale;
        
        CCPoint beforePos = scrollItem->getPosition();
        CCSize beforeSize = view->getViewSize();
        CCPoint maxPos = view->minContainerOffset();
        CCPoint minPos = view->maxContainerOffset();
        int y = view->getContentOffset().y;
        CCPoint newLoc;
        if(maxPos.y < y && y < -scrollViewSize.height/10){
            CCLOG("negative");
            CCPoint newPoint = view->convertToWorldSpace(view->getContentOffset());
            newPoint = scrollSide->convertToNodeSpace(newPoint);
            newLoc = ccp(beforePos.x, y/maxPos.y*scrItemInPos);
        }
        //
        if (maxPos.y > y) {
            newLoc = ccp(beforePos.x, scrItemInPos);
        }else if (y > -scrollViewSize.height/10) {
            newLoc = ccp(beforePos.x, scrollItem->getContentSize().height*scrollScale/2);
        }
        
        scrollItem->setPosition(newLoc);
        
        beforeY = y;
    }
}

void DressScene::scrollViewDidZoom(cocos2d::extension::CCScrollView *view){
    
}

void DressScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
    
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCLayer* buyLayer = (CCLayer*)_dressScene->getChildByTag(kBuyLayerTag);
    if (!buyLayer) {
        
        _dressScene->eyeMove(location);
        
        CCSprite* clickLayer = (CCSprite*)_dressScene->getChildByTag(kClickTag);
        if (clickLayer != NULL && clickLayer->boundingBox().containsPoint(location)) {
            _dressScene->clickCatSound();
        }
        
        CCSprite* standbySpr = (CCSprite*)_dressScene->getChildByTag(kStandbyAnimTag);
        if (standbySpr != NULL && standbySpr->boundingBox().containsPoint(location)) {
            if (strcmp(standbyName, "Clothes") == 0) {
                _dressScene->goInStore(2);
            }else if (strcmp(standbyName, "Toy") == 0){
                _dressScene->goInStore(2);
            }else if (strcmp(standbyName, "Set") == 0){
                _dressScene->goInStore(2);
            }else if (strcmp(standbyName, "Cat1") == 0){
                _dressScene->goInStore(2);
            }else if (strcmp(standbyName, "Cat2") == 0){
                _dressScene->goInStore(2);
            }else if (strcmp(standbyName, "Cat3") == 0){
                _dressScene->goInStore(2);
            }
        }
        
        CCSprite* homeBtn = (CCSprite*)_dressScene->getChildByTag(kHomeTag);
        if (homeBtn != NULL && homeBtn->boundingBox().containsPoint(location) && isTouchHome == false) {
            CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
            //            homeBtn->setScale(1.2);
            //            touchSprite = homeBtn;

            this->goToShowInterstitial();
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
            homeBtn->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(_dressScene, callfunc_selector(DressScene::returnLastScene))));
            //            _gameScene->selectMenuBtn(158);
            isTouchHome = true;
        }
        
        CCLayer* sysMenuLayer = (CCLayer*)_dressScene->getChildByTag(kSysMenuLayerTag);
        if (sysMenuLayer != NULL) {
            CCSprite* menuGroup = (CCSprite*)sysMenuLayer->getChildByTag(kMenuGroupTag);
            if (menuGroup != NULL && menuGroup->boundingBox().containsPoint(location) && isCanTouchMenu == true) {
                isCanTouchMenu = false;
                //            CCBAnimationManager* animation = (CCBAnimationManager*)sysMenuLayer->getUserObject();
                //            animation->setAnimationCompletedCallback(_dressScene, callfunc_selector(DressScene::completedMenuAnim));
                if (isShowSysMenu == true) {
                    isShowSysMenu = false;
                    //                animation->runAnimationsForSequenceNamed("reMenuGroupAnim");
                    _dressScene->runMenuAnim(false);
                    _dressScene->setAnotherFrame(menuGroup, "cancel");
                }else if (isShowSysMenu == false) {
                    isShowSysMenu = true;
                    //                animation->runAnimationsForSequenceNamed("menuGroupAnim");
                    _dressScene->runMenuAnim(true);
                    
                    _dressScene->setMenuBtnInVis();
                }
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/sysMenuAnim.mp3");
            }
        }
        
        if (isShowSysMenu == true) {
            _dressScene->touchMenuBtn(location);
        }
        
        CCLayer* catLayer = (CCLayer*)_dressScene->getChildByTag(kCatLayerTag);
        if (catLayer != NULL) {
            CCLayer* toyLayer = (CCLayer*)catLayer->getChildByTag(kToyLayerTag);
            CCSprite* toy;
            CCPoint toyLocation;
            if (toyLayer!=NULL) {
                toy = (CCSprite*)toyLayer->getChildByTag(kToyTag);
                toyLocation = toyLayer->convertToNodeSpace(location);
            }else {
                toy = (CCSprite*)catLayer->getChildByTag(kToyTag);
                toyLocation = catLayer->convertToNodeSpace(location);
            }
            if (toy!=NULL && toy->boundingBox().containsPoint(toyLocation) && isRunToy == false && toy->getScaleY() == 1.0) {
                isRunToy = true;
                _dressScene->showCCBToyAnim();
            }
        }
        
        
        if (curChest!=NULL) {
            
            CCScrollView* scroll = (CCScrollView*)curChest->getChildByTag(kScrollViewTag);
            CCLayer* scrollLayer = (CCLayer*)scroll->getChildByTag(kScrollLayerTag);
            for (int i = 0; i < curItemNum; i++) {
                CCSprite* item = (CCSprite*)scrollLayer->getChildByTag(i+kItemTag);
                
                CCPoint newLocation = scrollLayer->convertToNodeSpace(location);
                if (item!=NULL && item->boundingBox().containsPoint(newLocation) && scroll->isDragging()) {
                    touchSprite = item;
                    scrollInitY = location.y;
                    break;
                }
            }
        }
    }
}

void DressScene::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
    
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCLayer* buyLayer = (CCLayer*)_dressScene->getChildByTag(kBuyLayerTag);
    if (!buyLayer) {
        
        _dressScene->eyeMove(location);
        
        if (curChest!=NULL) {
            CCPoint scrollLoc = curChest->convertToNodeSpace(location);
            CCScrollView* scroll = (CCScrollView*)curChest->getChildByTag(kScrollViewTag);
            CCLayer* scrollLayer = (CCLayer*)scroll->getChildByTag(kScrollLayerTag);
            CCPoint newLocation = scrollLayer->convertToNodeSpace(location);
            double disY = fabs(scrollInitY-location.y);
            if (scroll != NULL && scroll->boundingBox().containsPoint(scrollLoc) && disY > 5.00) {
                touchSprite = NULL;
            }
        }
    }
}

void DressScene::goToShowInterstitial() {
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") == false){
        GameManager::sharedManager()->showInterstitial();
    }

}

void DressScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    if (_dressScene!=NULL){
    _dressScene->eyeRevert();
    
    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
    
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCScrollView* scroll;
    CCPoint newLoc;
    
    CCLayer* buyLayer = (CCLayer*)_dressScene->getChildByTag(kBuyLayerTag);
    if (!buyLayer) {
        if (curChest!=NULL) {
            
            scroll = (CCScrollView*)curChest->getChildByTag(kScrollViewTag);
            CCLayer* scrollLayer = (CCLayer*)scroll->getChildByTag(kScrollLayerTag);
            
            CCPoint scrollLoc = curChest->convertToNodeSpace(location);
            if (scroll != NULL && scroll->boundingBox().containsPoint(scrollLoc)) {
                isCanTouchItem = true;
            }
            
            newLoc = scrollLayer->convertToNodeSpace(location);
        }
        
        if (touchSprite != NULL && touchSprite->boundingBox().containsPoint(newLoc)) {
            CCLOG("---------->%d",touchSprite->getTag());
            if (selTag != touchSprite->getTag() || (curSelType != selectedType && selectedType != 0) || touchSprite->getTag() == kItemTag) {
                if (touchSprite->getTag() == kItemTag) {
                    _dressScene->removeItemSpr(touchSprite->getTag());
                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
                }
//#if defined(NEW_ID) || defined(OLD)
//                else if (touchSprite->getTag() == curItemNum+kItemTag-1 && !CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll")) {
//                    if (selectedType == kCLOTHE) {
//                        _dressScene->goInStore(2);
//                    }else if (selectedType == kTOY) {
//                        _dressScene->goInStore(2);
//                    }else if (selectedType == kSET) {
//                        _dressScene->goInStore(2);
//                    }else {
//                        _dressScene->goInStore(2);
//                    }
//                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
//                }
//#endif
                else {
                    CCSprite* lock = (CCSprite*)touchSprite->getChildByTag(kLockTag);
                    if (lock == NULL) {
                        _dressScene->wearItem(touchSprite->getTag(),location,true);
                    }else{
                        if (selectedType == kCLOTHE) {
                            _dressScene->goInStore(2);
                        }else if (selectedType == kTOY) {
                            _dressScene->goInStore(2);
                        }else if (selectedType == kSET) {
                            _dressScene->goInStore(2);
                        }else {
                            _dressScene->goInStore(2);
                        }
                        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchItem.mp3");
                    }
                }
            }
            touchSprite = NULL;
        }
    }
    }
}

void DressScene::removeItemSpr(int tag){
    CCString* selectName = _dressScene->getItemType(selectedType);
    CCSprite* sprite = (CCSprite*)weardGroup->objectForKey(selectName->getCString());
    CCSprite* moveSpr = (CCSprite*)movingGroup->objectForKey(selectName->getCString());
    int newTag;
    if (selectedType == kSET) {
        newTag = weardGroup->valueForKey(selectName->getCString())->intValue();
    }
    if (sprite != NULL && selectedType!=kSET && moveSpr == NULL) {
        _dressScene->unschedule(schedule_selector(DressScene::setParticle));
        
        _dressScene->setSprColor(sprite->getTag()-kItemTag, selectName->getCString(), false);
        sprite->removeAllChildrenWithCleanup(true);
        sprite->removeFromParentAndCleanup(true);
        sprite = NULL;
        weardGroup->removeObjectForKey(selectName->getCString());
        selItemGroup->removeObjectForKey(selectName->getCString());
        selTag = tag;
    }else if (selectedType == kSET && newTag != 0) {
        _dressScene->unschedule(schedule_selector(DressScene::setParticle));
        _dressScene->setSprColor(newTag, selectName->getCString(), false);
        CCDictionary* setInfo = CatDressManager::sharedManager()->getDictionary("setInformation.plist", NULL);
        CCDictionary* itemSetInfo = CatDressManager::sharedManager()->getDictionary(CCString::createWithFormat("set%d",newTag)->getCString(), setInfo);
        
        //    _gameScene->removeAllItem();
        CCArray* keys = itemSetInfo->allKeys();
        if (keys != NULL) {
            for (int i = 0; i < keys->count(); i++) {
                CCString* key = (CCString*)keys->objectAtIndex(i);
                if (key!=NULL) {
                    CCSprite* sprite = (CCSprite*)weardGroup->objectForKey(key->getCString());
                    int sprIndex = itemSetInfo->valueForKey(key->getCString())->intValue();
                    int sprTag = selItemGroup->valueForKey(key->getCString())->intValue();
                    if (sprite != NULL && sprTag-kItemTag == sprIndex) {
                        _dressScene->unschedule(schedule_selector(DressScene::setParticle));
                        _dressScene->setSprColor(sprite->getTag()-kItemTag, key->getCString(), false);
                        sprite->removeAllChildrenWithCleanup(true);
                        sprite->removeFromParentAndCleanup(true);
                        //                        if (strcmp(key->getCString(), "toy") == 0) {
                        //                            CC_SAFE_DELETE(sprite);
                        //                        }else {
                        sprite = NULL;
                        //                        }
                        
                        weardGroup->removeObjectForKey(key->getCString());
                        selItemGroup->removeObjectForKey(key->getCString());
                    }
                }
            }
        }
        weardGroup->removeObjectForKey(selectName->getCString());
        selItemGroup->removeObjectForKey(selectName->getCString());
        selTag = tag;
    }
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void DressScene::removeAllItem(){
    CCArray* keys = weardGroup->allKeys();
    if (keys != NULL) {
        //        bool isClean = false;
        for (int i = 0; i < keys->count(); i++) {
            CCString* key = (CCString*)keys->objectAtIndex(i);
            if (key!=NULL && strcmp(key->getCString(), "set") != 0) {
                CCSprite* sprite = (CCSprite*)weardGroup->objectForKey(key->getCString());
                CCSprite* moveSpr = (CCSprite*)movingGroup->objectForKey(key->getCString());
                if (sprite != NULL && moveSpr == NULL) {
                    _dressScene->unschedule(schedule_selector(DressScene::setParticle));
                    _dressScene->setSprColor(sprite->getTag()-kItemTag, key->getCString(), false);
                    sprite->removeAllChildrenWithCleanup(true);
                    sprite->removeFromParentAndCleanup(true);
                    sprite = NULL;
                    weardGroup->removeObjectForKey(key->getCString());
                    selItemGroup->removeObjectForKey(key->getCString());
                }
            }else if (key != NULL && strcmp(key->getCString(), "set") == 0){
                int newTag = weardGroup->valueForKey(key->getCString())->intValue();
                if (newTag != 0) {
                    _dressScene->setSprColor(newTag, key->getCString(), false);
                    newTag = 0;
                    weardGroup->removeObjectForKey(key->getCString());
                    selItemGroup->removeObjectForKey(key->getCString());
                }
            }
        }
        SimpleAudioEngine::sharedEngine()->unloadEffect(CCString::createWithFormat("mp3/toy/toy_%d.mp3",selectedToyTag)->getCString());
        //        if (isClean == true) {
        //            weardGroup->removeAllObjects();
        //            selItemGroup->removeAllObjects();
        //        }
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
}

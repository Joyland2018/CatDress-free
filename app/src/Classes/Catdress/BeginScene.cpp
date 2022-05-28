//
//  BeginScene.cpp
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-4.
//
//

#include "BeginScene.h"
#include "GameManager.h"
#include "CatSelectScene.h"
#include "CatDressManager.h"

enum{
    kBeginTag = 1,
    kMoreGameTag = 2,
    kStarTag = 20,
    kBackLayerTag = 499,
    kLockBackTag = 599,
    kLockMenuTag = 699,
    kJPBtnTag = 799,
};

CCScene* BeginScene::scene(){
    CCScene* scene = CCScene::create();
    
    BeginScene* layer = BeginScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool BeginScene::init(){
    if (!CCLayer::init()) {
        return false;
    }
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint center = GameManager::sharedManager()->getCenter();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
    CCPoint rightBottom = GameManager::sharedManager()->getRightBottomPos();
    CCPoint leftTop = GameManager::sharedManager()->getLeftTopPos();
    bool isSilence = CCUserDefault::sharedUserDefault()->getBoolForKey("isSound");
    bool isChangeSound = CCUserDefault::sharedUserDefault()->getBoolForKey("isChangeSound");
    if (isSilence == false && isChangeSound == true) {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
    }

    if (CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") == false){
        //导量
        bt_firstword = CCSprite::create("otherGame_FirstWords.png");
        bt_shapepuzzle = CCSprite::create("otherGame_ShapePuzzle.png");
        bt_wordblock = CCSprite::create("otherGame_WordBlock.png");
        bt_wordbreak = CCSprite::create("otherGame_WordBreak.png");
        bt_Jorland = CCSprite::create("otherGame_Joyland.png");
        bt_Match = CCSprite::create("otherGame_Match.png");
        bt_ad = CCSprite::create("ad.png");
        bt_background = CCSprite::create("background.png");

        bt_firstword->setPosition(ccp(leftTop.x+bt_firstword->getContentSize().width/2.0+5,leftTop.y-bt_firstword->getContentSize().height/2.0+5));
        bt_firstword->setScale(0.65);
        bt_shapepuzzle->setPosition(ccp(leftTop.x+bt_shapepuzzle->getContentSize().width/2.0+5,leftTop.y-bt_shapepuzzle->getContentSize().height/2.0-95));
        bt_shapepuzzle->setScale(0.65);
        bt_wordblock->setPosition(ccp(leftTop.x+bt_wordblock->getContentSize().width/2.0+5,leftTop.y-bt_wordblock->getContentSize().height/2.0-195));
        bt_wordblock->setScale(0.65);
        bt_wordbreak->setPosition(ccp(leftTop.x+bt_wordbreak->getContentSize().width/2.0+5,leftTop.y-bt_wordbreak->getContentSize().height/2.0-295));
        bt_wordbreak->setScale(0.65);
        bt_Jorland->setPosition(ccp(leftTop.x+bt_Jorland->getContentSize().width/2.0+5,leftTop.y-bt_Jorland->getContentSize().height/2.0-395));
        bt_Jorland->setScale(0.65);
        bt_Match->setPosition(ccp(leftTop.x+bt_Match->getContentSize().width/2.0+5,leftTop.y-bt_Match->getContentSize().height/2.0-495));
        bt_Match->setScale(0.65);
        bt_ad->setPosition(ccp(leftBottom.x+bt_ad->getContentSize().width/2.0,leftBottom.y+bt_ad->getContentSize().height/2.0+12));
        bt_background->setPosition(ccp(leftTop.x+bt_background->getContentSize().width/2.0,leftTop.y-bt_background->getContentSize().height/2.0-240));
        bt_background->setScaleY(4);

        this->addChild(bt_background,1);
        this->addChild(bt_firstword,1);
        this->addChild(bt_shapepuzzle,1);
        this->addChild(bt_wordblock,1);
        this->addChild(bt_wordbreak,1);
        this->addChild(bt_Jorland,1);
        this->addChild(bt_Match,1);
        this->addChild(bt_ad,1);

    }


    starInfo = CatDressManager::sharedManager()->getDictionary("begin/starInformation.plist", NULL);
    starInfo->retain();
    
    CCSprite* background = CCSprite::create("background/beginScene.png");
    background->setPosition(center);
    this->addChild(background);
    
    CCSprite* beginBtn = CCSprite::create("begin/begin.png");
    beginBtn->setPosition(ccp(rightBottom.x - beginBtn->getContentSize().width/2, rightBottom.y + beginBtn->getContentSize().height*0.7));
    beginBtn->setTag(kBeginTag);
    this->addChild(beginBtn);
    
    CCScaleBy* scaleBy = CCScaleBy::create(0.4, 0.7);
    //    CCScaleBy* reScaleBy = CCScaleBy::create(0.4, 1.2);
    CCRepeatForever* repeat = CCRepeatForever::create(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()));
    beginBtn->runAction(repeat);
    
//    CCSprite* moreBg = CCSprite::create("ui/moreGames.png");
//    if (winSize.width == 1024) {
//        moreBg->setPosition(ccp(winSize.width/10, winSize.height*0.95));
//    }else if (winSize.width == 1363){
//        moreBg->setPosition(ccp(winSize.width/10.5, winSize.height*0.95));
//    }else{
//        moreBg->setPosition(ccp(winSize.width/9.2, winSize.height*0.95));
//    }
//    this->addChild(moreBg);
//    
//    for (int i = 0; i < 6; i++) {
//        CCSprite* moreGame = CCSprite::create(CCString::createWithFormat("game%d_free.png",i+1)->getCString());
//        if (winSize.width == 1024) {
//            moreGame->setPosition(ccp(winSize.width/10, winSize.height*9/11 - i*winSize.height/7));
//        }else if (winSize.width == 1363){
//            moreGame->setPosition(ccp(winSize.width/10.5, winSize.height*10/13+30 - i*winSize.height/7));
//        }else{
//            moreGame->setPosition(ccp(winSize.width/9.2, winSize.height*10/13+30 - i*winSize.height/7));
//        }
//        
//        moreGame->setTag(i+kMoreGameTag);
//        this->addChild(moreGame);
//    }
    
    for (int i = 0; i < 4; i++) {
        CCSprite* star = CCSprite::create("begin/star.png");
        CCPoint starPos = CatDressManager::sharedManager()->getPos(CCString::createWithFormat("star%dPos",i+1)->getCString(), starInfo);
        star->setPosition(ccp(leftBottom.x+winSize.width*starPos.x, leftBottom.y+winSize.height*starPos.y));
        star->setRotation(M_PI*i);
        star->setTag(kStarTag+i);
        this->addChild(star);
        
        CCBlink* blink = CCBlink::create(4+i, i+1);
        CCRepeatForever* repeat = CCRepeatForever::create(blink);
        star->runAction(repeat);
    }
    
    int preBtnRan = arc4random()%6+1;
    
//    CCString* jptIconUrl = CCString::createWithFormat("begin/joyPreBtn%d.png",preBtnRan);
    
//    CCMenuItemImage* jptBtn = CCMenuItemImage::create(jptIconUrl->getCString(), jptIconUrl->getCString(), this, menu_selector(BeginScene::createParentsLock));
//    CCSize jptSize = jptBtn->getContentSize();
//    CCPoint jptPos = CCPoint(leftTop.x+jptBtn->getContentSize().width/2+10, leftTop.y-jptBtn->getContentSize().height/2-10);
//    jptBtn->setPosition(jptPos);
//    jptBtn->setTag(kJPBtnTag);
    
    //    CCSprite* share_sel = CCSprite::create("common/share_bt.png");
    //    share_sel->setScale(1.2);
    //    share_sel->setPosition(CCPoint(-share_sel->getContentSize().width/12, -share_sel->getContentSize().height/12));
    //    CCMenuItemSprite* shareMenuItem = CCMenuItemSprite::create(CCSprite::create("common/share_bt.png"), share_sel, this, menu_selector(BeginScene::createParentsLock));
    //    shareMenuItem->setPosition(ccp(rightTop.x - share_sel->getContentSize().width/2, rightTop.y - share_sel->getContentSize().height/2));
    //    shareMenuItem->setTag(kShareTag);
    //    CCMenuItemImage* game4Btn = CCMenuItemImage::create("parent/a2.png", "parent/a2.png",this,menu_selector(BeginScene::createParentsLock));
    //    game4Btn->setPosition(ccp(parentBtn->getPosition().x, game3Btn->getPosition().y-game4Btn->getContentSize().height*1.2));
    //    game4Btn->setTag(kGameBtnTag+4);
    
    //    CCMenu* parentMenu = CCMenu::create(parentBtn,game1Btn,game2Btn,game3Btn,game4Btn,game5Btn,shareMenuItem,NULL);
    
//    CCMenu* parentMenu = CCMenu::create(jptBtn,NULL);
//    parentMenu->setPosition(CCPointZero);
//    this->addChild(parentMenu);
    
    touchSprite = NULL;
    
    this->setTouchEnabled(true);
    
    //    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("begin.mp3", true);
    
    return true;
}

//导量按钮


BeginScene::BeginScene(){
    
}

BeginScene::~BeginScene(){
    starInfo->release();
    this->removeAllChildrenWithCleanup(true);
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void BeginScene::createParentsLock(cocos2d::CCObject *sender){
    CCSize winsize = CCEGLView::sharedOpenGLView()->getVisibleSize();
    CCPoint center = GameManager::sharedManager()->getCenter();
//    DownloadLayer* downloadLayer = (DownloadLayer*)this->getChildByTag(kDownloadLayerTag);
    
//    if (downloadLayer == NULL) {
        CCLayer *blacklayer = (CCLayer*)this->getChildByTag(kBackLayerTag);
        
        if (blacklayer == NULL) {
            //    CCSprite *back = (CCSprite*)this->getChildByTag(kParentLockTag);
            //    CCMenu *menu = (CCMenu*)back->getChildByTag(kParentMenuTag);
            //    menu->setEnabled(false);
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/pressBt.mp3");
            accessIndex = 0;
            
            moreGameTag = ((CCMenuItemImage*)sender)->getTag();
            
            CCLayerColor *blacklayer = CCLayerColor::create(ccc4(0, 0, 0, 180), winsize.width, winsize.height);
            blacklayer->ignoreAnchorPointForPosition(false);
            blacklayer->setTag(kBackLayerTag);
            blacklayer->setPosition(center);
            this->addChild(blacklayer,100);
            
            CCSprite* lock_back = CCSprite::create("lock/di.png");
            lock_back->setPosition(ccp(blacklayer->boundingBox().size.width/2, blacklayer->boundingBox().size.height/2));
            lock_back->setTag(kLockBackTag);
            blacklayer->addChild(lock_back);
            
            CCSprite* mulTag = CCSprite::create("lock/jia.png");
            mulTag->setPosition(CCPoint(lock_back->boundingBox().size.width*0.34, lock_back->boundingBox().size.height*0.82));
            lock_back->addChild(mulTag);
            
            CCSprite* equalTag = CCSprite::create("lock/deng.png");
            equalTag->setPosition(CCPoint(lock_back->boundingBox().size.width*0.53, lock_back->boundingBox().size.height*0.82));
            lock_back->addChild(equalTag);
            
            
            for (int i=0; i<2; i++) {
                if (i == 0) {
                    locknum[0] = arc4random() % 3+7;
                }else if (i == 1) {
                    locknum[1] = arc4random() % 8+2;
                    if (locknum[0]+locknum[1] == 9) {
                        locknum[1]+=2 ;
                    }
                    if (locknum[0]+locknum[1] == 10) {
                        locknum[1]+=1 ;
                    }
                }
                CCSprite* lable = CCSprite::create(CCString::createWithFormat("lock/w%d.png", locknum[i])->getCString());
                lable->setPosition(ccp(lock_back->boundingBox().size.width*0.43 + (i - 1)*lable->boundingBox().size.width*1.5, lock_back->boundingBox().size.height*0.82));
                lock_back->addChild(lable);
            }
            
            
            CCMenu* lockmenu = CCMenu::create();
            lockmenu->setPosition(CCPointZero);
            lockmenu->setTag(kLockMenuTag);
            for (int i=0; i<9; i++) {
                CCMenuItemImage* num = CCMenuItemImage::create(CCString::createWithFormat("lock/%d.png", i+1)->getCString(), CCString::createWithFormat("lock/%d.png", i+1)->getCString(), this, menu_selector(BeginScene::parentsLockCallback));
                num->setTag(i);
                int acX = i % 3 - 2;
                int acY = i / 3 - 1;
                num->setPosition(ccp(lock_back->boundingBox().size.width*0.745 + acX*(num->boundingBox().size.width+20), lock_back->boundingBox().size.height*0.68 - acY*(num->boundingBox().size.height - 5) - 143));
                lockmenu->addChild(num);
            }
            
            
            CCMenuItemImage* close = CCMenuItemImage::create("lock/x.png", "lock/x.png", this, menu_selector(BeginScene::parentsLockCallback));
            close->setTag(40);
            close->setPosition(ccp(lock_back->boundingBox().size.width - 30, lock_back->boundingBox().size.height - 30));
            lockmenu->addChild(close);
            
            
            lock_back->addChild(lockmenu);
        }
//    }
}

void BeginScene::parentsLockCallback(cocos2d::CCObject *sender){
    SimpleAudioEngine::sharedEngine()->playEffect("pressBt.mp3");
    CCLayer *blacklayer = (CCLayer*)this->getChildByTag(kBackLayerTag);
    CCSprite* lockback = (CCSprite*)blacklayer->getChildByTag(kLockBackTag);
    //    CCMenu *menu = (CCMenu*)lockback->getChildByTag(LOCK_MENU);
    
    
    int tag = ((CCMenuItem*)sender)->getTag();
    
    if (tag < 9) {
        CCSprite* show = CCSprite::create(CCString::createWithFormat("lock/w%d.png", tag+1)->getCString());
        show->setPosition(ccp(lockback->boundingBox().size.width*0.75 + (accessIndex - 1)*(show->boundingBox().size.width*0.9), lockback->boundingBox().size.height*0.82));
        show->setTag(20 + accessIndex);
        lockback->addChild(show);
        
        accessnum[accessIndex++] = tag+1;
        
    }
    
    if (tag == 40) {
        blacklayer->removeFromParentAndCleanup(true);
        //        CCSprite *back = (CCSprite*)this->getChildByTag(BACK);
        //        CCMenu *menu = (CCMenu*)back->getChildByTag(MENU);
        //        menu->setEnabled(true);
    }
    
    
    
    if (accessIndex > 1){
        accessIndex = 0;
        int result = locknum[0]+locknum[1] ;
        int inputNumber = (accessnum[0])*10+ (accessnum[1]);
        bool flag = false;
        if (result == inputNumber) {
            flag = true ;
        }
        
        if (flag) {
            //            blacklayer->removeFromParentAndCleanup(true);
            blacklayer->scheduleOnce(schedule_selector(CCNode::removeFromParentAndCleanup), 0.1);
            //            CCSprite *back = (CCSprite*)this->getChildByTag(BACK);
            //            CCMenu *menu = (CCMenu*)back->getChildByTag(MENU);
            //            menu->setEnabled(true);
            
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            //            if (moreGameTag == kParentBtnTag){
            //                CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ParentScene::scene(), ccBLACK));
            //            }else if (moreGameTag == kGameBtnTag+1){
            //                DeviceManager::sharedManager()->getURL(7);
            //            }else if (moreGameTag == kGameBtnTag+2){
            //                DeviceManager::sharedManager()->getURL(0);
            //            }else if (moreGameTag == kGameBtnTag+3){
            //                DeviceManager::sharedManager()->getURL(5);
            //            }else if (moreGameTag == kGameBtnTag+4){
            //                DeviceManager::sharedManager()->getURL(1);
            //            }else if (moreGameTag == kGameBtnTag+5){
            ////                DeviceManager::sharedManager()->getURL(16);
            //                DeviceManager::sharedManager()->getURL(15);
            //            }else if (moreGameTag == kShareTag){
            //                DeviceManager::sharedManager()->shareLinkWithShareDialog();
            //            }else if (moreGameTag == kJPBtnTag){
            //                DeviceManager::sharedManager()->getURL(18);
            //            }
            DeviceManager::shareManager()->showWebView();
#endif
        }else{
            for (int i=0; i<2; i++) {
                CCSprite* sprite = (CCSprite*)lockback->getChildByTag(20 + i);
                sprite->scheduleOnce(schedule_selector(CCNode::removeFromParentAndCleanup), 0.1);
            }
        }
    }
}

void BeginScene::touchStar(CCSprite* _sprite){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCMoveTo* moveTo = CCMoveTo::create(1, ccp(_sprite->getPosition().x+winSize.width/10, _sprite->getPosition().y+winSize.height/20));
    CCScaleTo* scaleTo = CCScaleTo::create(1, 0.1);
    CCRotateBy* rotateBy = CCRotateBy::create(1, 960);
    CCSpawn* spawn = CCSpawn::createWithTwoActions(moveTo, scaleTo);
    CCSpawn* spawnOther = CCSpawn::createWithTwoActions(spawn, rotateBy);
    
    _sprite->runAction(CCSequence::createWithTwoActions(spawnOther, CCCallFuncND::create(this, callfuncND_selector(BeginScene::revertStar), (int*)(intptr_t)_sprite->getTag())));
    int starSoundTag = arc4random()%4+1;
    SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mp3/star%d.mp3",starSoundTag)->getCString());
}

void BeginScene::revertStar(cocos2d::CCNode *sender, int _tag){
    int sprTag = _tag - kStarTag;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint starPos = CatDressManager::sharedManager()->getPos(CCString::createWithFormat("star%dPos",sprTag+1)->getCString(), starInfo);
    sender->setPosition(ccp(winSize.width*starPos.x, winSize.height*starPos.y));
    sender->setScale(1);
    sender->setRotation(M_PI*sprTag);

    CCBlink* blink = CCBlink::create(4+sprTag, sprTag+1);
    CCRepeatForever* repeat = CCRepeatForever::create(blink);
    sender->runAction(repeat);
}

void BeginScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
    
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCSprite* beginBtn = (CCSprite*)this->getChildByTag(kBeginTag);
    if (beginBtn != NULL && beginBtn->boundingBox().containsPoint(location)) {
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/touchButton.mp3");
        
        beginBtn->stopAllActions();
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, CatSelectScene::sceneWithID(0), ccWHITE));
    }

    if (CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") == false){
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
        for (int i = 0; i < 6; i++) {
            CCSprite* moreGame = (CCSprite*)this->getChildByTag(i+kMoreGameTag);
            if (moreGame != NULL && moreGame->boundingBox().containsPoint(location)) {
                moreGame->setScale(1.15);
                touchSprite = moreGame;
            }
        }
    }


    
    for (int i = 0; i < 4; i++) {
        CCSprite* star = (CCSprite*)this->getChildByTag(kStarTag+i);
        if (star != NULL && star->boundingBox().containsPoint(location) && star->getScale() == 1.0) {
            this->touchStar(star);
        }
    }
}

void BeginScene::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    
}

void BeginScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
    
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    if (touchSprite != NULL && touchSprite->boundingBox().containsPoint(location)) {
        touchSprite->setScale(1.0);
//        DeviceManager::shareManager()->selectURL(touchSprite->getTag());
        touchSprite = NULL;
    }
}

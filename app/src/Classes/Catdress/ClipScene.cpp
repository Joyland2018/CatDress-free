//
//  ClipScene.cpp
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-4.
//
//

#include "ClipScene.h"
//#include "HospitalScene.h"
#include "CatSelectScene.h"
#define ADJUST_ANIM_VELOCITY 800;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "BuyPage.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

enum{
    kHomeBtnTage = 1,
    kBatchNodeTag = 2,
    kBatchChildTag = 3,
    kBackSprTag = 4,
    kMaskNailTag = 5,
    kCatPawTag = 10,
    kPawTag = 20,
    kThornTag = 30,
    kNailPolishTag = 40,
    kNailFlowerTag = 50,
    kCollisionAreaTag = 70,
    kScrollViewTag = 100,
    kScrollLayerTag = 101,
    kLayerSpriteTag = 102,
    kNailPolishLayerTag = 103,
    kNailFlowerLayerTag = 104,
    kMaskInViewTag = 110,
    kForcepsTag = 120,
    kNailTag = 121,
    kBrushTage = 122,
    kPlateTag = 123,
    kDrawLayerTag = 200,
    kCleanTag = 500,
    kFlowerColTag = 600,
    kFlowerInViewTag = 700,
    kPointTag = 999,
    kPointBgTag = 1000,
};

CCScene* ClipScene::sceneWithID(int _catID){
    CCScene* scene = CCScene::create();
    
    ClipScene* layer = ClipScene::nodeWithID(_catID);
    
    scene->addChild(layer);
    
    return scene;
}

ClipScene* ClipScene::nodeWithID(int _animalID){
    ClipScene* layer = new ClipScene();
    if (layer->initWithID(_animalID)) {
        layer->autorelease();

        return layer;
    }else {
        return NULL;
    }
}

bool ClipScene::initWithID(int _animalID){
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("clip/clearTools.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("clip/nailPolishAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("clip/nailFlowerSet.plist");
    
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint center = GameManager::sharedManager()->getCenter();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
    
    rendertexture = CCRenderTexture::create(winSize.width, winSize.height);
    rendertexture->retain();
    
    CCDictionary* catInfo = CatDressManager::sharedManager()->getDictionary("clip/clipInformation.plist", NULL);
    nailPolishInfo = CatDressManager::sharedManager()->getDictionary("nailPolishInfo", catInfo);
    nailPolishInfo->retain();
    
    touchSprite = NULL;
    touchSpriteInPos = CCPointZero;
    isCutting = false;
    isTouchHome = false;
    isPlayPolishSound = false;
    touchNailPolishTag = 0;
    touchNailFlowerTag = 0;
    curLayerTag = 0;
    colPointTag = -1;
    curCatID = _animalID;
    
//    CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create("clip/maskBg.png");
//    batchNode->setPosition(ccp(winSize.width/2, winSize.height/2));
//    batchNode->setTag(kBatchNodeTag);
//    this->addChild(batchNode);
    
    DrawSprite* drawLayer = DrawSprite::create("clip/maskBg.png");
//    drawLayer->setPosition(ccp(winSize.width*0.498, winSize.height*10));
    drawLayer->setTag(kDrawLayerTag);
//    drawLayer->setScale(1.2);
    this->addChild(drawLayer);
    
//    CCSprite* batchBg = CCSprite::createWithTexture(batchNode->getTexture());
//    batchBg->setTag(kDrawLayerTag);
//    batchNode->addChild(batchBg);
    
    
    
    CCDictionary* flowerColInfo = CatDressManager::sharedManager()->getDictionary("areaViewInfo", catInfo);
    
    for (int i = 0; i < flowerColInfo->count(); i++) {
//      CCSprite* flowCol = CCSprite::create("catdress/clip/collisionArea2.png");
        CCSprite* flowCol = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("nailFlower1.png")->getCString());
        CCPoint areaPos = CatDressManager::sharedManager()->getPos(CCString::createWithFormat("pawArea%d",i+1)->getCString(), flowerColInfo);
        flowCol->setPosition(ccp(leftBottom.x+winSize.width/2+(areaPos.x*0.83), leftBottom.y+winSize.height*areaPos.y));
        flowCol->setTag(kFlowerColTag+i);
        flowCol->setScale(0.83);
        this->addChild(flowCol,2);
    }
    
    flowerColNum = flowerColInfo->count();
    
    CCSprite* background = CCSprite::create("background/clip_background.png");
    background->setPosition(center);
    this->addChild(background,2);
    if (GameManager::sharedManager()->isIphoneX()) {
        background->setScale(1.3);
    }
    
    CCSprite* catPaw = CCSprite::create("clip/catPaw.png");
    catPaw->setPosition(ccp(leftBottom.x+winSize.width/2, leftBottom.y+winSize.height*1.5));
    catPaw->setTag(kCatPawTag);
    
    CCLayer* scrollLayer = CCLayer::create();
    
    CCSprite* layerSpr = CCSprite::create();
    layerSpr->setContentSize(winSize);
    layerSpr->setPosition(ccp(winSize.width/2, winSize.height/2));
    layerSpr->setTag(kLayerSpriteTag);
    scrollLayer->addChild(layerSpr);
    
    scrollLayer->setTag(kScrollLayerTag);
    scrollLayer->setContentSize(CCSizeMake(winSize.width*3, winSize.height));
    
    scrollView = CCScrollView::create(CCSizeMake(winSize.width, winSize.height),scrollLayer);
    scrollView->setPosition(leftBottom);
    scrollView->setTag(kScrollViewTag);
    scrollView->setTouchEnabled(false);
    scrollView->setDelegate(this);
    scrollView->setDirection(kCCScrollViewDirectionHorizontal);
    scrollView->setContentSize(CCSizeMake(winSize.width*3, winSize.height));
    scrollView->setContentOffset(scrollView->maxContainerOffset());
    
    this->addChild(scrollView,5);
    
    CCDictionary* collisionAreaInfo = CatDressManager::sharedManager()->getDictionary("areaLayerInfo", catInfo);
    
    for (int i = 0; i < collisionAreaInfo->count(); i++) {
        CCSprite* collisionArea = CCSprite::create("clip/collisionArea.png");
//        CCSprite* collisionArea = CCSprite::create("universal/back.png");
        CCPoint areaPos = CatDressManager::sharedManager()->getPos(CCString::createWithFormat("pawArea%d",i+1)->getCString(), collisionAreaInfo);
        collisionArea->setPosition(ccp(catPaw->getContentSize().width*areaPos.x, catPaw->getContentSize().height*areaPos.y));
        collisionArea->setTag(kCollisionAreaTag+i);
        catPaw->addChild(collisionArea);
        
//        CCPoint worldPoint = catPaw->convertToWorldSpace(ccp(catPaw->getContentSize().width*areaPos.x*0.82, catPaw->getContentSize().height*areaPos.y*0.82));
//        CCLayer* scrollLayer = (CCLayer*)scrollView->getChildByTag(kScrollLayerTag);
//        CCPoint scrollPoint = scrollLayer->convertToNodeSpace(worldPoint);
//        CCSprite* homeBtn = CCSprite::create("universal/back.png");
//        homeBtn->setPosition(scrollPoint);
//        this->addChild(homeBtn, 20);
        
        
    }
    
    collisionAreaNum = collisionAreaInfo->count();
    
    CCTexture2D* texture;
    
    CCDictionary* pawInfo = CatDressManager::sharedManager()->getDictionary("pawInfo", catInfo);
    
    for (int i = 0; i < pawInfo->count(); i++) {
        CCSprite* paw = CCSprite::create(CCString::createWithFormat("clip/paw%d.png",i+1)->getCString());
        CCPoint pawPosInfo = CatDressManager::sharedManager()->getPos(CCString::createWithFormat("paw%d",i+1)->getCString(), pawInfo);
        paw->setPosition(ccp(catPaw->getContentSize().width*pawPosInfo.x, catPaw->getContentSize().height*pawPosInfo.y));
        paw->setTag(kPawTag+i);
        catPaw->addChild(paw,5);
    }
    
    pawNum = pawInfo->count();
    pawCount = pawInfo->count();
    
    CCSprite* maskInLayer = CCSprite::create("clip/pawArea.png");
    maskInLayer->setScale(0.83);
    texture = this->maskedWithSpriteTexture(drawLayer, maskInLayer, ccp(0.498, 0.521));
    CCSprite* maskInView = CCSprite::createWithTexture(texture);
//    CCSprite* maskInView = CCSprite::create("catdress/clip/pawArea.png");
    maskInView->setPosition(ccp(catPaw->getContentSize().width*0.5, catPaw->getContentSize().height*0.129));
    maskInView->setFlipY(true);
    maskInView->setTag(kMaskInViewTag);
    maskInView->setScale(1.2);
    catPaw->addChild(maskInView,3);
    
    CCDictionary* thornInfo = CatDressManager::sharedManager()->getDictionary("thornInfo", catInfo);
    
    for (int i = 0; i < thornInfo->count(); i++) {
        CCSprite* thorn = CCSprite::create(CCString::createWithFormat("clip/thorn%d.png",i+1)->getCString());
        CCDictionary* thornItemInfo = CatDressManager::sharedManager()->getDictionary(CCString::createWithFormat("thorn%d",i+1)->getCString(), thornInfo);
        float angle = thornItemInfo->valueForKey("angle")->intValue();
        CCPoint thornPosInfo = CatDressManager::sharedManager()->getPos("pos", thornItemInfo);
        thorn->setPosition(ccp(catPaw->getContentSize().width*thornPosInfo.x, catPaw->getContentSize().height*thornPosInfo.y));
        thorn->setRotation(angle);
        thorn->setTag(kThornTag+i);
        catPaw->addChild(thorn);
    }
    
    thornNum = thornInfo->count();
    thornCount = thornInfo->count();
    
//    CCLayer* scrollLayer = CCLayer::create();
//    
//    CCSprite* layerSpr = CCSprite::create();
//    layerSpr->setContentSize(winSize);
//    layerSpr->setPosition(ccp(winSize.width/2, winSize.height/2));
//    layerSpr->setTag(kLayerSpriteTag);
//    scrollLayer->addChild(layerSpr);
    
    CCSprite* plate = CCSprite::create("clip/plate.png");
    plate->setPosition(ccp(layerSpr->getContentSize().width/2, winSize.height*0.12));
    plate->setTag(kPlateTag);
    plate->setScale(0.83);
    layerSpr->addChild(plate);
    
    CCSprite* forceps = CCSprite::createWithSpriteFrameName("forceps_0001.png");
    forceps->setPosition(ccp(plate->getContentSize().width*0.20, plate->getContentSize().height*0.515));
    forceps->setTag(kForcepsTag);
    plate->addChild(forceps);
    
    forcepsInPos = forceps->getPosition();
    
    CCJumpBy* forcepsJump = CCJumpBy::create(0.5, CCPointZero, 50, 1);
    forceps->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(0.5), forcepsJump));
    
    CCSprite* nail = CCSprite::createWithSpriteFrameName("nail_0001.png");
    nail->setPosition(ccp(plate->getContentSize().width*0.80, plate->getContentSize().height*0.505));
    nail->setTag(kNailTag);
    plate->addChild(nail);
    
    nailInPos = nail->getPosition();
    
    CCJumpBy* nailJump = CCJumpBy::create(0.5, CCPointZero, 50, 1);
    nail->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(1), nailJump));
    
    CCSprite* nailPolishLayer = CCSprite::create();
    nailPolishLayer->setContentSize(winSize);
    nailPolishLayer->setPosition(ccp(winSize.width*3/2, winSize.height/2));
    nailPolishLayer->setTag(kNailPolishLayerTag);
    scrollLayer->addChild(nailPolishLayer);
    
    for (int i = 0; i < nailPolishInfo->count(); i++) {
        CCSprite* nailPolish = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("nailPolish%d_0001.png",i+1)->getCString());
        nailPolish->setPosition(ccp(winSize.width*(0.1+i*0.16), winSize.height*0.163));
        nailPolish->setTag(kNailPolishTag+i);
        nailPolish->setScale(0.83);
        nailPolishLayer->addChild(nailPolish);
    }
    
    nailPolishNum = nailPolishInfo->count();
    
    CCSprite* nailFlowerLayer = CCSprite::create();
    nailFlowerLayer->setContentSize(winSize);
    nailFlowerLayer->setPosition(ccp(winSize.width*5/2, winSize.height/2));
    nailFlowerLayer->setTag(kNailFlowerLayerTag);
    scrollLayer->addChild(nailFlowerLayer);
    
    for (int i = 0; i < 10; i++) {
        CCSprite* nailFlower = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("nailFlower%d.png",i+1)->getCString());
        nailFlower->setPosition(ccp(winSize.width*(0.05+i*0.10), winSize.height*0.124));
        nailFlower->setTag(kNailFlowerTag+i);
        nailFlower->setScale(0.83);
        nailFlowerLayer->addChild(nailFlower);
    }
    
    CCPoint initPointPos;
    
    for (int i = 0; i < 2; i++) {
        CCSprite* pointBg = CCSprite::create("pointBg.png");
        pointBg->setPosition(ccp(leftBottom.x+winSize.width*0.47+i*winSize.width/23, leftBottom.y+winSize.height/3));
        if (i == 0) {
            initPointPos = pointBg->getPosition();
        }
        pointBg->setVisible(false);
        pointBg->setTag(i+kPointBgTag);
        pointBg->setScale(0.83);
        this->addChild(pointBg,3);
    }
    
    CCSprite* point = CCSprite::create("point.png");
    point->setPosition(initPointPos);
    point->setVisible(false);
    point->setTag(kPointTag);
    point->setScale(0.83);
    this->addChild(point,3);
    
    CCSprite* homeBtn = CCSprite::create("back.png");
    homeBtn->setPosition(ccp(leftBottom.x+winSize.width/16, leftBottom.y+winSize.height*11/12));
    homeBtn->setTag(kHomeBtnTage);
    this->addChild(homeBtn,10);

    
    CCSprite* cleanBtn = CCSprite::create("clean_Btn.png");
    cleanBtn->setPosition(ccp(leftBottom.x+winSize.width*15/16, leftBottom.y+winSize.height*11/12));
    cleanBtn->setTag(kCleanTag);
    cleanBtn->setVisible(false);
    this->addChild(cleanBtn,999);
    
    CCMoveTo* moveTo = CCMoveTo::create(0.5, ccp(leftBottom.x+winSize.width/2, leftBottom.y+winSize.height*0.725));
    catPaw->runAction(moveTo);
    catPaw->setScale(0.82);
    this->addChild(catPaw,3);
    
    this->schedule(schedule_selector(ClipScene::setNewTexture),0.2);
    
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/background/clipBg.mp3", true);
    
    this->setTouchEnabled(true);
    
    return true;
}

ClipScene::ClipScene(){
    
}

ClipScene::~ClipScene(){
    scrollView->stopAllActions();
    scrollView->removeAllChildrenWithCleanup(true);
    rendertexture->release();
    rendertexture = NULL;
    nailPolishInfo->removeAllObjects();
    nailPolishInfo->release();
    nailPolishInfo = NULL;
    this->stopAllActions();
    this->removeAllChildrenWithCleanup(true);
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("clip/clearTools.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("clip/nailPolishAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("clip/nailFlowerSet.plist");
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void ClipScene::setNewTexture(cocos2d::CCTime *dt){
    
//    CCSpriteBatchNode* batchNode = (CCSpriteBatchNode*)this->getChildByTag(kBatchNodeTag);
    
    CCSprite* drawLayer = (CCSprite*)this->getChildByTag(kDrawLayerTag);
//    drawLayer->setContentSize(CCSize(900, 200));
//    CCSprite* catPaw = (CCSprite*)this->getChildByTag(kCatPawTag);
    
    CCSprite* maskInLayer = CCSprite::create("clip/pawArea.png");
    maskInLayer->setScale(0.83);
    this->maskedWithSpriteTexture(drawLayer, maskInLayer, ccp(0.498, 0.521));
    
    rendertexture->removeAllChildrenWithCleanup(true);
    
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    
//    CCSprite* maskInView = (CCSprite*)catPaw->getChildByTag(kMaskInViewTag);
//        
//    maskInView->setTexture(texture);
}

void ClipScene::adjustScrollView(){
    scrollView->unscheduleAllSelectors();
    
//    int winHalf = CCDirector::sharedDirector()->getWinSize().width;
    int winHalf = GameManager::sharedManager()->getViewVisibleSize().width;
    int x = scrollView->getContentOffset().x;
    int offset = (int)x%winHalf;
    
    CCPoint adjustPos;
    // 调整动画时间
    float adjustAnimDelay;
    
    if (offset < -winHalf/2) {
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
    // 调整位置
    scrollView->setContentOffsetInDuration(adjustPos, adjustAnimDelay);
    
    int curLayerIndex = adjustPos.x/-winHalf;
    CCSprite* pointBg = (CCSprite*)this->getChildByTag(curLayerIndex+kPointBgTag);
    if (pointBg != NULL) {
        CCSprite* point = (CCSprite*)this->getChildByTag(kPointTag);
        point->setPosition(pointBg->getPosition());
    }
    curLayerTag = curLayerIndex;
}

void ClipScene::scrollViewDidScroll(CCScrollView* view){
    
}

void ClipScene::scrollViewDidZoom(CCScrollView* view){
    
}

CCTexture2D* ClipScene::maskedWithSpriteTexture(CCSprite* texturesp, CCSprite* masksp,CCPoint location)
{
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    
//    CCSprite* textureChild = (CCSprite*)texturesp->getChildByTag(kDrawLayerTag);
    
    masksp->setPosition(ccp(winSize.width*location.x, winSize.height*location.y));
    texturesp->setPosition(ccp(winSize.width/2, winSize.height*0.52));
    
    masksp->setBlendFunc((ccBlendFunc){GL_ONE, GL_ZERO});
    texturesp->setBlendFunc((ccBlendFunc){GL_DST_ALPHA, GL_ZERO});
    
    rendertexture->begin();
    masksp->visit();
    texturesp->visit();
    rendertexture->end();
    rendertexture->cleanup();
    
    return rendertexture->getSprite()->getTexture();
}

CCTexture2D* ClipScene::anotherMaskedWithSpriteTexture(cocos2d::CCSprite *texturesp, cocos2d::CCSprite *masksp, cocos2d::CCPoint texturePos, cocos2d::CCPoint maskPos){
//    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    CCPoint center = GameManager::sharedManager()->getCenter();
//    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
    
    CCRenderTexture* newRendertexture = CCRenderTexture::create(texturesp->getContentSize().width, texturesp->getContentSize().height);
    
    masksp->setPosition(ccp(winSize.width/2, winSize.height/2));
    texturesp->setPosition(ccp(winSize.width/2, winSize.height/2));
    
    masksp->setBlendFunc((ccBlendFunc){GL_ONE, GL_ZERO});
    texturesp->setBlendFunc((ccBlendFunc){GL_DST_ALPHA, GL_ZERO});
    
    newRendertexture->begin();
    masksp->visit();
    texturesp->visit();
    newRendertexture->end();
    
    return newRendertexture->getSprite()->getTexture();
}

void ClipScene::warningItem(int itemTag){
    CCSprite* catPaw = (CCSprite*)this->getChildByTag(kCatPawTag);
    int itemNum = 0;
    switch (itemTag) {
        case kThornTag:
        {
            itemNum = thornNum;
        }
            break;
        case kPawTag:
        {
            itemNum = pawNum;
        }
            break;
        default:
            break;
    }
    for (int i = 0; i < itemNum; i++) {
        CCSprite* item = (CCSprite*)catPaw->getChildByTag(itemTag+i);
        if (item != NULL) {
            CCBlink* blink = CCBlink::create(1, 2);
            item->runAction(CCSequence::createWithTwoActions(blink, CCCallFuncN::create(this, callfuncN_selector(ClipScene::setItemVisible))));
        }
    }
}

void ClipScene::setItemVisible(cocos2d::CCNode *sender){
    sender->setVisible(true);
}

void ClipScene::clearItem(cocos2d::CCPoint location,int itemTag){
    
    CCSprite* catPaw = (CCSprite*)this->getChildByTag(kCatPawTag);
    
    CCPoint pawPos = catPaw->convertToNodeSpace(location);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    const char* fileName = NULL;
    int itemNum = 0;
    switch (itemTag) {
        case kThornTag:
        {
            fileName = "forceps";
            itemNum = thornNum;
        }
            break;
        case kPawTag:
        {
            fileName = "nail";
            itemNum = pawNum;
        }
            break;
        default:
            break;
    }
    
    for (int i = 0; i < itemNum; i++) {
        CCSprite* item = (CCSprite*)catPaw->getChildByTag(itemTag+i);
        if (item != NULL && item->boundingBox().containsPoint(pawPos) && isCutting == false) {
            item->stopAllActions();
            item->setVisible(true);
            isCutting = true;
            CCJumpTo* jumpTo = CCJumpTo::create(0.5, ccp(item->getPosition().x-50, -winSize.height*0.1), 200, 1);
            item->setRotation(0);
            if (touchSprite != NULL) {
                
                CCAnimate* spriteAnim = CatDressManager::sharedManager()->getSpriteAnimate(0, 2, fileName, true);
                touchSprite->runAction(spriteAnim);
            }
            item->runAction(CCSequence::createWithTwoActions(jumpTo, CCCallFuncN::create(this, callfuncN_selector(ClipScene::removeSelf))));
            switch (itemTag) {
                case kThornTag:
                {
                    thornCount--;
                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/clip/dropThorn.mp3");
                }
                    break;
                case kPawTag:
                {
                    pawCount--;
                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/clip/cutNail.mp3");
                }
                    break;
                default:
                    break;
            }
        }
    }
}

void ClipScene::removeSelf(cocos2d::CCNode *sender){
    if (sender != NULL) {
        sender->stopAllActions();
        sender->removeFromParentAndCleanup(true);
        sender = NULL;
        isCutting = false;
    }
}

void ClipScene::setAnotherFrame(CCSprite* _sprite, const char *frameName){
    CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName);
    _sprite->setDisplayFrame(frame);
}

void ClipScene::brushNail(cocos2d::CCSprite *_sprite, cocos2d::CCPoint location){
    CCPoint newLoc = CCPoint(location.x, location.y-_sprite->getContentSize().height*0.7);
    CCSprite* catPaw = (CCSprite*)this->getChildByTag(kCatPawTag);
//    CCSprite* nailMask = (CCSprite*)catPaw->getChildByTag(kMaskInViewTag);
//    CCPoint pawPoint = catPaw->convertToNodeSpace(newLoc);
    for (int i = 0; i < collisionAreaNum; i++) {
        CCSprite* collistionArea = (CCSprite*)catPaw->getChildByTag(kCollisionAreaTag+i);
        CCPoint pawPoint = catPaw->convertToNodeSpace(newLoc);
        if (collistionArea != NULL && collistionArea->boundingBox().containsPoint(pawPoint)) {
            CCPoint worldPoint = catPaw->convertToWorldSpace(collistionArea->getPosition());
            CCLayer* scrollLayer = (CCLayer*)scrollView->getChildByTag(kScrollLayerTag);
            CCPoint scrollPoint = scrollLayer->convertToNodeSpace(worldPoint);
            DrawSprite* drawLayer = (DrawSprite*)this->getChildByTag(kDrawLayerTag);
            CCPoint drawPoint = drawLayer->convertToNodeSpace(scrollPoint);
            drawLayer->setDrawPoint(scrollPoint,i,touchNailPolishTag);
            
//            drawLayer->setZOrder(10);
//            CCSprite* homeBtn = CCSprite::create("universal/back.png");
//            homeBtn->setPosition(drawPoint);
//            drawLayer->addChild(homeBtn, 20);
            if (isPlayPolishSound == false || colPointTag != i) {
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/clip/returnFlower.mp3");
                isPlayPolishSound = true;
                colPointTag = i;
            }
        }
    }
//    if (catPaw != NULL && catPaw->boundingBox().containsPoint(newLoc)) {
//        DrawSprite* drawLayer = (DrawSprite*)this->getChildByTag(kDrawLayerTag);
//        drawLayer->setDrawPoint(newLoc,touchNailPolishTag);
//    }
}

void ClipScene::setNailFlower(cocos2d::CCPoint location,int _tag,int _viewTag){
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center = GameManager::sharedManager()->getCenter();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
    
//    DrawSprite* drawSpr = (DrawSprite*)this->getChildByTag(kDrawLayerTag);
    
    CCSprite* catPaw = (CCSprite*)this->getChildByTag(kCatPawTag);
    CCSprite* maskInView = (CCSprite*)catPaw->getChildByTag(kMaskInViewTag);
    CCSprite* maskInLayer = CCSprite::create("clip/pawArea.png");
    maskInLayer->setScale(0.83);
    CCSprite* flowerSpr = NULL;
    
//    CCRenderTexture* newRender = CCRenderTexture::create(maskInView->getContentSize().width, maskInView->getContentSize().height);
    CCRenderTexture* newRender = CCRenderTexture::create(winSize.width, winSize.height);
    CCSprite* backSpr = (CCSprite*)this->getChildByTag(kBackSprTag);
    if (backSpr == NULL) {
        
        backSpr = CCSprite::create();
//        backSpr = CCSprite::create("clip/pawArea.png");
        backSpr->setContentSize(CCSizeMake(maskInView->getContentSize().width, maskInView->getContentSize().height));
        backSpr->setPosition(leftBottom);
        
        backSpr->setTag(kBackSprTag);
//        backSpr->setScale(0.83);
        this->addChild(backSpr);
    }else{
        flowerSpr = (CCSprite*)backSpr->getChildByTag(kFlowerInViewTag+_viewTag);
    }
    if (flowerSpr == NULL) {
        flowerSpr = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("nailFlower%d.png",_tag+1)->getCString());
        CCPoint backPoint = backSpr->convertToNodeSpace(location);
        flowerSpr->setPosition(backPoint);
        flowerSpr->setTag(kFlowerInViewTag+_viewTag);
//        flowerSpr->setScale(0.8);
        backSpr->addChild(flowerSpr,2);
    }else{
        this->setAnotherFrame(flowerSpr, CCString::createWithFormat("nailFlower%d.png",_tag+1)->getCString());
    }
//    newRender->setPosition(leftBottom);
    newRender->begin();
//    newRender->setPosition(leftBottom);
    backSpr->visit();
    newRender->end();
    newRender->cleanup();
    
    CCSprite* newSprite = CCSprite::createWithTexture(newRender->getSprite()->getTexture());
//    newSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
//    CCSize newSpriteSize = newSprite->getContentSize();
    newSprite->setFlipY(true);
//    this->addChild(newSprite, 3);
//    flowerSpr->setPosition(location);
//    drawSpr->addChild(flowerSpr);
    
    CCTexture2D* texture = this->anotherMaskedWithSpriteTexture(newSprite, maskInLayer, location, CCPointZero);
    
    CCSprite* newMask = (CCSprite*)catPaw->getChildByTag(kMaskNailTag);
    if (newMask == NULL) {
        
        newMask = CCSprite::createWithTexture(texture);
//        newMask = CCSprite::createWithTexture(newSprite->getTexture());
        newMask->setPosition(ccp(catPaw->getContentSize().width*0.496, catPaw->getContentSize().height*0.162));
        newMask->setFlipY(true);
        newMask->setTag(kMaskNailTag);
        newMask->setScale(1.2);
        catPaw->addChild(newMask,4);
    }else{
        newMask->setTexture(texture);
    }
    newRender->release();
    int flowerSoundTag = arc4random()%8+1;
    SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mp3/clip/putOnNail%d.mp3",flowerSoundTag)->getCString());
}

void ClipScene::moveLayer(){
    
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    int winHalf = GameManager::sharedManager()->getViewVisibleSize().width;
    int x = scrollView->getContentOffset().x;
    int offset = (int)x%winHalf;
    CCPoint adjustPos = ccpSub(scrollView->getContentOffset(), ccp(winHalf + offset, 0));
    float adjustAnimDelay = (float) (winHalf + offset) / ADJUST_ANIM_VELOCITY;
    CCLayer* scrollLayer = (CCLayer*)scrollView->getChildByTag(kScrollLayerTag);
    if (scrollLayer != NULL) {
        CCSprite* layerSprite = (CCSprite*)scrollLayer->getChildByTag(kLayerSpriteTag);
        CCMoveTo* moveTo = CCMoveTo::create(adjustAnimDelay, ccp(-winSize.width/2, winSize.height/2));
        layerSprite->runAction(CCSequence::createWithTwoActions(moveTo, CCCallFuncN::create(this, callfuncN_selector(ClipScene::removeSelf))));
        CCSprite* nailPolishLayer = (CCSprite*)scrollLayer->getChildByTag(kNailPolishLayerTag);
        CCMoveTo* polishMove = CCMoveTo::create(adjustAnimDelay, ccp(winSize.width/2, winSize.height/2));
        nailPolishLayer->runAction(polishMove);
        CCSprite* nailFlowerLayer = (CCSprite*)scrollLayer->getChildByTag(kNailFlowerLayerTag);
        CCMoveTo* flowerMove = CCMoveTo::create(adjustAnimDelay, ccp(winSize.width/2*3, winSize.height/2));
        nailFlowerLayer->runAction(flowerMove);
        scrollView->setContentSize(CCSizeMake(winSize.width*2, winSize.height));
    }
    SimpleAudioEngine::sharedEngine()->playEffect("mp3/clip/menuScroll.mp3");
    
//    int curLayerIndex = adjustPos.x/-winHalf;
    for (int i = 0; i < 2; i++) {
        CCSprite* pointBg = (CCSprite*)this->getChildByTag(i+kPointBgTag);
        if (pointBg != NULL) {
            pointBg->setVisible(true);
            if (i == 0) {
                CCSprite* point = (CCSprite*)this->getChildByTag(kPointTag);
                point->setPosition(pointBg->getPosition());
                point->setVisible(true);
            }
        }
    }
    
    curLayerTag = 0;
    
    CCSprite* cleanBtn = (CCSprite*)this->getChildByTag(kCleanTag);
    if (cleanBtn != NULL) {
        cleanBtn->setVisible(true);
    }
}

void ClipScene::reverseScrollView(){
    scrollView->setTouchEnabled(true);
}

void ClipScene::returnLastScene(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.8, CatSelectScene::sceneWithID(curCatID-1),ccWHITE));
}

void ClipScene::cleanPolish(){
    CCSprite* catPaw = (CCSprite*)this->getChildByTag(kCatPawTag);
    //    CCSprite* nailMask = (CCSprite*)catPaw->getChildByTag(kMaskInViewTag);
    //    CCPoint pawPoint = catPaw->convertToNodeSpace(newLoc);
    for (int i = 0; i < collisionAreaNum; i++) {
        CCSprite* collistionArea = (CCSprite*)catPaw->getChildByTag(kCollisionAreaTag+i);
        if (collistionArea != NULL) {
            CCPoint worldPoint = catPaw->convertToWorldSpace(collistionArea->getPosition());
            DrawSprite* drawLayer = (DrawSprite*)this->getChildByTag(kDrawLayerTag);
            drawLayer->setDrawPoint(worldPoint,i,6);
        }
    }
}

void ClipScene::cleanFlower(){
    CCSprite* catPaw = (CCSprite*)this->getChildByTag(kCatPawTag);
    CCSprite* newMask = (CCSprite*)catPaw->getChildByTag(kMaskNailTag);
    if (newMask != NULL) {
        newMask->removeFromParentAndCleanup(true);
        newMask = NULL;
    }
    CCSprite* backSpr = (CCSprite*)this->getChildByTag(kBackSprTag);
    if (backSpr != NULL) {
        
        backSpr->removeFromParentAndCleanup(true);
        backSpr = NULL;
    }
}

void ClipScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
    
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCLayer* scrollLayer = (CCLayer*)scrollView->getChildByTag(kScrollLayerTag);
    CCSprite* layerSprite = (CCSprite*)scrollLayer->getChildByTag(kLayerSpriteTag);
    CCSprite* nailPolishLayer = (CCSprite*)scrollLayer->getChildByTag(kNailPolishLayerTag);
    CCSprite* nailFlowerLayer = (CCSprite*)scrollLayer->getChildByTag(kNailFlowerLayerTag);
    
    CCPoint scrollPoint = scrollLayer->convertToNodeSpace(location);
    CCPoint nailPolishPoint = nailPolishLayer->convertToNodeSpace(location);
    CCPoint nailFlowerPoint = nailFlowerLayer->convertToNodeSpace(location);
    
    if (layerSprite != NULL && layerSprite->boundingBox().containsPoint(scrollPoint)) {
        CCSprite* plate = (CCSprite*)layerSprite->getChildByTag(kPlateTag);
        CCSprite* forceps = (CCSprite*)plate->getChildByTag(kForcepsTag);
        CCSprite* nail = (CCSprite*)plate->getChildByTag(kNailTag);
        CCPoint platePoint = plate->convertToNodeSpace(location);
        if (forceps != NULL && forceps->boundingBox().containsPoint(platePoint)) {
            touchSpriteInPos = forceps->getPosition();
            forceps->setPosition(platePoint);
            touchSprite = forceps;
            scrollView->setTouchEnabled(false);
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/clip/takeNail.mp3");
            this->warningItem(kThornTag);
        }else if (nail != NULL && nail->boundingBox().containsPoint(platePoint)){
            touchSpriteInPos = nail->getPosition();
            nail->setPosition(platePoint);
            touchSprite = nail;
            scrollView->setTouchEnabled(false);
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/clip/takeNail.mp3");
            this->warningItem(kPawTag);
        }
    }
    
    if (nailPolishLayer != NULL && nailPolishLayer->boundingBox().containsPoint(scrollPoint)) {
        for (int i = 0; i < nailPolishNum; i++) {
            CCSprite* nailPolish = (CCSprite*)nailPolishLayer->getChildByTag(kNailPolishTag+i);
            if (nailPolish != NULL && nailPolish->boundingBox().containsPoint(nailPolishPoint)) {
                scrollView->setTouchEnabled(false);
                this->setAnotherFrame(nailPolish, CCString::createWithFormat("nailPolish%d_0002.png",i+1)->getCString());
                CCSprite* brush = CCSprite::create(CCString::createWithFormat("clip/nailBrush%d.png",i+1)->getCString());
                brush->setPosition(nailPolishPoint);
                brush->setAnchorPoint(ccp(0.5, 0.75));
                brush->setTag(kBrushTage);
                brush->setScale(0.83);
                nailPolishLayer->addChild(brush);
                touchSprite = brush;
                touchNailPolishTag = i;
                CCDictionary* polishInfo = CatDressManager::sharedManager()->getDictionary(CCString::createWithFormat("nailPolish%d",i+1)->getCString(), nailPolishInfo);
                int red = polishInfo->valueForKey("red")->intValue();
                int green = polishInfo->valueForKey("green")->intValue();
                int blue = polishInfo->valueForKey("blue")->intValue();
                
                DrawSprite* drawLayer = (DrawSprite*)this->getChildByTag(kDrawLayerTag);
                drawLayer->setBrushColor(ccc4(red, green, blue, 255),i);
//                drawLayer->setZOrder(10);
//                drawLayer->isCanDraw(true);
                SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("mp3/clip/takePolish%d.mp3",i+1)->getCString());
            }
        }
    }
    
    if (nailFlowerLayer != NULL && nailFlowerLayer->boundingBox().containsPoint(scrollPoint)) {
        for (int i = 0; i < 10; i++) {
            CCSprite* nailFlower = (CCSprite*)nailFlowerLayer->getChildByTag(kNailFlowerTag+i);
            if (nailFlower != NULL && nailFlower->boundingBox().containsPoint(nailFlowerPoint)) {
                SimpleAudioEngine::sharedEngine()->playEffect("mp3/clip/returnFlower.mp3");
                scrollView->setTouchEnabled(false);
                touchSpriteInPos = nailFlower->getPosition();
                nailFlower->setPosition(nailFlowerPoint);
                touchSprite = nailFlower;
                touchNailFlowerTag = i;
            }
        }
    }
    
    CCSprite* homeBtn = (CCSprite*)this->getChildByTag(kHomeBtnTage);
    if (homeBtn != NULL && homeBtn->boundingBox().containsPoint(location) && isTouchHome == false) {
        CCScaleBy* scaleBy = CCScaleBy::create(0.1, 1.2);
        //            homeBtn->setScale(1.2);
        //            touchSprite = homeBtn;
        //            SimpleAudioEngine::sharedEngine()->playEffect("touchItem.mp3");
        //插页广告
        this->goToShowInterstitial();
        homeBtn->runAction(CCSequence::createWithTwoActions(CCSequence::createWithTwoActions(scaleBy, scaleBy->reverse()), CCCallFunc::create(this, callfunc_selector(ClipScene::returnLastScene))));
        //            _gameScene->selectMenuBtn(158);
        isTouchHome = true;
        SimpleAudioEngine::sharedEngine()->playEffect("mp3/clip/touchButton.mp3");
    }
    
    CCSprite* cleanBtn = (CCSprite*)this->getChildByTag(kCleanTag);
    if (cleanBtn != NULL && cleanBtn->boundingBox().containsPoint(location) && cleanBtn->isVisible() == true) {

        SimpleAudioEngine::sharedEngine()->playEffect("mp3/clip/touchButton.mp3");
        switch (curLayerTag) {
            case 0:
                this->cleanPolish();
                break;
            case 1:
                this->cleanFlower();
                break;
            default:
                break;
        }
        this->goToShowInterstitial();
    }
}


void ClipScene::goToShowInterstitial() {
    if (CCUserDefault::sharedUserDefault()->getBoolForKey("UnlockAll") == false){
        GameManager::sharedManager()->showInterstitial();
    }

}

void ClipScene::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
    
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCLayer* scrollLayer = (CCLayer*)scrollView->getChildByTag(kScrollLayerTag);
    CCSprite* nailPolishLayer = (CCSprite*)scrollLayer->getChildByTag(kNailPolishLayerTag);
    CCSprite* nailFlowerLayer = (CCSprite*)scrollLayer->getChildByTag(kNailFlowerLayerTag);
    CCSprite* layerSprite = (CCSprite*)scrollLayer->getChildByTag(kLayerSpriteTag);
    CCSprite* plate = NULL;
    CCPoint platePoint = CCPointZero;
    
    CCPoint scrollPoint = scrollLayer->convertToNodeSpace(location);
    CCPoint nailPolishPoint = nailPolishLayer->convertToNodeSpace(location);
    CCPoint nailFlowerPoint = nailFlowerLayer->convertToNodeSpace(location);
    
    if (layerSprite != NULL) {
        plate = (CCSprite*)layerSprite->getChildByTag(kPlateTag);
        platePoint = plate->convertToNodeSpace(location);
    }
    
    if (touchSprite != NULL) {
        
        if (touchSprite->getTag() == kForcepsTag) {
            touchSprite->setPosition(platePoint);
            this->clearItem(ccp(location.x-touchSprite->getContentSize().width/3, location.y-touchSprite->getContentSize().height/6), kThornTag);
        }else if (touchSprite->getTag() == kNailTag){
            touchSprite->setPosition(platePoint);
            this->clearItem(ccp(location.x-touchSprite->getContentSize().width/3, location.y+touchSprite->getContentSize().height/3), kPawTag);
        }else if (touchSprite->getTag() == kBrushTage){
            touchSprite->setPosition(nailPolishPoint);
            this->brushNail(touchSprite, location);
        }
        else{
            for (int i = 0; i < 10; i++) {
                if (touchSprite->getTag() == kNailFlowerTag+i) {
//                    CCPoint nailFlowerPoint = touchSprite->convertToNodeSpace(location);
                    touchSprite->setPosition(nailFlowerPoint);
                }
            }
        }
    }
}

void ClipScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
    
    CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    this->adjustScrollView();
    
    CCLayer* scrollLayer = (CCLayer*)scrollView->getChildByTag(kScrollLayerTag);
    CCSprite* nailFlowerLayer = (CCSprite*)scrollLayer->getChildByTag(kNailFlowerLayerTag);
    CCPoint nailFlowerPoint = nailFlowerLayer->convertToNodeSpace(location);
    if (touchSprite != NULL) {
        if (touchSprite->getTag() == kBrushTage) {
            CCLayer* scrollLayer = (CCLayer*)scrollView->getChildByTag(kScrollLayerTag);
            CCSprite* nailPolishLayer = (CCSprite*)scrollLayer->getChildByTag(kNailPolishLayerTag);
            CCSprite* nailPolish = (CCSprite*)nailPolishLayer->getChildByTag(kNailPolishTag+touchNailPolishTag);
            this->setAnotherFrame(nailPolish, CCString::createWithFormat("nailPolish%d_0001.png",touchNailPolishTag+1)->getCString());
            
            this->removeSelf(touchSprite);
            
            scrollView->setTouchEnabled(true);
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/clip/returnPolish.mp3");
            
            isPlayPolishSound = false;
//            DrawSprite* drawLayer = (DrawSprite*)this->getChildByTag(kDrawLayerTag);
//            drawLayer->isCanDraw(false);
        }else if (touchSprite->getTag() == kForcepsTag || touchSprite->getTag() == kNailTag){
            if (touchSprite->getTag() == kForcepsTag) {
                touchSprite->setPosition(forcepsInPos);
            }else{
                
                touchSprite->setPosition(nailInPos);
            }
            if (thornCount == 0 && pawCount == 0) {
                this->runAction(CCSequence::createWithTwoActions(CCCallFunc::create(this, callfunc_selector(ClipScene::moveLayer)), CCCallFunc::create(this, callfunc_selector(ClipScene::reverseScrollView))));
            }
            SimpleAudioEngine::sharedEngine()->playEffect("mp3/clip/returnNail.mp3");
        }else{
            touchSprite->setPosition(touchSpriteInPos);
            
            for (int i = 0; i < flowerColNum; i++) {
                CCSprite* flowerCol = (CCSprite*)this->getChildByTag(kFlowerColTag+i);
                if (flowerCol != NULL && flowerCol->boundingBox().containsPoint(location)) {
                    this->setNailFlower(flowerCol->getPosition(), touchNailFlowerTag,i);
                    SimpleAudioEngine::sharedEngine()->playEffect("mp3/clip/returnFlower.mp3");
                }
            }
//            CCPoint scrollPoint = scrollLayer->convertToNodeSpace(location);
//            
//            if (nailFlowerLayer != NULL && nailFlowerLayer->boundingBox().containsPoint(scrollPoint)) {
//                
//                CCSprite* catPaw = (CCSprite*)this->getChildByTag(kCatPawTag);
//                CCSprite* nailMask = (CCSprite*)catPaw->getChildByTag(kMaskInViewTag);
//                CCPoint pawPoint = catPaw->convertToNodeSpace(location);
//                if (nailMask != NULL && nailMask->boundingBox().containsPoint(pawPoint)) {
//                    this->setNailFlower(location, touchNailFlowerTag);
//                    SimpleAudioEngine::sharedEngine()->playEffect("returnFlower.mp3");
//                }
//            }
            scrollView->setTouchEnabled(true);
        }
        touchSprite = NULL;
        touchSpriteInPos = CCPointZero;
    }
}

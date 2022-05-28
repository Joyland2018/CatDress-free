//
//  CatDressManager.cpp
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-4.
//
//

#include "CatDressManager.h"

enum{
    kRocketTag = 13,
    kMagicTag = 14,
    kSprayTag = 17,
    kBrushTag = 41,
    kGunTag = 44,
    kScattTag = 51,
    kGunParTag = 19,
    kMagicParTag = 20,
    kRocketParTag = 21,
    kTailTag = 80,
    kBodyTag = 81,
    kHeadTag = 82,
    kEyeBgTag = 83,
    kEyeLTag = 84,
    kEyeRTag = 85,
    kMouthTag = 86,
    kToyTag = 101,
};

static CatDressManager* _sharedManager;

CatDressManager* CatDressManager::sharedManager(){
    if (!_sharedManager) {
        _sharedManager = new CatDressManager();
    }
    
    return _sharedManager;
}

CatDressManager::CatDressManager(){
    
}

CatDressManager::~CatDressManager(){
    
}

CCPoint CatDressManager::getViewInitPos(){
    return CCPoint(CCEGLView::sharedOpenGLView()->getVisibleOrigin().x, CCEGLView::sharedOpenGLView()->getVisibleOrigin().y);
}

CCSize CatDressManager::getViewVisibleSize(){
    return CCSize(CCEGLView::sharedOpenGLView()->getVisibleSize().width, CCEGLView::sharedOpenGLView()->getVisibleSize().height);
}

CCAnimate* CatDressManager::getSpriteAnimate(int initFrame,int frameMaxNum,const char* fileName,bool isRestoreFrame){
    CCArray* frames = CCArray::create();
    for (int i = initFrame; i < frameMaxNum; i++) {
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s_%04d.png",fileName,i+1)->getCString());
        if (frames!=NULL){
            frames->addObject(frame);
        }

    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames,1.0/12.0);
    animation->setRestoreOriginalFrame(isRestoreFrame);
    CCAnimate* anim = CCAnimate::create(animation);
    return anim;
}

CCDictionary* CatDressManager::getDictionary(const char *pName, cocos2d::CCDictionary *_dic){
    CCDictionary* plistInfo;
    if (_dic == NULL) {
        plistInfo = CCDictionary::createWithContentsOfFile(pName);
    }else {
        plistInfo = (CCDictionary*)_dic->objectForKey(pName);
    }
    
    return plistInfo;
}

CCPoint CatDressManager::getPos(const char *pName, cocos2d::CCDictionary *_dic){
    CCDictionary* itemInfo = this->getDictionary(pName, _dic);
    float x = itemInfo->valueForKey("x")->floatValue();
    float y = itemInfo->valueForKey("y")->floatValue();
    CCPoint itemPos = ccp(x, y);
    return itemPos;
}

CCLayer* CatDressManager::getCatSprite(int _catIndex,CCPoint _eyeLPos,CCPoint _eyeRPos){
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CCString::createWithFormat("catItems/cat%d.plist",_catIndex)->getCString());
    
//    CCSprite* catSpr = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("mao%d_shenti.png",_catIndex)->getCString());
    CCLayer* catSpr = CCLayer::create();
    
    if (catSpr != NULL) {
        
        CCDictionary* catDic = this->getDictionary("catInfo.plist", NULL);
        CCDictionary* catInfo = this->getDictionary(CCString::createWithFormat("cat%d",_catIndex)->getCString(), catDic);
        
        catSpr->setContentSize(GameManager::sharedManager()->getViewVisibleSize());
        
        CCSprite* body = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("mao%d_shenti.png",_catIndex)->getCString());
//        body->setScale(0.9);
        body->setTag(kBodyTag);
        body->setPosition(ccp(catSpr->getContentSize().width/2, catSpr->getContentSize().height/3));
        catSpr->addChild(body);
        
        CCSprite* head = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("mao%d_tou.png",_catIndex)->getCString());
        
        CCPoint headPos = this->getPos("head", catInfo);
        
//        head->setScale(0.9);
        head->setTag(kHeadTag);
        head->setPosition(ccp(catSpr->getContentSize().width/2+headPos.x, body->getPosition().y+body->getContentSize().height/2+headPos.y));
        catSpr->addChild(head);
        
        CCSprite* eye = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("mao%d_yankuang.png",_catIndex)->getCString());
        
        CCPoint eyePos = this->getPos("eyeBg", catInfo);
//        eye->setScale(0.9);
        eye->setTag(kEyeBgTag);
        eye->setPosition(eyePos);
        head->addChild(eye);
        
        CCSprite* eyeball1 = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("mao%d_yanren.png",_catIndex)->getCString());
//        eyeball1->setScale(0.9);
        eyeball1->setTag(kEyeRTag);
        eyeball1->setPosition(_eyeLPos);
        head->addChild(eyeball1);
        
        CCSprite* eyeball2 = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("mao%d_yanren.png",_catIndex)->getCString());
//        eyeball2->setScale(0.9);
        eyeball2->setTag(kEyeLTag);
        eyeball2->setPosition(_eyeRPos);
        head->addChild(eyeball2);
        
        CCSprite* mouth = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("mao%d_zui_1_01.png",_catIndex)->getCString());
//        mouth->setScale(0.9);
        CCPoint mouthPos = this->getPos("mouth", catInfo);
        
        mouth->setPosition(mouthPos);
        mouth->setTag(kMouthTag);
        head->addChild(mouth);
        
        CCSprite* tail = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("mao%d_weiba.png",_catIndex)->getCString());
//        tail->setScale(0.9);
        
        CCPoint tailPos = this->getPos("tail", catInfo);
        
        tail->setPosition(ccp(catSpr->getContentSize().width/2+tailPos.x, catSpr->getContentSize().height/2-tailPos.y));
        catSpr->addChild(tail,-1);
        
        return catSpr;
    }
    
    return NULL;
}

CCLayer* CatDressManager::getMenuLayer(){
    CCLayer* menuLayer = CCLayer::create();
    
    CCSize winSize = this->getViewVisibleSize();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
    
    if (menuLayer != NULL) {
        
        menuLayer->setContentSize(winSize);
        
        return menuLayer;
    }
    
    return NULL;
}

CCSprite* CatDressManager::getToySpr(int _toyIndex){
    CCSprite* toySpr = CCSprite::create();
    
    if (toySpr != NULL) {
        
        toySpr->setContentSize(CCDirector::sharedDirector()->getWinSize());
        
        CCSprite* toy;
        
        switch (_toyIndex) {
            case 40:
                toy = ToyManager::sharedManager()->getSpiderToy();
                break;
                
            default:
                toy = CCSprite::create(CCString::createWithFormat("toy/toy_%d.png",_toyIndex)->getCString());
                break;
        }
        
        if (toy != NULL) {
            if (_toyIndex == 17) {
                toy->setFlipX(true);
            }
            toy->setTag(kToyTag);
            toySpr->addChild(toy);
        }
        
        return toySpr;
    }
    
    return NULL;
}

void CatDressManager::selectPar(CCSprite* pSprite,int pTag,CCPoint curPos){
    switch (pTag) {
        case kRocketTag:
            this->setRocketPar(pSprite, "rocket", curPos);
            break;
        case kMagicTag:
            this->setMagicPar(pSprite, "magic", curPos);
            break;
        case kSprayTag:
            this->setSprayPar(pSprite, "spray",curPos);
            break;
        case kBrushTag:
            this->setMagicPar(pSprite, "magic", curPos);
            break;
        case kGunTag:
//            this->setGunPar(pSprite, "gun", curPos);
            break;
        case kScattTag:
            this->setMagicPar(pSprite, "magic", curPos);
            break;
        default:
            break;
    }
}

void CatDressManager::setRocketPar(cocos2d::CCSprite *pSprite, const char *pName, cocos2d::CCPoint curPos){
    
    
    
//    CCString* target = CCString::createWithFormat("%s",CCFileUtils::sharedFileUtils()->getResourceDirectory());
    
    CCString* fileName = CCString::createWithFormat("particle/%s.plist",pName);
    //    if (target->isEqual(CCString::create("hd/"))) {
    //        fileName = CCString::createWithFormat("%s_hd.plist",pName);
    //    }else if (target->isEqual(CCString::create("iphone/"))) {
    //        fileName = CCString::createWithFormat("%s_ip.plist",pName);
    //    }
    CCParticleSystem* rocketPar = (CCParticleSystem*)pSprite->getChildByTag(kRocketParTag);
    if (rocketPar == NULL) {
        rocketPar = CCParticleSystemQuad::create(fileName->getCString());
        CCSize sprSize = pSprite->getContentSize();
        rocketPar->setPositionType(kCCPositionTypeRelative);
        rocketPar->setPosition(ccp(sprSize.width/2, sprSize.height/5));
        rocketPar->setTag(kRocketParTag);
        pSprite->addChild(rocketPar,-1);
    }else {
        rocketPar->removeFromParentAndCleanup(true);
        rocketPar = NULL;
    }
}

void CatDressManager::setMagicPar(cocos2d::CCSprite *pSprite, const char *pName, cocos2d::CCPoint curPos){
//    CCString* target = CCString::createWithFormat("%s",CCFileUtils::sharedFileUtils()->getResourceDirectory());
    
    CCString* fileName = CCString::createWithFormat("particle/%s.plist",pName);
    //    if (target->isEqual(CCString::create("hd/"))) {
    //        fileName = CCString::createWithFormat("%s_hd.plist",pName);
    //    }else if (target->isEqual(CCString::create("iphone/"))) {
    //        fileName = CCString::createWithFormat("%s_ip.plist",pName);
    //    }
    CCParticleSystem* magicPar = (CCParticleSystem*)pSprite->getChildByTag(kMagicParTag);
    if (magicPar == NULL) {
        magicPar = CCParticleSystemQuad::create(fileName->getCString());
        CCSize sprSize = pSprite->getContentSize();
        magicPar->setPosition(ccp(sprSize.width/2, sprSize.height*4/5));
        magicPar->setAutoRemoveOnFinish(true);
        //        magicPar->setTag(kMagicParTag);
        pSprite->addChild(magicPar,-1);
    }
}

void CatDressManager::setSprayPar(cocos2d::CCSprite *pSprite, const char *pName,CCPoint curPos){
//    CCString* target = CCString::createWithFormat("%s",CCFileUtils::sharedFileUtils()->getResourceDirectory());
    
    CCString* fileName = CCString::createWithFormat("particle/%s.plist",pName);
    //    if (target->isEqual(CCString::create("hd/"))) {
    //        fileName = CCString::createWithFormat("%s_hd.plist",pName);
    //    }else if (target->isEqual(CCString::create("iphone/"))) {
    //        fileName = CCString::createWithFormat("%s_ip.plist",pName);
    //    }
    CCDictionary* toyInfo = this->getDictionary("toyInformation.plist", NULL);
    CCDictionary* itemToyInfo = this->getDictionary("toy17", toyInfo);
    CCPoint firstInfo = this->getPos("first", itemToyInfo);
    CCPoint secondInfo = this->getPos("second", itemToyInfo);
    if (curPos.equals(firstInfo) || curPos.equals(secondInfo)) {
        CCParticleSystem* sprayPar = CCParticleSystemQuad::create(fileName->getCString());
        CCSize sprSize = pSprite->getContentSize();
        sprayPar->setPosition(ccp(sprSize.width*3/4, sprSize.height*4/5));
        sprayPar->setAutoRemoveOnFinish(true);
        pSprite->addChild(sprayPar,-1);
    }
}


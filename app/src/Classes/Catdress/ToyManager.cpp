//
//  ToyManager.cpp
//  CatDressUp
//
//  Created by LiXiaofei on 2017/6/12.
//
//

#include "ToyManager.h"

enum{
    kSpiderTag = 2909,
};

static ToyManager* _sharedManager;

ToyManager* ToyManager::sharedManager(){
    if (!_sharedManager) {
        _sharedManager = new ToyManager();
        _sharedManager->autorelease();
    }
    
    return _sharedManager;
}

ToyManager::ToyManager(){
    
}

ToyManager::~ToyManager(){
    
}

CCSprite* ToyManager::getSpiderToy(){
    CCSprite* toySpr = CCSprite::create("toy/toy_40_1.png");
    
    if (toySpr != NULL) {
        
        CCSprite* spider = CCSprite::create("toy/toy_40_2.png");
        spider->setPosition(ccp(toySpr->getContentSize().width/2, toySpr->getContentSize().height/2));
        spider->setTag(kSpiderTag);
        toySpr->addChild(spider);
        
        return toySpr;
    }
    
    return NULL;
}

void ToyManager::showToyAnim(int _toyIndex,CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback){
    switch (_toyIndex) {
        case 11:
        case 12:
        case 37:
            this->anyCarAnim(_toy, _callTarget, _callback);
            break;
        case 13:
            this->rocketAnim(_toy, _callTarget, _callback);
            break;
        case 15:
        case 19:
        case 20:
        case 30:
        case 35:
        case 36:
            this->jumpAnim(_toy, _callTarget, _callback);
            break;
        case 17:
            this->watergunAnim(_toy, _callTarget, _callback);
            break;
        case 29:
        case 52:
        case 55:
        case 56:
            this->shieldAnim(_toy, _callTarget, _callback);
            break;
        case 32:
            this->rockAnim(_toy, _callTarget, _callback);
            break;
        case 34:
            this->updownAnim(_toy, _callTarget, _callback);
            break;
        case 39:
            this->dragonAnim(_toy, _callTarget, _callback);
            break;
        case 40:
            this->spiderAnim(_toy,_callTarget,_callback);
            break;
        case 16:
        case 18:
        case 33:
        case 38:
        case 45:
        case 53:
            this->scaleAnim(_toy, _callTarget, _callback);
            break;
        case 14:
        case 41:
        case 51:
            this->flyAnim(_toy, _callTarget, _callback);
            break;
        case 42:
            this->spaceshipAnim(_toy, _callTarget, _callback);
            break;
        case 43:
        case 60:
            this->foldLineAnim(_toy, _callTarget, _callback);
            break;
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 47:
        case 54:
        case 57:
        case 58:
        case 59:
            this->rotateAnim(_toy, _callTarget, _callback);
            break;
        case 48:
        case 49:
            this->fanAnim(_toy, _callTarget, _callback);
            break;
        case 50:
        case 67:
            this->rotateFlyAnim(_toy, _callTarget, _callback);
            break;
        default:
            break;
    }
}

void ToyManager::spiderAnim(CCSprite* _toy,CCObject* _callTarget,SEL_CallFunc _callback){
    CCSprite* spider = (CCSprite*)_toy->getChildByTag(kSpiderTag);
    
    CCMoveTo* move1 = CCMoveTo::create(0.3, ccp(_toy->getContentSize().width/3, _toy->getContentSize().height/3*2));
    CCMoveTo* move2 = CCMoveTo::create(0.4, ccp(_toy->getContentSize().width/3*2, _toy->getContentSize().height/2));
    CCMoveTo* move3 = CCMoveTo::create(0.4, ccp(_toy->getContentSize().width/3, _toy->getContentSize().height/3));
    CCMoveTo* reverseMove = CCMoveTo::create(0.3, ccp(_toy->getContentSize().width/2, _toy->getContentSize().height/2));
    
    spider->runAction(CCSequence::create(move1,move2,move3,reverseMove,CCCallFunc::create(_callTarget, _callback),NULL));
}

void ToyManager::watergunAnim(cocos2d::CCSprite *_toy, cocos2d::CCObject *_callTarget, SEL_CallFunc _callback){
    
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
    
    CCPoint toyInitPos = _toy->getPosition();
    
    CCMoveTo* move1 = CCMoveTo::create(0.3, ccp(244, 388));
    CCMoveTo* move2 = CCMoveTo::create(0.3, ccp(573, 462));
    CCMoveTo* reverseMove = CCMoveTo::create(0.4, toyInitPos);
    
    _toy->runAction(CCSequence::create(move1,CCDelayTime::create(1.0),move2,CCDelayTime::create(1.0),reverseMove,CCCallFunc::create(_callTarget, _callback),NULL));
}

void ToyManager::scaleAnim(cocos2d::CCSprite *_toy, cocos2d::CCObject *_callTarget, SEL_CallFunc _callback){
    
//    _toy->setAnchorPoint(ccp(0.5, 0));
    CCScaleTo* scale1 = CCScaleTo::create(0.2, 1.0,1.2);
    CCScaleTo* scale2 = CCScaleTo::create(0.2, 1.0,0.8);
    CCScaleTo* scale3 = CCScaleTo::create(0.2, 1.0,1.0);
    
    _toy->runAction(CCSequence::create(scale1,scale2,scale3,CCCallFunc::create(_callTarget, _callback),NULL));
}

void ToyManager::foldLineAnim(cocos2d::CCSprite *_toy, cocos2d::CCObject *_callTarget, SEL_CallFunc _callback){
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
    
    CCPoint toyInitPos = _toy->getPosition();
    
    CCMoveTo* move1 = CCMoveTo::create(0.3, ccp(toyInitPos.x+50, toyInitPos.y+60));
    CCMoveTo* move2 = CCMoveTo::create(0.3, ccp(toyInitPos.x+100, toyInitPos.y));
    CCMoveTo* move3 = CCMoveTo::create(0.3, ccp(toyInitPos.x+150, toyInitPos.y+60));
    CCMoveTo* move4 = CCMoveTo::create(0.3, ccp(toyInitPos.x+200, toyInitPos.y));
    CCMoveTo* reverseMove = CCMoveTo::create(0.4, toyInitPos);
    
    _toy->runAction(CCSequence::create(move1,move2,move3,move4,reverseMove,CCCallFunc::create(_callTarget, _callback),NULL));
}

void ToyManager::spaceshipAnim(cocos2d::CCSprite *_toy, cocos2d::CCObject *_callTarget, SEL_CallFunc _callback){
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
    
    CCPoint toyInitPos = _toy->getPosition();
    
    CCMoveTo* move1 = CCMoveTo::create(0.4, ccp(toyInitPos.x+250, toyInitPos.y+200));
    CCRotateTo* rotate1 = CCRotateTo::create(0.4, -30);
    CCMoveTo* move2 = CCMoveTo::create(0.4, ccp(toyInitPos.x-80, toyInitPos.y+220));
    CCRotateTo* rotate2 = CCRotateTo::create(0.4, 30);
    CCMoveTo* reverseMove = CCMoveTo::create(0.5, toyInitPos);
    CCRotateTo* reverseRotate = CCRotateTo::create(0.5, 0);
    
    CCSpawn* spawn1 = CCSpawn::createWithTwoActions(move1, rotate1);
    CCSpawn* spawn2 = CCSpawn::createWithTwoActions(move2, rotate2);
    CCSpawn* spawn3 = CCSpawn::createWithTwoActions(reverseMove, reverseRotate);
    
    _toy->runAction(CCSequence::create(spawn1,spawn2,spawn3,CCCallFunc::create(_callTarget, _callback),NULL));
}

void ToyManager::anyCarAnim(cocos2d::CCSprite *_toy, cocos2d::CCObject *_callTarget, SEL_CallFunc _callback){
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
    
    CCPoint toyInitPos = _toy->getPosition();
    
    CCMoveTo* move1 = CCMoveTo::create(0.8, ccp(toyInitPos.x+400, toyInitPos.y-250));
    
    _toy->runAction(CCSequence::create(move1,CCCallFunc::create(_callTarget, _callback),NULL));
}

void ToyManager::shieldAnim(cocos2d::CCSprite *_toy, cocos2d::CCObject *_callTarget, SEL_CallFunc _callback){
    CCPoint toyInitPos = _toy->getPosition();
    
    CCMoveTo* move1 = CCMoveTo::create(0.8, ccp(toyInitPos.x+300, toyInitPos.y));
    CCRotateBy* rotate1 = CCRotateBy::create(0.8, 360);
    CCMoveTo* move2 = CCMoveTo::create(0.8, ccp(toyInitPos.x, toyInitPos.y));
//    CCRotateBy* rotate2 = CCRotateTo::create(0.8, -360);
    CCRotateBy* rotate2 = (CCRotateBy*)rotate1->reverse();
    
    CCSpawn* spawn1 = CCSpawn::createWithTwoActions(move1, rotate1);
    CCSpawn* spawn2 = CCSpawn::createWithTwoActions(move2, rotate2);
    
    _toy->runAction(CCSequence::create(spawn1,spawn2,CCCallFunc::create(_callTarget, _callback),NULL));
}

void ToyManager::flyAnim(cocos2d::CCSprite *_toy, cocos2d::CCObject *_callTarget, SEL_CallFunc _callback){
    CCPoint toyInitPos = _toy->getPosition();
    
    CCMoveTo* move1 = CCMoveTo::create(0.5, ccp(toyInitPos.x+600, toyInitPos.y+100));
    CCMoveTo* move2 = CCMoveTo::create(0.5, ccp(toyInitPos.x+200, toyInitPos.y+200));
    CCMoveTo* reverseMove = CCMoveTo::create(0.5, toyInitPos);
    
    _toy->runAction(CCSequence::create(move1,move2,reverseMove,CCCallFunc::create(_callTarget, _callback),NULL));
}

void ToyManager::rotateFlyAnim(cocos2d::CCSprite *_toy, cocos2d::CCObject *_callTarget, SEL_CallFunc _callback){
    CCPoint toyInitPos = _toy->getPosition();
    
    CCMoveTo* move1 = CCMoveTo::create(0.5, ccp(toyInitPos.x+300, toyInitPos.y+300));
    CCMoveTo* move2 = CCMoveTo::create(0.5, ccp(toyInitPos.x+600, toyInitPos.y+200));
    CCMoveTo* reverseMove = CCMoveTo::create(0.5, toyInitPos);
    
    CCRotateBy* rotate = CCRotateBy::create(0.5, 1080);
    CCRotateBy* rotate2 = CCRotateBy::create(0.5, 1080);
    CCRotateBy* rotate3 = CCRotateBy::create(0.5, 1080);
    
    CCSpawn* spawn1 = CCSpawn::createWithTwoActions(move1, rotate);
    CCSpawn* spawn2 = CCSpawn::createWithTwoActions(move2, rotate2);
    CCSpawn* spawn3 = CCSpawn::createWithTwoActions(reverseMove, rotate3);
    
    _toy->runAction(CCSequence::create(spawn1,spawn2,spawn3,CCCallFunc::create(_callTarget, _callback),NULL));
}

void ToyManager::rotateAnim(cocos2d::CCSprite *_toy, cocos2d::CCObject *_callTarget, SEL_CallFunc _callback){
    CCSize winSize = GameManager::sharedManager()->getViewVisibleSize();
    CCPoint leftBottom = GameManager::sharedManager()->getLeftBottomPos();
    CCPoint center = GameManager::sharedManager()->getCenter();
    
    CCPoint toyInitPos = _toy->getPosition();
    
    CCMoveTo* move1 = CCMoveTo::create(0.4, ccp(winSize.width/2, winSize.height/2));
    CCRotateTo* rotate1 = CCRotateTo::create(0.4, -30);
    CCRotateTo* rotate2 = CCRotateTo::create(0.4, 30);
    CCRotateTo* reverseRotate = CCRotateTo::create(0.5, 0);
    CCMoveTo* reverseMove = CCMoveTo::create(0.5, toyInitPos);
    
    _toy->runAction(CCSequence::create(move1,rotate1,rotate2,reverseRotate,reverseMove,CCCallFunc::create(_callTarget, _callback),NULL));
}

void ToyManager::fanAnim(cocos2d::CCSprite *_toy, cocos2d::CCObject *_callTarget, SEL_CallFunc _callback){
    CCRotateBy* rotate = CCRotateBy::create(0.5, 0.0, -30.0);
    CCSkewBy* skew = CCSkewBy::create(0.5, 0.0, -30);
    CCScaleTo* scale = CCScaleTo::create(0.3, 1.0, 0.8);
    CCScaleTo* reScale = CCScaleTo::create(0.3, 1.0, 1.0);
//    CCSkewBy* reverseSkew = skewTo->reverse();
    
    CCSequence* seq = CCSequence::createWithTwoActions(scale, reScale);
    
    CCRepeat* repeat = CCRepeat::create(seq, 3);
    
    _toy->runAction(CCSequence::create(repeat,CCCallFunc::create(_callTarget, _callback),NULL));
}

void ToyManager::jumpAnim(cocos2d::CCSprite *_toy, cocos2d::CCObject *_callTarget, SEL_CallFunc _callback){
    
    CCPoint toyInitPos = _toy->getPosition();
    
    CCJumpTo* jump = CCJumpTo::create(1.0, toyInitPos, 180, 1);
    
    CCJumpTo* jump1 = CCJumpTo::create(0.5, toyInitPos, 30, 1);
    CCScaleTo* scale = CCScaleTo::create(0.3, 1.0, 0.8);
    CCScaleTo* reScale = CCScaleTo::create(0.3, 1.0, 1.0);
    
    CCRepeat* repeat = CCRepeat::create(CCSequence::create(scale,reScale,NULL), 2);
    
    _toy->runAction(CCSequence::create(jump,jump1,CCCallFunc::create(_callTarget, _callback),NULL));
}

void ToyManager::rockAnim(cocos2d::CCSprite *_toy, cocos2d::CCObject *_callTarget, SEL_CallFunc _callback){
    
    _toy->setAnchorPoint(CCPoint(0.5, 0.0));
    _toy->setPosition(ccp(_toy->getPosition().x, _toy->getPosition().y-_toy->getContentSize().height/2));
    
    CCRotateTo* rotate1 = CCRotateTo::create(0.4, 10);
    CCRotateTo* rotate2 = CCRotateTo::create(0.8, -10);
    CCRotateTo* reverseRotate = CCRotateTo::create(0.4, 0);
    
    _toy->runAction(CCSequence::create(rotate1,CCDelayTime::create(0.2),rotate2,CCDelayTime::create(0.2),reverseRotate,CCCallFunc::create(_callTarget, _callback),NULL));
}

void ToyManager::updownAnim(cocos2d::CCSprite *_toy, cocos2d::CCObject *_callTarget, SEL_CallFunc _callback){
    
    CCPoint toyInitPos = _toy->getPosition();
    
    CCMoveTo* move1 = CCMoveTo::create(0.8, ccp(toyInitPos.x, toyInitPos.y+200));
    
    CCMoveTo* move2 = CCMoveTo::create(0.8, ccp(toyInitPos.x, toyInitPos.y));
    
    CCRepeat* repeat = CCRepeat::create(CCSequence::create(move1,move2,NULL), 2);
    
    _toy->runAction(CCSequence::create(repeat,CCCallFunc::create(_callTarget, _callback),NULL));
    
}

void ToyManager::dragonAnim(cocos2d::CCSprite *_toy, cocos2d::CCObject *_callTarget, SEL_CallFunc _callback){
    
    CCPoint toyInitPos = _toy->getPosition();
    
    CCScaleTo* scale1 = CCScaleTo::create(0.4, 1.5);
    CCScaleTo* scale2 = CCScaleTo::create(0.4, 1.0);
    CCMoveTo* move1 = CCMoveTo::create(0.4, ccp(toyInitPos.x+20, toyInitPos.y+50));
    CCMoveTo* move2 = CCMoveTo::create(0.4, toyInitPos);
    
    CCRotateTo* rotate1 = CCRotateTo::create(0.2, 10);
    CCRotateTo* rotate2 = CCRotateTo::create(0.4, -10);
    CCRotateTo* reverseRotate = CCRotateTo::create(0.2, 0);
    
    CCSpawn* spawn1 = CCSpawn::createWithTwoActions(scale1, move1);
    CCSpawn* spawn2 = CCSpawn::createWithTwoActions(scale2, move2);
    
    _toy->runAction(CCSequence::create(spawn1,rotate1,rotate2,reverseRotate,spawn2,CCCallFunc::create(_callTarget, _callback),NULL));
}

void ToyManager::rocketAnim(cocos2d::CCSprite *_toy, cocos2d::CCObject *_callTarget, SEL_CallFunc _callback){
    CCPoint toyInitPos = _toy->getPosition();
    
    CCMoveTo* move1 = CCMoveTo::create(0.8, ccp(toyInitPos.x+500, toyInitPos.y+200));
    CCMoveTo* move2 = CCMoveTo::create(0.8, ccp(toyInitPos.x+300, toyInitPos.y+300));
    CCMoveTo* move3 = CCMoveTo::create(0.8, ccp(toyInitPos.x, toyInitPos.y+20));
    CCMoveTo* reverseMove = CCMoveTo::create(0.8, ccp(toyInitPos.x, toyInitPos.y));
    
    CCRotateTo* rotate1 = CCRotateTo::create(0.0, 45);
    CCRotateTo* rotate2 = CCRotateTo::create(0.0, -45);
    CCRotateTo* rotate3 = CCRotateTo::create(0.8, 0);
    
    CCSpawn* spawn1 = CCSpawn::createWithTwoActions(move1, rotate1);
    CCSpawn* spawn2 = CCSpawn::createWithTwoActions(move2, rotate2);
    CCSpawn* spawn3 = CCSpawn::createWithTwoActions(move3, rotate3);
    
    _toy->runAction(CCSequence::create(spawn1,spawn2,spawn3,reverseMove,CCCallFunc::create(_callTarget, _callback),NULL));
}


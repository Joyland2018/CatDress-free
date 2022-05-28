//
//  DrawSprite.cpp
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-21.
//
//

#include "DrawSprite.h"

DrawSprite* DrawSprite::create(const char *pszFileName){
    DrawSprite *sprite = new DrawSprite();
    
    if (sprite && sprite->initWithFile(pszFileName)) {
        
        //        sprite->
        
        sprite->autorelease();
        
        return sprite;
        
    }
    
    CC_SAFE_DELETE(sprite);
    
    sprite = NULL;
    
    return NULL;
};

DrawSprite::DrawSprite(){
    
    pointArray = CCArray::create();
    pointArray->retain();
    
    for (int i = 0; i < 8; i++) {
        
        DrawPoint* drawPoint = new DrawPoint();
        
        pointArray->addObject(drawPoint);
    }
    
    for (int i = 0; i < 7; i++) {
//        CCArray* itemPoint = CCArray::create();
//        pointArray->addObject(itemPoint);
        red[i] = 255;
        green[i] = 255;
        blue[i] = 255;
        alpha[i] = 255;
    }
//    pointArray = NULL;
}

DrawSprite::~DrawSprite(){
    
}

void DrawSprite::onEnter(){
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
    CCSprite::onEnter();
}

void DrawSprite::onExit(){
    pointArray->removeAllObjects();
    pointArray->release();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

void DrawSprite::draw(){
    CCSprite::draw();
    
    if (pointArray != NULL) {
        
        CCObject* pObject;
        
        CCARRAY_FOREACH(pointArray, pObject){
            DrawPoint* drawPoint = (DrawPoint*)pObject;
            int i = drawPoint->colorIndex;
            ccDrawColor4B(red[i], green[i], blue[i], alpha[i]);
            glLineWidth(20);
            CCPoint location = drawPoint->_curPos;
            CCPoint newLoc = this->convertToNodeSpace(ccp(location.x, location.y));
            
            ccDrawCircle(newLoc, 42, 40, 20, true);
        }
        
//        for (int i = 0; i < pointArray->count(); i++) {
//            CCArray* itemPoint = (CCArray*)pointArray->objectAtIndex(i);
//            for (int j = 0; j < itemPoint->count(); j++) {
//                
//                
//            }
//        }
    }
}

void DrawSprite::isCanDraw(bool isDraw){
    if (isDraw == true) {
        CCArray* itemPoint = CCArray::create();
        pointArray->addObject(itemPoint);
    }else{
        pointArray->release();
        pointArray = NULL;
    }
}

void DrawSprite::setBrushColor(const ccColor4B &color,int _tag){
    red[_tag] = color.r;
    green[_tag] = color.g;
    blue[_tag] = color.b;
    alpha[_tag] = color.a;
}

void DrawSprite::setDrawPoint(cocos2d::CCPoint location,int _tag,int _colorTag){
    
    if (pointArray != NULL) {
        
//        CCArray* itemPoint = (CCArray*)pointArray->objectAtIndex(_tag);
        
//        if (pointArray->count() >= 600) {
//            pointArray->removeObjectAtIndex(0);
//        }
        
        DrawPoint* drawPoint = (DrawPoint*)pointArray->objectAtIndex(_tag);
        drawPoint->setPointPos(location, _colorTag);
        
//        pointArray->addObject(drawPoint);
        
//        if (itemPoint != NULL) {
//            
//            CCPoint* newPoint = new CCPoint();
//            newPoint->x = location.x;
//            newPoint->y = location.y;
//            itemPoint->addObject(newPoint);
//            
//            newPoint->release();
//            newPoint = NULL;
//        }
    }
}

bool DrawSprite::ccTouchBegan(CCTouch* touch, CCEvent* event){
    
    CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    
    return true;
}

void DrawSprite::ccTouchMoved(CCTouch* touch, CCEvent* event){
    //    CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
    
    CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    
    
}

void DrawSprite::ccTouchEnded(CCTouch* touch, CCEvent* event){
    
}

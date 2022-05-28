//
//  DrawSprite.h
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-21.
//
//

#ifndef CatDressUp_DrawSprite_h
#define CatDressUp_DrawSprite_h

#include "cocos2d.h"
#include "DrawPoint.h"

using namespace cocos2d;

class DrawSprite : public CCSprite,public CCTouchDelegate{
public:
    static DrawSprite* create(const char *pszFileName);
//    static DrawSprite* create(CCTexture2D* texture);
    
    DrawSprite();
    ~DrawSprite();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual void draw();
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    void isCanDraw(bool isDraw);
    
    void setBrushColor(const ccColor4B& color,int _tag);
    void setDrawPoint(CCPoint location,int _tag,int _colorTag);
public:
    CCArray* pointArray;
    
    int red[7];
    int green[7];
    int blue[7];
    int alpha[7];
};

#endif

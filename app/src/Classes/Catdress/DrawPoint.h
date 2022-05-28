//
//  DrawPoint.h
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-26.
//
//

#ifndef __CatDressUp__DrawPoint__
#define __CatDressUp__DrawPoint__

//#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class DrawPoint : public CCObject{
public:
    CCPoint _curPos;
    int colorIndex;
public:
    DrawPoint();
    void setPointPos(CCPoint _location,int _colorIndex);
};

#endif /* defined(__CatDressUp__DrawPoint__) */

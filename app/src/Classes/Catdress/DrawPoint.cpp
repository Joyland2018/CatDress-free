//
//  DrawPoint.cpp
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-26.
//
//

#include "DrawPoint.h"

DrawPoint::DrawPoint(){
    colorIndex = 0;
}

void DrawPoint::setPointPos(cocos2d::CCPoint _location, int _colorIndex){
    this->_curPos.x = _location.x;
    this->_curPos.y = _location.y;
    this->colorIndex = _colorIndex;
}

//
//  CatDressManager.h
//  CatDressUp
//
//  Created by 李 文峰 on 13-6-4.
//
//

#ifndef CatDressUp_CatDressManager_h
#define CatDressUp_CatDressManager_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ToyManager.h"
#include "GameManager.h"

using namespace cocos2d;
using namespace extension;

class CatDressManager{
public:
    static CatDressManager* sharedManager();
    
    CatDressManager();
    virtual ~CatDressManager();
    
    CCPoint getLeftTopPos();
    CCPoint getLeftBottomPos();
    CCPoint getRightTopPos();
    CCPoint getRightBottomPos();
    CCPoint getCenter();
    CCPoint getViewInitPos();
    CCSize getViewVisibleSize();
    
    CCDictionary* getDictionary(const char *pName,CCDictionary* _dic);
    CCPoint getPos(const char *pName,CCDictionary* _dic);
    void selectPar(CCSprite* pSprite ,int pTag,CCPoint curPos);
    void setSprayPar(CCSprite* pSprite,const char *pName,CCPoint curPos);
    void setMagicPar(CCSprite* pSprite,const char *pName,CCPoint curPos);
    void setRocketPar(CCSprite* pSprite,const char *pName,CCPoint curPos);
    void setGunPar(CCSprite* pSprite,const char *pName,CCPoint curPos);
    CCAnimate* getSpriteAnimate(int initFrame,int frameMaxNum,const char* fileName,bool isRestoreFrame);
    
    CCLayer* getCatSprite(int _catIndex,CCPoint _eyeLPos,CCPoint _eyeRPos);
    
    CCLayer* getMenuLayer();
    
    CCSprite* getToySpr(int _toyIndex);
};

#endif

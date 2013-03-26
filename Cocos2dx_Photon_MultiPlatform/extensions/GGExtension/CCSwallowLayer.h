//
//  CCSwallowLayer.h
//  PhotonOnline
//
//  Created by George Guy on 12/10/12.
//
//

#ifndef __PhotonOnline__CCSwallowLayer__
#define __PhotonOnline__CCSwallowLayer__

#include "cocos2d.h"

class CCSwallowLayer : public cocos2d::CCLayer
{
public:
	typedef cocos2d::CCLayer super;
    CCSwallowLayer() : cocos2d::CCLayer() {};
    
    CREATE_FUNC( CCSwallowLayer );
    virtual bool init();
    virtual bool ccTouchBegan(cocos2d::CCTouch *touch,cocos2d::CCEvent *event);
};

#endif /* defined(__PhotonOnline__CCSwallowLayer__) */

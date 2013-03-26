//
//  CCRecursiveAction.h
//  Abstroku
//
//  Created by George Guy on 9/15/12.
//
//

#ifndef Abstroku_CCRecursiveAction_h
#define Abstroku_CCRecursiveAction_h

#include "cocos2d.h"
#include "GGUtil.h"

class CCRecursiveAction : public cocos2d::CCActionInstant
{
public:
	CC_SYNTHESIZE( bool, _innerIsInstant, InnerIsInstant );
    CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*, _innerAction, InnerAction);
    CC_SYNTHESIZE(cocos2d::CCNode*, _exemptNode, ExemptNode);
public:
    CCRecursiveAction() : cocos2d::CCActionInstant()
    { this->_innerAction = NULL; };
    ~CCRecursiveAction()
    { CC_SAFE_RELEASE_NULL( this->_innerAction ); };

    virtual void runInstantInnerActionOnChildren( cocos2d::CCNode* target );
    virtual void update( float delta );
    virtual bool init( cocos2d::CCAction* innerAction, cocos2d::CCNode* exemptNode = NULL, int instant = -1 );
    static CCRecursiveAction* create( cocos2d::CCAction* innerAction, cocos2d::CCNode* exemptNode = NULL );
    
    COPY_INIT_FUNC( CCRecursiveAction, cocos2d::CCActionInstant, init(
                                                                       (cocos2d::CCAction*)this->_innerAction->copy(),
                                                                       this->getExemptNode(), this->getInnerIsInstant() ) );
};

template<class targetType>
class CaTTypedRecursiveAction : public CCRecursiveAction
{
public:
    CaTTypedRecursiveAction() : CCRecursiveAction() {};
    
    virtual void update( float delta );
    static CaTTypedRecursiveAction* create( cocos2d::CCAction* innerAction, cocos2d::CCNode* exemptNode = NULL );
    
    COPY_FUNC( CaTTypedRecursiveAction<targetType>, CCRecursiveAction );
};

/*template<class callFuncTargetType>
class CaTTypedRecursiveCallFunc : public CaTTypedRecursiveAction<callFuncTargetType>
{
public:
    CaTTypedRecursiveCallFunc() : CaTTypedRecursiveAction<callFuncTargetType>() {};
    
    virtual void startWithTarget( cocos2d::CCNode* target );
    static CaTTypedRecursiveCallFunc* create( cocos2d::CCCallFunc* innerAction, cocos2d::CCNode* exemptNode = NULL );
};*/

#endif

#pragma once

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(HelloWorld);
};

/*
#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
	__TYPE__ *pRet = new __TYPE__(); \
	if (pRet && pRet->init()) \
	{ \
		pRet->autorelease(); \
		return pRet; \
	} \
	else \
	{ \
		delete pRet; \
		pRet = NULL; \
		return NULL; \
	} \
}
*/

#pragma once

#include "cocos2d.h"
#include "InputHandler.h"
#include "Player.h"
#include "Stage.h"
USING_NS_CC;

class Level : public Stage
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(Level);
};

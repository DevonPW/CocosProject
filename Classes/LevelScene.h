#pragma once

#include "cocos2d.h"

class Level : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update();

	CREATE_FUNC(Level);
private:
	cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format, int count);
};
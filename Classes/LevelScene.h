#pragma once

#include "cocos2d.h"
#include "InputHandler.h"
USING_NS_CC;

class Level : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float deltaTime);

	CREATE_FUNC(Level);
private:
	cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format, int count);

	Director* director = Director::getInstance();

	Node* stuff;

	Node* camPos;

	Vec2 playerPos;
	//Sprites
	Sprite* background;
	Sprite* knife;
	Sprite* player;
	Sprite* guard;
	Sprite* visionCone;
	Sprite* wall1;
	Sprite* wall2;
	Sprite* floor1;
	Sprite* floor2;
};

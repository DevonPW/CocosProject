#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = HelloWorld::create();

	scene->addChild(layer);

	return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto label = Label::createWithSystemFont("Hello World", "Arial", 96);
	label->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	this->addChild(label, 1);

	auto sprite = Sprite::create("MainCharacter.png");
	this->addChild(sprite, 1);
	sprite->setPosition(100, 100);
	sprite->setAnchorPoint(Vec2(0, 0));
	

	return true;
}
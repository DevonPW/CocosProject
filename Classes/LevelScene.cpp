#include "LevelScene.h"

USING_NS_CC;

Scene* Level::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = Level::create();

	scene->addChild(layer);

	return scene;
}

bool Level::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto label = Label::createWithSystemFont("Hello World", "Arial", 96);
	label->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	this->addChild(label, 1);

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("cityscene.plist");

	// background
	auto background = Sprite::createWithSpriteFrameName("background.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(0,0);
	this->addChild(background);

	Sprite* dude = Sprite::create("MainCharacter2.png");
	dude->setPosition(200, 200);
	this->addChild(dude, 1);

	return true;
}

void Level::update()
{

}

Vector<SpriteFrame*> Level::getAnimation(const char *format, int count)
{
	auto spritecache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames;
	char str[100];
	for (int i = 1; i <= count; i++)
	{
		sprintf(str, format, i);
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	return animFrames;
}
#include "LevelScene.h"

USING_NS_CC;

Scene* Level::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = Level::create();

	scene->getPhysicsWorld()->setGravity(Vec2(0, -100));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->addChild(layer);

	return scene;
}

bool Level::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	//Labelling
	auto label = Label::createWithSystemFont("Hello World", "Arial", 96);
	label->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	this->addChild(label, 1);

	//this is how to use a sprite sheet (.plist), to load sprites, for animations
	/*
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("cityscene.plist");

	// background
	auto background = Sprite::createWithSpriteFrameName("background.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(0,0);
	this->addChild(background);
	*/

	//getting a sprite from a sprite sheet and animating it
	/*
	auto frames = getAnimation("capguy/walk/%04d.png", 8);
	auto sprite = Sprite::createWithSpriteFrame(frames.front());
	this->addChild(sprite);
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(0, 300);
	//setting physics body
	auto body = PhysicsBody::createBox(sprite->getContentSize());
	sprite->setPhysicsBody(body);
	
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
	sprite->runAction(RepeatForever::create(Animate::create(animation)));
	*/

	/*//this is for moving a sprite ina set sequence
	auto movement = MoveBy::create(10, Vec2(1080, 0));
	auto resetPosition = MoveTo::create(0, Vec2(0, 300));
	auto sequence = Sequence::create(movement, resetPosition, NULL);
	sprite->runAction(RepeatForever::create(sequence));
	*/
	auto background = Sprite::create("mansionPhoto.jpg");
	background->setContentSize(Size(1920, 1080));
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(0, 0);
	this->addChild(background, 0);

	auto rectangle = Sprite::create("square.png");
	rectangle->setContentSize(Size(600, 100));
	rectangle->setAnchorPoint(Vec2(0, 0));
	rectangle->setPosition(0, 0);
	this->addChild(rectangle,1);

	auto rectBody = PhysicsBody::createBox(rectangle->getContentSize());
	rectBody->setDynamic(false);
	rectangle->setPhysicsBody(rectBody);

	//creating collision box on edge of screens
	auto director = Director::getInstance();
	auto floor = PhysicsBody::createEdgeBox(director->getWinSizeInPixels(),PHYSICSBODY_MATERIAL_DEFAULT,1.0f,Vec2(0, 0));
	floor->setDynamic(false);
	this->addComponent(floor);

	auto player = Sprite::create("player.png");
	player->setScale(2.0);
	player->setAnchorPoint(Vec2(0, 0));
	player->setPosition(400, 300);
	this->addChild(player,2);

	auto playerBody = PhysicsBody::createBox(player->getContentSize());
	playerBody->setDynamic(true);
	player->setPhysicsBody(playerBody);

	auto guard = Sprite::create("guard.png");
	guard->setScale(2.0);
	guard->setAnchorPoint(Vec2(0, 0));
	guard->setPosition(600, 300);
	this->addChild(guard,2);

	auto guardBody = PhysicsBody::createBox(guard->getContentSize());
	guardBody->setDynamic(true);
	guard->setPhysicsBody(guardBody);

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
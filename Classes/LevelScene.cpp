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

	stuff = Node::create();
	this->addChild(stuff);

	//Labelling
	/*auto label = Label::createWithSystemFont("Hello World", "Arial", 96);
	label->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	stuff->addChild(label, 1);*/

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
	background = Sprite::create("mansionPhoto.jpg");
	//background->setContentSize(Size(1920, 1080));
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(0, 0);
	background->setScale(0.5);
	stuff->addChild(background, 0);

	//creating collision box on edge of game area
	auto border = PhysicsBody::createEdgeBox(background->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT,1.0f,Vec2(0, 0));
	border->setDynamic(false);
	background->addComponent(border);

	//Walls
	wall1 = Sprite::create("square.png");
	wall1->setContentSize(Size(25, 650));
	wall1->setAnchorPoint(Vec2(0, 0));
	wall1->setPosition(100, 25);
	stuff->addChild(wall1, 1);
	auto wall1Body = PhysicsBody::createBox(wall1->getContentSize());
	wall1Body->setDynamic(false);
	wall1->setPhysicsBody(wall1Body);

	wall2 = Sprite::create("square.png");
	wall2->setContentSize(Size(25, 650));
	wall2->setAnchorPoint(Vec2(0, 0));
	wall2->setPosition(1075, 25);
	stuff->addChild(wall2, 1);
	auto wall2Body = PhysicsBody::createBox(wall2->getContentSize());
	wall2Body->setDynamic(false);
	wall2->setPhysicsBody(wall2Body);

	floor1 = Sprite::create("square.png");
	floor1->setContentSize(Size(1000, 25));
	floor1->setAnchorPoint(Vec2(0, 0));
	floor1->setPosition(100, 0);
	stuff->addChild(floor1, 1);
	auto floor1Body = PhysicsBody::createBox(floor1->getContentSize());
	floor1Body->setDynamic(false);
	floor1->setPhysicsBody(floor1Body);

	floor2 = Sprite::create("square.png");
	floor2->setContentSize(Size(1000, 25));
	floor2->setAnchorPoint(Vec2(0, 0));
	floor2->setPosition(100, 675);
	stuff->addChild(floor2, 1);
	auto floor2Body = PhysicsBody::createBox(floor2->getContentSize());
	floor2Body->setDynamic(false);
	floor2->setPhysicsBody(floor2Body);
	
	//Items
	knife = Sprite::create("knife.png");
	knife->setScale(0.75);
	knife->setFlippedX(true);
	knife->setAnchorPoint(Vec2(0, 0));
	knife->setPosition(400, 25);
	stuff->addChild(knife);

	//Invisible Node for the camera to follow
	camPos = Node::create();
	stuff->addChild(camPos, 2);

	//Characters
	player = Sprite::create("player.png");
	player->setScale(1.5);
	player->setAnchorPoint(Vec2(0, 0));
	player->setPosition(200, 25);
	stuff->addChild(player, 2);
	playerPos = (player->getPosition());

	auto playerBody = PhysicsBody::createBox(player->getContentSize());
	playerBody->setDynamic(true);
	playerBody->setCollisionBitmask(0x01);
	player->setPhysicsBody(playerBody);

	guard = Sprite::create("guard.png");
	guard->setScale(1.5);
	guard->setAnchorPoint(Vec2(0, 0));
	guard->setPosition(500, 25);
	stuff->addChild(guard,2);

	auto guardBody = PhysicsBody::createBox(guard->getContentSize());
	guardBody->setDynamic(true);
	guard->setPhysicsBody(guardBody);

	visionCone = Sprite::create("visionCone.png");
	visionCone->setScale(0.75);
	visionCone->setAnchorPoint(Vec2(0, 0));
	guard->addChild(visionCone, 3);
	visionCone->setPositionNormalized(Vec2(1, 0.4));

	auto visionBody = PhysicsBody::createBox(visionCone->getContentSize());
	visionBody->setDynamic(false);
	visionBody->setCategoryBitmask(0x02);
	visionCone->setPhysicsBody(visionBody);

	//guard moves automatically
	auto movement = MoveBy::create(5, Vec2(400, 0));
	auto turn = ScaleBy::create(0.0f,-1.0f, 1.0f);
	auto wait = MoveBy::create(0.5, Vec2(0, 0));
	auto moveback = MoveBy::create(5, Vec2(-400, 0));
	auto sequence = Sequence::create(movement, wait, turn, moveback, wait, turn, NULL);
	guard->runAction(RepeatForever::create(sequence));

	stuff->runAction(Follow::create(camPos, Rect::ZERO));//makes "camera" follow player

	this->scheduleUpdate();

	return true;
}

void Level::update(float deltaTime)
{
	//player movement
	if (INPUTS->getKey(KeyCode::KEY_D)) {
		playerPos = player->getPosition() + Vec2(5, 0);
		player->setPosition(playerPos);
		if (player->isFlippedX() == true) {
			player->setFlippedX(false);
		}
	}
	else if (INPUTS->getKey(KeyCode::KEY_A)) {
		playerPos = player->getPosition() + Vec2(-5, 0);
		player->setPosition(playerPos);
		if (player->isFlippedX() == false) {
			player->setFlippedX(true);
		}
	}

	if ((player->getPhysicsBody()->getCategoryBitmask() & visionCone->getPhysicsBody()->getCollisionBitmask()) == 0
		|| (visionCone->getPhysicsBody()->getCollisionBitmask() & player->getPhysicsBody()->getCategoryBitmask()) == 0)
	{
	}

	//positioning camera node to be below player (adding it as a child of player doesn't work)
	camPos->setPosition(player->getPosition() - Vec2(0, -400));

	//update the keybord each frame
	INPUTS->clearForNextFrame();
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
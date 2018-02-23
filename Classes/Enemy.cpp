#include "Enemy.h"

Enemy::Enemy()
{
	//sprite properties
	spriteName = "guard.png";
	scale = 1.5f;
	//physics body properties
	tag = 2;
	dynamic = true;

	initSprite();//sets the image for the sprite and other properties such as anchor point at (0,0); also creates physics body based on image

	initPhysics();//sets properties of the physics body and attaches it to sprite

	//initializing vision cone
	vision = Sprite::create("visionCone.png");
	vision->setScale(0.75);
	vision->setAnchorPoint(Vec2(0, 0));
	vision->setPositionNormalized(Vec2(1, 0.4));

	auto visionBody = PhysicsBody::createBox(vision->getContentSize());
	visionBody->setDynamic(false);
	visionBody->setCategoryBitmask(2);
	visionBody->setCollisionBitmask(3);
	visionBody->setContactTestBitmask(0xFFFFFFFF);
	visionBody->setTag(2);
	vision->setPhysicsBody(visionBody);

	sprite->addChild(vision);
}


Enemy::~Enemy()
{
}

#include "Player.h"

Player::Player()
{
	//sprite properties
	spriteName = "player.png";
	scale = 1.5f;
	//physics body properties
	tag = 1;
	dynamic = true;

	initSprite();//sets the image for the sprite and other properties such as anchor point at (0,0); also creates physics body based on image

	initPhysics();//sets properties of the physics body and attaches it to sprite
}


Player::~Player()
{
}

Player* Player::create(const std::string& filename)
{
	Player *sprite = new (std::nothrow) Player();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

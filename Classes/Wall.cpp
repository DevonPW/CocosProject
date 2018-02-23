#include "Wall.h"



Wall::Wall()
{
	//sprite properties
	spriteName = "default.png";
	scale = 1.0f;
	//physics body properties
	tag = 0;
	dynamic = false;

	initSprite();//sets the image for the sprite and other properties such as anchor point at (0,0); also creates physics body based on image

	sprite->setContentSize(Size(25, 25));//set the size of the wall, default is 25 X 25

	initPhysics();//sets properties of the physics body and attaches it to sprite
}

Wall::Wall(Size size)
{
	//sprite properties
	spriteName = "default.png";
	scale = 1.0f;
	//physics body properties
	tag = 0;
	dynamic = false;

	initSprite();//sets the image for the sprite and other properties such as anchor point at (0,0); also creates physics body based on image

	sprite->setContentSize(size);//set the size of the wall

	initPhysics();//sets properties of the physics body and attaches it to sprite
}


Wall::~Wall()
{
}

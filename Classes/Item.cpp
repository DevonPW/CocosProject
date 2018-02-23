#include "Item.h"



Item::Item()
{
	//sprite properties
	spriteName = "knife.png";
	scale = 0.75f;
	//physics body properties
	tag = 3;
	dynamic = false;
	category = 2;
	collision = 2;

	initSprite();//sets the image for the sprite and other properties such as anchor point at (0,0); also creates physics body based on image

	initPhysics();//sets properties of the physics body and attaches it to sprite
}


Item::~Item()
{
}

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


	//set the background name before calling setup
	backgroundName = "mansionPhoto.jpg";

	//initlializes stuff that is the same for all levels
	setup();

	//set player starting position
	player->setPosition(200, 25);

	//Walls
	auto wall = new Wall(Size(25, 650));
	wall->setPosition(100, 25);
	walls.push_back(wall);

	wall = new Wall(Size(25, 650));
	wall->setPosition(1075, 25);
	walls.push_back(wall);

	wall = new Wall(Size(1000, 25));
	wall->setPosition(100, 0);
	walls.push_back(wall);

	wall = new Wall(Size(1000, 25));
	wall->setPosition(100, 675);
	walls.push_back(wall);

	for (int i = 0; i < walls.size(); i++) {
		mainLayer->addChild(walls[i], 1);
	}
	
	//Items
	auto item = new Item;
	item->sprite->setFlippedX(true);
	item->setPosition(400, 25);
	items.push_back(item);
	mainLayer->addChild(items[0], 3);

	//Enemies
	auto guard = new Enemy;
	guard->setPosition(500, 25);

	//guard moves automatically
	auto movement = MoveBy::create(5, Vec2(400, 0));
	auto turn = ScaleBy::create(0.0f,-1.0f, 1.0f);
	auto wait = MoveBy::create(0.5, Vec2(0, 0));
	auto moveback = MoveBy::create(5, Vec2(-400, 0));
	auto sequence = Sequence::create(movement, wait, turn, moveback, wait, turn, NULL);
	guard->runAction(RepeatForever::create(sequence));

	enemies.push_back(guard);
	mainLayer->addChild(enemies[0], 2);

	return true;
}

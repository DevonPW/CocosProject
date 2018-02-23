#include "AppDelegate.h"
#include "LevelScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
	auto director = Director::getInstance();
	director->setAnimationInterval(1.0 / 60);
	director->setDisplayStats(true);
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::createWithRect("Hello", Rect(0, 0, 1920, 1080), 1, false);
		//glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);
		//glview->setFrameSize(1280, 720);
		director->setOpenGLView(glview);
	}

	auto level = Level::createScene();
	director->runWithScene(level);

	//Set up the input handler
	INPUTS->init();

	return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}

#include "HelloWorldScene.h"
#include"map.h"
#include"button.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = new HelloWorld();
	if (scene&&scene-> init() ) {
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return NULL;
}
bool HelloWorld::init()
{
	auto a = map::create();
	auto b = button::create();
	a->buttonlayer = b;
	addChild(a);
	addChild(b);
    return true;
}



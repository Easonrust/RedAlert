#include "SelectScene.h"

USING_NS_CC;

Scene* Select::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Select::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Select::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *bg = Sprite::create("background.jpg");

	// position the label on the center of the screen
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(40);
	
	// 
	MenuItemFont*lastMenuItem = MenuItemFont::create("GO BACK", CC_CALLBACK_1(Select::menuLastToggleCallback, this));
	lastMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(900, 500)));

	MenuItemFont*map1MenuItem = MenuItemFont::create("MAP1", CC_CALLBACK_1(Select::menuMap1ToggleCallback, this));
	map1MenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(580, 250)));

	MenuItemFont*map2MenuItem = MenuItemFont::create("MAP2", CC_CALLBACK_1(Select::menuMap2ToggleCallback, this));
	map2MenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(580, 300)));

	Menu* mu = Menu::create(lastMenuItem,map2MenuItem, map1MenuItem, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu);

	return true;
}

void Select::menuLastToggleCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

void Select::menuMap1ToggleCallback(Ref* pSender)
{
	
}

void Select::menuMap2ToggleCallback(Ref* pSender)
{

}
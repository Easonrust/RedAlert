#include "MainMenuScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* MainMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//ÉèÖÃ±³¾°
	Sprite *bg = Sprite::create("background.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(80);
	//¿ªÊ¼¡¢ÉèÖÃ¡¢°ïÖú²Ëµ¥

	MenuItemFont*startMenuItem = MenuItemFont::create("Start", CC_CALLBACK_1(MainMenu::menuItemStartCallback, this));
	MenuItemFont*settingMenuItem = MenuItemFont::create("Setting ", CC_CALLBACK_1(MainMenu::menuItemSettingCallback, this));
	MenuItemFont*helpMenuItem = MenuItemFont::create("Exit", CC_CALLBACK_1(MainMenu::menuItemExitCallback, this));

	Menu* mu = Menu::create(startMenuItem, settingMenuItem, helpMenuItem, NULL);
	mu->alignItemsVertically();
	this->addChild(mu);

	return true;
}

void MainMenu::menuItemStartCallback(Ref* pSender)
{
	auto sc = Select::createScene();
	//Director::getInstance()->replaceScene(sc);
	Director::getInstance()->pushScene(sc);
	SimpleAudioEngine::getInstance()->playEffect("sound/Blip.wav");
}

void MainMenu::menuItemSettingCallback(Ref* pSender)
{
	auto sc = Setting::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	//Director::getInstance()->replaceScene(sc);
	Director::getInstance()->pushScene(reScene);
	SimpleAudioEngine::getInstance()->playEffect("sound/Blip.wav");
}

void MainMenu::menuItemExitCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
	SimpleAudioEngine::getInstance()->playEffect("sound/Blip.wav");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}

void MainMenu::onEnter()
{
	Layer::onEnter();
	log("MainMenu onEnter");
}

void MainMenu::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("MainMenu onEnterTransitionDidFinish");
	//²¥·Å
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Xingdi.mp3", true);
}

void MainMenu::onExit()
{
	Layer::onExit();
	log("MainMenu onExit");
}

void MainMenu::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	log("MainMenu onExitTransitionDidStart");
}

void MainMenu::cleanup()
{
	Layer::cleanup();
	log("MainMenu cleanup");
	//Í£Ö¹
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/Xingdi.mp3");
}

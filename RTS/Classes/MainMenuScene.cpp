#include "MainMenuScene.h"
#include "SystemHeader.h"
#include "InPutIPsence.h"
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
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//设置背景
    Sprite *bg = Sprite::create("background.jpg");
    bg->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height /2));
    this->addChild(bg);


	//开始、设置、退出菜单
 
	MenuItemImage*startMenuItem = MenuItemImage::create("startbutton.png","startbutton2.png", CC_CALLBACK_1(MainMenu::menuItemStartCallback, this));
	MenuItemImage*settingMenuItem = MenuItemImage::create("setbutton.png", "setbutton2.png", CC_CALLBACK_1(MainMenu::menuItemSettingCallback, this));
	MenuItemImage*exitMenuItem = MenuItemImage::create("exitbutton.png", "exitbutton2.png", CC_CALLBACK_1(MainMenu::menuItemExitCallback, this));

	startMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(570, 230)));
	settingMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(570, 320)));
	exitMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(570, 410)));

	Menu* mu = Menu::create(startMenuItem, settingMenuItem, exitMenuItem, NULL);	
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu);
    
    return true;
}

void MainMenu::menuItemStartCallback(Ref* pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	}
	log("start");
	auto sc = InputIP::createScene();
	//Director::getInstance()->replaceScene(sc);
	Director::getInstance()->pushScene(sc);
}

void MainMenu::menuItemSettingCallback(Ref* pSender)
{
	auto sc = Setting::createScene();
	//Director::getInstance()->replaceScene(sc);
	Director::getInstance()->pushScene(sc);
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	}
}

void MainMenu::menuItemExitCallback(Ref* pSender)
{
		//Close the cocos2d-x game scene and quit the application
	    SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/Lose.mp3");
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
		}
		Director::getInstance()->end();
		
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
	//播放
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Lose1.mp3", true);
	}
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
	//停止
	//SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/Lose.mp3");
}

#include "SelectScene.h"
#include "InPutIPsence.h"

USING_NS_CC;
using namespace CocosDenshion;

extern SOCKET sClient;
extern mymap*a;
extern button*b;

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
	MenuItemImage*lastMenuItem = MenuItemImage::create("go backbutton.png", "go backbutton2.png", CC_CALLBACK_1(Select::menuLastToggleCallback, this));
	lastMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(900, 490)));

	MenuItemImage*map1MenuItem = MenuItemImage::create("map1button.png", "map1button2.png", CC_CALLBACK_1(Select::menuMap1ToggleCallback, this));
	map1MenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(580, 230)));

	MenuItemImage*map2MenuItem = MenuItemImage::create("map2button.png", "map2button2.png", CC_CALLBACK_1(Select::menuMap2ToggleCallback, this));
	map2MenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(580, 330)));
	Menu* mu = Menu::create(lastMenuItem,map2MenuItem, map1MenuItem, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu);

	//初始化
	if (!InitClient())
	{
		ExitClient();
	}
	
	//连接服务器
	if (ConnectServer())
	{
		ShowConnectMsg(TRUE);
	}
	else
	{
		ShowConnectMsg(FALSE);
		ExitClient();
	}

	//创建接收数据线程
	_beginthreadex(NULL, 0, clientreceiveThread, &sClient, 0, NULL); //启动接收消息线程


	return true;
}

void Select::menuLastToggleCallback(Ref* pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	}
	Director::getInstance()->popScene();
}

void Select::menuMap1ToggleCallback(Ref* pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	}
	auto sc = HelloWorld::createScene();
	//Director::getInstance()->replaceScene(sc);
	Director::getInstance()->pushScene(sc);
}

void Select::menuMap2ToggleCallback(Ref* pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	}
}
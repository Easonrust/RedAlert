#include "SettingScene.h"
#include "SystemHeader.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* Setting::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Setting::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Setting::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//ÉèÖÃ±³¾°
	Sprite *bg = Sprite::create("setbackground2.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(40);

	//ÒôÐ§
	
    auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuSoundToggleCallback, this), 
												MenuItemImage::create("onbutton.png","onbutton.png"),
												MenuItemImage::create("offbutton.png", "offbutton.png"),
												NULL);

	soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(710,279 )));

    //ÒôÀÖ
    auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuMusicToggleCallback, this), 
												MenuItemImage::create("onbutton.png", "onbutton.png"),
												MenuItemImage::create("offbutton.png", "offbutton.png"),
												NULL);
	musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(710, 190)));

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(80);
    //Ok°´Å¥
	MenuItemImage*okMenuItem = MenuItemImage::create("okbutton.png", "okbutton2.png", CC_CALLBACK_1(Setting::menuOkCallback, this));
	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(580, 410)));

	Menu* mu = Menu::create(soundToggleMenuItem, musicToggleMenuItem,okMenuItem, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu);

	UserDefault *defaults = UserDefault::getInstance();

	if (defaults->getBoolForKey(MUSIC_KEY)) {
		musicToggleMenuItem->setSelectedIndex(0);//off
	}
	else {
		musicToggleMenuItem->setSelectedIndex(1);//on
	}

	if (defaults->getBoolForKey(SOUND_KEY)) {
		soundToggleMenuItem->setSelectedIndex(0);//off
	}
	else {
		soundToggleMenuItem->setSelectedIndex(1);//on
	}
    return true;
}

void Setting::menuOkCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	}
}

void Setting::menuSoundToggleCallback(Ref* pSender)
{
	auto soundToggleMenuItem = (MenuItemToggle*)pSender;
	log("soundToggleMenuItem %d", soundToggleMenuItem->getSelectedIndex());

	UserDefault*defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(SOUND_KEY)) {
		defaults->setBoolForKey(SOUND_KEY, false);
	}
	else {
		defaults->setBoolForKey(SOUND_KEY, true);
		SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	}
}


void Setting::menuMusicToggleCallback(Ref* pSender)
{
	auto musicToggleMenuItem = (MenuItemToggle*)pSender;
	log("musicToggleMenuItem %d", musicToggleMenuItem->getSelectedIndex());

	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	}

	UserDefault*defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		defaults->setBoolForKey(MUSIC_KEY, false);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else {
		defaults->setBoolForKey(MUSIC_KEY, true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Lose1.mp3");
	}
}


void Setting::onEnter()
{
	Layer::onEnter();
	log("Setting onEnter");
}

void Setting::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("Setting onEnterTransitionDidFinish");
	isEffect = true;
	//²¥·Å
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Synth.mp3", true);
}

void Setting::onExit()
{
	Layer::onExit();
	log("Setting onExit");
}

void Setting::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	log("Setting onExitTransitionDidStart");
}

void Setting::cleanup()
{
	Layer::cleanup();
	log("Setting cleanup");
	//Í£Ö¹
	//SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/Synth.mp3");
}
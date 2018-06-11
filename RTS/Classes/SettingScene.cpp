 #include "SettingScene.h"

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

    Sprite *bg = Sprite::create("background2.png");
    
    // position the label on the center of the screen
    bg->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height /2));
    this->addChild(bg);

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(50);

	//ÒôÐ§
    auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuSoundToggleCallback, this), 
												MenuItemFont::create("On"),
                                                MenuItemFont::create("Off"),
												NULL);
	soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(550,300 )));

    //ÒôÀÖ
    auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuMusicToggleCallback, this), 
												MenuItemFont::create("On"),
                                                MenuItemFont::create("Off"),
												NULL);
	musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(550, 180)));

    //Ok°´Å¥
	MenuItemFont*okMenuItem = MenuItemFont::create("OK", CC_CALLBACK_1(Setting::menuOkCallback, this));
	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(580, 410)));

	Menu* mu = Menu::create(soundToggleMenuItem, musicToggleMenuItem,okMenuItem, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu);

    return true;
}

void Setting::menuOkCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
	if (isEffect) {
		SimpleAudioEngine::getInstance()->playEffect("sound/Blip.wav");
	}
}

void Setting::menuSoundToggleCallback(Ref* pSender)
{
	auto soundToggleMenuItem = (MenuItemToggle*)pSender;
	log("soundToggleMenuItem %d", soundToggleMenuItem->getSelectedIndex());

	if (isEffect) {
		SimpleAudioEngine::getInstance()->playEffect("sound/Blip.wav");
	}

	if (soundToggleMenuItem->getSelectedIndex() == 1) {//Ñ¡ÖÐ×´Ì¬Off -> On
		isEffect = false;
	}
	else {
		isEffect = true;
		SimpleAudioEngine::getInstance()->playEffect("sound/Blip.wav");
	}
}


void Setting::menuMusicToggleCallback(Ref* pSender)
{
	auto musicToggleMenuItem = (MenuItemToggle*)pSender;
	log("musicToggleMenuItem %d", musicToggleMenuItem->getSelectedIndex());

	if (musicToggleMenuItem->getSelectedIndex() == 1) {//Ñ¡ÖÐ×´Ì¬Off -> On
		SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/Synth.mp3");
	}
	else {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Synth.mp3");
	}
	if (isEffect) {
		SimpleAudioEngine::getInstance()->playEffect("sound/Blip.wav");
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
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Synth.mp3", true);
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
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/Synth.mp3");
}
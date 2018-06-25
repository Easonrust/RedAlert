#include "InPutIPsence.h"
#include "extensions\cocos-ext.h"  

USING_NS_CC_EXT;
USING_NS_CC;
using namespace cocos2d::extension;
using namespace CocosDenshion;
string IP;

Scene* InputIP::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = InputIP::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

	// Print useful error message instead of segfaulting when files are not there.
	static void problemLoading(const char* filename)
	{
		printf("Error while loading: %s\n", filename);
		printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in InputIPScene.cpp\n");
	}
 
	// on "init" you need to initialize your instance
	bool InputIP::init()
	{
	//////////////////////////////
	// 1. super init first
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (!Layer::init())
	{
		return false;
	}

	Sprite *bg = Sprite::create("background.jpg");

	// position the label on the center of the screen
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);


	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(InputIP::menuCloseCallback, this));
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));

		// create menu, it's an autorelease object
		auto menu = Menu::create(closeItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 1);

		/////////////////////////////
		// 3. add your codes below...

		// add a label shows "Hello World"
		// create and initialize a label

		auto editbox1 = EditBox::create(Size(200, 35), Scale9Sprite::create("text.png"));
		editbox1->setAnchorPoint(Point(0, 0));
		editbox1->setPosition(Point(visibleSize.width *0.3, visibleSize.height*0.55));
		editbox1->setPlaceHolder("IP:");//占位字符  
		editbox1->setMaxLength(30);
		editbox1->setFontColor(Color3B::BLACK);//设置输入字体的颜色  
		editbox1->setTag(1);
		this->addChild(editbox1, 2);
		//兑换按钮

		auto Exchangebuttom = MenuItemImage::create("enterbutton.png", "enterbutton2.png");
		Exchangebuttom->setCallback([&, editbox1](Ref*obj) {

			//取得输入框里面的文字，输出到控制台
			IP = editbox1->getText();
			cout << "ip:"<<IP;
			if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
				SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
			}
			log("%s", editbox1->getText());
			auto sc = Select::createScene();
			Director::getInstance()->pushScene(sc);
			
		});
		Menu* mu = Menu::create(Exchangebuttom, NULL);
		mu->setPosition(Vec2(400, 260));
		this->addChild(mu);
		return true;
}

	void InputIP::menuCloseCallback(Ref* pSender)
	{
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
		}
		Director::getInstance()->popScene();
	}

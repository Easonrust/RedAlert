#include"button.h"
bool button::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	buttonlist = Sprite::create("buttonlist.png");//下方建筑菜单栏
	buttonlist->setPosition(Vec2(800, 30));
	buttonlist->setScale(7.3, 1);
	addChild(buttonlist, 0, BUTTONLISTTAG);
	minebutton = Sprite::create("minebutton.png");//矿厂按钮
	minebutton->setPosition(Vec2(100, 23));
	addChild(minebutton, 1, MINEBUTTONTAG);
	minebutton->setScale(0.2, 0.2);
	epowerbutton = Sprite::create("epowerbutton.png");//电厂按钮
	epowerbutton->setPosition(Vec2(200, 27));
	addChild(epowerbutton, 1, EPOWERBUTTONTAG);
	epowerbutton->setScale(0.15, 0.15);
	barrackbutton = Sprite::create("barrackbutton.png");//兵营按钮
	barrackbutton->setPosition(Vec2(300, 27));
	addChild(barrackbutton, 1, BARRACKBUTTONTAG);
	barrackbutton->setScale(0.1, 0.1);
	carincbutton = Sprite::create("carincbutton.png");//车厂按钮
	carincbutton->setPosition(Vec2(400, 27));
	addChild(carincbutton, 1, CARINCBUTTONTAG);
	carincbutton->setScale(0.1, 0.11);

	//调整视角用的按钮
	setupbutton = Sprite::create("setup.png");
	setupbutton->setPosition(Vec2(800, 875));
	addChild(setupbutton, 1, UPBUTTONTAG);
	setdownbutton = Sprite::create("setdown.png");
	setdownbutton->setPosition(Vec2(800, 25));
	addChild(setdownbutton, 1, DOWNBUTTONTAG);
	setleftbutton = Sprite::create("setleft.png");
	setleftbutton->setPosition(Vec2(25, 450));
	addChild(setleftbutton, 1, LEFTBUTTONTAG);
	setrightbutton = Sprite::create("setright.png");
	setrightbutton->setPosition(Vec2(1575, 450));
	addChild(setrightbutton, 1, RIGHTBUTTONTAG);


	//显示钱与电力
	moneypowerlist = Sprite::create("moneypowerlist.png");//右上钱和电力状态栏
	moneypowerlist->setPosition(Vec2(1450, 875));
	moneypowerlist->setScale(5, 2.5);
	addChild(moneypowerlist, 0, MONEYPOWERLISTTAG);
	money = 0;
	smoney = String::createWithFormat("%d", money);
	lblmoney = Label::createWithTTF(smoney->getCString(), "fonts/Marker Felt.ttf", 24);
	lblmoney->setColor(Color3B::YELLOW);
	lblmoney->setPosition(1380, 875);
	this->addChild(lblmoney, 1, MONEYTAG);
	moneypng = Sprite::create("money.png");
	moneypng->setScale(0.9, 0.9);
	moneypng->setPosition(1403, 875);
	this->addChild(moneypng, 1, MONEYPNG);
	power = 0;
	spower = String::createWithFormat("%d", power);
	lblpower = Label::createWithTTF(spower->getCString(), "fonts/Marker Felt.ttf", 24);
	lblpower->setColor(Color3B::BLUE);
	lblpower->setPosition(1500, 875);
	this->addChild(lblpower, 1, POWERTAG);
	powerpng = Sprite::create("power.png");
	powerpng->setScale(0.8, 0.8);
	powerpng->setPosition(1523, 875);
	this->addChild(powerpng, 1, POWERPNG);
	return true;
}
void button::onEnter() {
	Layer::onEnter();
	log("mouseTouchEvent onEnter");

	auto listener = EventListenerMouse::create();

	listener->onMouseDown = CC_CALLBACK_1(button::onMouseDown, this);
	listener->onMouseUp = CC_CALLBACK_1(button::onMouseUp, this);
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void button::onExit() {
	Layer::onExit();
	log("mouseTouchEvent onExit");
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}
bool button::isTap(cocos2d::EventMouse*em, cocos2d::Node*node)
{
	Vec2 location1 = em->getLocation();
	location1.y = 900 - location1.y;
	Vec2 locationInNode = node->convertToNodeSpace(location1);
	Size s = node->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.width);
	if (rect.containsPoint(locationInNode))
	{
		return true;
	}
	return false;
}
bool button::onMouseDown(Event*e)
{
	return true;
}
void button::onMouseUp(Event*e)
{
	EventMouse* em = (EventMouse*)e;
	auto minebuttontag = this->getChildByTag(MINEBUTTONTAG);
	auto upbuttontag = this->getChildByTag(UPBUTTONTAG);
	auto downbuttontag = this->getChildByTag(DOWNBUTTONTAG);
	auto leftbuttontag = this->getChildByTag(LEFTBUTTONTAG);
	auto rightbuttontag = this->getChildByTag(RIGHTBUTTONTAG);
	//auto location = em->getLocation();
	if (this->isTap(em, minebuttontag))
	{
		buildornot = 1;
	}
	else if (this->isTap(em, upbuttontag))
	{
		set = 1;
	}
	else if (this->isTap(em, downbuttontag))
	{
		set = 2;
	}
	else if (this->isTap(em, leftbuttontag))
	{
		set = 3;
	}
	else if (this->isTap(em, rightbuttontag))
	{
		set = 4;
	}
}
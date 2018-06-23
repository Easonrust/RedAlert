#include"button.h"
//各类按钮初始化
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
	epowerbutton = Sprite::create("epowerbutton.png");//电厂按钮
	epowerbutton->setPosition(Vec2(200, 27));
	addChild(epowerbutton, 1, EPOWERBUTTONTAG);
	barrackbutton = Sprite::create("barrackbutton.png");//兵营按钮
	barrackbutton->setPosition(Vec2(300, 27));
	addChild(barrackbutton, 1, BARRACKBUTTONTAG);
	carincbutton = Sprite::create("carincbutton.png");//车厂按钮
	carincbutton->setPosition(Vec2(400, 27));
	addChild(carincbutton, 1, CARINCBUTTONTAG);
	soldierbutton = Sprite::create("soldierbutton.png");//士兵按钮
	soldierbutton->setPosition(Vec2(500, 27));
	addChild(soldierbutton, 1, SOLDIERBUTTONTAG);
	robotbutton = Sprite::create("robotbutton.png");//军犬按钮
	robotbutton->setPosition(Vec2(600, 27));
	addChild(robotbutton, 1, ROBOTBUTTONTAG);
	tankbutton = Sprite::create("tankbutton.png");//坦克按钮
	tankbutton->setPosition(Vec2(700, 27));
	addChild(tankbutton, 1, TANKBUTTONTAG);
	//显示钱与电力
	moneypowerlist = Sprite::create("moneypowerlist.png");//右上钱和电力状态栏
	moneypowerlist->setPosition(Vec2(1450, 875));
	moneypowerlist->setScale(5, 2.5);
	addChild(moneypowerlist, 0, MONEYPOWERLISTTAG);
	money = 0;
	smoney = String::createWithFormat("%d", money);
	lblmoney = Label::createWithTTF(smoney->getCString(), "fonts/Marker Felt.ttf", 24);
	lblmoney->setColor(Color3B::YELLOW);
	lblmoney->setPosition(1370, 875);
	this->addChild(lblmoney, 1, MONEYTAG);
	moneypng = Sprite::create("money.png");
	moneypng->setScale(0.9, 0.9);
	moneypng->setPosition(1403, 875);
	this->addChild(moneypng, 1, MONEYPNG);
	power = 0;
	spower = String::createWithFormat("%d", power);
	lblpower = Label::createWithTTF(spower->getCString(), "fonts/Marker Felt.ttf", 24);
	lblpower->setColor(Color3B::BLUE);
	lblpower->setPosition(1460, 875);
	this->addChild(lblpower, 1, POWERTAG);
	powerpng = Sprite::create("power.png");
	powerpng->setScale(0.8, 0.8);
	powerpng->setPosition(1483, 875);
	this->addChild(powerpng, 1, POWERPNG);
	schedule(schedule_selector(button::scheduleMoneyPower), 0.1f);//调整金钱的函数
	schedule(schedule_selector(button::schedulebutton), 0.1f);//调整建筑能否建造（钱和电力够不够）
	return true;
}
//判断能否点到精灵图片上的函数,辅助作用
bool button::isTap(cocos2d::EventMouse*em, cocos2d::Node*node)
{
	Vec2 location1 = em->getLocation();
	location1.y = 900 - location1.y;
	Vec2 locationInNode = node->convertToNodeSpace(location1);
	Size s = node->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	if (rect.containsPoint(locationInNode))
	{
		return true;
	}
	return false;
}
//调整金钱
void button::scheduleMoneyPower(float delta)
{
	money += 50;
	this->removeChildByTag(MONEYTAG);
	smoney = String::createWithFormat("%d", money);
	lblmoney = Label::createWithTTF(smoney->getCString(), "fonts/Marker Felt.ttf", 24);
	lblmoney->setColor(Color3B::YELLOW);
	lblmoney->setPosition(1370, 875);
	this->addChild(lblmoney, 1, MONEYTAG);
	power += 1;
	this->removeChildByTag(POWERTAG);
	spower = String::createWithFormat("%d", power);
	lblpower = Label::createWithTTF(spower->getCString(), "fonts/Marker Felt.ttf", 24);
	lblpower->setColor(Color3B::YELLOW);
	lblpower->setPosition(1460, 875);
	this->addChild(lblpower, 1, POWERTAG);
}

//调整建筑能否建造（钱和电力够不够）
void button::schedulebutton(float delta)
{
	//barrack
	this->removeChildByTag(BARRACKBUTTONTAG);
	if (money < 1000)
	{
		barrackbutton = Sprite::create("barrackbuttoncannot.png");
	}
	else
	{
		barrackbutton = Sprite::create("barrackbutton.png");
	}
	barrackbutton->setPosition(Vec2(300, 27));
	addChild(barrackbutton, 1, BARRACKBUTTONTAG);
	//mine
	this->removeChildByTag(MINEBUTTONTAG);
	if (money < 900)
	{
		minebutton = Sprite::create("minebuttoncannot.png");
	}
	else
	{
		minebutton = Sprite::create("minebutton.png");
	}
	minebutton->setPosition(Vec2(100, 23));
	addChild(minebutton, 1, MINEBUTTONTAG);
	//epower
	this->removeChildByTag(EPOWERBUTTONTAG);
	if (money < 800)
	{
		epowerbutton = Sprite::create("epowerbuttoncannot.png");
	}
	else
	{
		epowerbutton = Sprite::create("epowerbutton.png");
	}
	epowerbutton->setPosition(Vec2(200, 27));
	addChild(epowerbutton, 1, EPOWERBUTTONTAG);
	//carinc
	this->removeChildByTag(CARINCBUTTONTAG);
	if (money < 700)
	{
		carincbutton = Sprite::create("carincbuttoncannot.png");
	}
	else
	{
		carincbutton = Sprite::create("carincbutton.png");
	}
	carincbutton->setPosition(Vec2(400, 27));
	addChild(carincbutton, 1, CARINCBUTTONTAG);
	//soldier
	this->removeChildByTag(SOLDIERBUTTONTAG);
	if (money <= 100)
	{
		soldierbutton = Sprite::create("soldierbuttoncannot.png");
	}
	else
	{
		soldierbutton = Sprite::create("soldierbutton.png");
	}
	soldierbutton->setPosition(Vec2(500, 27));
	addChild(soldierbutton, 1, SOLDIERBUTTONTAG);
	//tank
	this->removeChildByTag(TANKBUTTONTAG);
	if (money <= 500)
	{
		tankbutton = Sprite::create("tankbuttoncannot.png");
	}
	else
	{
		tankbutton = Sprite::create("tankbutton.png");
	}
	tankbutton->setPosition(Vec2(700, 27));
	addChild(tankbutton, 1, TANKBUTTONTAG);
	this->removeChildByTag(ROBOTBUTTONTAG);
	if (money <= 150)
	{
		robotbutton = Sprite::create("robotbuttoncannot.png");
	}
	else
	{
		robotbutton = Sprite::create("robotbutton.png");
	}
	robotbutton->setPosition(Vec2(600, 27));
	addChild(robotbutton, 1, ROBOTBUTTONTAG);
}
//
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
bool button::onMouseDown(Event*e)
{
	return true;
}

void button::onMouseUp(Event*e)
{
	EventMouse* em = (EventMouse*)e;
	auto minebuttontag = this->getChildByTag(MINEBUTTONTAG);
	auto barrackbuttontag = this->getChildByTag(BARRACKBUTTONTAG);
	auto epowerbuttontag = this->getChildByTag(EPOWERBUTTONTAG);
	auto carincbuttontag = this->getChildByTag(CARINCBUTTONTAG);
	auto soldierbuttontag = this->getChildByTag(SOLDIERBUTTONTAG);
	auto tankbuttontag = this->getChildByTag(TANKBUTTONTAG);
	auto robotbuttontag = this->getChildByTag(ROBOTBUTTONTAG);
	if (this->isTap(em, minebuttontag))
	{
		buildornot = 1;
		buildchoice = 1;
	}
	else if (this->isTap(em, barrackbuttontag))
	{
		buildornot = 1;
		buildchoice = 2;
	}
	else if (this->isTap(em, epowerbuttontag))
	{
		buildornot = 1;
		buildchoice = 3;
	}
	else if (this->isTap(em, carincbuttontag))
	{
		buildornot = 1;
		buildchoice = 4;
	}
	else if (this->isTap(em, soldierbuttontag))
	{
		buildornot = 2;
		buildchoice = 5;
	}
	else if (this->isTap(em, tankbuttontag))
	{
		buildornot = 2;
		buildchoice = 6;
	}
	else if (this->isTap(em, robotbuttontag))
	{
		buildornot = 2;
		buildchoice = 7;
	}
}
//购买建筑后更新金钱
void button::updatemoney(int buildchoice)
{
	if (buildchoice == 1 && money >= 900)
	{
		money -= 900;
	}
	else if (buildchoice == 2 && money >= 1000)
	{
		money -= 1000;
	}
	else if (buildchoice == 3 && money >= 800)
	{
		money -= 800;
	}
	else if (buildchoice == 4 && money >= 700)
	{
		money -= 700;
	}
	else if (buildchoice == 5 && money >= 100)
	{
		money -= 100;
	}
	else if (buildchoice == 6 && money >= 500)
	{
		money -= 500;
	}
	else if (buildchoice == 7 && money >= 200)
	{
		money -= 200;
	}
	this->removeChildByTag(MONEYTAG);
	smoney = String::createWithFormat("%d", money);
	lblmoney = Label::createWithTTF(smoney->getCString(), "fonts/Marker Felt.ttf", 24);
	lblmoney->setColor(Color3B::YELLOW);
	lblmoney->setPosition(1370, 875);
	this->addChild(lblmoney, 1, MONEYTAG);
}

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
	soldierbutton = Sprite::create("soldierbutton.png");//士兵按钮
	soldierbutton->setPosition(Vec2(500, 27));
	addChild(soldierbutton, 1,SOLDIERBUTTONTAG);
	//soldierbutton->setScale(0.1, 0.11);

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
	schedule(schedule_selector(button::scheduleMoneyPower),0.1f);//调整金钱的函数
	schedule(schedule_selector(button::schedulebutton), 0.1f);//调整建筑能否建造（钱和电力够不够）
	return true;
}

//调整金钱
void button::scheduleMoneyPower(float delta)
{
	money +=50 ;
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
		buildornot = 0;
	}
	else
	{
		barrackbutton = Sprite::create("barrackbutton.png");
	}
	barrackbutton->setPosition(Vec2(300, 27));
	barrackbutton->setScale(0.1, 0.1);
	addChild(barrackbutton, 1,BARRACKBUTTONTAG);
	//mine
	this->removeChildByTag(MINEBUTTONTAG);
	if (money < 1000)
	{
		minebutton = Sprite::create("minebuttoncannot.png");
		buildornot = 0;
	}
	else
	{
		minebutton = Sprite::create("minebutton.png");
	}
	minebutton->setPosition(Vec2(100, 23));
	minebutton->setScale(0.2, 0.2);
	addChild(minebutton, 1,MINEBUTTONTAG);
	//epower
	this->removeChildByTag(EPOWERBUTTONTAG);
	if (money < 1000)
	{
		epowerbutton = Sprite::create("epowerbuttoncannot.png");
		buildornot = 0;
	}
	else
	{
		epowerbutton = Sprite::create("epowerbutton.png");
	}
	epowerbutton->setPosition(Vec2(200, 27));
	epowerbutton->setScale(0.15, 0.15);
	addChild(epowerbutton, 1,EPOWERBUTTONTAG);
	//carinc
	this->removeChildByTag(CARINCBUTTONTAG);
	if (money < 1000)
	{
		carincbutton = Sprite::create("carincbuttoncannot.png");
		buildornot = 0;
	}
	else
	{
		carincbutton = Sprite::create("carincbutton.png");
	}
	carincbutton->setPosition(Vec2(400, 27));
	carincbutton->setScale(0.1, 0.1);
	addChild(carincbutton, 1, CARINCBUTTONTAG);
}

//购买建筑后更新金钱
void button::updatemoney(int buildchoice)
{
	switch (buildchoice)
	{
	case 1:
		money -= 1000;//矿厂钱数
		break;
	case 2:
		money -= 1000;//兵营钱数
		break;
	case 3:
		money -= 1000;//电厂钱数
		break;
	case 4:
		money -= 1000;//车厂钱数
		break;
	case 5:
		money -= 1000;//士兵钱数
		break;
	default:
		break;
	}
	this->removeChildByTag(MONEYTAG);
	smoney = String::createWithFormat("%d", money);
	lblmoney = Label::createWithTTF(smoney->getCString(), "fonts/Marker Felt.ttf", 24);
	lblmoney->setColor(Color3B::YELLOW);
	lblmoney->setPosition(1370, 875);
	this->addChild(lblmoney, 1, MONEYTAG);
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

//判断能否点到精灵图片上的函数
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
	auto barrackbuttontag = this->getChildByTag(BARRACKBUTTONTAG);
	auto epowerbuttontag = this->getChildByTag(EPOWERBUTTONTAG);
	auto carincbuttontag = this->getChildByTag(CARINCBUTTONTAG);
	auto soldierbuttontag = this->getChildByTag(SOLDIERBUTTONTAG);
	if (this->isTap(em, minebuttontag))
	{
		buildornot = 1;
		buildchoice = 1;
	}
	else if (this->isTap(em,barrackbuttontag))
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
}

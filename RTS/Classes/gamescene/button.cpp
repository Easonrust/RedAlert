#include"button.h"
#include"SimpleAudioEngine.h"
#include <iostream>
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
	auto msmoney = String::createWithFormat("2500");
	auto mlblmoney = Label::createWithTTF(msmoney->getCString(), "fonts/Marker Felt.ttf", 24);
	mlblmoney->setColor(Color3B::YELLOW);
	mlblmoney->setPosition(180, 23);
	this->addChild(mlblmoney, 1);
	auto mmoneypng = Sprite::create("money.png");
	mmoneypng->setScale(0.9, 0.9);
	mmoneypng->setPosition(220, 23);
	this->addChild(mmoneypng, 1);
	epowerbutton = Sprite::create("epowerbutton.png");//电厂按钮
	epowerbutton->setPosition(Vec2(300, 27));
	addChild(epowerbutton, 1, EPOWERBUTTONTAG);
	auto esmoney = String::createWithFormat("800");
	auto elblmoney = Label::createWithTTF(esmoney->getCString(), "fonts/Marker Felt.ttf", 24);
	elblmoney->setColor(Color3B::YELLOW);
	elblmoney->setPosition(380, 23);
	this->addChild(elblmoney, 1);
	auto emoneypng = Sprite::create("money.png");
	emoneypng->setScale(0.9, 0.9);
	emoneypng->setPosition(420, 23);
	this->addChild(emoneypng, 1);
	barrackbutton = Sprite::create("barrackbutton.png");//兵营按钮
	barrackbutton->setPosition(Vec2(500, 27));
	addChild(barrackbutton, 1, BARRACKBUTTONTAG);
	auto bsmoney = String::createWithFormat("1000");
	auto blblmoney = Label::createWithTTF(bsmoney->getCString(), "fonts/Marker Felt.ttf", 24);
	blblmoney->setColor(Color3B::YELLOW);
	blblmoney->setPosition(580, 23);
	this->addChild(blblmoney, 1);
	auto bmoneypng = Sprite::create("money.png");
	bmoneypng->setScale(0.9, 0.9);
	bmoneypng->setPosition(620, 23);
	this->addChild(bmoneypng, 1);
	carincbutton = Sprite::create("carincbutton.png");//车厂按钮
	carincbutton->setPosition(Vec2(700, 27));
	addChild(carincbutton, 1, CARINCBUTTONTAG);
	auto csmoney = String::createWithFormat("2000");
	auto clblmoney = Label::createWithTTF(csmoney->getCString(), "fonts/Marker Felt.ttf", 24);
	clblmoney->setColor(Color3B::YELLOW);
	clblmoney->setPosition(780, 23);
	this->addChild(clblmoney, 1);
	auto cmoneypng = Sprite::create("money.png");
	cmoneypng->setScale(0.9, 0.9);
	cmoneypng->setPosition(820, 23);
	this->addChild(cmoneypng, 1);
	soldierbutton = Sprite::create("soldierbutton.png");//士兵按钮
	soldierbutton->setPosition(Vec2(900, 27));
	addChild(soldierbutton, 1, SOLDIERBUTTONTAG);
	auto ssmoney = String::createWithFormat("100");
	auto slblmoney = Label::createWithTTF(ssmoney->getCString(), "fonts/Marker Felt.ttf", 24);
	slblmoney->setColor(Color3B::YELLOW);
	slblmoney->setPosition(980, 23);
	this->addChild(slblmoney, 1);
	auto smoneypng = Sprite::create("money.png");
	smoneypng->setScale(0.9, 0.9);
	smoneypng->setPosition(1020, 23);
	this->addChild(smoneypng, 1);
	robotbutton = Sprite::create("robotbutton.png");//军犬按钮
	robotbutton->setPosition(Vec2(1100, 27));
	addChild(robotbutton, 1, ROBOTBUTTONTAG);
	auto rsmoney = String::createWithFormat("300");
	auto rlblmoney = Label::createWithTTF(rsmoney->getCString(), "fonts/Marker Felt.ttf", 24);
	rlblmoney->setColor(Color3B::YELLOW);
	rlblmoney->setPosition(1180, 23);
	this->addChild(rlblmoney, 1);
	auto rmoneypng = Sprite::create("money.png");
	rmoneypng->setScale(0.9, 0.9);
	rmoneypng->setPosition(1220, 23);
	this->addChild(rmoneypng, 1);
	tankbutton = Sprite::create("tankbutton.png");//坦克按钮
	tankbutton->setPosition(Vec2(1300, 27));
	addChild(tankbutton, 1, TANKBUTTONTAG);
	auto tsmoney = String::createWithFormat("800");
	auto tlblmoney = Label::createWithTTF(tsmoney->getCString(), "fonts/Marker Felt.ttf", 24);
	tlblmoney->setColor(Color3B::YELLOW);
	tlblmoney->setPosition(1380, 23);
	this->addChild(tlblmoney, 1);
	auto tmoneypng = Sprite::create("money.png");
	tmoneypng->setScale(0.9, 0.9);
	tmoneypng->setPosition(1420, 23);
	this->addChild(tmoneypng, 1);
	wallbutton = Sprite::create("wallbutton.png");//围墙按钮
	wallbutton->setPosition(Vec2(1480, 27));
	addChild(wallbutton, 1, WALLBUTTONTAG);
	auto wsmoney = String::createWithFormat("400");
	auto wlblmoney = Label::createWithTTF(wsmoney->getCString(), "fonts/Marker Felt.ttf", 24);
	wlblmoney->setColor(Color3B::YELLOW);
	wlblmoney->setPosition(1540, 23);
	this->addChild(wlblmoney, 1);
	auto wmoneypng = Sprite::create("money.png");
	wmoneypng->setScale(0.9, 0.9);
	wmoneypng->setPosition(1580, 23);
	this->addChild(wmoneypng, 1);
	//显示钱与电力
	moneypowerlist = Sprite::create("moneypowerlist.png");//右上钱和电力状态栏
	moneypowerlist->setPosition(Vec2(1450, 875));
	moneypowerlist->setScale(5, 2.5);
	addChild(moneypowerlist, 0, MONEYPOWERLISTTAG);
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
	if (mine_num && power >= 0) {
		money = money + 10 * mine_num;
	}
	this->removeChildByTag(MONEYTAG);
	smoney = String::createWithFormat("%d", money);
	lblmoney = Label::createWithTTF(smoney->getCString(), "fonts/Marker Felt.ttf", 24);
	lblmoney->setColor(Color3B::YELLOW);
	lblmoney->setPosition(1370, 875);
	this->addChild(lblmoney, 1, MONEYTAG);
    
	if (enemy_mine_num && enemy_power >= 0) {
		enemy_money = enemy_money + 10 * enemy_mine_num;
	}
	this->removeChildByTag(POWERTAG);
	spower = String::createWithFormat("%d", power);
	lblpower = Label::createWithTTF(spower->getCString(), "fonts/Marker Felt.ttf", 24);
    if(power<0)lblpower->setColor(Color3B::RED);
	else lblpower->setColor(Color3B::YELLOW);
	lblpower->setPosition(1460, 875);
	this->addChild(lblpower, 1, POWERTAG);
}

//调整建筑能否建造（钱和电力够不够）
void button::schedulebutton(float delta)
{
	//barrack
	this->removeChildByTag(BARRACKBUTTONTAG);
	if (money < 1000 || !base_num || !epower_num||power<100)
	{
		barrackbutton = Sprite::create("barrackbuttoncannot.png");
	}
	else
	{
		barrackbutton = Sprite::create("barrackbutton.png");
	}
	barrackbutton->setPosition(Vec2(500, 27));
	addChild(barrackbutton, 1, BARRACKBUTTONTAG);
	//mine
	this->removeChildByTag(MINEBUTTONTAG);
	if (money < 2500 || !base_num || !epower_num|| power < 150)
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
	if (money < 800 || !base_num)
	{
		epowerbutton = Sprite::create("epowerbuttoncannot.png");
	}
	else
	{
		epowerbutton = Sprite::create("epowerbutton.png");
	}
	epowerbutton->setPosition(Vec2(300, 27));
	addChild(epowerbutton, 1, EPOWERBUTTONTAG);
	//carinc
	this->removeChildByTag(CARINCBUTTONTAG);
	if (money < 2000 || !base_num || !epower_num || !mine_num || !barrack_num)
	{
		carincbutton = Sprite::create("carincbuttoncannot.png");
	}
	else
	{
		carincbutton = Sprite::create("carincbutton.png");
	}
	carincbutton->setPosition(Vec2(700, 27));
	addChild(carincbutton, 1, CARINCBUTTONTAG);
	//soldier
	this->removeChildByTag(SOLDIERBUTTONTAG);
	if (money <100 ||!barrack_num)
	{
		soldierbutton = Sprite::create("soldierbuttoncannot.png");
	}
	else
	{
		soldierbutton = Sprite::create("soldierbutton.png");
	}
	soldierbutton->setPosition(Vec2(900, 27));
	addChild(soldierbutton, 1, SOLDIERBUTTONTAG);
	//tank
	this->removeChildByTag(TANKBUTTONTAG);
	if (money < 800 || !carinc_num)
	{
		tankbutton = Sprite::create("tankbuttoncannot.png");
	}
	else
	{
		tankbutton = Sprite::create("tankbutton.png");
	}
	tankbutton->setPosition(Vec2(1300, 27));
	addChild(tankbutton, 1, TANKBUTTONTAG);
	this->removeChildByTag(ROBOTBUTTONTAG);
	if (money <300 || !carinc_num)
	{
		robotbutton = Sprite::create("robotbuttoncannot.png");
	}
	else
	{
		robotbutton = Sprite::create("robotbutton.png");
	}
	robotbutton->setPosition(Vec2(1100, 27));
	addChild(robotbutton, 1, ROBOTBUTTONTAG);
	this->removeChildByTag(WALLBUTTONTAG);
	if (money <= 400 ||!base_num)
	{
		wallbutton = Sprite::create("wallbuttoncannot.png");
	}
	else
	{
		wallbutton = Sprite::create("wallbutton.png");
	}
	wallbutton->setPosition(Vec2(1480, 27));
	addChild(wallbutton, 1,WALLBUTTONTAG);
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
	auto wallbuttontag = this->getChildByTag(WALLBUTTONTAG);
	if (this->isTap(em, wallbuttontag))
	{
		if (money >= 400 && base_num )
		{
			buildornot = 1;
			buildchoice = 8;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/buttonerror.wav");
		}
	}
	if (this->isTap(em, minebuttontag))
	{
		if (money >= 2500 && power >= 150 && base_num &&epower_num)
		{
			buildornot = 1;
			buildchoice = 1;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/buttonerror.wav");
		}
	}
	else if (this->isTap(em, barrackbuttontag))
	{
		if (money >= 1000 && power >= 100 && base_num && epower_num)
		{
			buildornot = 1;
			buildchoice = 2;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/buttonerror.wav");
		}
	}
	else if (this->isTap(em, epowerbuttontag))
	{
		if (money >= 800 && base_num)
		{
			buildornot = 1;
			buildchoice = 3;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/buttonerror.wav");
		}
	}
	else if (this->isTap(em, carincbuttontag))
	{
		if (money >= 2000 && power >= 120 && base_num && epower_num && barrack_num &&mine_num)
		{
			buildornot = 1;
			buildchoice = 4;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/buttonerror.wav");
		}
	}
	else if (this->isTap(em, soldierbuttontag))
	{
		if (barrack_num &&money >= 100)
		{
			buildornot = 2;
			buildchoice = 5;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/soldiersound.mp3");
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/buttonerror.wav");
		}
	}
	else if (this->isTap(em, tankbuttontag))
	{
		if (carinc_num && money >= 800)
		{
			buildornot = 2;
			buildchoice = 6;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/tanksound.wav");
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/buttonerror.wav");
		}
	}
	else if (this->isTap(em, robotbuttontag))
	{
		if (carinc_num &&money >= 300)
		{
			buildornot = 2;
			buildchoice = 7;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/robotsound.wav");
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/buttonerror.wav");
		}
	}
}
//购买建筑后更新金钱
void button::updatemoney(int buildchoice)
{
	if (buildchoice == 1 && money >= 2500&&power>=150)
	{
		money -= 2500;
        mine_num = mine_num+1;
        power = power - 150;
	}
	else if (buildchoice == 2 && money >= 1000&&power>=100)
	{
		money -= 1000;
        barrack_num = barrack_num+1;
        power = power - 100;
	}
	else if (buildchoice == 3 && money >= 800)
	{
		money -= 800;
        epower_num = epower_num+1;
        power = power + 250;
	}
	else if (buildchoice == 4 && money >= 2000&&power>=120)
	{
		money -= 2000;
        carinc_num = carinc_num+1;
        power = power - 120;
	}
	else if (buildchoice == 5 && money >= 100)
	{
		money -= 100;
	}
	else if (buildchoice == 6 && money >= 800)
	{
		money -= 800;
	}
	else if (buildchoice == 7 && money >= 300)
	{
		money -= 300;
	}
	else if (buildchoice == 8 && money >= 400)
	{
		money -= 400;
	}
	this->removeChildByTag(MONEYTAG);
	smoney = String::createWithFormat("%d", money);
	lblmoney = Label::createWithTTF(smoney->getCString(), "fonts/Marker Felt.ttf", 24);
	lblmoney->setColor(Color3B::YELLOW);
	lblmoney->setPosition(1370, 875);
	this->addChild(lblmoney, 1, MONEYTAG);
}

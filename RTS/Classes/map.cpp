#include"map.h"
#include"button.h"
#include "building.h"
#include <string>
#include <iostream>
bool mymap::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animate.plist");
	this->setAnchorPoint(Vec2(0, 0));
	originmap = this->getPosition();
	repair = Vec2(0, 0);//移动地图后，在地图上建造精灵时坐标的修正量
	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap, 0, MAPTAG);
	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(false);
	auto base = building::createWithBuildingType(Base);
	buildingnum += 1;//将地图上目前的建筑总数加一
	base->setPosition(Vec2(300, 300));
	building::add_blood_bar(base);
	addChild(base);
	addChild(base->blood);
	addChild(base->progress);
	enemy_buildings.pushBack(base);//将基地添加到建筑物容器中

	schedule(schedule_selector(mymap::moveBlood), 0.1f);  //刷新函数，每隔0.1秒
	schedule(schedule_selector(mymap::protectmap), 0);
	schedule(schedule_selector(mymap::iscollide), 0);
	schedule(schedule_selector(mymap::scheduleBlood_enemy), 0.1f);
	schedule(schedule_selector(mymap::scheduleBlood_mine), 0.1f);
	schedule(schedule_selector(mymap::soldierattack), 0.1f);
	return true;
}
bool mymap::isTap(cocos2d::Vec2 location, cocos2d::Node*node)//判断是否点中精灵的函数,辅助
{
	Vec2 locationInNode = node->convertToNodeSpace(location);
	Size s = node->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	if (rect.containsPoint(locationInNode))
	{
		return true;
	}
	return false;
}
void mymap::ruins()
{
	for (int i = 0; i < enemy_buildings.size(); ++i)
	{
		if (enemy_buildings.at(i)->progress->getPercentage() <= 0)
		{
			enemy_buildings.at(i)->stopAllActions();
			this->removeChild(enemy_buildings.at(i));
		}
	}
	for (int i = 0; i < enemy_soldiers.size(); ++i)
	{
		if (enemy_soldiers.at(i)->progress->getPercentage() <= 0)
		{
			enemy_soldiers.at(i)->stopAllActions();
			this->removeChild(enemy_soldiers.at(i));
		}
	}
	for (int i = 0; i < soldiers.size(); ++i)
	{
		if (soldiers.at(i)->progress->getPercentage() <= 0)
		{
			soldiers.at(i)->stopAllActions();
			this->removeChild(soldiers.at(i));
		}
	}
	for (int i = 0; i < buildings.size(); ++i)
	{
		if (buildings.at(i)->progress->getPercentage() <= 0)
		{
			buildings.at(i)->stopAllActions();
			this->removeChild(buildings.at(i));
		}
	}
}
void mymap::soldierattack(float delta)
{
	for (int i = 0; i < soldiers.size(); ++i)
	{
		if (soldiers.at(i)->atk == 1 && soldiers.at(i)->b_enemy&&soldiers.at(i)->getPosition().getDistance(soldiers.at(i)->b_enemy->getPosition()) <= 100)
		{
			Vec2 location = soldiers.at(i)->getPosition();
			soldiers.at(i)->setVisible(false);
			if (soldiers.at(i)->sprite == nullptr)
			{
				soldiers.at(i)->sprite = Sprite::create("a2.png");
				soldiers.at(i)->sprite->setPosition(location);
				addChild(soldiers.at(i)->sprite);
				if (soldiers.at(i)->getPosition().x < soldiers.at(i)->b_enemy->getPosition().x)
				{
					soldiers.at(i)->sprite->runAction(FlipX::create(true));
				}
				else if (!(soldiers.at(i)->getPosition().x < soldiers.at(i)->b_enemy->getPosition().x))
				{
					soldiers.at(i)->sprite->runAction(FlipX::create(false));
				}
			}
		}
		else
		{
			if (soldiers.at(i)->sprite)
			{
				this->removeChild(soldiers.at(i)->sprite);
				soldiers.at(i)->sprite = nullptr;
			}
			soldiers.at(i)->setVisible(true);
		}
	}
}
//血量刷新函数
void mymap::moveBlood(float delta) {
	for (int i = 0; i < soldiers.size(); ++i)
	{
		if (soldiers.at(i)->selected == 1)
		{
			soldiers.at(i)->blood->setPosition(soldiers.at(i)->getPositionX(), soldiers.at(i)->getPositionY() + 30);
			soldiers.at(i)->progress->setPosition(soldiers.at(i)->getPositionX(), soldiers.at(i)->getPositionY() + 30);
		}
	}

}
void mymap::scheduleBlood_enemy(float delta) {
	for (int i = 0; i < soldiers.size(); i++) {
		//敌方士兵
		if (soldiers.at(i)->s_enemy != nullptr) {
			if (soldiers.at(i)->getPosition().getDistance(soldiers.at(i)->s_enemy->getPosition()) <= 100) {
				soldiers.at(i)->stopAllActions();
				if (soldiers.at(i)->getPosition().x < soldiers.at(i)->s_enemy->getPosition().x)
				{
					soldiers.at(i)->runAction(FlipX::create(true));
				}
				else if (!(soldiers.at(i)->getPosition().x < soldiers.at(i)->s_enemy->getPosition().x))
				{
					soldiers.at(i)->runAction(FlipX::create(false));
				}
				if (soldiers.at(i)->s_enemy->progress->getPercentage() > 0)
				{
					int prehealth = soldiers.at(i)->s_enemy->health;
					int nowhealth = prehealth - soldiers.at(i)->atk;
					soldiers.at(i)->s_enemy->health = nowhealth;
					soldiers.at(i)->s_enemy->progress->setPercentage((nowhealth / soldiers.at(i)->s_enemy->originhealth) * 100);
					if (soldiers.at(i)->s_enemy->progress->getPercentage() <= 0)
					{
						this->removeChild(soldiers.at(i)->s_enemy->progress);
						this->removeChild(soldiers.at(i)->s_enemy->blood);
						if (soldiers.at(i)->s_enemy->atk == 100 || soldiers.at(i)->s_enemy->atk == 200)
						{
							Animation* animation = Animation::create();
							for (int i = 1; i <= 11; i++)
							{
								__String *frameName = __String::createWithFormat("z%d.png", i);
								log("frameName = %s", frameName->getCString());
								SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
								animation->addSpriteFrame(spriteFrame);
							}
							animation->setDelayPerUnit(0.1f);           //设置两个帧播放时间
							animation->setRestoreOriginalFrame(false);    //动画执行后还原初始状态

							FiniteTimeAction* action1 = Animate::create(animation);
							FiniteTimeAction* action2 = CallFunc::create(CC_CALLBACK_0(mymap::ruins, this));
							ActionInterval*seq = Sequence::create(action1, action2, NULL);
							soldiers.at(i)->s_enemy->runAction(Sequence::create(seq, NULL));
							soldiers.at(i)->stopAllActions();
						}
						else
						{
							this->removeChild(soldiers.at(i)->s_enemy);
						}
						soldiers.at(i)->s_enemy = nullptr;
						//soldiers.at(i)->isattack = 0;
						soldiers.at(i)->stopAllActions();

						soldiers.at(i)->s_enemy = nullptr;
						soldiers.at(i)->isattack = 0;
					}
				}
				else
				{
					soldiers.at(i)->s_enemy = nullptr;
					soldiers.at(i)->isattack = 0;
				}
			}
			else {
				Soldier::run(soldiers, soldiers.at(i)->s_enemy->getPosition());
			}
		}

		//地方建筑
		if (soldiers.at(i)->b_enemy != nullptr) {
			if (soldiers.at(i)->getPosition().getDistance(soldiers.at(i)->b_enemy->getPosition()) <= 100) {
				soldiers.at(i)->stopAllActions();
				if (soldiers.at(i)->getPosition().x < soldiers.at(i)->b_enemy->getPosition().x)
				{
					soldiers.at(i)->runAction(FlipX::create(true));
				}
				if (!(soldiers.at(i)->getPosition().x < soldiers.at(i)->b_enemy->getPosition().x))
				{
					soldiers.at(i)->runAction(FlipX::create(false));
				}
				if (soldiers.at(i)->b_enemy->progress->getPercentage() > 0)
				{

					int prehealth = soldiers.at(i)->b_enemy->building_health;
					int nowhealth = prehealth - soldiers.at(i)->atk;
					soldiers.at(i)->b_enemy->building_health = nowhealth;
					soldiers.at(i)->b_enemy->progress->setPercentage(nowhealth / soldiers.at(i)->b_enemy->originhealth * 100);

					if (soldiers.at(i)->b_enemy->progress->getPercentage() <= 0)
					{
						//Vec2 loc = soldiers.at(i)->b_enemy->getPosition();
						this->removeChild(soldiers.at(i)->b_enemy->progress);
						this->removeChild(soldiers.at(i)->b_enemy->blood);
						//this->removeChild(soldiers.at(i)->b_enemy);
						//soldiers.at(i)->b_enemy = nullptr;
						Animation* animation = Animation::create();
						for (int i = 1; i <= 10; i++)
						{
							__String *frameName = __String::createWithFormat("z%d.png", i);
							log("frameName = %s", frameName->getCString());
							SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
							animation->addSpriteFrame(spriteFrame);
						}
						animation->setDelayPerUnit(0.1f);           //设置两个帧播放时间
						animation->setRestoreOriginalFrame(false);    //动画执行后还原初始状态

						FiniteTimeAction* action1 = Animate::create(animation);
						FiniteTimeAction* action2 = CallFunc::create(CC_CALLBACK_0(mymap::ruins, this));
						ActionInterval*seq = Sequence::create(action1, action2, NULL);
						soldiers.at(i)->b_enemy->runAction(Sequence::create(seq, NULL));
						soldiers.at(i)->stopAllActions();
					}
				}
				else
				{

					soldiers.at(i)->b_enemy = nullptr;
					soldiers.at(i)->isattack = 0;
				}
			}
			else {
				auto enemy = soldiers.at(i)->b_enemy;
				Soldier::run(soldiers, soldiers.at(i)->b_enemy->getPosition());
				soldiers.at(i)->b_enemy = enemy;

			}
		}
	}
}
void mymap::scheduleBlood_mine(float delta) {
	for (int i = 0; i < enemy_soldiers.size(); i++) {
		//敌方士兵
		if (enemy_soldiers.at(i)->s_enemy != nullptr) {
			if (enemy_soldiers.at(i)->getPosition().getDistance(enemy_soldiers.at(i)->s_enemy->getPosition()) <= 100) {
				enemy_soldiers.at(i)->stopAllActions();
				if (enemy_soldiers.at(i)->getPosition().x < enemy_soldiers.at(i)->s_enemy->getPosition().x)
				{
					enemy_soldiers.at(i)->runAction(FlipX::create(true));
				}
				else if (!(enemy_soldiers.at(i)->getPosition().x < enemy_soldiers.at(i)->s_enemy->getPosition().x))
				{
					enemy_soldiers.at(i)->runAction(FlipX::create(false));
				}
				if (enemy_soldiers.at(i)->s_enemy->progress->getPercentage() > 0)
				{
					int prehealth = enemy_soldiers.at(i)->s_enemy->health;
					int nowhealth = prehealth - enemy_soldiers.at(i)->atk;
					enemy_soldiers.at(i)->s_enemy->health = nowhealth;
					enemy_soldiers.at(i)->s_enemy->progress->setPercentage((nowhealth / enemy_soldiers.at(i)->s_enemy->originhealth) * 100);
					if (enemy_soldiers.at(i)->s_enemy->progress->getPercentage() <= 0)
					{
						this->removeChild(enemy_soldiers.at(i)->s_enemy->progress);
						this->removeChild(enemy_soldiers.at(i)->s_enemy->blood);
						if (enemy_soldiers.at(i)->s_enemy->atk == 100 || enemy_soldiers.at(i)->s_enemy->atk == 200)
						{
							Animation* animation = Animation::create();
							for (int i = 1; i <= 10; i++)
							{
								__String *frameName = __String::createWithFormat("z%d.png", i);
								log("frameName = %s", frameName->getCString());
								SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
								animation->addSpriteFrame(spriteFrame);
							}
							animation->setDelayPerUnit(0.1f);           //设置两个帧播放时间
							animation->setRestoreOriginalFrame(false);    //动画执行后还原初始状态

							FiniteTimeAction* action1 = Animate::create(animation);
							FiniteTimeAction* action2 = CallFunc::create(CC_CALLBACK_0(mymap::ruins, this));
							ActionInterval*seq = Sequence::create(action1, action2, NULL);
							enemy_soldiers.at(i)->s_enemy->runAction(Sequence::create(seq, NULL));
							enemy_soldiers.at(i)->stopAllActions();
						}
						else
						{
							this->removeChild(enemy_soldiers.at(i)->s_enemy);
						}
						enemy_soldiers.at(i)->s_enemy = nullptr;
						//soldiers.at(i)->isattack = 0;
						enemy_soldiers.at(i)->stopAllActions();

						enemy_soldiers.at(i)->s_enemy = nullptr;
						enemy_soldiers.at(i)->isattack = 0;
					}
				}
				else
				{
					enemy_soldiers.at(i)->s_enemy = nullptr;
					enemy_soldiers.at(i)->isattack = 0;
				}
			}
			else {
				Soldier::run(soldiers, enemy_soldiers.at(i)->s_enemy->getPosition());
			}
		}

		//地方建筑
		if (enemy_soldiers.at(i)->b_enemy != nullptr) {
			if (enemy_soldiers.at(i)->getPosition().getDistance(enemy_soldiers.at(i)->b_enemy->getPosition()) <= 100) {
				enemy_soldiers.at(i)->stopAllActions();
				if (enemy_soldiers.at(i)->getPosition().x < enemy_soldiers.at(i)->b_enemy->getPosition().x)
				{
					enemy_soldiers.at(i)->runAction(FlipX::create(true));
				}
				if (!(enemy_soldiers.at(i)->getPosition().x < enemy_soldiers.at(i)->b_enemy->getPosition().x))
				{
					enemy_soldiers.at(i)->runAction(FlipX::create(false));
				}
				if (enemy_soldiers.at(i)->b_enemy->progress->getPercentage() > 0)
				{

					int prehealth = soldiers.at(i)->b_enemy->building_health;
					int nowhealth = prehealth - soldiers.at(i)->atk;
					enemy_soldiers.at(i)->b_enemy->building_health = nowhealth;
					enemy_soldiers.at(i)->b_enemy->progress->setPercentage(nowhealth / enemy_soldiers.at(i)->b_enemy->originhealth * 100);

					if (enemy_soldiers.at(i)->b_enemy->progress->getPercentage() <= 0)
					{

						this->removeChild(enemy_soldiers.at(i)->b_enemy->progress);
						this->removeChild(enemy_soldiers.at(i)->b_enemy->blood);
						this->removeChild(soldiers.at(i)->b_enemy);
						Animation* animation = Animation::create();
						for (int i = 1; i <= 10; i++)
						{
							__String *frameName = __String::createWithFormat("z%d.png", i);
							log("frameName = %s", frameName->getCString());
							SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
							animation->addSpriteFrame(spriteFrame);
						}
						animation->setDelayPerUnit(0.1f);           //设置两个帧播放时间
						animation->setRestoreOriginalFrame(false);    //动画执行后还原初始状态

						FiniteTimeAction* action1 = Animate::create(animation);
						FiniteTimeAction* action2 = CallFunc::create(CC_CALLBACK_0(mymap::ruins, this));
						ActionInterval*seq = Sequence::create(action1, action2, NULL);
						enemy_soldiers.at(i)->b_enemy->runAction(Sequence::create(seq, NULL));
						enemy_soldiers.at(i)->stopAllActions();
					}
				}
				else
				{

					enemy_soldiers.at(i)->b_enemy = nullptr;
					enemy_soldiers.at(i)->isattack = 0;
				}
			}
			else {
				auto enemy = enemy_soldiers.at(i)->b_enemy;
				Soldier::run(enemy_soldiers, enemy_soldiers.at(i)->b_enemy->getPosition());
				enemy_soldiers.at(i)->b_enemy = enemy;

			}
		}
	}
}
void mymap::onEnter() {
	Layer::onEnter();
	log("mouseTouchEvent onEnter");

	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [this](Event *e) {
		EventMouse* em = (EventMouse*)e;
		auto location = em->getLocation();
		location = Director::getInstance()->convertToGL(location);
		mouse_down = location + repair;
	};
	listener->onMouseMove = [this](Event *e) {
		EventMouse* em = (EventMouse*)e;
		auto location = em->getLocation();
		location.y = 900 - location.y;
		pos1 = this->getPosition();
		auto tilesize = _tileMap->getTileSize();
		auto visize = Director::getInstance()->getVisibleSize();
		if (location.y >= 880 && pos1.y > -700)
		{
			Action*actionup = this->runAction(MoveTo::create((pos1.y + 700) / 10, Vec2(pos1.x, -700)));
			actionup->setTag(1);
		}
		if (location.y <= 20 && pos1.y < 0)
		{
			//this->stopAllActions();
			Action*actiondown = this->runAction(MoveTo::create(-pos1.y / 10, Vec2(pos1.x, 0)));
			actiondown->setTag(2);
		}
		else if (location.x <= 20 && pos1.x < 0)
		{
			Action*actionleft = this->runAction(MoveTo::create(-pos1.x / 10, Vec2(0, pos1.y)));
			actionleft->setTag(3);
		}
		else if (location.x >= 1580 && pos1.x > -1600)
		{
			Action*actionright = this->runAction(MoveTo::create((pos1.x + 1600) / 10, Vec2(-1600, pos1.y)));
			actionright->setTag(4);
		}
		pos1 = this->getPosition();
		if (location.y < 850)
		{
			this->stopActionByTag(1);
			repair = originmap - pos1;
		}
		if (location.y > 20)
		{
			this->stopActionByTag(2);
			repair = originmap - pos1;
		}
		if (location.x > 50)
		{
			this->stopActionByTag(3);
			repair = originmap - pos1;
		}
		if (location.x < 1550)
		{
			this->stopActionByTag(4);
			repair = originmap - pos1;
		}
	};
	listener->onMouseUp = [this](Event *e) {

		EventMouse* em = (EventMouse*)e;
		std::string str = " ";
		str += to_string(static_cast<int>(em->getMouseButton()
			));
		if (str == " 1") {
			Soldier::clear(soldiers);
		}
		auto location = em->getLocation();
		location = Director::getInstance()->convertToGL(location);//将鼠标的坐标转换为世界坐标
																  //基本创建建筑的事件
		mouse_up = location + repair;
		Soldier::judge_selected(soldiers, mouse_down, mouse_up);
		if (mouse_up == mouse_down && !buttonlayer->buildornot && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(SOLDIERBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(CARINCBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(MINEBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(EPOWERBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(BARRACKBUTTONTAG))))
		{
			if (tapenemy(mouse_up, enemy_buildings, enemy_soldiers) == 0)
			{
				for (int i = 0; i < soldiers.size(); ++i)
				{
					if (soldiers.at(i)->selected == 1)
					{
						soldiers.at(i)->s_enemy = nullptr;
						soldiers.at(i)->b_enemy = nullptr;
					}
				}
				Soldier::run(soldiers, mouse_up);
			}
		}
		for (int i = 0; i < enemy_soldiers.size(); i++) {
			if (isTap(mouse_up - repair, enemy_soldiers.at(i))) {
				Soldier::attacksoldier(soldiers, enemy_soldiers, location);
			}
		}
		for (int i = 0; i < enemy_buildings.size(); i++) {
			if (isTap(mouse_up - repair, enemy_buildings.at(i))) {
				Soldier::attackbuilding(soldiers, enemy_buildings, location);
				break;
			}
		}
		if (buttonlayer->buildornot == 1 && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(SOLDIERBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(CARINCBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(MINEBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(EPOWERBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(BARRACKBUTTONTAG))))
		{
			Vec2 position = location + repair;//修正量起作用了
			building* Building = NULL;
			if (buttonlayer->buildchoice == 1 && buttonlayer->money >= 900) {
				Building = building::createWithBuildingType(Mine);
				moneyenough = true;
			}
			else if (buttonlayer->buildchoice == 2 && buttonlayer->money >= 1000) {
				Building = building::createWithBuildingType(Barrack);
				moneyenough = true;
				barrackpos = position;
			}
			else if (buttonlayer->buildchoice == 3 && buttonlayer->money >= 800) {
				Building = building::createWithBuildingType(Epower);
				moneyenough = true;
			}
			else if (buttonlayer->buildchoice == 4 && buttonlayer->money >= 700) {
				Building = building::createWithBuildingType(Carinc);
				moneyenough = true;
				carincpos = position;
			}
			if (moneyenough == true)
			{
				buildingnum += 1;//将地图上建筑总数加一
				Building->setPosition(position);
				building::add_blood_bar(Building);
				enemy_buildings.pushBack(Building);
				addChild(Building);
				addChild(Building->blood);
				addChild(Building->progress);
				//将建筑物血条添加到容器中
				buttonlayer->updatemoney(buttonlayer->buildchoice);//购买后更新钱数更新
				char name = 0;
				switch (buttonlayer->buildchoice)
				{
				case 1:
					name = 'm';
					break;
				case 2:
					name = 'b';
					break;
				case 3:
					name = 'e';
					break;
				case 4:
					name = 'c';
					break;
				default:
					break;
				}
				Animation* animation = Animation::create();
				for (int i = 1; i <= 4; i++)
				{
					__String *frameName = __String::createWithFormat("%c%d.png", name, i);
					log("frameName = %s", frameName->getCString());
					SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
					animation->addSpriteFrame(spriteFrame);
				}
				animation->setDelayPerUnit(0.3f);           //设置两个帧播放时间
				animation->setRestoreOriginalFrame(false);    //动画执行后还原初始状态

				Animate* action = Animate::create(animation);
				Building->runAction(action);
			}
			buttonlayer->buildornot = false;//将要不要建建筑设为false
			buttonlayer->buildchoice = 0;
		}
		else if (buttonlayer->buildornot == 2)
		{
			if (barrackpos != Vec2(0, 0) && buttonlayer->buildchoice == 5 && buttonlayer->money >= 100)
			{
				soldiernum += 1;
				auto bing = Soldier::createwithsoldiertype(human);
				bing->setPosition(barrackpos);
				Soldier::add_bloodbar(bing, repair);
				addChild(bing);
				addChild(bing->blood);
				addChild(bing->progress);
				soldiers.pushBack(bing);
			}
			if (carincpos != Vec2(0, 0) && buttonlayer->buildchoice == 6 && buttonlayer->money >= 500)
			{
				soldiernum += 1;
				auto bing = Soldier::createwithsoldiertype(tank);
				bing->setPosition(carincpos);
				Soldier::add_bloodbar(bing, repair);
				addChild(bing);
				addChild(bing->blood);
				addChild(bing->progress);
				soldiers.pushBack(bing);
			}
			if (carincpos != Vec2(0, 0) && buttonlayer->buildchoice == 7 && buttonlayer->money >= 200)
			{
				soldiernum += 1;
				auto bing = Soldier::createwithsoldiertype(robot);
				bing->setPosition(carincpos);
				Soldier::add_bloodbar(bing, repair);
				addChild(bing);
				addChild(bing->blood);
				addChild(bing->progress);
				soldiers.pushBack(bing);
			}


			buttonlayer->buildornot = false;
		}


	};

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void mymap::onExit() {
	Layer::onExit();
	log("mouseTouchEvent onExit");
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}
void mymap::protectmap(float delta)
{

	pos1 = this->getPosition();
	//log("%f", pos1.y);
	log("%f", pos1.x);
	if (pos1.y < -700)
	{
		this->stopActionByTag(1);
		this->setPositionY(-700);
	}
	if (pos1.y > 0)
	{
		this->stopActionByTag(2);
		this->setPositionY(0);
	}
	if (pos1.x < -1600)
	{
		this->stopActionByTag(4);
		this->setPositionX(-1600);
	}
	if (pos1.x > 0)
	{
		this->stopActionByTag(3);
		this->setPositionX(0);
	}
	pos1 = this->getPosition();
	repair = originmap - pos1;
}


//检测该地点能否建造建筑（不与其他建筑重叠）有bug。。。。没有使用物理引擎，在移动地图后就失效了，唉。。。
bool mymap::canbuild(Vec2 location)
{
	if (buildingnum == 0)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < buildings.size(); ++i)
		{
			Vec2 otherlocation = buildings.at(i)->getPosition();
			float distance = (location).getDistance(otherlocation + repair);
			if (distance < 100)
			{
				return false;
			}
		}
		return true;
	}
}
Vec2 mymap::tileCoordFromPosition(cocos2d::Vec2 position)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	int x = static_cast<int>(((position.x - origin.x)
		/ (_tileMap->getTileSize().width / CC_CONTENT_SCALE_FACTOR())));
	float pointHeight = _tileMap->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
	int y = static_cast<int>(((_tileMap->getMapSize().height * pointHeight - position.y) / pointHeight));

	return Vec2(x, y);
}

bool mymap::collide(Vec2 pos)
{
	Vec2 tileCoord = this->tileCoordFromPosition(pos);
	//获得瓦片的GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();

		if (collision == "true") { //碰撞检测成功
			return true;
		}
	}
	return false;
}
void mymap::iscollide(float delta) {
	for (int i = 0; i < soldiers.size(); ++i)
	{
		Vec2 pos = soldiers.at(i)->getPosition();
		if (collide(pos + Vec2(0, 1)))
		{
			soldiers.at(i)->stopAllActions();
			soldiers.at(i)->setPosition(pos - Vec2(0, 1));
		}
		else if (collide(pos + Vec2(1, 0)))
		{
			soldiers.at(i)->stopAllActions();
			soldiers.at(i)->setPosition(pos - Vec2(1, 0));
		}
		else if (collide(pos - Vec2(0, 1)))
		{
			soldiers.at(i)->stopAllActions();
			soldiers.at(i)->setPosition(pos + Vec2(0, 1));

		}
		else if (collide(pos - Vec2(1, 0)))
		{
			soldiers.at(i)->stopAllActions();
			soldiers.at(i)->setPosition(pos + Vec2(1, 0));
		}
	}
}
bool mymap::tapenemy(Vec2 location, Vector<building*>enemy_buildings, Vector<Soldier*>enemy_soldiers)
{
	bool tap = 0;
	for (int i = 0; i < enemy_soldiers.size(); i++) {
		if (Soldier::isTap(location, enemy_soldiers.at(i))) {
			tap = 1;
			break;
		}
	}
	for (int i = 0; i < enemy_buildings.size(); i++) {
		if (Soldier::isTap(location, enemy_buildings.at(i))) {
			tap = 1;
			break;
		}
	}
	return tap;
}

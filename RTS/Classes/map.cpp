#include"map.h"
#include"button.h"
#include "building.h"
#include <string>
#include <iostream>
#include "client.h"
float ourcopy[7] = { 0 };
extern float coordinate[7];
extern bool connectornot;
extern char camp[1];
bool mymap::init()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/Lose.mp3");
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//




	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animate.plist");
	this->setAnchorPoint(Vec2(0, 0));
	originmap = this->getPosition();
	repair = Vec2(0, 0);//移动地图后，在地图上建造精灵时坐标的修正量
	_tileMap = TMXTiledMap::create("map/Map1.tmx");
	addChild(_tileMap, 0, MAPTAG);
	auto base1 = building::createWithBuildingType(Base);
	base1->setPosition(Vec2(400, 300));
	building::add_blood_bar(base1);
	addChild(base1);
	addChild(base1->blood);
	addChild(base1->progress);

	auto base2 = building::createWithBuildingType(Base);
	base2->setPosition(Vec2(2700, 1300));
	building::add_blood_bar(base2);
	addChild(base2);
	addChild(base2->blood);
	addChild(base2->progress);
	drawNode = DrawNode::create();
	this->addChild(drawNode);
	if (camp[0] == '0')
	{
		enemy_buildings.pushBack(base2);
		buildings.pushBack(base1);
		base2->progress->setColor(Color3B::BLUE);
	}
	else if (camp[0] == '1')
	{
		buildings.pushBack(base2);
		enemy_buildings.pushBack(base1);
		base1->progress->setColor(Color3B::BLUE);
		this->setPosition(Vec2(-1600, -700));
		repair = originmap - Vec2(-1600, -700);
	}

	schedule(schedule_selector(mymap::moveBlood), 0.1f);  //刷新函数，每隔0.1秒
	schedule(schedule_selector(mymap::moveAttack), 0.1f);
	schedule(schedule_selector(mymap::protectmap), 0);
	schedule(schedule_selector(mymap::scheduleBlood_enemy), 0.1f);
	schedule(schedule_selector(mymap::scheduleBlood_mine), 0.1f);
	schedule(schedule_selector(mymap::soldierattack), 0.1f);
	//schedule(schedule_selector(mymap::iscollide), 0);
	schedule(schedule_selector(mymap::net), 0);
	schedule(schedule_selector(mymap::winlose), 0);
	return true;
}
void mymap::winlose(float delta)
{
	int mynumber = 0;
	int enemy_number = 0;
	mynumber = soldiers.size() + buildings.size();
	enemy_number = enemy_soldiers.size() + enemy_buildings.size();
	if (mynumber == 0)
	{
		removeChildByTag(200);
		String*swin = String::createWithFormat("you lose");
		Label*lwin = Label::createWithTTF(swin->getCString(), "fonts/Marker Felt.ttf", 60);
		lwin->setColor(Color3B::RED);
		lwin->setPosition(800 + repair.x, 450 + repair.y);
		addChild(lwin, 5);
		lwin->setTag(200);
	}
	if (enemy_number == 0)
	{
		removeChildByTag(100);
		String*slose = String::createWithFormat("you win");
		Label*llose = Label::createWithTTF(slose->getCString(), "fonts/Marker Felt.ttf", 60);
		llose->setColor(Color3B::YELLOW);
		llose->setPosition(800 + repair.x, 450 + repair.y);
		addChild(llose, 5);
		llose->setTag(100);
	}
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
			this->removeChild(enemy_buildings.at(i)->progress);
			this->removeChild(enemy_buildings.at(i)->blood);
			enemy_buildings.eraseObject(enemy_buildings.at(i));
		}
	}
	for (int i = 0; i < enemy_soldiers.size(); ++i)
	{
		if (enemy_soldiers.at(i)->progress->getPercentage() <= 0)
		{
			enemy_soldiers.at(i)->stopAllActions();
			this->removeChild(enemy_soldiers.at(i));
			this->removeChild(enemy_soldiers.at(i)->progress);
			this->removeChild(enemy_soldiers.at(i)->blood);
			enemy_soldiers.eraseObject(enemy_soldiers.at(i));
		}
	}
	for (int i = 0; i < soldiers.size(); ++i)
	{
		if (soldiers.at(i)->progress->getPercentage() <= 0)
		{
			soldiers.at(i)->stopAllActions();
			this->removeChild(soldiers.at(i));
			this->removeChild(soldiers.at(i)->progress);
			this->removeChild(soldiers.at(i)->blood);
			soldiers.eraseObject(soldiers.at(i));
		}
	}
	for (int i = 0; i < buildings.size(); ++i)
	{
		if (buildings.at(i)->progress->getPercentage() <= 0)
		{
			buildings.at(i)->stopAllActions();
			this->removeChild(buildings.at(i));
			this->removeChild(buildings.at(i)->progress);
			this->removeChild(buildings.at(i)->blood);
			buildings.eraseObject(buildings.at(i));

		}
	}
}
void mymap::net(float delta)
{
	if (connectornot == 1)
	{
		float x = coordinate[5] - repair.x;
		float y = coordinate[6] - repair.y;
		Vec2 dev = Vec2(x, y);
		Vec2 emouse_down = Vec2(coordinate[1], coordinate[2]);
		Vec2 emouse_up = Vec2(coordinate[3], coordinate[4]);
		Vec2 erepair = Vec2(coordinate[5], coordinate[6]);


		for (int j = 0; j < 7; j++)
		{
			ourcopy[j] = coordinate[j];
		}
		//右键
		if (coordinate[0] == 1)
		{
			Soldier::clear(enemy_soldiers);
			coordinate[0] = 0;
		}
		//button层
		if (isTap(emouse_up, buttonlayer->getChildByTag(WALLBUTTONTAG)) ||isTap(emouse_up, buttonlayer->getChildByTag(ROBOTBUTTONTAG)) || isTap(emouse_up, buttonlayer->getChildByTag(TANKBUTTONTAG)) || isTap(emouse_up, buttonlayer->getChildByTag(SOLDIERBUTTONTAG)) || isTap(emouse_up, buttonlayer->getChildByTag(CARINCBUTTONTAG)) || isTap(emouse_up, buttonlayer->getChildByTag(MINEBUTTONTAG)) || isTap(emouse_up, buttonlayer->getChildByTag(EPOWERBUTTONTAG)) || isTap(emouse_up, buttonlayer->getChildByTag(BARRACKBUTTONTAG)))
		{
			auto minebuttontag = buttonlayer->getChildByTag(MINEBUTTONTAG);
			auto barrackbuttontag = buttonlayer->getChildByTag(BARRACKBUTTONTAG);
			auto epowerbuttontag = buttonlayer->getChildByTag(EPOWERBUTTONTAG);
			auto carincbuttontag = buttonlayer->getChildByTag(CARINCBUTTONTAG);
			auto soldierbuttontag = buttonlayer->getChildByTag(SOLDIERBUTTONTAG);
			auto tankbuttontag = buttonlayer->getChildByTag(TANKBUTTONTAG);
			auto robotbuttontag = buttonlayer->getChildByTag(ROBOTBUTTONTAG);
			auto wallbuttontag = buttonlayer->getChildByTag(WALLBUTTONTAG);

			if (isTap(emouse_up, minebuttontag))
			{
				buttonlayer->enemy_buildornot = 1;
				buttonlayer->enemy_buildchoice = 1;
			}
			else if (isTap(emouse_up, barrackbuttontag))
			{
				buttonlayer->enemy_buildornot = 1;
				buttonlayer->enemy_buildchoice = 2;
			}
			else if (isTap(emouse_up, epowerbuttontag))
			{
				buttonlayer->enemy_buildornot = 1;
				buttonlayer->enemy_buildchoice = 3;
			}
			else if (isTap(emouse_up, carincbuttontag))
			{
				buttonlayer->enemy_buildornot = 1;
				buttonlayer->enemy_buildchoice = 4;
			}
			else if (isTap(emouse_up, soldierbuttontag))
			{
				buttonlayer->enemy_buildornot = 2;
				buttonlayer->enemy_buildchoice = 5;
			}
			else if (isTap(emouse_up, tankbuttontag))
			{
				buttonlayer->enemy_buildornot = 2;
				buttonlayer->enemy_buildchoice = 6;
			}
			else if (isTap(emouse_up, robotbuttontag))
			{
				buttonlayer->enemy_buildornot = 2;
				buttonlayer->enemy_buildchoice = 7;
			}
			else if (isTap(emouse_up, wallbuttontag))
			{
				buttonlayer->enemy_buildornot = 1;
				buttonlayer->enemy_buildchoice = 8;
			}
			if (buttonlayer->enemy_buildornot == 2)
			{
				if (buttonlayer->enemy_buildchoice == 5 && buttonlayer->enemy_money >= 100)
				{
					buttonlayer->enemy_money -= 100;
				}
				else if (buttonlayer->enemy_buildchoice == 6 && buttonlayer->enemy_money >= 500)
				{
					buttonlayer->enemy_money -= 500;
				}
				else if (buttonlayer->enemy_buildchoice == 7 && buttonlayer->enemy_money >= 200)
				{
					buttonlayer->enemy_money -= 200;
				}
				if (buttonlayer->enemy_barrack_num&&buttonlayer->enemy_buildchoice == 5 && buttonlayer->enemy_money >= 100)
				{
					auto bing = Soldier::createwithsoldiertype(human);
					bing->setPosition(enemy_barrackpos);
					Soldier::add_bloodbar(bing, repair);
					addChild(bing);
					addChild(bing->blood);
					addChild(bing->progress);
					bing->progress->setColor(Color3B::BLUE);
					enemy_soldiers.pushBack(bing);

				}
				if (buttonlayer->enemy_carinc_num&&buttonlayer->enemy_buildchoice == 6 && buttonlayer->enemy_money >= 800)
				{
					auto bing = Soldier::createwithsoldiertype(tank);
					bing->setPosition(enemy_carincpos);
					Soldier::add_bloodbar(bing, repair);

					addChild(bing);
					addChild(bing->blood,2);
					addChild(bing->progress,3);
					bing->progress->setColor(Color3B::BLUE);
					enemy_soldiers.pushBack(bing);
				}
				if (buttonlayer->enemy_carinc_num&&buttonlayer->enemy_buildchoice == 6 && buttonlayer->enemy_money >= 300)
				{
					auto bing = Soldier::createwithsoldiertype(robot);
					bing->setPosition(enemy_carincpos);
					Soldier::add_bloodbar(bing, repair);

					addChild(bing);
					addChild(bing->blood);
					addChild(bing->progress);
					bing->progress->setColor(Color3B::BLUE);
					enemy_soldiers.pushBack(bing);
				}

				buttonlayer->enemy_buildchoice = 0;
				buttonlayer->enemy_buildornot = false;
			}
		}

		//map层
		else
		{
			//建筑
			if (buttonlayer->enemy_buildornot == 1)
			{
				building*Building = nullptr;
				Vec2 position = emouse_up + dev + repair;//修正量起作用了
				if (buttonlayer->enemy_buildchoice == 1 && buttonlayer->enemy_money >= 2500 && buttonlayer->enemy_power >= 150 && buttonlayer->enemy_epower_num && buttonlayer->enemy_base_num) {
					Building = building::createWithBuildingType(Mine);
					enemy_moneyenough = true;
				}
				else if (buttonlayer->enemy_buildchoice == 2 && buttonlayer->enemy_money >= 1000 && buttonlayer->enemy_power >= 100 && buttonlayer->enemy_base_num &&buttonlayer->enemy_epower_num) {
					Building = building::createWithBuildingType(Barrack);
					enemy_moneyenough = true;
					enemy_barrackpos = position;
				}
				else if (buttonlayer->enemy_buildchoice == 3 && buttonlayer->enemy_money >= 800 && buttonlayer->enemy_base_num) {
					Building = building::createWithBuildingType(Epower);
					enemy_moneyenough = true;
				}
				else if (buttonlayer->enemy_buildchoice == 4 && buttonlayer->enemy_money >= 2000 && buttonlayer->enemy_power >= 120 && buttonlayer->enemy_epower_num &&buttonlayer->enemy_barrack_num&&buttonlayer->enemy_mine_num&&buttonlayer->enemy_base_num) {
					Building = building::createWithBuildingType(Carinc);
					enemy_moneyenough = true;
					enemy_carincpos = position;
				}
				else if (buttonlayer->enemy_buildchoice ==8 && buttonlayer->enemy_money >= 400 && buttonlayer->enemy_base_num) {
					Building = building::createWithBuildingType(Wall);
					enemy_moneyenough = true;
				}
				if (enemy_moneyenough == true)
				{
					Building->setPosition(position);
					building::add_blood_bar(Building);
					enemy_buildings.pushBack(Building);
					addChild(Building);
					addChild(Building->blood);
					addChild(Building->progress);
					Building->progress->setColor(Color3B::BLUE);
					char name = 0;
	
					if (buttonlayer->enemy_buildchoice == 1 && buttonlayer->enemy_money >= 2500 && buttonlayer->enemy_power >= 150 && buttonlayer->enemy_base_num&&buttonlayer->enemy_epower_num)
					{
						buttonlayer->enemy_money -= 2500;
						buttonlayer->enemy_mine_num += 1;
						buttonlayer->enemy_power -= 250;
					}
					else if (buttonlayer->enemy_buildchoice == 2 && buttonlayer->enemy_money >= 1000 && buttonlayer->enemy_power >= 100 && buttonlayer->enemy_base_num &&buttonlayer->enemy_epower_num)
					{
						buttonlayer->enemy_money -= 1000;
						buttonlayer->enemy_barrack_num += 1;
						buttonlayer->enemy_power -= 100;
					}
					else if (buttonlayer->enemy_buildchoice == 3 && buttonlayer->enemy_money >= 800 && buttonlayer->enemy_base_num)
					{
						buttonlayer->enemy_money -= 800;
						buttonlayer->enemy_epower_num += 1;
						buttonlayer->enemy_power += 250;
					}
					else if (buttonlayer->enemy_buildchoice == 4 && buttonlayer->enemy_money >= 2000 && buttonlayer->enemy_power >= 120 && buttonlayer->enemy_epower_num &&buttonlayer->enemy_barrack_num&&buttonlayer->enemy_mine_num&&buttonlayer->enemy_base_num) 
						
					{
						buttonlayer->enemy_money -= 2000;
						buttonlayer->enemy_carinc_num += 1;
						buttonlayer->enemy_power -= 120;
					}
					else if (buttonlayer->enemy_buildchoice == 8 && buttonlayer->enemy_money >= 400 && buttonlayer->enemy_base_num)
					{
						buttonlayer->enemy_money -= 400;
					}
				}
				buttonlayer->enemy_buildornot = false;//将要不要建建筑设为false
				buttonlayer->enemy_buildchoice = 0;
				moneyenough = false;
			}


			//士兵移动及攻击
			Soldier::judge_selected(enemy_soldiers, emouse_down + dev, emouse_up + dev, repair);
			if (emouse_up == emouse_down)
			{
				if (tapenemy(emouse_up+dev, buildings, soldiers) == 0)
				{
					for (int i = 0; i < enemy_soldiers.size(); ++i)
					{
						if (enemy_soldiers.at(i)->selected == 1)
						{
							enemy_soldiers.at(i)->s_enemy = nullptr;
							enemy_soldiers.at(i)->b_enemy = nullptr;
						}
					}
					Soldier::run(enemy_soldiers, emouse_up + dev+repair);
				}

				for (int i = 0; i < soldiers.size(); i++) {
					if (isTap(emouse_up+dev, soldiers.at(i))) {
						Soldier::attacksoldier(enemy_soldiers, soldiers, emouse_up + dev);
					}
				}
				for (int i = 0; i < buildings.size(); i++) {
					if (isTap(emouse_up+dev, buildings.at(i))) {
						Soldier::attackbuilding(enemy_soldiers, buildings, emouse_up + dev);
						break;
					}
				}
			}
		}
		mouse_up = Vec2(0, 0);
		mouse_down = Vec2(0, 0);
		connectornot = 0;
	}

}

void mymap::soldierattack(float delta)
{
	for (int i = 0; i < soldiers.size(); ++i)
	{
		if (soldiers.at(i)->atk == 1 && soldiers.at(i)->b_enemy&&soldiers.at(i)->getPosition().getDistance(soldiers.at(i)->b_enemy->getPosition()) <= 150)
		{
			Vec2 location = soldiers.at(i)->getPosition();
			soldiers.at(i)->setVisible(false);
			if (soldiers.at(i)->sprite == nullptr)
			{
				soldiers.at(i)->sprite = Sprite::create("al2.png");
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
	for (int i = 0; i < enemy_soldiers.size(); ++i)
	{
		if (enemy_soldiers.at(i)->atk == 1 && enemy_soldiers.at(i)->b_enemy&&enemy_soldiers.at(i)->getPosition().getDistance(enemy_soldiers.at(i)->b_enemy->getPosition()) <= 150)
		{
			Vec2 location = enemy_soldiers.at(i)->getPosition();
			enemy_soldiers.at(i)->setVisible(false);
			if (enemy_soldiers.at(i)->sprite == nullptr)
			{
				enemy_soldiers.at(i)->sprite = Sprite::create("al2.png");//士兵攻击图片
				enemy_soldiers.at(i)->sprite->setPosition(location);
				addChild(enemy_soldiers.at(i)->sprite);
				if (enemy_soldiers.at(i)->getPosition().x < enemy_soldiers.at(i)->b_enemy->getPosition().x)
				{
					enemy_soldiers.at(i)->sprite->runAction(FlipX::create(true));
				}
				else if (!(enemy_soldiers.at(i)->getPosition().x < enemy_soldiers.at(i)->b_enemy->getPosition().x))
				{
					enemy_soldiers.at(i)->sprite->runAction(FlipX::create(false));
				}
			}
		}
		else
		{
			if (enemy_soldiers.at(i)->sprite)
			{
				this->removeChild(enemy_soldiers.at(i)->sprite);
				enemy_soldiers.at(i)->sprite = nullptr;
			}
			enemy_soldiers.at(i)->setVisible(true);
		}
	}
}
void mymap::moveBlood(float delta) {
	for (int i = 0; i < soldiers.size(); ++i)
	{
		if (soldiers.at(i)->progress->getPercentage() > 0)
		{
			soldiers.at(i)->blood->setPosition(soldiers.at(i)->getPositionX(), soldiers.at(i)->getPositionY() + 30);
			soldiers.at(i)->progress->setPosition(soldiers.at(i)->getPositionX(), soldiers.at(i)->getPositionY() + 30);
		}
	}
	for (int i = 0; i < enemy_soldiers.size(); ++i)
	{
		if (enemy_soldiers.at(i)->progress->getPercentage() > 0)
		{
			enemy_soldiers.at(i)->blood->setPosition(enemy_soldiers.at(i)->getPositionX(), enemy_soldiers.at(i)->getPositionY() + 30);
			enemy_soldiers.at(i)->progress->setPosition(enemy_soldiers.at(i)->getPositionX(), enemy_soldiers.at(i)->getPositionY() + 30);
		}
	}
}
void mymap::moveAttack(float delta) {
	for (int i = 0; i < soldiers.size(); ++i)
	{
		if (soldiers.at(i)->sprite != nullptr)
		{
			soldiers.at(i)->sprite->setPosition(soldiers.at(i)->getPosition());
		}
	}
	for (int i = 0; i < enemy_soldiers.size(); ++i)
	{
		if (enemy_soldiers.at(i)->sprite != nullptr)
		{
			enemy_soldiers.at(i)->sprite->setPosition(enemy_soldiers.at(i)->getPosition());
		}
	}
}
void mymap::scheduleBlood_enemy(float delta) {
	for (int i = 0; i<soldiers.size(); i++) {
		//敌方士兵
		if (soldiers.at(i)->s_enemy != nullptr) {
			if (soldiers.at(i)->getPosition().getDistance(soldiers.at(i)->s_enemy->getPosition()) <= 150) {
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
					soldiers.at(i)->s_enemy->blood->setVisible(true);
					soldiers.at(i)->s_enemy->progress->setVisible(true);
					int prehealth = soldiers.at(i)->s_enemy->health;
					int nowhealth = prehealth - soldiers.at(i)->atk;
					soldiers.at(i)->s_enemy->health = nowhealth;
					soldiers.at(i)->s_enemy->progress->setPercentage((nowhealth / soldiers.at(i)->s_enemy->originhealth) * 100);
					if (soldiers.at(i)->s_enemy->progress->getPercentage() <= 0)
					{
						soldiers.at(i)->s_enemy->blood->setVisible(false);
						soldiers.at(i)->s_enemy->progress->setVisible(false);
						if (soldiers.at(i)->s_enemy->atk == 10 || soldiers.at(i)->s_enemy->atk == 10)
						{
							Animation* animation = Animation::create();
							for (int i = 1; i <= 9; i++)
							{
								__String *frameName = __String::createWithFormat("z%d.png", i);
								log("frameName = %s", frameName->getCString());
								SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
								animation->addSpriteFrame(spriteFrame);
							}
							animation->setDelayPerUnit(0.1f);           //设置两个帧播放时间
							animation->setRestoreOriginalFrame(false);    //动画执行后还原初始状态
							soldiers.at(i)->s_enemy->getPhysicsBody()->setDynamic(false);
							FiniteTimeAction* action1 = Animate::create(animation);
							FiniteTimeAction* action2 = CallFunc::create(CC_CALLBACK_0(mymap::ruins, this));
							ActionInterval*seq = Sequence::create(action1, action2, NULL);
							soldiers.at(i)->s_enemy->runAction(Sequence::create(seq, NULL));
						}
						else
						{
							Animation* animation = Animation::create();
							char a = 0;
							if (soldiers.at(i)->getPosition().x > soldiers.at(i)->s_enemy->getPosition().x)
							{
								a = 'r';
							}
							else
							{
								a = 'l';
							}
							for (int i = 1; i <= 2; i++)
							{
								__String *frameName = __String::createWithFormat("die%c%d.png", a, i);
								log("frameName = %s", frameName->getCString());
								SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
								animation->addSpriteFrame(spriteFrame);
							}
							animation->setDelayPerUnit(0.5f);           //设置两个帧播放时间
							animation->setRestoreOriginalFrame(false);    //动画执行后还原初始状态
							soldiers.at(i)->s_enemy->getPhysicsBody()->setDynamic(false);
							FiniteTimeAction* action1 = Animate::create(animation);
							FiniteTimeAction* action2 = CallFunc::create(CC_CALLBACK_0(mymap::ruins, this));
							ActionInterval*seq = Sequence::create(action1, action2, NULL);
							soldiers.at(i)->s_enemy->runAction(Sequence::create(seq, NULL));
						}
						soldiers.at(i)->s_enemy = nullptr;
						soldiers.at(i)->stopAllActions();
						soldiers.at(i)->s_enemy = nullptr;

					}
				}
				else
				{
					soldiers.at(i)->s_enemy = nullptr;
					soldiers.at(i)->isattack = 0;
				}
			}
			else {
				Soldier::run(soldiers, soldiers.at(i)->s_enemy->getPosition()+repair);
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
					soldiers.at(i)->b_enemy->blood->setVisible(true);
					soldiers.at(i)->b_enemy->progress->setVisible(true);
					int prehealth = soldiers.at(i)->b_enemy->building_health;
					int nowhealth = prehealth - soldiers.at(i)->atk;
					soldiers.at(i)->b_enemy->building_health = nowhealth;
					soldiers.at(i)->b_enemy->progress->setPercentage(nowhealth / soldiers.at(i)->b_enemy->originhealth * 100);

					if (soldiers.at(i)->b_enemy->progress->getPercentage() <= 0)
					{
						soldiers.at(i)->b_enemy->blood->setVisible(false);
						soldiers.at(i)->b_enemy->progress->setVisible(false);
						//Vec2 loc = soldiers.at(i)->b_enemy->getPosition();
						if (soldiers.at(i)->b_enemy->originhealth == 3000)
						{
							buttonlayer->enemy_base_num -= 1;
						}
						else if (soldiers.at(i)->b_enemy->originhealth == 2000)
						{
							buttonlayer->enemy_mine_num -= 1;
						}
						else if (soldiers.at(i)->b_enemy->originhealth == 1200)
						{
							buttonlayer->enemy_epower_num -= 1;
						}
						else if (soldiers.at(i)->b_enemy->originhealth == 1400)
						{
							buttonlayer->enemy_barrack_num -= 1;
						}
						else if (soldiers.at(i)->b_enemy->originhealth == 1900)
						{
							buttonlayer->enemy_carinc_num -= 1;
						}
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
						soldiers.at(i)->b_enemy->getPhysicsBody()->setDynamic(false);
						FiniteTimeAction* action1 = Animate::create(animation);
						FiniteTimeAction* action2 = CallFunc::create(CC_CALLBACK_0(mymap::ruins, this));
						ActionInterval*seq = Sequence::create(action1, action2, NULL);
						soldiers.at(i)->b_enemy->runAction(Sequence::create(seq, NULL));
						soldiers.at(i)->stopAllActions();
						soldiers.at(i)->b_enemy = nullptr;
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
	for (int i = 0; i<enemy_soldiers.size(); i++) {
		//敌方士兵
		if (enemy_soldiers.at(i)->s_enemy != nullptr) {
			
			if (enemy_soldiers.at(i)->getPosition().getDistance(enemy_soldiers.at(i)->s_enemy->getPosition()) <= 150) {
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
					enemy_soldiers.at(i)->s_enemy->blood->setVisible(true);
					enemy_soldiers.at(i)->s_enemy->progress->setVisible(true);
					int prehealth = enemy_soldiers.at(i)->s_enemy->health;
					int nowhealth = prehealth - enemy_soldiers.at(i)->atk;
					enemy_soldiers.at(i)->s_enemy->health = nowhealth;
					enemy_soldiers.at(i)->s_enemy->progress->setPercentage((nowhealth / enemy_soldiers.at(i)->s_enemy->originhealth) * 100);
					if (enemy_soldiers.at(i)->s_enemy->progress->getPercentage() <= 0)
					{
						enemy_soldiers.at(i)->s_enemy->blood->setVisible(false);
						enemy_soldiers.at(i)->s_enemy->progress->setVisible(false);
						if (enemy_soldiers.at(i)->s_enemy->atk == 10 || enemy_soldiers.at(i)->s_enemy->atk == 10)
						{
							Animation* animation = Animation::create();
							for (int i = 1; i <= 9; i++)
							{
								__String *frameName = __String::createWithFormat("z%d.png", i);
								log("frameName = %s", frameName->getCString());
								SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
								animation->addSpriteFrame(spriteFrame);
							}
							animation->setDelayPerUnit(0.1f);           //设置两个帧播放时间
							animation->setRestoreOriginalFrame(false);    //动画执行后还原初始状态
							enemy_soldiers.at(i)->s_enemy->getPhysicsBody()->setDynamic(false);
							FiniteTimeAction* action1 = Animate::create(animation);
							FiniteTimeAction* action2 = CallFunc::create(CC_CALLBACK_0(mymap::ruins, this));
							ActionInterval*seq = Sequence::create(action1, action2, NULL);
							enemy_soldiers.at(i)->s_enemy->runAction(Sequence::create(seq, NULL));
							enemy_soldiers.at(i)->stopAllActions();
						}
						else
						{
							Animation* animation = Animation::create();
							char a = 0;
							if (enemy_soldiers.at(i)->getPosition().x > enemy_soldiers.at(i)->s_enemy->getPosition().x)
							{
								a = 'r';
							}
							else
							{
								a = 'l';
							}
							for (int i = 1; i <= 2; i++)
							{
								__String *frameName = __String::createWithFormat("die%c%d.png", a, i);
								log("frameName = %s", frameName->getCString());
								SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
								animation->addSpriteFrame(spriteFrame);
							}
							animation->setDelayPerUnit(0.5f);           //设置两个帧播放时间
							animation->setRestoreOriginalFrame(false);    //动画执行后还原初始状态
							enemy_soldiers.at(i)->s_enemy->getPhysicsBody()->setDynamic(false);
							FiniteTimeAction* action1 = Animate::create(animation);
							FiniteTimeAction* action2 = CallFunc::create(CC_CALLBACK_0(mymap::ruins, this));
							ActionInterval*seq = Sequence::create(action1, action2, NULL);
							enemy_soldiers.at(i)->s_enemy->runAction(Sequence::create(seq, NULL));
							enemy_soldiers.at(i)->stopAllActions();
						}
						enemy_soldiers.at(i)->s_enemy = nullptr;
						//soldiers.at(i)->isattack = 0;
						enemy_soldiers.at(i)->stopAllActions();

					}
				}
				else
				{
					enemy_soldiers.at(i)->s_enemy = nullptr;
					enemy_soldiers.at(i)->isattack = 0;
				}
			}
			else {
				Soldier::run(enemy_soldiers, enemy_soldiers.at(i)->s_enemy->getPosition());
			}
		}

		//地方建筑
		if (enemy_soldiers.at(i)->b_enemy != nullptr) {
			
			if (enemy_soldiers.at(i)->getPosition().getDistance(enemy_soldiers.at(i)->b_enemy->getPosition()) <= 150) {
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
					enemy_soldiers.at(i)->b_enemy->blood->setVisible(true);
					enemy_soldiers.at(i)->b_enemy->progress->setVisible(true);
					int prehealth = enemy_soldiers.at(i)->b_enemy->building_health;
					int nowhealth = prehealth - enemy_soldiers.at(i)->atk;
					enemy_soldiers.at(i)->b_enemy->building_health = nowhealth;
					enemy_soldiers.at(i)->b_enemy->progress->setPercentage(nowhealth / enemy_soldiers.at(i)->b_enemy->originhealth * 100);

					if (enemy_soldiers.at(i)->b_enemy->progress->getPercentage() <= 0)
					{
						enemy_soldiers.at(i)->b_enemy->blood->setVisible(false);
						enemy_soldiers.at(i)->b_enemy->progress->setVisible(false);
						//Vec2 loc = soldiers.at(i)->b_enemy->getPosition();
						if (enemy_soldiers.at(i)->b_enemy->originhealth == 3000)
						{
							buttonlayer->enemy_base_num -= 1;
						}
						else if (enemy_soldiers.at(i)->b_enemy->originhealth == 2000)
						{
							buttonlayer->enemy_mine_num -= 1;
						}
						else if (enemy_soldiers.at(i)->b_enemy->originhealth == 1200)
						{
							buttonlayer->enemy_epower_num -= 1;
						}
						else if (enemy_soldiers.at(i)->b_enemy->originhealth == 1400)
						{
							buttonlayer->enemy_barrack_num -= 1;
						}
						else if (enemy_soldiers.at(i)->b_enemy->originhealth == 1900)
						{
							buttonlayer->enemy_carinc_num -= 1;
						}
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
						enemy_soldiers.at(i)->b_enemy->getPhysicsBody()->setDynamic(false);
						FiniteTimeAction* action1 = Animate::create(animation);
						FiniteTimeAction* action2 = CallFunc::create(CC_CALLBACK_0(mymap::ruins, this));
						ActionInterval*seq = Sequence::create(action1, action2, NULL);
						enemy_soldiers.at(i)->b_enemy->runAction(Sequence::create(seq, NULL));
						enemy_soldiers.at(i)->stopAllActions();
						enemy_soldiers.at(i)->b_enemy = nullptr;
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
		mouse_down = em->getLocation();
		mouse_down = Director::getInstance()->convertToGL(mouse_down);
		ismousedown = 1;
		//mouse_down = location+repair;
	};
	listener->onMouseMove = [this](Event *e) {
		EventMouse* em = (EventMouse*)e;
		mouse_move = em->getLocation();
		mouse_move = Director::getInstance()->convertToGL(mouse_move);

		drawNode->clear();
		if (ismousedown) {
			Vec2 point[4];
			point[0] = Vec2(mouse_down.x + repair.x, mouse_down.y + repair.y);
			point[1] = Vec2(mouse_down.x + repair.x, mouse_move.y + repair.y);
			point[2] = Vec2(mouse_move.x + repair.x, mouse_move.y + repair.y);
			point[3] = Vec2(mouse_move.x + repair.x, mouse_down.y + repair.y);
			drawNode->drawPolygon(point, 4, Color4F(1, 0, 0, 0), 1, Color4F(144, 144, 144, 1));
		}
		pos1 = this->getPosition();
		auto tilesize = _tileMap->getTileSize();
		auto visize = Director::getInstance()->getVisibleSize();
		if (mouse_move.y >= 880 && pos1.y > -700)
		{
			Action*actionup = this->runAction(MoveTo::create((pos1.y + 700) / 20, Vec2(pos1.x, -700)));
			actionup->setTag(1);
		}
		if (mouse_move.y <= 20 && pos1.y < 0)
		{
			//this->stopAllActions();
			Action*actiondown = this->runAction(MoveTo::create(-pos1.y / 20, Vec2(pos1.x, 0)));
			actiondown->setTag(2);
		}
		else if (mouse_move.x <= 20 && pos1.x < 0)
		{
			Action*actionleft = this->runAction(MoveTo::create(-pos1.x / 20, Vec2(0, pos1.y)));
			actionleft->setTag(3);
		}
		else if (mouse_move.x >= 1580 && pos1.x > -1600)
		{
			Action*actionright = this->runAction(MoveTo::create((pos1.x + 1600) / 20, Vec2(-1600, pos1.y)));
			actionright->setTag(4);
		}
		pos1 = this->getPosition();
		if (mouse_move.y < 850)
		{
			this->stopActionByTag(1);
			repair = originmap - pos1;
		}
		if (mouse_move.y > 20)
		{
			this->stopActionByTag(2);
			repair = originmap - pos1;
		}
		if (mouse_move.x > 50)
		{
			this->stopActionByTag(3);
			repair = originmap - pos1;
		}
		if (mouse_move.x < 1550)
		{
			this->stopActionByTag(4);
			repair = originmap - pos1;
		}
	};

	listener->onMouseUp = [this](Event *e) {
		ismousedown = 0;
		int right = 0;
		drawNode->clear();
		this->drawNode->clear();
		EventMouse* em = (EventMouse*)e;
		std::string str = " ";
		str += to_string(static_cast<int>(em->getMouseButton()
			));
		if (str == " 1") {
			Soldier::clear(soldiers);
			right = 1;
		}
		mouse_up = em->getLocation();
		mouse_up = Director::getInstance()->convertToGL(mouse_up);//将鼠标的坐标转换为世界坐标
																  //基本创建建筑的事件
		clientsend(right, mouse_up, mouse_down, repair);
		right = 0;

		Soldier::judge_selected(soldiers, mouse_down, mouse_up, repair);
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
				Soldier::run(soldiers, mouse_up + repair);
			}
		}
		for (int i = 0; i < enemy_soldiers.size(); i++) {
			if (isTap(mouse_up, enemy_soldiers.at(i))) {
				Soldier::attacksoldier(soldiers, enemy_soldiers, mouse_up);
			}
		}
		for (int i = 0; i<enemy_buildings.size(); i++) {
			if (isTap(mouse_up, enemy_buildings.at(i))) {
				Soldier::attackbuilding(soldiers, enemy_buildings, mouse_up);
				break;
			}
		}
		if (buttonlayer->buildornot == 1 && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(WALLBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(SOLDIERBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(CARINCBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(MINEBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(EPOWERBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(BARRACKBUTTONTAG))))
		{
			Vec2 position = mouse_up + repair;//修正量起作用了
			building* Building = NULL;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/buildingsound.mp3");
			if (buttonlayer->buildchoice == 1) {
				Building = building::createWithBuildingType(Mine);
				moneyenough = true;
			}
			else if (buttonlayer->buildchoice == 2) {
				Building = building::createWithBuildingType(Barrack);
				moneyenough = true;
				barrackpos = position;
			}
			else if (buttonlayer->buildchoice == 3) {
				Building = building::createWithBuildingType(Epower);
				moneyenough = true;
			}
			else if (buttonlayer->buildchoice == 4) {
				Building = building::createWithBuildingType(Carinc);
				moneyenough = true;
				carincpos = position;
			}
			else if (buttonlayer->buildchoice == 8) {
				Building = building::createWithBuildingType(Wall);
				moneyenough = true;
			}
			if (moneyenough == true)
			{
				Building->setPosition(position);
				building::add_blood_bar(Building);
				buildings.pushBack(Building);
				addChild(Building, 1);
				addChild(Building->blood, 2);
				addChild(Building->progress, 3);
				//将建筑物血条添加到容器中
				buttonlayer->updatemoney(buttonlayer->buildchoice);//购买后更新钱数更新
				if (buttonlayer->buildchoice != 8)
				{
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
				
					animation->setDelayPerUnit(0.5f);           //设置两个帧播放时间
					animation->setRestoreOriginalFrame(false);    //动画执行后还原初始状态

					Animate* action = Animate::create(animation);
					Building->runAction(action);
				}
				else
				{
					Building->blood->setScale(0.05);
					Building->progress->setScale(0.05);
				}
				moneyenough = false;
			}
			buttonlayer->buildornot = false;//将要不要建建筑设为false
			buttonlayer->buildchoice = 0;
		}
		else if (buttonlayer->buildornot == 2)
		{

			if (buttonlayer->buildchoice == 5)
			{
				soldiernum += 1;
				auto bing = Soldier::createwithsoldiertype(human);
				bing->setPosition(barrackpos);
				Soldier::add_bloodbar(bing, repair);
				addChild(bing, 1);
				addChild(bing->blood, 2);
				addChild(bing->progress, 3);
				soldiers.pushBack(bing);
				buttonlayer->updatemoney(buttonlayer->buildchoice);//购买后更新钱数更新
			}
			if (buttonlayer->buildchoice == 6)
			{
				soldiernum += 1;
				auto bing = Soldier::createwithsoldiertype(tank);
				bing->setPosition(carincpos);
				Soldier::add_bloodbar(bing, repair);

				addChild(bing, 1);
				addChild(bing->blood, 2);
				addChild(bing->progress, 3);
				soldiers.pushBack(bing);
				buttonlayer->updatemoney(buttonlayer->buildchoice);//购买后更新钱数更新
			}
			if (buttonlayer->buildchoice == 7)
			{
				soldiernum += 1;
				auto bing = Soldier::createwithsoldiertype(robot);
				bing->setPosition(carincpos);
				Soldier::add_bloodbar(bing, repair);

				addChild(bing, 1);
				addChild(bing->blood, 2);
				addChild(bing->progress, 3);
				soldiers.pushBack(bing);
				buttonlayer->updatemoney(buttonlayer->buildchoice);//购买后更新钱数更新
			}

			buttonlayer->buildchoice = 0;

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
bool mymap::tapenemy(Vec2 location, Vector<building*>enemy_buildings, Vector<Soldier*>enemy_soldiers)
{
	bool tap = 0;
	for (int i = 0; i < enemy_soldiers.size(); i++) {
		if (Soldier::isTap(location, enemy_soldiers.at(i))) {
			tap = 1;
			break;
		}
	}
	for (int i = 0; i<enemy_buildings.size(); i++) {
		if (Soldier::isTap(location, enemy_buildings.at(i))) {
			tap = 1;
			break;
		}
	}
	return tap;
}
bool mymap::taparmy(Vec2 location, Vector<building*>buildings, Vector<Soldier*>soldiers)
{
	bool tap = 0;
	for (int i = 0; i < soldiers.size(); i++) {
		if (Soldier::isTap(location, soldiers.at(i))) {
			tap = 1;
			break;
		}
	}
	for (int i = 0; i<buildings.size(); i++) {
		if (Soldier::isTap(location, buildings.at(i))) {
			tap = 1;
			break;
		}
	}
	return tap;
}









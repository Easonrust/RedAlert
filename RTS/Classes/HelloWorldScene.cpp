#include "HelloWorldScene.h"
#define BUTTONLISTTAG 0
#define MINEBUTTONTAG 1
#define EPOWERBUTTONTAG 2
#define BARRACKBUTTONTAG 3
#define CARINCBUTTONTAG 4
#define MONEYPOWERLISTTAG 5
#define MONEYTAG 6
#define MONEYPNG 7
#define POWERTAG 8
#define POWERPNG 9
#define SOLDIERBUTTONTAG 10
#define TANKBUTTONTAG 11
#define ROBOTBUTTONTAG 12
USING_NS_CC;

<<<<<<< HEAD
=======
//mymap*a1;
//button*b1;
>>>>>>> ab1ada03140212484ed3a40919f40438b177e69c
Scene* HelloWorld::createScene()

{
	auto a = mymap::create();//创建地图层
    auto b = button::create();//创建按钮层
	auto scene = Scene::createWithPhysics();//创造物理场景
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));//重力为零
	a->buttonlayer = b;//将地图层中按钮层指针指向按钮层（用于信息交互）注意两个类不能互相指
	scene->addChild(a);
	scene->addChild(b);
<<<<<<< HEAD
	return scene;
}



=======
	//a1 = a;
	//b1 = b;
	return scene;
}

/*void judgecamp(char*revcamp)
{
	int camp = (int)revcamp[0];
}*/

/*/*void revmessage(char*revmsg,mymap*a,button*b)
{
	float coordinate[7];
	/*cout << "receive message1:" << revmsg << endl;
	
	for (int i = 0; i < 7; i++)
	{
		coordinate[i] = atof(revmsg + 16 * i);
		cout << coordinate[i] << endl;
	}*/
/*	Json::Reader reader;
	Json::Value root;
	if (reader.parse(revmsg, root))
	{
		coordinate[0] = ((float)root["right"].asInt()) / 100000;
		coordinate[1] = ((float)root["downx"].asInt()) / 100000;
		coordinate[2] = ((float)root["downy"].asInt()) / 100000;
		coordinate[3] = ((float)root["upx"].asInt()) / 100000;
		coordinate[4] = ((float)root["upy"].asInt()) / 100000;
		coordinate[5] = ((float)root["fitx"].asInt()) / 100000;
		coordinate[6] = ((float)root["fity"].asInt()) / 100000;
	}
	Sleep(10);
	for (int i = 0; i < 7; i++)
	{
		cout << "coor:  " << coordinate[i] << endl;
	}
	
	float x = coordinate[5] - a->repair.x;
	float y = coordinate[6] - a->repair.y;
	Vec2 dev = Vec2(x, y);
	Vec2 emouse_down = Vec2(coordinate[1], coordinate[2]);
	Vec2 emouse_up = Vec2(coordinate[3], coordinate[4]);
	Vec2 erepair = Vec2(coordinate[5], coordinate[6]);
	//右键
	if (coordinate[0] == 1)
	{
		Soldier::clear(a->soldiers);
	}

	//button层
	if (a->isTap(emouse_up, a->buttonlayer->getChildByTag(SOLDIERBUTTONTAG))||a->isTap(emouse_up, a->buttonlayer->getChildByTag(CARINCBUTTONTAG))||a->isTap(emouse_up, a->buttonlayer->getChildByTag(MINEBUTTONTAG))||a->isTap(emouse_up, a->buttonlayer->getChildByTag(EPOWERBUTTONTAG)) ||a->isTap(emouse_up, a->buttonlayer->getChildByTag(BARRACKBUTTONTAG)))
{
auto minebuttontag = a->buttonlayer->getChildByTag(MINEBUTTONTAG);
auto barrackbuttontag = a->buttonlayer->getChildByTag(BARRACKBUTTONTAG);
auto epowerbuttontag = a->buttonlayer->getChildByTag(EPOWERBUTTONTAG);
auto carincbuttontag = a->buttonlayer->getChildByTag(CARINCBUTTONTAG);
auto soldierbuttontag = a->buttonlayer->getChildByTag(SOLDIERBUTTONTAG);
auto tankbuttontag = a->buttonlayer->getChildByTag(TANKBUTTONTAG);
auto robotbuttontag = a->buttonlayer->getChildByTag(ROBOTBUTTONTAG);
if (a->isTap(emouse_up, minebuttontag))
{
	b->enemy_buildornot = 1;
	b->enemy_buildchoice = 1;
}
else if (a->isTap(emouse_up, barrackbuttontag))
{
	b->enemy_buildornot = 1;
	b->enemy_buildchoice = 2;
}
else if (a->isTap(emouse_up, epowerbuttontag))
{
	b->enemy_buildornot = 1;
	b->enemy_buildchoice = 3;
}
else if (a->isTap(emouse_up, carincbuttontag))
{
	b->enemy_buildornot = 1;
	b->enemy_buildchoice = 4;
}
else if (a->isTap(emouse_up, soldierbuttontag))
{
	b->enemy_buildornot = 2;
	b->enemy_buildchoice = 5;
}
else if (a->isTap(emouse_up, tankbuttontag))
{
	b->enemy_buildornot = 2;
	b->enemy_buildchoice = 6;
}
else if (a->isTap(emouse_up, robotbuttontag))
{
	b->enemy_buildornot = 2;
	b->enemy_buildchoice = 7;
}
}

	//map层
	else
	{
		//建筑
		if (a->buttonlayer->enemy_buildornot == 1)
		{
			Vec2 position = emouse_up + a->repair;//修正量起作用了
			building* Building = NULL;
			if (a->buttonlayer->enemy_buildchoice == 1 && a->buttonlayer->enemy_money >= 900) {
				Building = building::createWithBuildingType(Mine);
				a->enemy_moneyenough = true;
			}
			else if (a->buttonlayer->enemy_buildchoice == 2 && a->buttonlayer->enemy_money >= 1000) {
				Building = building::createWithBuildingType(Barrack);
				a->enemy_moneyenough = true;
				a->enemy_barrackpos = position;
			}
			else if (a->buttonlayer->enemy_buildchoice == 3 && a->buttonlayer->enemy_money >= 800) {
				Building = building::createWithBuildingType(Epower);
				a->enemy_moneyenough = true;
			}
			else if (a->buttonlayer->enemy_buildchoice == 4 && a->buttonlayer->enemy_money >= 700) {
				Building = building::createWithBuildingType(Carinc);
				a->enemy_moneyenough = true;
				a->enemy_carincpos = position;
			}
			if (a->moneyenough == true)
			{
				Building->setPosition(position);
				building::add_blood_bar(Building);
				a->enemy_buildings.pushBack(Building);
				a->addChild(Building);
				a->addChild(Building->blood);
				a->addChild(Building->progress);
				char name = 0;
				switch (a->buttonlayer->buildchoice)
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
				if (b->enemy_buildchoice == 1 && b->enemy_money >= 900)
				{
					b->enemy_money -= 900;
				}
				else if (b->enemy_buildchoice == 2 && b->enemy_money >= 1000)
				{
					b->enemy_money -= 1000;
				}
				else if (b->enemy_buildchoice == 3 && b->enemy_money >= 800)
				{
					b->enemy_money -= 800;
				}
				else if (b->enemy_buildchoice == 4 && b->enemy_money >= 700)
				{
					b->enemy_money -= 700;
				}
			}
			a->buttonlayer->enemy_buildornot = false;//将要不要建建筑设为false
			a->buttonlayer->enemy_buildchoice = 0;
		}
		//兵种
		else if (a->buttonlayer->enemy_buildornot == 2)
		{
			if (b->enemy_buildchoice == 5 && b->enemy_money >= 100)
			{
				b->enemy_money -= 100;
			}
			else if (b->enemy_buildchoice == 6 && b->enemy_money >= 500)
			{
				b->enemy_money -= 500;
			}
			else if (b->enemy_buildchoice == 7 && b->enemy_money >= 200)
			{
				b->enemy_money -= 200;
			}
			if (a->enemy_barrackpos != Vec2(0, 0) && a->buttonlayer->enemy_buildchoice == 5 && a->buttonlayer->enemy_money >= 100)
			{
				auto bing = Soldier::createwithsoldiertype(human);
				bing->setPosition(a->enemy_barrackpos);
				Soldier::add_bloodbar(bing, a->repair);
				a->addChild(bing);
				a->addChild(bing->blood);
				a->addChild(bing->progress);
				a->enemy_soldiers.pushBack(bing);
			}
			if (a->enemy_carincpos != Vec2(0, 0) && a->buttonlayer->enemy_buildchoice == 6 && a->buttonlayer->enemy_money >= 500)
			{
				auto bing = Soldier::createwithsoldiertype(tank);
				bing->setPosition(a->enemy_carincpos);
				Soldier::add_bloodbar(bing, a->repair);

				a->addChild(bing);
				a->addChild(bing->blood);
				a->addChild(bing->progress);
				a->enemy_soldiers.pushBack(bing);
			}
			if (a->enemy_carincpos != Vec2(0, 0) &&a-> buttonlayer->enemy_buildchoice == 7 && a->buttonlayer->enemy_money >= 200)
			{
				auto bing = Soldier::createwithsoldiertype(robot);
				bing->setPosition(a->enemy_carincpos);
				Soldier::add_bloodbar(bing, a->repair);

				a->addChild(bing);
				a->addChild(bing->blood);
				a->addChild(bing->progress);
				a->enemy_soldiers.pushBack(bing);
			}

			a->buttonlayer->enemy_buildchoice = 0;
			a->buttonlayer->enemy_buildornot = false;
		}

		//士兵移动及攻击
		Soldier::judge_selected(a->soldiers, emouse_down + dev, emouse_up + dev, a->repair);
		if (emouse_up == emouse_down)
		{
			if (a->tapenemy(emouse_up, a->buildings, a->soldiers) == 0)
			{
				for (int i = 0; i < a->enemy_soldiers.size(); ++i)
				{
					if (a->enemy_soldiers.at(i)->selected == 1)
					{
						a->enemy_soldiers.at(i)->s_enemy = nullptr;
						a->enemy_soldiers.at(i)->b_enemy = nullptr;
					}
				}
				Soldier::run(a->enemy_soldiers, emouse_up + dev + a->repair);
			}
		}
		for (int i = 0; i < a->soldiers.size(); i++) {
			if (a->isTap(emouse_up + dev, a->soldiers.at(i))) {
				Soldier::attacksoldier(a->enemy_soldiers, a->soldiers, emouse_up + dev);
			}
		}
		for (int i = 0; i < a->buildings.size(); i++) {
			if (a->isTap(emouse_up + dev, a->buildings.at(i))) {
				Soldier::attackbuilding(a->enemy_soldiers, a->buildings, emouse_up + dev);
				break;
			}
		}
	}
}*/
>>>>>>> ab1ada03140212484ed3a40919f40438b177e69c

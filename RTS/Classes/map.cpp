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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("build.plist");
	this->setAnchorPoint(Vec2(0, 0));
	originmap = this->getPosition();
	repair = Vec2(0, 0);//�ƶ���ͼ���ڵ�ͼ�Ͻ��쾫��ʱ�����������

						//�����ͼ

	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap, 0, MAPTAG);
	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(false);
	/*//���ݵ�ͼ�ļ��еĶ���㴴�����ض���
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("base");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();*/
	auto bing = Soldier::create("base.png");
	bing->setPosition(720, 450);
	Soldier::add_bloodbar(bing);
	addChild(bing);
	addChild(bing->blood);
	addChild(bing->progress);
	enemy_soldiers.pushBack(bing);
	bing->blood->setVisible(true);
	bing->progress->setVisible(true);
	auto base = building::createWithBuildingType(Base);
	buildingnum += 1;//����ͼ��Ŀǰ�Ľ���������һ
	base->setPosition(Vec2(300, 300));
	building::add_blood_bar(base);
	buildings.pushBack(base);//��������ӵ�������������
	addChild(base);
	addChild(base->bloodbar);
	addChild(base->progress);

	schedule(schedule_selector(mymap::moveBlood), 0.1f);  //ˢ�º�����ÿ��0.1��
	schedule(schedule_selector(mymap::protectmap), 0);
	schedule(schedule_selector(mymap::iscollide), 0);
	return true;
}
//Ѫ��ˢ�º���
void mymap::moveBlood(float delta) {
	for (int i = 0; i < soldiers.size(); ++i)
	{
		if (soldiers.at(i)->selected == 1)
		{
			soldiers.at(i)->blood->setPosition(soldiers.at(i)->getPositionX(), soldiers.at(i)->getPositionY() + 16);
			soldiers.at(i)->progress->setPosition(soldiers.at(i)->getPositionX(), soldiers.at(i)->getPositionY() + 16);
		}
	}
}
/*void mymap::scheduleBlood_enemy(float delta){
int target = 0;
for(int i = 0;i<enemy_soldiers.size();i++){
if(enemy_soldiers.at(i)->attacker.size()){
target = i;
}
}
auto enemy_p = enemy_soldiers.at(target)->getPosition();

for(int i = 0;i<enemy_soldiers.at(target)->attacker.size();i++){
auto p =enemy_soldiers.at(target)->attacker.at(i)->getPosition();
if(p.getDistance(enemy_p)<=200){
enemy_soldiers.at(target)->attacker.at(i)->stopAllActions();
enemy_soldiers.at(target)->attacker.at(i)->isrun = 0;
enemy_soldiers.at(i)->progress->setPercentage(enemy_soldiers.at(i)->progress->getPercentage()-2);
}
}
}*/
/*void mymap::scheduleBlood_enemy(float delta) {
	for (int i = 0; i<enemy_soldiers.size(); i++) {
		if (!enemy_soldiers.at(i)->attacker) {
			enemy_soldiers.at(i)->progress->setPercentage(enemy_soldiers.at(i)->progress->getPercentage() - enemy_soldiers.at(i)->attacker * 2);
		}
	}
}*/
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
		location = Director::getInstance()->convertToGL(location);//����������ת��Ϊ��������
																  //���������������¼�
		mouse_up = location + repair;
		Soldier::judge_selected(soldiers, mouse_down, mouse_up);

		if (mouse_up == mouse_down && !buttonlayer->buildornot && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(SOLDIERBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(CARINCBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(MINEBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(EPOWERBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(BARRACKBUTTONTAG))))
		{

			Soldier::run(soldiers, mouse_up);
		}
		/*for (int i = 0; i<enemy_soldiers.size(); i++) {
			if (Soldier::isTap(location, enemy_soldiers.at(i))) {
				Soldier::attack(soldiers, enemy_soldiers, location);
			}
		}*/
		if (buttonlayer->buildornot == 1 && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(SOLDIERBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(CARINCBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(MINEBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(EPOWERBUTTONTAG))) && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(BARRACKBUTTONTAG))))
		{
			Vec2 position = location + repair;//��������������
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
			}
			if (moneyenough == true)
			{
				buildingnum += 1;//����ͼ�Ͻ���������һ
				Building->setPosition(position);
				building::add_blood_bar(Building);
				buildings.pushBack(Building);
				addChild(Building);
				addChild(Building->bloodbar);
				addChild(Building->progress);
				//��������Ѫ����ӵ�������
				buttonlayer->updatemoney(buttonlayer->buildchoice);//��������Ǯ������
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
				animation->setDelayPerUnit(0.7f);           //��������֡����ʱ��
				animation->setRestoreOriginalFrame(false);    //����ִ�к�ԭ��ʼ״̬

				Animate* action = Animate::create(animation);
				Building->runAction(action);

			}
			buttonlayer->buildornot = false;//��Ҫ��Ҫ��������Ϊfalse
			buttonlayer->buildchoice = 0;
		}
		else if (buttonlayer->buildornot == 2 && (buttonlayer->money) >= 100)
		{
			if (barrackpos != Vec2(0, 0))
			{
				auto location = barrackpos;
				soldiernum += 1;
				auto bing = Soldier::create("soldier.png");
				bing->setPosition(location);
				Soldier::add_bloodbar(bing);
				addChild(bing);
				addChild(bing->blood);
				addChild(bing->progress);
				soldiers.pushBack(bing);
			}
			buttonlayer->buildornot = false;
		}
		else if (buttonlayer->buildornot == 3 && (buttonlayer->money) >= 500)
		{
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


//���õص��ܷ��콨�����������������ص�����bug��������û��ʹ���������棬���ƶ���ͼ���ʧЧ�ˣ���������
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
			if (distance<100)
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
	//�����Ƭ��GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();

		if (collision == "true") { //��ײ���ɹ�
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
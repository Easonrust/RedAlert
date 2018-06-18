#include"map.h"
#include"button.h"
#include "building.h"
#include <iostream>
#include "Soldier.h"

bool mymap::init()
{
    if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	originmap=this->getPosition();
	repair = Vec2(0, 0);//�ƶ���ͼ���ڵ�ͼ�Ͻ��쾫��ʱ�����������

	//�����ͼ
	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap, 0, MAPTAG);
	//���ݵ�ͼ�ļ��еĶ���㴴�����ض���
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("base");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
    auto base = building::createWithBuildingType(Base);
	buildingnum += 1;//����ͼ��Ŀǰ�Ľ���������һ
    base->setPosition(Vec2(x,y));
    building::add_blood_bar(base);
	buildings.pushBack(base);//��������ӵ�������������
    addChild(base);
    addChild(base->bloodbar);
    addChild(base->progress);
    
	schedule(schedule_selector(mymap::scheduleBlood), 0.1f);  //ˢ�º�����ÿ��0.1��
	schedule(schedule_selector(mymap::setmap), 0.1f);
	return true;
}
//Ѫ��ˢ�º���


void mymap::scheduleBlood(float delta) {
    for(int i = 0;i<buildings.size();i++){
        if(buildings.at(i)->progress->getPercentage()!=100){
            buildings.at(i)->progress->setPercentage(buildings.at(i)->progress->getPercentage()+0.1);
            buildings.at(i)->progress->setVisible(true);
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
        mouse_down = location;
	};
	listener->onMouseUp = [this](Event *e) {
		EventMouse* em = (EventMouse*)e;
		auto location = em->getLocation();
        location = Director::getInstance()->convertToGL(location);//����������ת��Ϊ��������
        mouse_up = location;
        //Soldier::judge_selected(soldiers, mouse_down, mouse_up);
		//���������������¼�
		if (buttonlayer->buildornot==1 && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(SOLDIERBUTTONTAG))) &&!(buttonlayer->isTap(em, buttonlayer->getChildByTag(CARINCBUTTONTAG)))&&!(buttonlayer->isTap(em, buttonlayer->getChildByTag(MINEBUTTONTAG)))&& !(buttonlayer->isTap(em, buttonlayer->getChildByTag(EPOWERBUTTONTAG)))&& !(buttonlayer->isTap(em, buttonlayer->getChildByTag(BARRACKBUTTONTAG))))
		{
			buildingnum += 1;//����ͼ�Ͻ���������һ
			Vec2 position = location + repair;//��������������
			building*  Building;
            
            if(buttonlayer->buildchoice==1){
                Building = building::createWithBuildingType(Mine);
            }
            if(buttonlayer->buildchoice==2){
                Building = building::createWithBuildingType(Barrack);
            }
            if(buttonlayer->buildchoice==3){
                Building = building::createWithBuildingType(Epower);
            }
            if(buttonlayer->buildchoice==4){
                Building = building::createWithBuildingType(Carinc);
            }
			
			Building->setPosition(position);
            building::add_blood_bar(Building);
            buildings.pushBack(Building);
			addChild(Building);//���ﾫ���Tagֱ������Ϊ�����������ڹ���
            addChild(Building->progress);
            addChild(Building->bloodbar);
			//����������ӵ�������
			buttonlayer->updatemoney(buttonlayer->buildchoice);//��������Ǯ������
			buttonlayer->buildornot = false;//��Ҫ��Ҫ��������Ϊfalse
			buttonlayer->buildchoice = 0;
		}
		if (buttonlayer->buildornot == 2)
		{
           auto location = buildings.at(0)->getPosition();
			soldiernum += 1;
			auto bing = Soldier::create("soldier.png");
			bing->setPosition(location);
            Soldier::add_bloodbar(bing);
			addChild(bing);
            addChild(bing->blood);
            addChild(bing->progress);
			soldiers.pushBack(bing);
			buttonlayer->buildornot = 0;
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
void mymap::setmap(float delta)
{
	auto listener = EventListenerMouse::create();
	listener->onMouseMove = [this](Event *e) {
		EventMouse* em = (EventMouse*)e;
		auto location = em->getLocation();
		location.y = 900 - location.y;
		auto pos1 = this->getPosition();
		if (location.y >= 800)
		{
			Action*action = this->runAction(MoveTo::create(5000, Vec2(pos1.x, pos1.y - 1000)));
			action->setTag(1);
		}
		if (location.y <= 100 && location.y >= 50)
		{
			Action*action = this->runAction(MoveTo::create(5000, Vec2(pos1.x, pos1.y + 1000)));
			action->setTag(2);
		}
		else if (location.x <= 100 && location.x >= 50)
		{
			Action*action = this->runAction(MoveTo::create(5000, Vec2(pos1.x + 1000, pos1.y)));
			action->setTag(3);
		}
		else if (location.x >= 1500 && location.x <= 1550)
		{
			Action*action = this->runAction(MoveTo::create(5000, Vec2(pos1.x - 1000, pos1.y)));
			action->setTag(4);
		}
		if (location.y <= 800)
		{
			this->stopActionByTag(1);
			auto pos1 = this->getPosition();
			repair = originmap - pos1;
		}
		if (location.y >= 100 || location.y <= 50)
		{
			this->stopActionByTag(2);
			auto pos1 = this->getPosition();
			repair = originmap - pos1;
		}
		if (location.x >= 100 || location.x <= 50)
		{
			this->stopActionByTag(3);
			auto pos1 = this->getPosition();
			repair = originmap - pos1;
		}
		if (location.x <= 1500 || location.x >= 1550)
		{
			this->stopActionByTag(4);
			auto pos1 = this->getPosition();
			repair = originmap - pos1;
		}

	};
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
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
			float distance = (location).getDistance(otherlocation+repair);
			if (distance<100)
			{
				return false;
			}
		}
		return true;
	}
}


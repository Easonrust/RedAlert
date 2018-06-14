#include"map.h"
#include"button.h"
#include "building.h"
#include <iostream>
Vector<building*>buildings;//��������
Vec2 mouselocation;
bool mymap::init()
{
    if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	repair = Vec2(0, 0);//�ƶ���ͼ���ڵ�ͼ�Ͻ��쾫��ʱ�����������

	//�����ͼ
	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap, 0, MAPTAG);
	//���ݵ�ͼ�ļ��еĶ���㴴�����ض���
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("base");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
    auto base = building::createWithBuildingType(Mine);
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
	
}
void mymap::onEnter() {
	Layer::onEnter();
	log("mouseTouchEvent onEnter");

	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [this](Event *e) {
	};
	listener->onMouseUp = [this](Event *e) {
		EventMouse* em = (EventMouse*)e;
		auto location = em->getLocation();
        location = Director::getInstance()->convertToGL(location);//����������ת��Ϊ��������
		//���������������¼�
		if (buttonlayer->buildornot==1 && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(SOLDIERBUTTONTAG))) &&!(buttonlayer->isTap(em, buttonlayer->getChildByTag(CARINCBUTTONTAG)))&&!(buttonlayer->isTap(em, buttonlayer->getChildByTag(MINEBUTTONTAG)))&& !(buttonlayer->isTap(em, buttonlayer->getChildByTag(EPOWERBUTTONTAG)))&& !(buttonlayer->isTap(em, buttonlayer->getChildByTag(BARRACKBUTTONTAG))))
		{
			buildingnum += 1;//����ͼ�Ͻ���������һ
			Vec2 position = location + repair;//��������������
			building*  Building;
            cout <<buttonlayer->buildchoice<<endl;
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
			addChild(Building);//���ﾫ���Tagֱ������Ϊ�����������ڹ���
            addChild(Building->progress);
            addChild(Building->bloodbar);
			buildings.pushBack(Building);//����������ӵ�������
			buttonlayer->updatemoney(buttonlayer->buildchoice);//��������Ǯ������
			buttonlayer->buildornot = false;//��Ҫ��Ҫ��������Ϊfalse
			buttonlayer->buildchoice = 0;
		}
		if (buttonlayer->buildornot == 2)
		{
			auto location = buildings.at(0)->getPosition();
			soldiernum += 1;
			auto bing = Sprite::create("soldier.png");
			bing->setPosition(location);
			addChild(bing, 5, soldiernum*100);
			soldiers.pushBack(bing);
			float a = (bing->boundingBox().size.width)/2;
			auto body = PhysicsBody::createCircle(a);
			bing->setPhysicsBody(body);
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
void mymap::setmap(float delta )
{
	auto listener = EventListenerMouse::create();
	listener->onMouseMove = [this](Event *e) {
		EventMouse* em = (EventMouse*)e;
        auto location = em->getLocation();
        location = Director::getInstance()->convertToGL(location);
        auto pos = this->getPosition();
        std::cout << repair.x <<" "<<repair.y<<endl;
        if (location.y >= 850)
        {
            this->setPosition(Vec2(pos.x, pos.y - 0.05));
            repair.y += 0.05;
        }
        else if (location.y <= 50 )
        {
            this->setPosition(Vec2(pos.x, pos.y + 0.05));
            repair.y -= 0.05;
        }
        else if (location.x <= 50)
        {
            this->setPosition(Vec2(pos.x+0.05, pos.y));
            repair.x -= 0.05;
        }
        else if (location.x >= 1550)
        {
            this->setPosition(Vec2(pos.x-0.05, pos.y));
            repair.x += 0.05;
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

#include"map.h"
#include"button.h"
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
	base = building::create("base.png");
	base->setScale(0.15);//��ͼƬ����
	base->setPosition(Vec2(x, y));
	buildingnum += 1;//����ͼ��Ŀǰ�Ľ���������һ
	buildings.pushBack(base);//��������ӵ�������������

	//�������棬Ŀǰ�Ǿ��Σ����޸�ΪԲ�Σ��뾶������bug��������
	auto basebody = PhysicsBody::createBox(base->boundingBox().size);//boundingBox�ܻ�����ź���ͼƬ��С��getContentsize����
	base->setPhysicsBody(basebody);
	basebody->setRotationEnable(false);//���ò���ת
	basebody->setDynamic(false);//���ò��ᶯ
	addChild(base, 1, buildingnum);//������Tagֱ������Ϊ�����������ڹ���
	createblood(Vec2(x, y));
	schedule(schedule_selector(mymap::scheduleBlood), 0.1f);  //ˢ�º�����ÿ��0.1��
	schedule(schedule_selector(mymap::setmap), 0.1f);
	return true;
}
void mymap::createblood(Vec2 location)//Ѫ����������
{
	bloodnum += 1;
	auto sprite = Sprite::create("bar.png");   //�������ȿ�
	sprite->setPosition(Vec2(location.x, location.y + 65)); //���ÿ��λ��
	sprite->setScale(0.2);
	this->addChild(sprite,4,-bloodnum);            //�ӵ�Ĭ��ͼ������ȥ
	auto sprBlood = Sprite::create("blood.png");  //����Ѫ��
	ProgressTimer * progress = ProgressTimer::create(sprBlood); //����progress����
	progress->setType(ProgressTimer::Type::BAR);        //���ͣ���״
	progress->setPosition(Vec2(location.x, location.y + 65));
	progress->setScale(0.2);
	//���ҵ������Ѫ��
	progress->setMidpoint(Vec2(0, 0.5));     //����Ǵ����ҵĻ����ĳ�(1,0.5)����
	progress->setBarChangeRate(Vec2(1, 0));
	progress->setTag(bloodnum);       //��һ�����
	blood.pushBack(progress);
	this->addChild(progress,4,bloodnum);
}
//Ѫ��ˢ�º���
void mymap::scheduleBlood(float delta) {
	int num = 0;
	for (int i = 0; i < blood.size(); i++)
	{
		auto progress = (ProgressTimer *)this->getChildByTag(bloodnum);
		progress->setPercentage(buildings.at(i)->health/1000*100);  //�����ǰٷ�����ʾ
		if (progress->getPercentage() < 0) {
			num += 1;
		}
	}
	if (num >= blood.size())
	{
		this->unschedule(schedule_selector(mymap::scheduleBlood));
	}
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
		location.y = 900 - location.y;//����������ת��Ϊ��������
		//���������������¼�
		if (buttonlayer->buildornot==1 && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(SOLDIERBUTTONTAG))) &&!(buttonlayer->isTap(em, buttonlayer->getChildByTag(CARINCBUTTONTAG)))&&!(buttonlayer->isTap(em, buttonlayer->getChildByTag(MINEBUTTONTAG)))&& !(buttonlayer->isTap(em, buttonlayer->getChildByTag(EPOWERBUTTONTAG)))&& !(buttonlayer->isTap(em, buttonlayer->getChildByTag(BARRACKBUTTONTAG))))
		{
			buildingnum += 1;//����ͼ�Ͻ���������һ
			Vec2 position = location + repair;//��������������
			building*Building;
			switch (buttonlayer->buildchoice)
			{
			case 1:Building = building::create("mine.png");
				Building->setScale(0.4);//����
				break;
			case 2:Building = building::create("barrack.png");
				Building->setScale(0.35);//����
				barrackpos = position;
				break;
			case 3:Building = building::create("epower.png");
				Building->setScale(0.4);//����
				break;
			case 4:Building = building::create("carinc.png");
				Building->setScale(0.3);//����
				break;
			default:
				break;
			}
			Building->setPosition(position);
			float a =(Building->boundingBox().size.width )/ 2;
			auto body = PhysicsBody::createCircle(a);
			Building->setPhysicsBody(body);
			body->setRotationEnable(false);//���ò���ת
			body->setDynamic(false);//���ò��ᶯ
			addChild(Building, 3, buildingnum);//���ﾫ���Tagֱ������Ϊ�����������ڹ���
			buildings.pushBack(Building);//����������ӵ�������
			createblood(position);
			buttonlayer->updatemoney(buttonlayer->buildchoice);//��������Ǯ������
			buttonlayer->buildornot = false;//��Ҫ��Ҫ��������Ϊfalse
			buttonlayer->buildchoice = 0;
		}
		if (buttonlayer->buildornot == 2)
		{
			auto location = buildings.at(1)->getPosition();
			soldiernum += 1;
			auto bing = Sprite::create("soldier.png");
			bing->setPosition(location);
			addChild(bing, 5, soldiernum*100);
			soldiers.pushBack(bing);
			float a = (bing->boundingBox().size.width) / 2;
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
void mymap::setmap(float delta)
{
	auto listener = EventListenerMouse::create();
	listener->onMouseMove = [this](Event *e) {
		EventMouse* em = (EventMouse*)e;
		auto location = em->getLocation();
		location.y = 900 - location.y;
		auto pos = this->getPosition();
		if (location.y >= 800)
		{
			this->setPosition(Vec2(pos.x, pos.y - 0.05));
			repair.y += 0.05;
		}
		if (location.y <= 100&& location.y >=50 )
		{
			this->setPosition(Vec2(pos.x, pos.y + 0.05));
			repair.y -= 0.05;
		}
		else if (location.x <= 100&&location.x >= 50)
		{
			this->setPosition(Vec2(pos.x+0.05, pos.y));
			repair.x -= 0.05;
		}
		else if (location.x >= 1500&&location.x <= 1550)
		{
			this->setPosition(Vec2(pos.x-0.05, pos.y));
			repair.y += 0.05;
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
			float distance = (location).getDistance(otherlocation);
			if (distance<50)
			{
				return false;
			}
		}
		return true;
	}
}
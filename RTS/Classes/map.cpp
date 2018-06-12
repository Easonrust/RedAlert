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
	return true;
}
void mymap::createblood(Vec2 location)//Ѫ����������
{
	bloodnum += 1;
	auto sprite = Sprite::create("bar.png");   //�������ȿ�
	sprite->setPosition(Vec2(location.x, location.y + 65)); //���ÿ��λ��
	sprite->setScale(0.2);
	this->addChild(sprite);            //�ӵ�Ĭ��ͼ������ȥ
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
	this->addChild(progress);
}
//Ѫ��ˢ�º���
void mymap::scheduleBlood(float delta) {
	int num = 0;
	for (int i = 0; i < blood.size(); i++)
	{
		auto progress = (ProgressTimer *)this->getChildByTag(bloodnum);
		progress->setPercentage(50);  //�����ǰٷ�����ʾ
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
	listener->onMouseMove = [this](Event *e) {
		EventMouse* em = (EventMouse*)e;
		auto location = em->getLocation();
	};

	listener->onMouseUp = [this](Event *e) {
		EventMouse* em = (EventMouse*)e;
		auto location = em->getLocation();
		location.y = 900 - location.y;//����������ת��Ϊ��������
		//���������������¼�
		if (buttonlayer->buildornot == 1 && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(MINEBUTTONTAG)))&&canbuild(location))
		{

			buildingnum += 1;//����ͼ�Ͻ���������һ
			Vec2 position = location + repair;//��������������
			auto mine = building::create("mine.png");
			mine->setScale(0.4);//����
			mine->setPosition(position);
			float a =( mine->boundingBox().size.width )/ 2;
			auto body = PhysicsBody::createCircle(a);
			mine->setPhysicsBody(body);
			body->setRotationEnable(false);//���ò���ת
			body->setDynamic(false);//���ò��ᶯ
			addChild(mine, 3, buildingnum);//���ﾫ���Tagֱ������Ϊ�����������ڹ���
			buildings.pushBack(mine);//����������ӵ�������
			createblood(position);
			buttonlayer->buildornot = false;//��Ҫ��Ҫ��������Ϊfalse
		}

		//��ť�ƶ���ͼ�ĺ�����Ҫͬʱ���������������иı�
		if (buttonlayer->set)
		{
			if (buttonlayer->set == 1)
			{

				float up = this->getPositionY() - 50;
				this->setPositionY(up);
				repair.y += 50;
			}
			else if (buttonlayer->set == 2)
			{
				float down = this->getPositionY() + 50;
				this->setPositionY(down);
				repair.y -= 50;
			}
			else if (buttonlayer->set == 3)
			{
				float left = this->getPositionX() + 50;
				this->setPositionX(left);
				repair.x -= 50;
			}
			else if (buttonlayer->set == 4)
			{
				float right = this->getPositionX() - 50;
				this->setPositionX(right);
				repair.x += 50;
			}
			buttonlayer->set = 0;
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
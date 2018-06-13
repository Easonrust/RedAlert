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

	repair = Vec2(0, 0);//移动地图后，在地图上建造精灵时坐标的修正量

	//导入地图
	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap, 0, MAPTAG);
	//根据地图文件中的对象层创建基地对象
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("base");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	base = building::create("base.png");
	base->setScale(0.15);//将图片缩放
	base->setPosition(Vec2(x, y));
	buildingnum += 1;//将地图上目前的建筑总数加一
	buildings.pushBack(base);//将基地添加到建筑物容器中

	//物理引擎，目前是矩形，可修改为圆形，半径调控有bug。。。。
	auto basebody = PhysicsBody::createBox(base->boundingBox().size);//boundingBox能获得缩放后精灵图片大小，getContentsize不能
	base->setPhysicsBody(basebody);
	basebody->setRotationEnable(false);//设置不会转
	basebody->setDynamic(false);//设置不会动
	addChild(base, 1, buildingnum);//建筑的Tag直接设置为建筑总数便于管理
	createblood(Vec2(x, y));
	schedule(schedule_selector(mymap::scheduleBlood), 0.1f);  //刷新函数，每隔0.1秒
	schedule(schedule_selector(mymap::setmap), 0.1f);
	return true;
}
void mymap::createblood(Vec2 location)//血条创建函数
{
	bloodnum += 1;
	auto sprite = Sprite::create("bar.png");   //创建进度框
	sprite->setPosition(Vec2(location.x, location.y + 65)); //设置框的位置
	sprite->setScale(0.2);
	this->addChild(sprite,4,-bloodnum);            //加到默认图层里面去
	auto sprBlood = Sprite::create("blood.png");  //创建血条
	ProgressTimer * progress = ProgressTimer::create(sprBlood); //创建progress对象
	progress->setType(ProgressTimer::Type::BAR);        //类型：条状
	progress->setPosition(Vec2(location.x, location.y + 65));
	progress->setScale(0.2);
	//从右到左减少血量
	progress->setMidpoint(Vec2(0, 0.5));     //如果是从左到右的话，改成(1,0.5)即可
	progress->setBarChangeRate(Vec2(1, 0));
	progress->setTag(bloodnum);       //做一个标记
	blood.pushBack(progress);
	this->addChild(progress,4,bloodnum);
}
//血量刷新函数
void mymap::scheduleBlood(float delta) {
	int num = 0;
	for (int i = 0; i < blood.size(); i++)
	{
		auto progress = (ProgressTimer *)this->getChildByTag(bloodnum);
		progress->setPercentage(buildings.at(i)->health/1000*100);  //这里是百分制显示
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
		location.y = 900 - location.y;//将鼠标的坐标转换为世界坐标
		//基本创建建筑的事件
		if (buttonlayer->buildornot==1 && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(SOLDIERBUTTONTAG))) &&!(buttonlayer->isTap(em, buttonlayer->getChildByTag(CARINCBUTTONTAG)))&&!(buttonlayer->isTap(em, buttonlayer->getChildByTag(MINEBUTTONTAG)))&& !(buttonlayer->isTap(em, buttonlayer->getChildByTag(EPOWERBUTTONTAG)))&& !(buttonlayer->isTap(em, buttonlayer->getChildByTag(BARRACKBUTTONTAG))))
		{
			buildingnum += 1;//将地图上建筑总数加一
			Vec2 position = location + repair;//修正量起作用了
			building*Building;
			switch (buttonlayer->buildchoice)
			{
			case 1:Building = building::create("mine.png");
				Building->setScale(0.4);//缩放
				break;
			case 2:Building = building::create("barrack.png");
				Building->setScale(0.35);//缩放
				barrackpos = position;
				break;
			case 3:Building = building::create("epower.png");
				Building->setScale(0.4);//缩放
				break;
			case 4:Building = building::create("carinc.png");
				Building->setScale(0.3);//缩放
				break;
			default:
				break;
			}
			Building->setPosition(position);
			float a =(Building->boundingBox().size.width )/ 2;
			auto body = PhysicsBody::createCircle(a);
			Building->setPhysicsBody(body);
			body->setRotationEnable(false);//设置不会转
			body->setDynamic(false);//设置不会动
			addChild(Building, 3, buildingnum);//这里精灵的Tag直接设置为建筑总数便于管理
			buildings.pushBack(Building);//将建筑物添加到容器中
			createblood(position);
			buttonlayer->updatemoney(buttonlayer->buildchoice);//购买后更新钱数更新
			buttonlayer->buildornot = false;//将要不要建建筑设为false
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
			float distance = (location).getDistance(otherlocation);
			if (distance<50)
			{
				return false;
			}
		}
		return true;
	}
}
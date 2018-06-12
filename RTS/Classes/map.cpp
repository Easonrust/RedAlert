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
	return true;
}
void mymap::createblood(Vec2 location)//血条创建函数
{
	bloodnum += 1;
	auto sprite = Sprite::create("bar.png");   //创建进度框
	sprite->setPosition(Vec2(location.x, location.y + 65)); //设置框的位置
	sprite->setScale(0.2);
	this->addChild(sprite);            //加到默认图层里面去
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
	this->addChild(progress);
}
//血量刷新函数
void mymap::scheduleBlood(float delta) {
	int num = 0;
	for (int i = 0; i < blood.size(); i++)
	{
		auto progress = (ProgressTimer *)this->getChildByTag(bloodnum);
		progress->setPercentage(50);  //这里是百分制显示
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
		location.y = 900 - location.y;//将鼠标的坐标转换为世界坐标
		//基本创建建筑的事件
		if (buttonlayer->buildornot == 1 && !(buttonlayer->isTap(em, buttonlayer->getChildByTag(MINEBUTTONTAG)))&&canbuild(location))
		{

			buildingnum += 1;//将地图上建筑总数加一
			Vec2 position = location + repair;//修正量起作用了
			auto mine = building::create("mine.png");
			mine->setScale(0.4);//缩放
			mine->setPosition(position);
			float a =( mine->boundingBox().size.width )/ 2;
			auto body = PhysicsBody::createCircle(a);
			mine->setPhysicsBody(body);
			body->setRotationEnable(false);//设置不会转
			body->setDynamic(false);//设置不会动
			addChild(mine, 3, buildingnum);//这里精灵的Tag直接设置为建筑总数便于管理
			buildings.pushBack(mine);//将建筑物添加到容器中
			createblood(position);
			buttonlayer->buildornot = false;//将要不要建建筑设为false
		}

		//按钮移动地图的函数，要同时对坐标修正量进行改变
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
#include"map.h"
#include"button.h"
bool map::init()
{
	if (!Layer::init())
	{
		return false;
	}
	repair = Vec2(0, 0);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap, 0, 100);
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("base");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	 base = Sprite::create("base.png");
	 base->setScale(0.15, 0.15);
	 base->setPosition(Vec2(x, y));
	addChild(base, 2, 200);
	//setViewpointCenter(base->getPosition());

	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(false);
	return true;
}
void map::onEnter() {
	Layer::onEnter();
	log("mouseTouchEvent onEnter");

	auto listener = EventListenerMouse::create();
	listener->onMouseMove = [](Event *e) {
		EventMouse* em = (EventMouse*)e;
		//nothing
	};

	listener->onMouseUp = [this](Event *e) {
		EventMouse* em = (EventMouse*)e;
		auto location = em->getLocation();
		location.y = 900 - location.y;
		if (buttonlayer->buildornot == 1&&!(buttonlayer->isTap(em,buttonlayer->getChildByTag(MINEBUTTONTAG)))  )
		{
			Sprite*mine = Sprite::create("mine.png");
			mine->setScale(0.4, 0.4);
			mine->setPosition(location+repair);
			addChild(mine, 3, 400);
			buttonlayer->buildornot = 0;
		}
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
		//this->setViewpointCenter(location);
	};
	listener->onMouseDown = [](Event *e) {
		EventMouse* em = (EventMouse*)e;
		//nothing
	};

	listener->onMouseScroll = [](Event *e) {
		EventMouse* em = (EventMouse*)e;
		//nothing

	};

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void map::onExit() {
	Layer::onExit();
	log("mouseTouchEvent onExit");
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}
	
/*void map::setViewpointCenter(Vec2 position)
{
	log("setViewpointCenter");

	log("position (%f ,%f) ", position.x, position.y);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//���Է�ֹ����ͼ��߳�����Ļ֮�⡣
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	
	//���Է�ֹ����ͼ�ұ߳�����Ļ֮�⡣
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
		- visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
		- visibleSize.height / 2);

	//��Ļ���ĵ�
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//ʹ���鴦����Ļ���ģ��ƶ���ͼĿ��λ��
	Vec2 pointB = Vec2(x, y);
	log("Ŀ��λ�� (%f ,%f) ", pointB.x, pointB.y);

	//��ͼ�ƶ�ƫ����
	Vec2 offset = pointA - pointB;
	log("offset (%f ,%f) ", offset.x, offset.y);
	this->setPosition(offset);
}*/
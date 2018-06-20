#include"building.h"
void building::add_blood_bar(building* spr) {
	spr->blood = Sprite::create("bar.png");   //创建进度框
	spr->blood->setPosition(Vec2(spr->getPositionX(), spr->getPositionY() + 65)); //设置框的位置
	spr->blood->setScale(0.2);
	auto blood = Sprite::create("blood.png");  //创建血条
	spr->progress = ProgressTimer::create(blood); //创建progress对象
	spr->progress->setType(ProgressTimer::Type::BAR);        //类型：条状
	spr->progress->setPosition(Vec2(spr->getPositionX(), spr->getPositionY() + 65));
	spr->progress->setScale(0.2);
	spr->progress->setPercentage(100);
	//从右到左减少血量
	spr->progress->setMidpoint(Vec2(0, 0.5));     //如果是从左到右的话，改成(1,0.5)即可
	spr->progress->setBarChangeRate(Vec2(1, 0));
}

building* building::createWithBuildingType(Building_type building_type)
{
	building*sprite = new building();
	switch (building_type) {
	case Base:
		sprite->building_r = 180;
		sprite->building_health = 1000;
		sprite->originhealth = 1000;
		break;
	case Mine:
		sprite->building_r = 180;
		sprite->building_health = 1000;
		sprite->originhealth = 1000;
		break;
	case Epower:
		sprite->building_r = 250;
		sprite->building_health = 1000;
		sprite->originhealth = 1000;
		break;
	case Barrack:
		sprite->building_r = 250;
		sprite->building_health = 1000;
		sprite->originhealth = 1000;
		break;
	case Carinc:
		sprite->building_r = 250;
		sprite->building_health = 1000;
		sprite->originhealth = 1000;
		break;
	default:
		break;
	}
	if (sprite && building_type == Base &&sprite->initWithFile("base.png"))
	{
		sprite->autorelease();//将精灵放入内存自动池中
		sprite->setScale(0.10);
		auto body = PhysicsBody::create();
		body->addShape(PhysicsShapeCircle::create(sprite->building_r));

		body->setRotationEnable(false);
		body->setDynamic(false);
		sprite->setPhysicsBody(body);
		return sprite;
	}
	if (sprite && building_type == Mine &&sprite->initWithFile("mine.png"))
	{
		sprite->autorelease();//将精灵放入内存自动池中
		sprite->setScale(0.3);
		auto body = PhysicsBody::create();
		body->addShape(PhysicsShapeCircle::create(sprite->building_r));

		body->setRotationEnable(false);
		body->setDynamic(false);
		sprite->setPhysicsBody(body);
		return sprite;
	}
	if (sprite && building_type == Barrack &&sprite->initWithFile("barrack.png"))
	{
		sprite->autorelease();//将精灵放入内存自动池中
		sprite->setScale(0.15);
		auto body = PhysicsBody::create();
		body->addShape(PhysicsShapeCircle::create(sprite->building_r));

		body->setRotationEnable(false);
		body->setDynamic(false);
		sprite->setPhysicsBody(body);
		return sprite;
	}
	if (sprite && building_type == Epower &&sprite->initWithFile("epower.png"))
	{
		sprite->autorelease();//将精灵放入内存自动池中
		sprite->setScale(0.15);
		auto body = PhysicsBody::create();
		body->addShape(PhysicsShapeCircle::create(sprite->building_r));

		body->setRotationEnable(false);
		body->setDynamic(false);
		sprite->setPhysicsBody(body);
		return sprite;
	}
	if (sprite && building_type == Carinc &&sprite->initWithFile("carinc.png"))
	{
		sprite->autorelease();//将精灵放入内存自动池中
		sprite->setScale(0.15);
		auto body = PhysicsBody::create();
		body->addShape(PhysicsShapeCircle::create(sprite->building_r));

		body->setRotationEnable(false);
		body->setDynamic(false);
		sprite->setPhysicsBody(body);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void building::judge_selected(Vector<building*> vec, Vec2 down, Vec2 up) {
	if (up == down) {
		for (int i = 0; i<vec.size(); i++) {
			auto p = vec.at(i)->getPosition();  //GL
			if (isTap(down, vec.at(i))) {
				vec.at(i)->selected = 1;
				vec.at(i)->blood->setVisible(true);
				vec.at(i)->progress->setVisible(true);
			}
		}
	}
	if (up != down) {
		float x_min = fmin(up.x, down.x);
		float x_max = fmax(up.x, down.x);
		float y_min = fmin(up.y, down.y);
		float y_max = fmax(up.y, down.y);
		for (int i = 0; i<vec.size(); i++) {
			auto p = vec.at(i)->getPosition();
			if (p.x >= x_min&& p.x <= x_max&&p.y >= y_min&& p.y <= y_max) {
				vec.at(i)->blood->setVisible(true);
				vec.at(i)->progress->setVisible(true);
				vec.at(i)->selected = 1;
			}
		}
	}
}
 bool building:: isTap(cocos2d::Vec2 location, cocos2d::Node*node)//判断是否点中精灵的函数
{
	Vec2 locationInNode = node->convertToNodeSpace(location);
	Size s = node->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.width);
	if (rect.containsPoint(locationInNode))
	{
		return true;
	}
	return false;
}
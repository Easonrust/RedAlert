#include"building.h"
void building::add_blood_bar(building* spr) {
	spr->bloodbar = Sprite::create("bar.png");   //创建进度框
	spr->bloodbar->setPosition(Vec2(spr->getPositionX(), spr->getPositionY() + 65)); //设置框的位置
	spr->bloodbar->setScale(0.2);
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
		sprite->building_r = 75;
		sprite->building_health = 1000;
		break;
	case Mine:
		sprite->building_r = 75;
		sprite->building_health = 1000;
		break;
	case Epower:
		sprite->building_r = 75;
		sprite->building_health = 1000;
		break;
	case Barrack:
		sprite->building_r = 75;
		sprite->building_health = 1000;
		break;
	case Carinc:
		sprite->building_r = 75;
		sprite->building_health = 1000;
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
		return sprite;
	}
	if (sprite && building_type == Mine &&sprite->initWithFile("mine.png"))
	{
		sprite->autorelease();//将精灵放入内存自动池中
		sprite->setScale(0.15);
		auto body = PhysicsBody::create();
		body->addShape(PhysicsShapeCircle::create(sprite->building_r));

		body->setRotationEnable(false);
		body->setDynamic(false);
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
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void building::judge_seleted(Vector<building*>vec, Vec2 mouse_down, Vec2 mouse_up)
{
	if (mouse_up == mouse_down)
	{
		for (int i = 0; i < vec.size(); i++) {
			auto node = vec.at(i)->buildingnode;
			//auto location = vec[i]->getPosition();//世界坐标
			//auto p_size = vec[i]->getContentSize();
			if (isTap(mouse_down, node))//检查是否点到图片上,运用了自定义的函数isTap
			{
				vec.at(i)->Selected = 1;
			}
		}
	}
	if (mouse_up != mouse_down)
	{
		float x_min = min(mouse_up.x, mouse_down.x);
		float x_max = max(mouse_up.x, mouse_down.x);
		float y_min = min(mouse_up.y, mouse_down.y);
		float y_max = max(mouse_up.y, mouse_down.y);
		for (int i = 0; i < vec.size(); i++)
		{
			auto location = vec.at(i)->getPosition();//世界坐标
			if (location.x >= x_min&&location.x <= x_max&& location.y >= y_min && location.y <= y_max)//这里没有考虑图片大小，觉得需要优化
			{
				vec.at(i)->Selected = 1;
			}
		}
	}
}
void building::clear(Vector<building*>vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		vec.at(i)->Selected = 0;
		//血条消失
	}
}
bool building::isTap(cocos2d::Vec2 mouselocation, cocos2d::Node*node)
{

	//location1.y = 900 - location1.y;
	Vec2 locationInNode = node->convertToNodeSpace(mouselocation);
	Size s = node->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.width);
	if (rect.containsPoint(locationInNode))
	{
		return true;
	}
	return false;
}
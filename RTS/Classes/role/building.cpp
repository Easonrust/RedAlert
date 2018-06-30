#include"building.h"
void building::add_blood_bar(building* spr) {
	spr->blood = Sprite::create("bar.png");   //�������ȿ�
	spr->blood->setPosition(Vec2(spr->getPositionX(), spr->getPositionY() + 65)); //���ÿ��λ��
	spr->blood->setScale(0.2);
	auto blood = Sprite::create("blood.png");  //����Ѫ��
	spr->progress = ProgressTimer::create(blood); //����progress����
	spr->progress->setType(ProgressTimer::Type::BAR);        //���ͣ���״
	spr->progress->setPosition(Vec2(spr->getPositionX(), spr->getPositionY() + 65));
	spr->progress->setScale(0.2);
	spr->progress->setPercentage(100);
	
	//���ҵ������Ѫ��
	spr->progress->setMidpoint(Vec2(0, 0.5));     //����Ǵ����ҵĻ����ĳ�(1,0.5)����
	spr->progress->setBarChangeRate(Vec2(1, 0));
}

building* building::createWithBuildingType(Building_type building_type)
{
	building*sprite = new building();
	switch (building_type) {
	case Base:
		sprite->building_health = 3000;
		sprite->originhealth = 3000;
        
		break;
	case Mine:
		sprite->building_health = 2000;
		sprite->originhealth = 2000;
        
		break;
	case Epower:
		sprite->building_health = 1200;
		sprite->originhealth = 1200;
        
		break;
	case Barrack:
		sprite->building_health = 1400;
		sprite->originhealth = 1400;
        
		break;
	case Carinc:
		sprite->building_health = 1900;
		sprite->originhealth = 1900;
	case Wall:
		sprite->building_health = 300;
		sprite->originhealth = 300;
		break;
	default:
		break;
	}
	if (sprite && building_type == Base &&sprite->initWithFile("base.png"))
	{
		sprite->autorelease();//����������ڴ��Զ�����
		auto body = PhysicsBody::create();
		Size s = sprite->getContentSize();
		body->addShape(PhysicsShapeCircle::create(s.width / 2));

		body->setRotationEnable(false);
		body->setDynamic(false);
		sprite->setPhysicsBody(body);
		return sprite;
	}
	if (sprite && building_type == Mine &&sprite->initWithFile("m4.png"))
	{
		sprite->autorelease();//����������ڴ��Զ�����
		auto body = PhysicsBody::create();
		Size s = sprite->getContentSize();
		body->addShape(PhysicsShapeCircle::create(s.width / 2));

		body->setRotationEnable(false);
		body->setDynamic(false);
		sprite->setPhysicsBody(body);
		return sprite;
	}
	if (sprite && building_type == Barrack &&sprite->initWithFile("b4.png"))
	{
		sprite->autorelease();//����������ڴ��Զ�����
		auto body = PhysicsBody::create();
		Size s = sprite->getContentSize();
		body->addShape(PhysicsShapeCircle::create(s.width/2));

		body->setRotationEnable(false);
		body->setDynamic(false);
		sprite->setPhysicsBody(body);
		return sprite;
	}
	if (sprite && building_type == Epower &&sprite->initWithFile("e4.png"))
	{
		sprite->autorelease();//����������ڴ��Զ�����
		auto body = PhysicsBody::create();
		Size s = sprite->getContentSize();
		body->addShape(PhysicsShapeCircle::create(s.width / 2));

		body->setRotationEnable(false);
		body->setDynamic(false);
		sprite->setPhysicsBody(body);
		return sprite;
	}
	if (sprite && building_type == Carinc &&sprite->initWithFile("c4.png"))
	{
		sprite->autorelease();//����������ڴ��Զ�����
		auto body = PhysicsBody::create();
		Size s = sprite->getContentSize();
		body->addShape(PhysicsShapeCircle::create(s.width / 2));

		body->setRotationEnable(false);
		body->setDynamic(false);
		sprite->setPhysicsBody(body);
		return sprite;
	}
	if (sprite && building_type == Wall &&sprite->initWithFile("wall.png"))
	{
		sprite->autorelease();//����������ڴ��Զ�����
		auto body = PhysicsBody::create();
		Size s = sprite->getContentSize();
		body->addShape(PhysicsShapeCircle::create(s.width / 2));

		body->setRotationEnable(false);
		body->setDynamic(false);
		sprite->setPhysicsBody(body);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
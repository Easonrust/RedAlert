#ifndef __SOLDIER_H__
#define __SOLDIER_H__
#define soldier_human "soldier.png"
#define soldier_robot "robot.png"
#define soldier_tank "tank.png"
#include "cocos2d.h"
#include"building.h"
#include <algorithm>
USING_NS_CC;
typedef enum {
	human = 0,
	robot = 1,
	tank = 2,
}soldier_type;
class Soldier : public Sprite {

public:
	Sprite*sprite = nullptr;
	float health = 0;
	float originhealth = 0;
	int atk = 0;
	bool selected = 0;
	bool isrun = 0;
	bool isattack = 0;
	int collide_r = 16;
	Soldier* s_enemy = nullptr;
	building* b_enemy = nullptr;
	Sprite* blood;
	ProgressTimer* progress;
	static bool isTap(cocos2d::Vec2 location, cocos2d::Node*node)//判断是否点中精灵的函数
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
	static Soldier* createwithsoldiertype(soldier_type type)
	{
		Soldier* sprite = new Soldier();
		switch (type)
		{
		case human:
			sprite->health = 100;
			sprite->originhealth = 100;
			sprite->atk = 1;
			break;
		case robot:
			sprite->health = 200;
			sprite->originhealth = 200;
			sprite->atk = 10;
			break;
		case tank:
			sprite->health = 500;
			sprite->originhealth = 500;
			sprite->atk = 10;
			break;
		default:
			break;
		}
		if (sprite && type == human &&sprite->initWithFile("soldier.png"))
		{
			sprite->autorelease();//将精灵放入内存自动池中
			sprite->setScale(0.7);
			auto body = PhysicsBody::create();
			body->addShape(PhysicsShapeCircle::create(16));

			body->setRotationEnable(true);
			body->setDynamic(true);
			sprite->setPhysicsBody(body);
			return sprite;
		}
		if (sprite && type == robot &&sprite->initWithFile("robot.png"))
		{
			sprite->autorelease();//将精灵放入内存自动池中
			sprite->setScale(0.6);
			auto body = PhysicsBody::create();
			body->addShape(PhysicsShapeCircle::create(30));

			body->setRotationEnable(true);
			body->setDynamic(true);
			sprite->setPhysicsBody(body);
			return sprite;
		}
		if (sprite && type == tank &&sprite->initWithFile("tank.png"))
		{
			sprite->autorelease();//将精灵放入内存自动池中
			sprite->setScale(0.3);
			auto body = PhysicsBody::create();
			body->addShape(PhysicsShapeCircle::create(100));

			body->setRotationEnable(true);
			body->setDynamic(true);
			sprite->setPhysicsBody(body);
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	/*static Soldier* create(char*filename)
	{
		Soldier* sprite = new Soldier();
		if (sprite&&sprite->initWithFile(filename))
		{
			sprite->autorelease();//将精灵放入内存自动池中
			sprite->setScale(0.7);
			auto body = PhysicsBody::create();
			body->addShape(PhysicsShapeCircle::create(16));

			body->setRotationEnable(true);
			body->setDynamic(true);
			sprite->setPhysicsBody(body);
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}*/
	static void run(Vector<Soldier*> vec, Vec2 target) {
		for (int i = 0; i<vec.size(); i++) {
			if (vec.at(i)->selected) {
				vec.at(i)->isrun = 1;
			}
			auto pos = vec.at(i)->getPosition();
			auto distance = pos.getDistance(target);
			if (vec.at(i)->isrun == 1)
			{
				vec.at(i)->stopAllActions();
				vec.at(i)->isattack = 0;
				//vec.at(i)->s_enemy = nullptr;
				//vec.at(i)->b_enemy = nullptr;
				vec.at(i)->runAction(MoveTo::create(distance / 30, target));
				if (target.x > pos.x)
				{
					vec.at(i)->runAction(FlipX::create(true));
				}
				else
				{
					vec.at(i)->runAction(FlipX::create(false));
				}
			}
		}
	}
	static void judge_selected(Vector<Soldier*> vec, Vec2 down, Vec2 up) {
		if (up == down) {
			for (int i = 0; i<vec.size(); i++) {
				auto p = vec.at(i)->getPosition();  //GL
				if (isTap(down, vec.at(i))) {
					//vec.erase(vec.begin()+i);
					//vec[i]->removeFromParentAndCleanup(true);
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
	static void clear(Vector<Soldier*> vec) {
		for (int i = 0; i<vec.size(); i++) {
			vec.at(i)->selected = 0;
			vec.at(i)->isrun = 0;
			vec.at(i)->blood->setVisible(false);
			vec.at(i)->progress->setVisible(false);
		}
	}

	void shelduleAttack(Vector<Soldier*> vec, Vector<Soldier*> enemy, Vec2 target) {
		for (int i = 0; i<enemy.size(); i++) {
			auto p = enemy.at(i)->getPosition();  //GL
			if (p.x - 8 <= target.x && p.x + 8 >= target.x && p.y - 8 <= target.y && p.y + 8 >= target.y) {
				enemy.at(i)->selected = 1;
				enemy.at(i)->blood->setVisible(true);
				enemy.at(i)->progress->setVisible(true);
			}
		}
	}
	static void add_bloodbar(Soldier* spr) {
		spr->blood = Sprite::create("bar.png");   //¥¥Ω®Ω¯∂»øÚ
		spr->blood->setPosition(Vec2(spr->getPositionX(), spr->getPositionY() + 30)); //…Ë÷√øÚµƒŒª÷√
		spr->blood->setScale(0.05);
		spr->blood->setVisible(false);
		spr->progress = ProgressTimer::create(Sprite::create("blood.png")); //¥¥Ω®progress∂‘œÛ
		spr->progress->setType(ProgressTimer::Type::BAR);        //¿‡–Õ£∫Ãı◊¥
		spr->progress->setPosition(Vec2(spr->getPositionX(), spr->getPositionY() + 30));
		spr->progress->setScale(0.05);
		//¥””“µΩ◊Ûºı…Ÿ—™¡ø
		spr->progress->setMidpoint(Vec2(0, 0.5));     //»Áπ˚ «¥”◊ÛµΩ”“µƒª∞£¨∏ƒ≥…(1,0.5)º¥ø…
		spr->progress->setBarChangeRate(Vec2(1, 0));
		spr->progress->setPercentage(100);
		spr->progress->setVisible(false);
	}
	static void attacksoldier(Vector<Soldier*> vec, Vector<Soldier*> enemy, Vec2 target) {
		int a = 0;
		for (int i = 0; i<enemy.size(); i++) {
			if (isTap(target, enemy.at(i))) {
				a = i;
				break;
			}
		}
		for (int i = 0; i<vec.size(); i++) {
			if (vec.at(i)->selected) {
				vec.at(i)->s_enemy = enemy.at(a);
				vec.at(i)->b_enemy = nullptr;
				vec.at(i)->isattack = 1;
			}
		}
	}
	static void attackbuilding(Vector<Soldier*> vec, Vector<building*> enemy, Vec2 target) {
		int a = 0;
		for (int i = 0; i<enemy.size(); i++) {
			if (isTap(target, enemy.at(i)))
			{
				a = i;
				break;
			}
		}
		for (int i = 0; i<vec.size(); i++) {
			if (vec.at(i)->selected) {
				if (vec.at(i)->b_enemy)
				{
					vec.at(i)->b_enemy = nullptr;
				}
				vec.at(i)->b_enemy = enemy.at(a);
				vec.at(i)->s_enemy = nullptr;
				vec.at(i)->isattack = 1;
			}
		}
	}
};


#endif 

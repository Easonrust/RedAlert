#ifndef __SOLDIER_H__
#define __SOLDIER_H__
#include "cocos2d.h"
#include <algorithm>
USING_NS_CC;
class Soldier : public Sprite {

public:
	int health = 100;
	bool selected = 0;
	bool isrun = 0;
	int collide_r = 16;
	Sprite* blood;
	ProgressTimer* progress;
	static Soldier* create(const char* filename)
	{
		Soldier* sprite = new Soldier();
		if (sprite && sprite->initWithFile("soldier.png"))
		{
			sprite->autorelease();
			auto body = PhysicsBody::create();
			sprite->setScale(0.5);
			body->addShape(PhysicsShapeCircle::create(sprite->collide_r));
			body->setRotationEnable(true);
			body->setDynamic(true);

			sprite->setPhysicsBody(body);
			return sprite;
		}
	}

	static void run(Vector<Soldier*> vec, Vec2 target, float delta) {
		for (int i = 0; i<vec.size(); i++) {
			if (vec.at(i)->selected) {
				vec.at(i)->isrun = 1;
			}
		}
		//scheduler(schedule_selector(Soldier::scheduleRun), vec,target,delta);
	}

	static void scheduleRun(Vector<Soldier*> vec, Vec2 target, float delta) {
		for (int i = 0; i<vec.size(); i++) {
			if (vec.at(i)->isrun) {
				auto position = vec.at(i)->getPosition();
				position = Director::getInstance()->convertToGL(position);
				if ((position).getDistance(target) <= 1) {
					vec.at(i)->isrun = 0;
					//unscheduler(schedule_selector(Soldier::scheduleRun), vec,target,delta);
				}
				else {
					float x = 2 / (target.x - position.x);
					float y = 2 / (target.y - position.y);
					vec.at(i)->setPosition(position.x + x, position.y + y);
				}
			}
		}

	}
	static void scheduleRunToAttcak(Vector<Soldier*> vec, Vec2 target, float delta) {
		for (int i = 0; i<vec.size(); i++) {
			if (vec.at(i)->isrun) {
				auto position = vec.at(i)->getPosition();
				position = Director::getInstance()->convertToGL(position);
				if ((position).getDistance(target) <= 200) {
					vec.at(i)->isrun = 0;
					//unscheduler(schedule_selector(Soldier::scheduleRunToAttack), vec,target,delta);
					//scheduler(schedule_selector(Soldier::shelduleAttack), vec,target,delta);
				}
				else {
					auto distance = position.getDistance(target);
					float x = 2 * (target.x - position.x) / distance;
					float y = 2 * (target.y - position.y) / distance;
					vec.at(i)->setPosition(position.x + x, position.y + y);
				}
			}
		}
	}
	static bool judge_selected(Vector<Soldier*> vec, Vec2 down, Vec2 up) {
		bool isselected = 0;
		if (up == down) {
			for (int i = 0; i<vec.size(); i++) {
				auto p = vec.at(i)->getPosition();  //GL
				if (p.x - 16 <= down.x && p.x + 16 >= down.x && p.y - 16 <= down.y && p.y + 16 >= down.y) {
					//vec.erase(vec.begin()+i);
					//vec[i]->removeFromParentAndCleanup(true);
					vec.at(i)->selected = 1;
					vec.at(i)->blood->setVisible(true);
					vec.at(i)->progress->setVisible(true);
					isselected = 1;
				}
			}
		}
		if (up != down) {
			float x_min = fmin(up.x, down.x);
			float x_max = fmax(up.x, down.x);
			float y_min = fmin(up.x, down.x);
			float y_max = fmax(up.x, down.x);
			for (int i = 0; i<vec.size(); i++) {
				auto p = vec.at(i)->getPosition();
				if (p.x >= x_min&& p.x <= x_max&&p.y >= y_min&& p.y <= y_max) {
					vec.at(i)->blood->setVisible(true);
					vec.at(i)->progress->setVisible(true);
					vec.at(i)->selected = 1;
					isselected = 1;
				}
			}
		}
		return isselected;
	}
	static void clear(Vector<Soldier*> vec) {
		for (int i = 0; i<vec.size(); i++) {
			vec.at(i)->selected = 0;
			vec.at(i)->blood->setVisible(false);
			vec.at(i)->progress->setVisible(false);
		}
	}
	static void attack(Vector<Soldier*> vec, Vector<Soldier*> enemy, float delta) {}
	void shelduleAttack(Vector<Soldier*> vec, Vector<Soldier*> enemy, Vec2 target) {
		for (int i = 0; i<enemy.size(); i++) {
			auto p = enemy.at(i)->getPosition();  //GL
			if (p.x - 16 <= target.x && p.x + 16 >= target.x && p.y - 16 <= target.y && p.y + 16 >= target.y) {
				enemy.at(i)->selected = 1;
				enemy.at(i)->blood->setVisible(true);
				enemy.at(i)->progress->setVisible(true);
			}
		}
	}
	static void add_bloodbar(Soldier* spr) {
		spr->blood = Sprite::create("bar.png");   //¥¥Ω®Ω¯∂»øÚ
		spr->blood->setPosition(Vec2(spr->getPositionX(), spr->getPositionY() + 16)); //…Ë÷√øÚµƒŒª÷√
		spr->blood->setScale(0.1);
		spr->blood->setVisible(false);
		spr->progress = ProgressTimer::create(Sprite::create("blood.png")); //¥¥Ω®progress∂‘œÛ
		spr->progress->setType(ProgressTimer::Type::BAR);        //¿‡–Õ£∫Ãı◊¥
		spr->progress->setPosition(Vec2(spr->getPositionX(), spr->getPositionY() + 16));
		spr->progress->setScale(0.1);
		//¥””“µΩ◊Ûºı…Ÿ—™¡ø
		spr->progress->setMidpoint(Vec2(0, 0.5));     //»Áπ˚ «¥”◊ÛµΩ”“µƒª∞£¨∏ƒ≥…(1,0.5)º¥ø…
		spr->progress->setBarChangeRate(Vec2(1, 0));
		spr->progress->setPercentage(100);
		spr->progress->setVisible(false);
	}
};


#endif 

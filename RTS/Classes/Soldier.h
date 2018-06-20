#ifndef __SOLDIER_H__
#define __SOLDIER_H__
#include "cocos2d.h"
#include <algorithm>
USING_NS_CC;
class Soldier : public Sprite {

public:
	int health = 100;
    int attacker = 0;
	bool selected = 0;
	bool isrun = 0;
    bool isattack = 0;
	int collide_r = 16;
    Soldier* a_enemy = nullptr;
	Sprite* blood;
	//static float speed = 1.0;
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

	static void run(Vector<Soldier*> vec, Vec2 target) {
		for (int i = 0; i<vec.size(); i++) {
			if (vec.at(i)->selected) {
				vec.at(i)->isrun = 1;
			}
			auto pos = vec.at(i)->getPosition();
			auto distance = pos.getDistance(target);
			if(vec.at(i)->isrun == 1)
			{
				vec.at(i)->stopAllActions();
				vec.at(i)->runAction(MoveTo::create(distance/30, target));
			}
		}
		//scheduler(schedule_selector(Soldier::scheduleRun), vec,target,delta);
	}

	/*static void scheduleRun(Vector<Soldier*> vec, Vec2 target, float delta) {
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
		
	}*/
	/*
     static void RunToAttcak(Vector<Soldier*> vec,Vector<Soldier*> enemy,Vec2 target) {
     int a = 0;
     for(int i = 0;i<enemy.size();i++){
     if(isTap(target,enemy.at(i))) a = i;
     break;
     }
     for (int i = 0; i<vec.size(); i++) {
     if (vec.at(i)->selected) {
     vec.at(i)->isrun = 1;
     enemy.at(a)->attacker.pushback(vec.at(i));
     }
     auto position = vec.at(i)->getPosition();
     
     auto distance = position.getDistance(target);
     
     if (vec.at(i)->isrun) {
     vec.at(i)->stopAllActions();
     vec.at(i)->runAction(MoveTo::create(distance/30, target));
     }
     
     }
     }
     }
     */
	static bool judge_selected(Vector<Soldier*> vec, Vec2 down, Vec2 up) {
		bool isselected = 0;
		if (up == down) {
			for (int i = 0; i<vec.size(); i++) {
				auto p = vec.at(i)->getPosition();  //GL
				if (isTap(down,vec.at(i))) {
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
			float y_min = fmin(up.y, down.y);
			float y_max = fmax(up.y, down.y);
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
            vec.at(i)->isrun = 0;
			vec.at(i)->blood->setVisible(false);
			vec.at(i)->progress->setVisible(false);
		}
	}
    
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
		spr->blood->setScale(0.05);
		spr->blood->setVisible(false);
		spr->progress = ProgressTimer::create(Sprite::create("blood.png")); //¥¥Ω®progress∂‘œÛ
		spr->progress->setType(ProgressTimer::Type::BAR);        //¿‡–Õ£∫Ãı◊¥
		spr->progress->setPosition(Vec2(spr->getPositionX(), spr->getPositionY() + 16));
		spr->progress->setScale(0.05);
		//¥””“µΩ◊Ûºı…Ÿ—™¡ø
		spr->progress->setMidpoint(Vec2(0, 0.5));     //»Áπ˚ «¥”◊ÛµΩ”“µƒª∞£¨∏ƒ≥…(1,0.5)º¥ø…
		spr->progress->setBarChangeRate(Vec2(1, 0));
		spr->progress->setPercentage(100);
		spr->progress->setVisible(false);
	}
    static bool attack(Vector<Soldier*> vec,Vector<Soldier*> enemy,Vec2 target){
        int a = 0;
        for(int i = 0;i<enemy.size();i++){
            if(isTap(target,enemy.at(i))) a = i;
            break;
        }
        for(int i = 0;i<vec.size();i++){
            if(vec.at(i)->selected) vec.at(i)->a_enemy = enemy.at(a);
        }
        /*for (int i = 0; i<vec.size(); i++) {
            if(vec.at(i)->selected && vec.at(i)->getPosition().getDistance(target)<=200){
                if(vec.at(i)->a_enemy){
                    vec.at(i)->a_enemy->attacker--;
                    vec.at(i)->a_enemy = enemy.at(i);
                    enemy.at(a)->attacker++;
                }
                else{
                    vec.at(i)->a_enemy = enemy.at(i);
                    enemy.at(a)->attacker++;
                }
            }
            else{
                vec.at(i)->isrun = 1;
            }
        }
        for(int i = 0; i<vec.size(); i++){
            auto position = vec.at(i)->getPosition();
            auto distance = position.getDistance(target);
            Vec2 arrive(position.x+(target.x-position.x)*(distance-200)/distance,position.y+(target.y-position.y)*(distance-200)/distance);
            if(vec.at(i)->isrun){
                vec.at(i)->runAction(MoveTo::create(distance/30, arrive));
            }
        }*/
    }
};


#endif 

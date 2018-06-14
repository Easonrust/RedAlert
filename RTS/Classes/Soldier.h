#ifndef __SOLDIER_H__
#define __SOLDIER_H__
#include "cocos2d.h"
#include <algorithm>
USING_NS_CC;
class Soldier : public Sprite{
    
public:
    int health = 100;
    bool selected = 0;
    int collide_r = 16;
    Sprite* blood;
    ProgressTimer* progress;
    static Soldier* create(const char* filename);
    static void run(Vector<Soldier*> vec,Vec2 target);
    static void judge_selected(Vector<Soldier*> vec,Vec2 down,Vec2 up);
    static void clear(Vector<Soldier*> vec);
    static void add_bloodbar(Soldier* spr);
};

void judge_selected(Vector<Soldier*> vec,Vec2 down,Vec2 up){
    int abc = 0;
    if(up==down){
        for(int i = 0;i<vec.size();i++){
            auto p = vec.at(i)->getPosition();  //GL
            if(p.x-32<=down.x && p.x+32>=down.x && p.y-32<=down.y && p.y+32>=down.y){
                vec.at(i)->setOpacity(123);
                //vec.erase(vec.begin()+i);
                //vec[i]->removeFromParentAndCleanup(true);
                vec.at(i)->selected = 1;
                vec.at(i)->blood->setVisible(true);
                vec.at(i)->progress->setVisible(true);
                abc = 1;
            }
        }
    }
    if(up!=down){
        float x_min = up.x>=down.x ? up.x : down.x;
        float x_max = up.x<down.x ? up.x : down.x;
        float y_min = up.x>=down.x ? up.x : down.x;
        float y_max = up.x<down.x ? up.x : down.x;
        for(int i = 0;i<vec.size();i++){
            auto p = vec.at(i)->getPosition();
            if(p.x>=x_min&& p.x<=x_max&&p.y>=y_min&& p.y<=y_max ){
                vec.at(i)->blood->setVisible(true);
                vec.at(i)->progress->setVisible(true);
                vec.at(i)->selected = 1;
                abc = 1;
            }
        }
    }
}
 Soldier* Soldier:: create(const char* filename){
    Soldier* sprite = new Soldier();
    if (sprite && sprite->initWithFile("soldier.png"))
    {
        sprite->autorelease();
        auto body = PhysicsBody::create();
        sprite->setScale(0.5);
        body->addShape(PhysicsShapeCircle::create(sprite->collide_r));
        body->setRotationEnable(false);
        body->setDynamic(true);
        
        sprite->setPhysicsBody(body);
        return sprite;
    }
}

void Soldier::clear(Vector<Soldier*> vec){
    for(int i = 0;i<vec.size();i++){
        vec.at(i)->selected = 0;
        vec.at(i)->blood->setVisible(false);
        vec.at(i)->progress->setVisible(false);
    }
}
void Soldier::run(Vector<Soldier*> vec,Vec2 target){
    
}

void Soldier::add_bloodbar(Soldier *spr){
    spr->blood = Sprite::create("bar.png");   //¥¥Ω®Ω¯∂»øÚ
    spr->blood->setPosition(Vec2(spr->getPositionX(),spr->getPositionY()+65)); //…Ë÷√øÚµƒŒª÷√
    spr->blood->setScale(0.1);
    spr->blood->setVisible(false);
    spr->progress = ProgressTimer::create(Sprite::create("blood.png")); //¥¥Ω®progress∂‘œÛ
    spr->progress->setType(ProgressTimer::Type::BAR);        //¿‡–Õ£∫Ãı◊¥
    spr->progress->setPosition(Vec2(spr->getPositionX(),spr->getPositionY()+16));
    spr->progress->setScale(0.1);
    //¥””“µΩ◊Ûºı…Ÿ—™¡ø
    spr->progress->setMidpoint(Vec2(0, 0.5));     //»Áπ˚ «¥”◊ÛµΩ”“µƒª∞£¨∏ƒ≥…(1,0.5)º¥ø…
    spr->progress->setBarChangeRate(Vec2(1, 0));
    spr->progress->setPercentage(100);
    spr->progress->setVisible(false);
    
}
#endif 

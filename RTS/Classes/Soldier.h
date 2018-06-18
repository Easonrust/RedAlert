#ifndef __SOLDIER_H__
#define __SOLDIER_H__
#include "cocos2d.h"
#include <algorithm>
USING_NS_CC;
class Soldier : public Sprite{
    
public:
    int health = 100;
    bool selected = 0;
    bool isrun = 0;
    int collide_r = 16;
    Sprite* blood;
    ProgressTimer* progress;
    static Soldier* create(const char* filename);
    static void run(Vector<Soldier*> vec,Vec2 target,float delta);
    static void scheduleRun(Vector<Soldier*> vec,Vec2 target,float delta);
    static void scheduleRunToAttcak(Vector<Soldier*> vec,Vec2 target,float delta);
    static bool judge_selected(Vector<Soldier*> vec,Vec2 down,Vec2 up);
    static void clear(Vector<Soldier*> vec);
    static void attack(Vector<Soldier*> vec,Vector<Soldier*> enemy,float delta);
    void shelduleAttack(Vector<Soldier*> vec,Vector<Soldier*> enemy,Vec2 target);
    static void add_bloodbar(Soldier* spr);
};


#endif 

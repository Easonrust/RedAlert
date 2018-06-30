#ifndef __BUILDING_H__
#define __BUILDING_H__
#define building_base "base.png"
#define building_epower "e1.png"
#define building_mine "m1.png"
#define building_barrack "b1.png"
#define building_carinc "c1.png"
#define building_wall "wall.png"
#include"cocos2d.h"
#include<algorithm>
USING_NS_CC;
using namespace std;
typedef enum {
	Base = 0,
	Epower = 1,
	Mine = 2,
	Barrack = 3,
	Carinc = 4,
	Wall = 5
}Building_type;

class building : public Sprite {
public:
	float building_health=0;
	float originhealth=0;
	Sprite* blood;
	Sprite*ani;
	ProgressTimer* progress;
	static building*createWithBuildingType(Building_type building_type);//按照建筑类型进行建造
	static void add_blood_bar(building* spr);
	Node* buildingnode;
};
#endif


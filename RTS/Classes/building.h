#ifndef __BUILDING_H__
#define __BUILDING_H__
#define building_base "base.png"
#define building_epower "e1.png"
#define building_mine "m1.png"
#define building_barrack "b1.png"
#define building_carinc "c1.png"
#include"cocos2d.h"
#include<algorithm>
USING_NS_CC;
using namespace std;
typedef enum {
	Base = 0,
	Epower = 1,
	Mine = 2,
	Barrack = 3,
	Carinc = 4
}Building_type;

class building : public Sprite {
public:
	float building_health=0;
	float originhealth=0;
	int building_r;//�뾶
	bool selected = 0;
	Sprite* blood;
	ProgressTimer* progress;
	static building*createWithBuildingType(Building_type building_type);//���ս������ͽ��н���
	static void judge_selected(Vector<building*>vec, Vec2 mouse_down, Vec2 mouse_up);//�Ƿ�ѡ��
	static void add_blood_bar(building* spr);
	static bool isTap(cocos2d::Vec2 location, cocos2d::Node*node);
	Node* buildingnode;
};
#endif


#ifndef __MAP_H__
#define __MAP_H__
#define MAPTAG 0
#include"cocos2d.h"  
#include"button.h"
#include"building.h"
#include"Soldier.h"
USING_NS_CC;
class mymap : public Layer
{
	Vec2 originmap;
	cocos2d::TMXTiledMap* _tileMap;//地图
	cocos2d::TMXLayer* _collidable;
	Vector<building*>buildings;//建筑容器
    Vector<building*>enemy_buildings;
	Vector<Soldier*>soldiers;
    Vector<Soldier*>enemy_soldiers;
	Vec2 repair; //坐标修正量
	int buildingnum = 0;//建筑数量
	int soldiernum = 0;
	Vec2 barrackpos;
	Vec2 mouse_up;
	Vec2 mouse_down;
	int bloodnum = 100;//血量条的数量+100
	bool moneyenough = false;
public:
	button*buttonlayer;//按钮层指针（用于信息交互）
					   //士兵容器
	bool canbuild(Vec2 location);//能否建造不与其他建筑碰撞的函数
	bool collide(Vec2 pos);//检测碰撞的函数
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	void moveBlood(float delta);//更新建筑血量的函数
    void scheduleBlood_enemy(float delta);
	void setmap(float delta);//移动地图的函数
	CREATE_FUNC(mymap);
};

#endif


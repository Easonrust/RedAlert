#ifndef __MAP_H__
#define __MAP_H__
#define MAPTAG 0
#include"cocos2d.h"  
#include"button.h"
#include"building.h"
USING_NS_CC;
class mymap : public Layer
{

	cocos2d::TMXTiledMap* _tileMap;//地图
	building* base;//基地
	Vec2 repair;//坐标修正量
	int buildingnum=0;//建筑数量
	int soldiernum = 0;
	Vec2 barrackpos;
	Vector<ProgressTimer *>blood;
	int bloodnum=100;//血量条的数量+100
public:
	button*buttonlayer;//按钮层指针（用于信息交互）
	Vector<building*>buildings;//建筑容器
	Vector<Sprite*>soldiers;//士兵容器
	bool canbuild(Vec2 location);//能否建造不与其他建筑碰撞的函数
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	void createblood(Vec2 location);//创建血条的函数
	void scheduleBlood(float delta);//更新建筑血量的函数
	void setmap(float delta);//移动地图的函数
	CREATE_FUNC(mymap);
};

#endif
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
	cocos2d::TMXTiledMap* _tileMap;//��ͼ
	cocos2d::TMXLayer* _collidable;
	Vector<building*>buildings;//��������
	Vector<building*>enemy_buildings;
	Vector<Soldier*>soldiers;
	Vector<Soldier*>enemy_soldiers;
	Vec2 repair; //����������
	int buildingnum = 0;//��������
	int soldiernum = 0;
	Vec2 barrackpos = Vec2(0, 0);
	Vec2 carincpos = Vec2(0, 0);
	Vec2 enemy_barrackpos = Vec2(0, 0);
	Vec2 enemy_carincpos = Vec2(0, 0);
	Vec2 mouse_up;
	Vec2 mouse_down;
	Vec2 mouse_move;
	bool ismousedown;
	DrawNode* drawNode;
	Vec2 pos1;
	int bloodnum = 100;//Ѫ����������+100
	bool moneyenough = false;
	bool enemy_moneyenough = false;
public:
	button*buttonlayer;//��ť��ָ�루������Ϣ������
					   //ʿ������
	bool canbuild(Vec2 location);//�ܷ��첻������������ײ�ĺ���
	bool collide(Vec2 pos);//�����ײ�ĺ���
	bool tapenemy(Vec2 location, Vector<building*>enemy_building, Vector<Soldier*>enemy_soldiers);
	bool taparmy(Vec2 location, Vector<building*>buildings, Vector<Soldier*>soldiers);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	void moveBlood(float delta);//���½���Ѫ���ĺ���
	void scheduleBlood_enemy(float delta);
	void scheduleBlood_mine(float delta);
	void protectmap(float delta);
	void iscollide(float delta);
	void soldierattack(float delta);
	void ruins();
	static bool isTap(cocos2d::Vec2 location, cocos2d::Node*node);
	
	CREATE_FUNC(mymap);
};

#endif


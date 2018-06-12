#ifndef __MAP_H__
#define __MAP_H__
#define MAPTAG 0
#include"cocos2d.h"  
#include"button.h"
#include"building.h"
USING_NS_CC;
class mymap : public Layer
{
	cocos2d::TMXTiledMap* _tileMap;//��ͼ
	building* base;//����
	Vec2 repair;//����������
	int buildingnum=0;//��������
	Vector<ProgressTimer *>blood;
	int bloodnum=100;//Ѫ����������+100
public:
	button*buttonlayer;//��ť��ָ�루������Ϣ������
	Vector<building*>buildings;//��������
	bool canbuild(Vec2 location);//�ܷ��첻������������ײ�ĺ���
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	void createblood(Vec2 location);
	void scheduleBlood(float delta);
	CREATE_FUNC(mymap);
};

#endif

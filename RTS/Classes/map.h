#ifndef __MAP_H__
#define __MAP_H__
#define MAPTAG 0
#include"cocos2d.h"  
#include"button.h"


USING_NS_CC;
class mymap : public Layer
{
    
	cocos2d::TMXTiledMap* _tileMap;//��ͼ
	
	Vec2 repair; //����������
	int buildingnum=0;//��������
	int soldiernum = 0;
	Vec2 barrackpos;
	int bloodnum=100;//Ѫ����������+100
public:
	button*buttonlayer;//��ť��ָ�루������Ϣ������
    
	//ʿ������
	bool canbuild(Vec2 location);//�ܷ��첻������������ײ�ĺ���
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	void scheduleBlood(float delta);//���½���Ѫ���ĺ���
	void setmap(float delta);//�ƶ���ͼ�ĺ���
	CREATE_FUNC(mymap);
};

#endif

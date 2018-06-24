#ifndef __BUTTON_H__
#define __BUTTON_H__
//����Tag
#define BUTTONLISTTAG 0
#define MINEBUTTONTAG 1
#define EPOWERBUTTONTAG 2
#define BARRACKBUTTONTAG 3
#define CARINCBUTTONTAG 4
#define MONEYPOWERLISTTAG 5
#define MONEYTAG 6
#define MONEYPNG 7
#define POWERTAG 8
#define POWERPNG 9
#define SOLDIERBUTTONTAG 10
#define TANKBUTTONTAG 11
#define ROBOTBUTTONTAG 12
#include"cocos2d.h"
USING_NS_CC;
class button : public Layer
{
	//���ཨ����ť
	Sprite*minebutton;
	Sprite*epowerbutton;
	Sprite*barrackbutton;
	Sprite*carincbutton;
	Sprite*soldierbutton;
	Sprite*tankbutton;
	Sprite*robotbutton;
	//���°�ť������
	Sprite*buttonlist;
	Sprite*moneypowerlist;
	//Ǯ�����
	String*smoney;
	Sprite*moneypng;
	Label*lblmoney;
	String*spower;
	Sprite*powerpng;
	Label*lblpower;
    
public:
    int base_num = 1;
    int mine_num = 0;
    int epower_num = 0 ;
    int barrack_num = 0;
    int carinc_num  = 0;
	int money = 4000;
	int power = 0;
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	bool isTap(cocos2d::EventMouse*em, cocos2d::Node*node);
	int buildornot = 0;//��ť�Ƿ��ṩ�˽�������
	int buildchoice = 0;//�޽��ĸ�����
	virtual bool onMouseDown(Event*e);
	virtual void onMouseUp(Event*e);
	void scheduleMoneyPower(float delta);
	void schedulebutton(float delta);
	void updatemoney(int buildchoice);
	CREATE_FUNC(button);
};
#endif 


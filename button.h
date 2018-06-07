#ifndef __BUTTON_H__
#define __BUTTON_H__
#define BUTTONLISTTAG 0
#define MINEBUTTONTAG 1
#define EPOWERBUTTONTAG 2
#define BARRACKBUTTONTAG 3
#define CARINCBUTTONTAG 4
#define UPBUTTONTAG 5
#define DOWNBUTTONTAG 6
#define RIGHTBUTTONTAG 7
#define LEFTBUTTONTAG 8
#define MONEYPOWERLISTTAG 9
#define MONEYTAG 10
#define MONEYPNG 11
#define POWERTAG 12
#define POWERPNG 13
#include"cocos2d.h"
USING_NS_CC;
class button : public Layer
{
	Sprite*minebutton;
	Sprite*epowerbutton;
	Sprite*barrackbutton;
	Sprite*carincbutton;
	Sprite*setupbutton;
	Sprite*setdownbutton;
	Sprite*setleftbutton;
	Sprite*setrightbutton;
	Sprite*buttonlist;
	Sprite*moneypowerlist;
	String*smoney;
	Sprite*moneypng;
	int money;
	Label*lblmoney;
	String*spower;
	Sprite*powerpng;
	int power;
	Label*lblpower;
public:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	bool isTap(cocos2d::EventMouse*em, cocos2d::Node*node);
	bool buildornot;
	int set;
	virtual bool onMouseDown(Event*e);
	virtual void onMouseUp(Event*e);
	CREATE_FUNC(button);
};
#endif 

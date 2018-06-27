#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "SystemHeader.h"
USING_NS_CC;
class Room : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
	//菜单项回调函数
	void menuGobackCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Room);
};
#endif
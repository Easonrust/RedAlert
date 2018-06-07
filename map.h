#ifndef __MAP_H__
#define __MAP_H__
#include"cocos2d.h"  
#include"button.h"
USING_NS_CC;
class map : public Layer
{
	cocos2d::TMXTiledMap* _tileMap;

	cocos2d::Sprite* base;
	Vec2 repair;
public:
	button*buttonlayer;
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(map);
}; 
#endif

#ifndef __Select_SCENE_H__
#define __Select_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "SystemHeader.h"

class Select : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//菜单项回调函数
	void menuLastToggleCallback(cocos2d::Ref* pSender);
	void menuMap1ToggleCallback(cocos2d::Ref* pSender);
	void menuMap2ToggleCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Select);
};

#endif // __Setting_SCENE_H__

#pragma once
#ifndef __GAME_SCENEB_H__
#define __GAME_SCENEB_H__

#include "cocos2d.h"
#include"map.h"
#include"button.h"

class GameScenea : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();


	CREATE_FUNC(GameScenea);
};

#endif 
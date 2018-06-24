#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"map.h"
#include"button.h"

class HelloWorld : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();


	CREATE_FUNC(HelloWorld);
};
void revmessage(char*revmsg, mymap*a, button*b);
//void revmessage(char*revmsg);
void judgecamp(char*revcamp);
#endif // __HELLOWORLD_SCENE_H__

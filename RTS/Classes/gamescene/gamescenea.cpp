#include "gamescenea.h"
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
USING_NS_CC;

Scene* GameScenea::createScene()

{
	auto a = mymap::create();//创建地图层
	auto b = button::create();//创建按钮层
	auto scene = Scene::createWithPhysics();//创造物理场景
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));//重力为零
	a->buttonlayer = b;//将地图层中按钮层指针指向按钮层（用于信息交互）注意两个类不能互相指
	scene->addChild(a);
	scene->addChild(b);
	return scene;
}

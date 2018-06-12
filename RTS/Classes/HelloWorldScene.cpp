#include "HelloWorldScene.h"
#include"map.h"
#include"button.h"

USING_NS_CC;

Scene* HelloWorld::createScene()

{
	auto scene = Scene::createWithPhysics();//创造物理场景
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));//重力为零
	auto a = mymap::create();//创建地图层
	auto b = button::create();//创建按钮层
	a->buttonlayer = b;//将地图层中按钮层指针指向按钮层（用于信息交互）注意两个类不能互相指
	scene->addChild(a);
	scene->addChild(b);
	return scene;
}


#include "HelloWorldScene.h"
#include"map.h"
#include"button.h"

USING_NS_CC;

Scene* HelloWorld::createScene()

{
	auto scene = Scene::createWithPhysics();//����������
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));//����Ϊ��
	auto a = mymap::create();//������ͼ��
	auto b = button::create();//������ť��
	a->buttonlayer = b;//����ͼ���а�ť��ָ��ָ��ť�㣨������Ϣ������ע�������಻�ܻ���ָ
	scene->addChild(a);
	scene->addChild(b);
	return scene;
}


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
	auto a = mymap::create();//������ͼ��
	auto b = button::create();//������ť��
	auto scene = Scene::createWithPhysics();//����������
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));//����Ϊ��
	a->buttonlayer = b;//����ͼ���а�ť��ָ��ָ��ť�㣨������Ϣ������ע�������಻�ܻ���ָ
	scene->addChild(a);
	scene->addChild(b);
	return scene;
}

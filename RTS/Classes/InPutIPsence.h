#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED


#include "SelectScene.h"
#include <iostream>
#include <winsock2.h>
#include <process.h>
#include "json/json.h"
#include "cocos2d.h"

#pragma comment(lib, "WS2_32.lib")
USING_NS_CC;
using namespace std;
//宏定义
#define	SERVERPORT			10001		//服务器TCP端口
#define	MAX_NUM_BUF			10240			//缓冲区的最大长度

class InputIP : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
	//菜单项回调函数
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(InputIP);
};



//函数声明
bool InitClient(void);              //初始化
void InitMember(void);              //初始化全局变量
bool InitSockt(void);               //非阻塞套接字
bool ConnectServer(void);           //连接服务器
void ShowConnectMsg(bool bSuc);     //连接打印函数
void ExitClient(void);              //退出服务器
void clientsend(float right,Vec2&mouse_up, Vec2&mouse_down, Vec2&fit);
unsigned __stdcall clientreceiveThread(void* param);
#endif
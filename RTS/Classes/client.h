#pragma once
#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
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
#define	MAX_NUM_BUF			1024			//缓冲区的最大长度

//变量
extern SOCKET	sClient;							//套接字
extern char    bufSend[MAX_NUM_BUF];				//发送数据缓冲区
extern BOOL    bSend;                      //发送标记位
extern BOOL	bConnecting;						//与服务器的连接状态
extern CRITICAL_SECTION cs;					    //临界区对象，锁定bufSend
extern char *IP;                                  //IP地址
extern float coordinate[6];

//函数声明
BOOL InitClient(void);              //初始化
void InitMember(void);              //初始化全局变量
BOOL InitSockt(void);               //非阻塞套接字
BOOL ConnectServer(void);           //连接服务器
void ShowConnectMsg(BOOL bSuc);     //连接打印函数
void ExitClient(void);              //退出服务器
void clientsend(Vec2&mouse_up, Vec2&mouse_down, Vec2&fit);
unsigned __stdcall clientreceiveThread(void* param);
#endif
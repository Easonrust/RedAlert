#pragma once
#ifndef CLIENT_H_INCLUDED
#include"cocos2d.h"
#include <winsock2.h>
#include <process.h>

USING_NS_CC;
using namespace std;

#define MAX_NUM_BUF 10240
#define SERVERPORT  10001
//函数声明
bool InitClient(void);              //初始化
void InitMember(void);              //初始化全局变量
bool InitSockt(void);               //非阻塞套接字
bool ConnectServer(void);           //连接服务器
void ShowConnectMsg(bool bSuc);     //连接打印函数
void ExitClient(void);              //退出服务器
void clientsend(int right, Vec2&mouse_up, Vec2&mouse_down, Vec2&fit);
unsigned __stdcall clientreceiveThread(void* param);
#endif
#pragma once
#ifndef CLIENT_H_INCLUDED
#include"cocos2d.h"
#include <winsock2.h>
#include <process.h>

USING_NS_CC;
using namespace std;

#define MAX_NUM_BUF 10240
#define SERVERPORT  10001
//��������
bool InitClient(void);              //��ʼ��
void InitMember(void);              //��ʼ��ȫ�ֱ���
bool InitSockt(void);               //�������׽���
bool ConnectServer(void);           //���ӷ�����
void ShowConnectMsg(bool bSuc);     //���Ӵ�ӡ����
void ExitClient(void);              //�˳�������
void clientsend(int right, Vec2&mouse_up, Vec2&mouse_down, Vec2&fit);
unsigned __stdcall clientreceiveThread(void* param);
#endif
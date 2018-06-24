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

//�궨��
#define	SERVERPORT			10001		//������TCP�˿�
#define	MAX_NUM_BUF			1024			//����������󳤶�

//����
extern SOCKET	sClient;							//�׽���
extern char    bufSend[MAX_NUM_BUF];				//�������ݻ�����
extern BOOL    bSend;                      //���ͱ��λ
extern BOOL	bConnecting;						//�������������״̬
extern CRITICAL_SECTION cs;					    //�ٽ�����������bufSend
extern char *IP;                                  //IP��ַ
extern float coordinate[6];

//��������
BOOL InitClient(void);              //��ʼ��
void InitMember(void);              //��ʼ��ȫ�ֱ���
BOOL InitSockt(void);               //�������׽���
BOOL ConnectServer(void);           //���ӷ�����
void ShowConnectMsg(BOOL bSuc);     //���Ӵ�ӡ����
void ExitClient(void);              //�˳�������
void clientsend(Vec2&mouse_up, Vec2&mouse_down, Vec2&fit);
unsigned __stdcall clientreceiveThread(void* param);
#endif
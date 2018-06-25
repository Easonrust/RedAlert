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
//�궨��
#define	SERVERPORT			10001		//������TCP�˿�
#define	MAX_NUM_BUF			10240			//����������󳤶�

class InputIP : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
	//�˵���ص�����
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(InputIP);
};



//��������
bool InitClient(void);              //��ʼ��
void InitMember(void);              //��ʼ��ȫ�ֱ���
bool InitSockt(void);               //�������׽���
bool ConnectServer(void);           //���ӷ�����
void ShowConnectMsg(bool bSuc);     //���Ӵ�ӡ����
void ExitClient(void);              //�˳�������
void clientsend(float right,Vec2&mouse_up, Vec2&mouse_down, Vec2&fit);
unsigned __stdcall clientreceiveThread(void* param);
#endif
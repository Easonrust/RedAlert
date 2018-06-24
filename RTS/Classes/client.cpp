#include "InPutIPsence.h"
//����
 SOCKET	sClient;							//�׽���
 bool    bSend;                      //���ͱ��λ
 bool	bConnecting;						//�������������״̬
 CRITICAL_SECTION cs;					    //�ٽ�����������bufSend
 extern string IP;
 extern mymap*a1;
 extern button*b1;
//����
	/**
		*	��ʼ��
	*/
bool InitClient(void)
{
	//��ʼ��ȫ�ֱ���
	InitMember();
	//����SOCKET
	if (!InitSockt())
	{
		return FALSE;
	}
	return TRUE;
}

//��ʼ��ȫ�ֱ���
void InitMember(void)
{
	InitializeCriticalSection(&cs);

	sClient = INVALID_SOCKET;		//�׽���
	bConnecting = FALSE;			//Ϊ����״̬
}

//��������ʽ�׽���
 bool InitSockt(void)
{
	int			reVal;	//����ֵ
	WSADATA		wsData;	//WSADATA����
	reVal = WSAStartup(MAKEWORD(2, 2), &wsData);//��ʼ��Windows Sockets Dll
									
	sClient = socket(AF_INET, SOCK_STREAM, 0);//�����׽���
	if (INVALID_SOCKET == sClient)
	{
		return FALSE;
	}
	return TRUE;
}

//���ӷ�����
bool ConnectServer(void)
{
	int reVal;			//����ֵ
	sockaddr_in serAddr;//��������ַ
						
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(SERVERPORT);
	serAddr.sin_addr.S_un.S_addr = inet_addr(IP.c_str());
	cout << IP;
	//���ӷ�����
	reVal = connect(sClient, (struct sockaddr*)&serAddr, sizeof(serAddr));
	//�������Ӵ���
	if (SOCKET_ERROR == reVal)
	{
		return FALSE;
	}
	else if (reVal == 0)//���ӳɹ�
	{
		bConnecting = TRUE;
		return TRUE;
	}
	else
	{
		bConnecting = TRUE;
		return TRUE;
	}		
}

//��������
void clientsend(int right,Vec2&mouse_up,Vec2&mouse_down,Vec2&fit)
{
	Json::Value v_root;
	v_root["right"] = right;
	v_root["downx"] = mouse_down.x * 1000000;
	v_root["downy"] = mouse_down.y * 1000000;
	v_root["upx"] = mouse_up.x * 1000000;
	v_root["upy"] = mouse_up.y * 1000000;
	v_root["fitx"] = fit.x * 1000000;
	v_root["fity"] = fit.y * 1000000;
	cout << "�ѷ��ͣ�";
	cout << "toStyledString()" << endl;
	cout << v_root.toStyledString() << endl; 
	std::string SendBuf = v_root.toStyledString();
	//���������������  
	send(sClient, SendBuf.c_str(), SendBuf.size(), 0);
}

//���������߳�
unsigned __stdcall clientreceiveThread(void* param)
{
	cout << "�����̴߳����ɹ���" << endl;
	char recData[MAX_NUM_BUF];
	int number = 0;
	while (true)
	{
		number++;
		int ret = recv(sClient, recData, MAX_NUM_BUF, 0);
		if (ret == SOCKET_ERROR)
		{
			Sleep(50);
			continue;
		}
		if (ret > 0)
		{
			cout << "Recive message�� " << recData << endl;
			if (number == 1)
			{
				judgecamp(recData);
			}
			else
			{
				revmessage(recData,a1,b1);
				//revmessage(recData);
			}
			memset(recData, 0, ret);
		}
	}
	
}

/**
* �ͻ����˳�
*/
void ExitClient(void)
{
	DeleteCriticalSection(&cs);
	closesocket(sClient);
	WSACleanup();
}

/**
* ��ʾ���ӷ�����ʧ����Ϣ
*/
void ShowConnectMsg(bool bSuc)
{
	if (bSuc)
	{
		cout << "* Succeed to connect server! *" << endl;
	}
	else
	{
		cout << "* Client has to exit! *" << endl;
	}
}
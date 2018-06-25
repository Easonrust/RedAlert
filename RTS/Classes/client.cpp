#include "InPutIPsence.h"
//����
 SOCKET	sClient;							//�׽���
 bool    bSend;                      //���ͱ��λ
 bool	bConnecting;						//�������������״̬
 CRITICAL_SECTION cs;					    //�ٽ�����������bufSend
 float coordinate[7] = {0};
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
void clientsend(float right,Vec2&mouse_up,Vec2&mouse_down,Vec2&fit)
{
	Json::Value v_root;
	long  scoordinate[7];
	scoordinate[0] = right;
	scoordinate[1]=mouse_down.x*1000000;
	scoordinate[2] = mouse_down.y * 1000000;
	scoordinate[3] = mouse_up.x * 1000000;
	scoordinate[4] = mouse_up.y * 1000000;
	scoordinate[5] = fit.x * 1000000;
	scoordinate[6] = fit.y * 1000000;
	v_root["right"] = scoordinate[0];
	v_root["downx"] = scoordinate[1];
	v_root["downy"] = scoordinate[2];
	v_root["upx"] = scoordinate[3];
	v_root["upy"] = scoordinate[4];
	v_root["fitx"] = scoordinate[5];
	v_root["fity"] = scoordinate[6];
	cout << "�ѷ��ͣ�";
	cout << "toStyledString()" << endl;
	cout << v_root.toStyledString() << endl; 
	std::string SendBuf = v_root.toStyledString();
	//���������������  
	send(sClient, SendBuf.c_str(), SendBuf.size(), 0);
	/*char data[1024] = {0};
	sprintf(data, "%-16f%-16f%-16f%-16f%-16f%-16f%-16f", right, mouse_down.x, mouse_down.y, mouse_up.x, mouse_up.y, fit.x, fit.y);
	cout << "�ѷ��ͣ�" << data << endl;
	send(sClient, data, 200, 0);*/
}

//���������̺߳���
unsigned __stdcall clientreceiveThread(void* param)
{
	cout << "�����̴߳����ɹ���" << endl;
	char recData[MAX_NUM_BUF];
	while (true)
	{
		int ret = recv(sClient, recData, MAX_NUM_BUF, 0);
		if (ret == SOCKET_ERROR)
		{
			Sleep(50);
			continue;
		}
		if (ret > 0)
		{
			cout << "ret: " << ret << endl;
			cout << "���յ�1��" << recData << endl;
			//revmessage(recData,a1,b1);
			Json::Reader reader;
			Json::Value root;
			if (reader.parse(recData, root))
			{
				coordinate[0] = ((float)root["right"].asInt()) / 1000000;
				coordinate[1] = ((float)root["downx"].asInt()) / 1000000;
				coordinate[2] = ((float)root["downy"].asInt()) / 1000000;
				coordinate[3] = ((float)root["upx"].asInt()) / 1000000;
				coordinate[4] = ((float)root["upy"].asInt()) / 1000000;
				coordinate[5] = ((float)root["fitx"].asInt()) / 1000000;
				coordinate[6] = ((float)root["fity"].asInt()) / 1000000;
			}
			Sleep(10);
			for (int i = 0; i < 7; i++)
			{
				cout << "coordinate:  " << coordinate[i] << endl;
			}
			memset(recData, 0, MAX_NUM_BUF);
		}
	}
}

/**
* �ͻ����˳���������Դ
*/
void ExitClient(void)
{
	DeleteCriticalSection(&cs);
	closesocket(sClient);
	WSACleanup();
}

/**
* ��ʾ���ӷ������ɹ���ʧ����Ϣ
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
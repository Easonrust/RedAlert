#include "client.h"
#include"iostream"
#include"json\json.h"
//����
 SOCKET	sClient;							//�׽���
 bool    bSend;                      //���ͱ��λ
 bool	bConnecting;						//�������������״̬
 CRITICAL_SECTION cs;					    //�ٽ�����������bufSend
 //extern string IP;
 float coordinate[7] = { 0 };
 bool connectornot = 0;
 bool comein=0;
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
	serAddr.sin_addr.S_un.S_addr = inet_addr("119.29.202.243");//(IP.c_str());
	//cout << IP;
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
	long  coordinate[7];
	coordinate[0] = right;
	coordinate[1] = mouse_down.x * 1000000;
	coordinate[2] = mouse_down.y * 1000000;
	coordinate[3] = mouse_up.x * 1000000;
	coordinate[4] = mouse_up.y * 1000000;
	coordinate[5] = fit.x * 1000000;
	coordinate[6] = fit.y * 1000000;
	v_root["right"] = coordinate[0];
	v_root["downx"] = coordinate[1];
	v_root["downy"] = coordinate[2];
	v_root["upx"] = coordinate[3];
	v_root["upy"] = coordinate[4];
	v_root["fitx"] = coordinate[5];
	v_root["fity"] = coordinate[6];

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
			cout << "Recive message�� " << recData << endl;
			Json::Reader reader;
			Json::Value root;
			if (reader.parse(recData, root))
			{
				coordinate[0] = ((float)root["right"].asInt());
				coordinate[1] = ((float)root["downx"].asInt()) / 1000000;
				coordinate[2] = ((float)root["downy"].asInt()) / 1000000;
				coordinate[3] = ((float)root["upx"].asInt()) / 1000000;
				coordinate[4] = ((float)root["upy"].asInt()) / 1000000;
				coordinate[5] = ((float)root["fitx"].asInt()) / 1000000;
				coordinate[6] = ((float)root["fity"].asInt()) / 1000000;
				Sleep(10);
				for (int i = 0; i < 7; i++)
				{
					cout << "coordinate:  " << coordinate[i] << endl;
				}
					connectornot = 1;
			}
			else
			{
				comein = 1;
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
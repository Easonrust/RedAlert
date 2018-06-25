#include "InPutIPsence.h"
//变量
 SOCKET	sClient;							//套接字
 bool    bSend;                      //发送标记位
 bool	bConnecting;						//与服务器的连接状态
 CRITICAL_SECTION cs;					    //临界区对象，锁定bufSend
 float coordinate[7] = {0};
 extern string IP;
 extern mymap*a1;
 extern button*b1;
 float coordinate[7] = { 0 };
 bool connectornot = 0;
//变量
	/**
		*	初始化
	*/
bool InitClient(void)
{
	//初始化全局变量
	InitMember();
	//创建SOCKET
	if (!InitSockt())
	{
		return FALSE;
	}
	return TRUE;
}

//初始化全局变量
void InitMember(void)
{
	InitializeCriticalSection(&cs);

	sClient = INVALID_SOCKET;		//套接字
	bConnecting = FALSE;			//为连接状态
}

//创建阻塞式套接字
 bool InitSockt(void)
{
	int			reVal;	//返回值
	WSADATA		wsData;	//WSADATA变量
	reVal = WSAStartup(MAKEWORD(2, 2), &wsData);//初始化Windows Sockets Dll
									
	sClient = socket(AF_INET, SOCK_STREAM, 0);//创建套接字
	if (INVALID_SOCKET == sClient)
	{
		return FALSE;
	}
	return TRUE;
}

//连接服务器
bool ConnectServer(void)
{
	int reVal;			//返回值
	sockaddr_in serAddr;//服务器地址
						
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(SERVERPORT);
	serAddr.sin_addr.S_un.S_addr = inet_addr(IP.c_str());
	cout << IP;
	//连接服务器
	reVal = connect(sClient, (struct sockaddr*)&serAddr, sizeof(serAddr));
	//处理连接错误
	if (SOCKET_ERROR == reVal)
	{
		return FALSE;
	}
	else if (reVal == 0)//连接成功
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

//发送数据
void clientsend(float right,Vec2&mouse_up,Vec2&mouse_down,Vec2&fit)
{
	Json::Value v_root;
<<<<<<< HEAD
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

=======
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
>>>>>>> ab1ada03140212484ed3a40919f40438b177e69c
	cout << "已发送：";
	cout << "toStyledString()" << endl;
	cout << v_root.toStyledString() << endl; 
	std::string SendBuf = v_root.toStyledString();
	//向服务器发送数据  
	send(sClient, SendBuf.c_str(), SendBuf.size(), 0);
	/*char data[1024] = {0};
	sprintf(data, "%-16f%-16f%-16f%-16f%-16f%-16f%-16f", right, mouse_down.x, mouse_down.y, mouse_up.x, mouse_up.y, fit.x, fit.y);
	cout << "已发送：" << data << endl;
	send(sClient, data, 200, 0);*/
}

//接收数据线程函数
unsigned __stdcall clientreceiveThread(void* param)
{
	cout << "接收线程创建成功！" << endl;
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
<<<<<<< HEAD
			cout << "Recive message： " << recData << endl;
=======
			cout << "ret: " << ret << endl;
			cout << "接收到1：" << recData << endl;
			//revmessage(recData,a1,b1);
>>>>>>> ab1ada03140212484ed3a40919f40438b177e69c
			Json::Reader reader;
			Json::Value root;
			if (reader.parse(recData, root))
			{
<<<<<<< HEAD
				coordinate[0] = ((float)root["right"].asInt());
=======
				coordinate[0] = ((float)root["right"].asInt()) / 1000000;
>>>>>>> ab1ada03140212484ed3a40919f40438b177e69c
				coordinate[1] = ((float)root["downx"].asInt()) / 1000000;
				coordinate[2] = ((float)root["downy"].asInt()) / 1000000;
				coordinate[3] = ((float)root["upx"].asInt()) / 1000000;
				coordinate[4] = ((float)root["upy"].asInt()) / 1000000;
				coordinate[5] = ((float)root["fitx"].asInt()) / 1000000;
				coordinate[6] = ((float)root["fity"].asInt()) / 1000000;
<<<<<<< HEAD
				connectornot = 1;
=======
>>>>>>> ab1ada03140212484ed3a40919f40438b177e69c
			}
			Sleep(10);
			for (int i = 0; i < 7; i++)
			{
				cout << "coordinate:  " << coordinate[i] << endl;
			}
<<<<<<< HEAD

			memset(recData, 0, ret);
=======
			memset(recData, 0, MAX_NUM_BUF);
>>>>>>> ab1ada03140212484ed3a40919f40438b177e69c
		}
	}
}

/**
* 客户端退出，清理资源
*/
void ExitClient(void)
{
	DeleteCriticalSection(&cs);
	closesocket(sClient);
	WSACleanup();
}

/**
* 显示连接服务器成功或失败信息
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
#include <stdlib.h>
#include <stdio.h>
#include<iostream>
#include<string>
#include <winsock2.h>
#include <time.h>
#include "conio.h"
#include <windows.h>
#include <process.h>
#include <math.h>
using namespace std;
#define    QLEN       5
#define    WSVERS    MAKEWORD(2, 0)
#define    BUFLEN    10240              // 缓冲区大小
#pragma comment(lib,"ws2_32.lib")       //winsock 2.2 library

SOCKET    msock, ssock;                 // master & slave sockets
SOCKET    sockets[1000] = { NULL };

int cc;
char    *pts;                           // pointer to time string
time_t    now;                          // current time
char buf[2000];                         // buffer
char *input;
HANDLE hThread1, hThread[1000] = { NULL };
unsigned int threadID, ThreadID[1000], number;

struct    sockaddr_in fsin;
struct    sockaddr_in Sin;

bool camp[2] = { 0 };
unsigned int __stdcall receiveandsend(PVOID PM)          //接收和发送数据线程
{
	char buf1[20000] = { 0 };
	char buf2[20000] = { 0 };
	(void)time(&now);
	pts = ctime(&now);
	SOCKET    sock = ssock;
	const int n = number;
	unsigned int threadid = threadID;
	sockets[n] = sock;
	ThreadID[n] = threadid;
	sprintf(buf1, " 线程号 <%d> 客户<IP:%s 端口:%d>  enter ！  \n \t\t时间： %s\n", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port, pts);
	printf("%s ", buf1);
	printf("number:%d\n", n);
	char cap[10];
	camp[1] = !camp[1];
	sprintf(cap, "%d", camp[1]);
	printf("camp:%s\n", cap);
	send(sock, cap, sizeof(cap), 0);           //判断阵营
	while (true)
	{
		cc = recv(sock, buf2, BUFLEN, 0);      //cc为接收的字符数
		if (cc == SOCKET_ERROR || cc == 0)     //客户端离开，关闭线程
		{
			cout << "接收失败！"<<endl;
			(void)time(&now);
			pts = ctime(&now);
			sprintf(buf2, " 线程号 <%d> 客户<IP:%s 端口:%d>  leave !  \n \t\t时间： %s\n", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port, pts);
			sock = NULL;
			sockets[n] = NULL;
			CloseHandle(hThread[n]);
			printf("%s ", buf2);
			(void)closesocket(sock);
			break;
		}
		else if (cc >= 0)
		{
			(void)time(&now);
			pts = ctime(&now);
			buf2[cc] = 0x00;
			printf("收到来自线程号<%d>:%s \n", threadid, buf2);
			for (int i = 0; i <= number; i++)                            //将信息发给其它客户端
			{
				if (sockets[i] != NULL && sockets[i] != sock)
				{
					(void)send(sockets[i], buf2, sizeof(buf2), 0);
					printf(" 发送至线程号<%d>成功！\n", ThreadID[i]);
				}
			}
		}
	}
	return 0;
}


/*------------------------------------------------------------------------
* main - Iterative TCP server for DAYTIME service
*------------------------------------------------------------------------
*/

void main(int argc, char *argv[])
{
	string IP;
	cout << "请输入本机IP地址：";
	cin >> IP;
	int     alen;                                         // from-address length
	WSADATA wsadata;
	const char    *service = "10001";                     //端口号
	WSAStartup(WSVERS, &wsadata);                         //加载 winsock 2.2 library
	msock = socket(AF_INET, SOCK_STREAM, 0);              //生成套接字。TCP协议号=6， UDP协议号=17
	memset(&Sin, 0, sizeof(Sin));
	Sin.sin_family = AF_INET;
	Sin.sin_addr.s_addr = inet_addr(IP.c_str());          //指定绑定接口的IP地址。
	Sin.sin_port = htons((u_short)atoi(service));         //atoi--把ascii转化为int，htons - 主机序(host)转化为网络序(network), s(short)
	bind(msock, (struct sockaddr *)&Sin, sizeof(Sin));    // 绑定端口号（和IP地址)
	listen(msock, 5);                                     //队列长度为5

	printf("\t\t\t\t                RedAlert \n");
	printf("\t\t\t\t                (Server) \n");
	(void)time(&now);
	pts = ctime(&now);
	printf("\t\t\t           时间 ：%s", pts);            //输出服务器标题
	number = -1;
	srand((unsigned)time(&now));
	camp[0] = rand() % 1;                                 //生成阵营判断随机数  
	while (1)                                            
	{
		alen = sizeof(struct sockaddr);
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
		number++;
		hThread[number] = (HANDLE)_beginthreadex(NULL, 0, receiveandsend, NULL, 0, &threadID);   //创建接收和发送数据线程
	}
	(void)closesocket(msock);
	WSACleanup();                         //卸载载 winsock 2.2 library
}
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
#define    BUFLEN    10240              // ��������С
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
unsigned int __stdcall receiveandsend(PVOID PM)          //���պͷ��������߳�
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
	sprintf(buf1, " �̺߳� <%d> �ͻ�<IP:%s �˿�:%d>  enter ��  \n \t\tʱ�䣺 %s\n", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port, pts);
	printf("%s ", buf1);
	printf("number:%d\n", n);
	char cap[10];
	camp[1] = !camp[1];
	sprintf(cap, "%d", camp[1]);
	printf("camp:%s\n", cap);
	send(sock, cap, sizeof(cap), 0);           //�ж���Ӫ
	while (true)
	{
		cc = recv(sock, buf2, BUFLEN, 0);      //ccΪ���յ��ַ���
		if (cc == SOCKET_ERROR || cc == 0)     //�ͻ����뿪���ر��߳�
		{
			cout << "����ʧ�ܣ�"<<endl;
			(void)time(&now);
			pts = ctime(&now);
			sprintf(buf2, " �̺߳� <%d> �ͻ�<IP:%s �˿�:%d>  leave !  \n \t\tʱ�䣺 %s\n", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port, pts);
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
			printf("�յ������̺߳�<%d>:%s \n", threadid, buf2);
			for (int i = 0; i <= number; i++)                            //����Ϣ���������ͻ���
			{
				if (sockets[i] != NULL && sockets[i] != sock)
				{
					(void)send(sockets[i], buf2, sizeof(buf2), 0);
					printf(" �������̺߳�<%d>�ɹ���\n", ThreadID[i]);
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
	cout << "�����뱾��IP��ַ��";
	cin >> IP;
	int     alen;                                         // from-address length
	WSADATA wsadata;
	const char    *service = "10001";                     //�˿ں�
	WSAStartup(WSVERS, &wsadata);                         //���� winsock 2.2 library
	msock = socket(AF_INET, SOCK_STREAM, 0);              //�����׽��֡�TCPЭ���=6�� UDPЭ���=17
	memset(&Sin, 0, sizeof(Sin));
	Sin.sin_family = AF_INET;
	Sin.sin_addr.s_addr = inet_addr(IP.c_str());          //ָ���󶨽ӿڵ�IP��ַ��
	Sin.sin_port = htons((u_short)atoi(service));         //atoi--��asciiת��Ϊint��htons - ������(host)ת��Ϊ������(network), s(short)
	bind(msock, (struct sockaddr *)&Sin, sizeof(Sin));    // �󶨶˿ںţ���IP��ַ)
	listen(msock, 5);                                     //���г���Ϊ5

	printf("\t\t\t\t                RedAlert \n");
	printf("\t\t\t\t                (Server) \n");
	(void)time(&now);
	pts = ctime(&now);
	printf("\t\t\t           ʱ�� ��%s", pts);            //�������������
	number = -1;
	srand((unsigned)time(&now));
	camp[0] = rand() % 1;                                 //������Ӫ�ж������  
	while (1)                                            
	{
		alen = sizeof(struct sockaddr);
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
		number++;
		hThread[number] = (HANDLE)_beginthreadex(NULL, 0, receiveandsend, NULL, 0, &threadID);   //�������պͷ��������߳�
	}
	(void)closesocket(msock);
	WSACleanup();                         //ж���� winsock 2.2 library
}
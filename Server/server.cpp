#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")


using namespace std;

int main(int argc, char **argv)
{
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Can't Initialize winsock! Quitting" << endl;
		return 0;
	}
	
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create a socket! Quitting" << endl;
		return 0;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(808);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; 
	
	bind(listening, (sockaddr*)&hint, sizeof(hint));

	listen(listening, SOMAXCONN);

	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];		
	char service[NI_MAXSERV];	

	ZeroMemory(host, NI_MAXHOST); 
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << " connected on port " << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " <<
			ntohs(client.sin_port) << endl;
	}

	closesocket(listening);

	char buf[4096] = "13";
	
	while (true)
	{
		int bytesSend = send(clientSocket, buf, 3, 0);
		cout<< string(buf, 0, bytesSend) << " was sent to client" << endl;
		if (bytesSend == SOCKET_ERROR)
		{
			cerr << "Error in send(). Quitting" << endl;
			break;
		}

		if (bytesSend == 0)
		{
			cout << "Client disconnected " << endl;
			break;
		}

		Sleep(2000);
	} 
	
	closesocket(clientSocket);
	WSACleanup();	
	system("pause");
	
	return 0;
}

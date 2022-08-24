#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "libws2_32")

using namespace std;

int main()
{
	string ipAddress = "127.0.0.1";			
	int port = 808;						

	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return 0;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return 0;
	}

	char buf[4096];
	string recievedmsg;

	while(true){
		int result = recv(sock, buf, 3, 0);
		cout<< "SERVER > " << buf << endl;
		Sleep(2000);
	}

	closesocket(sock);
	WSACleanup();
}

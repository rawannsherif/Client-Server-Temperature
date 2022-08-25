#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <thread>
#include <chrono>
#include <iomanip>
#pragma comment(lib, "libws2_32")

using namespace std;

void readTemp(SOCKET sock){

	chrono::steady_clock sc;
	auto start = sc.now();

	char buf[4096];
	string recievedmsg;
	int sum = 0;
	int count = 0;

	while(true){
		int result = recv(sock, buf, 3, 0);
		cout<< "SERVER : " << buf << endl;

		int temp = atoi(buf);
		sum += temp;
		//count += 5;
		auto end = sc.now();
		auto time_span = static_cast<chrono::duration<double>>(end-start);
		Sleep(5000);
		cout<< "time : " << std:: setprecision(2) << time_span.count()<<endl;
		cout<<"Accumlation : " << sum / time_span.count() << endl;
		cout<<"Average : " << sum / time_span.count() << endl;

	}
}

void connectionClient(){
	string ipAddress = "127.0.0.1";			
	int port = 808;						

	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
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
		return;
	}

	readTemp(sock);
	closesocket(sock);
	WSACleanup();
}
int main()
{
	connectionClient();
}

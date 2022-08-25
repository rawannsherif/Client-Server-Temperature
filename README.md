# FireForecasting-
Client/Server architecture for fire forecasting where server sends temperature readings to client every second and client calculates average and accumulation over 5 seconds and responds. || C++


## **Winsock for client server connection using C++**
 

**Server Side:**

- It creates a socket on the server side to allow client to connect.
    - socket(AF_INET, SOCK_STREAM, 0)</sup>
- Binds the socket created to an ip address and port so the client can listen on that port and connect to server at said port. 
    - bind(listening, (sockaddr*)&hint, sizeof(hint))
- Tells winsock the socket is ready for listening 
    - listen(listening, SOMAXCONN);
- Client accepts connection to socket 
    - accept(listening, (sockaddr*)&client, &clientSize)
- Server sends temperature readings (random numbers) in array of characters buf  to client 
    - send(clientSocket, buf, 3, 0)
 
**Client side:**

- Connects on the port number used in server where socket is at.
    - connect(sock, (sockaddr*)&hint, sizeof(hint)).
- Buf fills with temperature readings send from server to client 
    - recv(sock, buf, 3, 0)
- Chrono library is used to track the time between each calculations to produce after 5 seconds 
    - chrono::steady_clock sc;
- Buf is converted into integer so average and accumulation over time is calculated 
    - auto time_span = static_cast<chrono::duration<double>>(end-start);
 
 
 Build commands:
```
make build_all
make run_server
make run_client
```

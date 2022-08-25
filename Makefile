CC = g++
CFLAGS = -lws2_32
MAKE = make

build_all: ./client/client.cpp ./server/server.cpp
	$(CC) -o ./build/client.exe ./client/client.cpp ${CFLAGS}
	$(CC) -o ./build/server.exe ./server/server.cpp ${CFLAGS}

run_server:
	./build/server.exe

run_client:
	./build/client.exe

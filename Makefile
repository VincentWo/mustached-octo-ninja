CPPFLAGS=-std=c++1y -Wall -Werror
server: server.o http.o
	g++ server.o http.o -o server

server.o: server.cpp
	g++ server.cpp $(CPPFLAGS) -c  -o server.o

http.o: http_request.cpp
	g++ http_request.cpp $(CPPFLAGS) -c -o http.o

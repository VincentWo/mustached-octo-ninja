CPPFLAGS=-std=c++1y -Wall -Werror
server: server.o
	g++ server.o -o server -lboost_program_options -Lhttp -lhttp

server.o: server.cpp
	g++ server.cpp $(CPPFLAGS) -c  -o server.o

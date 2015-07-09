#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>

#include "http.hpp"

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cerr << "ERROR, no port provided\n";
		return 1;
	}

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0)
	{
		error("ERROR opening socket");
	}
	int portno = atoi(argv[1]);

	sockaddr_in serv_addr{};
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if(bind(sockfd, (sockaddr *) &serv_addr,
	        sizeof(serv_addr)) <0)
	{
		error("ERROR on binding");
	}

	listen(sockfd, 5);

	sockaddr_in cli_addr{};
	socklen_t clilen = sizeof(cli_addr);
	int newsockfd = accept(sockfd,
	                       (sockaddr *)&cli_addr,
					       &clilen);

	if(newsockfd < 0)
	{
		error("ERROR on accept");
	}

	char buffer[256]{};
	int n = read(newsockfd, buffer, 255);
	if(n < 0)
	{
		error("ERROR reading from socket");
	}

	std::cout << "Here is the raw request: " << buffer;

	http::Request request{buffer};

	n = write(newsockfd,"I got your message", 18);
	if(n < 0)
	{
		error("ERROR writing to socket");
	}
	close(newsockfd);
	close(sockfd);
	return 0;
}

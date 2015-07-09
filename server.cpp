#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>
#include <boost/program_options.hpp>

#include "http/http.hpp"

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

using std::cout;
using std::cerr;

int main(int argc, char* argv[])
{
	namespace po = boost::program_options;

	po::options_description desc("Allowed options");
	desc.add_options()
	                ("help", "produce help message")
									("port", po::value<int>(), "The server listen for this port.");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if(vm.count("help"))
	{
		cout << desc << std::endl;
		return 0;
	}

	if(vm.count("port") == 0)
	{
		cerr << "Fatal Error: No Port given!\n";
		return 1;
	}

	int portno = vm["port"].as<int>();

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0)
	{
		error("ERROR opening socket");
	}

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
	std::string message{"HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n<html><head><title>Test Title</title></head><body><p>Test</p></body></html>\r\n"};
	n = write(newsockfd, message.c_str(), message.size());
	if(n < 0)
	{
		error("ERROR writing to socket");
	}
	close(newsockfd);
	close(sockfd);
	return 0;
}

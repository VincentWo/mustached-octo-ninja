#include <cstring>
#include "http.hpp"

namespace http
{
	Request::Request(const std::string& raw_request) : _method{},
	                                                   _request_uri{},
	                                                   _version{}
	{
		std::stringstream ss {raw_request};
		ss >> _method >> _request_uri >> _version;
	}

	std::istream& operator>>(std::istream& lhs, Method& rhs)
	{
		std::string cont;
		std::cin >> cont;
		lhs >> cont;

		if(cont == "OPTIONS")
		{
			rhs = Method::OPTIONS;
		}
		else if(cont == "GET")
		{
			rhs = Method::GET;
		}
		else if(cont == "HEAD")
		{
			rhs = Method::HEAD;
		}
		else if(cont == "POST")
		{
			rhs = Method::POST;
		}
		else if(cont == "PUT")
		{
			rhs = Method::PUT;
		}
		else if(cont == "DELETE")
		{
			rhs = Method::DELETE;
		}
		else if(cont == "TRACE")
		{
			rhs = Method::TRACE;
		}
		else if(cont == "CONNECT")
		{
			rhs = Method::CONNECT;
		}
		else
		{
			throw std::invalid_argument("Unknown Method: \"" + cont + '"');
		}

		return lhs;
	}

	std::istream& operator>>(std::istream& lhs, URI& rhs)
	{
		std::string cont;
		lhs >> cont;
		rhs.set(cont);
		return lhs;
	}

	std::istream& operator>>(std::istream& lhs, Version& rhs)
	{
		char buffer[5];
		lhs.getline(buffer, 5, '/');
		if(!lhs)
		{
			throw invalid_request("Request ends too early");
		}
		if(std::strcmp("HTTP", buffer)!=0)
		{
			throw invalid_request("HTTP Version has to begin with \"HTTP\"");
		}

		unsigned int first_digit;
		unsigned int second_digit;
		char dot;
		lhs >> first_digit >> dot >> second_digit;

		if(dot != '.' || !lhs)
		{
			throw invalid_request("Error while parsing the HTTP-Version");
		}

		rhs = {first_digit, second_digit};
		
		return lhs;
	}

	void URI::set(const std::string& val)
	{
		_URI = val;
	}
}

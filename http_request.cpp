#include "http/http.hpp"
namespace http
{
	Request::Request(const std::string& raw_request) : _method{},
	                                                   _request_uri{},
	                                                   _version{}
	{
		std::stringstream ss {raw_request};
		//ss >> _method >> _request_uri >> _version;
	}

	std::ostream& operator>>(std::ostream& lhs, Method& rhs)
	{
		std::string cont;
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
}

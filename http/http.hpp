#ifndef __http_http_hpp
#define __http_http_hpp

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>


namespace http
{
	class Version
	{
	public:
		constexpr Version(unsigned int first, unsigned int second) noexcept 
		        : _first_digit(first),
		          _second_digit{second} {}

		constexpr Version() noexcept
		        : _first_digit{},
		          _second_digit{} {}

		constexpr int first_digit() const noexcept  { return _first_digit; }
		constexpr int second_digit() const noexcept { return _second_digit;}
		constexpr void first_digit(int val) noexcept  { _first_digit = val;}
		constexpr void second_digit(int val) noexcept { _second_digit = val;}

	private:
		unsigned int _first_digit;
		unsigned int _second_digit;
	};

	#include "version_impl.hpp" // TODO: This is just a short hack, should be outsourced completly

	enum class Method
	{
		UNSUPPORTED,
		OPTIONS,
		GET,
		HEAD,
		POST,
		PUT,
		DELETE,
		TRACE,
		CONNECT
	};

	class URI
	{
	public:
		enum Type
		{
			NO_PARTICULAR_RESOURCE,
			ABSOLUTE_URI,
			ABSOLUTE_PATH,
			AUTHORITY
		};

		URI() : _URI{} {};
		URI(const std::string&);
		void set(const std::string&);
	private:
		std::string _URI;
	};

	class Request 
	{
		public:
			Request(const std::string&);
		private:
			Method _method;
			URI _request_uri;
			Version _version;
	};

	class invalid_request : std::exception
	{
	public:
		invalid_request(const char* what) : std::exception(), _what(what){}
		const char* what() const noexcept override { return _what;}
	private:
		const char* _what;
	};

	class Respond
	{
	};



	std::istream& operator>>(std::istream&, Method&);
	std::istream& operator>>(std::istream&, URI&);
	std::istream& operator>>(std::istream&, Version&);
}

#endif //__http_http_hpp

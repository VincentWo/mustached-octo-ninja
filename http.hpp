#ifndef __http_rohin_hpp
#define __http_rohin_hpp

#include <stdexcept>
#include <ostream>

#include "http/version_impl.hpp"

namespace http
{
	class Version
	{
	public:
		constexpr Version(int first, int second) noexcept;
		constexpr int first_digit() noexcept;
		constexpr int second_digit() noexcept;
		void first_digit(int) noexcept;
		void second_digit(int) noexcept;

	private:
		int _first_digit;
		int _second_digit;
	};

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

	class Request 
	{
		public:
			Request(const std::string&);
		private:
			URI _request_uri;
			Method _method;
			Version _version;
	};

	class invalid_request : std::exception
	{
	};

	class Respond
	{
	};



	std::ostream& operator>>(std::ostream&, Method&);
	std::ostream& operator>>(std::ostream&, URI&);
	std::ostream& operator>>(std::ostream&, Version&);
}
#endif

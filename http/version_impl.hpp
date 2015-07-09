#ifndef __http_rohin_hpp
#define __http_rohin_hpp
#include "http.hpp"
namespace http
{
	inline Version::Version(int first, int second) : _first_digit(first),
	                                          _second_digit(second)

	{}

	inline int first_digit()
	{
		return _first_digit;
	}
	inline int second_digit()
	{
		return _second_digit;
	}

	inline void first_digit(int val)
	{
		_first_digit = val;
	}

	inline void second_digit(int val)
	{
		_second_digit = val;
	}
	constexpr inline bool operator==(const Version& lhs, const Version& rhs)
	{
		return (lhs.first_digit()  == rhs.first_digit())
		    && (lhs.second_digit() == rhs.second_digit());
	}
	constexpr inline bool operator!=(const Version& lhs, const Version& rhs)
	{
		return !(lhs == rhs);
	}

	constexpr inline bool operator<(const Version& lhs, const Version& rhs)
	{
		return lhs.first_digit() == rhs.first_digit() ?
		       lhs.second_digit() < rhs.second_digit() :
		       lhs.first_digit() < rhs.first_digit();
	}
	constexpr inline bool operator>(const Version& lhs, const Version& rhs)
	{
		return !(lhs < rhs);
	}

}
#endif

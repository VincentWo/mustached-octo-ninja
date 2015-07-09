#ifndef __http_version_impl_hpp
#define __http_version_impl_hpp
#include "http.hpp"
namespace http
{
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
		return lhs.first_digit() == rhs.first_digit()
		     ? lhs.second_digit() < rhs.second_digit()
		     : lhs.first_digit() < rhs.first_digit();
	}
	constexpr inline bool operator>(const Version& lhs, const Version& rhs)
	{
		return lhs.first_digit() == rhs.first_digit()
		     ? lhs.second_digit() > rhs.second_digit()
		     : lhs.first_digit() > rhs.first_digit();
	}

}
#endif //__http_version_imp_hpp

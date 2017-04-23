#ifndef _STRING_SET_
#define _STRING_SET_

#include <string>
#include <set>

#include <side.h>

// Sorts from right to left instead of left to right
// Equivalent to if std::less was called with both strings reversed
struct ReverseLess
{

		bool operator()(const std::string& first, const std::string& second) const;

};

typedef std::set<std::string, std::less<std::string>> ForwardStringSet;
typedef std::set<std::string, ReverseLess> ReverseStringSet;


template <Side::e side>
struct TypeTraits;

template <>
struct TypeTraits<Side::Left>
{
	typedef ForwardStringSet Set;
};

template <>
struct TypeTraits<Side::Right>
{
	typedef ReverseStringSet Set;
};

#endif

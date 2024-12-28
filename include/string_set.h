#ifndef _STRING_SET_
#define _STRING_SET_

#include <string>
#include <set>

#include <side.h>

//! Binary operator used to sort strings from right to left instead of left to right.
//! Equivalent to if std::less was called with both strings reversed.
struct ReverseLess
{

	bool operator()(const std::string& first, const std::string& second) const;

};

//! Helper class necessary for full specialization of using template alias
template <Side side>
struct SetSpecializationHelper;

template <>
struct SetSpecializationHelper<Side::Left>
{
	using Set = std::set<std::string, std::less<std::string>>;
};

template <>
struct SetSpecializationHelper<Side::Right>
{
	using Set = std::set<std::string, ReverseLess>;
};

//! Generalized version of sorted string set which is ForwardStringSet for Side::Left and
//! ReverseStringSet for Side::Right
template <Side side>
using SortedStringSet = typename SetSpecializationHelper<side>::Set;

#endif

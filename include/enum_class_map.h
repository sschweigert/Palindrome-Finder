#ifndef _ENUM_CLASS_MAP_
#define _ENUM_CLASS_MAP_

#include <unordered_map>

struct EnumClassHash
{
	template <typename T>
	std::size_t operator()(T t) const
	{
		return static_cast<std::size_t>(t);
	}
};

template <class EnumType, class ValueType>
using EnumMap = std::unordered_map<EnumType, ValueType, EnumClassHash>;

#endif

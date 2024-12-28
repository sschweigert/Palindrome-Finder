#ifndef _DOUBLE_ORDERED_SET_H_
#define _DOUBLE_ORDERED_SET_H_

#include <string_set.h>
#include <string>
#include <vector>

struct DoubleOrderedSet
{

	DoubleOrderedSet(const std::vector<std::string>& words) :
		forward(words.begin(), words.end()),
		reverse(words.begin(), words.end())
	{}

	SortedStringSet<Side::Left> forward;

	SortedStringSet<Side::Right> reverse;

};

#endif

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

	ForwardStringSet forward;

	ReverseStringSet reverse;

};

#endif

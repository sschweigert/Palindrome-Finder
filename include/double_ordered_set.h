#ifndef _DOUBLE_ORDERED_SET_H_
#define _DOUBLE_ORDERED_SET_H_

#include <string_set.h>
#include <string>
#include <vector>

struct DoubleOrderedSet
{

	SortedStringSet<Side::Left> forward;

	SortedStringSet<Side::Right> reverse;

};

DoubleOrderedSet buildFrom(const std::vector<std::string>& words) {
	return { 
		{words.begin(), words.end()},
		{words.begin(), words.end()}
	};
}


#endif

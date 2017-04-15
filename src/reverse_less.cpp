#include <reverse_less.h>

#include <algorithm>

bool ReverseLess::operator()(const std::string& first, const std::string& second) const
{
	std::string reversedFirst = first;	
	std::string reversedSecond = second;	

	reverse(reversedFirst.begin(), reversedFirst.end());
	reverse(reversedSecond.begin(), reversedSecond.end());
	return reversedFirst < reversedSecond;
}

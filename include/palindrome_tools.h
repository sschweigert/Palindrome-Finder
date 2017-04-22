#ifndef _PALINDROME_TOOLS_
#define _PALINDROME_TOOLS_

#include <string>
#include <boost/optional.hpp>

#include <side.h>

template <class Iterator>
void incrementPastSpaces(Iterator& iterator)
{
	while (*iterator == ' ')
	{
		++iterator;
	}
}

bool isPalindrome(const std::string& first);

template <Side::e side = Side::Left>
boost::optional<std::string> incrementWord(std::string toIncrement);

std::string reverseString(const std::string& toReverse);

#endif

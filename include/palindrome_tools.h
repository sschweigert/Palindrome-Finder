#ifndef _PALINDROME_TOOLS_
#define _PALINDROME_TOOLS_

#include <string>
#include <boost/optional.hpp>

template <class Iterator>
void incrementPastSpaces(Iterator& iterator)
{
	while (*iterator == ' ')
	{
		++iterator;
	}
}

bool isPalindrome(const std::string& first);

boost::optional<std::string> incrementWord(std::string toIncrement);

std::string reverseString(const std::string& toReverse);

#endif

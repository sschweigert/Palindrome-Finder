#ifndef _PALINDROME_TOOLS_
#define _PALINDROME_TOOLS_

#include <string>

template <class Iterator>
void incrementPastSpaces(Iterator& iterator)
{
	while (*iterator == ' ')
	{
		++iterator;
	}
}

bool isPalindrome(const std::string& first);

#endif

#include <palindrome_tools.h>

bool isPalindrome(const std::string& first)
{
	auto forwardItr = first.begin();
	auto reverseItr = first.rbegin();

	while (forwardItr != first.end())
	{
		incrementPastSpaces(forwardItr);
		incrementPastSpaces(reverseItr);

		if (*forwardItr != *reverseItr)
		{
			return false;
		}

	}
	return true;	
}

std::string incrementWord(std::string toIncrement)
{
	int i = toIncrement.size() - 1;

	// Remove all z characters except the first one
	// in the case of string of z's (ie "zzzzzzz")
	while (toIncrement[i] == 'z' && i > 0)
	{
		toIncrement[i] = 'a';
		--i;
	}

	// First character is a z
	if (toIncrement[i] == 'z')
	{
		// Last 'z' is special because string length is increased
		toIncrement[i] = 'a';
		toIncrement = 'a' + toIncrement;
	}
	else
	{
		// Normal increment (most cases will just do this to the
		// last letter)
		toIncrement[i] = toIncrement[i] + (char)1;
	}
	return toIncrement;
}

std::string reverseString(const std::string& toReverse)
{
	std::string toReturn(toReverse.rbegin(), toReverse.rend());
	return toReturn;
}

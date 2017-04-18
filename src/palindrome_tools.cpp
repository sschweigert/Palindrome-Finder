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

boost::optional<std::string> incrementWord(std::string toIncrement)
{
	std::string toReturn = toIncrement;
	int i = toReturn.size() - 1;

	// Remove all z characters except the first one
	// in the case of string of z's (ie "zzzzzzz")
	while (toReturn[i] == 'z' && i > 0)
	{
		toReturn[i] = 'a';
		--i;
	}

	// First character is a z
	if (toReturn[i] == 'z')
	{
		// All characters were z, so no way to icnrement
		return boost::none;
	}
	else
	{
		// Normal increment (most cases will just do this to the
		// last letter)
		toReturn[i] = toReturn[i] + (char)1;
	}
	return toReturn;
}

std::string reverseString(const std::string& toReverse)
{
	std::string toReturn(toReverse.rbegin(), toReverse.rend());
	return toReturn;
}

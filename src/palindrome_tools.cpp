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

		++forwardItr;
		++reverseItr;
	}
	return true;	
}

template <class IteratorType>
bool incrementImpl(IteratorType rbegin, IteratorType rend)
{
	auto itr = rbegin;
	auto secondLast = std::prev(rend);

	// Remove all z characters except the first one
	// in the case of string of z's (ie "zzzzzzz")
	while (*itr == 'z' && itr != secondLast)
	{
		*itr = 'a';
		++itr;
	}

	// First character is a z
	if (*itr == 'z')
	{
		// All characters were z, so no way to icnrement
		return false;
	}
	else
	{
		// Normal increment (most cases will just do this to the
		// last letter)
		*itr = *itr + (char)1;
	}
	return true;
}

template <>
boost::optional<std::string> incrementWord<Side::Left>(std::string toIncrement)
{
	std::string toReturn = toIncrement;
	incrementImpl(toReturn.rbegin(), toReturn.rend());
	return toReturn;
}

template <>
boost::optional<std::string> incrementWord<Side::Right>(std::string toIncrement)
{
	std::string toReturn = toIncrement;
	incrementImpl(toReturn.begin(), toReturn.end());
	return toReturn;
}

std::string reverseString(const std::string& toReverse)
{
	std::string toReturn(toReverse.rbegin(), toReverse.rend());
	return toReturn;
}

#include <palindrome_tools.h>

template <class Iterator>
void incrementPastSpaces(Iterator& iterator)
{
	while (*iterator == ' ')
	{
		++iterator;
	}
}

template <class Iterator>
void incrementToFirstNotZ(Iterator& iterator, Iterator end)
{
	while (iterator != end && *iterator == 'z')
	{
		++iterator;
	}
}

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

template <>
boost::optional<std::string> wordTailBounds<Side::Left>(const std::string& toIncrement)
{
	std::string::const_reverse_iterator iterator = toIncrement.rbegin();
	std::string::const_reverse_iterator end = toIncrement.rend();

	incrementToFirstNotZ(iterator, end);
	
	if (iterator != end)
	{
		size_t toReturnSize = std::distance(iterator, end);
		std::string toReturn(toReturnSize, ' ');

		std::string::reverse_iterator insertIterator = toReturn.rbegin();

		do
		{
			*insertIterator = *iterator;
			++iterator;
			++insertIterator;
		} while (iterator != end);

		toReturn.back() = toReturn.back() + (char)1;

		return toReturn;
	}
	else
	{
		return boost::none;
	}
}

template <>
boost::optional<std::string> wordTailBounds<Side::Right>(const std::string& toIncrement)
{
	std::string::const_iterator iterator = toIncrement.begin();
	std::string::const_iterator end = toIncrement.end();

	incrementToFirstNotZ(iterator, end);
	
	if (iterator != end)
	{
		std::string toReturn(iterator, end);

		toReturn.front() = toReturn.front() + (char)1;

		return toReturn;
	}
	else
	{
		return boost::none;
	}
}

std::string reverseString(const std::string& toReverse)
{
	std::string toReturn(toReverse.rbegin(), toReverse.rend());
	return toReturn;
}

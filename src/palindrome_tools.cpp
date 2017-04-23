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
std::string buildWordFromIterators(std::string::const_iterator begin, std::string::const_iterator end)
{
	return std::string(begin, end);
}

template <>
std::string buildWordFromIterators(std::string::const_reverse_iterator iterator, std::string::const_reverse_iterator end)
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
	return toReturn;
}

template <>
BackwardsRange<Side::Left> getBackwardsRange<Side::Left>(const std::string& word)
{
	BackwardsRange<Side::Left> toReturn;
	toReturn.iterator = word.rbegin();
	toReturn.end = word.rend();
	return toReturn;
}

template <>
BackwardsRange<Side::Right> getBackwardsRange<Side::Right>(const std::string& word)
{
	BackwardsRange<Side::Right> toReturn;
	toReturn.iterator = word.begin();
	toReturn.end = word.end();
	return toReturn;
}

template <>
boost::optional<std::string> wordTailBounds<Side::Left>(const std::string& toIncrement)
{
	BackwardsRange<Side::Left> backwardsRange = getBackwardsRange<Side::Left>(toIncrement);

	incrementToFirstNotZ(backwardsRange.iterator, backwardsRange.end);
	
	if (backwardsRange.iterator != backwardsRange.end)
	{
		std::string toReturn = buildWordFromIterators(backwardsRange.iterator, backwardsRange.end);

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
	BackwardsRange<Side::Right> backwardsRange = getBackwardsRange<Side::Right>(toIncrement);

	incrementToFirstNotZ(backwardsRange.iterator, backwardsRange.end);
	
	if (backwardsRange.iterator != backwardsRange.end)
	{
		std::string toReturn = buildWordFromIterators(backwardsRange.iterator, backwardsRange.end);

		toReturn.front() = toReturn.front() + (char)1;

		return toReturn;
	}
	else
	{
		return boost::none;
	}
}

//template boost::optional<std::string> wordTailBounds<Side::Right>(const std::string& toIncrement);
//template boost::optional<std::string> wordTailBounds<Side::Left>(const std::string& toIncrement);

std::string reverseString(const std::string& toReverse)
{
	std::string toReturn(toReverse.rbegin(), toReverse.rend());
	return toReturn;
}

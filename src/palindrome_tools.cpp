#include <palindrome_tools.h>

#include <iostream>

void incrementPastSpaces(std::string::const_iterator& iterator)
{
	while (*iterator == ' ')
	{
		++iterator;
	}
}

void decrementPastSpaces(std::string::const_iterator& iterator)
{
	while (*iterator == ' ')
	{
		--iterator;
	}
}

template <class Iterator>
void incrementToFirstNotZ(Iterator& iterator, const Iterator& end)
{
	while (iterator != end && *iterator == 'z')
	{
		++iterator;
	}
}

bool isSpacedPalindrome(const std::string& first)
{
	auto forwardItr = first.begin();
	auto reverseItr = std::prev(first.end());

	while (forwardItr <= reverseItr)
	{
		incrementPastSpaces(forwardItr);
		decrementPastSpaces(reverseItr);

		// The iterators overlapped each other while
		// going over a space.
		if (forwardItr > reverseItr)
		{
			return true;
		}

		if (*forwardItr != *reverseItr)
		{
			// Characters don't match
			return false;
		}

		++forwardItr;
		--reverseItr;
	}
	return true;	
}

bool isPalindrome(const std::string& first)
{
	auto forwardItr = first.begin();
	auto reverseItr = std::prev(first.end());

	while (forwardItr <= reverseItr)
	{
		if (*forwardItr != *reverseItr)
		{
			return false;
		}

		++forwardItr;
		--reverseItr;
	}
	return true;	
}

template <>
std::string buildWordFromIterators(std::string::const_iterator begin, std::string::const_iterator end)
{
	// Simple implementation
	return std::string(begin, end);
}

template <>
std::string buildWordFromIterators(std::string::const_reverse_iterator iterator, std::string::const_reverse_iterator end)
{
	// Pre-allocate std::string
	size_t toReturnSize = std::distance(iterator, end);
	std::string toReturn(toReturnSize, ' ');

	// Iterator used for inserting
	std::string::reverse_iterator insertIterator = toReturn.rbegin();

	do
	{
		// Insert
		*insertIterator = *iterator;

		// Increment
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
char& endOfWord<Side::Left>(std::string& word)
{
	return word.back();
}

template <>
char& endOfWord<Side::Right>(std::string& word)
{
	return word.front();
}

template <Side side>
boost::optional<std::string> wordTailBounds(const std::string& toIncrement)
{
	BackwardsRange<side> backwardsRange = getBackwardsRange<side>(toIncrement);

	incrementToFirstNotZ(backwardsRange.iterator, backwardsRange.end);
	
	if (backwardsRange.iterator != backwardsRange.end)
	{
		std::string toReturn = buildWordFromIterators(backwardsRange.iterator, backwardsRange.end);

		// Add to the last character so that it is larger
		char& charToIncrement = endOfWord<side>(toReturn);
		charToIncrement = charToIncrement + (char)1;

		return toReturn;
	}
	else
	{
		return boost::none;
	}
}

template boost::optional<std::string> wordTailBounds<Side::Right>(const std::string& toIncrement);
template boost::optional<std::string> wordTailBounds<Side::Left>(const std::string& toIncrement);

std::string reverseString(const std::string& toReverse)
{
	std::string toReturn(toReverse.rbegin(), toReverse.rend());
	return toReturn;
}

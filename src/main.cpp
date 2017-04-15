#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
#include <stack>

#include <reverse_less.h>

template <class Iterator>
void incrementPastSpaces(Iterator& iterator)
{
	while (*iterator == ' ')
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

	}
	return true;	
}

enum class Side
{

	Left,

	Right

};

template <class IteratorType>
struct IteratorBounds
{

	IteratorType lowerBound;
	IteratorType upperBound;

};

int main(int argc, char** argv)
{
	
	std::fstream fileStream;
	fileStream.open("/home/sebastian/Downloads/words.txt", std::fstream::in);

	typedef std::set<std::string, std::less<std::string>> ForwardStringSet;
	typedef std::set<std::string, ReverseLess> ReverseStringSet;

	ForwardStringSet forwardOrdering;
	ReverseStringSet backwardOrdering;

	while (!fileStream.eof())
	{
		std::string line;
		fileStream >> line;
		
		forwardOrdering.insert(line);
		backwardOrdering.insert(line);
	}

	int numberOfWords = 3;

	std::vector<std::string> palindromes;

	std::vector<ForwardStringSet::iterator> forwardIterators;
	std::vector<ReverseStringSet::iterator> reverseIterators;

	std::vector<IteratorBounds<ForwardStringSet::iterator>> forwardIteratorBounds;
	std::vector<IteratorBounds<ReverseStringSet::iterator>> reverseIteratorBounds;

	ForwardStringSet::iterator seedIterator = forwardOrdering.begin();

	while (seedIterator != forwardOrdering.end())
	{
		int leftCharacters = 0;
		int rightCharacters = 0;
		int numberOfWordsSoFar = 0;
		
		// Setup first/seed word
		forwardIterators.push_back(seedIterator);
		leftCharacters += seedIterator->size();

		++numberOfWordsSoFar;

		// Insert new words
		while (numberOfWordsSoFar < numberOfWords)
		{
			if (leftCharacters >= rightCharacters)
			{
				// Begin inserting right words

				// Number of left characters that must be matched by the new right characters
				int numMatchingCharacters = leftCharacters - rightCharacters;

				int accumulatedChars = 0;

				int index = forwardIterators.size() - 1;
				for (; index >= 0 && accumulatedChars < numMatchingCharacters; --index)
				{
					accumulatedChars += forwardIterators[index]->size();	
				}

				int firstCharPosition = accumulatedChars - numMatchingCharacters;

				std::string matchingCharacters = "";

				// Deal with overlapping word
				matchingCharacters.insert(0, *(forwardIterators[index]), firstCharPosition, std::string::npos);
				++index;

				for (; index < forwardIterators.size() - 1; ++index)
				{
					matchingCharacters += *(forwardIterators[index]);
				}

				reverse(matchingCharacters.begin(), matchingCharacters.end());

				IteratorBounds<ReverseStringSet::iterator> newBounds;
				newBounds.lowerBound = backwardOrdering.lower_bound(matchingCharacters);
				newBounds.upperBound = backwardOrdering.upper_bound(matchingCharacters);

				
			}
			else
			{

			}

			++numberOfWordsSoFar;
			
		}

		// Check "overhanging" characters

		++seedIterator;
	}

	std::cout << *backwardOrdering.lower_bound("test") << std::endl;
	std::cout << *backwardOrdering.upper_bound("test") << std::endl;

	std::cout << "Found the following palindromes: " << std::endl;
	for (const auto& palindrome : palindromes)
	{
		std::cout << palindrome << std::endl;
	}

	return 0;
}

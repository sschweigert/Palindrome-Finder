#include <superword_iterator.h>

#include <palindrome_tools.h>
#include <algorithm>

#include <iostream>

ForwardSuperwordIterator::ForwardSuperwordIterator(const std::string& wordToMatch, const ForwardStringSet& wordsToSearch) :
	mCurrentValue(wordsToSearch.upper_bound(wordToMatch)),
	mUpperBounds(calculateUpperBounds(wordToMatch, wordsToSearch))
{

}

const std::string& ForwardSuperwordIterator::operator*() const
{
	return *mCurrentValue;	
}

bool ForwardSuperwordIterator::hasNext()
{
	return mCurrentValue != mUpperBounds;
}

IWordCandidateIterator& ForwardSuperwordIterator::operator++()
{
	++mCurrentValue;
	return *this;
}	

ForwardStringSet::const_iterator ForwardSuperwordIterator::calculateUpperBounds(const std::string& wordToMatch, const ForwardStringSet& wordsToSearch)
{
	boost::optional<std::string> incrementedWord = incrementWord(wordToMatch);
	if (incrementedWord)
	{
		return wordsToSearch.lower_bound(*incrementedWord);
	}
	else
	{
		// Special case where word is all 'z'
		return wordsToSearch.end();
	}
}

ReverseSuperwordIterator::ReverseSuperwordIterator(const std::string& wordToMatch, const ReverseStringSet& wordsToSearch) :
	mCurrentValue(wordsToSearch.upper_bound(wordToMatch)),
	mUpperBounds(calculateUpperBounds(wordToMatch, wordsToSearch))
{

}

const std::string& ReverseSuperwordIterator::operator*() const
{
	return *mCurrentValue;	
}

bool ReverseSuperwordIterator::hasNext()
{
	return mCurrentValue != mUpperBounds;
}

IWordCandidateIterator& ReverseSuperwordIterator::operator++()
{
	++mCurrentValue;
	return *this;
}	

ReverseStringSet::const_iterator ReverseSuperwordIterator::calculateUpperBounds(const std::string& wordToMatch, const ReverseStringSet& wordsToSearch)
{
	std::string reverseTemp = wordToMatch;
	reverse(reverseTemp.begin(), reverseTemp.end());

	boost::optional<std::string> incrementedWord = incrementWord(reverseTemp);

	if (incrementedWord)
	{
		reverseTemp = *incrementedWord;
		reverse(reverseTemp.begin(), reverseTemp.end());

		return wordsToSearch.lower_bound(reverseTemp);
	}
	else
	{
		// Special case where word is all 'z'
		return wordsToSearch.end();
	}
}

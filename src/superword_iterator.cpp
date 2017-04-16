#include <superword_iterator.h>

#include <palindrome_tools.h>
#include <algorithm>

ForwardSuperwordIterator::ForwardSuperwordIterator(const std::string& wordToMatch, const ForwardStringSet& wordsToSearch) :
	mCurrentValue(wordsToSearch.upper_bound(wordToMatch)),
	mUpperBounds(calculateUpperBounds(wordToMatch, wordsToSearch))
{

}

std::string ForwardSuperwordIterator::operator*()
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
	std::string incrementedWord = incrementWord(wordToMatch);
	return wordsToSearch.lower_bound(incrementedWord);
}

ReverseSuperwordIterator::ReverseSuperwordIterator(const std::string& wordToMatch, const ReverseStringSet& wordsToSearch) :
	mCurrentValue(wordsToSearch.upper_bound(wordToMatch)),
	mUpperBounds(calculateUpperBounds(wordToMatch, wordsToSearch))
{

}

std::string ReverseSuperwordIterator::operator*()
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

	std::string incrementedWord = incrementWord(reverseTemp);
	reverse(incrementedWord.begin(), incrementedWord.end());

	return wordsToSearch.lower_bound(incrementedWord);
}

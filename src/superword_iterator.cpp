#include <superword_iterator.h>

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

std::string ForwardSuperwordIterator::incrementWord(std::string toIncrement)
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
	if (i == 0)
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

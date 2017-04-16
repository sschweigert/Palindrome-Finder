#include <subword_iterator.h>

ForwardSubwordIterator::ForwardSubwordIterator(const std::string& wordToMatch, const ForwardStringSet& wordsToSearch) :
	mHasNext(true),
	mIndex(-1),
	mWordToMatch(wordToMatch),	
	mWordsToSearch(wordsToSearch),
	mSubWord("")
{
	operator++();
}

std::string ForwardSubwordIterator::operator*() 
{
	return mSubWord;	
}

bool ForwardSubwordIterator::hasNext()
{
	return mHasNext;
}

IWordCandidateIterator& ForwardSubwordIterator::operator++()
{
	// Note we ignore the case of the full word
	while (++mIndex < (int)mWordToMatch.size() - 1)
	{
		mSubWord += mWordToMatch[mIndex];
		if (mWordsToSearch.count(mSubWord) == 1)
		{
			// Subword is valid, so break out of loop
			return *this;
		}	
	}

	// Reached end of word so there is nothing new to add
	mHasNext = false;

	return *this;
}	

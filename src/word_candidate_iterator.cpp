#include <word_candidate_iterator.h>

ForwardCandidateIterator::ForwardCandidateIterator(const std::string& wordToMatch, const ForwardStringSet& wordsToSearch) :
	mCurrentState(State::SubWord),
	mSubwordIterator(wordToMatch, wordsToSearch),
	mSuperwordIterator(wordToMatch, wordsToSearch)
{

}

std::string ForwardCandidateIterator::operator*() const
{
	if (mCurrentState == State::SubWord)
	{
		return *mSubwordIterator;	
	}
	else
	{
		return *mSuperwordIterator;
	}
}

bool ForwardCandidateIterator::hasNext()
{
	if (mCurrentState == State::SubWord)
	{
		return true;		
	}
	else
	{
		return mSuperwordIterator.hasNext();
	}
}

IWordCandidateIterator& ForwardCandidateIterator::operator++()
{
	if (mCurrentState == State::SubWord)
	{
		++mSubwordIterator;
		if (!mSubwordIterator.hasNext())
		{
			mCurrentState = State::Superword;
		}				
	}
	else
	{
		++mSuperwordIterator;
	}
	return *this;
}

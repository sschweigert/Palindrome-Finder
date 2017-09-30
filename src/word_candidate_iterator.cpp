#include <word_candidate_iterator.h>

template <Side side>
WordCandidateIterator<side>::WordCandidateIterator(std::string wordToMatch, const SortedStringSet<side>& wordsToSearch) :
	mWordToMatch(wordToMatch),
	mSubwordIterator(mWordToMatch, wordsToSearch),
	mSuperwordIterator(mWordToMatch, wordsToSearch),
	mCurrentState(mSubwordIterator.hasNext() ? State::SubWord : State::Superword)
{
}

template <Side side>
const std::string& WordCandidateIterator<side>::operator*() const
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

template <Side side>
bool WordCandidateIterator<side>::hasNext()
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

template <Side side>
IWordCandidateIterator<side>& WordCandidateIterator<side>::operator++()
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

// Explicit instantiations
template class WordCandidateIterator<Side::Left>;
template class WordCandidateIterator<Side::Right>;

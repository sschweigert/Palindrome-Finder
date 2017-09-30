#include <word_candidate_iterator.h>

template <Side side>
WordCandidateIterator<side>::WordCandidateIterator(const std::string& wordToMatch, const SortedStringSet<side>& wordsToSearch) :
	mSubwordIterator(wordToMatch, wordsToSearch),
	mSuperwordIterator(wordToMatch, wordsToSearch),
	mCurrentState(mSubwordIterator.hasNext() ? State::SubWord : State::Superword)
{}

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
bool WordCandidateIterator<side>::hasNext() const
{
	if (mCurrentState == State::SubWord)
	{
		// If the subword iterator is done, the class will switch states.
		// Therefore, being in subword state implies that subword iterator is
		// not done.
		return true;		
	}
	else
	{
		return mSuperwordIterator.hasNext();
	}
}

template <Side side>
IWordIterator& WordCandidateIterator<side>::operator++()
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

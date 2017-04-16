#ifndef _WORD_CANDIDATE_ITERATOR_
#define _WORD_CANDIDATE_ITERATOR_

#include <iword_candidate_iterator.h>
#include <subword_iterator.h>
#include <superword_iterator.h>

template <class SubwordType, class SuperwordType>
class WordCandidateIterator : public IWordCandidateIterator
{

	public:

		WordCandidateIterator(const std::string& wordToMatch, const ForwardStringSet& wordsToSearch) :
			mCurrentState(State::SubWord),
			mSubwordIterator(wordToMatch, wordsToSearch),
			mSuperwordIterator(wordToMatch, wordsToSearch)
			{

			}

		virtual std::string operator*()
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

		virtual bool hasNext()
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

		virtual IWordCandidateIterator& operator++()
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

	private:

		enum class State
		{

			SubWord,

			Superword			

		};

		State mCurrentState;

		SubwordType mSubwordIterator;

		SuperwordType mSuperwordIterator;

};

typedef WordCandidateIterator<ForwardSubwordIterator, ForwardSuperwordIterator> ForwardCandidateIterator;
typedef WordCandidateIterator<ReverseSubwordIterator, ReverseSuperwordIterator> ReverseCandidateIterator;

#endif

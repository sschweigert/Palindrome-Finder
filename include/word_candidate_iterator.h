#ifndef _WORD_CANDIDATE_ITERATOR_
#define _WORD_CANDIDATE_ITERATOR_

#include <iword_candidate_iterator.h>
#include <subword_iterator.h>
#include <superword_iterator.h>

#include <iostream>

#include <side.h>
#include <string_set.h>

template <Side::e side>
class WordCandidateIterator : public IWordCandidateIterator<side>
{

	typedef typename TypeTraits<side>::Set Set;

	public:

		WordCandidateIterator(std::string wordToMatch, const Set& wordsToSearch) :
			mWordToMatch(wordToMatch),
			mSubwordIterator(mWordToMatch, wordsToSearch),
			mSuperwordIterator(mWordToMatch, wordsToSearch),
			mCurrentState(mSubwordIterator.hasNext() ? State::SubWord : State::Superword)
			{
			}

		virtual const std::string& operator*() const
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

		virtual IWordCandidateIterator<side>& operator++()
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

		std::string mWordToMatch;

		SubwordIterator<side> mSubwordIterator;

		SuperwordIterator<side> mSuperwordIterator;

		State mCurrentState;

};

typedef WordCandidateIterator<Side::Left> ForwardCandidateIterator;
typedef WordCandidateIterator<Side::Right> ReverseCandidateIterator;

#endif

#ifndef _WORD_CANDIDATE_ITERATOR_
#define _WORD_CANDIDATE_ITERATOR_

#include <iword_candidate_iterator.h>
#include <subword_iterator.h>
#include <superword_iterator.h>

#include <iostream>

template <class SubwordType, class SuperwordType, class StringSetType, class Interface>
class WordCandidateIterator : public Interface 
{

	public:

		WordCandidateIterator(std::string wordToMatch, const StringSetType& wordsToSearch) :
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

		std::string mWordToMatch;

		SubwordType mSubwordIterator;

		SuperwordType mSuperwordIterator;

		State mCurrentState;

};

typedef WordCandidateIterator<SubwordIterator<Side::Left>, ForwardSuperwordIterator, ForwardStringSet, IForwardWordCandidateIterator> ForwardCandidateIterator;
typedef WordCandidateIterator<SubwordIterator<Side::Right>, ReverseSuperwordIterator, ReverseStringSet, IReverseWordCandidateIterator> ReverseCandidateIterator;

#endif

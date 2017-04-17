#ifndef _WORD_CANDIDATE_ITERATOR_
#define _WORD_CANDIDATE_ITERATOR_

#include <iword_candidate_iterator.h>
#include <subword_iterator.h>
#include <superword_iterator.h>

template <class SubwordType, class SuperwordType, class StringSetType, class Interface>
class WordCandidateIterator : public Interface 
{

	public:

		WordCandidateIterator(std::string wordToMatch, const StringSetType& wordsToSearch) :
			mWordToMatch(wordToMatch),
			mCurrentState(State::SubWord),
			mSubwordIterator(mWordToMatch, wordsToSearch),
			mSuperwordIterator(mWordToMatch, wordsToSearch)
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

typedef WordCandidateIterator<ForwardSubwordIterator, ForwardSuperwordIterator, ForwardStringSet, IForwardWordCandidateIterator> ForwardCandidateIterator;
typedef WordCandidateIterator<ReverseSubwordIterator, ReverseSuperwordIterator, ReverseStringSet, IReverseWordCandidateIterator> ReverseCandidateIterator;

#endif

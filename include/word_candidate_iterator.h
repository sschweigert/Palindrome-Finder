#ifndef _WORD_CANDIDATE_ITERATOR_
#define _WORD_CANDIDATE_ITERATOR_

#include <iword_candidate_iterator.h>
#include <subword_iterator.h>
#include <superword_iterator.h>

class ForwardCandidateIterator : public IWordCandidateIterator
{

	public:

		ForwardCandidateIterator(const std::string& wordToMatch, const ForwardStringSet& wordsToSearch);

		virtual std::string operator*();

		virtual bool hasNext();

		virtual IWordCandidateIterator& operator++();

	private:

		enum class State
		{

			SubWord,

			Superword			

		};

		State mCurrentState;

		ForwardSubwordIterator mSubwordIterator;

		ForwardSuperwordIterator mSuperwordIterator;

};

#endif

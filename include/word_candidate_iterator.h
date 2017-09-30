#ifndef _WORD_CANDIDATE_ITERATOR_
#define _WORD_CANDIDATE_ITERATOR_

#include <iword_candidate_iterator.h>
#include <subword_iterator.h>
#include <superword_iterator.h>

#include <iostream>

#include <side.h>
#include <string_set.h>

template <Side side>
class WordCandidateIterator : public IWordCandidateIterator<side>
{

	public:

		WordCandidateIterator(const std::string& wordToMatch, const SortedStringSet<side>& wordsToSearch);

		virtual const std::string& operator*() const;

		virtual bool hasNext();

		virtual IWordCandidateIterator<side>& operator++();

	private:

		enum class State
		{

			SubWord,

			Superword			

		};

		SubwordIterator<side> mSubwordIterator;

		SuperwordIterator<side> mSuperwordIterator;

		State mCurrentState;

};

typedef WordCandidateIterator<Side::Left> ForwardCandidateIterator;
typedef WordCandidateIterator<Side::Right> ReverseCandidateIterator;

#endif

#ifndef _WORD_CANDIDATE_ITERATOR_
#define _WORD_CANDIDATE_ITERATOR_

#include <subword_iterator.h>
#include <superword_iterator.h>

#include <side.h>
#include <string_set.h>

template <Side side>
class WordCandidateIterator
{

	public:

		WordCandidateIterator(const std::string& wordToMatch, const SortedStringSet<side>& wordsToSearch);

		const std::string& operator*() const;

		bool hasNext() const; 

		WordCandidateIterator<side>& operator++();

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

using ForwardCandidateIterator = WordCandidateIterator<Side::Left>;
using ReverseCandidateIterator = WordCandidateIterator<Side::Right>;

#endif

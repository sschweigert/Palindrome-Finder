#ifndef _SUPERWORD_ITERATOR_
#define _SUPERWORD_ITERATOR_

#include <iword_candidate_iterator.h>
#include <string_set.h>

class ForwardSuperwordIterator : public IWordCandidateIterator
{

	public:

		ForwardSuperwordIterator(const std::string& wordToMatch, const ForwardStringSet& wordsToSearch);

		virtual std::string operator*();

		virtual bool hasNext();

		virtual IWordCandidateIterator& operator++();

	private:

		ForwardStringSet::const_iterator calculateUpperBounds(const std::string& wordToMatch, const ForwardStringSet& wordsToSearch);

		std::string incrementWord(std::string toIncrement);

		ForwardStringSet::const_iterator mCurrentValue;

		const ForwardStringSet::const_iterator mUpperBounds;

};

#endif

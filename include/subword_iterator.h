#ifndef _SUBWORD_ITERATOR_
#define _SUBWORD_ITERATOR_

#include <iword_candidate_iterator.h>
#include <string_set.h>
#include <side.h>
#include <specialized_subword_behaviors.h>

template <Side side>
class SubwordIterator
{

	public:

		typedef typename TypeTraits<side>::Set Set;

		SubwordIterator(const std::string& wordToMatch, const Set& wordsToSearch);

		const std::string& operator*() const;

		bool hasNext();

		SubwordIterator<side>& operator++();

	private:

		void next();

		typename SpecializedSubwordBehaviors<side>::iterator current;

		typename SpecializedSubwordBehaviors<side>::iterator end;

		const Set& mWordsToSearch;

		std::string mSubWord;

};


#endif

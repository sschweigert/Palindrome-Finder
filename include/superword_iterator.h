#ifndef _SUPERWORD_ITERATOR_
#define _SUPERWORD_ITERATOR_

#include <iword_candidate_iterator.h>
#include <string_set.h>
#include <side.h>
#include <boost/optional.hpp>
#include <palindrome_tools.h>
#include <algorithm>

template <Side side>
class SuperwordIterator
{

	typedef SortedStringSet<side> Set;

	public:

		SuperwordIterator(const std::string& wordToMatch, const Set& wordsToSearch);

		const std::string& operator*() const;

		bool hasNext();

		SuperwordIterator<side>& operator++();

	private:

		typename Set::const_iterator calculateUpperBounds(const std::string& wordToMatch, const Set& wordsToSearch);

		typename Set::const_iterator mCurrentValue;

		const typename Set::const_iterator mUpperBounds;

};

#endif

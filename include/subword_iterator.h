#ifndef _SUBWORD_ITERATOR_
#define _SUBWORD_ITERATOR_

#include <iword_candidate_iterator.h>
#include <string_set.h>
#include <side.h>
#include <specialized_subword_behaviors.h>

//! \brief An iterator that is used to find substrings of a string which have corresponding entries in a set.
//! The input is a string to be used to generate the search criteria and a set of sorted strings to search.
//!
//! The search criteria is composed of the subsets of a string, built one character at a time from either
//! the left or the right.
//!
//! For example with  "apple," the following is used as the search criteria: 
//! from left: { "a", "ap", "app", "appl", "apple" }
//! from right: { "e", "le", "ple", "pple", "apple" }
//
//! The template parameter is used to determine if this iterator builds from the left or the right.
//! Different strings are generated depending on the order in which they are built, although both
//! sides will generate the entire string at the end.
//!
//! When constructed or operator++() is called, the iterator will build a word by adding characters,
//! one by one, and will only stop when the resulting word matches one found in the set.
template <Side side>
class SubwordIterator
{

	public:

		SubwordIterator(const std::string& wordToMatch, const SortedStringSet<side>& wordsToSearch);

		const std::string& operator*() const;

		bool hasNext() const;

		SubwordIterator<side>& operator++();

	private:

		//! Starting at current, add characters to mSubWord until a match is found with
		//! the set or end is reached
		void buildUntilMatch();

		//! Current position within the string. At all times this will point to the
		//! last character added to mSubWord, or end() if !hasNext()
		typename SpecializedSubwordBehaviors<side>::iterator current;

		//! Cached generalized version of end()
		typename SpecializedSubwordBehaviors<side>::iterator end;

		//! Local reference to the set of words over which to search
		const SortedStringSet<side>& mWordsToSearch;

		// Incrementally built word which is returned via operator*
		std::string mSubWord;

};


#endif

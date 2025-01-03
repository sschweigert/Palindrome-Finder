#ifndef _SUBWORD_ITERATOR_
#define _SUBWORD_ITERATOR_

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
//! This iterator is either in a valid or invalid state. If hasNext returns true, the iterator contains
//! a value which can be obtained via operator*.
//!
//! When constructed, the iterator will update to first substring which matches in the set. If no value
//! is found, the iterator will be set to the invalid state and hasNext() will return false.
//!
//! When operator++ is called, the iterator will update to the next matching substring, if one exists.
//! If none exists, the iterator will be set to the invalid state and hasNext() will return false.
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

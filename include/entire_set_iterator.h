#ifndef _ENTIRE_SET_ITERATOR_
#define _ENTIRE_SET_ITERATOR_

#include <iword_candidate_iterator.h>
#include <string_set.h>
#include <side.h>

//! \brief Class which iterates over an entire set.
//! This is basically a wrapper for begin() and end() so
//! that it implements IWordCandidateIterator interface.
template <Side side>
class EntireSetIterator : public IWordCandidateIterator<side>
{

	public:

		EntireSetIterator(const SortedStringSet<side>& set);

		virtual const std::string& operator*() const;

		virtual bool hasNext();

		virtual IWordCandidateIterator<side>& operator++();

	private:

		typename SortedStringSet<side>::const_iterator mCurrentPos;

		const SortedStringSet<side>& mData;

};

#endif

#ifndef _IWORD_CANDIDATE_ITERATOR_
#define _IWORD_CANDIDATE_ITERATOR_

#include <string>
#include <side.h>

template <Side::e side>
class IWordCandidateIterator
{

	public:

		virtual const std::string& operator*() const = 0;

		virtual bool hasNext() = 0;

		virtual IWordCandidateIterator<side>& operator++() = 0;

		virtual ~IWordCandidateIterator()
		{}

};

#endif

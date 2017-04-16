#ifndef _IWORD_CANDIDATE_ITERATOR_
#define _IWORD_CANDIDATE_ITERATOR_

#include <string>

class IWordCandidateIterator
{

	public:

		virtual std::string operator*() = 0;

		virtual bool hasNext() = 0;

		virtual IWordCandidateIterator& operator++() = 0;

		virtual ~IWordCandidateIterator()
		{}

};

class IForwardWordCandidateIterator : public IWordCandidateIterator
{

};

class IReverseWordCandidateIterator : public IWordCandidateIterator
{

};


#endif

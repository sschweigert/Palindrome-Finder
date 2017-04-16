#ifndef _IWORD_CANDIDATE_ITERATOR_
#define _IWORD_CANDIDATE_ITERATOR_

#include <string>

class IWordCandidateIterator
{

	public:

		virtual const std::string& operator*() const = 0;

		virtual bool hasNext() = 0;

		virtual IWordCandidateIterator& operator++() = 0;

		const std::string* operator->() const
		{
			return &(this->operator*());
		}

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

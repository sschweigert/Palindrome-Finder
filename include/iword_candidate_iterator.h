#ifndef _IWORD_CANDIDATE_ITERATOR_
#define _IWORD_CANDIDATE_ITERATOR_

#include <string>
#include <side.h>


//! \brief Interface for an iterator that returns a set of words determind by 
//! an algorithm. Implementations of these iterators are used to search through
//! sets of words for ones that can be used to generate palindromes.
class IWordIterator
{

	public:

		//! \brief Get the current word
		virtual const std::string& operator*() const = 0;

		//! \brief Check if there are any more words that can be generated
		virtual bool hasNext() = 0;

		//! \brief Generate and cache the next word
		virtual IWordIterator& operator++() = 0;

		virtual ~IWordIterator()
		{}

};

template <Side side>
class IWordCandidateIterator : public IWordIterator
{};

#endif

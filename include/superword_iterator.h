#ifndef _SUPERWORD_ITERATOR_
#define _SUPERWORD_ITERATOR_

#include <iword_candidate_iterator.h>
#include <string_set.h>
#include <side.h>
#include <boost/optional.hpp>
#include <palindrome_tools.h>
#include <algorithm>

template <Side::e side>
class SuperwordIterator
{

	typedef typename TypeTraits<side>::Set Set;

	public:

		SuperwordIterator(const std::string& wordToMatch, const Set& wordsToSearch) :
			mCurrentValue(wordsToSearch.upper_bound(wordToMatch)),
			mUpperBounds(calculateUpperBounds(wordToMatch, wordsToSearch))
	{

	}

		const std::string& operator*() const
		{
			return *mCurrentValue;	
		}

		bool hasNext()
		{
			return mCurrentValue != mUpperBounds;
		}

		auto operator++() -> decltype(*this)&
		{
			++mCurrentValue;
			return *this;
		}	

	private:

		typename Set::const_iterator calculateUpperBounds(const std::string& wordToMatch, const Set& wordsToSearch)
		{
			boost::optional<std::string> incrementedWord = wordTailBounds<side>(wordToMatch);

			if (incrementedWord)
			{
				return wordsToSearch.lower_bound(*incrementedWord);
			}
			else
			{
				// Special case where word is all 'z'
				return wordsToSearch.end();
			}
		}

		typename Set::const_iterator mCurrentValue;

		const typename Set::const_iterator mUpperBounds;

};

#endif

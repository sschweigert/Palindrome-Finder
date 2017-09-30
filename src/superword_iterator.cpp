#include <superword_iterator.h>

#include <palindrome_tools.h>
#include <algorithm>

template <Side side>
SuperwordIterator<side>::SuperwordIterator(const std::string& wordToMatch, const SortedStringSet<side>& wordsToSearch) :
	mCurrentValue(wordsToSearch.upper_bound(wordToMatch)),
	mUpperBounds(calculateUpperBounds(wordToMatch, wordsToSearch))
{

}

template <Side side>
const std::string& SuperwordIterator<side>::operator*() const
{
	return *mCurrentValue;	
}

template <Side side>
bool SuperwordIterator<side>::hasNext()
{
	return mCurrentValue != mUpperBounds;
}

template <Side side>
SuperwordIterator<side>& SuperwordIterator<side>::operator++()
{
	++mCurrentValue;
	return *this;
}	

template <Side side>
typename SortedStringSet<side>::const_iterator SuperwordIterator<side>::calculateUpperBounds(const std::string& wordToMatch, const SortedStringSet<side>& wordsToSearch)
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

template class SuperwordIterator<Side::Left>;
template class SuperwordIterator<Side::Right>;

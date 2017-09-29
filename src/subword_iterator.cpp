#include <subword_iterator.h>

template <Side side>
SubwordIterator<side>::SubwordIterator(const std::string& wordToMatch, const Set& wordsToSearch) :
	iterator(wordToMatch),
	mHasNext(iterator.current != iterator.end),
	mWordsToSearch(wordsToSearch),
	mSubWord(mHasNext ? std::string(1, *(iterator.current)) : "")
{}

template <Side side>
const std::string& SubwordIterator<side>::operator*() const 
{
	return mSubWord;	
}

template <Side side>
bool SubwordIterator<side>::hasNext()
{
	return mHasNext;
}

template <Side side>
SubwordIterator<side>& SubwordIterator<side>::operator++()
{
	// Note we ignore the case of the full word
	while (++iterator.current < iterator.end)
	{
		iterator.buildOntoWord(mSubWord);
		if (mWordsToSearch.count(mSubWord) == 1)
		{
			// Subword is valid, so break out of loop
			return *this;
		}	
	}

	// Reached end of word so there is nothing new to add
	mHasNext = false;

	return *this;
}	

template class SubwordIterator<Side::Left>;
template class SubwordIterator<Side::Right>;

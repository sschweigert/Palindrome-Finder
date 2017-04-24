#include <subword_iterator.h>

template <Side::e side>
SubwordIterator<side>::SubwordIterator(const std::string& wordToMatch, const Set& wordsToSearch) :
	iterator(wordToMatch),
	mHasNext(iterator.current < iterator.end),
	mWordToMatch(wordToMatch),	
	mWordsToSearch(wordsToSearch),
	mSubWord(mHasNext ? std::string(1, *(iterator.current)) : "")
{}

template <Side::e side>
const std::string& SubwordIterator<side>::operator*() const 
{
	return mSubWord;	
}

	template <Side::e side>
bool SubwordIterator<side>::hasNext()
{
	return mHasNext;
}

template <Side::e side>
auto SubwordIterator<side>::operator++() -> decltype(*this)&
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

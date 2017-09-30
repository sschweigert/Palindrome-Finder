#include <subword_iterator.h>

#include <iostream>

template <>
std::string buildOntoWord<Side::Left>(std::string word, char toAdd)
{
	return (word + toAdd);
}

template <>
std::string buildOntoWord<Side::Right>(std::string word, char toAdd)
{
	return (toAdd + word);
}

template <>
SubStringIterator<Side::Left> iteratorAtFirstLetter<Side::Left>(const std::string& wordToMatch)
{
	return { wordToMatch.begin(), wordToMatch.end() };
}

template <>
SubStringIterator<Side::Right> iteratorAtFirstLetter<Side::Right>(const std::string& wordToMatch)
{
	return { wordToMatch.rbegin(), wordToMatch.rend() };
}

template <Side side>
SubwordIterator<side>::SubwordIterator(const std::string& wordToMatch, const Set& wordsToSearch) :
	iterator(iteratorAtFirstLetter<side>(wordToMatch)),
	mWordsToSearch(wordsToSearch),
	mSubWord("")
{
	// Add characters to the word, moving iterator to first position or to end if
	// no match in set
	next();
}

template <Side side>
const std::string& SubwordIterator<side>::operator*() const 
{
	return mSubWord;	
}

template <Side side>
bool SubwordIterator<side>::hasNext()
{
	return (iterator.current != iterator.end);
}

template <Side side>
SubwordIterator<side>& SubwordIterator<side>::operator++()
{
	// Start checking from next character
	++(iterator.current);

	// Keep adding characters until reach a word in the set
	next();

	return *this;
}	

template <Side side>
void SubwordIterator<side>::next()
{
	// Should be (iterator.current != iterator.end), but this doesn't work for some reason
	while (iterator.current < iterator.end)
	{
		mSubWord = buildOntoWord<side>(mSubWord, *(iterator.current));

		if (mWordsToSearch.count(mSubWord) == 1)
		{
			// Subword is in set, so break out of loop
			break;
		}	
		else
		{

			// If the word wasn't in set, increment and try with next character
			++(iterator.current);
		}
	}
}

template class SubwordIterator<Side::Left>;
template class SubwordIterator<Side::Right>;

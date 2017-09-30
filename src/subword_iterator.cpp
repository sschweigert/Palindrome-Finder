#include <subword_iterator.h>

template <Side side>
SubwordIterator<side>::SubwordIterator(const std::string& wordToMatch, const Set& wordsToSearch) :
	current(SpecializedSubwordBehaviors<side>::begin(wordToMatch)),
	end(SpecializedSubwordBehaviors<side>::end(wordToMatch)),
	mWordsToSearch(wordsToSearch),
	mSubWord("")
{
	// Add characters to the word, moving iterator to first position or to end if
	// no match in set
	buildUntilMatch();
}

template <Side side>
const std::string& SubwordIterator<side>::operator*() const 
{
	return mSubWord;	
}

template <Side side>
bool SubwordIterator<side>::hasNext()
{
	return (current != end);
}

template <Side side>
SubwordIterator<side>& SubwordIterator<side>::operator++()
{
	// Start checking from next character
	++current;

	// Keep adding characters until reach a word in the set
	buildUntilMatch();

	return *this;
}	

template <Side side>
void SubwordIterator<side>::buildUntilMatch()
{
	// Should be (iterator.current != iterator.end), but this doesn't work for some reason
	while (current < end)
	{
		mSubWord = SpecializedSubwordBehaviors<side>::buildOntoWord(mSubWord, *current);

		if (mWordsToSearch.count(mSubWord) == 1)
		{
			// Subword is in set, so break out of loop
			break;
		}	
		else
		{

			// If the word wasn't in set, increment and try with next character
			++current;
		}
	}
}

// Explicit instantiations
template class SubwordIterator<Side::Left>;
template class SubwordIterator<Side::Right>;

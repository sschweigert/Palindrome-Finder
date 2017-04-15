#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
#include <stack>

#include <string_set.h>
#include <palindrome_tools.h>


enum class Side
{

	Left,

	Right

};

template <class IteratorType>
struct IteratorBounds
{

	IteratorType lowerBound;
	IteratorType upperBound;

};

class IWordCandidateIterator
{

	public:

		virtual std::string operator*() = 0;

		virtual bool hasNext() = 0;

		virtual IWordCandidateIterator& operator++() = 0;

};

class ForwardSubwordIterator : public IWordCandidateIterator
{

	public:

		ForwardSubwordIterator(const std::string& wordToMatch, const ForwardStringSet& wordsToSearch) :
		mHasNext(true),
		mIndex(-1),
		mWordToMatch(wordToMatch),	
		mWordsToSearch(wordsToSearch),
		mSubWord("")
		{

		}

		virtual std::string operator*()
		{
			return mSubWord;	
		}

		virtual bool hasNext()
		{
			return mHasNext;
		}

		virtual IWordCandidateIterator& operator++()
		{
			while (++mIndex < (int)mWordToMatch.size())
			{
				mSubWord += mWordToMatch[mIndex];
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

	private:

		bool mHasNext;

		int mIndex;
		
		const std::string& mWordToMatch;

		const ForwardStringSet& mWordsToSearch;

		std::string mSubWord;
		
};

class ForwardCandidateIterator : public IWordCandidateIterator
{

	public:

		ForwardCandidateIterator(const std::string& wordToMatch, const ForwardStringSet& wordsToSearch) :
			mSubwordIterator(wordToMatch, wordsToSearch)
		{

		}

		virtual std::string operator*()
		{

		}

		virtual bool hasNext()
		{
			return mSubwordIterator.hasNext();
		}

		virtual IWordCandidateIterator& operator++()
		{

		}

	private:

		ForwardSubwordIterator mSubwordIterator;

};

int main(int argc, char** argv)
{

	/*	
	std::fstream fileStream;
	fileStream.open("/home/sebastian/Downloads/words.txt", std::fstream::in);

	ForwardStringSet forwardOrdering;
	ReverseStringSet backwardOrdering;

	while (!fileStream.eof())
	{
		std::string line;
		fileStream >> line;
		
		forwardOrdering.insert(line);
		backwardOrdering.insert(line);
	}

	int numberOfWords = 3;

	std::vector<std::string> palindromes;

	std::vector<ForwardStringSet::iterator> forwardIterators;
	std::vector<ReverseStringSet::iterator> reverseIterators;

	std::vector<IteratorBounds<ForwardStringSet::iterator>> forwardIteratorBounds;
	std::vector<IteratorBounds<ReverseStringSet::iterator>> reverseIteratorBounds;

	ForwardStringSet::iterator seedIterator = forwardOrdering.begin();

	while (seedIterator != forwardOrdering.end())
	{
		int leftCharacters = 0;
		int rightCharacters = 0;
		int numberOfWordsSoFar = 0;
		
		// Setup first/seed word
		forwardIterators.push_back(seedIterator);
		leftCharacters += seedIterator->size();

		++numberOfWordsSoFar;

		// Insert new words
		while (numberOfWordsSoFar < numberOfWords)
		{
			if (leftCharacters >= rightCharacters)
			{
				// Begin inserting right words

				// Number of left characters that must be matched by the new right characters
				int numMatchingCharacters = leftCharacters - rightCharacters;

				int accumulatedChars = 0;

				int index = forwardIterators.size() - 1;
				for (; index >= 0 && accumulatedChars < numMatchingCharacters; --index)
				{
					accumulatedChars += forwardIterators[index]->size();	
				}

				int firstCharPosition = accumulatedChars - numMatchingCharacters;

				std::string matchingCharacters = "";

				// Deal with overlapping word
				matchingCharacters.insert(0, *(forwardIterators[index]), firstCharPosition, std::string::npos);
				++index;

				for (; index < forwardIterators.size() - 1; ++index)
				{
					matchingCharacters += *(forwardIterators[index]);
				}

				reverse(matchingCharacters.begin(), matchingCharacters.end());

				IteratorBounds<ReverseStringSet::iterator> newBounds;
				newBounds.lowerBound = backwardOrdering.lower_bound(matchingCharacters);
				newBounds.upperBound = backwardOrdering.upper_bound(matchingCharacters);

				
			}
			else
			{

			}

			++numberOfWordsSoFar;
			
		}

		// Check "overhanging" characters

		++seedIterator;
	}

	std::cout << *backwardOrdering.lower_bound("test") << std::endl;
	std::cout << *backwardOrdering.upper_bound("test") << std::endl;

	std::cout << "Found the following palindromes: " << std::endl;
	for (const auto& palindrome : palindromes)
	{
		std::cout << palindrome << std::endl;
	}
	*/

	ForwardStringSet set;
	set.insert("t");
	set.insert("te");
	set.insert("tes");
	set.insert("tea");
	set.insert("teaa");
	set.insert("test");
	set.insert("testy");
	set.insert("testacle");
	set.insert("testicle");
	set.insert("tesla");
	

	auto low = set.lower_bound("test");
	auto upper = set.upper_bound("tesu");

	for (auto itr = low; itr != upper; ++itr)
	{
		std::cout << *itr << std::endl;
	}

	return 0;
}

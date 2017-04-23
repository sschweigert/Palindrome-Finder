#ifndef _SUBWORD_ITERATOR_
#define _SUBWORD_ITERATOR_

#include <iword_candidate_iterator.h>
#include <string_set.h>
#include <side.h>

template <Side::e side>
struct SubwordStringIterator;

template <>
struct SubwordStringIterator<Side::Left>
{

	SubwordStringIterator(const std::string& wordToMatch) :
		current(wordToMatch.begin()),
		end(std::prev(wordToMatch.end()))
	{}

	typedef typename std::string::const_iterator iterator;

	void buildOntoWord(std::string& word)
	{
		word += *current;
	}

	iterator current;

	iterator end;

};

template <>
struct SubwordStringIterator<Side::Right>
{

	SubwordStringIterator(const std::string& wordToMatch) :
		current(wordToMatch.rbegin()),
		end(std::prev(wordToMatch.rend()))
	{}

	typedef typename std::string::const_reverse_iterator iterator;

	void buildOntoWord(std::string& word)
	{
		word = *current + word;
	}

	iterator current;

	iterator end;

};

template <Side::e side>
class SubwordIterator
{

	public:

		typedef typename TypeTraits<side>::Set Set;

		SubwordIterator(const std::string& wordToMatch, const Set& wordsToSearch) :
			iterator(wordToMatch),
			mHasNext(iterator.current < iterator.end),
			mWordToMatch(wordToMatch),	
			mWordsToSearch(wordsToSearch),
			mSubWord(mHasNext ? std::string(1, *(iterator.current)) : "")
			{}

		const std::string& operator*() const 
		{
			return mSubWord;	
		}

		bool hasNext()
		{
			return mHasNext;
		}

		auto operator++() -> decltype(*this)&
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

	private:

		SubwordStringIterator<side> iterator;

		bool mHasNext;

		const std::string& mWordToMatch;

		const Set& mWordsToSearch;

		std::string mSubWord;

};

#endif

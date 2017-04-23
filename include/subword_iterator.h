#ifndef _SUBWORD_ITERATOR_
#define _SUBWORD_ITERATOR_

#include <iword_candidate_iterator.h>
#include <string_set.h>
#include <side.h>

class ForwardSubwordIterator : public IWordCandidateIterator
{

	public:

		ForwardSubwordIterator(const std::string& wordToMatch, const ForwardStringSet& wordsToSearch);

		virtual const std::string& operator*() const;

		virtual bool hasNext();

		virtual IWordCandidateIterator& operator++();

	private:

		bool mHasNext;

		int mIndex;
		
		const std::string& mWordToMatch;

		const ForwardStringSet& mWordsToSearch;

		std::string mSubWord;
		
};


class ReverseSubwordIterator : public IWordCandidateIterator
{

	public:

		ReverseSubwordIterator(const std::string& wordToMatch, const ReverseStringSet& wordsToSearch);

		virtual const std::string& operator*() const;

		virtual bool hasNext();

		virtual IWordCandidateIterator& operator++();

	private:

		bool mHasNext;

		int mIndex;
		
		const std::string& mWordToMatch;

		const ReverseStringSet& mWordsToSearch;

		std::string mSubWord;
		
};

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

	iterator current;

	iterator end;

};

template <Side::e side>
class SubwordIterator
{

	SubwordIterator(const std::string& wordToMatch, const ForwardStringSet& wordsToSearch) :
		iterator(wordToMatch),
		mHasNext(iterator.current < iterator.end),
		mWordToMatch(wordToMatch),	
		mWordsToSearch(wordsToSearch),
		mSubWord(mHasNext ? *(iterator.current) : "")
	{}

	const std::string& operator*() const 
	{
		return mSubWord;	
	}

	bool hasNext()
	{
		return mHasNext;
	}

	IWordCandidateIterator& operator++()
	{
		// Note we ignore the case of the full word
		while (++iterator.current < iterator.end)
		{
			mSubWord += ++iterator.current;
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

	SubwordStringIterator<side> iterator;

	bool mHasNext;

	const std::string& mWordToMatch;

	const ReverseStringSet& mWordsToSearch;

	std::string mSubWord;

};

#endif

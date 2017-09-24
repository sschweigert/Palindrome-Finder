#ifndef _SUBWORD_ITERATOR_
#define _SUBWORD_ITERATOR_

#include <iword_candidate_iterator.h>
#include <string_set.h>
#include <side.h>

template <Side side>
struct SubwordStringIterator;

template <>
struct SubwordStringIterator<Side::Left>
{

	SubwordStringIterator(const std::string& wordToMatch) :
		current(wordToMatch.begin()),
		end(wordToMatch.end())
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
		end(wordToMatch.rend())
	{}

	typedef typename std::string::const_reverse_iterator iterator;

	void buildOntoWord(std::string& word)
	{
		word = *current + word;
	}

	iterator current;

	iterator end;

};

template <Side side>
class SubwordIterator
{

	public:

		typedef typename TypeTraits<side>::Set Set;

		SubwordIterator(const std::string& wordToMatch, const Set& wordsToSearch);

		const std::string& operator*() const;

		bool hasNext();

		auto operator++() -> decltype(*this)&;

	private:

		SubwordStringIterator<side> iterator;

		bool mHasNext;

		const std::string& mWordToMatch;

		const Set& mWordsToSearch;

		std::string mSubWord;

};

#endif

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

	iterator current;

	iterator end;

};

template <class Iterator>
struct IteratorPair
{

	Iterator current;

	Iterator end;

};

template <Side side>
using SubStringIterator = IteratorPair< typename SubwordStringIterator<side>::iterator >;

template <Side side>
SubStringIterator<side> iteratorAtFirstLetter(const std::string& wordToMatch);

template <>
SubStringIterator<Side::Left> iteratorAtFirstLetter<Side::Left>(const std::string& wordToMatch);

template <>
SubStringIterator<Side::Right> iteratorAtFirstLetter<Side::Right>(const std::string& wordToMatch);

template <Side side>
class SubwordIterator
{

	public:

		typedef typename TypeTraits<side>::Set Set;

		SubwordIterator(const std::string& wordToMatch, const Set& wordsToSearch);

		const std::string& operator*() const;

		bool hasNext();

		SubwordIterator<side>& operator++();

	private:

		SubwordStringIterator<side> iterator;

		bool mHasNext;

		const Set& mWordsToSearch;

		std::string mSubWord;

};

template <Side side>
std::string buildOntoWord(std::string word, char toAdd);

template <>
std::string buildOntoWord<Side::Left>(std::string word, char toAdd);

template <>
std::string buildOntoWord<Side::Right>(std::string word, char toAdd);


#endif

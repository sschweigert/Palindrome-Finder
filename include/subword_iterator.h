#ifndef _SUBWORD_ITERATOR_
#define _SUBWORD_ITERATOR_

#include <iword_candidate_iterator.h>
#include <string_set.h>
#include <side.h>

template <Side side>
class SpecializedSubwordBehaviors;

template <>
class SpecializedSubwordBehaviors<Side::Left>
{

	public:

		typedef std::string::const_iterator iterator;

		static std::string buildOntoWord(std::string word, char toAdd);

};

template <>
class SpecializedSubwordBehaviors<Side::Right>
{

	public:

		typedef std::string::const_reverse_iterator iterator;

		static std::string buildOntoWord(std::string word, char toAdd);

};

template <class Iterator>
struct IteratorPair
{

	Iterator current;

	Iterator end;

};

template <Side side>
using SubStringIterator = IteratorPair< typename SpecializedSubwordBehaviors<side>::iterator >;

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

		void next();

		SubStringIterator<side> iterator;

		const Set& mWordsToSearch;

		std::string mSubWord;

};


#endif

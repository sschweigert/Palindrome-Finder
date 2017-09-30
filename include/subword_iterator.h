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

		static iterator begin(const std::string& toIterate);

		static iterator end(const std::string& toIterate);

};

template <>
class SpecializedSubwordBehaviors<Side::Right>
{

	public:

		typedef std::string::const_reverse_iterator iterator;

		static std::string buildOntoWord(std::string word, char toAdd);

		static iterator begin(const std::string& toIterate);

		static iterator end(const std::string& toIterate);

};

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

		typename SpecializedSubwordBehaviors<side>::iterator current;

		typename SpecializedSubwordBehaviors<side>::iterator end;

		const Set& mWordsToSearch;

		std::string mSubWord;

};


#endif

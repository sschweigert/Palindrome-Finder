#ifndef _SPECIALIZED_SUBWORD_BEHAVIORS_
#define _SPECIALIZED_SUBWORD_BEHAVIORS_

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

#endif

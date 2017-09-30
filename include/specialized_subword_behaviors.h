#ifndef _SPECIALIZED_SUBWORD_BEHAVIORS_
#define _SPECIALIZED_SUBWORD_BEHAVIORS_

#include <string_set.h>
#include <side.h>

//! \brief A fully specialized class that generalizes functions used in SubwordIterator<Side side>
template <Side side>
class SpecializedSubwordBehaviors;

//! \brief Left generalized functions used to build the string from the left side to the right
template <>
class SpecializedSubwordBehaviors<Side::Left>
{

	public:

		typedef std::string::const_iterator iterator;

		static std::string buildOntoWord(std::string word, char toAdd);

		static iterator begin(const std::string& toIterate);

		static iterator end(const std::string& toIterate);

};

//! \brief Right generalized functions used to build the string from the right side to the left
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

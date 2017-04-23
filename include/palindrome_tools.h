#ifndef _PALINDROME_TOOLS_
#define _PALINDROME_TOOLS_

#include <string>
#include <boost/optional.hpp>

#include <side.h>

//! \brief Check if a word is a palindrome. This treats spaces as characters.
bool isPalindrome(const std::string& first);

//! \brief Helper function for isPalindrome. Increments an iterator past the 
//! leading spaces. This is a template to allow handling of both forward
//! and reverse iterators.
template <class Iterator>
void incrementPastSpaces(Iterator& iterator);

template <class Iterator>
void incrementToFirstNotZ(Iterator& iterator, Iterator end);

template <class Iterator>
std::string buildWordFromIterators(Iterator begin, Iterator end);

template <Side::e side>
struct BackwardsRange;

template <>
struct BackwardsRange<Side::Left>
{
	std::string::const_reverse_iterator iterator;
	std::string::const_reverse_iterator end;
};

template <>
struct BackwardsRange<Side::Right>
{
	std::string::const_iterator iterator;
	std::string::const_iterator end;
};

template <Side::e side>
BackwardsRange<side> getBackwardsRange(const std::string& word);

//! \brief Generate the next larger word that does not start with the same letters
//! as the given word. For example if "app" was input then "apq" would be the next
//! larger word that doesn't start with the same letters. "apple" would be in between
//! "app" and "apq." This function is used to generate lower_bound criteria for searches
//! of words that start with a specific set of characters.
//! Normally, the last or first character in the string will simply be incremented (which
//! one depends on the value of the side template parameter). However, this is not the
//! case for words that start or end with 'z'. In that case the first non-'z' character
//! is incremented and then word is truncated up to that point.
//! \param side The side to view the word. Side::Left implies left to right, while
//! Side::Right implies right to left. Therefore, Side::Left will likely increment
//! the rightmost character, while Side::Right will likely increment the rightmost character.
//! \param toIncrement The word used to find the next larger one.
//! \return The next larger word that doesn't start with the same letters. If the input
//! is entire 'z', then boost::none will be returned (because there is no larger word
//! in that case.
template <Side::e side>
boost::optional<std::string> wordTailBounds(const std::string& toIncrement);

std::string reverseString(const std::string& toReverse);

#endif

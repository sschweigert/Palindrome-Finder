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

//! Add to a word as if it were a base-26 number. For example "aabbcc" -> "aabbcd"
//! This function will fail (return boost::none) if the function is all 'z' characters.
//! In such a case the number "rolls-over" in a scenario analogous to 999 -> 1000.
//! Thus, "zzz" -> "aaaa"
//
template <Side::e side>
boost::optional<std::string> wordTailBounds(std::string toIncrement);

std::string reverseString(const std::string& toReverse);

#endif

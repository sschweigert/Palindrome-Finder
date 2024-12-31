#ifndef _PALINDROME_CALCULATION_H_
#define _PALINDROME_CALCULATION_H_

#include <vector>
#include <string>

#include <enum_class_map.h>
#include <word_type.h>

// Given a vocabularly of words, find and return all the associated palindromes.
// @param seedWords Vocabulary of words to use for creation of palindromes
// @param numberOfWords The number of words that will be contained within the resulting palindromes.
std::vector<std::string> findAllPalindromes(const std::vector<std::string>& seedWords, int numberOfWords);

// Given a description of a phrase in the form of a list of word types and a vocabulary that is categorized by word types,
// search and find all the existing palindromes that adhere to the description of the phrase. The description of the phrase
// implicitly defines the length of the palindrome (ie. types.size() words)
// @param types The description of the phrase
// @param words Vocabulary of words sorted by word type
std::vector<std::string> findTypedPalindromes(const std::vector<WordType>& types, const EnumMap<WordType, std::vector<std::string>>& words, bool useNew);

#endif

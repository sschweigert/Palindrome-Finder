#ifndef _FILE_IO_H_
#define _FILE_IO_H_

#include <word_type.h>
#include <vector>
#include <string>
#include <enum_class_map.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <boost/optional.hpp>

// Macro to stringify expanded macro
#define XSTR(a) STR(a)
#define STR(a) #a

// The path of the project directory
constexpr const char* topPath = XSTR(TOP_PATH);

void saveToHomeDir(const std::vector<std::string>& data, std::string path);

std::string homeDir();

boost::optional< std::vector<std::string> > importWordSet(std::string path);

boost::optional< std::vector<std::string> > importGoogleWords();

EnumMap<WordType, std::vector<std::string>> importTypedWords();

constexpr const char* typedWordDirectory = "wordnet_words";

const EnumMap<WordType, std::string> typedWordFilenames =
{
	{ WordType::Noun, "nouns.txt" },
	{ WordType::Adjective, "adjectives.txt" },
	{ WordType::Verb, "verbs.txt" },
	{ WordType::Adverb, "adverbs.txt" }
};

#endif

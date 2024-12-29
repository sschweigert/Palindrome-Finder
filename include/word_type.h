#ifndef _WORD_TYPE_H_
#define _WORD_TYPE_H_

enum class WordType
{

	Noun,

	Adjective,

	Verb,

	Adverb

};

inline const char* to_string(WordType val)
{
	switch(val) {
		case WordType::Noun:
			return "Noun";
		case WordType::Adjective:
			return "Adjective";
		case WordType::Verb:
			return "Verb";
		case WordType::Adverb:
			return "Adverb";
	}
	return "[Invalid]";
}

#endif

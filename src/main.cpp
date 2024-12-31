#include <palindrome_calculation.h>
#include <palindrome_tools.h>
#include <file_io.h>
#include <timer.h>
#include <iostream>
#include <iomanip>
#include <unordered_set>

int main(int argc, char** argv)
{
	/*
	boost::optional<std::vector<std::string>> words = importGoogleWords();

	if (!words)
	{
		std::cout << "Could not open file" << std::endl;	
		return 0;
	}

	const int numberOfPalindromes = 5;

	Timer timer;

	std::vector<std::string> palindromes = findAllPalindromes(*words, numberOfPalindromes);

	std::cout << "Processing to 10% took: " << timer.secondsElapsed() << std::endl;

	std::cout << "Found " << palindromes.size() << " words. Now saving. " << std::endl;

	saveToHomeDir(palindromes, "generated_palindromes.txt");
	*/

	std::cout << "Importing word banks...\n";

	EnumMap<WordType, std::vector<std::string>> typedWords = importTypedWords();

	std::cout << "\nWord banks imported\n";
	for (const auto wordset : typedWords)
	{
		std::string desc = std::string(to_string(wordset.first)) + "s:";
		std::cout << std::left << std::setw(14) << std::setfill(' ') << desc << wordset.second.size() << "\n";
	}

	std::cout << "\nRunning palindrome calculation\n";

	std::vector<WordType> types = { WordType::Adjective, WordType::Adjective, WordType::Adjective, WordType::Noun };

	std::vector<std::string> palindromesNew;
	
	auto calc = [&] ()
	{
		palindromesNew = findTypedPalindromes(types, typedWords, true);
	};

	double runtime = timeFunction(calc);

	std::vector<std::string> palindromesOld;
	
	auto calcOld = [&] ()
	{
		palindromesOld = findTypedPalindromes(types, typedWords, false);
	};

	runtime = timeFunction(calcOld);

	std::cout << "Found " << palindromesNew.size() << " palindromes in " << runtime << " seconds\n";

	for (const auto& val : palindromesOld)
	{
		if (!isSpacedPalindrome(val))
		{
			std::cout << "Invalid result found: \"" << val << "\"\n";
		}
	}

	//saveToHomeDir(palindromes, "generated_palindromes.txt");
	return 0;
}

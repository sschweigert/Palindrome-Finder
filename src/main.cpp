#include <palindrome_calculation.h>
#include <file_io.h>
#include <timer.h>
#include <iostream>
#include <iomanip>

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

	std::vector<std::string> palindromes;
	
	auto calc = [&] ()
	{
		palindromes = findTypedPalindromes(types, typedWords);
	};

	double runtime = timeFunction(calc);

	std::cout << "Found " << palindromes.size() << " palindromes in " << runtime << " seconds\n";

	saveToHomeDir(palindromes, "generated_palindromes.txt");
	return 0;
}

#include <palindrome_calculation.h>
#include <file_io.h>
#include <timer.h>

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

	EnumMap<WordType, std::vector<std::string>> typedWords = importTypedWords();

	std::vector<WordType> types = { WordType::Adjective, WordType::Adjective, WordType::Adjective, WordType::Noun };

	std::vector<std::string> palindromes = findTypedPalindromes(types, typedWords);

	saveToHomeDir(palindromes, "generated_palindromes.txt");
	return 0;
}

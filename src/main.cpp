#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
#include <stack>
#include <memory>
#include <unordered_map>

#include <string_set.h>
#include <palindrome_tools.h>
#include <word_candidate_iterator.h>
#include <entire_set_iterator.h>
#include <word_building_stack.h>
#include <palindrome_calculation.h>
#include <file_io.h>
#include <timer.h>

int main(int argc, char** argv)
{
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

	return 0;
}

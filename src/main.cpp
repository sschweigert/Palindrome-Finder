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
#include <timer.h>


int main(int argc, char** argv)
{

	std::fstream fileStream;
	//fileStream.open("/home/sebastian/bOb-Programming-Problem/words.txt", std::fstream::in);
	fileStream.open("/home/sebastian/bOb-Programming-Problem/google_words.txt", std::fstream::in);
	//fileStream.open("/home/sebastian/bOb-Programming-Problem/words_subset.txt", std::fstream::in);

	if (fileStream.fail())
	{
		std::cout << "Could not open file" << std::endl;	
		return 0;
	}

	std::vector<std::string> words;

	while (!fileStream.eof())
	{
		std::string line;
		fileStream >> line;

		if (line.size() > 0)	
		{
			words.push_back(line);
		}
	}
	fileStream.close();

	const int numberOfPalindromes = 5;

	Timer timer;

	std::vector<std::string> palindromes = calculatePalindromes(words, numberOfPalindromes);

	std::cout << "Processing to 10% took: " << timer.secondsElapsed() << std::endl;

	std::fstream palindromeStream;
	palindromeStream.open("/home/sebastian/generated_palindromes.txt", std::fstream::out);

	std::cout << "Found " << palindromes.size() << " words. Now saving. " << std::endl;

	for (const auto& palindrome : palindromes)
	{
		palindromeStream << palindrome << std::endl;
	}


	return 0;
}

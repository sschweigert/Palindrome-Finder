#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
#include <stack>
#include <memory>

#include <string_set.h>
#include <palindrome_tools.h>
#include <word_candidate_iterator.h>
#include <entire_set_iterator.h>
#include <word_building_stack.h>

int main(int argc, char** argv)
{

	std::fstream fileStream;
	fileStream.open("/home/sebastian/bOb-Programming-Problem/words_subset.txt", std::fstream::in);


	if (fileStream.fail())
	{
		std::cout << "Could not open file" << std::endl;	
		return 0;
	}

	ForwardStringSet forwardOrdering;
	ReverseStringSet reverseOrdering;

	while (!fileStream.eof())
	{
		std::string line;
		fileStream >> line;

		if (line.size() > 0)	
		{
			forwardOrdering.insert(line);
			reverseOrdering.insert(line);
		}
	}

	std::cout << "Words collected" << std::endl;

	int numberOfWords = 3;

	std::vector<std::string> palindromes;

	WordBuildingStack wordBuildingStack;
	
	std::unique_ptr<IForwardWordCandidateIterator> seedIterator(new EntireSetIterator<ForwardStringSet, IForwardWordCandidateIterator>(forwardOrdering));

	wordBuildingStack.push(std::move(seedIterator));

	Overhang overhang = wordBuildingStack.getOverhang();
	if (overhang.side == Side::Left)
	{
		std::unique_ptr<IReverseWordCandidateIterator> newIterator(new ReverseCandidateIterator(overhang.overhangText, reverseOrdering));

		wordBuildingStack.push(std::move(newIterator));
	}
	else
	{
		std::unique_ptr<IForwardWordCandidateIterator> newIterator(new ForwardCandidateIterator(overhang.overhangText, forwardOrdering));

		wordBuildingStack.push(std::move(newIterator));
	}
	
	while (wordBuildingStack.top().hasNext())
	{
		std::cout << wordBuildingStack.generateString() << std::endl;
		++(wordBuildingStack.top());
	}
	
	return 0;
}

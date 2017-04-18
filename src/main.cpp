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

void incrementStack(WordBuildingStack& wordBuildingStack)
{
	++(wordBuildingStack.top());

	while (!wordBuildingStack.empty() && !wordBuildingStack.top().hasNext())
	{
		wordBuildingStack.pop();

		if (wordBuildingStack.empty())
		{
			break;
		}

		++(wordBuildingStack.top());
	}
}

int main(int argc, char** argv)
{

	std::fstream fileStream;
	fileStream.open("/home/sebastian/bOb-Programming-Problem/words.txt", std::fstream::in);


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

	do
	{

		while (wordBuildingStack.size() < numberOfWords)
		{
			Overhang overhang = wordBuildingStack.getOverhang();
			if (overhang.side == Side::Left)
			{
				std::unique_ptr<IReverseWordCandidateIterator> newIterator(new ReverseCandidateIterator(reverseString(overhang.overhangText), reverseOrdering));

				if (newIterator->hasNext())
				{
					wordBuildingStack.push(std::move(newIterator));
				}
				else
				{
					incrementStack(wordBuildingStack);
				}
			}
			else
			{
				std::unique_ptr<IForwardWordCandidateIterator> newIterator(new ForwardCandidateIterator(reverseString(overhang.overhangText), forwardOrdering));

				if (newIterator->hasNext())
				{
					wordBuildingStack.push(std::move(newIterator));
				}
				else
				{
					incrementStack(wordBuildingStack);
				}
			}

			if (wordBuildingStack.empty())
			{
				break;
			}

		}

		// Fix double loop break outs
		if (wordBuildingStack.empty())
		{
			break;
		}

		//palindromes.push_back(wordBuildingStack.generateString());

		std::cout << wordBuildingStack.generateString() << std::endl;

		incrementStack(wordBuildingStack);

	} while (!wordBuildingStack.empty());

	for (const auto& palindrome : palindromes)
	{
		std::cout << palindrome << std::endl;
	}

	return 0;
}

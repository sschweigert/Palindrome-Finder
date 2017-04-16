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
		std::unique_ptr<IForwardWordCandidateIterator> newIterator(new ForwardCandidateIterator(overhang.overhangText, forwardOrdering));

		wordBuildingStack.push(std::move(newIterator));
	}
	else
	{
		std::unique_ptr<IReverseWordCandidateIterator> newIterator(new ReverseCandidateIterator(overhang.overhangText, reverseOrdering));
		wordBuildingStack.push(std::move(newIterator));
	}


	std::string textToMatch = "a";
	ForwardSuperwordIterator forwardItr(textToMatch, forwardOrdering);
	
	for (int i = 0; forwardItr.hasNext() && i < 10; i++)
	{
		std::cout << *forwardItr << std::endl;
		++forwardItr;
	}
	
	//std::cout << wordBuildingStack.generateString() << std::endl;

	//
	/*
	WordSearcher initialSearcher;
	initialSearcher.mSide = Side::Left;
	initialSearcher.mWordCandidateIterator.reset(new EntireSetIterator<ForwardStringSet>(forwardOrdering));


	candidateStack.push(std::move(initialSearcher));

	ReverseStringSet set;
	set.insert("t");
	set.insert("te");
	set.insert("tes");
	set.insert("tea");
	set.insert("teaa");
	set.insert("tess");
	set.insert("test");
	set.insert("tesu");
	set.insert("testy");
	set.insert("testacle");
	set.insert("testicle");
	set.insert("tesla");
	set.insert("st");
	set.insert("stest");
	set.insert("adfsfastest");
	set.insert("sest");
	set.insert("uest");

	std::string toMatch = "test";
	
	for (auto itr = ReverseCandidateIterator(toMatch, set); itr.hasNext(); ++itr)
	{
		std::cout << *itr << std::endl;
	}
	*/

	return 0;
}

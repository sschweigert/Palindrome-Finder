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
#include <timer.h>

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

template <class Functor>
class IteratorWrapper : public IForwardWordCandidateIterator
{

	public:

		IteratorWrapper(IWordCandidateIterator& wordCandidateIterator, Functor& functor) :
			wordCandidateIterator(wordCandidateIterator),
			functor(functor)
	{}

		virtual const std::string& operator*() const
		{
			return *wordCandidateIterator;
		}

		virtual bool hasNext()
		{
			return wordCandidateIterator.hasNext();
		}

		virtual IWordCandidateIterator& operator++()
		{
			functor();
			++wordCandidateIterator;
			return *this;
		}


	private:

		IWordCandidateIterator& wordCandidateIterator;

		Functor& functor;

};

int main(int argc, char** argv)
{

	std::fstream fileStream;
	//fileStream.open("/home/sebastian/bOb-Programming-Problem/words.txt", std::fstream::in);
	fileStream.open("/home/sebastian/bOb-Programming-Problem/google_words.txt", std::fstream::in);


	if (fileStream.fail())
	{
		std::cout << "Could not open file" << std::endl;	
		return 0;
	}


	ForwardStringSet forwardOrdering;
	ReverseStringSet reverseOrdering;

	Timer timer;
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

	std::cout << "Loading words took: " << timer.secondsElapsed() << std::endl;

	fileStream.close();


	std::cout << "Words loaded into data structures" << std::endl;

	int numberOfWords = 6;

	std::vector<std::string> palindromes;

	WordBuildingStack wordBuildingStack;

	EntireSetIterator<ForwardStringSet, IForwardWordCandidateIterator> entireSetOrdering(forwardOrdering);

	bool done = false;

	int count = 0;
	auto counter = [&]
	{
		const float percentStep = 0.5;
		const int countStep = ((float)percentStep / 100.0) * (float)forwardOrdering.size();

		++count;
		if (count % countStep == 0)
		{
			float fraction = (float)count / (float)forwardOrdering.size();
			std::cout << (fraction * 100.0) << "% done" << std::endl;

			done = fraction > 0.02;
		
		}
	};

	std::unique_ptr<IForwardWordCandidateIterator> seedIterator(new IteratorWrapper<decltype(counter)>(entireSetOrdering, counter));

	wordBuildingStack.push(std::move(seedIterator));

	const float minAverageWordLength = 4;
	const int minPalindromeLength = ((minAverageWordLength + 1) * numberOfWords) - 1;

	do
	{

		// Refill the stack to numberOfWords size
		while (wordBuildingStack.size() < numberOfWords - 1)
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

		Overhang overhang = wordBuildingStack.getOverhang();
		if (overhang.side == Side::Left)
		{
			std::unique_ptr<IReverseWordCandidateIterator> newIterator(new ReverseCandidateIterator(reverseString(overhang.overhangText), reverseOrdering));

			while ((*newIterator).hasNext())
			{
				std::string potentialPalindrome = overhang.overhangText + **newIterator;
				if (isPalindrome(potentialPalindrome))
				{
					std::string palindromeText = wordBuildingStack.generateString(**newIterator);
					if (palindromeText.size() >= minPalindromeLength)
					{
						palindromes.push_back(palindromeText);
					}
				}

				++(*newIterator);
			}
		}
		else
		{
			std::unique_ptr<IForwardWordCandidateIterator> newIterator(new ForwardCandidateIterator(reverseString(overhang.overhangText), forwardOrdering));

			while ((*newIterator).hasNext())
			{
				std::string potentialPalindrome = **newIterator + overhang.overhangText;
				if (isPalindrome(potentialPalindrome))
				{
					std::string palindromeText = wordBuildingStack.generateString(**newIterator);
					if (palindromeText.size() >= minPalindromeLength)
					{
						palindromes.push_back(palindromeText);
					}
				}

				++(*newIterator);
			}
		}

		//std::cout << wordBuildingStack.generateString() << std::endl;

		incrementStack(wordBuildingStack);

	} while (!wordBuildingStack.empty() && !done);

	std::fstream palindromeStream;
	palindromeStream.open("/home/sebastian/generated_palindromes.txt", std::fstream::out);

	std::cout << "Found " << palindromes.size() << " words. Now saving. " << std::endl;

	for (const auto& palindrome : palindromes)
	{
		palindromeStream << palindrome << std::endl;
	}


	return 0;
}

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
#include <timer.h>

std::stack<WordCandidateIterator<Side::Right>> concreteRightIterators;
std::stack<WordCandidateIterator<Side::Left>> concreteLeftIterators;

void incrementStack(WordBuildingStack& wordBuildingStack)
{
	wordBuildingStack.incrementTop();

	while (!wordBuildingStack.empty() && !wordBuildingStack.topHasNext())
	{
		Side poppedSide = wordBuildingStack.pop();

		if (wordBuildingStack.empty())
		{
			break;
		}

		if (poppedSide == Side::Left)
		{
			concreteLeftIterators.pop();
		}
		else
		{
			concreteRightIterators.pop();
		}

		wordBuildingStack.incrementTop();
	}
}

template <class Functor, Side side>
class IteratorWrapper : public IWordCandidateIterator<side>
{

	public:

		IteratorWrapper(IWordCandidateIterator<side>& wordCandidateIterator, Functor& functor) :
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

		virtual IWordCandidateIterator<side>& operator++()
		{
			functor();
			++wordCandidateIterator;
			return *this;
		}


	private:

		IWordCandidateIterator<side>& wordCandidateIterator;

		Functor& functor;

};

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
	fileStream.close();
	std::cout << "Words loaded into data structures" << std::endl;


	std::unordered_map<std::string, WordCandidateIterator<Side::Left>> leftCachedIterators;
	std::unordered_map<std::string, WordCandidateIterator<Side::Right>> rightCachedIterators;
	
	leftCachedIterators.reserve(25000);
	rightCachedIterators.reserve(25000);

	// Length of palindrome
	const int numberOfWords = 6;

	// Output
	std::vector<std::string> palindromes;


	EntireSetIterator<Side::Left> entireSetOrdering(forwardOrdering);

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
			
		}

	};

	IteratorWrapper<decltype(counter), Side::Left> wrappedItr(entireSetOrdering, counter);

	WordBuildingStack wordBuildingStack;
	wordBuildingStack.push(&wrappedItr);

	const float minAverageWordLength = 4;
	const int minPalindromeLength = ((minAverageWordLength + 1) * numberOfWords) - 1;

	Timer timer;

	do
	{

		// Refill the stack to numberOfWords size
		while (wordBuildingStack.size() < numberOfWords - 1)
		{
			Overhang overhang = wordBuildingStack.getOverhang();

			std::string reversedOverhang = reverseString(overhang.overhangText);
			if (overhang.side == Side::Left)
			{
				if (rightCachedIterators.count(reversedOverhang) == 0)
				{
					rightCachedIterators.insert(std::make_pair(reversedOverhang, WordCandidateIterator<Side::Right>(reversedOverhang, reverseOrdering)));
				}

				WordCandidateIterator<Side::Right> cachedIterator = rightCachedIterators.at(reversedOverhang);

				if (cachedIterator.hasNext())
				{
					concreteRightIterators.push(cachedIterator);
					wordBuildingStack.push(&concreteRightIterators.top());
				}
				else
				{
					incrementStack(wordBuildingStack);
				}
			}
			else
			{
				if (leftCachedIterators.count(reversedOverhang) == 0)
				{
					leftCachedIterators.insert(std::make_pair(reversedOverhang, WordCandidateIterator<Side::Left>(reversedOverhang, forwardOrdering)));
				}

				WordCandidateIterator<Side::Left> cachedIterator = leftCachedIterators.at(reversedOverhang);

				if (cachedIterator.hasNext())
				{
					concreteLeftIterators.push(cachedIterator);
					wordBuildingStack.push(&concreteLeftIterators.top());
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
		std::string reversedOverhang(reverseString(overhang.overhangText));
		if (overhang.side == Side::Left)
		{
			WordCandidateIterator<Side::Right> newIterator(reversedOverhang, reverseOrdering);

			while (newIterator.hasNext())
			{
				std::string potentialPalindrome = overhang.overhangText + *newIterator;
				if (isPalindrome(potentialPalindrome))
				{
					std::string palindromeText = wordBuildingStack.generateString(*newIterator);
					if (palindromeText.size() >= minPalindromeLength)
					{
						palindromes.push_back(palindromeText);
					}
				}

				++newIterator;
			}
		}
		else
		{
			WordCandidateIterator<Side::Left> newIterator(reversedOverhang, forwardOrdering);

			while (newIterator.hasNext())
			{
				std::string potentialPalindrome = *newIterator + overhang.overhangText;
				if (isPalindrome(potentialPalindrome))
				{
					std::string palindromeText = wordBuildingStack.generateString(*newIterator);
					if (palindromeText.size() >= minPalindromeLength)
					{
						palindromes.push_back(palindromeText);
					}
				}

				++newIterator;
			}
		}

		//std::cout << wordBuildingStack.generateString() << std::endl;

		incrementStack(wordBuildingStack);

	} while (!wordBuildingStack.empty() && !done);

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

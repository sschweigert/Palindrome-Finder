#include <palindrome_calculation.h>

void incrementStack(WordBuildingStack& wordBuildingStack, std::stack<WordCandidateIterator<Side::Left>>& concreteLeftIterators, std::stack<WordCandidateIterator<Side::Right>>& concreteRightIterators)
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

std::vector<std::string> calculatePalindromes(const std::vector<std::string>& seedWords, int numberOfWords)
{
	std::stack<WordCandidateIterator<Side::Right>> concreteRightIterators;
	std::stack<WordCandidateIterator<Side::Left>> concreteLeftIterators;

	ForwardStringSet forwardOrdering;
	ReverseStringSet reverseOrdering;

	for (const auto& word : seedWords)
	{
		forwardOrdering.insert(word);
		reverseOrdering.insert(word);
	}

	std::cout << "Words loaded into data structures" << std::endl;


	std::unordered_map<std::string, WordCandidateIterator<Side::Left>> leftCachedIterators;
	std::unordered_map<std::string, WordCandidateIterator<Side::Right>> rightCachedIterators;
	
	leftCachedIterators.reserve(25000);
	rightCachedIterators.reserve(25000);

	// Output
	std::vector<std::string> palindromes;


	EntireSetIterator<Side::Left> entireSetOrdering(forwardOrdering);

	bool done = false;

	int count = 0;
	auto counter = [&]
	{
		const float percentStep = 0.5;
		int countStep = ((float)percentStep / 100.0) * (float)forwardOrdering.size();
		countStep = std::max(1, countStep);

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
					incrementStack(wordBuildingStack, concreteLeftIterators, concreteRightIterators);
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
					incrementStack(wordBuildingStack, concreteLeftIterators, concreteRightIterators);
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
					palindromes.push_back(palindromeText);
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
					palindromes.push_back(palindromeText);
				}

				++newIterator;
			}
		}

		incrementStack(wordBuildingStack, concreteLeftIterators, concreteRightIterators);

	} while (!wordBuildingStack.empty() && !done);

	return palindromes;
}

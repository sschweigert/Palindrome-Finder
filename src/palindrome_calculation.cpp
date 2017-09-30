#include <palindrome_calculation.h>

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

		wordBuildingStack.incrementTop();
	}
}

std::vector<std::string> calculatePalindromes(const std::vector<std::string>& seedWords, int numberOfWords)
{
	ForwardStringSet forwardOrdering;
	ReverseStringSet reverseOrdering;

	for (const auto& word : seedWords)
	{
		forwardOrdering.insert(word);
		reverseOrdering.insert(word);
	}

	std::cout << "Words loaded into data structures" << std::endl;


	// Output
	std::vector<std::string> palindromes;

	/*
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
	*/

	auto entireSetOrdering = std::make_unique<EntireSetIterator<Side::Left>>(forwardOrdering);

	WordBuildingStack wordBuildingStack;
	wordBuildingStack.push(std::move(entireSetOrdering));

	do
	{

		// Refill the stack to numberOfWords size
		while (wordBuildingStack.size() < numberOfWords - 1)
		{
			Overhang overhang = wordBuildingStack.getOverhang();

			std::string reversedOverhang = reverseString(overhang.overhangText);
			if (overhang.side == Side::Left)
			{
				auto cachedIterator = std::make_unique<WordCandidateIterator<Side::Right>>(reversedOverhang, reverseOrdering);

				if (cachedIterator->hasNext())
				{
					wordBuildingStack.push(std::move(cachedIterator));
				}
				else
				{
					incrementStack(wordBuildingStack);
				}
			}
			else
			{
				auto cachedIterator = std::make_unique<WordCandidateIterator<Side::Left>>(reversedOverhang, forwardOrdering);

				if (cachedIterator->hasNext())
				{
					wordBuildingStack.push(std::move(cachedIterator));
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

		incrementStack(wordBuildingStack);

	} while (!wordBuildingStack.empty() && !done);

	return palindromes;
}

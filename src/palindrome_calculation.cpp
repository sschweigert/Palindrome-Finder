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

template <Side side>
void addIteratorToSide(const std::string& overhangText, WordBuildingStack& wordBuildingStack, const SortedStringSet<side>& stringSet)
{
	std::string reversedOverhang = reverseString(overhangText);
	auto cachedIterator = std::make_unique<WordCandidateIterator<side>>(reversedOverhang, stringSet);

	if (cachedIterator->hasNext())
	{
		wordBuildingStack.push(std::move(cachedIterator));
	}
	else
	{
		incrementStack(wordBuildingStack);
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

	auto entireSetOrdering = std::make_unique<EntireSetIterator<Side::Left>>(forwardOrdering);

	WordBuildingStack wordBuildingStack;
	wordBuildingStack.push(std::move(entireSetOrdering));

	bool done = false;
	do
	{

		// Refill the stack to numberOfWords size
		while (wordBuildingStack.size() < numberOfWords - 1)
		{
			Overhang overhang = wordBuildingStack.getOverhang();

			if (overhang.side == Side::Left)
			{
				addIteratorToSide<Side::Right>(overhang.overhangText, wordBuildingStack, reverseOrdering);
			}
			else
			{
				addIteratorToSide<Side::Left>(overhang.overhangText, wordBuildingStack, forwardOrdering);
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

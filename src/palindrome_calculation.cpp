#include <palindrome_calculation.h>

void incrementStack(WordBuildingStack& wordBuildingStack)
{
	wordBuildingStack.incrementTop();

	while (!wordBuildingStack.empty() && !wordBuildingStack.topHasNext())
	{
		wordBuildingStack.pop();

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
	
void fillWordBuildingStack(WordBuildingStack& wordBuildingStack, int numberOfWords, const SortedStringSet<Side::Left>& forwardOrdering, const SortedStringSet<Side::Right>& reverseOrdering)
{
	while (wordBuildingStack.size() < numberOfWords)
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
}

void constructPalindromesFromStack(WordBuildingStack& wordBuildingStack, const SortedStringSet<Side::Left>& forwardOrdering, const SortedStringSet<Side::Right>& reverseOrdering, std::vector<std::string>& palindromeOutput)
{
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
				palindromeOutput.push_back(palindromeText);
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
				palindromeOutput.push_back(palindromeText);
			}

			++newIterator;
		}
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
		fillWordBuildingStack(wordBuildingStack, numberOfWords - 1, forwardOrdering, reverseOrdering);

		// Fix double loop break outs
		if (wordBuildingStack.empty())
		{
			break;
		}

		constructPalindromesFromStack(wordBuildingStack, forwardOrdering, reverseOrdering, palindromes);

		incrementStack(wordBuildingStack);

	} while (!wordBuildingStack.empty() && !done);

	return palindromes;
}

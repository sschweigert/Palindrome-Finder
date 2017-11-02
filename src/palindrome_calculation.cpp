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

template <Side side>
std::string buildOntoString(const std::string& initial, const std::string& toAdd);

template <>
std::string buildOntoString<Side::Left>(const std::string& initial, const std::string& toAdd)
{
	return toAdd + initial;
}

template <>
std::string buildOntoString<Side::Right>(const std::string& initial, const std::string& toAdd)
{
	return initial + toAdd;
}

template <Side side>
void constructPalindromesFromOverhang(std::string overhangText, WordBuildingStack& wordBuildingStack, const SortedStringSet<side>& ordering, std::vector<std::string>& palindromeOutput)
{
	std::string reversedOverhang(reverseString(overhangText));

	WordCandidateIterator<side> newIterator(reversedOverhang, ordering);

	while (newIterator.hasNext())
	{
		std::string potentialPalindrome = buildOntoString<side>(overhangText, *newIterator);
		if (isPalindrome(potentialPalindrome))
		{
			std::string palindromeText = wordBuildingStack.generateString(*newIterator);
			palindromeOutput.push_back(palindromeText);
		}

		++newIterator;
	}
}

void constructPalindromesFromStack(WordBuildingStack& wordBuildingStack, const SortedStringSet<Side::Left>& forwardOrdering, const SortedStringSet<Side::Right>& reverseOrdering, std::vector<std::string>& palindromeOutput)
{
	Overhang overhang = wordBuildingStack.getOverhang();
	std::string reversedOverhang(reverseString(overhang.overhangText));
	if (overhang.side == Side::Left)
	{
		constructPalindromesFromOverhang<Side::Right>(overhang.overhangText, wordBuildingStack, reverseOrdering, palindromeOutput);
	}
	else
	{
		constructPalindromesFromOverhang<Side::Left>(overhang.overhangText, wordBuildingStack, forwardOrdering, palindromeOutput);
	}
}

std::vector<std::string> findAllPalindromes(const std::vector<std::string>& seedWords, int numberOfWords)
{
	DoubleOrderedSet orderedSet(seedWords);

	// Output
	std::vector<std::string> palindromes;

	auto entireSetOrdering = std::make_unique<EntireSetIterator<Side::Left>>(orderedSet.forward);

	WordBuildingStack wordBuildingStack;
	wordBuildingStack.push(std::move(entireSetOrdering));

	bool done = false;
	do
	{

		// Refill the stack to numberOfWords size
		fillWordBuildingStack(wordBuildingStack, numberOfWords - 1, orderedSet.forward, orderedSet.reverse);

		// Fix double loop break outs
		if (wordBuildingStack.empty())
		{
			break;
		}

		constructPalindromesFromStack(wordBuildingStack, orderedSet.forward, orderedSet.reverse, palindromes);

		incrementStack(wordBuildingStack);

	} while (!wordBuildingStack.empty() && !done);

	return palindromes;
}

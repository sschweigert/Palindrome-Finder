#include <palindrome_calculation.h>

#include <iostream>

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
	
void fillWordBuildingStack(WordBuildingStack& wordBuildingStack, const std::vector<DoubleOrderedSet*>& wordSets)
{
	unsigned int wordCount = wordSets.size();

	// Fill up to the second last word
	while (wordBuildingStack.size() < (wordCount - 1))
	{
		Overhang overhang = wordBuildingStack.getOverhang();

		if (overhang.side == Side::Left)
		{
			unsigned int index = (wordCount - 1) - wordBuildingStack.getSideSize<Side::Right>();
			addIteratorToSide<Side::Right>(overhang.overhangText, wordBuildingStack, wordSets[index]->reverse);
		}
		else
		{
			unsigned int index = wordBuildingStack.getSideSize<Side::Left>();
			addIteratorToSide<Side::Left>(overhang.overhangText, wordBuildingStack, wordSets[index]->forward);
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

void constructPalindromesFromStack(WordBuildingStack& wordBuildingStack, const std::vector<DoubleOrderedSet*>& wordSets, std::vector<std::string>& palindromeOutput)
{
	// Should always work no matter what the overhang because the last word will be to the left of left side
	unsigned int wordSetIndex = wordBuildingStack.getSideSize<Side::Left>();
	const DoubleOrderedSet& lastSet = *(wordSets[wordSetIndex]);

	Overhang overhang = wordBuildingStack.getOverhang();
	std::string reversedOverhang(reverseString(overhang.overhangText));
	if (overhang.side == Side::Left)
	{
		constructPalindromesFromOverhang<Side::Right>(overhang.overhangText, wordBuildingStack, lastSet.reverse, palindromeOutput);
	}
	else
	{
		constructPalindromesFromOverhang<Side::Left>(overhang.overhangText, wordBuildingStack, lastSet.forward, palindromeOutput);
	}
}

std::vector<std::string> findPalindromes(const std::vector<DoubleOrderedSet*>& wordSets)
{
	// Output
	std::vector<std::string> palindromes;

	auto entireSetOrdering = std::make_unique<EntireSetIterator<Side::Left>>(wordSets.front()->forward);

	WordBuildingStack wordBuildingStack;
	wordBuildingStack.push(std::move(entireSetOrdering));

	bool done = false;
	do
	{

		// Refill the stack to numberOfWords size
		fillWordBuildingStack(wordBuildingStack, wordSets);

		// Fix double loop break outs
		if (wordBuildingStack.empty())
		{
			break;
		}

		constructPalindromesFromStack(wordBuildingStack, wordSets, palindromes);

		incrementStack(wordBuildingStack);

	} while (!wordBuildingStack.empty() && !done);

	return palindromes;
}

std::vector<std::string> findAllPalindromes(const std::vector<std::string>& seedWords, int numberOfWords)
{
	DoubleOrderedSet orderedSet(seedWords);

	std::vector<DoubleOrderedSet*> wordSets;
	for (int i = 0; i < numberOfWords; i++)
	{
		wordSets.push_back(&orderedSet);
	}

	return findPalindromes(wordSets);
}

std::vector<std::string> findTypedPalindromes(const std::vector<WordType>& types, const EnumMap<WordType, std::vector<std::string>>& words)
{
	EnumMap<WordType, DoubleOrderedSet> mappedSets;
	for (auto element : words)
	{
		mappedSets.insert({element.first, element.second});
	}

	std::vector<DoubleOrderedSet*> wordSets;
	for (const auto& type : types)
	{
		wordSets.push_back(&(mappedSets.at(type)));
	}

	return findPalindromes(wordSets);
}

#include <palindrome_calculation.h>

#include <side.h>

#include <string_set.h>
#include <palindrome_tools.h>
#include <word_candidate_iterator.h>
#include <entire_set_iterator.h>
#include <double_ordered_set.h>
#include <word_building_stack.h>

namespace
{

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
std::string concatenate(const std::string& initial, const std::string& toAdd);

template <>
std::string concatenate<Side::Left>(const std::string& initial, const std::string& toAdd)
{
	return toAdd + initial;
}

template <>
std::string concatenate<Side::Right>(const std::string& initial, const std::string& toAdd)
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
		std::string potentialPalindrome = concatenate<side>(overhangText, *newIterator);
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

struct WordStack
{
	std::vector<std::string> left;
	std::vector<std::string> right;
};

struct CalculationState
{
	Overhang overhang;

	int leftIndex;

	int rightIndex;
	
	WordStack& wordStack;
};


std::string fromStack(const WordStack& stack)
{
	bool first = true;
	std::string toReturn = "";
	for (const auto& val : stack.left)
	{
		if (!first)
		{
			toReturn += " ";
		}
		toReturn += val;
		first = false;
	}
	for (int i = stack.right.size() - 1; i >= 0; --i)
	{
		if (!first)
		{
			toReturn += " ";
		}
		toReturn += stack.right[i];
		first = false;
	}
	return toReturn;
}

void findPalindromesImpl(const std::vector<DoubleOrderedSet*>& wordSets, const CalculationState& state, std::vector<std::string>& toReturn)
{
	if (state.leftIndex > state.rightIndex)
	{
		if (isPalindrome(state.overhang.overhangText))
		{
			toReturn.push_back(fromStack(state.wordStack));
		}
		return;
	}

	std::string reversedOverhang = reverseString(state.overhang.overhangText);
	if (state.overhang.side == Side::Left)
	{
		const auto& wordset = wordSets[state.rightIndex];
		auto itr = WordCandidateIterator<Side::Right>(reversedOverhang, wordset->reverse);
		
		while (itr.hasNext())
		{
			const auto& nextCandidate = *itr;
			state.wordStack.right.push_back(nextCandidate);
			if (nextCandidate.size() > reversedOverhang.size())
			{
				// Next overhang is going to be on right side now
				std::string nextOverhang = nextCandidate.substr(0, nextCandidate.size() - reversedOverhang.size());
				findPalindromesImpl(wordSets, { { Side::Right, nextOverhang}, state.leftIndex, state.rightIndex - 1, state.wordStack }, toReturn);
			}
			else
			{
				// New word is not long enough, so overhang will remain on left side
				std::string nextOverhang = state.overhang.overhangText.substr(nextCandidate.size());
				findPalindromesImpl(wordSets, { { Side::Left, nextOverhang }, state.leftIndex, state.rightIndex - 1, state.wordStack }, toReturn);
			}
			state.wordStack.right.pop_back();
			++itr;
		}
	}
	else
	{
		// Side == Right
		const auto& wordset = wordSets[state.leftIndex];
		auto itr = WordCandidateIterator<Side::Left>(reversedOverhang, wordset->forward);
		
		while (itr.hasNext())
		{
			const auto& nextCandidate = *itr;
			state.wordStack.left.push_back(nextCandidate);
			if (nextCandidate.size() > reversedOverhang.size())
			{
				// Next overhang is going to be on left side now
				std::string nextOverhang = nextCandidate.substr(reversedOverhang.size());
				findPalindromesImpl(wordSets, { { Side::Left, nextOverhang}, state.leftIndex + 1, state.rightIndex, state.wordStack }, toReturn);
			}
			else
			{
				// New word is not long enough, so overhang will remain on right side
				std::string nextOverhang = state.overhang.overhangText.substr(0, reversedOverhang.size() - nextCandidate.size());
				findPalindromesImpl(wordSets, { { Side::Right, nextOverhang }, state.leftIndex + 1, state.rightIndex, state.wordStack }, toReturn);
			}
			state.wordStack.left.pop_back();
			++itr;
		}

	}
}

std::vector<std::string> findPalindromesNew(const std::vector<DoubleOrderedSet*>& wordSets)
{
	std::vector<std::string> toReturn;
	WordStack wordStack;
	findPalindromesImpl(wordSets, { { Side::Right, "" }, 0, wordSets.size() - 1, wordStack }, toReturn);
	return toReturn;
}

} // namespace

std::vector<std::string> findAllPalindromes(const std::vector<std::string>& seedWords, int numberOfWords)
{
	DoubleOrderedSet orderedSet = buildFrom(seedWords);

	std::vector<DoubleOrderedSet*> wordSets;
	for (int i = 0; i < numberOfWords; i++)
	{
		wordSets.push_back(&orderedSet);
	}

	return findPalindromesNew(wordSets);
}

std::vector<std::string> findTypedPalindromes(const std::vector<WordType>& types, const EnumMap<WordType, std::vector<std::string>>& words, bool useNew)
{
	EnumMap<WordType, DoubleOrderedSet> mappedSets;
	for (auto element : words)
	{
		mappedSets.insert({element.first, buildFrom(element.second)});
	}

	std::vector<DoubleOrderedSet*> wordSets;
	for (const auto& type : types)
	{
		wordSets.push_back(&(mappedSets.at(type)));
	}

	if (useNew)
	{
		return findPalindromesNew(wordSets);
	}
	else
	{
		return findPalindromes(wordSets);
	}
}

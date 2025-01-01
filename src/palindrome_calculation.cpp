#include <palindrome_calculation.h>

#include <side.h>

#include <string_set.h>
#include <palindrome_tools.h>
#include <word_candidate_iterator.h>
#include <entire_set_iterator.h>
#include <double_ordered_set.h>
#include <overhang.h>

namespace
{

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

std::vector<std::string> findPalindromes(const std::vector<DoubleOrderedSet*>& wordSets)
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

	return findPalindromes(wordSets);
}

std::vector<std::string> findTypedPalindromes(const std::vector<WordType>& types, const EnumMap<WordType, std::vector<std::string>>& words)
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

	return findPalindromes(wordSets);
}

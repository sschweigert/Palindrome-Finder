#ifndef _WORD_BUILDING_STACK_
#define _WORD_BUILDING_STACK_

#include <memory>
#include <stack>
#include <vector>

#include <word_candidate_iterator.h>
#include <side.h>

struct Overhang
{

	Side::e side;

	std::string overhangText;

};

class WordBuildingStack
{

	public:

		template <Side::e side>
			void push(std::unique_ptr<IWordCandidateIterator<side>> newIterator)
			{
				getStack<side>().push_back(std::move(newIterator));
				lastAddition.push(side);
			}

		Overhang getOverhang() const;

		int size() const;

		void incrementTop();

		bool topHasNext();

		void pop();

		bool empty() const;

		std::string generateString(std::string middleString = "") const;

		template <Side::e side>
			const std::vector<std::unique_ptr<IWordCandidateIterator<side>>>& getStack() const;

		template <Side::e side>
			std::vector<std::unique_ptr<IWordCandidateIterator<side>>>& getStack();

		template <Side::e side>
			int getSideLength() const
			{
				const auto& sideStack = getStack<side>();
				int length = 0;
				for (auto& side : sideStack)
				{
					length += (*side)->size();	
				}
				return length;
			}

		template <Side::e side>
			std::string generateOverhangText(int numMatchingCharacters) const
			{
				std::string toReturn;

				int accumulatedChars = 0;

				const auto& sideStack = getStack<side>();

				int index = sideStack.size() - 1;
				for (; index >= 0 && accumulatedChars < numMatchingCharacters; --index)
				{
					accumulatedChars += (*sideStack[index])->size();	
				}

				int overlapIndex = index + 1;

				int overlapCharPosition;

				if (side == Side::Left)
				{
					overlapCharPosition = accumulatedChars - numMatchingCharacters;
				}
				else
				{
					overlapCharPosition = (*sideStack[overlapIndex])->size() - (accumulatedChars - numMatchingCharacters);
				}

				if (side == Side::Left)
				{
					// Deal with overlapping word
					toReturn = (*sideStack[overlapIndex])->substr(overlapCharPosition);

					for (int appendingIndex = overlapIndex + 1; 
							appendingIndex < sideStack.size() - 1; ++appendingIndex)
					{
						toReturn += **(sideStack[appendingIndex]);
					}
				}
				else
				{
					for (int appendingIndex = sideStack.size() - 1; 
							appendingIndex >= overlapIndex + 1; --appendingIndex)
					{
						toReturn += **(sideStack[appendingIndex]);
					}

					// Deal with overlapping word
					toReturn += (*sideStack[overlapIndex])->substr(0, overlapCharPosition);
				}

				return toReturn;
			}


	private:

		std::stack<Side::e> lastAddition;

		std::vector<std::unique_ptr<IWordCandidateIterator<Side::Left>>> leftIterators;

		std::vector<std::unique_ptr<IWordCandidateIterator<Side::Right>>> rightIterators;

};

#endif

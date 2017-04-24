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

		Overhang getOverhang() const;

		int size() const;

		void incrementTop();

		bool topHasNext();

		Side::e pop();

		bool empty() const;

		std::string generateString(std::string middleString = "") const;

		template <Side::e side>
			void push(IWordCandidateIterator<side>* newIterator);

	private:

		template <Side::e side>
			std::vector<IWordCandidateIterator<side>*>& getStack();

		template <Side::e side>
			const std::vector<IWordCandidateIterator<side>*>& getStack() const;

		template <Side::e side>
			int getSideLength() const;

		template <Side::e side>
			std::string generateOverhangText(int numMatchingCharacters) const;

		std::stack<Side::e> lastAddition;

		std::vector<IWordCandidateIterator<Side::Left>*> leftIterators;

		std::vector<IWordCandidateIterator<Side::Right>*> rightIterators;

};

#endif

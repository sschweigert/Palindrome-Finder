#ifndef _WORD_BUILDING_STACK_
#define _WORD_BUILDING_STACK_

#include <memory>
#include <stack>
#include <vector>

#include <word_candidate_iterator.h>
#include <side.h>

struct Overhang
{

	Side side;

	std::string overhangText;

};

class WordBuildingStack
{

	public:

		Overhang getOverhang() const;

		int size() const;

		void incrementTop();

		bool topHasNext();

		Side pop();

		bool empty() const;

		std::string generateString(std::string middleString = "") const;

		template <Side side>
			void push(IWordCandidateIterator<side>* newIterator);

	private:

		template <Side side>
			std::vector<IWordCandidateIterator<side>*>& getStack();

		template <Side side>
			const std::vector<IWordCandidateIterator<side>*>& getStack() const;

		template <Side side>
			int getSideLength() const;

		template <Side side>
			std::string generateOverhangText(int numMatchingCharacters) const;

		std::stack<Side> lastAddition;

		std::vector<IWordCandidateIterator<Side::Left>*> leftIterators;

		std::vector<IWordCandidateIterator<Side::Right>*> rightIterators;

};

#endif

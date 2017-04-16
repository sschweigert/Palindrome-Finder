#ifndef _WORD_BUILDING_STACK_
#define _WORD_BUILDING_STACK_

#include <memory>
#include <stack>
#include <vector>

#include <iword_candidate_iterator.h>
#include <side.h>

struct Overhang
{

	Side side;

	std::string overhangText;

};

class WordBuildingStack
{

	public:

		void addItem(std::unique_ptr<IForwardWordCandidateIterator> leftIterator);

		void addItem(std::unique_ptr<IReverseWordCandidateIterator> rightIterator);

		Overhang getOverhang() const;

		int size() const;

		IWordCandidateIterator& top();

		void pop();

	private:

		const std::vector<IWordCandidateIterator*>& getSideStack(Side side) const;

		int getSideLength(Side side) const;

		std::stack<std::unique_ptr<IWordCandidateIterator>> candidateStack;

		std::vector<IWordCandidateIterator*> leftIterators;

		std::vector<IWordCandidateIterator*> rightIterators;

};

#endif

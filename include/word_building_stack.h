#ifndef _WORD_BUILDING_STACK_
#define _WORD_BUILDING_STACK_

#include <memory>
#include <stack>
#include <vector>

#include <iword_candidate_iterator.h>

class WordBuildingStack
{

	public:

		void addItem(std::unique_ptr<IForwardWordCandidateIterator> leftIterator);

		void addItem(std::unique_ptr<IReverseWordCandidateIterator> rightIterator);

	private:

		std::stack<std::unique_ptr<IWordCandidateIterator>> candidateStack;

		std::vector<IForwardWordCandidateIterator*> leftIterators;

		std::vector<IReverseWordCandidateIterator*> rightIterators;

};

#endif

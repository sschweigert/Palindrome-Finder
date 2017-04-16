#include <word_building_stack.h>

void WordBuildingStack::addItem(std::unique_ptr<IForwardWordCandidateIterator> leftIterator)
{
	leftIterators.push_back(leftIterator.get());
	candidateStack.push(std::move(leftIterator));
}

void WordBuildingStack::addItem(std::unique_ptr<IReverseWordCandidateIterator> rightIterator)
{
	rightIterators.push_back(rightIterator.get());
	candidateStack.push(std::move(rightIterator));
}

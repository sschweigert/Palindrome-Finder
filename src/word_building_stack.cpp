#include <word_building_stack.h>

void WordBuildingStack::push(std::unique_ptr<IForwardWordCandidateIterator> leftIterator)
{
	leftIterators.push_back(leftIterator.get());
	candidateStack.push(std::move(leftIterator));
}

void WordBuildingStack::push(std::unique_ptr<IReverseWordCandidateIterator> rightIterator)
{
	rightIterators.push_back(rightIterator.get());
	candidateStack.push(std::move(rightIterator));
}

const std::vector<IWordCandidateIterator*>& WordBuildingStack::getSideStack(Side side) const
{
	if (side == Side::Left)
	{
		return leftIterators;
	}
	else
	{
		return rightIterators;
	}
}

int WordBuildingStack::getSideLength(Side side) const
{
	const std::vector<IWordCandidateIterator*>& sideStack = getSideStack(side);
	int length = 0;
	for (auto& side : sideStack)
	{
		length += (*side)->size();	
	}
	return length;
}

Overhang WordBuildingStack::getOverhang() const
{
	Overhang toReturn;

	int leftSideLength = getSideStack(Side::Left).size();
	int rightSideLength = getSideStack(Side::Right).size();

	toReturn.side = (rightSideLength > leftSideLength) ? Side::Right : Side::Left; 

	// Number of left characters that must be matched by the new right characters
	int numMatchingCharacters = std::abs(rightSideLength - leftSideLength);

	int accumulatedChars = 0;

	auto sideStack = getSideStack(toReturn.side);

	int index = sideStack.size() - 1;
	for (; index >= 0 && accumulatedChars < numMatchingCharacters; --index)
	{
		accumulatedChars += (*sideStack[index])->size();	
	}

	int overlapCharPosition = accumulatedChars - numMatchingCharacters;
	int overlapIndex = index;

	if (toReturn.side == Side::Left)
	{
		// Deal with overlapping word
		toReturn.overhangText = (*sideStack[overlapIndex])->substr(overlapCharPosition);

		for (int appendingIndex = overlapIndex + 1; 
			appendingIndex < sideStack.size() - 1; ++appendingIndex)
		{
			toReturn.overhangText += **(sideStack[appendingIndex]);
		}
	}
	else
	{
		for (int appendingIndex = sideStack.size() - 1; 
			appendingIndex > overlapIndex; --appendingIndex)
		{
			toReturn.overhangText += **(sideStack[appendingIndex]);
		}

		// Deal with overlapping word
		toReturn.overhangText += (*sideStack[overlapIndex])->substr(0, overlapCharPosition);
	}

	return toReturn;

}

int WordBuildingStack::size() const
{
	return candidateStack.size();
}

IWordCandidateIterator& WordBuildingStack::top()
{
	return *candidateStack.top();
}

void WordBuildingStack::pop()
{
	IWordCandidateIterator* toPop = &top();

	if (leftIterators.back() == toPop)
	{
		leftIterators.pop_back();
	}
	else
	{
		rightIterators.pop_back();
	}

	candidateStack.pop();
}

std::string WordBuildingStack::generateString() const
{
	std::string toReturn;

	for (int i = 0; i < leftIterators.size(); i++)
	{
		toReturn += **leftIterators[i];
	}

	for (int i = rightIterators.size() - 1; i >= 0; i--)
	{
		toReturn += **leftIterators[i];
	}

	return toReturn;
}

#include <word_building_stack.h>

template <Side side>
void WordBuildingStack::push(IWordCandidateIterator<side>* newIterator)
{
	getStack<side>().push_back(newIterator);
	lastAddition.push(side);
}

template <Side side>
int WordBuildingStack::getSideLength() const
{
	const auto& sideStack = getStack<side>();
	int length = 0;
	for (auto& word : sideStack)
	{
		length += (**word).size();	
	}
	return length;
}

template <Side side>
std::string WordBuildingStack::generateOverhangText(int numMatchingCharacters) const
{
	std::string toReturn;

	int accumulatedChars = 0;

	const auto& sideStack = getStack<side>();

	int index = sideStack.size() - 1;
	for (; index >= 0 && accumulatedChars <= numMatchingCharacters; --index)
	{
		accumulatedChars += (**sideStack[index]).size();	
	}

	int overlapIndex = index + 1;

	int overlapCharPosition;

	if (side == Side::Left)
	{
		overlapCharPosition = accumulatedChars - numMatchingCharacters;
	}
	else
	{
		overlapCharPosition = (**sideStack[overlapIndex]).size() - (accumulatedChars - numMatchingCharacters);
	}

	if (side == Side::Left)
	{
		// Deal with overlapping word
		toReturn = (**sideStack[overlapIndex]).substr(overlapCharPosition);

		for (unsigned int appendingIndex = overlapIndex + 1; 
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
		toReturn += (**sideStack[overlapIndex]).substr(0, overlapCharPosition);
	}

	return toReturn;
}

// Explicitly extantiate public functions
template void WordBuildingStack::push<Side::Left>(IWordCandidateIterator<Side::Left>* newIterator);
template void WordBuildingStack::push<Side::Right>(IWordCandidateIterator<Side::Right>* newIterator);

template <>
const std::vector<IWordCandidateIterator<Side::Left>*>& WordBuildingStack::getStack<Side::Left>() const
{
	return leftIterators;
}

template <>
const std::vector<IWordCandidateIterator<Side::Right>*>& WordBuildingStack::getStack<Side::Right>() const
{
	return rightIterators;
}

	template <>
std::vector<IWordCandidateIterator<Side::Left>*>& WordBuildingStack::getStack<Side::Left>()
{
	return leftIterators;
}

	template <>
std::vector<IWordCandidateIterator<Side::Right>*>& WordBuildingStack::getStack<Side::Right>()
{
	return rightIterators;
}

void WordBuildingStack::incrementTop()
{
	if (lastAddition.top() == Side::Left)
	{
		++(*(getStack<Side::Left>().back()));
	}
	else
	{
		++(*(getStack<Side::Right>().back()));
	}
}

bool WordBuildingStack::topHasNext()
{
	if (lastAddition.top() == Side::Left)
	{
		return getStack<Side::Left>().back()->hasNext();
	}
	else
	{
		return getStack<Side::Right>().back()->hasNext();
	}
}

Overhang WordBuildingStack::getOverhang() const
{
	Overhang toReturn;

	int leftSideLength = getSideLength<Side::Left>();
	int rightSideLength = getSideLength<Side::Right>();

	toReturn.side = (rightSideLength > leftSideLength) ? Side::Right : Side::Left; 

	// Number of left characters that must be matched by the new right characters
	int numMatchingCharacters = std::abs(rightSideLength - leftSideLength);

	if (toReturn.side == Side::Right)
	{	
		toReturn.overhangText = generateOverhangText<Side::Right>(numMatchingCharacters);
	}
	else
	{
		toReturn.overhangText = generateOverhangText<Side::Left>(numMatchingCharacters);
	}

	return toReturn;

}

int WordBuildingStack::size() const
{
	return lastAddition.size();
}

Side WordBuildingStack::pop()
{
	Side sideToPop = lastAddition.top();
	if (sideToPop == Side::Left)
	{
		leftIterators.pop_back();
	}
	else
	{
		rightIterators.pop_back();
	}

	lastAddition.pop();
	return sideToPop;
}

std::string WordBuildingStack::generateString(std::string middleString) const
{
	std::string toReturn;

	for (unsigned int i = 0; i < leftIterators.size(); i++)
	{
		toReturn += **leftIterators[i];
		toReturn += ' ';
	}

	if (middleString != "")
	{
		toReturn += middleString;
		toReturn += ' ';
	}

	for (int i = rightIterators.size() - 1; i >= 0; i--)
	{
		toReturn += **rightIterators[i];
		toReturn += ' ';
	}

	toReturn.pop_back();

	return toReturn;
}

bool WordBuildingStack::empty() const
{
	return (size() == 0);
}

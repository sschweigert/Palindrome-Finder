#include <word_building_stack.h>

template <Side side>
void WordBuildingStack::push(IWordCandidateIterator<side>* newIterator)
{
	getStackStatic<side>().push_back(newIterator);
	lastAddition.push(side);
}

template <Side side>
int WordBuildingStack::getSideLength() const
{
	const auto& sideStack = getStackStatic<side>();
	int length = 0;
	for (auto& word : sideStack)
	{
		length += (**word).size();	
	}
	return length;
}

OverhangSplitProperties WordBuildingStack::findSplitProperties(Side side, const std::vector<IWordIterator*>& sideStack, int numMatchingCharacters) const
{
	OverhangSplitProperties splitProperties;

	int accumulatedChars = 0;

	int index = sideStack.size() - 1;
	while (index >= 0 && accumulatedChars <= numMatchingCharacters)
	{
		accumulatedChars += (**sideStack[index]).size();	

		 --index;
	}

	splitProperties.overlapIndex = index + 1;

	if (side == Side::Left)
	{
		splitProperties.overlapCharPosition = accumulatedChars - numMatchingCharacters;
	}
	else
	{
		splitProperties.overlapCharPosition = (**sideStack[splitProperties.overlapIndex]).size() - (accumulatedChars - numMatchingCharacters);
	}
	return splitProperties;
}

template <Side side>
std::string WordBuildingStack::generateOverhangText(int numMatchingCharacters) const
{
	std::string toReturn;


	const auto& sideStack = getStackStatic<side>();

	OverhangSplitProperties splitProperties = findSplitProperties(side, sideStack, numMatchingCharacters);

	if (side == Side::Left)
	{
		// Deal with overlapping word
		toReturn = (**sideStack[splitProperties.overlapIndex]).substr(splitProperties.overlapCharPosition);

		for (unsigned int appendingIndex = splitProperties.overlapIndex + 1; 
				appendingIndex < sideStack.size() - 1; ++appendingIndex)
		{
			toReturn += **(sideStack[appendingIndex]);
		}
	}
	else
	{
		for (int appendingIndex = sideStack.size() - 1; 
				appendingIndex >= splitProperties.overlapIndex + 1; --appendingIndex)
		{
			toReturn += **(sideStack[appendingIndex]);
		}

		// Deal with overlapping word
		toReturn += (**sideStack[splitProperties.overlapIndex]).substr(0, splitProperties.overlapCharPosition);
	}

	return toReturn;
}

// Explicitly extantiate public functions
template void WordBuildingStack::push<Side::Left>(IWordCandidateIterator<Side::Left>* newIterator);
template void WordBuildingStack::push<Side::Right>(IWordCandidateIterator<Side::Right>* newIterator);

template <>
const std::vector<IWordIterator*>& WordBuildingStack::getStackStatic<Side::Left>() const
{
	return leftIterators;
}

template <>
const std::vector<IWordIterator*>& WordBuildingStack::getStackStatic<Side::Right>() const
{
	return rightIterators;
}

template <>
std::vector<IWordIterator*>& WordBuildingStack::getStackStatic<Side::Left>()
{
	return leftIterators;
}

template <>
std::vector<IWordIterator*>& WordBuildingStack::getStackStatic<Side::Right>()
{
	return rightIterators;
}

void WordBuildingStack::incrementTop()
{
	++(getTop());
}

bool WordBuildingStack::topHasNext() const
{
	return getTop().hasNext();
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
	getStackDynamic(sideToPop).pop_back();

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

IWordIterator& WordBuildingStack::getTop()
{
	return const_cast<IWordIterator&>(static_cast<const WordBuildingStack*>(this)->getTop());
}

const IWordIterator& WordBuildingStack::getTop() const
{
	Side sideToPop = lastAddition.top();
	return *(getStackDynamic(sideToPop).back());
}

std::vector<IWordIterator*>& WordBuildingStack::getStackDynamic(Side side)
{
	return const_cast<std::vector<IWordIterator*>&>(static_cast<const WordBuildingStack*>(this)->getStackDynamic(side));
}

const std::vector<IWordIterator*>& WordBuildingStack::getStackDynamic(Side side) const
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

bool WordBuildingStack::empty() const
{
	return lastAddition.empty();
}

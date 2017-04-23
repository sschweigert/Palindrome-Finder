#include <word_building_stack.h>

template <>
const std::vector<std::unique_ptr<IWordCandidateIterator<Side::Left>>>& WordBuildingStack::getStack<Side::Left>() const
{
	return leftIterators;
}

template <>
const std::vector<std::unique_ptr<IWordCandidateIterator<Side::Right>>>& WordBuildingStack::getStack<Side::Right>() const
{
	return rightIterators;
}

template <>
std::vector<std::unique_ptr<IWordCandidateIterator<Side::Left>>>& WordBuildingStack::getStack<Side::Left>()
{
	return leftIterators;
}

template <>
std::vector<std::unique_ptr<IWordCandidateIterator<Side::Right>>>& WordBuildingStack::getStack<Side::Right>()
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

void WordBuildingStack::pop()
{
	if (lastAddition.top() == Side::Left)
	{
		leftIterators.pop_back();
	}
	else
	{
		rightIterators.pop_back();
	}

	lastAddition.pop();
}

std::string WordBuildingStack::generateString(std::string middleString) const
{
	std::string toReturn;

	for (int i = 0; i < leftIterators.size(); i++)
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

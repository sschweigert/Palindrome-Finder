#include <string_set.h>

bool ReverseLess::operator()(const std::string& first, const std::string& second) const
{
	auto firstItr = first.rbegin();
	auto secondItr = second.rbegin();

	auto firstEnd = first.rend();
	auto secondEnd = second.rend();

	while (true)
	{
		if (secondItr == secondEnd)
		{
			// second <= first, therefore !(first < second)
			return false;
		}
		else if (firstItr == firstEnd)
		{
			return true;
		}
		else if (*firstItr != *secondItr)
		{
			return *firstItr < *secondItr;
		}
		++firstItr;
		++secondItr;
	}
}

#include <specialized_subword_behaviors.h>

std::string SpecializedSubwordBehaviors<Side::Left>::buildOntoWord(std::string word, char toAdd)
{
	return (word + toAdd);
}

std::string SpecializedSubwordBehaviors<Side::Right>::buildOntoWord(std::string word, char toAdd)
{
	return (toAdd + word);
}

typename SpecializedSubwordBehaviors<Side::Left>::iterator SpecializedSubwordBehaviors<Side::Left>::begin(const std::string& toIterate)
{
	return toIterate.begin();
}

typename SpecializedSubwordBehaviors<Side::Left>::iterator SpecializedSubwordBehaviors<Side::Left>::end(const std::string& toIterate)
{
	return toIterate.end();
}

typename SpecializedSubwordBehaviors<Side::Right>::iterator SpecializedSubwordBehaviors<Side::Right>::begin(const std::string& toIterate)
{
	return toIterate.rbegin();
}

typename SpecializedSubwordBehaviors<Side::Right>::iterator SpecializedSubwordBehaviors<Side::Right>::end(const std::string& toIterate)
{
	return toIterate.rend();
}

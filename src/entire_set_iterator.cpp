#include <entire_set_iterator.h>

template <Side::e side>
EntireSetIterator<side>::EntireSetIterator(const SetType& set) :
mData(set),
mCurrentPos(set.begin())
{}

template <Side::e side>
const std::string& EntireSetIterator<side>::operator*() const
{
	return *mCurrentPos;
}

template <Side::e side>
bool EntireSetIterator<side>::hasNext()
{
	return mCurrentPos != mData.end();
}

template <Side::e side>
IWordCandidateIterator<side>& EntireSetIterator<side>::operator++()
{
	++mCurrentPos;
	return *this;
}

template class EntireSetIterator<Side::Left>;
template class EntireSetIterator<Side::Right>;

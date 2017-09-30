#include <entire_set_iterator.h>

template <Side side>
EntireSetIterator<side>::EntireSetIterator(const SortedStringSet<side>& set) :
mCurrentPos(set.begin()),
mData(set)
{}

template <Side side>
const std::string& EntireSetIterator<side>::operator*() const
{
	return *mCurrentPos;
}

template <Side side>
bool EntireSetIterator<side>::hasNext()
{
	return mCurrentPos != mData.end();
}

template <Side side>
IWordCandidateIterator<side>& EntireSetIterator<side>::operator++()
{
	++mCurrentPos;
	return *this;
}

template class EntireSetIterator<Side::Left>;
template class EntireSetIterator<Side::Right>;

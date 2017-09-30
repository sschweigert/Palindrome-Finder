#include <entire_set_iterator.h>

template <Side side>
EntireSetIterator<side>::EntireSetIterator(const SortedStringSet<side>& set) :
mCurrent(set.begin()),
mEnd(set.end())
{}

template <Side side>
const std::string& EntireSetIterator<side>::operator*() const
{
	return *mCurrent;
}

template <Side side>
bool EntireSetIterator<side>::hasNext()
{
	return mCurrent != mEnd;
}

template <Side side>
IWordIterator& EntireSetIterator<side>::operator++()
{
	++mCurrent;
	return *this;
}

template class EntireSetIterator<Side::Left>;
template class EntireSetIterator<Side::Right>;

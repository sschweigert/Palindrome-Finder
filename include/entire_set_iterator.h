#ifndef _ENTIRE_SET_ITERATOR_
#define _ENTIRE_SET_ITERATOR_

#include <iword_candidate_iterator.h>

#include <string_set.h>
#include <side.h>

template <Side::e side>
class EntireSetIterator : public IWordCandidateIterator<side>
{

		typedef typename TypeTraits<side>::Set SetType;

	public:

		EntireSetIterator(const SetType& set) :
		mData(set),
		mCurrentPos(set.begin())
		{}

		virtual const std::string& operator*() const
		{
			return *mCurrentPos;
		}

		virtual bool hasNext()
		{
			return mCurrentPos != mData.end();
		}

		virtual IWordCandidateIterator<side>& operator++()
		{
			++mCurrentPos;
			return *this;
		}

	private:

		typename SetType::const_iterator mCurrentPos;

		const SetType& mData;

};

#endif

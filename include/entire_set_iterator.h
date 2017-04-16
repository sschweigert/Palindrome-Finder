#ifndef _ENTIRE_SET_ITERATOR_
#define _ENTIRE_SET_ITERATOR_

#include <iword_candidate_iterator.h>

template <class SetType>
class EntireSetIterator : public IWordCandidateIterator
{

	public:

		EntireSetIterator(const SetType& set) :
		mData(set),
		mCurrentPos(set.begin())
		{}

		virtual std::string operator*()
		{
			return *mCurrentPos;
		}

		virtual bool hasNext()
		{
			return mCurrentPos != mData.end();
		}

		virtual IWordCandidateIterator& operator++()
		{
			++mCurrentPos;
			return *this;
		}

	private:

		typename SetType::const_iterator mCurrentPos;

		const SetType& mData;

};

#endif

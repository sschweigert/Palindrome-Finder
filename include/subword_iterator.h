#ifndef _SUBWORD_ITERATOR_
#define _SUBWORD_ITERATOR_

#include <iword_candidate_iterator.h>
#include <string_set.h>


class ForwardSubwordIterator : public IWordCandidateIterator
{

	public:

		ForwardSubwordIterator(const std::string& wordToMatch, const ForwardStringSet& wordsToSearch);

		virtual const std::string& operator*() const;

		virtual bool hasNext();

		virtual IWordCandidateIterator& operator++();

	private:

		bool mHasNext;

		int mIndex;
		
		const std::string& mWordToMatch;

		const ForwardStringSet& mWordsToSearch;

		std::string mSubWord;
		
};


class ReverseSubwordIterator : public IWordCandidateIterator
{

	public:

		ReverseSubwordIterator(const std::string& wordToMatch, const ReverseStringSet& wordsToSearch);

		virtual const std::string& operator*() const;

		virtual bool hasNext();

		virtual IWordCandidateIterator& operator++();

	private:

		bool mHasNext;

		int mIndex;
		
		const std::string& mWordToMatch;

		const ReverseStringSet& mWordsToSearch;

		std::string mSubWord;
		
};

#endif

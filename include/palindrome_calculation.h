#ifndef _PALINDROME_CALCULATION_H_
#define _PALINDROME_CALCULATION_H_

#include <vector>
#include <string>
#include <stack>

#include <side.h>

#include <iostream>
#include <set>
#include <algorithm>
#include <functional>
#include <memory>
#include <unordered_map>

#include <string_set.h>
#include <palindrome_tools.h>
#include <word_candidate_iterator.h>
#include <entire_set_iterator.h>
#include <word_building_stack.h>
#include <double_ordered_set.h>
#include <timer.h>

std::vector<std::string> findAllPalindromes(const std::vector<std::string>& seedWords, int numberOfWords);

void incrementStack(WordBuildingStack& wordBuildingStack, std::stack<WordCandidateIterator<Side::Left>>& concreteLeftIterators, std::stack<WordCandidateIterator<Side::Right>>& concreteRightIterators);

/*
template <class Functor, Side side>
class IteratorWrapper : public IWordCandidateIterator<side>
{

	public:

		IteratorWrapper(IWordCandidateIterator<side>& wordCandidateIterator, Functor& functor) :
			wordCandidateIterator(wordCandidateIterator),
			functor(functor)
	{}

		virtual const std::string& operator*() const
		{
			return *wordCandidateIterator;
		}

		virtual bool hasNext() const
		{
			return wordCandidateIterator.hasNext();
		}

		virtual IWordCandidateIterator<side>& operator++()
		{
			functor();
			++wordCandidateIterator;
			return *this;
		}


	private:

		IWordCandidateIterator<side>& wordCandidateIterator;

		Functor& functor;

};


int count = 0;
auto counter = [&]
{
	const float percentStep = 0.5;
	int countStep = ((float)percentStep / 100.0) * (float)forwardOrdering.size();
	countStep = std::max(1, countStep);

	++count;
	if (count % countStep == 0)
	{
		float fraction = (float)count / (float)forwardOrdering.size();
		std::cout << (fraction * 100.0) << "% done" << std::endl;
		
	}

};

IteratorWrapper<decltype(counter), Side::Left> wrappedItr(entireSetOrdering, counter);
*/

#endif

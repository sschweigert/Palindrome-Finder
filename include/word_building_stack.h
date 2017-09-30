#ifndef _WORD_BUILDING_STACK_
#define _WORD_BUILDING_STACK_

#include <memory>
#include <stack>
#include <vector>

#include <word_candidate_iterator.h>
#include <side.h>
#include <overhang.h>

class WordBuildingStack
{

	public:

		//! \brief Calculate the amount one side is larger than the other, and the string
		//! that accounts for the extra size.
		Overhang getOverhang() const;

		//! \brief Get the number of words in the stack.
		int size() const;

		//! \brief Remove the top of the stack.
		//! \return The Side from which the top was removed.
		Side pop();

		//! \brief Check if there are any iterators in the stack.
		bool empty() const;

		//! \brief Generate a string from whatever is currently in the stack by concatenating
		//! words stored in the iterators with spaces in between.
		std::string generateString(std::string middleString) const;

		//! \brief Increment the current top iterator.
		void incrementTop();

		//! \brief Check if the top iterator is pointing to a valid state.
		bool topHasNext() const;

		//! \brief Add a new iterator to the stack.
		template <Side side>
			void push(IWordCandidateIterator<side>* newIterator);

	private:

		template <Side side>
			std::vector<IWordIterator*>& getStackStatic();

		template <Side side>
			const std::vector<IWordIterator*>& getStackStatic() const;

			IWordIterator& getTop();

			const IWordIterator& getTop() const;

		template <Side side>
			int getSideLength() const;

		template <Side side>
			std::string generateOverhangText(int numMatchingCharacters) const;

		std::stack<Side> lastAddition;

		std::vector<IWordIterator*> leftIterators;

		std::vector<IWordIterator*> rightIterators;

};

#endif

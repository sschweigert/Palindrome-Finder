#include <cxxtest/TestSuite.h>

#include <subword_iterator.h>
#include <string_set.h>

class SubwordIteratorTest : public CxxTest::TestSuite
{

	public:

		void testForwardSubwordIterator(void)
		{
			typename TypeTraits<Side::Left>::Set set;
			
			set.insert("a");
			set.insert("app");

	
			std::string wordToMatch = "apple";

			SubwordIterator<Side::Left> subwordIterator(wordToMatch, set);
			//ForwardSubwordIterator subwordIterator(wordToMatch, set);
			
			TS_ASSERT(subwordIterator.hasNext());
			TS_ASSERT_EQUALS(*subwordIterator, "a");

			++subwordIterator;

			TS_ASSERT(subwordIterator.hasNext());
			TS_ASSERT_EQUALS(*subwordIterator, "app");

			++subwordIterator;

			TS_ASSERT(!subwordIterator.hasNext());
		}

		void testReverseSubwordIterator(void)
		{
			typename TypeTraits<Side::Right>::Set set;
			
			set.insert("e");
			set.insert("ple");

	
			std::string wordToMatch = "apple";

			SubwordIterator<Side::Right> subwordIterator(wordToMatch, set);
			
			TS_ASSERT(subwordIterator.hasNext());
			TS_ASSERT_EQUALS(*subwordIterator, "e");

			++subwordIterator;

			TS_ASSERT(subwordIterator.hasNext());
			TS_ASSERT_EQUALS(*subwordIterator, "ple");

			++subwordIterator;

			TS_ASSERT(!subwordIterator.hasNext());
		}

};

#include <cxxtest/TestSuite.h>

#include <subword_iterator.h>
#include <string_set.h>

class SubwordIteratorTest : public CxxTest::TestSuite
{

	public:

		void testForwardSubwordIterator(void)
		{
			TypeTraits<Side::Left>::Set set =
			{
				"a",
				"app",
				"apple"
			};

	
			std::string wordToMatch = "apple";

			SubwordIterator<Side::Left> subwordIterator(wordToMatch, set);
			
			TS_ASSERT(subwordIterator.hasNext());
			TS_ASSERT_EQUALS(*subwordIterator, "a");

			++subwordIterator;

			TS_ASSERT(subwordIterator.hasNext());
			TS_ASSERT_EQUALS(*subwordIterator, "app");

			++subwordIterator;

			TS_ASSERT(subwordIterator.hasNext());
			TS_ASSERT_EQUALS(*subwordIterator, "apple");

			++subwordIterator;

			TS_ASSERT(!subwordIterator.hasNext());
		}

		void testForwardNoFind(void)
		{
			TypeTraits<Side::Left>::Set set =
			{
				"unrelated",
				"no_match"
			};

	
			std::string wordToMatch = "apple";

			SubwordIterator<Side::Left> subwordIterator(wordToMatch, set);
			
			TS_ASSERT(!subwordIterator.hasNext());
		}

		void testReverseSubwordIterator(void)
		{
			TypeTraits<Side::Right>::Set set =
			{
				"e",
				"ple"
			};

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

		void testSingleLetterTest(void)
		{
			TypeTraits<Side::Left>::Set set =
			{
				"a"
			};

			std::string wordToMatch = "a";

			SubwordIterator<Side::Left> subwordIterator(wordToMatch, set);
			
			TS_ASSERT(subwordIterator.hasNext());
			TS_ASSERT_EQUALS(*subwordIterator, "a");

			++subwordIterator;

			TS_ASSERT(!subwordIterator.hasNext());
		}

};

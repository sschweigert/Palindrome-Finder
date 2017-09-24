#include <cxxtest/TestSuite.h>

#include <unordered_set>
#include <iostream>

#include <palindrome_calculation.h>

class PalindromeCalculationTest : public CxxTest::TestSuite
{

	public:

		// Simple "sanity check" using single letter words and exploiting the combinatorial
		// nature of palindromes
		void testSingleLetterPermutations(void)
		{
	
			std::vector<std::string> seedWords =
			{
				"a",
				"b",
				"c"
			};

			std::vector<std::string> result = calculatePalindromes(seedWords, 3);

			std::unordered_set<std::string> expectedResult =
			{
				"a a a",
				"a b a",
				"a c a",

				"b a b",
				"b b b",
				"b c b",

				"c a c",
				"c b c",
				"c c c"
			};

			TS_ASSERT(expectedResult.size() == result.size());

			for (const auto& resultString : result)
			{
				bool matchesExpected = (expectedResult.count(resultString) == 1);
				TS_ASSERT(matchesExpected);
			}
		}

};

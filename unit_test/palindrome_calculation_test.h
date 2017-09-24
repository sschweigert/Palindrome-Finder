#include <cxxtest/TestSuite.h>

#include <unordered_set>
#include <iostream>

#include <palindrome_calculation.h>

class PalindromeCalculationTest : public CxxTest::TestSuite
{

	public:

		void verifyPalindrome(const std::vector<std::string>& input, int length, const std::unordered_set<std::string>& expectedOutput)
		{
			std::vector<std::string> result = calculatePalindromes(input, length);

			TS_ASSERT(expectedOutput.size() == result.size());

			for (const auto& resultString : result)
			{
				bool matchesExpected = (expectedOutput.count(resultString) == 1);
				TS_ASSERT(matchesExpected);
			}
		}

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

			const int palindromeLength = 3;

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

			verifyPalindrome(seedWords, palindromeLength, expectedResult);
		}

		// Make sure palindromes are found in the extreme case of a, aaa, z and zzz.
		// These have caused problems before where they were skipped or caused hanging/crashes.
		void testFirstAndLastCheck(void)
		{
			std::vector<std::string> seedWords =
			{
				"a",
				"aaa",
				"z",
				"zzz"
			};

			const int palindromeLength = 3;

			std::unordered_set<std::string> expectedResult =
			{
				"a a a",
				"a aaa a",
				"a z a",
				"a zzz a",
				"a a aaa",
				"a aaa aaa",
				"aaa a a",
				"aaa aaa a",
				"aaa a aaa",
				"aaa aaa aaa",
				"aaa z aaa",
				"aaa zzz aaa",
				"z a z",
				"z aaa z",
				"z z z",
				"z zzz z",
				"z z zzz",
				"z zzz zzz",
				"zzz z z",
				"zzz zzz z",
				"zzz a zzz",
				"zzz aaa zzz",
				"zzz z zzz",
				"zzz zzz zzz"
			};

			verifyPalindrome(seedWords, palindromeLength, expectedResult);
		}

};

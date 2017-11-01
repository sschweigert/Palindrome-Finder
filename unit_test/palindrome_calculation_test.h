#include <cxxtest/TestSuite.h>

#include <unordered_set>
#include <iostream>

#include <palindrome_calculation.h>

class PalindromeCalculationTest : public CxxTest::TestSuite
{

	public:

		void verifyPalindrome(const std::vector<std::string>& input, int length, const std::unordered_set<std::string>& expectedOutput)
		{
			std::vector<std::string> result = findAllPalindromes(input, length);

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

		bool allPalindromes(const std::vector<std::string>& results)
		{
			bool toReturn = true;
			for (const auto& result : results) 
			{
				toReturn &= isPalindrome(result); 
			}
			return toReturn;
		}

		// Split a string into substrings separated by a character
		std::vector<std::string> splitString(const std::string& toSplit, char splittingChar)
		{
			std::vector<std::string> toReturn;

			auto beginSplit = toSplit.begin();
			decltype(beginSplit) endSplit;

			do
			{
				endSplit = std::find(beginSplit, toSplit.end(), splittingChar);

				if (beginSplit == toSplit.end())
				{
					break;
				}

				toReturn.push_back(std::string(beginSplit, endSplit));
				
				beginSplit = std::next(endSplit);

			} while (endSplit != toSplit.end());

			return toReturn;

		}

		void testSplitSingleString(void)
		{
			std::string single = "single";	

			std::vector<std::string> expected = { "single" };

			TS_ASSERT(expected == splitString(single, ' '));
		}

		void testSplitMultipleStrings(void)
		{
			std::string single = "first second third";	

			std::vector<std::string> expected = { "first", "second", "third" };

			TS_ASSERT(expected == splitString(single, ' '));
		}

		// Verify that the results only contain words from the seeds
		bool resultsFromSeed(const std::vector<std::string>& seedWords, const std::vector<std::string>& results)
		{
			std::unordered_set<std::string> seedSet(seedWords.begin(), seedWords.end());

			bool toReturn = true;
			for (const auto& result : results)
			{
				auto splitResult = splitString(result, ' ');
				for (const auto& word : splitResult)
				{
					toReturn &= (seedSet.count(word) == 1);
				}
			}
			return toReturn;
		}

		bool foundPalindromes(const std::unordered_set<std::string>& expectedPalindromes, const std::vector<std::string>& results)
		{
			std::unordered_set<std::string> resultsSet(results.begin(), results.end());

			bool toReturn = true;
			for (const auto& expectedPalindrome : expectedPalindromes)
			{
				toReturn &= (resultsSet.count(expectedPalindrome) == 1);
			}
			return toReturn;
		}

		// Make sure palindromes are found in the extreme case of a, aaa, z and zzz.
		// These have caused problems before where they were skipped or caused hanging/crashes.
		void testLongerPhrases(void)
		{
			std::vector<std::string> seedWords =
			{
				"no",
				"worm",
				"star",
				"live",
				"emit",
				"time",
				"on",
				"evil",
				"my",
				"metal",
				"owl",
				"ate",
				"rats"
			};

			const int palindromeLength = 6;

			std::unordered_set<std::string> expectedResult =
			{
				"rats live on no evil star",
				"live on time emit no evil"
			};

			std::vector<std::string> result = findAllPalindromes(seedWords, palindromeLength);

			TS_ASSERT(allPalindromes(result));
			TS_ASSERT(resultsFromSeed(seedWords, result));
			TS_ASSERT(foundPalindromes(expectedResult, result));
		}

		void testLongerWord(void)
		{
			std::vector<std::string> seedWords =
			{
				"evil",
				"live",
				"rats",
				"star"
			};

			const int palindromeLength = 2;

			std::unordered_set<std::string> expectedResult =
			{
				"evil live",
				"live evil",
				"star rats",
				"rats star"
			};

			verifyPalindrome(seedWords, palindromeLength, expectedResult);
		}

};

#include <cxxtest/TestSuite.h>

#include <unordered_set>
#include <iostream>

#include <palindrome_calculation.h>

class PalindromeCalculationTest : public CxxTest::TestSuite
{

	public:

		void testBasicPalindromeCalculation(void)
		{
			std::vector<std::string> seedWords =
			{
				"a"
			};

			std::vector<std::string> result = calculatePalindromes(seedWords, 3);

			std::unordered_set<std::string> expectedResult =
			{
				"a a a"
			};

			std::cout << "Found: " << result.size() << " palindromes" << std::endl;
			//TS_ASSERT(expectedResult.size() == result.size());

			for (const auto& resultString : result)
			{
				bool matchesExpected = (expectedResult.count(resultString) == 1);
				std::cout << resultString << std::endl;
				//TS_ASSERT(matchesExpected);
			}
		}

};

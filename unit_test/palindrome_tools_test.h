#include <cxxtest/TestSuite.h>

#include <palindrome_tools.h>

class PalindromeToolsTest : public CxxTest::TestSuite
{

	public:

		void testPalindromeIndentification(void)
		{
			TS_ASSERT(isPalindrome("racecar"));
			TS_ASSERT(!isPalindrome("bacecar"));
		}

		void testForwardWordIncrementation(void)
		{
			auto incrementResult = incrementWord("a");
			
			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "b");

			incrementResult = incrementWord("sebastian");

			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "sebastiao");

			incrementResult = incrementWord("pizazz");

			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "pizbaa");

			incrementResult = incrementWord("azzzzz");

			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "baaaaa");

			incrementResult = incrementWord("zzzzzzz");

			TS_ASSERT(!incrementResult);
		}
};

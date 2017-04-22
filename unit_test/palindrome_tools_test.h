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
			auto incrementResult = incrementWord<Side::Left>("a");
			
			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "b");

			incrementResult = incrementWord<Side::Left>("sebastian");

			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "sebastiao");

			incrementResult = incrementWord<Side::Left>("pizazz");

			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "pizbaa");

			incrementResult = incrementWord<Side::Left>("azzzzz");

			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "baaaaa");

			incrementResult = incrementWord<Side::Left>("zzzzzzz");

			TS_ASSERT(!incrementResult);
		}

		void testReverseWordIncrementation(void)
		{
			auto incrementResult = incrementWord<Side::Right>("a");
			
			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "b");

			incrementResult = incrementWord<Side::Right>("nascent");

			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "oascent");

			incrementResult = incrementWord<Side::Right>("zanny");

			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "abnny");

			incrementResult = incrementWord<Side::Right>("zzzzza");

			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "aaaaab");

			incrementResult = incrementWord<Side::Right>("zzzzzzz");

			TS_ASSERT(!incrementResult);
		}
};

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
			auto incrementResult = wordTailBounds<Side::Left>("a");
			
			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "b");

			incrementResult = wordTailBounds<Side::Left>("sebastian");

			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "sebastiao");

			incrementResult = wordTailBounds<Side::Left>("pizazz");

			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "pizbaa");

			incrementResult = wordTailBounds<Side::Left>("azzzzz");

			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "baaaaa");

			incrementResult = wordTailBounds<Side::Left>("zzzzzzz");

			TS_ASSERT(!incrementResult);
		}

		void testReverseWordIncrementation(void)
		{
			auto incrementResult = wordTailBounds<Side::Right>("a");
			
			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "b");

			incrementResult = wordTailBounds<Side::Right>("nascent");

			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "oascent");

			incrementResult = wordTailBounds<Side::Right>("zanny");

			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "abnny");

			incrementResult = wordTailBounds<Side::Right>("zzzzza");

			TS_ASSERT(incrementResult);
			TS_ASSERT_EQUALS(*incrementResult, "aaaaab");

			incrementResult = wordTailBounds<Side::Right>("zzzzzzz");

			TS_ASSERT(!incrementResult);
		}
};

#include <cxxtest/TestSuite.h>

#include <palindrome_tools.h>

class MyTestSuite : public CxxTest::TestSuite
{
	public:

		void testAddition( void )
		{
			TS_ASSERT(isPalindrome("racecar"));
			TS_ASSERT(!isPalindrome("bacecar"));
		}
};

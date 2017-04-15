#ifndef _STRING_SET_
#define _STRING_SET_

#include <string>
#include <set>

class ReverseLess
{

	public:

		bool operator()(const std::string& first, const std::string& second) const;

};

typedef std::set<std::string, std::less<std::string>> ForwardStringSet;
typedef std::set<std::string, ReverseLess> ReverseStringSet;

#endif

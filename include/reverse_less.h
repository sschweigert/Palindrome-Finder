#ifndef _REVERSE_LESS_
#define _REVERSE_LESS_

#include <string>

class ReverseLess
{

	public:

		bool operator()(const std::string& first, const std::string& second) const;

};

#endif

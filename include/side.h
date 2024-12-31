#ifndef _SIDE_
#define _SIDE_

//! \brief Enum which specifies side of palindrome building.
enum class Side 
{

	//! Adding a word to the left side of a sentence
	Left,

	//! Adding a word to the right side of a sentence
	Right

};

constexpr Side opposite(Side side)
{
	return (side == Side::Left) ? Side::Right : Side::Left;
}

inline const char* to_string(Side side)
{
	switch (side)
	{
		case Side::Left:
			return "Left";
		case Side::Right:
			return "Right";
	}
	return "[INVALID]";
}

#endif

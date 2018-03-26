#include "GameWorld.h"

bool has_road(const unsigned char field)
{
	return (field & (1 << ROAD_INDEX_MASK)) > 0;

	// other index:
//	return (field & (ROAD_MASK)) > 0;
	// other way of testing:
//	return (field & ROAD_MASK) == ROAD_MASK;
}


void set_road(unsigned char & field)
{
	field = field | (1 << ROAD_INDEX_MASK);

	// or with different mask, and shorter operator:
//	field |= ROAD_MASK;
}


bool has_treasure(const unsigned char field)
{
	//	actually, C++ takes every value other than 0 as true
	return field & TREASURE_MASK;
}


void remove_treasure(unsigned char & field)
{
	// You have to set to 0, invert MASK and use &
	field &= ~TREASURE_MASK;

	// or, slightly more easy to see what is going on:
	field = field & ~(1 << TREASURE_INDEX_MASK);
}


bool extraction_allowed(const unsigned char field)
{
	// It has to be either sand or stone, and has resource
	return (field & SAND_OR_STONE_MASK) && (field & RESOURCE_MASK);
}


int get_player_ID(unsigned char unit)
{
	// filtering player ID goes with: unit & PLAYER_ID_MASK
	// then shift 4 places: (unit & PLAYER_ID_MASK) >> 4
	// but if you shift the 4 leftmost bits 4 places to the right, 
	// there is no need for a mask:
	return (int)(unit >> 4);
}


void set_player_ID(unsigned char & unit, int playerID)
{
	if (0 <= playerID && playerID < 16)
	{
		// if you don't clear the ID and write a new ID over it, 
		// existing bits will not turn to 0
		// first, clear the old ID: (set them all to 0)
		unit &= ~PLAYER_ID_MASK;

		// second, cast playerID to unsigned char, shift 4 to left and store in unit:
		unit |= (unsigned char)(playerID) << 4;
	}
}



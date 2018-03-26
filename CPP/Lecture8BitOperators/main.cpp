#include "GameWorld.h"
#include <iostream>

using namespace std;


void main()
{
	unsigned char field = 0;
	unsigned char field_with_treasure = (unsigned char)(TREASURE_MASK);
	unsigned char unit = 0;
	unsigned char field_with_everything = 255;

	set_road(field);
	if (has_road(field))
		cout << "This field has a road" << endl;
	else
		cout << "This field does not have a road" << endl;

	if (has_treasure(field_with_treasure))
		cout << "This field has a treasure..." << endl;
	else
		cout << "There is no treasure here, Terance" << endl;
	remove_treasure(field_with_treasure);
	if (has_treasure(field_with_treasure))
		cout << "It is too heavy to lift!" << endl;
	else
		cout << "... and it's gone!" << endl;

	if (extraction_allowed(field_with_everything))
		cout << "We can build a well or a mine here" << endl;
	else
		cout << "You do not have the proper permits" << endl;

	set_player_ID(unit, 13);
	cout << "Player number " << get_player_ID(unit) << endl;

	cin.get();
}
#ifndef GAME_WORLD_HEADER
#define GAME_WORLD_HEADER

// Two ways to define masks, by using the powers of 2 
// or by shifting bits to the desired location. 
// To demonstrate, I'll do both:

// Field byte looks like:
// +---+---+---+---+---+---+---+---+
// | ? | ? | ? | ? | ? | ? | ? | ? |
// +---+---+---+---+---+---+---+---+
//  \_____/  |   |   |   |   |   |
//     |     |   |   |   |   |   +---> unit 
//     |     |   |   |   |   +-------> treasure
//     |     |   |   |   +-----------> extraction (well / mine)
//     |     |   |   +---------------> road
//     |     |   +-------------------> resource (fish / oil / sheep / gold)
//     |     +-----------------------> village
//     +-----------------------------> terrain (water 00 / sand 01 / grass 10 / stone 11)

const int UNIT_MASK = 1;
const int TREASURE_MASK = 2;
const int EXTRACTION_MASK = 4;
const int ROAD_MASK = 8;
const int RESOURCE_MASK = 16;
const int VILLAGE_MASK = 32;
const int TERRAIN_MASK = 128 + 64;
const int SAND_OR_STONE_MASK = 64;

const int UNIT_INDEX_MASK = 0;
const int TREASURE_INDEX_MASK = 1;
const int EXTRACTION_INDEX_MASK = 2;
const int ROAD_INDEX_MASK = 3;
const int RESOURCE_INDEX_MASK = 4;
const int VILLAGE_INDEX_MASK = 5;
const int SAND_OR_STONE_INDEX_MASK = 6;

// Unit byte looks like:
// +---+---+---+---+---+---+---+---+
// | ? | ? | ? | ? | ? | ? | ? | ? |
// +---+---+---+---+---+---+---+---+
//  \_____________/ \_____________/
//         |               |
//         |               +----------> unit type
//         +--------------------------> player ID

const int UNIT_TYPE_MAKS = 8 + 4 + 2 + 1;
const int PLAYER_ID_MASK = 128 + 64 + 32 + 16;

// Here are some examples of working with bit operators.
// I think I have everything covered, but if there is another function
// that you want me to show, please let me know.
bool has_road(const unsigned char field);
void set_road(unsigned char & field);
bool has_treasure(const unsigned char field);
void remove_treasure(unsigned char & field);
bool extraction_allowed(const unsigned char field);
int get_player_ID(unsigned char unit);
void set_player_ID(unsigned char & unit, int playerID);

#endif

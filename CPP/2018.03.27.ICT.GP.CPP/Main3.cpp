#include <iostream>
#include <fstream>

using namespace std;

struct Player
{
	int ID;
	char name[32];
	int strength;
	int magic;
	int dexterity;
	int vitality;
	
	Player() {}
	
	Player(int the_ID, const char the_name[], int the_strength, int the_magic, int the_dexterity, int the_vitality)
	{
		ID = the_ID;
		strcpy_s(name, the_name);
		strength = the_strength;
		magic = the_magic;
		dexterity = the_dexterity;
		vitality = the_vitality;
	}
	
	void print()
	{
		cout << "ID  : " << ID << endl;
		cout << "Name: " << name << endl;
		cout << "STR : " << strength << endl;
		cout << "MAG : " << magic << endl;
		cout << "DEX : " << dexterity << endl;
		cout << "VIT : " << vitality << endl;
	}
};




void main()
{
	Player player1(13, "Kees", 1, 2, 3, 4);
	Player player2;

	char filename[] = "player.struct";

	cout << "Player 1 :" << endl;
	player1.print();

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 3a and 3b test code :                                  *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	//if (open_output_file(out_file, filename))
	//	write_player(out_file, player1);

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 3c and 3d test code :                                  *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	//if (open_input_file(in_file, filename))
	//	player2 = read_player(in_file);

	cout << endl << "Player 2 :" << endl;
	player2.print();
	// output:
	// player2 should be the same as player1

	system("PAUSE");
}
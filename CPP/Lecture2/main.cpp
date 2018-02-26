#include <iostream>
#include <fstream>
#include "Functions.h"

using namespace std;

void simplifyFraction(int& numerator, int& denominator);
bool isPalindrome(char input[]);
void readFile(const char fileName[]);

// 6. Create a struct ‘PlayerState’ with the following attributes:
//		name(type : char[20])
//		level(type : int)
//		health(type : double)
//		experience(type : int)
struct PlayerState
{
	char name[20];
	int level;
	double health;
	int experience;
};

PlayerState createPlayerState(char name[20], int level, double health, int experience);

int main()
{
	// 1. Follow the step-by-step guide to create a library for the functions you made last time.
	cout << Functions::Power(4, 3) << endl;

	// 2. Create a function that gets two integers ‘numerator’ and ‘denominator’
	//    that form a fraction. Alter these integers so that the new fraction is
	//    a simplified version of the first.
	int numerator = 8;
	int denominator = 12;
	cout << numerator << "/" << denominator;
	simplifyFraction(numerator, denominator);
	cout << " simplified: " << numerator << "/" << denominator << endl;

	// 3. Create a two dimensional character array and fill it with several names
	//    of different length. Print the names in a for-loop.
	char names[3][20] = { "Reinier", "Ellen", "Sjonnie" };
	int nameAmount = size(names);
	for (int i = 0; i < nameAmount; i++)
	{
		cout << names[i] << endl;
	}

	// 4. Create a function that gets a c - string as input and checks whether
	//	  it is a palindrome. One can assume the word in the c - string ends with ‘\0’.
	char name[] = "reinier";
	cout << name << " is" << (isPalindrome(name) ? " a" : " no") << " palindrome" << endl;

	// 5. Create a function that reads a txt - file and prints it to the console.
	readFile("text.txt");

	// 7. Create an array with 3 PlayerStates, fill and print them.
	PlayerState playerStates[3];
	playerStates[0] = createPlayerState(names[0], 1337, 20, 100);
	playerStates[1] = createPlayerState(names[1], 1, 2, 3);
	playerStates[2] = createPlayerState(names[2], 3, 2, 1);

	for (int i = 0; i < 3; i++)
	{
		PlayerState p = playerStates[i];
		cout << "PlayerState, name: " << p.name << ", level: " << p.level << ", health: " << p.health << ", exp.: " << p.experience << endl;
	}

	// 8. Save the array with PlayerStates to a binary file with name: “game.dat”.
	ofstream output;
	output.open("game.dat");
	for (int i = 0; i < 3; i++)
	{
		PlayerState p = playerStates[i];
		output.write((char *)&p, sizeof(PlayerState));
	}
	output.close();

	// 9. Load the file: “game.dat” and create a textfile that stores the names from the PlayerStates. 
	ifstream input;
	output.open("names.txt");
	input.open("game.dat", ios::binary);
	if (input)
	{
		PlayerState state;
		input.read((char *)&state, sizeof(state));
		while (!input.eof())
		{
			output << state.name << endl;
			input.read((char *)&state, sizeof(PlayerState));
		}
	}
	else
	{
		cout << "Unable to open file." << endl;
	}

	input.close();
	output.close();

	cin.get();
	return 0;
}

void simplifyFraction(int& numerator, int& denominator)
{
	int gcm = Functions::GreatestCommonDivisor(numerator, denominator);
	numerator /= gcm;
	denominator /= gcm;
}

bool isPalindrome(char input[])
{
	int length = strlen(input);
	for (int i = 0; i < length / 2; i++)
	{
		if (input[i] != input[length - 1 - i])
		{
			return false;
		}
	}

	return true;
}

void readFile(const char fileName[])
{
	char letter;
	ifstream file;
	file.open(fileName);
	if (file)
	{
		letter = file.get();
		while (!file.eof())
		{
			cout << letter;
			letter = file.get();
		}
		file.close();
	}
	else
	{
		cout << "Unable to open file." << endl;
	}
}

PlayerState createPlayerState(char name[20], int level, double health, int experience)
{
	PlayerState p;
	strcpy_s(p.name, name);
	p.level = level;
	p.health = health;
	p.experience = experience;

	return p;
}
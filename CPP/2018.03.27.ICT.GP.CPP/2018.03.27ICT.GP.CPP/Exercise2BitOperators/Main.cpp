#include <iostream>

using namespace std;

const int SPEED_MASK = 128 + 64 + 32;
const int DIRECTION_MASK = 16;
const int ENGINE_ID_MASK = 8 + 4 + 2 + 1;

const int SPEED_INDEX = 5;


bool direction(const unsigned char engine_status)
{
	return (engine_status & DIRECTION_MASK) == DIRECTION_MASK;
}

int speed(const unsigned char engine_status)
{
	return (int)(engine_status >> SPEED_INDEX);
}

void set_engine_id(unsigned char & robot, int id)
{
	if (0 <= id && id <= 3)
	{
		robot &= ~ENGINE_ID_MASK;
		robot |= id << 1;
	}
}

void set_direction(unsigned char & robot)
{
	// Clear the direction bit.
	robot &= ~DIRECTION_MASK;
	robot |= DIRECTION_MASK;
}

void set_speed(unsigned char & robot, int speed)
{
	if (0 <= speed && speed <= 7)
	{
		robot &= ~SPEED_MASK;
		robot |= (unsigned char)(speed) << SPEED_INDEX;
	}
}

unsigned char set_status(int id, bool direction, int speed)
{
	unsigned char robot = 0;

	set_engine_id(robot, id);
	if (direction)
	{
		set_direction(robot);
	}
	set_speed(robot, speed);
	return robot;
}

int main()
{
	int i;
	unsigned char instruction[4] = { unsigned char(98), unsigned char(145), unsigned char(20), unsigned char(168) };

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 2a test code :                                         *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	cout << "exercise 2a:" << endl;

	for (i = 0; i < 4; i++)
		if (direction(instruction[i]))
			cout << "forward" << endl;
		else
			cout << "backward" << endl;
	// output:
	// backward
	// forward
	// forward
	// backward

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 2b test code :                                         *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	cout << endl << "exercise 2b:" << endl;

	for (i = 0; i < 4; i++)
		cout << speed(instruction[i]) << endl;
	// output:
	// 3
	// 4
	// 0
	// 5

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 2c test code :                                         *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	cout << endl << "exercise 2c:" << endl;

	if (set_status(1, false, 3) == (unsigned char(98)))
		cout << "this instruction is set correctly" << endl;
	else
		cout << "ERROR: instruction is NOT correct" << endl;
	if (set_status(0, true, 4) == (unsigned char(144)))
		cout << "this instruction is set correctly" << endl;
	else
		cout << "ERROR: instruction is NOT correct" << endl;
	if (set_status(2, true, 0) == (unsigned char(20)))
		cout << "this instruction is set correctly" << endl;
	else
		cout << "ERROR: instruction is NOT correct" << endl;
	if (set_status(3, false, 5) == (unsigned char(166)))
		cout << "this instruction is set correctly" << endl;
	else
		cout << "ERROR: instruction is NOT correct" << endl;
	// output: it should say 4 times that the instruction is set correctly


	system("PAUSE");
}
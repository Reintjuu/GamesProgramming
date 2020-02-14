#include <iostream>

using namespace std;





void main()
{
	int i;
	unsigned char instruction[4] = { unsigned char(98), unsigned char(145), unsigned char(20), unsigned char(168) };

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 2a test code :                                         *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	cout << "exercise 2a:" << endl;

	//for (i = 0; i < 4; i++)
	//	if (direction(instruction[i]))
	//		cout << "forward" << endl;
	//	else
	//		cout << "backward" << endl;
	//// output:
	//// backward
	//// forward
	//// forward
	//// backward

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 2b test code :                                         *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	cout << endl << "exercise 2b:" << endl;

	//for (i = 0; i < 4; i++)
	//	cout << speed(instruction[i]) << endl;
	//// output:
	//// 3
	//// 4
	//// 0
	//// 5

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 2c test code :                                         *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	cout << endl << "exercise 2c:" << endl;

	//if (set_status(1, false, 3) == (unsigned char(98)))
	//	cout << "this instruction is set correctly" << endl;
	//else
	//	cout << "ERROR: instruction is NOT correct" << endl;
	//if (set_status(0, true, 4) == (unsigned char(145)))
	//	cout << "this instruction is set correctly" << endl;
	//else
	//	cout << "ERROR: instruction is NOT correct" << endl;
	//if (set_status(2, true, 0) == (unsigned char(20)))
	//	cout << "this instruction is set correctly" << endl;
	//else
	//	cout << "ERROR: instruction is NOT correct" << endl;
	//if (set_status(3, false, 5) == (unsigned char(168)))
	//	cout << "this instruction is set correctly" << endl;
	//else
	//	cout << "ERROR: instruction is NOT correct" << endl;
	//// output: it should say 4 times that the instruction is set correctly


	system("PAUSE");
}
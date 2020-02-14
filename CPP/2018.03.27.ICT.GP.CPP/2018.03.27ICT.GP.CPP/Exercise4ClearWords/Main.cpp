#include <iostream>

using namespace std;

bool is_integer(char c)
{
	return ('0' <= c && c <= '9');
}

void clear_string(char * &input)
{
	int inputLength = strlen(input);
	int outputLength = 0;
	for (int i = 0; i < inputLength; i++)
	{
		char c = input[i];
		if (is_integer(c))
		{
			outputLength++;
		}
	}

	char* output = new char[outputLength + 1];
	int outputIndex = 0;
	for (int i = 0; i < inputLength; i++)
	{
		char c = input[i];
		if (is_integer(c))
		{
			output[outputIndex++] = c;
		}
	}
	output[outputIndex] = '\0'; // set the null terminator

	input = output;
}

void main()
{
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 4 test code :                                          *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	cout << "case 1: " << endl;
	char* case1 = new char[6]{ 'a', '3', '4', 'b', '5', '\0' };
	cout << ">" << case1 << "<" << endl; // output: >a34b5<
	clear_string(case1);
	cout << ">" << case1 << "<" << endl; // output: >345<


	cout << endl << "case 2: " << endl;
	char* case2 = new char[4]{ '1', '2', '3', '\0' };
	cout << ">" << case2 << "<" << endl; // output: >123<
	clear_string(case2);
	cout << ">" << case2 << "<" << endl; // output: >123<


	cout << endl << "case 3: " << endl;
	char* case3 = new char[6]{ '5', 'b', '4', '3', 'a', '\0' };
	cout << ">" << case3 << "<" << endl; // output: >5b43a<
	clear_string(case3);
	cout << ">" << case3 << "<" << endl; // output: >543<


	cout << endl << "case 4: " << endl;
	char* case4 = new char[4]{ 'a', 'b', 'c', '\0' };
	cout << ">" << case4 << "<" << endl; // output: >abc<
	clear_string(case4);
	cout << ">" << case4 << "<" << endl; // output: ><

	delete case1;
	delete case2;
	delete case3;
	delete case4;

	system("PAUSE");
}
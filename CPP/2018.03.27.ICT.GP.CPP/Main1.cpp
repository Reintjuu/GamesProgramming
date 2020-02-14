#include <iostream>

using namespace std;


void main()
{
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 1a test code :                                         *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	//Linked_List my_list1;
	//Linked_List my_list2;


	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 1b test code :                                         *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	//my_list1.add(8);
	//my_list1.add(2);
	//my_list1.add(5);
	
	
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 1c test code :                                         *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	cout << "exercise 1c:" << endl;

	//my_list1.print(); // output: 8 -> 2 -> 5
	//my_list2.print(); // output: -

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 1d test code :                                         *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	cout << endl << "exercise 1d:" << endl;

	//my_list1.add(3); // this one is added to create an extra test case
	//my_list1.print(); // output: 8 -> 2 -> 5 -> 3

	//my_list1.remove(5);
	//my_list1.print(); // output: 8 -> 2 -> 3

	//my_list1.remove(8);
	//my_list1.print(); // output: 2 -> 3

	//my_list1.remove(3);
	//my_list1.print(); // output: 2

	//my_list1.remove(2);
	//my_list1.print(); // output: -

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 1e test code :                                         *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	//Hash_Table my_hash_table(7);

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 1f test code :                                         *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	cout << endl << "exercise 1f:" << endl;

	//cout << my_hash_table.hash_value(3) << endl; // output: 3
	//cout << my_hash_table.hash_value(7) << endl; // output: 0
	//cout << my_hash_table.hash_value(8) << endl; // output: 1

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 1g test code :                                         *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	//my_hash_table.add(1);
	//my_hash_table.add(2);
	//my_hash_table.add(3);
	//my_hash_table.add(4);
	//my_hash_table.add(15);
	//my_hash_table.add(41);
	//my_hash_table.add(24);
	//my_hash_table.add(10);


	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	*   Exercise 1h test code :                                         *
	\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	cout << endl << "exercise 1h:" << endl;

	//my_hash_table.print();
	//// output:
	//// 0 : -
	//// 1 : 1 -> 15
	//// 2 : 2
	//// 3 : 3 -> 24 -> 10
	//// 4 : 4
	//// 5 : -
	//// 6 : 41

	system("PAUSE");
}
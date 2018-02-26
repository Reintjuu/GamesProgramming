#include <iostream>
#include <cstdlib>
#include <sec_api/string_s.h>

void lectureThree();

int linearCongruential();

int *shuffle(int n);

using namespace std;


int main()
{
//	cout << "Speler 1, kies een woord: " << endl;
//	string word;
//	cin >> word;
//	auto *legacy = const_cast<char *>(word.c_str());
//
//
//    cout << "Player 2, guess the word: " << endl;
//    for (int i = 0; i < length; i++) {
//        cout << ".";
//    }
//    cout << endl;
//
//	//bool guessed = false;
//	//int i = 0;
//	//while (!guessed) {
//	//i++;
//	//cout << "Guess " << i << ":";
//	char guess[1];
//	cin >> guess;
//	cout << guess << endl;
//	//int guessLength = strlen(guess);
//	//cout << strcmp(guess, word) << endl;
//	//}


	//lectureThree();


//	for (int i = 0; i < 100; ++i)
//	{
//		cout << linearCongruential() << endl;
//
//	}
	cout << *shuffle(5) << endl;
	return 0;
}


void assignmentTwo(int *&p, int n)
{
	p = new int[n];
	for (int i = 0; i < n; i++)
	{
		p[i] = i + 1;
		cout << p[i];
	}

	cout << endl;
}

void lectureThree()
{
	// a, b
	int *p = new int;
	int *q = new int;
	int *r;

	// c
	*p = 2;
	*q = 3;

	// d
	cout << *p << "," << *q << endl;

	// e
	r = q;
	q = p;
	p = r;

	// f
	cout << *p << "," << *q << endl;

	// g
	cout << &p << "," << &q << "," << &r << endl;
	delete p, q, r;
	cout << &p << "," << &q << "," << &r << endl;

	// 2.
	int *five = new int;
	assignmentTwo(five, 5);
}

int linearCongruential()
{
	int a = 221;
	int c = 1;
	int m = 1000;
	static int n = 42;
	n = (a * n + c) % m;
	return n;
}

int *shuffle(int n)
{
	int i, r;
	int a[] = {1,2,3,4};
	for (i = 0; i < n; ++i)
	{
		a[i] = i + 1;
	}

	for (i = n; i > 0; i--)
	{
		r = rand() % i;
		std::swap(&a[r], &a[i]);
		//swap(a[r], a[i]);
	}
	return &a[rand() % n];
}
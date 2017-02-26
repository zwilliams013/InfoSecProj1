#include <iostream>
#include <sstream>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */
#include <bitset>
#include <string>


static const int InitialPerm[64] = {

	58, 50, 42, 34, 26, 18, 10,  2, 60, 52, 44, 36, 28, 20, 12,  4,
	62, 54, 46, 38, 30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 16,  8,
	57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3,
	61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 23, 15,  7

};


static const int PC1[56] = {

	57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4

};

static const int PC2[48] = {

	14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32

};

static const int Shifts[16] = {
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};



static const int Expansion [48] = {

	32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
	8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1

};


int SBoxContents[8][4][16] = {
	{ { 14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7 },
	{ 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8 },
	{ 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0 },
	{ 15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13 }, },

	{ { 15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10 },
	{ 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5 },
	{ 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15 },
	{ 13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9 }, },

	{ { 10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8 },
	{ 13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1 },
	{ 13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7 },
	{ 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12 }, },

	{ { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15 },
	{ 13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9 },
	{ 10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4 },
	{ 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14 }, },

	{ { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9 },
	{ 14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6 },
	{ 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14 },
	{ 11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3 }, },

	{ { 12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11 },
	{ 10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8 },
	{ 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6 },
	{ 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13 }, },

	{ { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1 },
	{ 13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6 },
	{ 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2 },
	{ 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12 }, },

	{ { 13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7 },
	{ 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2 },
	{ 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8 },
	{ 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11 }, },

};


//Bit shifting schedule
static int shiftAmount[] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };



using namespace std;

int main() {

	int i;

	//Get meesage string
	string num = "5b8ec873bf43a652";

	//Convert data from hexadecimal to binary 
	string myString = "5b8ec873bf43a652";
	string binMessage;
	for (uint64_t i = 0; i < myString.size(); ++i)
	{
		bitset<4> b(myString.c_str()[i]);
		binMessage += b.to_string();
	}


	cout << binMessage << endl;

	for (int i = 0; i < binMessage.length(); ++i) {


		if (i % 4 == 0 && i != 0) {
			cout << " ";
		}
		cout << binMessage[i];

	}

	cout << '\n' << binMessage.length() << endl;


	//1. Split message into left and right half

	const int space = binMessage.length() / 2;
	string left;
	string right;
	//cout << binMessage.length() / 2;

	//Fill left side
	for (i = 0; i < binMessage.length() / 2; i++) {
		left += binMessage[i];
	}

	//Print left side DELETE WHEN DONE								@@@@@@@@@@@@@@@@@@@@@@@@@
	for (i = 0; i < binMessage.length() / 2; i++) {

		if (i % 4 == 0 && i != 0) {
			cout << " ";
		}
		cout << left[i];
	}

	//Fill right side
	cout << "\n\n Right " << endl;
	for (i < binMessage.length() / 2; i < binMessage.length(); i++) {
		right += binMessage[i];
	}

	//Printing right side of message   DELETE WHEN DONE         @@@@@@@@@@@@@@@@@@@@@@@@@@@
	cout << " ";
	for (i = 0; i < binMessage.length() / 2; i++) {

		if (i % 4 == 0 && i != 0) {
			cout << " ";
		}
		cout << right[i];
	}
	cout << " ";


	//2. Initial Permutation
	string initialPerm;

	//cout << '\n' << InitialPerm[63] << endl;
	//cout << "Printing a " << binMessage[InitialPerm[8]] << endl;


	for (i = 0; i < binMessage.length(); i++) {
		initialPerm += binMessage[InitialPerm[i]];
	}

	cout << "\n Printing out Initial Permd message:" << endl;
	for (i = 0; i < binMessage.length(); i++) {
		if (i % 4 == 0 && i != 0) {						//used to separate bits into blocks of 4
			cout << " ";
		}
		cout << initialPerm[i];

	}



	//3. Key convert
	string word = "eb57c5e9bf1d";
	string key;
	for (uint64_t i = 0; i < word.size(); ++i)
	{
		bitset<4> b(word.c_str()[i]);
		key += b.to_string();
	}
	cout << endl;
	cout << "KEY" << endl;
	for (i = 0; i < key.length(); i++) {
		if (i % 4 == 0 && i != 0) {						//used to separate bits into blocks of 4
			cout << " ";
		}
		cout << key[i];

	}


	//4. Right side expansion
	string expansion;
	//cout << "\n\n Right" << right << endl;



	//Printing right side of message   DELETE WHEN DONE         @@@@@@@@@@@@@@@@@@@@@@@@@@@
	cout << "\nRight side" << endl;
	for (i = 0; i < binMessage.length() / 2; i++) {

		if (i % 4 == 0 && i != 0) {
			cout << " ";
		}
		cout << right[i];
	}
	//cout << " ";

	for (i = 1; i < (sizeof(Expansion) / sizeof(*Expansion)); ++i) {
		//expansion += 'a'
		if (i != 0) {
			expansion += right[Expansion[i]];															//Check on this 

		}
		else {
			expansion += right[Expansion[i-1]];
		}

		//cout << "expansion at i: " << right[Expansion[i]] << " ";
	}



	cout << "\nexpansion " << (sizeof(Expansion) / sizeof(*Expansion)) << endl;

	for (i = 0; i < (sizeof(Expansion) / sizeof(*Expansion)); i++) {
		if (i % 4 == 0 && i != 0) {
			cout << " ";
		}
		cout << expansion[i];
	}
	cout << "\n\n\n\asdsa" << expansion;




	//5. Xor key with expanded right
	cout << "\nExpanded Right\n" << expansion << endl;
	cout << "\n\nKey\n" << key << endl;

	int keyXorRight[48];
	int a[1] = { 1 };
	int b[1] = { 0 };

	//cout << a[1] ^ b[1];

	//Xor operation
	for (i = 0; i < expansion.length(); i++) {
		if (key[i] != expansion[i])
			keyXorRight[i] = 1;
		else {
			keyXorRight[i] = 0;
		}
	}
	

}

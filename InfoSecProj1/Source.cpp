#include <iostream>
#include <sstream>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */
#include <bitset>
#include <string>
#include <vector>

using namespace std;

int stringToInt(string num) {
	
	int result = 0;
	for (int i = 0; i < num.length(); i++) {
			result *= 2;
			if (num[i] == '1') {
				result += 1;
			}
	
	}
	return result;
}

void ConvertToBinary(int n) {
	if (n / 2 != 0) {
		ConvertToBinary(n / 2);
	}
	printf("%d", n % 2);
}

string dec2bin(unsigned n)
{
	string res;
	/*
	while (n){
		res.push_back((n & 1) + '0');
		n >>= 1;
	}

	if (res.empty())
		res = "0";
	else
		reverse(res.begin(), res.end());
		*/
	for (int i = 0; i < 4; i++) {
		if (n % 2 == 0)
			res.append("0");
		else
			res.append("1");
		n /= 2;
	}
	reverse(res.begin(), res.end());
	return res;
}

string GetBinaryStringFromHexString(string sHex)
{
	string stringReturn = "";
	for (int i = 0; i < sHex.length(); ++i)
	{
		switch (sHex[i])
		{
		case '0': stringReturn.append("0000"); break;
		case '1': stringReturn.append("0001"); break;
		case '2': stringReturn.append("0010"); break;
		case '3': stringReturn.append("0011"); break;
		case '4': stringReturn.append("0100"); break;
		case '5': stringReturn.append("0101"); break;
		case '6': stringReturn.append("0110"); break;
		case '7': stringReturn.append("0111"); break;
		case '8': stringReturn.append("1000"); break;
		case '9': stringReturn.append("1001"); break;
		case 'a': stringReturn.append("1010"); break;
		case 'b': stringReturn.append("1011"); break;
		case 'c': stringReturn.append("1100"); break;
		case 'd': stringReturn.append("1101"); break;
		case 'e': stringReturn.append("1110"); break;
		case 'f': stringReturn.append("1111"); break;
		}
	}
	return stringReturn;
}

void printString(std::string s) {
	int i;
	std::cout << "\nUsed print funct" << std::endl;
	for (i = 0; i < s.length(); i++) {
		if (i % 8 == 0 && i != 0) {						//used to separate bits into blocks of 4
			std::cout << " ";
		}
		std::cout << s[i];
	}
	std::cout << std::endl;
}


static const int InitialPerm[64] = {

	58, 50, 42, 34, 26, 18, 10,  2, 60, 52, 44, 36, 28, 20, 12,  4,
	62, 54, 46, 38, 30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 16,  8,
	57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3,
	61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 23, 15,  7

};



static const int Expansion [48] = {

	32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
	8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1

};

static const int P[32] = {
	16,	7,	20,	21,	29,	12,	28, 17,
	1,	15,	23,	26,	5,	18, 31,	10,
	2,	8,	24,	14,	32,	27,	3,	9,
	19,	13,	30,	6,	22,	11,	4,	25
};

static const int IP[64] = {
	40,	8,	48,	16,	56,	24,	64,	32,
	39,	7,	47,	15,	55,	23,	63,	31,
	38,	6,	46,	14,	54,	22,	62,	30,
	37,	5,	45,	13,	53,	21,	61,	29,
	36,	4,	44,	12,	52,	20,	60,	28,
	35,	3,	43,	11,	51,	19,	59,	27,
	34,	2,	42,	10,	50,	18,	58,	26,
	33,	1,	41,	9,	49,	17,	57,	25
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



int main() {

	int i;

	//Get meesage string
	string num = "0123456789abcdef";
	string bum;
	//Convert data from hexadecimal to binary 
	string myString = "5b8ec873bf43a652";

	string binMessage;
	binMessage = GetBinaryStringFromHexString(num);
	bum = GetBinaryStringFromHexString(num);

	cout << "Print message" << endl;
	cout << binMessage << endl;

	for (int i = 0; i < binMessage.length(); ++i) {
		if (i % 4 == 0 && i != 0) {
			cout << " ";
		}
		cout << binMessage[i];

	}

	//1. Split message into left and right half
	string left;
	string right;

	//2. Initial Permutation
	string initialPerm = GetBinaryStringFromHexString(num);

/*
	for (i = 0; i < binMessage.length() ; i++) {
		initialPerm += binMessage[InitialPerm[i]-1];

	}

	cout << "\nPrinting out Initial Permd message:" << endl;
	for (i = 0; i < initialPerm.length(); i++) {
		if (i % 4 == 0 && i != 0) {						//used to separate bits into blocks of 4
			cout << " ";
		}
		cout << initialPerm[i];

	}
	*/
	cout << endl;
	//Fill left side
	for (i = 0; i < initialPerm.length() / 2; i++) {
		left += initialPerm[i];
	}

	//Print left side DELETE WHEN DONE								@@@@@@@@@@@@@@@@@@@@@@@@@
	cout << "\nLeft" << endl;
	for (i = 0; i < left.length(); i++) {

		if (i % 4 == 0 && i != 0) {
			cout << " ";
		}
		cout << left[i];
	}
	cout << endl;

	//Fill right side
	cout << "\nRight " << endl;
	for (i = initialPerm.length() / 2; i < initialPerm.length(); i++) {
		right += initialPerm[i];
	}

	//Printing right side of message   DELETE WHEN DONE         @@@@@@@@@@@@@@@@@@@@@@@@@@@
	for (i = 0; i < right.length(); i++) {

		if (i % 4 == 0 && i != 0) {
			cout << " ";
		}
		cout << right[i];
	}
	cout << " ";
	cout << endl;

	
	//3. Key convert
	string old = "eb57c5e9bf1d";
	//string word = "F0CCAAF556678F";
	string word = "1b02effc7072";
	string key;
	
	cout << word;
	key = GetBinaryStringFromHexString(word);
	cout << endl;

	cout << "\nKey" << endl;
	cout << key << endl;
	for (i = 0; i < key.length(); i++) {
		if (i % 6 == 0 && i != 0) {						//used to separate bits into blocks of 4
			cout << " ";
		}
		cout << key[i];

	}
	cout << '\n' << endl;

	//4. Right side expansion
	string expansion;
	for (i = 0; i < (sizeof(Expansion) / sizeof(*Expansion)); ++i) {
		expansion += right[Expansion[i] - 1];															//Works
	}

	cout << "\nExpanded Right" << expansion.length() << " \n" << expansion << endl;
	for (i = 0; i < (sizeof(Expansion) / sizeof(*Expansion)); i++) {
		if (i % 6 == 0 && i != 0) {
			cout << " ";
		}
		cout << expansion[i];
	}


	//5. Xor key with expanded right
	string keyXorRight;

	//Xor operation
	for (i = 0; i < expansion.length(); i++) {
		if (key[i] != expansion[i])
			keyXorRight += '1';
		else {
			keyXorRight += '0';
		}
	}
	cout << "\n\nXor"<< endl;
	cout << keyXorRight<< endl;
	for (i = 0; i < keyXorRight.length(); i++) {
		if (i % 6 == 0 && i != 0) {
			cout << " ";
		}
		cout << keyXorRight[i];
	}

	//6. Substitution split xord key into 8 blocks of 6 then use S table to sub with 4 numbers
	//printString(keyXorRight);
	string s1, s2, s3, s4,s5,s6,s7, s8;
	string se1, se2, se3, se4, se5, se6, se7, se8;
	string sm1, sm2, sm3, sm4, sm5, sm6, sm7, sm8;

	

	for (i = 0; i < 6; i++) {
		s1 += keyXorRight[i];
		s2 += keyXorRight[i + 6];
		s3 += keyXorRight[i + 12];
		s4 += keyXorRight[i + 18];
		s5 += keyXorRight[i + 24];
		s6 += keyXorRight[i + 30];
		s7 += keyXorRight[i + 36];
		s8 += keyXorRight[i + 42];
	}
	for (i = 0; i < 2; i++) {
		se1 += s1[i * 5];
		se2 += s2[i * 5];
		se3 += s3[i * 5];
		se4 += s4[i * 5];
		se5 += s5[i * 5];
		se6 += s6[i * 5];
		se7 += s7[i * 5];
		se8 += s8[i * 5];
	}
	for (i = 1; i < 5; i++) {
		sm1 += s1[i];
		sm2 += s2[i];
		sm3 += s3[i];
		sm4 += s4[i];
		sm5 += s5[i];
		sm6 += s6[i];
		sm7 += s7[i];
		sm8 += s8[i];
	}

	cout << endl;
	/*	
	cout << "\n" << stringToInt(s1);
	cout << " " << stringToInt(s2);
	cout << " " << stringToInt(s3);
	cout << " " << stringToInt(s4);
	cout << " " << stringToInt(s5);
	cout << " " << stringToInt(s6);
	cout << " " << stringToInt(s7);
	cout << " " << stringToInt(s8) << endl;*/

	cout << " " << stringToInt(se1);
	cout << " " << stringToInt(se2);
	cout << " " << stringToInt(se3);
	cout << " " << stringToInt(se4);
	cout << " " << stringToInt(se5);
	cout << " " << stringToInt(se6);
	cout << " " << stringToInt(se7);
	cout << " " << stringToInt(se8);
	cout << endl;

	cout << " " << stringToInt(sm1);
	cout << " " << stringToInt(sm2);
	cout << " " << stringToInt(sm3);
	cout << " " << stringToInt(sm4);
	cout << " " << stringToInt(sm5);
	cout << " " << stringToInt(sm6);
	cout << " " << stringToInt(sm7);
	cout << " " << stringToInt(sm8);
	cout << endl;

	

	//string sub1 = dec2bin(SBoxContents[0][0][12]);
	string sub1 = dec2bin(SBoxContents[0][stringToInt(se1)][stringToInt(sm1)]);
	string sub2 = dec2bin(SBoxContents[1][stringToInt(se2)][stringToInt(sm2)]);
	string sub3 = dec2bin(SBoxContents[2][stringToInt(se3)][stringToInt(sm3)]);
	string sub4 = dec2bin(SBoxContents[3][stringToInt(se4)][stringToInt(sm4)]);
	string sub5 = dec2bin(SBoxContents[4][stringToInt(se5)][stringToInt(sm5)]);
	string sub6 = dec2bin(SBoxContents[5][stringToInt(se6)][stringToInt(sm6)]);
	string sub7 = dec2bin(SBoxContents[6][stringToInt(se7)][stringToInt(sm7)]);
	string sub8 = dec2bin(SBoxContents[7][stringToInt(se8)][stringToInt(sm8)]);

	cout << "sube " << sub1 << endl;

	string fullsub = sub1 + sub2 + sub3 +sub4 + sub5 + sub6 + sub7 + sub8;

	printString(fullsub);
	cout << endl;


	// P Permutation
	string pPerm;
	for (i = 0; i < fullsub.length(); i++) {
		pPerm += fullsub[P[i] - 1];
	}

	printString(pPerm);



	string rswap;
	//Second Xor operation with left + perm
	for (i = 0; i < pPerm.length(); i++) {
		if (left[i] != pPerm[i])
			rswap += '1';
		else {
			rswap += '0';
		}
	}
	cout << "\n\nXor" << endl;
	cout << rswap << endl;
	for (i = 0; i < rswap.length(); i++) {
		if (i % 4 == 0 && i != 0) {
			cout << " ";
		}
		cout << rswap[i];
	}
	cout << endl;

	//swap left with right
	left = right;

	string complete; 
	//complete =  left + rswap;
	complete =  rswap + left;
	cout << "\n" << complete << endl;
	printString(complete);
	cout << endl;

	//reverse(complete.begin(), complete.end());

	cout << complete << " before inverse" <<  endl;


	
	//Inverse PErmutation
	string inverse;
	for (i = 0; i < complete.length(); i++) {
		inverse += complete[IP[i] - 1];
	}
	cout << inverse << " inverse" << endl;
	
	//reverse(inverse.begin(), inverse.end());


	string asdf = "1011111101000011101001100101001010000111101010001101000010011100";
	cout << asdf << " Correct" << endl;

	
	if (complete == asdf || inverse == asdf) {
		cout << "\n ********************Youre done" << endl;
	}
	
}

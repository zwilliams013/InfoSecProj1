#include <iostream>
#include <sstream>
#include <stdio.h>     
#include <string>

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
string GetHexFromBin(string sBinary)
{
	string hexStr(""), tmp, chr = "0000";
	int len = sBinary.length() / 4;
	chr = chr.substr(0, len);
	sBinary = chr + sBinary;
	for (int i = 0; i<sBinary.length(); i += 4)
	{
		tmp = sBinary.substr(i, 4);
		 if (!tmp.compare("0001"))
		{
			hexStr = hexStr + "1";
		}
		else if (!tmp.compare("0010"))
		{
			hexStr = hexStr + "2";
		}
		else if (!tmp.compare("0011"))
		{
			hexStr = hexStr + "3";
		}
		else if (!tmp.compare("0100"))
		{
			hexStr = hexStr + "4";
		}
		else if (!tmp.compare("0101"))
		{
			hexStr = hexStr + "5";
		}
		else if (!tmp.compare("0110"))
		{
			hexStr = hexStr + "6";
		}
		else if (!tmp.compare("0111"))
		{
			hexStr = hexStr + "7";
		}
		else if (!tmp.compare("1000"))
		{
			hexStr = hexStr + "8";
		}
		else if (!tmp.compare("1001"))
		{
			hexStr = hexStr + "9";
		}
		else if (!tmp.compare("1010"))
		{
			hexStr = hexStr + "A";
		}
		else if (!tmp.compare("1011"))
		{
			hexStr = hexStr + "B";
		}
		else if (!tmp.compare("1100"))
		{
			hexStr = hexStr + "C";
		}
		else if (!tmp.compare("1101"))
		{
			hexStr = hexStr + "D";
		}
		else if (!tmp.compare("1110"))
		{
			hexStr = hexStr + "E";
		}
		else if (!tmp.compare("1111"))
		{
			hexStr = hexStr + "F";
		}
		else
		{
			continue;
		}
	}
	return hexStr;
}

string dec2bin(unsigned n)
{
	string res;
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
	for (i = 0; i < s.length(); i++) {
		if (i % 4 == 0 && i != 0) {						//used to separate bits into blocks of 4
			cout << " ";
		}
		cout << s[i];
	}
	cout << endl;
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


int main() {

	int i;

	string binMessage;
	cout << "Enter 64 bit input: ";
	cin >> binMessage;
	
	binMessage = GetBinaryStringFromHexString(binMessage);
	
	//1. Split message into left and right half
	string left;
	string right;

	//Fill left side
	for (i = 0; i < binMessage.length() / 2; i++) {
		left += binMessage[i];
	}

	//Fill right side
	for (i = binMessage.length() / 2; i < binMessage.length(); i++) {
		right += binMessage[i];
	}

	//3. Key convert
	string key;
	cout << "Enter 48 bit key: ";
	cin >> key;
	key = GetBinaryStringFromHexString(key);
	
	//4. Right side expansion using table
	string expansion;
	for (i = 0; i < (sizeof(Expansion) / sizeof(*Expansion)); ++i) {
		expansion += right[Expansion[i] - 1];														
	}

	//5. Xor key with expanded right
	string keyXorRight;

	//Xor operation
	for (i = 0; i < expansion.length(); i++) {
		if (expansion[i] != key[i])
			keyXorRight += '1';
		else {
			keyXorRight += '0';
		}
	}

	//6. Substitution split xord key into 8 blocks of 6 then use S table to sub with 4 numbers
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
	//get end tails of xord output for s table lookup
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
	//get middle of xord output for s table lookup
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
	//get s table values
	int sub1 = (SBoxContents[0][stringToInt(se1)][stringToInt(sm1)]);
	int sub2 = (SBoxContents[1][stringToInt(se2)][stringToInt(sm2)]);
	int sub3 = (SBoxContents[2][stringToInt(se3)][stringToInt(sm3)]);
	int sub4 = (SBoxContents[3][stringToInt(se4)][stringToInt(sm4)]);
	int sub5 = (SBoxContents[4][stringToInt(se5)][stringToInt(sm5)]);
	int sub6 = (SBoxContents[5][stringToInt(se6)][stringToInt(sm6)]);
	int sub7 = (SBoxContents[6][stringToInt(se7)][stringToInt(sm7)]);
	int sub8 = (SBoxContents[7][stringToInt(se8)][stringToInt(sm8)]);
	
	//add binary values of s tables to a string 
	string fullsub;
	fullsub += dec2bin(sub1);
	fullsub += dec2bin(sub2);
	fullsub += dec2bin(sub3);
	fullsub += dec2bin(sub4);
	fullsub += dec2bin(sub5);
	fullsub += dec2bin(sub6);
	fullsub += dec2bin(sub7);
	fullsub += dec2bin(sub8);

	// P Permutation
	string pPerm;
	for (i = 0; i < fullsub.length(); i++) {
		pPerm += fullsub[P[i] - 1];
	}

	string rswap;
	//Second Xor operation with left + perm
	for (i = 0; i < pPerm.length(); i++) {
		if (left[i] != pPerm[i])
			rswap += '1';
		else {
			rswap += '0';
		}
	}

	//swap left with right
	left = right;

	string complete; 
	//join left and right back to 64 bits
	complete = left + rswap;
	
	//print output
	cout << "Complete" << endl;
	cout << GetHexFromBin(complete);
}

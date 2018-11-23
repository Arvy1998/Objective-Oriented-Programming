#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

unsigned char symbUnsignedChar;
unsigned int symbDec, n;

struct CP437 {
	int CP437DecimalValues[49] = {176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208,
										 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 254};
	string CP437HexadecimalValues[49] = {"2591", "2592", "2593", "2502", "2524", "2561", "2562", "2556", "2555", "2563", "2551", "2557", "255D", "255C", "255B", "2510", "2514", "2534", "252C", "251C", "2500",
									   "253C", "255E", "255F", "255A", "2554", "2596", "2566", "2560", "2550", "256C", "2567", "2568", "2564", "2565", "2559", "2558", "2552", "2553", "256B", "256A", "2518",
									   "250C", "2588", "2584", "258C", "2590", "2580", "25A0"};
	unsigned char CP437Characters[49] = { unsigned char(176), unsigned char(177), unsigned char(178), unsigned char(179), unsigned char(180), unsigned char(181), unsigned char(182), unsigned char(183), unsigned char(184), unsigned char(185), unsigned char(186), unsigned char(187), unsigned char(188), unsigned char(189), unsigned char(190),
		unsigned char(191), unsigned char(192), unsigned char(193), unsigned char(194), unsigned char(195), unsigned char(196), unsigned char(197), unsigned char(198), unsigned char(199), unsigned char(200), unsigned char(201), unsigned char(202), unsigned char(203), unsigned char(204), unsigned char(205),
		unsigned char(206), unsigned char(207), unsigned char(208), unsigned char(209), unsigned char(210), unsigned char(211), unsigned char(212), unsigned char(213), unsigned char(214), unsigned char(215), unsigned char(216), unsigned char(217), unsigned char(218), unsigned char(219), unsigned char(220),
		unsigned char(221), unsigned char(222), unsigned char(223), unsigned char(254) };
} CP437_;

class Unikodas {
public:
	int decimalValue;
	string binaryValue;
	string hexadecimalValue;
	string binaryToHexadecimal(string x);
	string decimalToBinary(int x);
	string decToUTF8(int x);
};

string Unikodas::binaryToHexadecimal(string x) {
	int position = 0;
	hexadecimalValue = "00";
	for (auto i = 0; i < 8; i += 4) {
		if (x[i] == '0' && x[i + 1] == '0' && x[i + 2] == '0' && x[i + 3] == '0') { // 0000
			hexadecimalValue[position] = '0';
			position++;
		}
		else if (x[i] == '0' && x[i + 1] == '0' && x[i + 2] == '0' && x[i + 3] == '1') { // 0001
			hexadecimalValue[position] = '1';
			position++;
		}
		else if (x[i] == '0' && x[i + 1] == '0' && x[i + 2] == '1' && x[i + 3] == '0') { // 0010
			hexadecimalValue[position] = '2';
			position++;
		}
		else if (x[i] == '0' && x[i + 1] == '0' && x[i + 2] == '1' && x[i + 3] == '1') { // 0011
			hexadecimalValue[position] = '3';
			position++;
		}
		else if (x[i] == '0' && x[i + 1] == '1' && x[i + 2] == '0' && x[i + 3] == '0') { //0100
			hexadecimalValue[position] = '4';
			position++;
		}
		else if (x[i] == '0' && x[i + 1] == '1' && x[i + 2] == '0' && x[i + 3] == '1') { // 0101
			hexadecimalValue[position] = '5';
			position++;
		}
		else if (x[i] == '0' && x[i + 1] == '1' && x[i + 2] == '1' && x[i + 3] == '0') { // 0110
			hexadecimalValue[position] = '6';
			position++;
		}
		else if (x[i] == '0' && x[i + 1] == '1' && x[i + 2] == '1' && x[i + 3] == '1') { // 0111
			hexadecimalValue[position] = '7';
			position++;
		}
		else if (x[i] == '1' && x[i + 1] == '0' && x[i + 2] == '0' && x[i + 3] == '0') { // 1000
			hexadecimalValue[position] = '8';
			position++;
		}
		else if (x[i] == '1' && x[i + 1] == '0' && x[i + 2] == '0' && x[i + 3] == '1') { // 1001
			hexadecimalValue[position] = '9';
			position++;
		}
		else if (x[i] == '1' && x[i + 1] == '0' && x[i + 2] == '1' && x[i + 3] == '0') { // 1010
			hexadecimalValue[position] = 'A';
			position++;
		}
		else if (x[i] == '1' && x[i + 1] == '0' && x[i + 2] == '1' && x[i + 3] == '1') { // 1011
			hexadecimalValue[position] = 'B';
			position++;
		}
		else if (x[i] == '1' && x[i + 1] == '1' && x[i + 2] == '0' && x[i + 3] == '0') { // 1100
			hexadecimalValue[position] = 'C';
			position++;
		}
		else if (x[i] == '1' && x[i + 1] == '1' && x[i + 2] == '0' && x[i + 3] == '1') { // 1101
			hexadecimalValue[position] = 'D';
			position++;
		}
		else if (x[i] == '1' && x[i + 1] == '1' && x[i + 2] == '1' && x[i + 3] == '0') { // 1110
			hexadecimalValue[position] = 'E';
			position++;
		}
		else { // 1111
			hexadecimalValue[position] = 'F';
			position++;
		}
	}
	return hexadecimalValue;
}

string Unikodas::decimalToBinary(int x) {
	int temp, i = 0;
	binaryValue = "";
	decimalValue = x;
	if (x == 0) {
		binaryValue = "000000000000000000000";
	}
	else if (x == 1) {
		binaryValue = "000000000000000000001";
	}
	else {
		while (x != 0) {
			temp = x % 2;
			if (temp == 0) {
				binaryValue.append("0");
			}
			else if (temp == 1) {
				binaryValue.append("1");
			}
			x = x / 2;
			i++;
		}
		if (binaryValue.length() < 22) {
			for (auto i = binaryValue.length(); i < 22; i++) {
				binaryValue.append("0");
			}
		}
		reverse(binaryValue.begin(), binaryValue.end());
	}
	return binaryValue;
}

string Unikodas::decToUTF8(int x) {
	if (x >= 0 && x <= 127) {
		n = 2;
		string byte1 = "00000000";
		int counter = 0;
		decimalToBinary(x);
		for (auto i = 7; i > 0; i--) {
			byte1[i] = binaryValue[binaryValue.length() - 1 - counter];
			counter++;
		}
		hexadecimalValue = binaryToHexadecimal(byte1);
	}
	else if (x >= 128 && x <= 2047) {
		n = 4;
		string byte1 = "11000000", byte2 = "10000000", temp1, temp2;
		int counter = 0;
		decimalToBinary(x);
		for (auto i = 7; i > 1; i--) {
			byte2[i] = binaryValue[binaryValue.length() - 1 - counter];
			counter++;
		}
		for (auto i = 7; i > 2; i--) {
			byte1[i] = binaryValue[binaryValue.length() - 1 - counter];
			counter++;
		}
		temp1 = binaryToHexadecimal(byte1);
		temp2 = binaryToHexadecimal(byte2);
		hexadecimalValue = temp1 + temp2;
	}
	else if (x >= 2048 && x <= 65535) {
		n = 6;
		string byte1 = "11100000", byte2 = "10000000", byte3 = "10000000", temp1, temp2, temp3;
		int counter = 0;
		decimalToBinary(x);
		for (auto i = 7; i > 1; i--) {
			byte3[i] = binaryValue[binaryValue.length() - 1 - counter];
			counter++;
		}
		for (auto i = 7; i > 1; i--) {
			byte2[i] = binaryValue[binaryValue.length() - 1 - counter];
			counter++;
		}
		for (auto i = 7; i > 3; i--) {
			byte1[i] = binaryValue[binaryValue.length() - 1 - counter];
			counter++;
		}
		temp1 = binaryToHexadecimal(byte1);
		temp2 = binaryToHexadecimal(byte2);
		temp3 = binaryToHexadecimal(byte3);
		hexadecimalValue = temp1 + temp2 + temp3;
	}
	else if (x >= 65536 && x <= 1114111) {
		n = 8;
		string byte1 = "11110000", byte2 = "10000000", byte3 = "10000000", byte4 = "10000000", temp1, temp2, temp3, temp4;
		decimalToBinary(x);
		int counter = 0;
		for (auto i = 7; i > 1; i--) {
			byte4[i] = binaryValue[binaryValue.length() - 1 - counter];
			counter++;
		}
		for (auto i = 7; i > 1; i--) {
			byte3[i] = binaryValue[binaryValue.length() - 1 - counter];
			counter++;
		}
		for (auto i = 7; i > 1; i--) {
			byte2[i] = binaryValue[binaryValue.length() - 1 - counter];
			counter++;
		}
		for (auto i = 7; i > 4; i--) {
			byte1[i] = binaryValue[binaryValue.length() - 1 - counter];
			counter++;
		}
		temp1 = binaryToHexadecimal(byte1);
		temp2 = binaryToHexadecimal(byte2);
		temp3 = binaryToHexadecimal(byte3);
		temp4 = binaryToHexadecimal(byte4);
		hexadecimalValue = temp1 + temp2 + temp3 + temp4;
	}
	else {
		cout << "Ivesta per didele desimtaine reiksme..." << endl;
		exit(0);
	}
	return hexadecimalValue;
}

int main()
{
	char Symbol;
	vector <unsigned char> charArray = {};
	string x;
	int choose;
	Unikodas utf_8_encoder;
	cout << "1) Ivesti simbolio unikoda ir pamatyti jo utf-8..." << endl;
	cout << "2) Apdoroti 386intel.txt faila..." << endl;
	cin >> choose;
	switch (choose) {
	case 1: {
		cout << "Iveskite desimtaini simbolio koda, kurio utf-8 norite pamatyti: " << endl;
		cin >> symbDec;
		cout << "UTF8: " << utf_8_encoder.decToUTF8(symbDec) << endl;
		cout << "UNICODE: U+" << hex << symbDec;
		system("PAUSE");
		break;
	}
	case 2: {
		unsigned char BOM[] = { 0xEF, 0xBB, 0xBF };
		ifstream textFile("386intel.txt");
		ofstream outputFile("386intelOutput.txt", ios_base::binary);
		outputFile.clear();
		outputFile.write((char*)BOM, sizeof(BOM));
		while (!textFile.eof()) {
			textFile.get(Symbol);
			symbUnsignedChar = static_cast<unsigned char> (Symbol);
			symbDec = symbUnsignedChar;
			for (auto y = 0; y < 48; y++) {
				if (symbDec == CP437_.CP437DecimalValues[y]) {
					char temp[5];
					strcpy_s(temp, CP437_.CP437HexadecimalValues[y].c_str());
					symbDec = strtoul(temp, 0, 16);
				}
			}
			x = utf_8_encoder.decToUTF8(symbDec);
			vector <unsigned char> values;
			unsigned int utf8value;
			int position = 0;
			for (size_t i = 0; i < x.size() / 2; i++) {
				stringstream stringStream;
				stringStream << hex << x.substr(position, 2);
				position = position + 2;
				stringStream >> utf8value;
				values.push_back(utf8value);
			}
			outputFile.write((const char*)&values.at(0), values.size() * sizeof(values[0]));
			cout << Symbol;
		}
		outputFile.close();
		textFile.close();
		system("PAUSE");
		break;
	}
	default: {
		cout << "Toks pasirinkimas nenumatytas..." << endl;
		break;
		}
	}
    return 0;
}

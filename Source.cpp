/******************************************************************
BitString Project
Matthew Friemoth
CS-441 Computer Architecture
This source file uses C++ to explicitly show how booth's theorem is implemented for binary numbers.
*******************************************************************/



#include<iostream>
#include"BitString.h";

using namespace std;

int main() {


	/*
		Input Variables
	*/
	int int_bits = 0;
	int int_multiplacand;
	int int_multiplier;

	do {
		cout << "Bits:";
		cin >> int_bits;
	} while (int_bits <= 0);
	cout << "Multipacand:";
	cin >> int_multiplacand;
	cout << "Multiplier:";
	cin >> int_multiplier;


	/*
		User Input
	*/
	/*
	while (multiplacand.length() == 0) {
		cout << "Multipacand: ";
		cin >> multiplacand;
	}
	while (multiplacand.length() != multiplier.length()) {
		cout << "Multiplier:  ";
		cin >> multiplier;
	}
	*/
	/*
		Conversions into bitstring
	*/

	BitString bit1 = BitString(int_bits, int_multiplacand);
	BitString bit2 = BitString(int_bits, int_multiplier);

	int bitLength = bit1.getNumBits();

	BitString NegBit1 = BitString(bit1.toString());
	NegBit1.negate();	//This is for subtraction

	//Display bits and decimals to user
	bit1.print(1);
	bit2.print(1);


	//Initialize
	string A = "";
	for (int i = 0; i < bitLength; i++) {
		A = A + '0';
	}
	BitString product = BitString(A + bit2.toString() + "0");
	int numProductBits = product.getNumBits();


	//Display inital multiplacand and product to user
	cout << "| 0 | Initialize   | " << bit1.toString() << " | " << product.toString() << " |" << endl;


	/*
		Booth's Multiplacation
	*/
	for (int i = 1; i <= bitLength; i++) {		//Loop the amount of time as there are bits
		if (product[numProductBits - 2]) {		//Check second to last bit
			if (product[numProductBits - 1]) {	//Check last bit
				//NO OP
				cout << "| " << i << " | NO OPERATION | " << bit1.toString() << " | " << product.toString() << " |" << endl;
			} else {
				//A = A - M
				product.primeAdd(NegBit1);
				cout << "| " << i << " | A = A - M    | " << bit1.toString() << " | " << product.toString() << " |" << endl;
			}
		} else {
			if (product[numProductBits - 1]) {
				//A = A + Ms
				product.primeAdd(bit1);
				cout << "| " << i << " | A = A + M    | " << bit1.toString() << " | " << product.toString() << " |" << endl;
			} else {
				//NO OP
				cout << "| " << i << " | NO OPERATION | " << bit1.toString() << " | " << product.toString() << " |" << endl;
			}
		}
		//SHIFT
		product.ARS();
		cout << "|   | ARS Shift    | " << bit1.toString() << " | " << product.toString() << " |" << endl;

	}

	//Remove last bit, display to user
	string productValue = product.toString();
	productValue.pop_back();
	BitString productBits = BitString(productValue);
	productBits.print(1);

	return 0;
}

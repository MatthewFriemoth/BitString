/******************************************************************
BitString Project; Booths therom to multiply bianary numbers
Matthew Friemoth;
*******************************************************************/


#pragma once
#include"BitString.h"

/*
	BitString is a representation of a signed bianary number.
*/

/*
	Constructor that creates a binary string with "_numBits" number of bits
*/
BitString::BitString(int _numBits)
{
	this->numBits = _numBits;
	this->bits = new bool[numBits] {0};
}

/*
	Constructor that creates a binary string from a character string of 1s and 0s
*/
BitString::BitString(std::string ref_Bits)
{
	this->numBits = ref_Bits.length();
	this->bits = new bool[numBits] {0};
	for (int i = 0; i < numBits; i++) {
		bits[i] = ref_Bits[i] == '0' ? 0 : 1;
	}
}

/*
	Constructor that creates a binary string from a number of bits and an integer value
*/
BitString::BitString(int _bits, int num)
{
	this->numBits = _bits;
	this->bits = new bool[numBits] {0};
	if (num > 0) {
		for (int i = 0; i < numBits; i++) {
			bits[numBits - i - 1] = num % 2 == 0 ? 0 : 1;
			num = num / 2;
		}
	} else if (num < 0) {
		num = num + 1;
		for (int i = 0; i < numBits; i++) {
			bits[numBits - i - 1] = num % 2 == 0 ? 1 : 0;
			num = num / 2;
		}
	}
}

/*
	toString, returns the bits as a string
*/
std::string BitString::toString() const
{
	std::string output = "";
	for (int i = 0; i < numBits; i++) {
		output += bits[i] ? '1' : '0';
	}
	return output;
}
/*
	Returns the signed integer value of the binary
*/
int BitString::toInt() const
{
	int output = 0;
	if (bits[0]) {
		for (int i = 0; i < numBits; i++) {
			if (!bits[i]) {
				output = output - pow(2, ((numBits - 1) - i));
			}
		}
		output = output - 1;
	} else {
		for (int i = 0; i < numBits; i++) {
			if (bits[i]) {
				output += pow(2, (numBits - 1) - i);
			}
		}
	}
	return output;
}
/*
	returns the number of bits
*/
int BitString::getNumBits() const
{
	return numBits;
}

/*
	Negates the binary
*/
void BitString::negate()
{
	for (int i = 0; i < numBits; i++) {
		bits[i] = !bits[i];
	}
	std::string pre = "";
	for (int i = 0; i < numBits - 1; i++) {
		pre += '0';
	}
	*this += BitString(pre + '1');
}
/*
	Arithmetic Right Shift, shift bits right based on signed value
*/
void BitString::ARS()
{
	if (numBits > 1) {
		bool* tempBits = new bool[numBits] {0};
		for (int i = 0; i < numBits; i++) {
			tempBits[i] = bits[i];
		}
		for (int i = 1; i < numBits; i++) {
			bits[i] = tempBits[i - 1];
		}
		delete[] tempBits;
	}
}
void BitString::primeAdd(const BitString toAdd)
{
	bool carry = 0;
	for (int i = toAdd.getNumBits() - 1; i >= 0; i--) {

		bool a = bits[i];
		bool b = toAdd[i];

		bits[i] = (a && !b && !carry) || (!a && b && !carry) || (!a && !b && carry) || (a && b && carry);
		carry = (b && carry) || (a && carry) || (a && b);
	}
}
/*
	Gets the bit at index "index"
*/
bool BitString::operator[](int index) const
{
	return bits[index];
}
/*
	Adds a bitstring to the bitstring
*/
void BitString::operator+=(const BitString toAdd)
{
	bool carry = 0;
	for (int i = numBits - 1; i >= 0; i--) {

		bool a = bits[i];
		bool b = toAdd[i];
		bits[i] = (a && !b && !carry) || (!a && b && !carry) || (!a && !b && carry) || (a && b && carry);
		carry = (b && carry) || (a && carry) || (a && b);
	}
}

/*
	directly prints the bitstring to the output
*/
void BitString::print(bool newLine = 0) const
{
	std::cout << "Binary: " << toString() << " | Decimal: " << toInt() << std::endl;

}

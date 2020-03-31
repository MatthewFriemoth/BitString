/******************************************************************
BitString Project; Booths therom to multiply bianary numbers
Matthew Friemoth;
03/10/2020
*******************************************************************/
#pragma once
#include<iostream>
#include<string>

class BitString
{
private:
	int numBits;
	bool* bits;
public:
	BitString(int);
	BitString(std::string);
	BitString(int bits, int num);

	int getNumBits() const;
	bool operator[](int index) const;
	int toInt() const;
	std::string toString() const;
	void print(bool) const;

	void operator+=(const BitString);
	void primeAdd(const BitString);
	void negate();
	void ARS();
};


/*
 * RomanNumeral.cpp
 *
 *  Created on: Mar 1, 2019
 *      Author: Akshat Bansal
 */

#include "RomanNumeral.h"
#include <map>
#include <cmath>

RomanNumeral::RomanNumeral(){
	//default constructor does nothing.
}
RomanNumeral::RomanNumeral(int decimal_val) {
	decimal 				= decimal_val;
	roman 					= to_roman(decimal);
}
RomanNumeral::RomanNumeral(string roman_val){
	roman 					= roman_val;
	decimal 				= to_decimal(roman);
}

int RomanNumeral::get_decimal() const{
	return decimal;
}
string RomanNumeral::get_roman() const{
	return roman;
}

void RomanNumeral::set_roman (string roman_val){
	roman = roman_val;
	decimal = to_decimal(roman_val);
}

int RomanNumeral::count_digits(int number){
	int num_digits 		= 0;

	while (number > 0){
		number 			= number/10;
		num_digits++;
	}

	return num_digits;
}
string RomanNumeral::get_code(int decimal){
	map<int, string> 	codes;
	map<int, string> :: iterator it;

	codes[1] 			= "I";
	codes[5]			= "V";
	codes[10]			= "X";
	codes[50]			= "L";
	codes[100]			= "C";
	codes[500]			= "D";
	codes[1000]			= "M";

	for (it = codes.begin(); it != codes.end(); it++){
		if (it->first == decimal)
			return it->second;
	}

	return "";
}
string RomanNumeral::to_roman(int decimal){
	string roman 		= "";

	while (decimal > 0){
		int num_digits 	= count_digits(decimal);			//4 for 2968
		int order 		= pow(10, num_digits-1);

		if (num_digits != 1 && order % 10 != 0)
			order 		+= 1;

		int msb 	   	= decimal/order;					//2 for 2968
		int num_order 	= msb*order;						//2000 for 2968
		decimal 		= decimal - num_order;				//968 for 2968

		if (1 <= msb && msb <= 3){
			for (int i = 0; i < msb; i++)
				roman += get_code(order);
		}
		if (4 <= msb && msb <= 8){
			if (msb == 4)
				roman += get_code(order) + get_code(5*order);
			else{
				roman += get_code(5*order);
				for (int i = 5; i < msb; i++)
					roman += get_code(order);
			}
		}
		if (msb == 9)
			roman += get_code(order) + get_code(pow(10, num_digits));
	}
	return roman;
}

int RomanNumeral::to_decimal(string roman){
	map<char, int> 		codes;
	int number 				= 0;

	codes['I']				= 1;
	codes['V']				= 5;
	codes['X']				= 10;
	codes['L']				= 50;
	codes['C']				= 100;
	codes['D']				= 500;
	codes['M']				= 1000;

	for (unsigned int i = 0; i < roman.length(); i++){
		if (i != roman.length() - 1){
			if (codes[roman.at(i+1)] > codes[roman.at(i)]){
				number += codes[roman.at(i+1)] - codes[roman.at(i)];
				i++;
			}
			else
				number += codes[roman.at(i)];
		}
		else
			number += codes[roman.at(i)];
	}

	return number;
}

RomanNumeral::~RomanNumeral() {
	// TODO Auto-generated destructor stub
}

RomanNumeral operator + (const RomanNumeral& r1, const RomanNumeral& r2){
	int sum = r1.get_decimal() + r2.get_decimal();
	return RomanNumeral(sum);
}
RomanNumeral operator - (const RomanNumeral& r1, const RomanNumeral& r2){
	int difference = r1.get_decimal() - r2.get_decimal();
	return RomanNumeral(difference);
}
RomanNumeral operator * (const RomanNumeral& r1, const RomanNumeral& r2){
	int product = r1.get_decimal() * r2.get_decimal();
	return RomanNumeral(product);
}
RomanNumeral operator / (const RomanNumeral& r1, const RomanNumeral& r2){
	int quotient = r1.get_decimal()/r2.get_decimal();
	return RomanNumeral(quotient);
}

bool operator == (const RomanNumeral& r1, const RomanNumeral& r2){
	return r1.get_decimal() == r2.get_decimal();
}

bool operator != (const RomanNumeral& r1, const RomanNumeral& r2){
	return r1.get_decimal() != r2.get_decimal();
}

ostream& operator << (ostream& out, const RomanNumeral& r){
	out << "[" << r.get_decimal() << ":" << r.get_roman() << "]";
	return out;
}

istream& operator >> (istream& in, RomanNumeral& r){
	string roman;
	in >> roman;
	r.set_roman(roman);
	return in;
}


/*
 * RomanNumeral.h
 *
 *  Created on: Mar 1, 2019
 *      Author: Akshat Bansal
 */
#include <iostream>

#ifndef ROMANNUMERAL_H_
#define ROMANNUMERAL_H_

using namespace std;

class RomanNumeral {
public:
	RomanNumeral();					//default constructor
	RomanNumeral(int decimal);		//paramaterized constructor with integer argument
	RomanNumeral(string roman);		//paramaterized constructor with string argument

	int get_decimal() const;		//returns decimal instance variable
	string get_roman() const;		//returns roman instance variable

	/**
	 * sets instance variable roman equal to the argument roman.
	 * @param1 roman - string of roman characters.
	 */
	void set_roman(string roman);

	/**
	 * @param1 r1 - reference to the first RomanNumeral object
	 * @param2 r2 - reference to the second RomanNumeral object
	 * @return result - result equal to r1 + r2
	 */
	friend RomanNumeral operator + (const RomanNumeral& r1, const RomanNumeral& r2);
	/**
	 * @param1 r1 - reference to the first RomanNumeral object
	 * @param2 r2 - reference to the second RomanNumeral object
	 * @return result - result equal to r1 - r2
	 */
	friend RomanNumeral operator - (const RomanNumeral& r1, const RomanNumeral& r2);
	/**
	 * @param1 r1 - reference to the first RomanNumeral object
	 * @param2 r2 - reference to the second RomanNumeral object
	 * @return result - result equal to r1 * r2
	 */
	friend RomanNumeral operator * (const RomanNumeral& r1, const RomanNumeral& r2);
	/**
	 * @param1 r1 - reference to the first RomanNumeral object
	 * @param2 r2 - reference to the second RomanNumeral object
	 * @return result - result equal to r1 / r2
	 */
	friend RomanNumeral operator / (const RomanNumeral& r1, const RomanNumeral& r2);

	/**
	 * @param1 r1 - reference to the first RomanNumeral object
	 * @param2 r2 - reference to the second RomanNumeral object
	 * @return - true if both r1 and r2 objects are equal. Otherwise, returns false
	 */
	friend bool operator == (const RomanNumeral& r1, const RomanNumeral& r2);
	/**
	 * @param1 r1 - reference to the first RomanNumeral object
	 * @param2 r2 - reference to the second RomanNumeral object
	 * @return - true if r1 and r2 objects are not equal. Otherwise, returns false
	 */
	friend bool operator != (const RomanNumeral& r1, const RomanNumeral& r2);

	/**
	 * @param1 out - reference to the output stream
	 * @param2 r - reference to the RomanNumeral to be outputted to the output stream
	 * @return out
	 */
	friend ostream& operator << (ostream& out, const RomanNumeral& r);

	/**
	 * @param1 in - reference to the input stream
	 * @param2 r - reference to the RomanNumeral to be inputted from the input stream
	 * @return in
	 */
	friend istream& operator >> (istream& in, RomanNumeral& r);

	virtual ~RomanNumeral();		//destructor
private:
	string roman;
	int decimal;

	/**
	 * @param1 decimal - the decimal number
	 * @return - the number of digits in the decimal number
	 */
	int count_digits(int decimal);

	/**
	 * @param1 roman - string of roman characters
	 * @return - decimal equivalent of the roman characters
	 */
	int to_decimal(string roman);

	/**
	 * @param1 decimal - the decimal number
	 * @return - the roman equivalent single character string equivalent to the decimal number
	 */
	string get_code(int decimal);

	/**
	 * @param1 decimal - the decimal number
	 * @return - the roman character string equivalent of the decimal number
	 */
	string to_roman(int decimal);
};

#endif /* ROMANNUMERAL_H_ */

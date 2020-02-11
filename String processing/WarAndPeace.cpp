//============================================================================
// Name        : CS.cpp
// Author      : Akshat Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Names to search for.
const string ALEXEEVICH  		= "Makar Alexeevich";
const string BAZDEEV     		= "Joseph Bazdeev";
const string DRUBETSKOY  		= "Boris Drubetskoy";

const string ALEXEEVICH_FIRST	= "Makar";
const string ALEXEEVICH_LAST 	= "Alexeevich";
const string BAZDEEV_FIRST 		= "Joseph";
const string BAZDEEV_LAST		= "Bazdeev";
const string DRUBETSKOY_FIRST 	= "Boris";
const string DRUBETSKOY_LAST 	= "Drubetskoy";

const string INPUT_FILE_NAME 	= "WarAndPeace.txt";

/**
 * @param1 input 		- reference to the input stream to be connected to the actual text file
 * Postcondition(s): 	the input stream whose reference was passed as the argument is connected to the actual physical file on disk whose name is defined by the constant INPUT_FILE_NAME.
 * 						If fails to do so, the program exits.
 */
void open_input_file(ifstream &input);

/**
 * Precondition(s): 	the input stream whose reference is passed as the second argument must already be connected to the file on the disk drive.
 * 						this function does NOT check whether the input stream was successfully connected to the physical file on disk.
 * @param lines 		- reference to the string vector that needs to store all the text lines
 * @param input 		- reference to the input stream that is connected to the actual text file
 * Postcondition(s): 	lines vector is populated with the lines of the text. Input stream is closed.
 */
void read_input_file(vector<string> &lines, ifstream &input);

/**
 * Precondition(s):		All necessary text lines must be in the vector passed as reference. This function looks for names in the vector not the input stream which has been closed already.
 * @param lines 		- reference to the string vector that stores all the text lines.
 * Postcondition(s): 	All required information is printed to console.
 */
void find_all(const vector<string> &lines);

/**
 * @param lines 		- reference to the string vector that needs to store all the text lines.
 * @param line_number	- current line number in which the function needs to look for full names.
 * @param full_name	- full name that is to be searched for in the line.
 * Postcondition(s): 	All required information is printed to console.
 */
void find_full_name(const vector<string> &lines, unsigned int line_number, string full_name);

/**
 * @param lines 		- reference to the string vector that needs to store all the text lines.
 * @param line_number	- current line number in which the function needs to look for full names.
 * @param first_name	- first name that is to be searched for in the current line.
 * @param last_name	- last name that is to be searched for in the next line.
 * Postcondition(s): 	All required information is printed to console.
 */
void find_half_name(const vector<string> &lines, unsigned int line_number, string first_name, string last_name);

int main()
{
	ifstream input;
	open_input_file(input);

	vector<string> lines;
	read_input_file(lines, input);

	find_all(lines);

	return 0;
}


void open_input_file(ifstream& input)
{
	input.open(INPUT_FILE_NAME);
	if (input.fail())
	{
		cout << "Failed to open " << INPUT_FILE_NAME << endl;
		exit(1);
	}
}
void read_input_file(vector<string> &lines, ifstream &input)
{
	string line;
	do{
		getline(input, line);	//read line
		lines.push_back(line);	//add line to vector
	}
	while(!input.eof());

	input.close();				//closing the input stream
}
void find_all(const vector<string> &lines)
{
	cout << setw(5) << "LINE" << setw(10) << "POSITION" << " ";
	cout << setw(16) << left << "NAME" << endl;

	for (unsigned int line_number = 0; line_number < lines.size(); line_number++)
	{
		//First look for full names
		find_full_name(lines, line_number, ALEXEEVICH);
		find_full_name(lines, line_number, BAZDEEV);
		find_full_name(lines, line_number, DRUBETSKOY);

		//Then look for half names
		find_half_name(lines, line_number, ALEXEEVICH_FIRST, ALEXEEVICH_LAST);
		find_half_name(lines, line_number, BAZDEEV_FIRST, BAZDEEV_LAST);
		find_half_name(lines, line_number, DRUBETSKOY_FIRST, DRUBETSKOY_LAST);
	}
}
void find_full_name (const vector<string> &lines, unsigned int line_number, string full_name)
{
	size_t position = lines.at(line_number).find(full_name);
	if (position != string::npos)
		cout << right << setw(5) << line_number + 1 << setw(10) << position + 1 << " " << setw(16) << left << full_name << endl;
}
void find_half_name(const vector<string> &lines, unsigned int line_number, string first_name, string last_name)
{
	//if the line is not the last one
	if (line_number == lines.size() - 1)
		return;

	size_t position = lines.at(line_number).find(first_name);
	size_t last_name_posi = lines.at(line_number+1).find(last_name);

	if (position != string::npos)
		if (last_name_posi == 0)
			cout << right << setw(5) << line_number + 1 << setw(10) << position + 1 << " " << left << first_name << " " << last_name << endl;
}
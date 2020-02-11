//============================================================================
// Name        : CS.cpp
// Author      : Akshat Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const string INPUT_FILE_NAME = "students.txt";

/*
 * Precondition(s) 		- input file format is validated.
 * @param course_name 	- variable to store the name of the course.
 * @param num_students	- number of students enrolled in the course.
 * @param names 		   - names pointer to dynamically allocate memory as needed and store student names.
 * @param scores 		- pointer for a 2D array to store the scores of the students.
 * @param num_scores_per_student - number of scores per student to allocate just enough memory needed to store the scores of each student.
 * @return num_scores_per_student - number of scores per student to allocate just enough memory needed to store the scores of each student.
 */
int* read(string& course_name, int& num_students, string* &names, int** &scores, int* num_scores_per_student);
/*
 * CAUTION              - this method does not gaurantee 2D array scores' immutability.
 * @param course_name 	- variable to store the name of the course.
 * @param num_students	- number of students enrolled in the course.
 * @param names 		   - names pointer to dynamically allocate memory as needed and store student names.
 * @param scores 		- pointer for a 2D array to store the scores of the students.
 * @param num_scores_per_student - number of scores per student to allocate just enough memory needed to store the scores of each student.
 */
void print(const string& course_name, const int& num_students, const string names[], int** &scores, const int num_scores_per_student[]);


int main() {
	string course_name	= "";
	int num_students	   = 0;
	string* names 		   = NULL;
	int** scores 		   = NULL;
	int* num_scores_per_student = NULL;

	num_scores_per_student = read (course_name, num_students, names, scores, num_scores_per_student);
	print (course_name, num_students, names, scores, num_scores_per_student);

	return 0;
}

int* read(string& course_name, int& num_students, string* &names, int** &scores, int* num_scores_per_student){
	ifstream input;
	input.open(INPUT_FILE_NAME);
	if (input.fail()){
		cout << "Could not load file " << INPUT_FILE_NAME << endl;
		exit(1);
	}

	//get name of the course and number of students from the first line of input
	input >> course_name;
	input >> num_students;

	names 					= new string[num_students];
	scores					= new int*[num_students];
	num_scores_per_student 	= new int[num_students];
	int student_number  	= 0;

	//while input has not reached the end of file
	while (!input.eof()){
		string first_name 	= "";
		string last_name 	= "";
		int num_scores		= 0;

		//extraction operator stops at first whitespace character
		input >> first_name;
		input >> last_name;
		input >> num_scores;

		scores[student_number] 		= new int[num_scores];
		num_scores_per_student[student_number] = num_scores;

		for (int i = 0; i < num_scores; i++)
			input >> scores[student_number][i];

		names[student_number] 		= first_name + " " + last_name;
		student_number++;
	}

	return num_scores_per_student;
}

void print(const string& course_name, const int& num_students, const string names[], int** &scores, const int num_scores_per_student[]){
	cout << "STUDENT SCORES for " << course_name << endl << endl;
	for (int i = 0; i < num_students; i++){
		cout << names[i] << endl;

		if (num_scores_per_student[i] == 0)
			cout << right << setw(10) << "(none)";

		for (int j = 0; j < num_scores_per_student[i];  j++)
			cout << right << setw(5) << scores[i][j];

		cout << endl << endl;
	}
}

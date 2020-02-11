//============================================================================
// Name        : CS.cpp
// Author      : Akshat Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

enum Door {DOOR_1 = 1, DOOR_2 = 2, DOOR_3 = 3};

/*
 * @param simulation_count 			- the number of times the simulation needs to run
 */
void run_simulations (int simulation_count);

/*
 * @param simulation_num 			- current simulation number
 * @param num_first_choice_wins 	- number of wins with first choice
 * @param num_second_choice_wins 	- number of wins with second choice
 */
void simulate(int simulation_num, int& num_first_choice_wins, int& num_second_choice_wins);

/*
 * prints simulation table column headers
 */
void print_simulation_table();

/*
 * prints simulation data with required formatting
 * @param simulation_num 			- current simulation number
 * @param reward_door 				- car behind this door
 * @param first_choice 			- initial choice of the contestant
 * @param opened_door 				- door opened by Monty after the initial choice of the contestant
 * @param second_choice 			- second choice of the contestant
 */
void print_simulation_data(int simulation_num, Door reward_door, Door first_choice, Door opened_door, Door second_choice);

/*
 * prints conclusion at end of the simulations
 * @param num_first_choice_wins 	- number of wins with first choice
 * @param num_second_choice_wins 	- number of wins with second choice
 */
void print_conclusion(int num_first_choice_wins, int num_second_choice_wins);

/*
 * @return random door from DOOR_1, DOOR_2, DOOR_3
 */
Door get_random_door();

/*
 * @param reward_door 				- the correct door that has the car behind it
 * @param first_choice 			- the door that the contestant initially selected
 * @return the door that is neither the reward door nor the contestant's first pick.
 */
Door open_door_after_first_choice (Door reward_door, Door first_choice);

/*
 * @param opened_door 				- the door Monty opened after contestant's initial pick.
 * @param first_choice 			- the door that the contestant initially selected
 * @return the second choice of the contestant
 */
Door get_second_door(Door opened_door, Door first_choice);

int main() {
	srand (time(NULL));				//seeding random generator
	run_simulations(100);			//simulating experiment
	return 0;
}

void run_simulations (int simulation_count){
	int num_first_choice_wins 		= 0;
	int num_second_choice_wins 		= 0;

	print_simulation_table();

	for (int i = 0; i < simulation_count; i++){
		simulate (i, num_first_choice_wins, num_second_choice_wins);
	}

	print_conclusion(num_first_choice_wins, num_second_choice_wins);
}
void simulate(int simulation_num, int& num_first_choice_wins, int& num_second_choice_wins){
	Door reward_door 				= get_random_door();										//#1 Randomly pick a door to hide car.
	Door first_choice 				= get_random_door();										//#2 As a contestant, randomly pick a door as the first choice
	Door opened_door 				= open_door_after_first_choice(reward_door, first_choice);	//#3 As Monty, open door to reveal a goat.
	Door second_choice 				= get_second_door(opened_door, first_choice);				//#4 Second choice of the contestant.

	print_simulation_data(simulation_num, reward_door, first_choice, opened_door, get_second_door(opened_door, first_choice));

	if (first_choice == reward_door)
		num_first_choice_wins++;
	if (second_choice == reward_door)
		num_second_choice_wins++;

	cout << endl;
}
Door get_random_door(){
	int num 						= rand()%3 + 1;		//get an integer from 1 to 3.

	if (1 == num)
		return DOOR_1;
	if (2 == num)
		return DOOR_2;
	else
		return DOOR_3;
}
Door open_door_after_first_choice (Door reward_door, Door first_choice){
	Door door_to_open;			//

	//loop terminates when the program finds a door which is neither the reward_door door nor contestant's first choice
	do{
		door_to_open 				= get_random_door();
	}
	while (door_to_open == reward_door || door_to_open == first_choice);

	return door_to_open;
}
Door get_second_door(Door opened_door, Door first_choice){
	Door second_choice;

	//loop terminates when the program finds a door which is neither the door opened by Monty nor the contestant's first choice
	do{
		second_choice 				= get_random_door();
	}
	while(second_choice == opened_door || second_choice == first_choice);

	return second_choice;
}
void print_simulation_table(){
	cout << right << setw(6) << "#";
	cout << right << setw(8) << "Car";
	cout << right << setw(8) << "First";
	cout << right << setw(8) << "Opened";
	cout << right << setw(8) << "Second";
	cout << right << setw(8) << "Win";
	cout << right << setw(8) << "Win" << endl;

	cout << right << setw(6) << "";
	cout << right << setw(8) << "here";
	cout << right << setw(8) << "choice";
	cout << right << setw(8) << "door";
	cout << right << setw(8) << "choice";
	cout << right << setw(8) << "first";
	cout << right << setw(8) << "second" << endl;

	cout << endl;
}
void print_simulation_data(int simulation_num, Door reward_door, Door first_choice, Door opened_door, Door second_choice){
	cout << right << setw(6) << simulation_num+1;
	cout << right << setw(8) << reward_door;
	cout << right << setw(8) << first_choice;
	cout << right << setw(8) << opened_door;
	cout << right << setw(8) << second_choice;

	if (first_choice == reward_door)
		cout << right << setw(8) << "yes";
	else
		cout << right << setw(8) << "" << right << setw(8) << "yes";
}
void print_conclusion(int num_first_choice_wins, int num_second_choice_wins){
	cout << endl;
	cout << right << setw(6) << num_first_choice_wins << " wins if stay with first choice" << endl;
	cout << right << setw(6) << num_second_choice_wins << " wins if switch to the second choice" << endl;
	cout << endl;

	cout << "Win ratio of switch over stay: " << setprecision(2) << static_cast<double>(num_second_choice_wins)/num_first_choice_wins;
}

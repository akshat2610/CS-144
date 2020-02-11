/*
 * main.cpp
 *
 *  Created on: Feb 1, 2019
 *      Author: Akshat Bansal
 *
 *  The assignment is modelled as follows:
 *  F - Faucet
 *  P - Plants
 *  Numbers below the letters represent their position. This design was chosen to facilitate array traversal
 *
 *  F  P  P  P  P  P  P  ... upto N plants
 *  -1 0  1  2  3  4  5  ... upto N-1
 *
 *  A dynamically allocated boolean array is used to keep track of the status of a plant - watered or unwatered. As the plants are watered,
 *  values at corresponding indexes are set to true. 
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

const short WATER_CAN_CAPACITY			= 3;					//According to assignment requirements
const short STARTING_POSITION 			= -1;					//At the faucet
const string INPUT_FILE_NAME 			   = "counts.txt";	//Given in the assignment description

short *get_simulation_counts();									//@return pointer to the array of simulation counts
short get_num_diff_simulations();								//@return number of different simulation counts provided in the input file

/************************************* ARGUMENT NAMES ******************************************
 * @param num_plants 	- number of plants in the arrangement
 * @param watered 		- array of boolean values to keep record of the status of each plant
 * @param position		- current position of the water can
 * @param water_units 	- amount of water units in the can
 * @param num_steps 	   - current number of steps already taken
 ***********************************************************************************************/

short water_plan_near(short num_plants, bool *watered, short& position, short& water_units, short& num_steps);	//@return number of step-units for near water plan
short water_plan_far(short num_plants, bool *watered, short& position, short& water_units, short& num_steps);	//@return number of step-units for far water plan
short first_unwatered_index(bool* watered, short num_plants);	//@return index of the first unwatered plant. if not found, returns -1
short last_unwatered_index(bool* watered, short num_plants);	//@return index of the last unwatered plant. if not found, returns -1

void refill(short& position, short& water_units, short& num_steps, short& num_step_units); //models refilling the water can
void water(bool *watered, short& position, short& water_units, short& num_steps, short& unwatered_index, short& num_step_units); //models watering the plant
void reset_variables(short& num_steps, short& position, short& water_units);	//resets the variables to 0, STARTING_POSITION, WATER_CAN_CAPACITY
void set_status_unwatered(bool *watered, short num_plants);						   //initializes the boolean array to false

void print_data(short num_steps, short num_step_units);  //prints the line immediately after the table
void print_near_plan_heading(short num_plants);          //prints the heading of the near plan table
void print_far_plan_heading(short num_plants);           //prints the heading of the far plan table
void print_table_heading();                              //prints the column headers for the table
void print_conclusion(short num_plants, short near_plan_step_units, short far_plan_step_units); 

int main(){
	short num_diff_simulations 			= get_num_diff_simulations(); //number of different simulation counts in the input file
	short *simulation_counts 			   = get_simulation_counts();    //array containing different simulation counts

   //iterates until all the simulation counts have been computed.
	for (int i = 0; i < num_diff_simulations; i++){
	   //SETUP
		short num_steps 				      = 0;                       //initial steps are zero
		short position 					   = STARTING_POSITION;		   //each plan starts at the faucet
		short water_units 				   = WATER_CAN_CAPACITY; 		//each plan starts with a full can
		
		short num_plants 				      = simulation_counts[i];    //get the number of plants for the corresponding simulation  
		bool *watered 					      = new bool[num_plants];		//keep track the status of every plant
		set_status_unwatered(watered, num_plants);					   //initialize all plants to false

      //NEAR PLAN TEST
		print_near_plan_heading(num_plants);                        //print column headers for near plan table
		short near_plan_step_units 		= water_plan_near(num_plants, watered, position, water_units, num_steps);  //get number of step-units for near plan
		cout << "Plan Near: ";
		print_data(num_steps, near_plan_step_units);
      
      //RESET STATE TO TEST FAR PLAN
		reset_variables(num_steps, position, water_units);          //reset initial setup variables to original values
		set_status_unwatered(watered, num_plants);					   //initialize all plants to false

      //FAR PLAN TEST
		print_far_plan_heading(num_plants);                         //print column headers for far plan table
		short far_plan_step_units 		   = water_plan_far(num_plants, watered, position, water_units, num_steps);
		cout << "Plan Far: ";
		print_data(num_steps, far_plan_step_units);

      //CONCLUSION
		print_conclusion(num_plants, near_plan_step_units, far_plan_step_units);
	}
	cout << endl;

	return 0;
}

short get_num_diff_simulations(){
	ifstream input_file;
	short num_diff_simulations 			= 0;
	short val 							      = 0;

	input_file.open(INPUT_FILE_NAME);
	//check whether file opened correctly
	if (input_file.fail()){
		cout << "Failed to open file: " << INPUT_FILE_NAME << endl;
		exit(1);
	}

	//Count the number of different simulations provided in the input file
	while (input_file >> val){
		if (val > 0)
			num_diff_simulations++;
		else
			break;
	}
	input_file.close();

	return num_diff_simulations;
}
short *get_simulation_counts(){
	ifstream input_file;
	short *simulation_counts;
	short num_diff_simulations 			= get_num_diff_simulations();
	simulation_counts 					   = new short [num_diff_simulations];

	input_file.open(INPUT_FILE_NAME);
	//check whether file opened correctly
	if (input_file.fail()){
		cout << "Failed to open file for reading simulation counts: " << INPUT_FILE_NAME << endl;
		exit(1);
	}

	for (int i = 0; i < num_diff_simulations; i++)
		input_file >> simulation_counts[i];

	return simulation_counts;
}

void water(bool *watered, short& position, short& water_units, short& num_steps, short& unwatered_index, short& num_step_units){
	num_steps 				               += abs(unwatered_index - position);                //increase number of steps by the distance between unwatered plant index and current position
	num_step_units 			            += water_units * abs(unwatered_index - position);  //increase number of step-units by the product of water units and the distance between unwatered plant index and current position
	position				                  = unwatered_index;                                 //set current position to unwatered plant index
	watered[position]		               = true;                                            //set status of plant as watered or true
	cout << "Plant  " << position+1 << right << setw(9) << num_steps << right << setw(11) << water_units << right << setw(16) << num_step_units << endl;
	water_units--;                                                                         //decrease number of water units in the can
}
void refill(short& position, short& water_units, short& num_steps, short& num_step_units){
	num_steps 			               	+= position - STARTING_POSITION;                   //increase number of steps by the distance between current position and the position of the FAUCET
	num_step_units 			            += water_units*(position - STARTING_POSITION);     //increase number of step-units by the product of water units and the distance between current position and FAUCET   
	position 				               = STARTING_POSITION;                               //set current position to the position of the FAUCET
	cout << "FAUCET  " << right << setw(9) << num_steps << right << setw(11) << water_units << right << setw(16) << num_step_units << endl;
	water_units				               = WATER_CAN_CAPACITY;                             //completely fill the water can
}

short water_plan_near(short num_plants, bool *watered, short& position, short& water_units, short& num_steps){
	short num_step_units 				= 0;
	short first_unwatered 				= -1;
	bool done 							   = false;
	
	//loop until there are no unwatered plants left
	while (!done){
		first_unwatered 				   = first_unwatered_index(watered, num_plants);	//find first unwatered plant
		//if no unwatered plant found, return num_step_units
		if (-1 == first_unwatered)
			done 						      = true;
		//else if unwatered plant found 
		else{
		   //decide next move - water or refill? bases on the number of units in the can
			if (water_units > 0){
			   //if can has water, water the plant.
				water(watered, position, water_units, num_steps, first_unwatered, num_step_units);
			}
			else{
			   //else if can does not have water, refill the water can
				refill(position, water_units, num_steps, num_step_units);
			}
		}
	}
	//walk back to the faucet
	num_steps 							   += position - STARTING_POSITION;
	num_step_units 					   += water_units * (position-STARTING_POSITION);
	cout << "FAUCET" << right << setw(11) << num_steps << right << setw(11) << water_units << right << setw(16) << num_step_units << endl << endl;

	return num_step_units;
}
short water_plan_far(short num_plants, bool *watered, short& position, short& water_units, short& num_steps){
	short num_step_units 				= 0;
	short last_unwatered 			   = -1;
	bool done 							   = false;
	
	//loop until no unwatered plants are left
	while (!done){
		last_unwatered 				   = last_unwatered_index(watered, num_plants);	//find first unwatered plant
		//if no unwatered plant found, return num_step_units
		if (-1 == last_unwatered)
			done 						= true;
		//else if unwatered plant found
		else{
		   //decide whether to water the plant or refill the can? bases on the water in can
			if (water_units > 0){
			   //if can has water, water the plant
				water(watered, position, water_units, num_steps, last_unwatered, num_step_units);
			}
			else{
			   //else if can does not have water, refill the can
				refill(position, water_units, num_steps, num_step_units);
			}
		}
	}
	//walk back to the faucet
	num_steps 							   += position - STARTING_POSITION;
	num_step_units 						+= water_units * (position-STARTING_POSITION);
	cout << "FAUCET" << right << setw(11) << num_steps << right << setw(11) << water_units << right << setw(16) << num_step_units << endl << endl;

	return num_step_units;
}


short first_unwatered_index(bool* watered, short num_plants){
   //loop over the plants to find the first unwatered plant
	for (short i = 0; i < num_plants; i++){
		if (!watered[i])
			return i;
	}
	return -1;
}
short last_unwatered_index(bool* watered, short num_plants){
   //loop over the plants to find the last unwatered plant
	for (short i = num_plants-1; i >= 0; i--){
		if (!watered[i])
			return i;
	}
	return -1;
}

void print_data(short num_steps, short num_step_units){
	cout << "Total steps = " << num_steps << ", total step-units = " << num_step_units << endl;
}
void print_near_plan_heading(short num_plants){
   cout << endl;
   cout << "==========================" << endl;
   cout << " Plan Near with " << num_plants << " plants" << endl;
   cout << "==========================" << endl;
   print_table_heading();
}
void print_far_plan_heading(short num_plants){
   cout << endl;
	cout << "=========================" << endl;
   cout << " Plan Far with " << num_plants << " plants" << endl;
   cout << "=========================" << endl;
   print_table_heading();
}
void print_table_heading(){
   cout << endl;
	cout << "Where      Cum. steps  Water amt.  Cum. step-units" << endl;
   cout << "---------  ----------  ----------  ---------------" << endl;
}
void set_status_unwatered(bool *watered, short num_plants){
	for (short i = 0; i < num_plants; i++)
		watered[i] 						= false;
}
void reset_variables(short& num_steps, short& current_position, short& current_water_units){
	num_steps 							= 0;
	current_position 					= STARTING_POSITION;
	current_water_units 				= WATER_CAN_CAPACITY;
}
void print_conclusion(short num_plants, short near_plan_step_units, short far_plan_step_units){
   cout << endl;
   cout << "*** With " << num_plants << " plants, ";
	if (near_plan_step_units <= far_plan_step_units)
		cout << "Plan Near is better with " << far_plan_step_units - near_plan_step_units << " fewer step-units." << endl;
	else
		cout << "Plan Far is better with " << near_plan_step_units - far_plan_step_units << " fewer step-units." << endl;
}

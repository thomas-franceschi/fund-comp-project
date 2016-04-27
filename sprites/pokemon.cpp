#include <iostream>
#include <cstdlib>
#include <cmath>
#include "pokemon.h"

using namespace std;

//Constructor 
Pokemon::Pokemon(string n, int max_hp, int hp, int att, int def, int lev, int ev_lev, int ex ) {
	if (max_hp < 75 ) max_hp = 75;
	if ( hp < 0 ) hp = 0;
	if (att < 0 ) att = 0;
	if ( def < 0 ) def = 0;
	if (lev < 2 ) lev = 2;
	if (ev_lev < lev ) ev_lev = lev + 5;  
	if (ex < 0 ) ex = 10;
	
	name = n; 
	hit_points = hp;
	attack = att;
	defense = def;
	level = lev;
	evolve_level = ev_lev;
	max_hit_points = max_hp;
	exp = ex;
	
}

//Battle function returns 1 for a win and 0 for a loss
int Pokemon::battle ( Pokemon &opponent ) {
	int move = 1, kill = 0, run = 0;
	int choice;
	
	srand(time(NULL));

	cout << "Your HitPoints: " << hit_points << endl;
	cout << "Opponent HitPoints: " << opponent.get_hit_points() << endl;
	cout << endl;

	//While neither pokemon has fainted, continue the battle 
	while (hit_points > 0 && opponent.get_hit_points() > 0 && kill == 0 ) {
		//Allow user the option to fight or run 
		cout << "Press (1) to fight and (2) to run." << endl;
		cin >> choice;
		
		//Break the while loop and end the battle if user chooses to run 
		if (choice == 2) {
			kill = 1;
			run = 1;
			break;
		}
		
		//If user chooses to fight switch between user turn and opponent turn (by a simple *-1 switch)
		else{
			move = move * -1;
			if(move == -1) {
				make_attack(opponent);
			}
			
			else {
				defend(opponent);
			}
			
			//Sets negative hit point values to zero since negative health does not make sense 
			if (hit_points < 0 ) hit_points = 0;
			if (opponent.get_hit_points() < 0) opponent.set_hit_points(0);
			
			cout << "Your HitPoints: " << hit_points << endl;
			cout << "Opponent HitPoints: " << opponent.get_hit_points() << endl;
			cout << endl;
		}
	}
	
	//If while loop is exited and the user has fled (setting run to 1) then output message and return 0 for loss 
	if (run == 1 ) {
		cout << "You fled the battle!" << endl;
		return 0;
	}
	
	//If user did not flee check for winner 
	else {
		//Check to see if your pokemon won, return 1 for winning 0 for loss
		if (hit_points > 0) {
			exp = exp + (pow(2, opponent.get_level())); //Gain experience points for making the opponent faint based on opponent's level
			check_pokemon();	//Check to see if pokemon should level up 
			opponent.set_hit_points(get_max_hit_points()); //Heal the pokemon that was just beaten so that it can battle in the future 
			return 1;	//Your win
		}
	
		else {
			return 0;	//Your loss 
		}
	}
}


//Performs attack from current pokemon on a chosen pokemon 
void Pokemon::make_attack( Pokemon &opponent ) {
	
	//Declare Variables 
	int strike_power = 0, strike_accuracy = 0, move_number = 0, move_power = 0;
	
	srand(time(NULL));
	
	//Prompt user to choose a move 
	cout << "Please choose a move for " << name << " to use on " << opponent.get_name() << endl;
	cout << " ----------------------------------------------------------" << endl;
	list_moves();

	//Choose a move
	cout << endl << "Which move would you like to use? Incorrect input will choose first move." << endl;
	cin >> move_number;
	cout << endl;
	
	//Check that move number is valid
	if (move_number < 1 || move_number > moves.size()) move_number = 1;
	
	//Change move number to move number - 1 since access starts at 0
	move_number = move_number - 1;	
	move_power = moves[move_number].get_power();

	//Calculate force and accuracy of attack
	strike_power = attack + move_power - opponent.get_defense() - (rand() % 10 + 5);

	if (strike_power < 0 ) strike_power = 15;

	//Determine if attack is accurate 
	strike_accuracy = rand() % 100 + 1;     // strike_accuracy in the range 1 to 100

	//User move's accuracy against randomized number. If random number is within range then the move hits 
	if (strike_accuracy <= moves[move_number].get_accuracy() ) {
		cout << name << " used " << moves[move_number].get_name() << " and " << opponent.get_name() << " lost " << strike_power << " hit points!" << endl << endl;
		opponent.deduct_hit_points( strike_power );
		cout << "-------------------------------------------------" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << endl;
	} 
	
	//If accuracy is not enough then display that the attack missed.
	if (strike_accuracy > moves[move_number].get_accuracy() ) {
		cout << name << " used " << moves[move_number].get_name() << " but it missed!!" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << endl;	
	}
}



//Defend attack from opponent 
void Pokemon::defend( Pokemon &opponent ) {
	//Set seed to time 
	srand(time(NULL));

	//Declare Variables 
	int strike_power = 0, strike_accuracy = 0, move_number = 0, move_power = 0;
	
	//Randomly choose a move  
	move_number = rand () % opponent.moves.size();

	//Find move power of chosen move 
	move_power = moves[move_number].get_power();
	
	//Calculate power of a strike based off various attributes (rand added at end to make strike values more realistic)
	strike_power = opponent.get_attack() + move_power - defense - (rand() % 10 + 5);

	if (strike_power < 0 ) strike_power = 5;

	//Determine if attack is accurate 
	strike_accuracy = rand() % 100 + 1;     // strike_accuracy in the range 1 to 100

	//User move's accuracy against randomized number. If random number is within range then the move hits 
	if (strike_accuracy <= moves[move_number].get_accuracy() ) {
		deduct_hit_points( strike_power );
		cout << "You've been hit by " << opponent.moves[move_number].get_name() << "! You lost " << strike_power << " hit points." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << endl;
	} 
	
	//If accuracy is not enough then display that the attack missed.
	if (strike_accuracy > opponent.moves[move_number].get_accuracy() ) {
		cout << "Your opponent used " << opponent.moves[move_number].get_name() << " but it missed!!" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << endl;
	}
}




//This function takes the inputted type of Potion (which is an object) and increases Pokemon health by that amount of healing
void Pokemon::heal(Potion healing_type) {
	
	hit_points = hit_points + healing_type.get_healing_power();  
	
	//Make sure hit_points does not go over max amount
	if ( hit_points > 200 ) hit_points = 200;
	
}


//Get functions 
int Pokemon::get_max_hit_points() {
	return (max_hit_points);
}

int Pokemon::get_hit_points () {
	return (hit_points);
}

int Pokemon::get_attack() {
	return (attack);
}

int Pokemon::get_defense() {
	return (defense);
}

string Pokemon::get_name () {
	return (name);
}

int Pokemon::get_level() {
	return (level);
}

int Pokemon::get_exp() {
	return (exp); 
}

//Checks pokemon to see if it should faint, evolve etc. (This may not be used but created just in case)
void Pokemon::check_pokemon(){
	if (exp > 50) level = 3;
	if (exp > 100) level =4;
	if (exp > 150) level = 5;
	if (exp > 200) level = 6;
	if (exp > 400) level = 7;
	if (exp > 600) level = 8;
	if (exp > 800) level = 9;
	if (exp > 1000) level = 10;
	if (exp > 1500) level = 11;
	if (exp > 2000) level = 12;
	if (exp > 3000) level = 13;
	if (exp > 4000) level = 14;
	if (exp > 5000) level = 15;
	if (exp > 6000) level = 16;
	if (exp > 7000) level = 17;
	if (exp > 8000) level = 18;
}

//Sends pokemon to the next level (Most likely will not be used)
void Pokemon::evolve(){
	
}


//Adds move to list of moves pokemon can execute
void Pokemon::add_move( Moves input_move ) {
	moves.push_back( input_move );
}

//List moves
void Pokemon::list_moves() {
	cout << "Your Pokemon has the following moves:" << endl;
	
	//Cycle through and print moves 
	for (int i = 0; i < moves.size(); i++ ) {
		cout << i + 1 << ".	" << moves[i].get_name() << endl;
	}
	cout << endl;
}


//Set functions to change the number of hit_points 
void Pokemon::deduct_hit_points( int deduction_amount ) {
	 hit_points = hit_points - deduction_amount;
}


void Pokemon::set_hit_points(int val) {
	hit_points = val;
}

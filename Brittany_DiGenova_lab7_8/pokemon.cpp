#include <iostream>
#include <cstdlib>
#include "pokemon.h"

using namespace std;

Pokemon::Pokemon(string n, int hp, int att, int def, int lev, int ev_lev ) {
	if ( hp < 0 ) hp = 0;
	if (att < 0 ) att = 0;
	if ( def < 0 ) def = 0;
	if (lev < 2 ) lev = 2;
	if (ev_lev < lev ) ev_lev = lev + 5;  
	
	name = n; 
	hit_points = hp;
	attack = att;
	defense = def;
	level = lev;
	evolve_level = ev_lev;
	
}

//Battle function returns 1 for a win and 0 for a loss
int Pokemon::battle ( Pokemon &opponent ) {
	int move = 1;
	
	while (hit_points > 0 && opponent.get_hit_points() > 0 ) {
		//switch between attacking and defending 
		move = move * -1;
		if(move == -1) {
			cout << "Making attack" << endl;
			make_attack(opponent);
		}
		
		else {
			cout << "Defending Opponent" << endl;
			defend(opponent);
			
		}
	}
	
	//Check to see if your pokemon won, return 1 for winning 0 for loss
	if (hit_points > 0) {
		return 1;	//Your win
	}
	return 0;		//Your loss 
	
}

//Performs attack from current pokemon on a chosen pokemon 
void Pokemon::make_attack( Pokemon &opponent ) {
	int strike_power = 0, strike_accuracy = 0, move_number = 0, move_power = 0;
	
	//Prompt user to choose a move 
	cout << "Please choose a move" << endl;
	list_moves();

	//Choose a move
	cout << "Which move would you like to use? Incorrect input will choose first move." << endl;
	cin >> move_number;
	
	//Check that move number is valid
	if (move_number < 1 || move_number > moves.size()) move_number = 1;
	
	//Change move number to move number - 1 since access starts at 0
	move_number = move_number - 1;
	
	move_power = moves[move_number].get_power();
	cout << "Brittany's Move power is " << move_power << endl;
	//Calculate force and accuracy of attack
	strike_power = attack + move_power - opponent.get_defense();
	cout << "strike power is " << strike_power << endl;

	//Determine if attack is accurate 
	srand(time(NULL));
	strike_accuracy = rand() % 100 + 1;     // strike_accuracy in the range 1 to 100
	cout << "The strike accuracy is " << strike_accuracy << endl;
	cout << "Chosen move accuracy is " << moves[move_number].get_accuracy() << endl;
	
	if (strike_accuracy <= moves[move_number].get_accuracy() ) {
		opponent.deduct_hit_points( strike_power );
		cout << opponent.get_hit_points() << endl; 
	} 
	
	//If accuracy is not enough then display that the attack missed.
	if (strike_accuracy > moves[move_number].get_accuracy() ) {
		cout << "Used " << moves[move_number].get_name() << " but it missed!!" << endl;
	}
}

//Defend attack from opponent 
void Pokemon::defend( Pokemon &opponent ) {
	//Set seed to time 
	srand(time(NULL));

	int strike_power = 0, strike_accuracy = 0, move_number = 0, move_power = 0;
	
	//Randomly choose a move  
	move_number = rand () % opponent.moves.size();
	cout << "Your oppononent chose move number " << move_number + 1 << " " << opponent.moves[move_number].get_name() << "." << endl;

	//Find move power of chosen move 
	move_power = moves[move_number].get_power();
	cout << "Opponent's Move power is " << move_power << endl;
	
	//Calculate force and accuracy of attack
	strike_power = opponent.get_attack() + move_power - defense;
	cout << "strike power is " << strike_power << endl;

	//Determine if attack is accurate 
	strike_accuracy = rand() % 100 + 1;     // strike_accuracy in the range 1 to 100
	cout << "The strike accuracy is " << strike_accuracy << endl;
	cout << "Chosen move accuracy is " << opponent.moves[move_number].get_accuracy() << endl;
	
	if (strike_accuracy <= moves[move_number].get_accuracy() ) {
		deduct_hit_points( strike_power );
		cout << get_hit_points() << endl; 
	} 
	
	//If accuracy is not enough then display that the attack missed.
	if (strike_accuracy > opponent.moves[move_number].get_accuracy() ) {
		cout << "Your opponent used " << opponent.moves[move_number].get_name() << " but it missed!!" << endl;
	}

}




//This function takes the inputted type of Potion (which is an object) 
//and increases Pokemon health by that amount of healing
void Pokemon::heal(Potion healing_type) {
	
	hit_points = hit_points + healing_type.get_healing_power();  
	
	//Make sure hit_points does not go over max amount
	if ( hit_points > 200 ) hit_points = 200;
	
}


//retrieves number of hit_points
int Pokemon::get_hit_points () {
	return (hit_points);
}

int Pokemon::get_attack() {
	return (attack);
}

int Pokemon::get_defense() {
	return (defense);
}

//Checks pokemon to see if it should faint, evolve etc. 
void Pokemon::check_pokemon(){
	//check level and compare to evolve level
	if (level != 100 && level >= evolve_level) {
		evolve();
	}
}

//Sends pokemon to the next level 
void Pokemon::evolve(){
	
}


//Adds move to list of moves pokemon can execute
void Pokemon::add_move( Moves input_move ) {
	moves.push_back( input_move );
}

//List moves
void Pokemon::list_moves() {
	
	//cout << "Your Pokemon has the following moves:" << endl;
	for (int i = 0; i < moves.size(); i++ ) {
		cout << i + 1 << ".	" << moves[i].get_name() << endl;
	}
	
	cout << endl;
}



void Pokemon::deduct_hit_points( int deduction_amount ) {
	 hit_points = hit_points - deduction_amount;
}


/*void Pokemon::set_hit_points(int val) {
	hit_points = val;
}*/
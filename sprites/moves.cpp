//Brittany DiGenova
//moves.cpp
//This file contains the basic member functions for the class type moves

#include <iostream> 
#include "moves.h"

using namespace std;

//Default Constructor 
Moves::Moves( string n, int pow , int acc ){
	if (pow < 5) pow = 5;
	if (acc < 70) acc = 70;
	
	name = n;
	power = pow;
	accuracy = acc;
}

//Get functions to access private data 
int Moves::get_power() {
	
	return (power);
	
}

int Moves::get_accuracy() {
	
	return (accuracy);
	
}

string Moves::get_name(){
	return (name);
}
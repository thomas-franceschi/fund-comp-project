#include <iostream>
#include "watertype.h"

using namespace std;

//Default constructor
Watertype::Watertype(string n, int hp, int att, int def, int lev, int ev_lev, int str, int wk) : Pokemon (n, hp, att, def, lev, ev_lev ) {
	strengths = str;
	weaknesses = wk;
}
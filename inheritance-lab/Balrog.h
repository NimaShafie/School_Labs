#pragma
// LAB 7 SHAFIE,Nima W
#ifndef BALROG_H
#define BALROG_H
#include "Demon.h"

#include <iostream>

class Balrog : public Demon {					// Balrog is a dervied class of Creature
private:
	int strength;									// how much damage we can inflict
	int hitpoints;									// how much damage we can sustain
	string getSpecies();							// returns type of species
public:
	// constructors/destructors
	Balrog();									// default constructor
	Balrog(int newStrength, int newHit);		// 2 argument constructor
	Balrog(const Balrog& copyFromCreature);		// copy constructor
	~Balrog();									// destructor

	// accessor functions
	int getStrength() const;			// gets strength member variable of creature
	int getHitPoints() const;			// gets hitpoints member variable of creature

	// mutator functions
	void setStrength(int newStrength);	// sets creatures strength
	void setHitpoints(int newHit);		// sets creatures hitpoints
	int getDamage();					// returns amount of damage this creature inflicts in one round of combat
};
#endif
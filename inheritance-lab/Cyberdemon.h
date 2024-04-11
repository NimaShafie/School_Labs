#pragma
// LAB 7 SHAFIE,Nima W
#ifndef CYBERDEMON_H
#define CYBERDEMON_H
#include "Demon.h"

#include <iostream>

class Cyberdemon : public Demon {					// Human is a dervied class of Creature
private:
	int strength;									// how much damage we can inflict
	int hitpoints;									// how much damage we can sustain
	string getSpecies();						// returns type of species
public:
	// constructors/destructors
	Cyberdemon();									// default constructor
	Cyberdemon(int newStrength, int newHit);		// 2 argument constructor
	Cyberdemon(const Cyberdemon& copyFromCreature);	// copy constructor
	~Cyberdemon();									// destructor

	// accessor functions
	int getStrength() const;			// gets strength member variable of creature
	int getHitPoints() const;			// gets hitpoints member variable of creature

	// mutator functions
	void setStrength(int newStrength);	// sets creatures strength
	void setHitpoints(int newHit);		// sets creatures hitpoints
	int getDamage();					// returns amount of damage this creature inflicts in one round of combat
};
#endif
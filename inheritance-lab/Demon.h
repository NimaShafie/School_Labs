#pragma once
#pragma
#ifndef DEMON_H
#define DEMON_H
#include "Creature.h"

#include <iostream>

class Demon : public Creature {		// Demon is a dervied abstract class of Creature
private:
	int strength;								// How much damage we can inflict
	int hitpoints;								// How much damage we can sustain
	string getSpecies();			// returns type of species
public:
	// constructor/destructors
	Demon();									// default constructor
	Demon(int newStrength, int newHit);			// 2 int constructor (creates creature object with strength and hitpoints given in argument)
	Demon(const Demon& copyFromCreature);		// copy constructor
	~Demon();									// destructor

	// accessor functions
	int getStrength() const;					// gets strength member variable of creature
	int getHitPoints() const;					// gets hitpoints member variable of creature

	// mutator functions
	void setStrength(int newStrength);			// sets creatures strength
	void setHitpoints(int newHit);				// sets creatures hitpoints
	int getDamage();							// returns amount of damage this creature inflicts in one round of combat
};
#endif
#pragma once
#pragma
#ifndef ELF_H
#define ELF_H
#include "Creature.h"

#include <iostream>

class Elf : public Creature {		// Elf is a dervied class of Creature
private:
	int strength;           // how much damage we can inflict
	int hitpoints;          // how much damage we can sustain
	string getSpecies();    // returns type of species
public:
	// constructors/destructors
	Elf();									// default constructor
	Elf(int newStrength, int newHit);		// 2 argument constructor
	Elf(const Elf& copyFromCreature);		// copy constructor
	~Elf();									// destructor

	// accessor functions
	int getStrength() const;			// gets strength member variable of creature
	int getHitPoints() const;			// gets hitpoints member variable of creature

	// mutator functions
	void setStrength(int newStrength);	// sets creatures strength
	void setHitpoints(int newHit);		// sets creatures hitpoints
	int getDamage();					// returns amount of damage this creature inflicts in one round of combat
};
#endif
#pragma
// LAB 7 SHAFIE,Nima W
#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
using namespace std;

class Creature {								// creature is an abstract class used for inheritance
private:
	int strength;								// how much damage we can inflict
	int hitpoints;								// how much damage we can sustain
	virtual string getSpecies() = 0;			// returns type of species
public:
	// constructor/destructors
	Creature();									// default constructor
	Creature(int newStrength, int newHit);		// 2 int constructor (creates creature object with strength and hitpoints given in argument)
	Creature(const Creature& copyFromCreature);	// copy constructor
	virtual ~Creature() = 0;					// destructor

	// accessor functions
	int getStrength() const;					// gets strength member variable of creature
	int getHitPoints() const;					// gets hitpoints member variable of creature

	// mutator functions
	void setStrength(int newStrength);			// sets creatures strength
	void setHitpoints(int newHit);				// sets creatures hitpoints
	virtual int getDamage() = 0;				// returns amount of damage this creature inflicts in one round of combat
};
#endif
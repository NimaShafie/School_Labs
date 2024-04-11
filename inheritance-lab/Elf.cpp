#pragma
// LAB 7 SHAFIE,Nima W
#include <iostream>
#include <string>
#include "Elf.h"
using namespace std;

// default constructor will set strength and hitpoints of creature to 10
Elf::Elf()
{
	strength = 35;           // how much damage we can inflict
	hitpoints = 15;          // how much damage we can sustain
	cout << getSpecies() << "\t\tStrength: " << strength << "\tHitpoints: " << hitpoints << endl;
}

// 2 int constructor will set creatures strength and hit points according to entered arguments
Elf::Elf(int newStrength, int newHit)
{
	strength = newStrength;
	hitpoints = newHit;
	cout << getSpecies() << "\t\tStrength: " << strength << "\tHitpoints: " << hitpoints << endl;
}

// copy constructor that will copy creatures strength and hitpoints
Elf::Elf(const Elf& copyFromCreature)
{
	strength = copyFromCreature.strength;
	hitpoints = copyFromCreature.hitpoints;
}

// destructor will simply reset values of strength and hitpoints to 1
Elf::~Elf()
{
	cout << "\nElf destructor run!";
	strength = 1;
	hitpoints = 1;
}


// accessor functions


// gets strength member variable of creature
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain strength
// post -> will return strength equal to default creature class unless object was intitalized and strength have been set via argument on 2 int constructor
int Elf::getStrength() const
{
	return strength;
}

// gets hitpoints member variable of creature
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain hitpoints
// post -> will return hitpoints equal to default creature class unless object was intitalized and hitpoints have been set via argument on 2 int constructor
int Elf::getHitPoints() const
{
	return hitpoints;
}


// mutator functions


// gets strength member variable of creature
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain strength
// post -> will return strength equal to default creature class unless object was intitalized and strength have been set via argument on 2 int constructor
void Elf::setStrength(int newStrength)
{
	strength = newStrength;
}

// every creature inflicts damage that is a random number r, where 0 < r <= strength
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain hitpoints
// post -> will return hitpoints equal to default creature class unless object was intitalized and hitpoints have been set via argument on 2 int constructor
void Elf::setHitpoints(int newHitpoints)
{
	hitpoints = newHitpoints;
}

// every creature inflicts damage that is a random number r, where 0 < r <= strength
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain strength
// post -> will return a random number based on creature class equal to the amount of damage creature deals based on strength
int Elf::getDamage()
{
	// Elves have a 10% chance to inflict a magical attack that doubles the normal amount of damage.
	int damage;
	damage = (rand() % strength) + 1;
	cout << getSpecies() << " attacks for " << damage << " points!" << endl;
	if ((rand() % 10) == 0) {
		cout << "Magical attack inflicts " << damage << " additional damage points!" << endl;
		damage = damage * 2;
	}
	return damage;
}

// used to return class of creature, this function is used within getDamage() function
// pre -> none
// post -> will return the species of the creature depending on the class they were initialized as
string Elf::getSpecies() {
	string species = "Elf";
	return species;
}

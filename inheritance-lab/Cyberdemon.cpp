#pragma
// LAB 7 SHAFIE,Nima W
#include <iostream>
#include <string>
#include "Cyberdemon.h"
using namespace std;

// default constructor will set strength and hitpoints of creature
Cyberdemon::Cyberdemon()
{
	strength = 25;           // how much damage we can inflict
	hitpoints = 30;          // how much damage we can sustain
	cout << getSpecies() << "\tStrength: " << strength << "\tHitpoints: " << hitpoints << endl;
}

// 2 int constructor will set creatures strength and hit points according to entered arguments
Cyberdemon::Cyberdemon(int newStrength, int newHit)
{
	strength = newStrength;
	hitpoints = newHit;
	cout << getSpecies() << "\t\tStrength: " << strength << "\tHitpoints: " << hitpoints << endl;
}

// copy constructor that will copy creatures strength and hitpoints
Cyberdemon::Cyberdemon(const Cyberdemon& copyFromCreature)
{
	strength = copyFromCreature.strength;
	hitpoints = copyFromCreature.hitpoints;
}

// destructor will simply reset values of strength and hitpoints to 1
Cyberdemon::~Cyberdemon()
{
	cout << "\nCyberdemon destructor run!";
	strength = 1;
	hitpoints = 1;
}


// accessor functions


// gets strength member variable of creature
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain strength
// post -> will return strength equal to default creature class unless object was intitalized and strength have been set via argument on 2 int constructor
int Cyberdemon::getStrength() const
{
	return strength;
}

// gets hitpoints member variable of creature
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain hitpoints
// post -> will return hitpoints equal to default creature class unless object was intitalized and hitpoints have been set via argument on 2 int constructor
int Cyberdemon::getHitPoints() const
{
	return hitpoints;
}


// mutator functions


// gets strength member variable of creature
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain strength
// post -> will return strength equal to default creature class unless object was intitalized and strength have been set via argument on 2 int constructor
void Cyberdemon::setStrength(int newStrength)
{
	strength = newStrength;
}

// every creature inflicts damage that is a random number r, where 0 < r <= strength
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain hitpoints
// post -> will return hitpoints equal to default creature class unless object was intitalized and hitpoints have been set via argument on 2 int constructor
void Cyberdemon::setHitpoints(int newHitpoints)
{
	hitpoints = newHitpoints;
}

// every creature inflicts damage that is a random number r, where 0 < r <= strength
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain strength
// post -> will return a random number based on creature class equal to the amount of damage creature deals based on strength
int Cyberdemon::getDamage()
{
	//Every creature inflicts damage that is a random number r, where 0 < r <= strength
	// All creatures inflict damage, which is a random number up to their strength
	int damage;
	damage = (rand() % strength) + 1;
	// Demons can inflict damage of 50 with a 5% chance
	if ((rand() % 100) < 5) {
		damage = damage + 50;
		cout << "Demonic attack inflicts 50 additional damage points!" << endl;
	}
	cout << getSpecies() << " attacks for " << damage << " points!" << endl;
	return damage;
}

// used to return class of creature, this function is used within getDamage() function
// pre -> none
// post -> will return the species of the creature depending on the class they were initialized as
string Cyberdemon::getSpecies() {
	string species = "Cyberdemon";
	return species;
}
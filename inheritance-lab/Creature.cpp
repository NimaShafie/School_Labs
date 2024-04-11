#pragma
#include <iostream>
#include <string>
#include "Creature.h"
using namespace std;

// default constructor will set strength and hitpoints of creature to 10
Creature::Creature()
{
    // this runs anytime a derived classes constructor runs
    strength = 10;           // how much damage we can inflict
    hitpoints = 10;          // how much damage we can sustain
}

// 2 int constructor will set creatures strength and hit points according to entered arguments
Creature::Creature(int newStrength, int newHit)
{
    strength = newStrength;
    hitpoints = newHit;
}

// copy constructor that will copy creatures strength and hitpoints
Creature::Creature(const Creature& copyFromCreature)
{
    strength = copyFromCreature.strength;
    hitpoints = copyFromCreature.hitpoints;
}

// destructor will simply reset values of strength and hitpoints to 1
Creature::~Creature()
{
    //cout << "\nCreature destructor run!";
    strength = 1;
    hitpoints = 1;
}


// accessor functions


// gets strength member variable of creature
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain strength
// post -> will return strength equal to default creature class unless object was intitalized and strength have been set via argument on 2 int constructor
int Creature::getStrength() const
{
    return strength;
}

// gets hitpoints member variable of creature
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain hitpoints
// post -> will return hitpoints equal to default creature class unless object was intitalized and hitpoints have been set via argument on 2 int constructor
int Creature::getHitPoints() const
{
    return hitpoints;
}


// mutator functions


// gets strength member variable of creature
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain strength
// post -> will return strength equal to default creature class unless object was intitalized and strength have been set via argument on 2 int constructor
void Creature::setStrength(int newStrength)
{
    strength = newStrength;
}

// every creature inflicts damage that is a random number r, where 0 < r <= strength
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain hitpoints
// post -> will return hitpoints equal to default creature class unless object was intitalized and hitpoints have been set via argument on 2 int constructor
void Creature::setHitpoints(int newHitpoints)
{
    hitpoints = newHitpoints;
}


// every creature inflicts damage that is a random number r, where 0 < r <= strength
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain strength
// post -> will return a random number based on creature class equal to the amount of damage creature deals based on strength
int Creature::getDamage()
{
    /*
    Every creature inflicts damage that is a random number r, where 0 < r <= strength.
    Demons have a 5% chance of inflicting a demonic attack, which is an additional 50 damage points. Balrogs and Cyberdemons are demons.
    Elves have a 10% chance to inflict a magical attack that doubles the normal amount of damage.
    Balrogs are very fast, so they get to attack twice.
    All creatures inflict damage, which is a random number up to their strength
    */
    int damage;
    damage = (rand() % strength) + 1;
    cout << getSpecies() << " attacks for " << damage << " points!" << endl;
    return damage;
}

// used to return class of creature, this function is used within getDamage() function
// pre -> none
// post -> will return the species of the creature depending on the class they were initialized as
string Creature::getSpecies() {
    string species = "Creature";
    return species;
}

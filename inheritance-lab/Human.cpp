#pragma
#include <iostream>
#include <string>
#include "Human.h"
using namespace std;

// default constructor will set strength and hitpoints of creature to 10
Human::Human()
{
    strength = 10;           // how much damage we can inflict
    hitpoints = 10;          // how much damage we can sustain
    cout << getSpecies() << "\t\tStrength: " << strength << "\tHitpoints: " << hitpoints << endl;
}

// 2 int constructor will set creatures strength and hit points according to entered arguments
Human::Human(int newStrength, int newHit)
{
    strength = newStrength;
    hitpoints = newHit;
    cout << getSpecies() << "\t\tStrength: " << strength << "\tHitpoints: " << hitpoints << endl;
}

// copy constructor that will copy creatures strength and hitpoints
Human::Human(const Human& copyFromCreature)
{
    strength = copyFromCreature.strength;
    hitpoints = copyFromCreature.hitpoints;
}

// destructor will simply reset values of strength and hitpoints to 1
Human::~Human()
{
    cout << "\nHuman destructor run!";
    strength = 1;
    hitpoints = 1;
}


// accessor functions


// gets strength member variable of creature
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain strength
// post -> will return strength equal to default creature class unless object was intitalized and strength have been set via argument on 2 int constructor
int Human::getStrength() const
{
    return strength;
}

// gets hitpoints member variable of creature
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain hitpoints
// post -> will return hitpoints equal to default creature class unless object was intitalized and hitpoints have been set via argument on 2 int constructor
int Human::getHitPoints() const
{
    return hitpoints;
}


// mutator functions


// gets strength member variable of creature
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain strength
// post -> will return strength equal to default creature class unless object was intitalized and strength have been set via argument on 2 int constructor
void Human::setStrength(int newStrength)
{
    strength = newStrength;
}

// every creature inflicts damage that is a random number r, where 0 < r <= strength
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain hitpoints
// post -> will return hitpoints equal to default creature class unless object was intitalized and hitpoints have been set via argument on 2 int constructor
void Human::setHitpoints(int newHitpoints)
{
    hitpoints = newHitpoints;
}

// every creature inflicts damage that is a random number r, where 0 < r <= strength
// pre -> run default constructor or 2 int constructor with valid data (we're not checking here) to obtain strength
// post -> will return a random number based on creature class equal to the amount of damage creature deals based on strength
int Human::getDamage()
{
    int damage;
    damage = (rand() % strength) + 1;
    cout << getSpecies() << " attacks for " << damage << " points!" << endl;
    return damage;
}

// used to return class of creature, this function is used within getDamage() function
// pre -> none
// post -> will return the species of the creature depending on the class they were initialized as
string Human::getSpecies() {
    string species = "Human";
    return species;
}

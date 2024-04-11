// Nima Shafie
#pragma once
#include <iostream>
#include <string>
#include "Creature.h"
#include "Human.h"
#include "Elf.h"
#include "Demon.h"
#include "Cyberdemon.h"
#include "Balrog.h"

using namespace std;

void twoConstructorTest();

int inheritanceMain() {
	// In main, create an array of pointers to a base abstract Creatures class
	int* ptrInt = nullptr;
	int numOfDerivedClasses = 4;
	Creature** creatureArray;

	try {
		creatureArray = new Creature * [numOfDerivedClasses];
		creatureArray[0] = new Human;
		creatureArray[1] = new Elf;
		creatureArray[2] = new Cyberdemon;
		creatureArray[3] = new Balrog;
		cout << "\n\n";
		} catch (bad_alloc&) {
	cout << "Error: Dynamic Memory Allocation Failed.\nProgram Terminating.\n" << endl;
	return 0;
	}

	// testing humans
	int dmgHuman = creatureArray[0]->getDamage();
	int newHumanStrength = 5;
	cout << "Setting a new strength to Human with setStrength() function, (current human health = 10) ";
	creatureArray[0]->setStrength(newHumanStrength);
	cout << "\nDisplaying new Human strength with getStrength() function: " << creatureArray[0]->getStrength() << endl;

	cout << endl;

	// testing elves
	Elf elf;
	int dmgElf = elf.getDamage(); 
	int newElfHitpoints = 5;
	cout << "Setting new hitpoints to Elf with getHitPoints() function, (current elf health = 15) ";
	elf.setHitpoints(newElfHitpoints);
	cout << "\nDisplaying new Elf hitpoints with getHitPoints() function: " << elf.getHitPoints() << endl;

	cout << endl;

	// testing cyberdemons
	Cyberdemon cyberdemon;
	int dmgCyberdemon = cyberdemon.getDamage();

	cout << endl;
	Balrog balrog;
	int dmgBalrog = balrog.getDamage();
	cout << "\n\n";

	twoConstructorTest();
	cout << "\n\n\nAttempting to delete array of pointers to base class:\n";
	for (int i = 0; i < numOfDerivedClasses; i++) {
		cout << "\nDeleting creatureArray[" << i << "] now";
		delete creatureArray[i];
	}
	delete[]creatureArray;
	cout << "\nNow program terminates (2 argument destructors will run past this line)\n" << endl;
	return 0;
}

void twoConstructorTest() {
	// testing 2 argument constructors here
	cout << "Testing 2 argument constructors here\n";
	Human human2(25, 8);
	int dmgHuman2 = human2.getDamage();

	cout << endl;

	Elf elf2(40, 5);
	int dmgElf2 = elf2.getDamage();

	cout << endl;

	Cyberdemon cyberdemon2(10, 50);
	int dmgCyberdemon2 = cyberdemon2.getDamage();

	cout << endl;

	Balrog balrog2(20, 30);
	int dmgBalrog2 = balrog2.getDamage();
}
// Nima Shafie
#pragma once
#include <iostream>
#include <exception>
using namespace std;

// node struct
struct Node {
	int data;
	Node* next;
};

// class for linked list
class LinkedList {
private:
	Node* head;
	Node* tail;

public:
	LinkedList();			// default ctor
	~LinkedList();			// dtor
	// displays the remaining number of players (nodes) on linked list
	int numberOfPlayersRemaining(LinkedList& linkList) const;
	// returns the current head node of a given circular linked list
	Node* returnHeadNode(LinkedList&) const;
	// -------------------------------------------------------------------------------------
	// adds a new node to the end of a given linked list
	void appendList(LinkedList& linkList, int& playerNumber);
	//traverses through nodes in given linked list object, from the most recent player, cycling to the player we will remove
	Node* startPassing(LinkedList&, int numberOfPasses, Node* continueFromHere);
	// given a player # to remove, removes that players and starts "passing" once more 1 node after the removed player
	void removePlayer(LinkedList&, Node* playerToRemove, Node* playerToStartFrom);
	// given a node, sets the given node as the new head (used for when previous head player has been removed)
	void setNewHeadNode(LinkedList&, Node* newHeadToSet);
};

// default ctor (will set head & tail pointers to nullptr)
LinkedList::LinkedList() {
	head = nullptr;
	tail = nullptr;
}

// destructor used to reset nodes (nodes are deleted with "delete" keyword in removePlayer function)
LinkedList::~LinkedList() {
	head = nullptr;
	tail = nullptr;
}

// ************************************************************** const accessor function defintions below

/*
description: returns the number of nodes(players) remaining in a given circular linked list
pre -> must be passed a non-empty circular linked list object
post -> returns an int of the number of nodes (players) remaining*/
int LinkedList::numberOfPlayersRemaining(LinkedList& linkList) const {
	Node* scanPlayers;
	scanPlayers = head;
	int numberOfPlayers = 0;
	do {
		numberOfPlayers++;
		scanPlayers = scanPlayers->next;
	} while (scanPlayers != head);
	return numberOfPlayers;
}

/*
description: returns the current head node of a given circular linked list
pre -> must be passed a non-empty circular linked list object
post -> returns the head node
*/
Node* LinkedList::returnHeadNode(LinkedList&) const {
	Node* headNode;
	headNode = head;
	return headNode;
}

// ************************************************************** mutator function defintions below

/*
description: appends a new node to a linked list
pre -> an object of class LinkedList must exist and be passed, pass the player number associated to be added
post -> will add a new node to the linked list object (if linked list object is empty,
will create a head node and point head & tail nodes accordingly)
*/
void LinkedList::appendList(LinkedList& linkList, int& playerNumber) {
	try {
		// new nodes will be deleted (released) from memory in removePlayer function
		Node* newNode = new Node;
		newNode->data = playerNumber;
		newNode->next = nullptr;

		if (head == nullptr) {
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = tail->next;
			tail->next = head;
		}
	}
	catch (bad_alloc&) {
		cout << "Could not dynamically allocate memory to append anymore players (nodes) "
			" to our linked list, program will terminate.";
		exit(-1);
	}
}

/*
description: traverses through nodes in given linked list object(depending on number of passes passed)
from the most recent player to obtain the hot potato, cycling to the player we will remove
pre -> must be passed a non-empty linked list object, must be passed number of passes from main,
must be passed a node to continue traversing from (last player)
post -> returns the player (node) that has been selected to be removed from the game (hot potato!)
*/
Node* LinkedList::startPassing(LinkedList&, int numberOfPasses, Node* continueFromHere) {
	Node* passNode;
	passNode = head;
	// first we must locate the player that we will continue passing from (passed by our main)
	while (passNode != continueFromHere) {
		passNode = passNode->next;						// iterate through our linked list
	}
	// start passing (traversing) through our list of players until we've reached the number of passes specified
	for (int i = 0; i != numberOfPasses; i++) {
		passNode = passNode->next;
	}
	// output the message that player X has been eliminated
	cout << "Player " << passNode->data << " has been eliminated." << endl;
	return passNode;	// returns the player (node) that we will be using to pass to our removePlayer function
}

/*
description: given a non - empty linked list object, a player to remove, and a player to continue from,
will remove the player from the object, and continue from next node given(for iteration for hot potato)
pre -> must be passed a linked list object with at least two players (nodes),
a player to remove (node to remove), and a player to start from (node to continue from)
post -> will remove given playerToRemove node, and link pervious node to next node
*/
void LinkedList::removePlayer(LinkedList&, Node* playerToRemove, Node* playerToStartFrom) {
	Node* afterPlayer;			// successor node to our node to be removed
	Node* beforePlayer;			// predecessor node of our node to be removed
	beforePlayer = head;		// initailizing our predecessor node to be searching from head node (base)
	// searching for the node we want to remove (which is the next node after our beforePlayer node)
	while (beforePlayer->next->data != playerToRemove->data) {
		// setting our headNode search index to the next node in line to compare further
		beforePlayer = beforePlayer->next;
	}
	// initalizing successor node to be the node after the node we want to remove
	afterPlayer = playerToRemove->next;
	delete playerToRemove;			// deleting (freeing) player from memory
	// we will return the successor node as the player to continue passing from once we remove
	playerToStartFrom = afterPlayer;
	// setting our predecssor node to our successor node, thus eliminating our "playerToRemove" node from linked list
	beforePlayer->next = afterPlayer;
}

/*
description: when passed the argument node with linked list object, will set the given node to the head of the linked list object
pre -> must be passed a non-empty linked list object, and a player (new head node) that will become the new head
post -> will set a player as the new head (will change a current node to the head node)
*/
void LinkedList::setNewHeadNode(LinkedList&, Node* newHeadToSet) {
	newHeadToSet = head;
	head = newHeadToSet->next;
}

int hotPotatoMain() {
	char restartProgram = 'z';
	while (restartProgram != 'n' && restartProgram != 'N') {
		// creating an object of the LinkedList class 'linkList' as our linked list
		LinkedList linkList;
		int numberOfPlayers = 0;
		int numberOfPasses = 0;
		cout << "Hot Potato!\n\n";
		do {
			cout << "Enter number of players: ";
			cin >> numberOfPlayers;
			if (numberOfPlayers <= 1) cout << "\nInvalid number of players, must have more than 1 player to continue\n";
		} while (numberOfPlayers <= 1);
		do {
			cout << "Enter number of passes: ";
			cin >> numberOfPasses;
			if (numberOfPasses < 0) cout << "\nInvalid number of passes, passes must be a positive number to continue\n";
		} while (numberOfPasses < 0);
		cout << "\nSo, we're playing with " << numberOfPlayers << " players, and passing the potato "
			<< numberOfPasses << " time(s) per player, let's start!\n" << endl;
		// will iterate through number of players starting from 1
		for (int i = 1; i < (numberOfPlayers + 1); i++) {
			// and generate player list by calling the append function each time to add a player
			linkList.appendList(linkList, i);
		}
		Node* toRemove;					// used as the "to delete" player node
		// used to continue passing (play the game) after a player is removed from the game
		Node* playerToContinueFrom;
		// one time initialization of setting the player to continue from as our head node (starting from player 1)
		playerToContinueFrom = linkList.returnHeadNode(linkList);
		// will be used to count how many players (nodes) are left in our linked list object
		int playersLeft = linkList.numberOfPlayersRemaining(linkList);
		// will perform this as long as there isn't only 1 player reamining
		while (playersLeft != 1) {
			// the player (node) to remove will be set to the toRemove node object
			toRemove = linkList.startPassing(linkList, numberOfPasses, playerToContinueFrom);
			// if we are to delete/remove our current head node, we will set a new head node according to the next player in line
			if (toRemove == linkList.returnHeadNode(linkList)) linkList.setNewHeadNode(linkList, toRemove);
			// initialziing our next player (successor node) as the player (node) after the one that is removed
			playerToContinueFrom = toRemove->next;
			// will remove "toRemove" player (node) and continue from the next player (successor node) in line
			linkList.removePlayer(linkList, toRemove, playerToContinueFrom);
			// setting our new count of how many players (nodes) exist in our linked list object
			playersLeft = linkList.numberOfPlayersRemaining(linkList);
		}
		// will hold our only node (head node) as the victorious player
		playerToContinueFrom = linkList.returnHeadNode(linkList);
		cout << "\nOur winner is Player " << playerToContinueFrom->data << ", congratulations!!\n\n";
		delete playerToContinueFrom;	// deleting (freeing) our last node in the linked list
		do {
			cout << "Would you like to play a new game? (Type 'n' or 'N' to quit program, and 'y' or 'Y' to continue): ";
			cin >> restartProgram;
		} while (restartProgram != 'n' && restartProgram != 'N' && restartProgram != 'y' && restartProgram != 'Y');
	}
	cout << "\nProgram ended successfully.\n\n";
	return 0;
}
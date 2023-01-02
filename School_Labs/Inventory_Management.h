// Nima Shafie
// All fields in the input file are separated by a tab (‘\t’)
// all "item names" are to be one word (no spaces)
#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// global const variables
const string INPUTFILE = "C:/temp/cs136.txt";
const string ERRORFILE = "C:/temp/cs136-errorfile.txt";
const int ARRSIZE = 100;

// struct declaration
struct Inventory {
	string itemID;
	string itemName = "";
	int stockPresent;
	float itemPrice;
};

// function declaration
// opens data file to read & sort
void readData(Inventory inventory[], int& numOfItems);
// checks for input data file presence
bool checkForInputFilePresent();
// prints inventory in an unsorted order (FIFO)
void unsortedInventory(Inventory inventory[], int numOfItems);
// print inventory in ascending order, allow user to search by any field
void sortedInventory(Inventory* arrayPointers[], int numOfItems);
// helper function to sortedInventory (uses bubble sorting to tidy up our list)
void initalizeBubbleSort(Inventory* arrayPointers[], int numOfItems, int searchField);
// bubble sort used to the ascending menu option
void bubbleSort(int searchField, int numOfItems, Inventory* arrayPointers[]);
// searches for an item by ID/name (can use upper or lower case when searching)
void searchIDName(Inventory* inventory, int numOfItems);
// turns given string into lower case for sorting purposes
void lowercaseIt(string& inputGiven);
// will print number of unique items, total worth of the inventory, total count of all items in inventory
void printReport(Inventory* inventory, int numOfItems);
// used to display the sorted menu after bubble sorting is completed
void displaySortedObject(Inventory* arrayPointers[], int numOfItems);

int inventoryMain() {
	// array of structures declared (size based off global const ARRSIZE)
	Inventory inventory[ARRSIZE];
	int numOfItems = 0;

	// open and read data, (sorts valid data and splits invalid data)
	readData(inventory, numOfItems);

	// creating array of pointers
	Inventory* arrayPointers[ARRSIZE];
	for (int i = 0; i < numOfItems; i++) {
		arrayPointers[i] = &inventory[i];
	}

	int choice = 1;
	while (choice != 5) {
		cout << "\nPlease select how you would like to view the product list.\n"
			"\n1. Unsorted"
			"\n2. Sorted in Ascending Order (Item ID/Item Name/Quantity on Hand/Price)"
			"\n3. By ID/Name"
			"\n4. Unique Items/Total Inventory Worth"
			"\n5. Exit program\n" << endl;
		cin >> choice;
		switch (choice) {
		case 1:		// unsorted
			unsortedInventory(inventory, numOfItems);
			break;
		case 2:		// sorted
			sortedInventory(arrayPointers, numOfItems);
			break;
		case 3:		// ID/name (not case sensitive)
			searchIDName(inventory, numOfItems);
			break;
		case 4:		// exit program
			printReport(inventory, numOfItems);
			break;
		case 5:		// ID/name (not case sensitive)
			cout << "\nQuitting program.\n";
			break;
		default:
			cout << "\nInvalid choice, select again.\n" << endl;
		}
	}
	cout << "\nProgram ended successfully.\n";
	return 0;
}

/* one record per line in the following  order : item ID, item  name(one word), quantity on hand, and a price.
Read data from file located in: INPUTFILE global const
*/
void readData(Inventory inventory[], int& numOfItems) {
	fstream openedFile;									// will be used to read from file
	ofstream outputErrorFile;							// will be used to output errors
	bool checkForFile = checkForInputFilePresent();		// will be used to check if input file is present and in correct local directory.
	if (!checkForFile) exit(-1);						// will exit if input file is not found
	openedFile.open(INPUTFILE);							// open input file
	outputErrorFile.open(ERRORFILE, ios_base::app);		// open error file (and append)
	numOfItems = 0;

	// where we assign our data from the file to
	string readAndConvertItemID = "";					// used to read item ID # (assuming it only contains numbers)
	string readItemName = "";							// used to read in the item name
	int readAndConvertStockPresent;						// used to read in quantity on hand
	float readItemPrice;								// used to read in the price of the item
	bool validRecord = true;							// used to determine if data is valid or not
	bool triggerErrorFile = false;						// once this turns on, we will create the error file
	int validRecordCount = 0;							// how many valid records we processed from helper function 'sortValidateFile'

	//  check the record if the entire record is valid, then copy it into array of structs after
	while (openedFile && numOfItems != ARRSIZE)
	{
		openedFile >> readAndConvertItemID >> readItemName >> readAndConvertStockPresent >> readItemPrice;	// reading in data from file

		lowercaseIt(readItemName);		// turns given item name with mixed casing into all lower casing for sorting purposes

		// check if data is valid here - item price & quantity cannot be negative
		if (readItemPrice < 0 || readAndConvertStockPresent < 0) {
			triggerErrorFile = true;					// will create the error file here
			validRecord = false;

			// print the record to the error file
			outputErrorFile << readAndConvertItemID << "\t" << readItemName << "\t"
				<< readAndConvertStockPresent << "\t" << readItemPrice << "\n";
		}

		if (validRecord) {			// only record data if valid, we will be adding data into dummy struct first
			inventory[numOfItems].itemID = readAndConvertItemID;		// setting variables here
			inventory[numOfItems].itemName = readItemName;
			inventory[numOfItems].stockPresent = readAndConvertStockPresent;
			inventory[numOfItems].itemPrice = readItemPrice;
			numOfItems++;
		}
		validRecord = true;
		openedFile.ignore();		// need to ignore last line
	}
	if (openedFile && numOfItems == ARRSIZE) cout << "Not enough space to store all records, only obtained first "
		<< ARRSIZE << " records." << endl;
	openedFile.close();
	outputErrorFile.close();
	if (triggerErrorFile) cout << "Some records were not able to be processed, check error file located in: '"
		<< ERRORFILE << "' for more info." << endl;
	cout << "Number of items recorded: " << numOfItems << endl;
}

bool checkForInputFilePresent() {
	fstream openedFile;							// will be used to read from file
	openedFile.open(INPUTFILE);					// attempt to open file here
	if (!openedFile) {							// if we cannot find file, inform user and exit
		cout << "File: '" << INPUTFILE << "' could not be located/opened, program will terminate." << endl;
		return false;
	}
	return true;
}

/* view list functions below
prints inventory unsorted (FIFO) style
*/
void unsortedInventory(Inventory inventory[], int numOfItems) {
	cout << "Unsorted List----------------------" << endl;
	for (int i = 0; i < numOfItems; i++) {
		cout << inventory[i].itemID << setfill(' ') << setw(20)
			<< inventory[i].itemName << setfill(' ') << setw(10)
			<< inventory[i].stockPresent << setfill(' ') << setw(10)
			<< inventory[i].itemPrice << endl;
	}
}

// will display the sorted inventory and prompt user to select which item to sort by
void sortedInventory(Inventory* arrayPointers[], int numOfItems) {
	int choice = 1;
	while (choice != 5) {
		cout << "Sorted List---------------------- \n"
			<< "Select which category you would like to sort by\n"
			"1. Item ID\n"
			"2. Item Name (One Word)\n"
			"3. Quantity on Hand\n"
			"4. Price\n"
			"5. Return to Previous Menu\n" << endl;
		cin >> choice;
		switch (choice) {
		case 1:		// Item ID
		case 2:		// Item Name (One Word)
		case 3:		// Quantity on Hand
		case 4:		// Price
			initalizeBubbleSort(arrayPointers, numOfItems, choice);
			break;
		case 5:		// Exit
			cout << "Return to main menu" << endl;
			break;
		default:
			cout << "\nInvalid choice, select again.\n" << endl;
		}
	}
}

// initiate the bubble sort, will create array of pointers, then will call the bubble sort function & display contents
void initalizeBubbleSort(Inventory* arrayPointers[], int numOfItems, int searchField) {
	bubbleSort(searchField, numOfItems, arrayPointers);
	displaySortedObject(arrayPointers, numOfItems);
}

// prints inventory unsorted (FIFO) style
void displaySortedObject(Inventory* arrayPointers[], int numOfItems) {
	cout << "----------------------" << endl;
	for (int i = 0; i < numOfItems; i++) {
		cout << arrayPointers[i]->itemID << setfill(' ') << setw(20)
			<< arrayPointers[i]->itemName << setfill(' ') << setw(10)
			<< arrayPointers[i]->stockPresent << setfill(' ') << setw(10)
			<< arrayPointers[i]->itemPrice << "\n";
	}
	cout << endl;
}

// bubble sort for ascending fields option, using a switch menu and arguments for selecting which field to sort by
void bubbleSort(int searchField, int numOfItems, Inventory* arrPtr[]) {
	// create an empty temporary struct that can hold values temporarly for bubble sort swap
	Inventory* temp[ARRSIZE];
	bool makeSwap = true;
	bool startLoop = true;
	while (startLoop) {
		startLoop = false;
		makeSwap = false;
		for (int j = 0; j < (numOfItems - 1); j++) {
			makeSwap = false;
			// switch menu to determine which member variable we will sort by
			switch (searchField) {
			case 1:
				// check if current pointer value is greater than pointer + 1
				// (if so, change makeSwap to true and re run to scan for more swappable elements)
				makeSwap = arrPtr[j]->itemID > arrPtr[j + 1]->itemID;
				break;
			case 2:
				makeSwap = arrPtr[j]->itemName > arrPtr[j + 1]->itemName;
				break;
			case 3:
				makeSwap = arrPtr[j]->stockPresent > arrPtr[j + 1]->stockPresent;
				break;
			case 4:
				makeSwap = arrPtr[j]->itemPrice > arrPtr[j + 1]->itemPrice;
				break;
			}
			if (makeSwap) {
				startLoop = true;
				temp[j] = arrPtr[j];
				arrPtr[j] = arrPtr[j + 1];
				arrPtr[j + 1] = temp[j];
			}
		}
	}
}

// will take any given case characters and turn into lower case
void lowercaseIt(string& inputGiven) {
	// used to set all item name characters to lower case
	char fixItemNameCase;
	// turns all characters entered in 'name' into lowercase for sorting purposes
	for (int i = 0; (unsigned)i < inputGiven.length(); ++i) {
		fixItemNameCase = inputGiven[i];
		inputGiven[i] = tolower(fixItemNameCase);
	}
}

// will search either according to item ID or item name
void searchIDName(struct Inventory* inventory, int numOfItems) {
	bool wasFound = false;								// used to return back if search was found or not
	string selection;									// user will enter input here
	cout << "Enter in Item ID/Item Name to search through inventory for corresponding item" << endl;
	cin >> selection;
	lowercaseIt(selection);			// turns entered string into lower case for sorting purposes
	bool found = false;
	int count = 0;
	for (; count < numOfItems && !found; count++) {
		found = selection == inventory[count].itemID || selection == inventory[count].itemName;
	}
	if (found) {
		cout << "\nItem ID \t Name \t Price \t Stock Present\n"
			<< inventory[count - 1].itemID << setfill(' ') << setw(12) <<
			inventory[count - 1].itemName << setfill(' ') << setw(12)

			<< inventory[count - 1].itemPrice << setfill(' ') << setw(12) <<
			inventory[count - 1].stockPresent << setfill(' ') << setw(12) << endl;
		wasFound = true;
	}
	else {
		cout << "\nItem was not found, invalid item ID/Name." << endl;
	}
}

/* will print number of unique items(according to item ID) and
  total worth of the inventory and total count of all items in the inventory
 */
void printReport(struct Inventory* inventory, int numOfItems) {
	int itemCount = 0;
	float totalWorth = 0.0;
	for (int i = 0; i < numOfItems; i++) {
		itemCount += inventory[i].stockPresent;
		totalWorth += (inventory[i].stockPresent * inventory[i].itemPrice);
	}
	cout << "Print Report List---------------------- \n"
		"Number of Unique Items: " << numOfItems << "\n"
		"Total Worth: " << fixed << showpoint << setprecision(2) << totalWorth << "\n"
		"Total Count of all items: " << itemCount << "\n" << endl;
}

/*
Record sample:
997196478	StroLLer	25		134.78
997196281	Mop			20		38.99
997196810	rake		22		44.99
997196000	OveN		18		4.99
997186420	SinK		8		14.99
997186420	cAbinet		14		-44.99
997196001	hose		24		18.99
*/

// test data here
/*
Some records were not able to be processed, check error file located in: 'C:/temp/cs136-errorfile.txt' for more info.
Please select how you would like to view the product list.
1. Unsorted
2. Sorted in Ascending Order (Item ID/Item Name/Quantity on Hand/Price)
3. By ID/Name
4. Unique Items/Total Inventory Worth
5. Exit program
1
Unsorted List----------------------
997196478            stroller        25    134.78
997196281                 mop        20     38.99
997196810                rake        22     44.99
997196000                oven        18      4.99
997186420                sink         8     14.99
997196001                hose        24     18.99
Please select how you would like to view the product list.
1. Unsorted
2. Sorted in Ascending Order (Item ID/Item Name/Quantity on Hand/Price)
3. By ID/Name
4. Unique Items/Total Inventory Worth
5. Exit program
2
Sorted List----------------------
Select which category you would like to sort by
1. Item ID
2. Item Name (One Word)
3. Quantity on Hand
4. Price
5. Return to Previous Menu
1
----------------------
997186420                sink         8     14.99
997196000                oven        18      4.99
997196001                hose        24     18.99
997196281                 mop        20     38.99
997196478            stroller        25    134.78
997196810                rake        22     44.99
Sorted List----------------------
Select which category you would like to sort by
1. Item ID
2. Item Name (One Word)
3. Quantity on Hand
4. Price
5. Return to Previous Menu
2
----------------------
997196001                hose        24     18.99
997196281                 mop        20     38.99
997196000                oven        18      4.99
997196810                rake        22     44.99
997186420                sink         8     14.99
997196478            stroller        25    134.78
Sorted List----------------------
Select which category you would like to sort by
1. Item ID
2. Item Name (One Word)
3. Quantity on Hand
4. Price
5. Return to Previous Menu
3
----------------------
997186420                sink         8     14.99
997196000                oven        18      4.99
997196281                 mop        20     38.99
997196810                rake        22     44.99
997196001                hose        24     18.99
997196478            stroller        25    134.78
Sorted List----------------------
Select which category you would like to sort by
1. Item ID
2. Item Name (One Word)
3. Quantity on Hand
4. Price
5. Return to Previous Menu
4
----------------------
997196000                oven        18      4.99
997186420                sink         8     14.99
997196001                hose        24     18.99
997196281                 mop        20     38.99
997196810                rake        22     44.99
997196478            stroller        25    134.78
Sorted List----------------------
Select which category you would like to sort by
1. Item ID
2. Item Name (One Word)
3. Quantity on Hand
4. Price
5. Return to Previous Menu
5
Please select how you would like to view the product list.
1. Unsorted
2. Sorted in Ascending Order (Item ID/Item Name/Quantity on Hand/Price)
3. By ID/Name
4. Unique Items/Total Inventory Worth
5. Exit program
3
Enter in Item ID/Item Name to search through inventory for corresponding item
StRoLLer
Item ID          Name    Price   Stock Present
997196478    stroller      134.78          25
Please select how you would like to view the product list.
1. Unsorted
2. Sorted in Ascending Order (Item ID/Item Name/Quantity on Hand/Price)
3. By ID/Name
4. Unique Items/Total Inventory Worth
5. Exit program
3
Enter in Item ID/Item Name to search through inventory for corresponding item
997196281
Item ID          Name    Price   Stock Present
997196281         mop       38.99          20
Please select how you would like to view the product list.
1. Unsorted
2. Sorted in Ascending Order (Item ID/Item Name/Quantity on Hand/Price)
3. By ID/Name
4. Unique Items/Total Inventory Worth
5. Exit program
4
Print Report List----------------------
Number of Unique Items: 6
Total Worth: 5804.58
Total Count of all items: 117
Please select how you would like to view the product list.
1. Unsorted
2. Sorted in Ascending Order (Item ID/Item Name/Quantity on Hand/Price)
3. By ID/Name
4. Unique Items/Total Inventory Worth
5. Exit program
5
Quitting program.
Program ended successfully.
*/
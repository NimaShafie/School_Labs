// Nima Shafie
#include "Inventory_Management.h"
#include "Hot_Potato.h"
#include <iostream>

int main()
{
	int choice = 1;
    std::cout << "Initiating Lab Projects Now\n\n";
	while (choice != 5) {
		std::cout << "\nPlease select a lab to interact with\n"
			"\n1. Inventory Management"
			"\n2. Hot Potato (Linked Lists)"
			"\n3. .."
			"\n4. .."
			"\n5. Exit program\n" << endl;
		cin >> choice;
		switch (choice) {
		case 1:		// Inv Management
			inventoryMain();
			break;
		case 2:		// Hot Potato
			hotPotatoMain();
			break;
		case 3:
			//
			break;
		case 4:
			//
			break;
		case 5:
			std::cout << "\nQuitting program.\n";
			break;
		default:
			std::cout << "\nInvalid choice, select again.\n" << endl;
		}
	}
	std::cout << "\nProgram ended successfully.\n";
	return 0;
}
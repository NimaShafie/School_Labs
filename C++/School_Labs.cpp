// Nima Shafie
#include "Inventory_Management.h"
#include "Hot_Potato.h"
#include "Stack_Warehouse.h"
#include "Recursion.h"
#include <iostream>

int main()
{
	int choice = 1;
    std::cout << "Initiating Lab Projects Now\n\n";
	while (choice != 5) {
		std::cout << "\nPlease select a lab to interact with\n"
			"\n1. Inventory Management"
			"\n2. Hot Potato (Linked Lists)"
			"\n3. Stack Warehouse (Stack DS)"
			"\n4. Recursion"
			"\n5. Exit program\n" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			inventoryMain();
			break;
		case 2:
			hotPotatoMain();
			break;
		case 3:
			stackWarehouseMain();
			break;
		case 4:
			recursionMain();
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
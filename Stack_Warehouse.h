// Nima Shafie
#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

// global const functions (how we're limiting our stack size)
// stack size is really (STACK_SIZE + 1), so if you would like stack size == 10, you will need to input 11
const int STACK_SIZE = 101;

struct Deliveries_Orders {
	int orderNumber = 0;
	int widgetCount = 0;
	float price = 0.0;
};

class Stack {
private:
	int orderNumber;
	int deliveryNumber;
	int stackNumber;

public:
	// constructors/destructors
	Stack();
	~Stack();

	// direct stack related functions
	void push(Stack& stack, Deliveries_Orders deliverStack[], Deliveries_Orders orderStack[],
		string& deliveryOrOrder, int& orderNumber, int& widgetsToAccept, float pricePerWidget = 0);
	void pop(Stack& stack, Deliveries_Orders deliverStack[], Deliveries_Orders orderStack[],
		string& deliveryOrOrder, int& orderNumber, int& widgetsToAccept, float& pricePerWidget);
	void print(Stack& stack, Deliveries_Orders objStack[], string& deliveryOrOrder) const;
	bool isEmpty(Stack& stack, Deliveries_Orders objStack[]) const;
	bool isFull(Stack& stack);
	int lastElementOnStack(Stack& stack, Deliveries_Orders objStack[]);

	// helper functions
	void takeOrder(Stack& objOrder, Deliveries_Orders deliverStack[], Deliveries_Orders orderStack[]);
	void acceptDelivery(Stack& objDeliver, Deliveries_Orders deliveryStack[], Deliveries_Orders orderStack[]);
	void displayOrderDetails(Stack& stack, Deliveries_Orders deliverStack[], Deliveries_Orders orderStack[],
		string& deliveryOrOrder, int& orderNumber, int& widgetsToAccept, int& qtyShipped, float& pricePerWidget);
	int generateOrderNumber(string deliveryOrOrder);

	// accessor functions
	void displayDeliveries(Stack& objDeliver, Deliveries_Orders deliveryStack[]) const;
	void displayOrderOnHand(Stack& objDeliver, Deliveries_Orders deliveryStack[]) const;
};

// function declarations here
// constructors/destructors
Stack::Stack() {
	//cout << "Default Constructor Run!\n";
	orderNumber = 99;
	deliveryNumber = 499;
	stackNumber = 0;
}

// destructor
Stack::~Stack() {
	//cout << "Destructor called!\n";
}

// stack related functions here

/*stack function used to push an object on a given stack(delivery / order)
pre -> needs to be passed an object of a stack with function takeOrder(...) or acceptDelivery(...)
post -> will either place object on stack if it has no counter-stack objects existing,
or will fulfill order/delivery if possible and pop corresponding stack object after
*/
void Stack::push(Stack& stack, Deliveries_Orders deliverStack[], Deliveries_Orders orderStack[],
	string& deliveryOrOrder, int& orderNumber, int& widgetsToAccept, float pricePerWidget)
{
	bool inventoryEmpty = isEmpty(stack, deliverStack);
	bool pendingOrdersEmpty = isEmpty(stack, orderStack);
	int stackIndex = 1;							// 0 is our head, we will add to stack starting at index 1
	if (deliveryOrOrder == "delivery") {		// run if our delivery stack is empty
		if (inventoryEmpty) {
			deliverStack[stackIndex].orderNumber = orderNumber;
			deliverStack[stackIndex].widgetCount = widgetsToAccept;
			deliverStack[stackIndex].price = pricePerWidget;
		}
		else {									// run if our delivery stack is not empty
			int nextEmptyIndex = 2;
			// traverse our delivery stack and find our next empty available stack to assign values to
			for (; deliverStack[nextEmptyIndex].orderNumber != 0; nextEmptyIndex++) {}
			cout << "Our next avaiable spot on the stack is at index: " << nextEmptyIndex << endl;
			deliverStack[nextEmptyIndex].orderNumber = orderNumber;
			deliverStack[nextEmptyIndex].widgetCount = widgetsToAccept;
			deliverStack[nextEmptyIndex].price = pricePerWidget;
		}
	}
	if (deliveryOrOrder == "order") {			// run if our order stack is empty
		if (pendingOrdersEmpty) {
			orderStack[stackIndex].orderNumber = orderNumber;
			orderStack[stackIndex].widgetCount = widgetsToAccept;
		}
		else {									// run if our order stack is not empty
			int nextEmptyIndex = 2;
			// traverse our delivery stack and find our next empty available stack to assign values to
			for (; orderStack[nextEmptyIndex].orderNumber != 0; nextEmptyIndex++) {}
			cout << "Our next avaiable spot on the stack is at index: " << nextEmptyIndex << endl;
			orderStack[stackIndex].orderNumber = orderNumber;
			orderStack[stackIndex].widgetCount = widgetsToAccept;
		}
	}
	// CHECKING DELIVERIES
	if (deliveryOrOrder == "delivery") {
		if (pendingOrdersEmpty) {		// if orders are empty
		}
		else {							// if orders are not empty
			stack.pop(stack, deliverStack, orderStack, deliveryOrOrder, orderNumber, widgetsToAccept, pricePerWidget);
		}
	}
	else {	// CHECKING ORDERS
		if (inventoryEmpty) {		// if deliveries are empty
		}
		else {						// if deliveres are not empty
			// we will use our order to fufill deliveres on the delivery stack
			stack.pop(stack, deliverStack, orderStack, deliveryOrOrder, orderNumber, widgetsToAccept, pricePerWidget);
		}
	}
}

/* stack function used to pop an object on a given stack(delivery / order)
 pre -> needs to be passed an object of a stack with function push(...)
 post -> will pop off corresponding objects off stack when an order is presented while we have inventory,
 or if inventory is delivered and we have orders waiting to go out
 */
void Stack::pop(Stack& stack, Deliveries_Orders deliverStack[], Deliveries_Orders orderStack[],
	string& deliveryOrOrder, int& orderNumber, int& widgetsToAccept, float& pricePerWidget) {
	do {
		int currentDelivery = stack.lastElementOnStack(stack, deliverStack);
		int currentOrder = stack.lastElementOnStack(stack, orderStack);
		int qtyShipped;
		// first we determine which stack has the higher widget count (delivery) or (order) and go from there
		// if we're dealing with orders <= deliveries (so we will remove all orders and still have deliveries (inventory) left over)
		if (deliverStack[currentDelivery].widgetCount >= orderStack[currentOrder].widgetCount) {
			deliverStack[currentDelivery].widgetCount =
				(deliverStack[currentDelivery].widgetCount) - (orderStack[currentOrder].widgetCount);
			qtyShipped = orderStack[currentOrder].widgetCount;
			orderStack[currentOrder].widgetCount = 0;
			displayOrderDetails(stack, deliverStack, orderStack, deliveryOrOrder, orderNumber,
				widgetsToAccept, qtyShipped, deliverStack[currentDelivery].price);
			currentOrder--;
			widgetsToAccept = widgetsToAccept - qtyShipped;
		}
		// else, we're dealing with orders > deliveries (so we will remove all deliveries and have orders left over)
		else {
			orderStack[currentOrder].widgetCount =
				(orderStack[currentOrder].widgetCount) - (deliverStack[currentDelivery].widgetCount);
			qtyShipped = deliverStack[currentDelivery].widgetCount;
			deliverStack[currentDelivery].widgetCount = 0;
			displayOrderDetails(stack, deliverStack, orderStack, deliveryOrOrder, orderNumber,
				widgetsToAccept, qtyShipped, deliverStack[currentDelivery].price);
			currentDelivery--;
			widgetsToAccept = widgetsToAccept - qtyShipped;
		}
	} while (orderStack[stack.lastElementOnStack(stack, orderStack)].widgetCount > 0 &&
		(stack.lastElementOnStack(stack, deliverStack) - 1) == 0 ||
		deliverStack[stack.lastElementOnStack(stack, deliverStack)].widgetCount > 0 &&
		(stack.lastElementOnStack(stack, orderStack) - 1) == 0);
}

/*
stack function used to return if stack is empty
 pre -> needs to be passed a stack object and struct for objects
 post -> return true if stack is empty, false if it's not
 */
bool Stack::isEmpty(Stack& stack, Deliveries_Orders objStack[]) const {
	if (objStack[1].widgetCount != 0) return false;		// if widgets exist in stack, then our stack is not empty
	else return true;									// otherwise stack is empty
}

/*
stack function used to return if stack is full
 pre -> needs to be passed a stack object and struct for objects
 post -> return true if stack is full, false if it's not
 */
bool Stack::isFull(Stack& stack) {
	if (stack.stackNumber++ == STACK_SIZE) return true;
	else return false;
}

/*
stack function used to return the last element position of object on stack
 pre -> needs to be passed a stack object and struct for objects
 post -> return last element indexed position of stack object
 */
int Stack::lastElementOnStack(Stack& stack, Deliveries_Orders objStack[]) {
	int nextFreeElement = 0;
	for (; objStack[nextFreeElement + 1].widgetCount != 0; nextFreeElement++) {}
	return (nextFreeElement);
}

// helper functions

/*
used to accept a new order from menu option #4 (user inputs how many widgets customer requests)
pre -> stack object must be passed as well stack struct
post -> once data has been validated, order is pushed onto stack with stack push(...) function
*/
void Stack::takeOrder(Stack& objOrder, Deliveries_Orders deliverStack[], Deliveries_Orders orderStack[]) {
	bool fullStack = isFull(objOrder);	// check if our stack is full, only run if we have room on the stack
	if (!fullStack) {
		int orderNumber = generateOrderNumber("order");
		string pushOrder = "order";
		int widgetsToAccept = 0;
		cout << "\nAccepting an Order\n";
		while (widgetsToAccept <= 0) {
			cout << "Enter number of widgets to be requested from this order: ";
			cin >> widgetsToAccept;
			if (widgetsToAccept <= 0) cout << "\nMust enter a value greater than 0\n";
		}
		cout << "What is the order number for this order?: " << orderNumber << endl;
		objOrder.push(objOrder, deliverStack, orderStack, pushOrder, orderNumber, widgetsToAccept);
	}
	else cout << "Our orders (order stack) are full at the moment, we need some deliveries placed before we can receive anymore orders.\n";
}

/*
used to accept a new delivery from menu option #3 (user inputs how many widgets we receive, and at what cost)
pre -> stack object must be passed as well stack struct
post -> once data has been validated, delivery is pushed onto stack with stack push(...) function
*/
void Stack::acceptDelivery(Stack& objDeliver, Deliveries_Orders deliveryStack[], Deliveries_Orders orderStack[]) {
	bool fullStack = isFull(objDeliver);	// check if our stack is full, only run if we have room on the stack
	if (!fullStack) {
		objDeliver.stackNumber++;			// ensures our stack is increased everytime this function runs
		string pushDelivery = "delivery";
		int orderNumber = generateOrderNumber("delivery");
		int widgetsToAccept = 0;
		float pricePerWidget = 0.00;
		cout << setprecision(2) << fixed;
		cout << "\nAccepting a Delivery\n";
		while (widgetsToAccept <= 0) {		// ensures we receive valid data for number of widgets to accept
			cout << "Enter number of widgets to receive from this delivery: ";
			cin >> widgetsToAccept;
			if (widgetsToAccept <= 0) cout << "\nMust enter a value greater than 0\n";
		}
		while (pricePerWidget <= 0) {		// ensures we receive valid data for price for widgets to accept
			cout << "Enter price per widget cost: ";
			cin >> pricePerWidget;
			if (pricePerWidget <= 0) cout << "\nMust enter a value greater than 0\n";
		}
		cout << "What is the order number for this order? Order #: " << orderNumber << endl;
		objDeliver.push(objDeliver, deliveryStack, orderStack, pushDelivery,
			orderNumber, widgetsToAccept, pricePerWidget);     // push this delivery onto our delivery stack
		cout << endl;
	}
	else cout << "Our inventory (delivery stack) is full at the moment, "
		"we need some orders placed before we can receive anymore widgets.\n";
}

/*displays a table of order details right after an order / delivery has been fulfilled
pre -> stack function pop(...) must be run
post -> will display order details of last popped object (last fulfilled order)
*/
void Stack::displayOrderDetails(Stack& stack, Deliveries_Orders deliverStack[],
	Deliveries_Orders orderStack[], string& deliveryOrOrder, int& orderNumber,
	int& widgetsToAccept, int& qtyShipped, float& pricePerWidget) {
	double priceForCustomer = (pricePerWidget * 2.0);
	double totalCostForCustomer = (priceForCustomer * qtyShipped);
	int remainingWidgetsToSend = (widgetsToAccept - qtyShipped);

	cout << "\nTransaction Details:\n";
	cout << "Order #: " << setw(19) << right << orderNumber << endl;
	cout << "Qty. Ordered: " << setw(14) << right << widgetsToAccept << endl;
	cout << "Qty. Shipped: " << setw(14) << right << qtyShipped << endl;
	cout << "Price per Widget: " << setw(10) << right << priceForCustomer << endl;
	cout << "Total Cost: " << setw(16) << right << totalCostForCustomer << endl;
	cout << "Remanining Widgets: " << setw(8) << right << remainingWidgetsToSend << endl << endl;
}

/*
generates an ID number based on whether we are dealing with an order or a delivery
pre -> must be passed a string of either "delivery" or "order" from function takeOrder(...) or acceptDelivery(...)
post -> will display order details of last popped object (last fulfilled order)
*/
int Stack::generateOrderNumber(string deliveryOrOrder) {
	// #100 - 499 are used for orders (max number of orders are 400)
	// #500 - ... are used for deliveries (max number of deliveres are... based on computer memory)
	// all order numbers should be unique, there should never be an order with the same order number
	if (deliveryOrOrder == "delivery") {        // everytime we enter this if statement we increase the delivery number by 1
		deliveryNumber++;
		return deliveryNumber;
	}
	else if (deliveryOrOrder == "order") {      // everytime we enter this if statement, we increase the order number by 1
		orderNumber++;
		return orderNumber;
	}
	else {
		cout << "Invalid argument given to generate a new order number, number not generated\n";
		return 0;
	}
}

/*
prints the contents of the stack
pre -> displayDeliveries(...) or displayOrderOnHand(...) must be run
post -> prints out all orders from order/delivery stack
*/
void Stack::print(Stack& stack, Deliveries_Orders objStack[], string& deliveryOrOrder) const {
	const int WIDTH_SPACE = 18;
	int stackIndex = 0;
	bool checkForEmptyStack = isEmpty(stack, objStack);				// checks if stack is empty
	if (checkForEmptyStack && deliveryOrOrder == "delivery") {		// if we're checking the delivery stack
		cout << "There is currently no inventory on hand.\n";
	}
	else if (checkForEmptyStack && deliveryOrOrder == "order") {	// if we're checking the order stack
		cout << "There are currently no orders.\n";
	}
	else if (!checkForEmptyStack && deliveryOrOrder == "order") {	// if stack is not empty, and we're dealing with an order
		cout << "Order on Hand Details:\n\n"
			"Order Stack #\t"
			"Order #\t"
			"Qty. on Hand" << setw(9) << "\t"
			"Price (Customers Pay)" << endl;
	}
	else if (!checkForEmptyStack && deliveryOrOrder == "delivery") // if stack is not empty, and we're dealing with a delivery
	{
		cout << "Inventory on Hand Details:\n\n"
			"Delivery Stack #\t"
			"Delivery #\t"
			"Qty. on Hand" << setw(9) << "\t"
			"Price (Warehouse Price)" << endl;
	}
	for (int i = 1; objStack[i].widgetCount != 0; i++) {
		cout << setw(16) << right << i << setw(18)
			<< right << objStack[i].orderNumber << setw(18)
			<< right << objStack[i].widgetCount << setw(27)
			<< right << objStack[i].price << endl;
	}
	cout << endl;
}


/*
passes info to print out delivery stack
pre -> stack objects must have been initialized
post -> prints out all active orders from delivery stack by calling print(...) function
*/
void Stack::displayDeliveries(Stack& objDeliver, Deliveries_Orders deliveryStack[]) const {
	string stackChoice = "delivery";
	objDeliver.print(objDeliver, deliveryStack, stackChoice);
}

/*
passes info to print out order stack
pre -> stack objects must have been initialized
post -> prints out all active orders from order stack by calling print(...) function
*/
void Stack::displayOrderOnHand(Stack& objDeliver, Deliveries_Orders orderStack[]) const {
	string stackChoice = "order";
	objDeliver.print(objDeliver, orderStack, stackChoice);
}

// main below ***********************************************

int stackWarehouseMain() {
	Stack delivery;     // used for incoming deliveres to warehouse (add to inventory)
	Stack order;        // used for incoming orders for the warehouse to fill
	cout << "Welcome to the Backwards Warehouse!\n\nChoose an option from the menu.\n";
	int menuOption = 1;

	// delivery array(stack) created
	Deliveries_Orders deliveryStack[STACK_SIZE];
	Deliveries_Orders orderStack[STACK_SIZE];

	enum menuChoice {
		c_InventoryDetails = 1,
		c_OrderDetails,
		c_AcceptDelivery,
		c_TakeOrder,
		c_Exit
	};

	while (menuOption != 5) {
		cout << "Enter corresponding menu button to advance\n"
			"1. Display Inventory on Hand\n"
			"2. Display Outstanding Orders\n"
			"3. Accept Delivery\n"
			"4. Take an Order\n"
			"5. Quit program\n" << endl;

		cin >> menuOption;

		switch (menuOption) {
		case c_InventoryDetails:      // 1 (display deliveries)
			delivery.displayDeliveries(delivery, deliveryStack);
			break;
		case c_OrderDetails:          // 2 (display orders)
			order.displayOrderOnHand(delivery, orderStack);
			break;
		case c_AcceptDelivery:        // 3 (add to inventory)
			delivery.acceptDelivery(delivery, deliveryStack, orderStack);
			break;
		case c_TakeOrder:             // 4 (fufill an order from stock in inventory)
			order.takeOrder(order, deliveryStack, orderStack);
			break;
		case c_Exit:
			break;
		default:
			cout << "Invalid menu selection, enter a number from (1-5)" << endl;
		}
	}
	cout << "Program terminated.\n\n";
	return 0;
}
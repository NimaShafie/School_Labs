// Nima Shafie
#pragma once
#include <iostream>
using namespace std;

// handles output of function, also handles positive/negative distribution of answers (this calls recursiveExponential)
void exponentialExpression(int base, int power);
// uses recursion to find exponential expression provided by user
double recursiveExponential(int base, int power);
// uses recursion to find sum of squares (starting with 1 + (2*2) + (n*n) + ...)
int recursiveSumOfSquares(int numOfTerms, int counter);
// uses recursion to find sum of squares in reverse (starting with (n*n) + ((n-1) * (n-1)) + ...)
int recursiveReverseSumOfSquares(int numOfTerms);

int recursionMain() {
	int menuChoice = 1;
	int sumTotal = 0;
	int sumSquares = 0;
	int numOfSquares = 0;
	int counter = 1;
	while (menuChoice != 0) {
		cout << "Enter corresponding menu button to advance\n\n"
			"1. Exponential Recursive Function\n"
			"2. Recursive Sum of Squares with User Input\n"
			"3. Recursive Reverse Sum of Squares with User Input\n"
			"0. Quit program\n" << endl;
		cin >> menuChoice;

		switch (menuChoice) {
		case 1:		// Exponential Recursive Function choice
			int userBase, userPower;
			cout << "\nEnter Base: ";
			cin >> userBase;
			cout << "Enter Power: ";
			cin >> userPower;
			cout << endl;
			exponentialExpression(userBase, userPower);	// calls output function that has recursive function within it
			break;
		case 2:		// Recursive Sum of Squares with User Input choice
			do {
				cout << "Enter number of terms: ";
				cin >> numOfSquares;
			} while (numOfSquares <= 0);		// positive values only, will not proceed until user enters 0 or more
			sumSquares = recursiveSumOfSquares(numOfSquares, counter);
			cout << " = " << sumSquares << "\n" << endl;
			break;
		case 3:		// Recursive Reverse Sum of Squares with User Input choice
			do {
				cout << "Enter number of terms: ";
				cin >> numOfSquares;
			} while (numOfSquares <= 0);		// positive values only, will not proceed until user enters 0 or more
			sumSquares = recursiveReverseSumOfSquares(numOfSquares);
			cout << sumSquares << "\n" << endl;
			break;
		case 0:		// quit program
			cout << "Quitting program." << endl;
			break;
		default:	// invalid choice
			cout << "Invalid choice, try again." << endl;
			break;
		}
	}
	cout << "\n";
	return 0;
}

// will be used to filter through negative/positive answers and will call the recursive function, along with output
void exponentialExpression(int userBase, int userPower) {
	bool negativePower = false;					// marks if power provided is negative
	bool negativeBase = false;					// marks if base provided is negative
	// temporary variable to hold user input base # to output at end (will need to manipulate base # for positive/negative answers below)
	int tempBase = userBase;
	// temporary variable to hold user input base # to output at end (will need to manipulate base # for positive/negative answers below)
	int tempPower = userPower;
	double expoAnswer;							// the final answer will be held here
	if (userPower < 0) {						// if user enters a negative number, we will temporarily change to positive number in order to run recursion algorithim
		negativePower = true;					// will flag this boolean so we can convert back to 1/x once recursion returns answer
		userPower = (userPower * (-1));			// converting number to its positive form
	}
	if (userBase < 0) {							// checking if base entered by user is negative
		if (userPower % 2 == 0) {				// if base is negative but power is even, then we can say answer will be positive
			userBase = (userBase * (-1));		// convert answer to positive
		}
		else {									// if base is negative and power is odd, then we will switch answer to negative at the end
			userBase = (userBase * (-1));		// switch answer to negative
			negativeBase = true;				// flagging that answer will be converted to a negative in the end
		}
	}
	expoAnswer = recursiveExponential(userBase, userPower);	// calling recursive function to return base^power
	if (negativePower) {
		expoAnswer = (1 / expoAnswer);			// converting number to base^(-power) to return correct form
	} if (negativeBase) {
		expoAnswer = (expoAnswer * (-1));		// converting answer to negative due to base being negative and power being odd
	}
	cout << tempBase << "^" << tempPower << " = " << expoAnswer << "\n" << endl;		// outputs result
}

// recursive function to return base^power provided (only returns positive powers, main converts to negative)
double recursiveExponential(int base, int power) {
	if (power == 1) {			// base case
		return (base);
	}
	else if (power == 0) {		// another base case
		return 1;
	}
	else {
		return ((base)*recursiveExponential(base, (power - 1)));		// recursion call here
	}
}

// recursive call to output case 2
int recursiveSumOfSquares(int numOfTerms, int counter) {
	// (recursive sum of squares (starting with 1 + (2*2) + (n*n) + ...))
	if (counter == 1 && numOfTerms != 0) {   // base case
		cout << "1";
	}
	if (numOfTerms == 1) {		// base case
		return numOfTerms;
	}
	else {
		counter++;
		cout << " + " << "(" << counter << "*" << counter << ")";
		return ((counter * counter) + (recursiveSumOfSquares((numOfTerms - 1), (counter))));
	}
}

// recursion call to output case 3
int recursiveReverseSumOfSquares(int numOfTerms) {
	// (recursive reverse sum of squares (starting with (n*n) + ((n-1) * (n-1)) + ...))
	if (numOfTerms == 1) {		// base case
		cout << "1 = ";
		return 1;
	}
	else {
		cout << "(" << numOfTerms << "*" << numOfTerms << ") + ";
		return ((numOfTerms * numOfTerms) + (recursiveReverseSumOfSquares((numOfTerms - 1))));		// recursion call here
	}
}

/* test output data below
Enter corresponding menu button to advance
1. Exponential Recursive Function
2. Recursive Sum of Squares with User Input
3. Recursive Reverse Sum of Squares with User Input
0. Quit program
1
Enter Base: 3
Enter Power: 4
3^4 = 81
Enter corresponding menu button to advance
1. Exponential Recursive Function
2. Recursive Sum of Squares with User Input
3. Recursive Reverse Sum of Squares with User Input
0. Quit program
1
Enter Base: 3
Enter Power: -4
3^-4 = 0.0123457
Enter corresponding menu button to advance
1. Exponential Recursive Function
2. Recursive Sum of Squares with User Input
3. Recursive Reverse Sum of Squares with User Input
0. Quit program
1
Enter Base: -3
Enter Power: -4
-3^-4 = 0.0123457
Enter corresponding menu button to advance
1. Exponential Recursive Function
2. Recursive Sum of Squares with User Input
3. Recursive Reverse Sum of Squares with User Input
0. Quit program
1
Enter Base: 0
Enter Power: 3
0^3 = 0
Enter corresponding menu button to advance
1. Exponential Recursive Function
2. Recursive Sum of Squares with User Input
3. Recursive Reverse Sum of Squares with User Input
0. Quit program
1
Enter Base: 3
Enter Power: 0
3^0 = 1
Enter corresponding menu button to advance
1. Exponential Recursive Function
2. Recursive Sum of Squares with User Input
3. Recursive Reverse Sum of Squares with User Input
0. Quit program
1
Enter Base: 0
Enter Power: 0
0^0 = 1
Enter corresponding menu button to advance
1. Exponential Recursive Function
2. Recursive Sum of Squares with User Input
3. Recursive Reverse Sum of Squares with User Input
0. Quit program
2
Enter number of terms: 1
1 = 1
Enter corresponding menu button to advance
1. Exponential Recursive Function
2. Recursive Sum of Squares with User Input
3. Recursive Reverse Sum of Squares with User Input
0. Quit program
2
Enter number of terms: -1
Enter number of terms: -2
Enter number of terms: -3
Enter number of terms: 3
1 + (2*2) + (3*3) = 14
Enter corresponding menu button to advance
1. Exponential Recursive Function
2. Recursive Sum of Squares with User Input
3. Recursive Reverse Sum of Squares with User Input
0. Quit program
3
Enter number of terms: 1
1 = 1
Enter corresponding menu button to advance
1. Exponential Recursive Function
2. Recursive Sum of Squares with User Input
3. Recursive Reverse Sum of Squares with User Input
0. Quit program
3
Enter number of terms: -1
Enter number of terms: -2
Enter number of terms: -3
Enter number of terms: 3
(3*3) + (2*2) + 1 = 14
Enter corresponding menu button to advance
1. Exponential Recursive Function
2. Recursive Sum of Squares with User Input
3. Recursive Reverse Sum of Squares with User Input
0. Quit program
0
*/
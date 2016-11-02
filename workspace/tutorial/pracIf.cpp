// STEP 1:   Complete the documentation here
//
// PracIf.cpp
// Written by:		Christopher Wai
// On the date:		13th September 2013
//
// This program does a few simple things with if statements for practice
// In general, a simple if statement looks like one of these:
// 
//     if (condition)		if (condition)
//         statement		   statement
//							else
//							   statement
//
// where the condition is an expression that evaluates to true or false
// and statement is any single statement, or a group of statements within braces { }

// The following lines will be part of every program in this course:
#include <iostream>
using namespace std;

int main()
{
	//  We will be testing various things about this input value:
	int input;			// value to test

	cout << "Please enter an integer value:  ";
	cin >> input;

	//  STEP 2:   Determine whether this value is equal to 5

 if (input == 5) 

		cout << "This value is equal to 5." << endl;

	//  STEP 3:   Determine whether this value is between 1.5 and 4.5

if (input >= 1.5 && input <= 4.5)

		cout << "This value is between 1.5 and 4.5." << endl;

	//  STEP 4:   Determine whether this value is even or odd, with only one 'if'

if (input % 2 == 0)

		cout << "This value is even." << endl;
else
		cout << "This value is odd." << endl;

	//  STEP 5:   Pick exactly one of the following results as compared to zero.

if (input > 0)

		cout << "This value is positive." << endl;
else if (input < 0)
		cout << "This value is negative." << endl;
else
		cout << "This value is equal to zero." << endl;


	//  STEP 6:   Determine whether this number is a factor of 60.
	//	          (2, 5, and 6 are factors; 0 and 120 are not)
	//  Be careful!  This should work correctly for all valid inputs.

if (input > 0 && 60 % input == 0)
		cout << "This is a factor of 60." << endl;

	return 0;
}
	//  STEP 7:	  Test your program.  Be sure to include as many
	//			  representataive examples for each case as you can think of.

	//  STEP 8:	  Submit your C++ Source file (NOT The solution) in the dropbox
	//			  Also, choose the Clean Solution option from the Build menu.
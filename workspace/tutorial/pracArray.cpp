// Practice with Arrays
// CMPSC 121       Fall 2013
// Name: Christopher Wai
// This program provides a little practice
// programming with arrays.  All of the function
// prototypes have already been provided, so the
// exercise is all about manipulating the arrays themselves.

// NOTE: None of your changes to this file are to be in
// the main function, but only in the indicated places.
// This will facilitate testing code for different data.

#include <iostream>			// access to cin, cout
#include <iomanip>			// access to setw
#include <cstring>
#include <string.h>
using namespace std;

// some function prototypes to be implemented later
void ArrayTest( const int[], int );		// various array practice loops

void reflow( char[], int );				// rearrange some character data

int main()
{
	// These arrays hold data to be tested with.  Different sizes!
	int arrayOne[] = { 3, 1, 7, 5,10, 8, 2, 9, 6, 4 };
	int arrayTwo[] = { 3,-1, 7, 5,-3, 8,-2, 9,-6, 4, 2, -8 };
	
	// A string is just an array of characters
	char getty[] = 
"Four score and seven years ago, our forefathers brought\
 forth on this continent a new nation, conceived in liberty\
 and dedicated to the proposition that all men are created equal.";
	char reform[200];			// to hold a copy of the above
	
	ArrayTest( arrayOne, 10 );
    ArrayTest( arrayTwo, 12 );
	
	for (int i = 60; i >= 40; i -= 10)
	{
		cout << '|' << setw(i) << '|' << endl;
		strcpy(reform, getty);
		reflow(reform, i);
		cout << reform << endl << endl;
	}
}

//  ArrayTest
//  Just a bunch of random operations on arrays
//  Parameters:	list[]		an array of values to handle
//              size		number of elements in these arrays
//  Local Var:  list2[]		another array to manipulate
void ArrayTest( const int list[], int size )
{
	int list2[20];		// big enough (we won't use it all)

	// STEP 1:  Print all the values in the array called list
	//			of the size given above
	//			The setw is here to make it look neat and tidy
	
	for (int i = 0; i  < size; i = i + 1) {

		cout << setw(4)               ; // output here within loop
		
		cout << list[i];

	cout << endl;						// end the output line
	}

	// STEP 2:  Compute the sum of the elements of the argument 'list'
	//          whose size was given as a parameter

	int sum = 0;						// sum of no numbers is zero
	
	for (int j = 0; j < size; j = j + 1) {
	    sum = sum + list[j];
	}

    cout << "The sum is " << sum << endl;

	// STEP 3:  Count the odd values in the argument 'list'

    int count = 0;						// no odd values found yet
    
    for (int k = 0; k < size; k = k + 1) {
        if (list[k] % 2 != 0) {
	        count = count + 1;
        }
	}

	cout << "There are " << count << " odd values." << endl;

	// STEP 4:  If you have not already done so, compile and test the above code.

}

	// STEP 12:  Complete the following function.  The main program will test it.
	// Try to understand how the algorithm works before diving into the code

//  reflow
//  Rearranges text to fit on a screen within assumed margins.
//  Parameters:	text[]		text to rearrange
//				lineLength	maximum number of characters per line
//
//  Overall algorithm:
//  Start from the beginning of the text
//  While the remaining text > length of a line
//      Skip forward over a number of characters equal to the line length
//      Search backwards for a space character   ' '
//			(hint: this is a nested loop)
//	    Replace the space with a newline character   '\n'
void reflow( char text[], int lineLength ) 
{
	int  textLength = int(strlen(text));		// total number of characters
    int  position;								// current array position
	position = 0;								// start at beginning
	
	while (textLength - position > lineLength) {
    	position = position + lineLength;
    	while (text[position] != ' '){
    	    position = position - 1;
    	}
    	text[position] = '\n';
	}

	// Hint: for the while condition listed above,
	//    with a current a current position in the text and total textLength,
	//       how much of the text remains to be examined?


}
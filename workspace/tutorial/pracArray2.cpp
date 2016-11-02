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
using namespace std;

// some function prototypes to be implemented later
void printArray( const int[] );						// show the contents of an array
void printPermuted( const int[], const int[] );		//    or in a permuted order

void ArrayTest( const int[], const int[], int );	// various array practice loops

int main()
{
	// These arrays hold data to be tested with.  Different sizes!
	int arrayOne[] = { 3, 1, 7, 5,10, 8, 2, 9, 6, 4 };
	int arrayTwo[] = { 3,-1, 7, 5,-3, 8,-2, 9,-6, 4, 2, -8 };

	// These are used to change the order in which array 
	// elements are processed. (They make the data appear sorted)
	int permute1[] = { 1, 6, 0, 9, 3, 8, 2, 5, 7, 4 };
	int permute2[] = { 11, 8, 4, 6, 1, 10, 0, 9, 3, 2, 5, 7 };
		
	ArrayTest( arrayOne, permute1, 10 );
    ArrayTest( arrayTwo, permute2, 12 );
}

// printArray
// Display the contents of the array, all on the same line
// 
// Parameters:      list[]		the array to display
//					size		number of elements in array to display
void printArray( const int list[], int size )
{
	for(int i = 0; i < size; i = i + 1) {
	//  STEP 1:  the loop body is given; implement the loop around it here
		cout << setw(4) << list[i];
	}
	
	cout << endl;
}

// printPermuted
// Display the contents of the array on one line, in a permuted order
// 
// Parameters:	list[]		the array to display
//				permute[]   a permutation of the values 0 to size-1
//				size		number of elements in these arrays
//
// Ex. if the first three elements of permute[] are 4, 0, 3
//     then the first three values displayed are list[4], list[0], list[3]
void printPermuted( const int list[], const int permute[], int size )
{
	for(int i = 0; i < size; i =  i + 1) {
	//  STEP 2:  Complete the function here.
	//           For neat output, use setw(4) as the last function did.
		cout << setw(4) << list[permute[i]];
	}
	cout << endl;

}

// STEP 3:  Implement this function.
//
// Hint: assume the first array value is the largest value,
// then search the array is a larger one,
// remembering where that largest value is.
//
// maximumPosition
// find the maximum value of an array
//
// Parameters:  list[]		the array to examine
//				length		number of array elements to examine
// Returns:  the position of the maximum value in the array
//     e.g. if the largest is in list[4], return 4
//     NOTE: Not the largest value itself, but its position
//
// Hint: assume the first array value is the largest value,
// then see if there is a larger one.
int maximumPosition( const int list[], int length )
{
	int maxPos = 0;					// initialized to please the compiler
	for(int i = 0; i < length; i =  i + 1) {
	    if (list[maxPos] < list[i]) {
	        maxPos = i;
	    }
	}


	return maxPos;
}

//  ArrayTest
//  Just a bunch of random operations on arrays
//  Parameters:	list[]		an array of values to handle
//				permute[]	a permutation of the list
//              size		number of elements in these arrays
//  Local Var:  list2[]		another array to manipulate
void ArrayTest( const int list[], const int permute[], int size )
{
	int list2[20];		// big enough (we won't use it all)

	// STEP 4:  Display the contents of the argument 'list'
	//			of the 'size' given above
	//          Call a function above to do so (NO LOOP here!)
	//			Syntax Hint: you want the display the entire array,
	//			    not just one subscripted array element.
	//		    The brackets [] are not part of the name of the array.
	//          NOTE: NO credit if you do not call the function above
	
	printArray(list,size);

    // STEP 5:  Copy all the values from list into list2 (in the same order)
	//          You will have to do this one element at a time.
	
	for(int i = 0; i < size; i =  i + 1) {
	    list2[i] = list[i];
	}

	// STEP 6:  Display the values of list2, permuted by the array called permute
	//          NOTE:  You must use a function implemented above!
	cout << "Permuted list2 (should appear sorted): " << endl;
	
	printPermuted(list2,permute,size);
	
	// This loop implements a selection sort, assuming the maximumPosition
	// function works properly.  It places the largest values at the end first.
	for (int len = size; len > 1; len--)
		swap( list2[len-1], list2[maximumPosition( list2, len )] );

	// STEP  7:  Display the values of list2 now!  (not permuted)
	//           NOTE:  This still uses a function implemented above.
	//           Since the list has been sorted, it should appear so.
	cout << "Unpermuted list2 (after sorting): " << endl;
	
	printArray(list2,size);

	cout << endl;

	// STEP  8:  Test your results.  The array should appear sorted in both cases.
}

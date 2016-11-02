// Linked List Tutorial
// Completed by: Christopher Wai
// ON date: 6th December 2013
#include <iostream>
using namespace std;

// This is a little practice with singly-linked lists
// using the following structure:
struct List {
	int val;
	struct List *next;
};

// Some function prototypes
void printList( const struct List *list );
void printReverse( const struct List *list );
void insert( struct List *&list, int val );
void deleteAll( struct List *list );
void append( struct List *&list, struct List *tail );
void split( struct List *whole, struct List *&first, struct List *&second,
		   int test( int, int ));
void qsort( struct List *&list );

//  This main program populates two lists, displays them,
//  appends them into one list, and then sorts taht one list.
int main()
{
	const int data1[] = {1, 3, 5, 7, 9};
	const int data2[] = {2, 4, 6, 8 };
	struct List *first=NULL, *second=NULL;

    for (int i=0; i<5; i++)
		insert( first, data1[i] );
	for (int i=0; i<4; i++)
		insert( second, data2[i] );
	cout << "Odd  values decreasing: ";
	printList( first );
	cout << "Even values increasing: ";
	printReverse( second );
	cout << endl;
	append( second, first );
	cout << "Appended List:  ";
	printList( second );
	qsort( second );
	cout << "Sorted List:  ";
	printList( second );
}

//  deleteAll
//  deallocates all the members of a given linked list
//  Parameter:
//		list	(modified list)		list to deallocate
//  NOTE: Since the list pointer is passed by value here,
//	      it is not changed, and will point at deallocated memory!
void deleteAll( struct List *list )
{
	if (list != NULL)
		deleteAll( list->next );
	delete list;
}

//  TUTORIAL Step 1:
//  Complete the following two functions as recursive functions.
//  They should look very similar to each other, only differing
//  in the order that they do their operations.

//  printList
//  displays all the values in the linked list on ONE output line
//      beginning with the one pointad at by 'list'
//  Parameter:
//		list	(input list)	list to display
//  NOTE: the 'const' keywords in this prototype
//      says the structure 'list' points at will not be changed.
//
//  HINTE:  The easiest list to display is the empty list.
void printList( const struct List *list )
{
    if (list != NULL) {
        cout << list->val << "  ";
        printList(list->next);
    }
}

//  printReverse
//  displays all the values in the linked list on ONE output line
//      ending with the one pointed at by 'list'
//  Parameter:
//		list	(input list)	list to display
void printReverse( const struct List *list )
{
    if (list != NULL) {
        printReverse(list->next);
        cout << list->val << "  ";
    }
}

//  TUTORIAL Step 2:
//  Complete the following two functions that modify
//  the contents of a list.

//  insert
//  inserts a new value into the front of a given list
//  Parameters:
//		list	(modified list)		list to insert into
//		val		(input int)		`	value to add to the front
//  NOTE:  The given list may have initially been empty!
void insert( struct List *&list, int val )
{
    struct List *toAdd = new struct List;
	toAdd->val = val;
	toAdd->next = list;
	list = toAdd;
}

//  append
//  appends one list to the end of another, preserving the order of both
//  Parameters:
//		list	(modified list)		list to append to
//		tail	(input list)		back end of new list
//
//  HINT:   There is no need to visit all the elements of the tail.
//			All you need is that 'tail' pointer.  Just modify 'list'
//  This function may be implemented either recursively or as a loop.
void append( struct List *&list, struct List *tail )
{
    int val;
    if (list != NULL) {
        val = tail->val;
        insert(list,val);
    }
}

//  TUTORIAL Step 3:
//  This would be a good time to compile and test what you have so far.

//  Split
//  Divides a list into two smaller lists, based on how they compare
//		to a given value
//  Parameters:
//		whole	(input list)		list to divide
//		pivot	(input integer)		pivot value to compare to
//		small	(output list)		sublist for values less than pivot
//		large 	(output list)		sublist for values greater than pivot
void split( struct List *whole, int pivot, 
		struct List *&small, struct List *&large )
{


}

//  QSort
//  Applies the Quick Sort Algorithm to a Linked List
//  As a summary of the quick sort algorithms
//     1) Pick a pivot value   (the first is easiest to access)
//     2) Divide the remaining values into two sets
//                             (do not include the first)
//     3) Sort the two smaller lists, recursively
//	   4) Combine the results into the final result
//								(don't forget to include the pivot!)
//	Parameter:
//		list	(modified list)	data to sort
//								will point to newly created list
//
//  Two Extra Credit points for properly deallocating memory
//  that is no longer needed.
void qsort( struct List *&list )
{
	// lists of 0 or 1 element are already sorted
	if (list != NULL && list->next != NULL)
	{
		int    pivot;			// value to compare to
		struct List *smaller,	// for values smaller than the pivot 
					*greater;	// for values greater than the pivot


	}
}

//  TUTORIAL Step 4:
//  Try it out, and see if the data is sorted.
//  If you need additional debug help, you may use the
//  existing functions to print out any list at any time

//  TUTORIAL Step 5:
//  Be sure to submit your .cpp file and not your .sln
//  since you may have gone home for break before a mistake is found!
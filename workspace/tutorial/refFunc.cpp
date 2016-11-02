// Practice with Functions
// Roger Christman		Fall 2013
//
// This tutorial assignment will practice the declaration
// and inplementation of simple functions with reference parameters.
// For simplicity, and to remove the extra time to define function prototypes,
// the main() function will be left at the bottom of this program file.
//
// For each of the three functions in this tutorial:
//    -- determine what appears in the formal parameter list
//		 i.e. they all have no parametrs now, but that must change
//    -- determine which formal parameters will be references to variables
//    -- code the function to perform its task
//
// The main function is already complete, except for some comment markers
// (which are present to avoid compiler errors).
// For each case, implement the function so that it matches
// the expected behavior as called by main().

// DO NOT rewrite the function calls in main -- only remove the comments.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;

// Implement your functions within the sets of braces below.
// (Remove the // comment indicators in main() to test them)

// advanceTimeInMinutes
// advances a simulated digital clock by a specified amount of time
// this clock uses hours and minutes on the 24-hour scale (0:00-23:59)
// a third parameter indicates how much time has elapsed
// For example, if the original time was 8:45, the following
// call would advance the time 30 minutes to 9:15:
//      advanceTimeInMinutes(  hour, minute, 30 );
void advanceTimeInMinutes(int& hour,int& minute,int increment)
{
	minute = minute + increment;
    if (minute > 60) {
        hour = hour + 1;
        minute = minute - 60;
    }
	else
		minute + increment;
    if (hour > 23) {
        hour = hour % 24;
    }
}

// advanceTimeInHours
// This also advances time, but expresses the elapsed time in hours
// (which may be fractional).   For example:
//		advanceTimeInHours(  hour, minute, 0.5 );
void advanceTimeInHours(int& hour,int& minute,float increment)
{
    increment = increment * 60;
	advanceTimeInMinutes(hour,minute,increment);
}

// sort3:
// given references to three integer variables,
// rearranges them so the first is the largest, and the third is the smallest
// example call: sort3( k, l, m );
//
// HINT: It is possible to do this with exactly three statements of the form:
// if ( ____ > ____ )
//    swap( ____, ____ );
// Some assertions are provided to help you
//
// There is already a function called swap that exchanges value
// which you may use.  There is no need to implement that function.
void sortThree(int& x,int& y,int& z)
{
	//  originally, the three values may be in any order
     if (y > x) {
         swap(x,y);
     }

	//  the first is now greater than the second
     if (z > y) {
         swap(y,z);
     }

	//  the first is greater than both the second and the third (it is largest)

    if (y > x) {
         swap(x,y);
     }
	//  the values are now all sorted with the first largest and third smallest 
}

void sortFive(int& a,int& b,int& c,int& d,int& e) {
	sortThree(c,d,e);
	sortThree(b,c,d);
	sortThree(a,b,c);
	sortThree(a,c,e);
}

//  The code below will test the functions implemented above.
//  Make no changes here aside from removing the '//' comment markers.
int main()
{
	int   i, k, l, m;				// some generic integer variables

	int  hour, minute;					// simulated clock time

	cout << setfill( '0' );				// pad minutes with zero digits
	hour = 8;
	minute = 0;
	for (i = 1; i <= 3; i++)
	{
		cout << "Class period " << i << " runs from " 
			 << hour << ":" << setw(2) << minute << " to ";
		advanceTimeInMinutes( hour, minute, 50 );
		cout << hour << ":" << setw(2) << minute << endl;
		advanceTimeInMinutes( hour, minute, 15 );
	}
	for (i = 4; i<= 5; i++)
	{
		cout << "Class period " << i << " runs from " 
			 << hour << ":" << setw(2) << minute << " to ";
		advanceTimeInHours( hour, minute, 5.0/6 );
		cout << hour << ":" << setw(2) << minute << endl;
		advanceTimeInHours( hour, minute, 0.25 );
	}

	for (i = 0; i < 7; i++)
	{
		k = rand() % 100;
		l = rand() % 100;
		m = rand() % 100;
		sortThree( k, l, m );
		cout << k << " >= " << l << " >= " << m << endl;
	}
}
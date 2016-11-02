// Practice with Functions
// Roger Christman		Fall 2013
//
// This tutorial assignment will practice the declaration
// and inplementation of simple functions with value parameters.
// For simplicity, and to remove the extra time to define function prototypes,
// the main() function will be left at the bottom of this program file.
//
// For each of the three functions in this tutorial:
//    -- determine what appears in the formal parameter list
//		 i.e. they all have no parameters now, but that must change
//	  -- determine what type of value the function returns
//		 they are all void now (no value returned), but two must change!
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
// (Remove the leading // comment indicators in main() to test them)

// maximum:
// returns the larger of two integers
// example call: cout << maximum(14, 25);      would output 25
int maximum(int p, int q)
{
    if (p >= q) {
        return p;
    }
    else {
        return q;
    }
}

// printMax4:
// displays the largest of four integers
// example call: printMax4( 1, 4, 3, 7 );    would output 7
// For full credit, this must use the maximum function above.
void printMax4(int x, int y, int w, int z)
{
int n = maximum(x,y);
int m = maximum(w,z);
cout << maximum(n,m);
}


// intPower:
// given a real value (double) and an integer exponent
// raises the value to the desired power, returning the result
// DO NOT call the pow function... do the multiplication yourself
// example call: cout << intPower( -2.7, 2 );    would output 7.29
// This function may assume the given exponent is not less than zero.
//     (but it may be exactly zero)
// recall:    x ^ N = 1 * x * x * x ....  (N times)
double intPower(double a, int n)
{
    if (n == 0)
    return 1;
    double total = 1;
	while (n > 0) {
	    total = total * a;
	    n = n - 1;
	}
	return total;
}

//  The code below will test the functions implemented above.
//  Make no changes here aside from removing the '//' comment markers.
int main()
{
	int   i, j, k, l, m;				// some generic integer variables

	cout << setprecision(4);			// show only 4 significant digits
	for (i = 1; i <= 3; i++)
	{
		j = rand() % 100;
		cout << "The larger of " << j << " and 25 is " << maximum( j, 25 ) << endl;
		cout << "The larger of " << j << " and 50 is " << maximum( 50, j ) << endl;
	}

    for (i = 1; i <= 3; i++)
	{
		j = rand() & 100;
		k = rand() % 100;
		l = rand() % 100;
		m = rand() % 100;
        cout << "The largest of " << j << ", " << k << ", " 
		     << l << ", and " << m << " is ";
		printMax4( j, k, l, m );
        cout << endl;
    }
    for (i = 0; i <= 4; i++)
	{
		cout << right;				// right justify these integer results
		cout << "-2 ^ " << i << " = " << setw(2) << intPower( -2, i ); 	
		cout << left;				// left justify these float results
		cout <<	"   1.414 ^ " << i << " = " << setw(6) << intPower( sqrt(2.0f), i );
		cout << endl;
	}
	
}
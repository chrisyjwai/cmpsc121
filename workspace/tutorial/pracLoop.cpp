// STEP 1:   Complete the documentation here
//
// PracLoop.cpp
// Written by:	Christopher Wai	
// On the date:		20th September 2013
//
// This program does a few simple things with loops for practice
// In general, a while loop looks like this:
// 
//     while  (condition)
//         statement
//
// where the condition is an expression that evaluates to true or false
// and statement is any single statement, or a group of statements within braces { }
//
// NOTE:  The loop condition must be chosen as appropriate to the problem.
//        ANY answer that uses a 'break' to leave the loop will count as incorrect

// The following lines will be part of every program in this course:
#include <iostream>
using namespace std;

int main()
{
	// This variable 'input' will be used the next several loops
	int input;				// an input value to be used for caculations

	// Some loop counter variables
	int counter1, counter2;		// two counters should be enough for now

	// These variables will hold the sums and products of selected values
	int sum, product;

	cout << "Please enter a small positive integer:  ";
	cin >> input;

	// The first loops will be repeated for various values of 'input'
	// DO NOT change this input!
	while (input > 0)
	{
		// STEP 2:
		// Write a loop that determines the sum of the smallest 'input' positive integers
		// For example, the sum of the first three integers is 6.
sum = 0;
counter1 = 0;
while (counter1 <= input) {
sum = sum + counter1;

counter1 = counter1 + 1;
}
		cout << "The sum of the first " << input << " integers is " << sum << "." << endl;


		// STEP 3:
		// Write a loop that determines the sum of the first 'input' odd integers
		// The largest such integer will be just less than 2*input
		// For partial credit, it will suffice to get the correct sum
		// For full credit, do so without using any if statements for any purpose
		//	  (and a while-loop that never repeats is just an if in disguise)
		// Hint: how will you obtain just the odd numbers?
sum = 0;
counter1 = 0;
while (counter1 <= input){
sum = sum + ((2 * counter1)  - 1);
counter1 = counter1 + 1;
}
sum = sum + 1;
		cout << "The sum of the first " << input << " odd integers is " << sum << "." << endl;




		// STEP 4:
		// Write a loop that determines the smallest factor of 'input' (other than 1)
		// This would be 2 for even numbers, or 'input' itself if 'input' is prime.
		// (You will need to change the last part of the provided cout statement.)

counter1 = 2;
while (counter2 != 0) {
counter2 = input % counter1;

counter1 = counter1 + 1;
}
counter1 = counter1 - 1;
		cout << "The smallest factor of " << input << " is " << counter1 << endl;

	//	cout << endl << "Please enter another small integer, or 0 to stop this part:  ";
	//	cin >> input;
	//}

	// STEP 5:
	// Test the code that you have so far

	// STEP 6:
	// For any positive integer n, n factorial (written as 'n!' in math)
	// is the product of all the positive integers up to and including n.
	// Write a program loop that displays the first nine factorials
	// The first three lines of    1! = 1
	// output should look like     2! = 2
	// those at the right here     3! = 6
	// For full credit, do so with a single loop (no nested loops)
	// HINT: Use the value you found in the previous iteration.
/*
product = 1;
counter1=input;
while(counter1 > 0) {
product = product * counter1;

counter1 = counter1 - 1;
}

cout << "The factorial of " << input << " is " << product << endl;

}
*/
	// STEP 7:  (as time permits)
	// Remove the comments from these next two lines,
	// and then complete the assigned problem.
	// cout << "How many rows and columns will the rectangle have?  ";
	// cin >> input;

	// Write a while loop within a while loop     ****
	// that displays a rectangle shape like the   ****
	// one shown to the right here.  This one     ****
	// example would be the case for input = 4    ****

	// Display the rectangle here.
	// Hint: print one asterisk * at a time,
	// and then the end of line (endl) as needed.





	// STEP 8: (as time permits)
	// Now write nested loops that would   ****
	// display a a parallelogram like       ****
	// the one illustrated here.             ****
	// Hint: spaces are characters too!       ****
	// This will use the same input value as above.





	return 0;
}

// STEP 8:
// Once you are satisfied with your program
// submit the C++ file into the ANGEL dropbox.
// Also the Clean option from the Build menu
// will clean up files you no longer need.

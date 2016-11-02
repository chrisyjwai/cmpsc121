#include<iostream>
#include<cstdlib>
#include<cmath>

using namespace std;

void playMastermind(); // Runs the mastermind sequence.
int rollDie(int,int); // Generates the combination to guess.
void evaluate(int,int,int); // Evaluates the user guess against the combination.
int nthDigit(int,int); // Identifies the nth digit in a combination/guess.
int clearNthDigit(int,int); // Sets the nth digit in a combination/guess to zero.

int main() {
    playMastermind(); // Calls on the game sequence.
    char yesNo;
    do { // Do-while for input validation.
        cout << "Play another game? (y/n) ";
        cin >> yesNo;
        cout << endl;
    } while (yesNo != 'y' && yesNo != 'n'); // Checks if y or n entered.
    if (yesNo == 'y') {
        return main(); // Calls this function to run game sequence again.
    }
    else if (yesNo == 'n') {
        cout << "Thank you for playing Mastermind. Goodbye!" << endl; 
        return 0; // Exit message and terminate program.
    }
}

void playMastermind() {
    int sides; // Number of sides to the die.
    int digits; // Number of digits to guess.
    int guesses; // Number of guesses desired.
    do { // Do-while for input validation.
        cout << "How many sides to the die? (Enter a value from 1 to 9)" << endl;
        cin >> sides;
    } while (sides < 1 || sides > 9); // Checks there are only between 1 and 9 sides.
    do { // Do-while for input validation.
        cout << "How many numbers to guess? (Enter a number 1 or greater)" << endl;
        cin >> digits;
    } while (digits < 1); // Checks no numbers less than 1.
    do { // Do-while for input validation.
        cout << "How many guesses do you want? (Enter a number 1 or greater)" << endl;
        cin >> guesses;
    } while (guesses < 1); // Checks no numbers less than 1.
    int combination = rollDie(sides,digits); // Generates combination to guess.
    int guess; // User combination guess.
//    cout << combination << endl; // Remove comment to see combination.
    while (guesses >= 1) {
        do { // Do-while for input validation.
            cout << "Try to guess the combination (Enter " << digits << " number(s)):  ";
            cin >> guess;
        } while (floor(log10(guess)) + 1 != digits); // Checks if number of digits entered is correct.
        guesses = guesses - 1; // Decrements number of guesses left.
        evaluate(combination,guess,digits); // Calls function to evaluate guess against combination.
        if (combination == guess) { // If guess is correct.
            cout << "You guessed my combination! Congratulations!" << endl; // Winning message.
            return; // Exit function to main for user input for next game or terminate program.
        }
    }
    cout << "Sorry, you've run out of guesses. The combination was " << combination << ". Better luck next time!" << endl; // Losing message if guesses run out and exit function.
}

int rollDie(int n,int m) { // Generates combination to guess.
    int roll; // Value of combination.
    for (int i = m - 1; i >= 0; i = i - 1) { // Decrements and adds random digit next place down.
        roll = roll + (1 + rand() % n) * pow(10,i);
    }
    return roll; // Returns combination.
}

int nthDigit(int x,int n) { // Identifies the nth digit in the combination x from the right.
    x = x / pow(10,(n - 1)); // Combination is divided till nth digit is in ones digit place and truncates decimals.
    return (x % 10); // Returns digit in ones digit place.
}

int clearNthDigit(int x,int n) { // Identifies and clears to zero the nth digit in the combination x from the right.
    return (x - (nthDigit(x,n) * pow(10,(n - 1)))); // Minus from combination the digit times it's place in base 10 and return.
}

void evaluate(int x,int y,int n) { // x is the combination, y is the guess, n is the number of digits in the current game.
    int blackPegs = 0; // Counter for black pegs.
    int whitePegs = 0; // Counter for white pegs.
    for (int i = n; i >= 1; i = i - 1) { // Counter loop combination.
        for (int j = n; j >= 1; j = j - 1) { // Counter loop for guess. Checks all digits against a single current digit in the ith place of the combination.
            if (nthDigit(x,i) == nthDigit(y,j) && i == j) { // Condition if digit is same AND place is the same for combination and guess.
                blackPegs = blackPegs + 1; // Increments black pegs by one.
                y = clearNthDigit(y,j); // Clears matched digit so future digits checked won't get checked more than once.
            }
            else if (nthDigit(x,i) == nthDigit(y,j)) { // Condition if digit is same regardless of position.
                whitePegs = whitePegs + 1; // Increments white pegs by one.
                y = clearNthDigit(y,j); // Clears matched digit so future digits checked won't get checked more than once.
            }
        }
    }
    cout << "You get " << blackPegs << " black pegs and " << whitePegs << " white pegs." << endl; // Reveals to user how many black and white pegs obtained..
}
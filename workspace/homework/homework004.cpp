#include<iostream>
#include<cstdlib>
#include<cmath>

using namespace std;

void playMastermind(); // Runs the mastermind sequence.
int rollDie(int); // Picks a random integer >=1 and <= the provided argument.
void evaluate(int,int,int&,int&); // Evaluates the user guess against the combination.
int nthDigit(int,int); // Identifies the nth digit in a combination/guess.
void clearNthDigit(int&,int); // Sets the nth digit in a combination/guess to zero.

int generateAnswer(); // Asks for combination or generates a random one.
void generateSearchSpace(int,int); // Generates an array with all possible guesses.
int methodicalEliminate(int); // Methodically eliminates guesses starting with the first element.
int guessAndEliminate(int); // Methodically eliminates guesses starting with a random element.
int guessThreeThenEliminate(int); // Methodically eliminates guesses starting with three random elements.
void trim(int[],int&,int,int&,int&); // Trims the guess and all the elements with a nonsimilar peg profile from the array.

int main() {
    playMastermind(); // Calls on the game sequence.
    char askYesNo;
    do { // Do-while for input validation.
        cout << "Play another game? (y/n) ";
        cin >> askYesNo;
        cout << endl;
    } while (askYesNo != 'y' && askYesNo != 'n'); // Checks if y or n entered.
    if (askYesNo == 'y') {
        return main(); // Calls this function to run game sequence again.
    }
    else if (askYesNo == 'n') {
        cout << "Thank you for playing Mastermind. Goodbye!" << endl; 
        return 0; // Exit message and terminate program.
    }
}

void playMastermind() {
    int combination = generateAnswer(); // Variable stores generated or inputted answer.
    int guessMethodical = methodicalEliminate(combination); // Variable stores number of tries needed by this strategy.
    cout << endl;
    int guessEliminate = guessAndEliminate(combination); // Variable stores number of tries needed by this strategy.
    cout << endl;
    int guessThree = guessThreeThenEliminate(combination); // Variable stores number of tries needed by this strategy.
    cout << endl;
}

// Functions rollDie, evaluate, nthDigit and clearNthDigit are from the solutions.

int rollDie(int sides) { // Picks a random integer >=1 and <= the provided argument.
    return 1 + rand() % sides;
}

void evaluate(int guess,int answer,int &black,int &white) {
/*--------------------------------------------------------------------------
 evaluate a Mastermind combination
 First count the digits in the correct positions, then clear them 
 then look for digits in incorrect positions, clearing them when found
 Since the guess and the answer are both passed by value to this function
 we do not fear destroying the original copies while we are here.
--------------------------------------------------------------------------*/
	black = 0;			// nothing confirmed yet
	white = 0;
	for (int i = 1; i <= 4; i = i + 1) {
		if (nthDigit(guess,i) == nthDigit(answer,i)) {
			black = black + 1;						// digit in correct spot
			clearNthDigit(guess,i);		// don't match these again
			clearNthDigit(answer,i);
		}
	}
	for (int i = 1; i <= 4; i = i + 1) {
		for (int j = 1; j <= 4 && nthDigit(guess,i) > 0; j = j + 1) {
											// don't try a cleared peg
			if (nthDigit(guess,i) == nthDigit(answer,j)) {
				white = white + 1;					// digit in incorrect spot
				clearNthDigit(guess,i);  // don't match these again
				clearNthDigit(answer,j);
			}
		}
	}
}

int nthDigit(int combination,int position) {
/*------------------------------------------------------------------
nthDigit
Identifies the n'th digit of a 4 digit number
This implementation treats the 1's place as the 4th digit,
but the program would work equally well if it counted in reverse.
-------------------------------------------------------------------*/
	int current;			// current digit in the 1's place
	while (position < 4) {
		combination = combination / 10;		// knock off a digit
		position = position + 1;				// desired digit moved to the right
	}
	//  Now that the desired digit is in the one's place,
	// remove the leading digits.
	return (combination % 10);			// remainder modulo 10 is one's place
}

void clearNthDigit(int &combination,int position) {
/*--------------------------------------------------------------
clearNthDigit
Replaces the n'th digit of a 4-digit number with a 0
Again, this implementation counts digits from left to right,
but counting in the reverse order is also valid.
--------------------------------------------------------------*/
	int current;			// position currently being examined
	int digitValue;			// the actual positional value of that digit
	current = 4;			// the 4th digit is in the 1's place
	digitValue = 1;			// the 1's place has a value of 1
	while (position < current) {
		digitValue = digitValue * 10;	// previou digit has 10 times the value
		current = current - 1;			// digitValue refers to previous digit
	}
	// subtract the digit minus itself to make it into a zero digit
	combination = combination - (digitValue * nthDigit(combination,position));
}

int generateAnswer() {
    int combination; // Variable to store the combination.
    char yesNo;
    do { // Do-while for input validation.
        cout << "Would you like to pick your own combination?" << endl;
        cin >> yesNo; // User input.
    } while (yesNo != 'y' && yesNo != 'n'); // Checks if y or n entered.
    if (yesNo == 'y') { // Asks user for combination to guess.
        do { // Do-while for input validation.
            cout << "Enter a combination (Enter 4 numbers between 1 and 8):  ";
            cin >> combination; // User input.
        } while (floor(log10(combination)) + 1 != 4 
                    && (combination % 10) < 1 && (combination % 10) > 8
                    && ((combination / 10) % 10) < 1 && ((combination / 10) % 10) > 8
                    && ((combination / 100) % 10) < 1 && ((combination / 100) % 10) > 8
                    && ((combination / 1000) % 10) < 1 && ((combination / 1000) % 10) > 8
                    ); // Checks if number of digits entered is correct.
    return combination; // Returns user input.
    }
    else if (yesNo == 'n') {
        combination = 1000 * rollDie(8) + 100 * rollDie(8) + 10 * rollDie(8) + rollDie(8); // Pick a number. Each digit can be from 1-8 (% 8 gives 0=7).
        cout << "The randomly generated combination is " << combination << "." << endl;
        return combination; // Returns random number.
    }
}

void generateSearchSpace(int guesses[],int length) {
    int units; // Units place of the possible combination.
    int tens; // Tens place of the possible combination.
    int hundreds; // Hundreds place of the possible combination.
    int thousands; // Thousands place of the possible combination.
    for (units = 0; units <= length - 1; units = units + 1) {
        tens = units / 8; // Increments by truncation one for every eight of previous digit.
        hundreds = tens / 8; // Increments by truncation one for every eight of previous digit.
        thousands = hundreds / 8; // Increments by truncation one for every eight of previous digit.
        guesses[units] =   (1 + (units % 8)) * pow(10,0) // Only the units place is incremented by loop.
                         + (1 + (tens % 8)) * pow(10,1) // And puts it in the current element number i.
                         + (1 + (hundreds % 8)) * pow(10,2)
                         + (1 + (thousands % 8)) * pow(10,3);
    }
}

int methodicalEliminate(int answer) { // Methodically eliminates guesses starting with the first element.
    int length = 4096; // Upper limit of nonzero elements in the array.
    const int SIZE = length;
    int black; // Counter for black pegs.
    int white; // Counter for white pegs.
    int guessNum = 0; // Counter for number of guesses made.
    int guesses[SIZE]; // Array of length length for storing all possible outcomes.
    generateSearchSpace(guesses,length); // Generates all possible outcomes and stores them in the array.
    while (black != 4) { // Or length < 1, or length != 1, all are nonwinning conditions.
        cout << "Guessing " << guesses[0] << "..." << endl; // Prints the current first element in the array.
        evaluate(answer,guesses[0],black,white); // Evaluates the peg profile of the first element.
        trim(guesses,length,guesses[0],black,white); // Trims the guess and all the elements with a nonsimilar peg profile from the array.
        guessNum = guessNum + 1; // Increments the number of guesses made.
    }
    cout << "Methodical Eliminate required " << guessNum << " tries." << endl; // Print number of guesses needed.
    return guessNum; // Returns the number of guesses needed.
}

int guessAndEliminate(int answer) { // Methodically eliminates guesses starting with a random element.
    int length = 4096; // Upper limit of nonzero elements in the array.
    const int SIZE = length;
    int black; // Counter for black pegs.
    int white; // Counter for white pegs.
    int guessNum = 0; // Counter for number of guesses made.
    int guesses[SIZE]; // Array of length length for storing all possible outcomes.
    int guessPosition; // Position of element in the array.
    generateSearchSpace(guesses,length); // Generates all possible outcomes and stores them in the array.
    while (black != 4) { // Or length < 1, or length != 1, all are nonwinning conditions.
        guessPosition = rand() % length; // Randomly generates a position of an element in the array.
        cout << "Guessing " << guesses[guessPosition] << "..." << endl; // Prints a random element in the array.
        evaluate(answer,guesses[guessPosition],black,white); // Evaluates the peg profile of the randomly selected element.
        trim(guesses,length,guesses[guessPosition],black,white); // Trims the guess and all the elements with a nonsimilar peg profile from the array.
        guessNum = guessNum + 1; // Increments the number of guesses made.
    }
    cout << "Guess and eliminate required " << guessNum << " tries." << endl; // Print number of guesses needed.
    return guessNum; // Returns the number of guesses needed.
}

int guessThreeThenEliminate(int answer) { // Methodically eliminates guesses starting with three random elements.
    int length = 4096; // Upper limit of nonzero elements in the array.
    const int SIZE = length;
    int black; // Counter for black pegs for the methodical eliminate.
    int white; // Counter for white pegs for the methodical eliminate.
    int firstBlack; // Counter for black pegs for the first random guess.
    int firstWhite; // Counter for white pegs for the first random guess.
    int secondBlack; // Counter for black pegs for the second random guess.
    int secondWhite; // Counter for white pegs for the second random guess.
    int thirdBlack; // Counter for black pegs for the third random guess.
    int thirdWhite; // Counter for white pegs for the third random guess.
    int guessNum = 3; // Initialized counter for the methodical eliminate.
    int guesses[SIZE]; // Array of length length for storing all possible outcomes.
    int firstGuessPosition = rand() % length; // Randomly selected first position for array.
    int secondGuessPosition = rand() % length; // Randomly selected second position for array.
    int thirdGuessPosition = rand() % length; // Randomly selected third position for array.
    generateSearchSpace(guesses,length); // Generates all possible outcomes and stores them in the array.
    cout << "Guessing " << guesses[firstGuessPosition] << "..." << endl; // Prints the element at the first random position in the array.
    cout << "Guessing " << guesses[secondGuessPosition] << "..." << endl; // Prints the element at the second random position in the array.
    cout << "Guessing " << guesses[thirdGuessPosition] << "..." << endl; // Prints the element at the third random position in the array.
    evaluate(answer,guesses[firstGuessPosition],firstBlack,firstWhite); // Evaluates the peg profile of the first random element.
    trim(guesses,length,guesses[firstGuessPosition],firstBlack,firstWhite); // Trims the guess and all the elements with a nonsimilar peg profile from the array.
    if (firstBlack == 4) { // Winning condition.
        return 1; // Returns one guess needed.
    }
    evaluate(answer,guesses[secondGuessPosition],secondBlack,secondWhite); // Evaluates the peg profile of the second random element.
    trim(guesses,length,guesses[secondGuessPosition],secondBlack,secondWhite); // Trims the guess and all the elements with a nonsimilar peg profile from the array.
    if (secondBlack == 4) { // Winning condition.
        return 2; // Returns two guesses needed.
    }
    evaluate(answer,guesses[thirdGuessPosition],thirdBlack,thirdWhite); // Evaluates the peg profile of the third random element.
    trim(guesses,length,guesses[thirdGuessPosition],thirdBlack,thirdWhite); // Trims the guess and all the elements with a nonsimilar peg profile from the array.
    if (thirdBlack == 4) { // Winning condition.
        return 3; // Returns three guesses needed.
    }
    while (black != 4) { // Or length < 1, or length != 1, all are nonwinning conditions.
        cout << "Guessing " << guesses[0] << "..." << endl; // Prints the current first element in the array.
        evaluate(answer,guesses[0],black,white); // Evaluates the peg profile of the first element.
        trim(guesses,length,guesses[0],black,white); // Trims the guess and all the elements with a nonsimilar peg profile from the array.
        guessNum = guessNum + 1; // Increments the number of guesses made.
    }
    cout << "Guess three then eliminate required " << guessNum << " tries." << endl; // Print number of guesses needed.
    return guessNum; // Returns the number of guesses needed.
}

void trim(int guesses[],int& length,int guess,int& black,int& white) { // Trims the guess and all the elements with a nonsimilar peg profile from the array.
    int checkBlack; // Counter of black pegs for the guess.
    int checkWhite; // Counter of white pegs for the guess.
    const int SIZE = length;
    int trimmed[SIZE]; // Array for the remaining possible values.
    for (int n = 0; n < length; n = n + 1) {
        trimmed[n] = guesses[n]; // Loop for initializing the test array to equal the original array.
    }
    for (int n = 0; n < length; n = n + 1) {
        if (guess == trimmed[n]) { // Searches for the element in the secondary array that is the same as the current guess and zeros it out.
            trimmed[n] = 0;
        }
    }
    for (int i = 0; i < length; i = i + 1) {
        evaluate(guess,trimmed[i],checkBlack,checkWhite);
        if (checkBlack != black || checkWhite != white) { // For nonzero element in the array,
            trimmed[i] = 0; // If the peg numbers don't match, the element is zeroed out.
        }
    }
    int k = 0; // Initializing new length counter.
    for (int j = 0; j < length; j = j + 1) { // Passes every nonzero element from the secondary array,
        if (trimmed[j] != 0) { // back to the front of the original array.
            guesses[k] = trimmed[j];
            k = k + 1; // Increments the number of nonzero elements.
        }
    }
    length = k; // Assignment of new length.
}
/* 
Anthony Marucci
Section 001
Cmpsc 121
Mastermind(computer guess version)
 */

#include <iostream>
#include <math.h>
#include <cstdlib>

using namespace std;
//get the number for the computer to guess.
int getNum(){
	int num = 0;
	for (int i = 0; i < 4; i ++){
		num += (int)(((rand() % 8) + 1) * pow(10, i));
	}
	return num;
}

//this will return the nth digit in the number
//it really only is because this will be used more than once
int nthDigit( int combination, int position ){
	int current;			// current digit in the 1's place
	while (position < 4)
	{
		combination /= 10;		// knock off a digit
		position++;				// desired digit moved to the right
	}
	//  Now that the desired digit is in the one's place,
	// remove the leading digits.
	return (combination % 10);			// remainder modulo 10 is one's place
}

//this will set on of the digits to zero. so no extra pegs are awarded
void clearNthDigit( int &combination, int position ){
	int current = 4, digitValue = 1;			// the actual positional value of that digit
	while (position < current)
	{
		digitValue *= 10;	// previou digit has 10 times the value
		current--;			// digitValue refers to previous digit
	}
	// subtract the digit minus itself to make it into a zero digit
	combination -= digitValue * nthDigit( combination, position );
}

//asks the user for the answer
int generateAnswer(){
	int number;

	do {
		cout << "Pick a number(0 for a random number):";
		cin >> number;
	}while((number < 1111 || number > 9999) && number != 0);

	//set a random number to guess, if user chooses that
	if(number == 0)
		number = getNum(); 

	return number;
}

//populates the array
//as units increments tens and hundreds and thousands will increase and because of integer division
//it will increment by one
int generateSearchSpace(int guesses[], int length) {
    int tens, hundreds,thousands;
    
    for (int ones = 0; ones <= length - 1; ones ++) {
        tens = ones / 8;
        hundreds = tens / 8;
        thousands = hundreds / 8;
        
        guesses[ones] =   ((1 + ones % 8) * pow(10,0))+ ((1 + tens % 8) * pow(10,1)) 
                + ((1 + hundreds % 8) * pow(10,2)) + ((1 + thousands % 8) * pow(10,3));
    }
}

//checks to see how many black pegs and white pegs awarded
void evaluate(int guess, int answer, int &black, int &white){
	black = 0;			// nothing confirmed yet
	white = 0;
	
	for (int i=1; i<=4; i++)
		if (nthDigit( guess, i ) == nthDigit( answer, i ) )
		{
			black++;						// digit in correct spot
			clearNthDigit( guess, i );		// don't match these again
			clearNthDigit( answer, i );
		}
	for (int i=1; i<=4; i++)
		for (int j=1; j<=4 && nthDigit(guess,i)>0; j++)
			// don't try a cleared peg
			if (nthDigit( guess,i ) == nthDigit( answer, j ) )
			{
				white++;					// digit in incorrect spot
				clearNthDigit( guess, i );  // don't match these again
				clearNthDigit( answer, j );
			}
}

//"deletes" elements from an array by setting them to 0 in a temporary array and then putting
//non-zero values in the real array.
int trim(int guesses[], int length, int guess, int black, int white){
	int guesses2[length], tempLength = 0;//used to copy all the possible values of guesses and a temporary length
	int black2,white2;
	
	//copy guesses into temporary array
	for(int i = 0; i <= length; i ++)
		guesses2[i] = guesses[i];
	
	if(black == 4){
	    return 1;
	}else if (white == 0 && black == 0){//check first to see if there are pegs
	    for(int i = 0; i < length; i ++) //remove any number from that array that contains 
	        for(int x = 1; i <= 4; x ++) // a number from the value that has no white or black pegs
	            for(int z = 1; z <= 4; z ++)
	                if(nthDigit(guesses2[i],z) == nthDigit(guess, x))
	                    guesses2[i] = 0;              
	}else { //if there are pegs, find every other number that has the same amount of pegs, as they are
    	for(int i = 0; i < length; i ++){ //candidates to be to correct answer
    	    evaluate(guess, guesses2[i], black2, white2);
    	    if (white != white2 && black != black2)
    	        guesses2[i] = 0;
    	}
    	guesses2[0] = 0; //we know that this value is not the answer, so set it to 0 so you don't guess it again
	}
	    
	//put all the correct values into the array.
	for(int i = 0; i < length; i ++){
		if(guesses2[i] != 0){
			guesses[tempLength] = guesses2[i];
			tempLength ++;
		}
	}
	
	int temp;
	cin >>temp;

	//set the length to the proper length as counted by the loop
	return tempLength;
}

int methodicalEliminate(int answer){
	int length = 4096;
	int tries = 0, guess[length], black, white;

	//populate the array
	generateSearchSpace(guess, length);

	//start to check the digits using the trim function.
	while(black != 4){
        cout << "Guessing " << guess[0] << "...\n";
        cout << "here";
        evaluate(guess[0], answer, black, white);
        cout << "here2";
        length = trim(guess, length, guess[0], black, white);
        tries += 1;
        cout<< "here2";
	}

	return tries;
}

int guessAndEliminate(){
	int tries;
	return tries;
}

int guessThreeAndEliminate(){
	int tries;
	return tries;
}

//calls all the methods that do the workload.
void playMasterMind(){
	int blackPegs, whitePegs, number, tries;

	//input the number
	number = generateAnswer();
	
	//call the three methods for the different guessing methods
	tries = methodicalEliminate(number);
}

//main method, just calls playMastermind() and loops so it can be played more than once
int main()
{
	char yesNo = 'y';

	while (yesNo == 'y'){
		playMasterMind(); //calls the method that will handle one game.
		cout << "Play another game?(y or n): ";
		cin >> yesNo;
	}
	return 0;
}

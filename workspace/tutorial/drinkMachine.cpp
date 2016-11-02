// Drink Machine Simulation
// Roger Christman		Spring 2013
// Motivated by Programming Challenge #12 in 
// "Starting Out with C++" by Tony Gaddis
//
// This tutorial practices the use of structures to
// maintain and record information.  The simulated
// machine holds onto both the drinks it sells and
// the change it has available.
//
// This machine accepts dollar bills, but never returns them as change.
#include <iostream>
#include <iomanip>
using namespace std;

//  Information recorded about beverages within the machine.
struct DrinkType {
	char	name[15];			// name of the drink
	int		price;				// price (in cents)
	int		stock;				// how many are available
};

//  Information recorded about coins within the machine
struct CoinType {
	char	name[10];			// name of the coin
	int		value;				// value of coin (in cents)
	int		stock;				// how many are available
};

//  Function prototypes for this program
void	insertCoin( CoinType &, int & );	// insert a coin into the machine
void	coinReturn( CoinType[], int, int& );	// return coins from the machine
bool	purchaseable( DrinkType, int );		// can we buy this drink?
void	purchase( DrinkType &, int & );		// if so, purchase the drink

//  This driver program provides a very simple user-interface,
//  and should not require any major changes.  The focus of the
//  tutorial is in the functions that follow it.
int main()
{
	struct DrinkType drinks[] =
		{ { "Pepper Cola", 75, 5 }, { "Rot Beer", 75, 5 },
		  { "Lemon Sludge", 80, 5 }, { "Grape Ape", 80, 5 } };
	struct CoinType coins[] =
		{ { "quarter", 25, 5 }, { "dime", 10, 5 }, { "nickel", 5, 20 } };
	
	char response;						// user-interface input
	int  balance = 0;					// money spent so far

	cout << left;						// left justify strings below
	cout << fixed << setprecision(2);	// all real numbers reported this way
	cout << "Welcome to the not-so-refreshing Drink Simulation" << endl;
	do {
		cout << endl;
		cout << "Current Balance:  $" << (balance*0.01)<< endl;
		cout << "Please select one of these choices by typing the letter:" << endl;
		cout << setw(25) << "buy (P)epper Cola" << "insert a (Q)uarter" << endl;
		cout << setw(25) << "buy (R)ot Beer" << "insert a (D)ime" << endl;
		cout << setw(25) << "buy (L)emon Sludge" << "insert a (N)ickel" << endl;
		cout << setw(25) << "buy (G)rape Ape" << "insert (O)ne Dollar" << endl;
		cout << setw(25) << "press the (C)oin Return" << "e(X)it the simulation" << endl;

		cin >> response;
		switch (response)
		{
		case 'p': case 'P':
			if (purchaseable( drinks[0], balance ))
				purchase( drinks[0], balance );
			break;
		case 'r': case 'R':
			if (purchaseable( drinks[1], balance ))
				purchase( drinks[1], balance );
			break;
		case 'l': case 'L':
			if (purchaseable( drinks[2], balance ))
				purchase( drinks[2], balance );
			break;
		case 'g': case 'G':
			if (purchaseable( drinks[3], balance ))
				purchase( drinks[3], balance );
			break;
		case 'q': case 'Q':
			insertCoin( coins[0], balance );
			break;
		case 'd': case 'D':
			insertCoin( coins[1], balance );
			break;
		case 'n': case 'N':
			insertCoin( coins[2], balance );
			break;
		case 'o': case 'O':
			balance += 100;
			break;
		case 'c': case 'C':
			coinReturn( coins, 3, balance );
		}
	} while ( response != 'x' && response != 'X' );
}

//  TUTORIAL:  Complete the functions below
//  Remember, to manipulate a structure, type the variable name followed by a period (.)
//  Visual Studio will remind you what the member variables are when you type that period

//  InsertCoin
//  Supplies a coin to the machine, recording the balance so far
//      The number of coins in the machine will increase
//  Parameters:
//		coin		(modified struct)	the coin inserted (one more)
//		money		(modified int)		amount of money entered so far (increased)
void	insertCoin( CoinType &coin, int &money )
{
    cout << "Clink!" << endl;	// you may remove this line!
    coin.stock = coin.stock + 1;
    money = money + coin.value;
}

//  Purchase
//  Purchases a drink.  The cost of the drink is deducted
//		from the money supplied -- but the change is not yet returned.
//		(in case the person wants to make additional purchases)
//  Parameters:
//		drink		(modified struct)	the selected beverage (one fewer)
//		money		(modiifed int)		the customer's credit (reduced when spent)	
//  NOTE: YOu may assume that the Purchaseable function below has
//  already been called and yields a true result.
void	purchase( DrinkType &drink, int &money )
{
	cout << "Enjoy your " << drink.name << endl;
	drink.stock = drink.stock - 1;
	money = money - drink.price;
}

//  Purchaseable
//  Determines whether a drink can be purchased.
//  If it cannot, it will also say why not
//     (either not enough money is supplied, or the drink is out of stock)
//  Parameters:
//		drink		(input struct)		the selected beverage
//		money		(input int)			the amount of money supplied
// NOTE: This does not actually change any data -- it simply answers the
// boolean question, and produces an output if the answer is false.
bool	purchaseable( DrinkType drink, int money )
{
    if (money >= drink.price && drink.stock > 0)
	    return true;
}




//  CoinReturn
//  Returns change to the customer (and out of the machine)
//  NOTE: For best results, take advantage of the array of structures.
//  The code should then work with any monetary system.
//
//  Hint:  Recall the programming question from the first midterm
//      which also computed change to return.
//  NOTE:  The array is there to allow code repetition in a loop.
//	    For full credit, your implementation must take advantage of that
//			In other words, the number 25 must NOT appear here!
//
//  Do not return coins the machine does not havr --
//     do not leave the machine with a negative number of any coin
//			DO display what coins are being returned
//
//  Parameters:
//		coins		(modified struct array)	all the types of coins available
//	    coinTypes	(input int)				size of coins array
//		change		(input integer	)		amount of change to return		
void	coinReturn( CoinType coins[], int coinTypes, int& change )
{
    int counter[3] = {0,0,0};
    for (int i; i < coinTypes; i = i + 1) {
        while (coins[i].stock >  0 && change >= coins[i].value) {
            counter[i] = counter[i] + 1;
            coins[i].stock = coins[i].stock - 1;
            change = change - coins[i].value;
        }
    }
    
    cout << "Change returned:" << endl;
    cout << counter[0] << " quarters." << endl;
    cout << counter[1] << " dimes." << endl;
    cout << counter[2] << " nickels." << endl;
	
	change = 0;					// assumes all change has been returned
}